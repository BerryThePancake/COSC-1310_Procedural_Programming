#include "mnist_io.h"
#include "mnist_math.h"
#include <stdio.h>
#include <stdlib.h>

// Helper to read Big-Endian integers from MNIST files
static uint32_t read_be_u32(FILE* f) {
    uint8_t b[4];
    if (fread(b, 1, 4, f) != 4) return 0;
    return ((uint32_t)b[0] << 24) | ((uint32_t)b[1] << 16) | ((uint32_t)b[2] << 8) | (uint32_t)b[3];
}

MNISTImages load_mnist_images(const char* path) {
    FILE* f = fopen(path, "rb");
    if (!f) return (MNISTImages){0, NULL};
    
    uint32_t magic = read_be_u32(f);
    uint32_t n = read_be_u32(f);
    read_be_u32(f); // rows (28)
    read_be_u32(f); // cols (28)
    
    uint8_t* buf = (uint8_t*)malloc((size_t)n * M_IN);
    if (buf) fread(buf, 1, (size_t)n * M_IN, f);
    fclose(f);
    return (MNISTImages){(int)n, buf};
}

MNISTLabels load_mnist_labels(const char* path) {
    FILE* f = fopen(path, "rb");
    if (!f) return (MNISTLabels){0, NULL};
    
    uint32_t magic = read_be_u32(f);
    uint32_t n = read_be_u32(f);
    
    uint8_t* buf = (uint8_t*)malloc((size_t)n);
    if (buf) fread(buf, 1, (size_t)n, f);
    fclose(f);
    return (MNISTLabels){(int)n, buf};
}

void mnist_u8_to_float(const uint8_t* src, float dst[M_IN]) {
    for (int i = 0; i < M_IN; i++) {
        // Normalizing 0-255 to 0.0-1.0
        dst[i] = src[i] / 255.0f;
    }
}