#ifndef MNIST_IO_H
#define MNIST_IO_H

#include <stdint.h>

typedef struct { int n; uint8_t* x; } MNISTImages;
typedef struct { int n; uint8_t* y; } MNISTLabels;

MNISTImages load_mnist_images(const char* path);
MNISTLabels load_mnist_labels(const char* path);
void load_pgm_28x28(const char* path, float x[784]);
void mnist_u8_to_float(const uint8_t* src784, float dst784[784]);
void maybe_invert(float x[784]);

#endif