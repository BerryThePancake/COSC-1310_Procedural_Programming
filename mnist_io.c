#include "mnist_io.h"
#include <stdio.h>
#include <stdlib.h>

static void die(const char* msg) { fprintf(stderr, "Error: %s\n", msg); exit(1); }

static uint32_t read_be_u32(FILE* f) {
  uint8_t b[4];
  if (fread(b, 1, 4, f) != 4) die("failed to read u32");
  return ((uint32_t)b[0] << 24) | ((uint32_t)b[1] << 16) | ((uint32_t)b[2] << 8) | (uint32_t)b[3];
}

MNISTImages load_mnist_images(const char* path) {
  FILE* f = fopen(path, "rb");
  if (!f) die("cannot open images idx file");
  uint32_t magic = read_be_u32(f);
  uint32_t n = read_be_u32(f);
  uint32_t rows = read_be_u32(f);
  uint32_t cols = read_be_u32(f);
  size_t total = (size_t)n * 784;
  uint8_t* buf = (uint8_t*)malloc(total);
  fread(buf, 1, total, f);
  fclose(f);
  return (MNISTImages){(int)n, buf};
}

MNISTLabels load_mnist_labels(const char* path) {
  FILE* f = fopen(path, "rb");
  if (!f) die("cannot open labels idx file");
  uint32_t magic = read_be_u32(f);
  uint32_t n = read_be_u32(f);
  uint8_t* buf = (uint8_t*)malloc((size_t)n);
  fread(buf, 1, (size_t)n, f);
  fclose(f);
  return (MNISTLabels){(int)n, buf};
}

void mnist_u8_to_float(const uint8_t* src784, float dst784[784]) {
  for (int i = 0; i < 784; i++) dst784[i] = src784[i] / 255.0f;
}

void maybe_invert(float x[784]) {
  float mean = 0.0f;
  for (int i = 0; i < 784; i++) mean += x[i];
  if ((mean / 784.0f) > 0.5f) {
    for (int i = 0; i < 784; i++) x[i] = 1.0f - x[i];
  }
}