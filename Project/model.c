#include "model.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static uint32_t rng_state = 0x12345678u;

// Removed 'static' to match model.h
uint32_t xorshift32(void) {
  uint32_t x = rng_state;
  x ^= x << 13; x ^= x >> 17; x ^= x << 5;
  rng_state = x;
  return x;
}

static float frand_uniform(void) { return (xorshift32() / 4294967296.0f); }
static float frand_normal(void) {
  float u1 = frand_uniform();
  float u2 = frand_uniform();
  if (u1 < 1e-7f) u1 = 1e-7f;
  float r = sqrtf(-2.0f * logf(u1));
  return r * cosf(2.0f * (float)M_PI * u2);
}

void model_init(Model* m, uint32_t seed) {
  if (seed) rng_state = seed;
  float s1 = sqrtf(2.0f / (float)M_IN);
  for (int i = 0; i < M_H; i++) {
    m->b1[i] = 0.0f;
    for (int j = 0; j < M_IN; j++) m->W1[i][j] = s1 * frand_normal();
  }
  float s2 = sqrtf(2.0f / (float)M_H);
  for (int i = 0; i < M_OUT; i++) {
    m->b2[i] = 0.0f;
    for (int j = 0; j < M_H; j++) m->W2[i][j] = s2 * frand_normal();
  }
}

void model_save(const char* path, const Model* m) {
  FILE* f = fopen(path, "wb");
  if (!f) return;
  uint32_t magic = 0x4D4C5031u;
  fwrite(&magic, sizeof(magic), 1, f);
  fwrite(m, sizeof(Model), 1, f);
  fclose(f);
}

void model_load(const char* path, Model* m) {
  FILE* f = fopen(path, "rb");
  if (!f) return;
  uint32_t magic = 0;
  if (fread(&magic, sizeof(magic), 1, f) != 1) { fclose(f); return; }
  if (fread(m, sizeof(Model), 1, f) != 1) { fclose(f); return; }
  fclose(f);
}