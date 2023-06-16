#include "vectors.h"

void vector_2d_add(vector_2d* a, vector_2d*b){
    a->x += b->x;
    a->y += b->y;
}

vector_2d* vector_2d_add_return(vector_2d* a, vector_2d*b){
    vector_2d* v = malloc(sizeof(vector_2d));
    v->x = a->x + b->x;
    v->y = a->y + b->y;

    return v;
}

void vector_2d_sub(vector_2d* a, vector_2d*b){
    a->x -= b->x;
    a->y -= b->y;
}

vector_2d* vector_2d_sub_return(vector_2d* a, vector_2d*b){
    vector_2d* v = malloc(sizeof(vector_2d));
    v->x = a->x - b->x;
    v->y = a->y - b->y;

    return v;
}

void vector_2d_mult(vector_2d* a, double b){
    a->x *= b;
    a->y *= b;
}

vector_2d* vector_2d_mult_return(vector_2d* a, double b){
    vector_2d* v = malloc(sizeof(vector_2d));
    v->x = a->x*b;
    v->y = a->y*b;

    return v;
}

void vector_2d_normilize(vector_2d* v){
    double r = 1/sqrt((v->x*v->x)+(v->y*v->y));
    v->x *= r;
    v->y *= r;
}

vector_2d* vector_2d_normilize_return(vector_2d* a){
    vector_2d* v = malloc(sizeof(vector_2d));
    double r = 1/sqrt((a->x*a->x)+(a->y*a->y));
    v->x = a->x*r;
    v->y = a->y*r;

    return v;
}

double vector_2d_dot_mult(vector_2d* a, vector_2d*b){
    return a->x*b->x + a->y*b->y;
}