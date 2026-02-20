#ifndef MNIST_MATH_H
#define MNIST_MATH_H

#include <stdint.h>

// Renamed to avoid Windows.h conflicts
#define M_IN 784
#define M_H  128
#define M_OUT 10

typedef struct {
    float W1[M_H][M_IN];
    float b1[M_H];
    float W2[M_OUT][M_H];
    float b2[M_OUT];
} Model;

void forward(const Model* m, const float x[M_IN], float z1[M_H], float a1[M_H], float z2[M_OUT], float p[M_OUT]);
int argmax(const float* a, int n);
float train_step_sgd(Model* m, const float x[M_IN], uint8_t y, float lr);

#endif