#ifndef VECTORS_H
#define VECTORS_H

#include <stdlib.h>
#include <math.h>

struct vector_2d{
    double x;
    double y;
};typedef struct vector_2d vector_2d;

struct vector_3d{
    double x;
    double y;
    double z;
};typedef struct vector_3d vector_3d;

struct vector_2d_int{
    int x;
    int y;
};typedef struct vector_2d_int vector_2d_int;

struct vector_3d_int{
    int x;
    int y;
    int z;
};typedef struct vector_3d_int vector_3d_int;

struct matrix_2x2{
    double element[4];
};

void vector_2d_add(vector_2d* a, vector_2d* b);
void vector_2d_int_add(vector_2d_int* a, vector_2d_int* b);
vector_2d* vector_2d_add_return(vector_2d* a, vector_2d* b);
vector_2d_int* vector_2d_int_add_return(vector_2d_int* a, vector_2d_int* b);
void vector_2d_sub(vector_2d* a, vector_2d* b);
void vector_2d_int_sub(vector_2d_int* a, vector_2d_int* b);
vector_2d* vector_2d_sub_return(vector_2d* a, vector_2d* b);
vector_2d_int* vector_2d_int_sub_return(vector_2d_int* a, vector_2d_int* b);
void vector_2d_mult(vector_2d* a, double b);
void vector_2d_int_mult(vector_2d_int* a, int b);
vector_2d* vector_2d_mult_return(vector_2d* a, double b);
vector_2d_int* vector_2d_int_mult_return(vector_2d_int* a, int b);
void vector_2d_normilize(vector_2d* v);
vector_2d* vector_2d_normilize_return(vector_2d* v);
vector_2d* vector_2d_int_normilize_return(vector_2d_int* v);
double vector_2d_dot_mult(vector_2d* a, vector_2d* b);
int vector_2d_int_dot_mult(vector_2d_int* a, vector_2d_int* b);


#endif