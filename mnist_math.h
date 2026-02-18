#ifndef MNIST_MATH_H
#define MNIST_MATH_H

#include <stdint.h>

#define IN 784
#define H  128
#define OUT 10

typedef struct {
  float W1[H][IN];
  float b1[H];
  float W2[OUT][H];
  float b2[OUT];
} Model;

void forward(const Model* m, const float x[IN], float z1[H], float a1[H], float z2[OUT], float p[OUT]);
float train_step_sgd(Model* m, const float x[IN], uint8_t y, float lr);
int argmax(const float* a, int n);

#endif