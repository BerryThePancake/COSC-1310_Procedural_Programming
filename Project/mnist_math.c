#include "mnist_math.h"
#include <math.h>

static inline float relu(float v) { return v > 0.0f ? v : 0.0f; }
static inline float relu_grad(float v) { return v > 0.0f ? 1.0f : 0.0f; }

static void softmax(const float* z, float* p, int n) {
  float maxv = z[0];
  for (int i = 1; i < n; i++) if (z[i] > maxv) maxv = z[i];
  float sum = 0.0f;
  for (int i = 0; i < n; i++) {
    p[i] = expf(z[i] - maxv);
    sum += p[i];
  }
  float inv = 1.0f / (sum > 1e-12f ? sum : 1e-12f);
  for (int i = 0; i < n; i++) p[i] *= inv;
}

int argmax(const float* a, int n) {
  int best = 0;
  for (int i = 1; i < n; i++) if (a[i] > a[best]) best = i;
  return best;
}

void forward(const Model* m, const float x[M_IN], float z1[M_H], float a1[M_H], float z2[M_OUT], float p[M_OUT]) {
  for (int i = 0; i < M_H; i++) {
    float s = m->b1[i];
    for (int j = 0; j < M_IN; j++) s += m->W1[i][j] * x[j];
    z1[i] = s;
    a1[i] = relu(s);
  }
  for (int k = 0; k < M_OUT; k++) {
    float s = m->b2[k];
    for (int i = 0; i < M_H; i++) s += m->W2[k][i] * a1[i];
    z2[k] = s;
  }
  softmax(z2, p, M_OUT);
}

float train_step_sgd(Model* m, const float x[M_IN], uint8_t y, float lr) {
  float z1[M_H], a1[M_H], z2[M_OUT], p[M_OUT];
  forward(m, x, z1, a1, z2, p);

  float py = p[y];
  if (py < 1e-12f) py = 1e-12f;
  float loss = -logf(py);

  float d2[M_OUT];
  for (int k = 0; k < M_OUT; k++) d2[k] = p[k];
  d2[y] -= 1.0f;

  for (int k = 0; k < M_OUT; k++) {
    m->b2[k] -= lr * d2[k];
    for (int i = 0; i < M_H; i++) m->W2[k][i] -= lr * (d2[k] * a1[i]);
  }

  float d1[M_H];
  for (int i = 0; i < M_H; i++) {
    float s = 0.0f;
    for (int k = 0; k < M_OUT; k++) s += m->W2[k][i] * d2[k];
    d1[i] = s * relu_grad(z1[i]);
  }

  for (int i = 0; i < M_H; i++) {
    m->b1[i] -= lr * d1[i];
    for (int j = 0; j < M_IN; j++) m->W1[i][j] -= lr * (d1[i] * x[j]);
  }
  return loss;
}