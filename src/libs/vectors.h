#ifndef VECTORS_H
#define VECTORS_H

#include <stdlib.h>
#include <math.h>

struct vector_2d{
    double x;
    double y;
};typedef struct vector_2d vector_2d;

struct matrix_2x2{
    double element[4];
};

void vector_2d_add(vector_2d* a, vector_2d*b);
vector_2d* vector_2d_add_return(vector_2d* a, vector_2d*b);
void vector_2d_sub(vector_2d* a, vector_2d*b);
vector_2d* vector_2d_sub_return(vector_2d* a, vector_2d*b);
void vector_2d_mult(vector_2d* a, double b);
vector_2d* vector_2d_mult_return(vector_2d* a, double b);
void vector_2d_normilize(vector_2d* v);
vector_2d* vector_2d_normilize_return(vector_2d* v);
double vector_2d_dot_mult(vector_2d* a, vector_2d*b);


#endif