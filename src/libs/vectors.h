#ifndef VECTORS_H
#define VECTORS_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

typedef struct vector_2d{
    float x;
    float y;
} vector_2d;
typedef vector_2d vector2d;

typedef struct vector_3d{
    float x;
    float y;
    float z;
} vector_3d;
typedef vector_3d vector3d;

struct vector_2d_int{
    int x;
    int y;
};typedef struct vector_2d_int vector_2d_int;

struct vector_3d_int{
    int x;
    int y;
    int z;
};typedef struct vector_3d_int vector_3d_int;

struct mastrix_2x2{
    float element[4];
};
// Debug
void print_2dVector(vector_2d* v);
// Add
void vector_2d_add(vector_2d* a, vector_2d* b);
void vector_2d_int_add(vector_2d_int* a, vector_2d_int* b);
vector_2d* vector_2d_add_return(vector_2d* a, vector_2d* b);
vector_2d_int* vector_2d_int_add_return(vector_2d_int* a, vector_2d_int* b);
// Sub
void vector_2d_sub(vector_2d* a, vector_2d* b);
void vector_2d_int_sub(vector_2d_int* a, vector_2d_int* b);
vector_2d* vector_2d_sub_return(vector_2d* a, vector_2d* b);
vector_2d_int* vector_2d_int_sub_return(vector_2d_int* a, vector_2d_int* b);
// Mult
void vector_2d_mult(vector_2d* a, float b);
void vector_2d_int_mult(vector_2d_int* a, int b);
vector_2d* vector_2d_mult_return(vector_2d* a, float b);
vector_2d_int* vector_2d_int_mult_return(vector_2d_int* a, int b);
// Normilize
void vector_2d_normilize(vector_2d* v);
vector_2d* vector_2d_normilize_return(vector_2d* v);
vector_2d* vector_2d_int_normilize_return(vector_2d_int* v);
// Dot product
float vector_2d_dot_mult(vector_2d* a, vector_2d* b);
int vector_2d_int_dot_mult(vector_2d_int* a, vector_2d_int* b);
// Cross product
void vector_3d_cross_mult(vector_3d* a, vector_3d* b);
vector_3d* vector_3d_cross_mult_return(vector_3d* a, vector_3d* b);
vector_3d* vector_2d_cross_mul(vector_2d* a, vector_2d* b);
vector_3d_int* vector_2d_int_cross_mult(vector_2d_int* a, vector_2d_int* b);
//others
float vector2d_distance(vector2d* a, vector2d* b);
void vector2d_rotate(vector2d* v, vector2d* r);
void vector2d_rotateInverse(vector2d* v, vector2d* r);
void vector2d_rotateTheta(vector2d* v, float theta);
void vector2d_rotateCenter(vector2d* v, vector2d* r, vector2d* c);
void vector2d_rotateCenterInverse(vector2d* v, vector2d* r, vector2d* c);
bool intersectionPoint(vector2d* a, vector2d* b, vector2d* c, vector2d* d, vector2d* v);

#endif