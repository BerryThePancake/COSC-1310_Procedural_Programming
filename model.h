#ifndef MODEL_H
#define MODEL_H

#include "mnist_math.h"

void model_init(Model* m, uint32_t seed);
void model_save(const char* path, const Model* m);
void model_load(const char* path, Model* m);
uint32_t xorshift32(void); // Exposed for shuffling

#endif