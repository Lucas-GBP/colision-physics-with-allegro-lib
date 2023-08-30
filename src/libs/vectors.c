#include "vectors.h"

void print_2dVector(vector_2d* v){
    printf("%f\t%f\n", v->x, v->y);
}

void vector_2d_add(vector_2d* a, vector_2d*b){
    a->x += b->x;
    a->y += b->y;
}
void vector_2d_int_add(vector_2d_int* a, vector_2d_int* b){
    a->x += b->x;
    a->y += b->y;
}
vector_2d* vector_2d_add_return(vector_2d* a, vector_2d*b){
    vector_2d* v = malloc(sizeof(vector_2d));
    v->x = a->x + b->x;
    v->y = a->y + b->y;

    return v;
}
vector_2d_int* vector_2d_int_add_return(vector_2d_int* a, vector_2d_int* b){
    vector_2d_int* v = malloc(sizeof(vector_2d_int));
    v->x = a->x + b->x;
    v->y = a->y + b->y;

    return v;
}
void vector_2d_sub(vector_2d* a, vector_2d*b){
    a->x -= b->x;
    a->y -= b->y;
}
void vector_2d_int_sub(vector_2d_int* a, vector_2d_int* b){
    a->x -= b->x;
    a->y -= b->y;
}
vector_2d* vector_2d_sub_return(vector_2d* a, vector_2d*b){
    vector_2d* v = malloc(sizeof(vector_2d));
    v->x = a->x - b->x;
    v->y = a->y - b->y;

    return v;
}
vector_2d_int* vector_2d_int_sub_return(vector_2d_int* a, vector_2d_int* b){
    vector_2d_int* v = malloc(sizeof(vector_2d_int));
    v->x = a->x - b->x;
    v->y = a->y - b->y;

    return v;
}
void vector_2d_mult(vector_2d* a, float b){
    a->x *= b;
    a->y *= b;
}
void vector_2d_int_mult(vector_2d_int* a, int b){
    a->x *= b;
    a->y *= b;
}
vector_2d* vector_2d_mult_return(vector_2d* a, float b){
    vector_2d* v = malloc(sizeof(vector_2d));
    v->x = a->x*b;
    v->y = a->y*b;

    return v;
}
vector_2d_int* vector_2d_int_mult_return(vector_2d_int* a, int b){
    vector_2d_int* v = malloc(sizeof(vector_2d_int));
    v->x = a->x*b;
    v->y = a->y*b;

    return v;
}
void vector_2d_normilize(vector_2d* v){
    float r = 1/sqrtf((v->x*v->x)+(v->y*v->y));
    v->x *= r;
    v->y *= r;
}
vector_2d* vector_2d_normilize_return(vector_2d* a){
    vector_2d* v = malloc(sizeof(vector_2d));
    float r = 1/sqrtf((a->x*a->x)+(a->y*a->y));
    v->x = a->x*r;
    v->y = a->y*r;

    return v;
}
vector_2d* vector_2d_int_normilize_return(vector_2d_int* a){
    vector_2d* v = malloc(sizeof(vector_2d));
    float r = 1/sqrtf((float)((a->x*a->x)+(a->y*a->y)));
    v->x = (float)(a->x)*r;
    v->y = (float)(a->y)*r;

    return v;
}
float vector_2d_dot_mult(vector_2d* a, vector_2d*b){
    return a->x*b->x + a->y*b->y;
}
int vector_2d_int_dot_mult(vector_2d_int* a, vector_2d_int* b){
    return a->x*b->x + a->y*b->y;
}
void vector_3d_cross_mult(vector_3d* a, vector_3d* b){
    vector_3d v = {
        .x = a->y*b->z - a->z*b->y,
        .y = a->z*b->x - a->x*b->z,
        .z = a->x*b->y-a->y*b->x,
    };

    *a = v;
}
vector_3d* vector_3d_cross_mult_return(vector_3d* a, vector_3d* b){
    vector_3d* v = malloc(sizeof(vector_3d));

    v->x = a->y*b->z - a->z*b->y;
    v->y = a->z*b->x - a->x*b->z;
    v->z = a->x*b->y-a->y*b->x;

    return v;
}
vector_3d* vector_2d_cross_mul(vector_2d* a, vector_2d* b){
    vector_3d* v = malloc(sizeof(vector_3d));
    
    v->x = 0;
    v->y = 0;
    v->z = a->x*b->y-a->y*b->x;

    return v;
}
vector_3d_int* vector_2d_int_cross_mult(vector_2d_int* a, vector_2d_int* b){
    vector_3d_int* v = malloc(sizeof(vector_3d_int));

    v->x = 0;
    v->y = 0;
    v->z = a->x*b->y-a->y*b->x;

    return v;
}

float vector2d_distance(vector2d* a, vector2d* b){
    const float dx = a->x - b->x;
    const float dy = a->y - b->y;

    return sqrtf(dx*dx + dy*dy);
}

void vector2d_rotate(vector2d* v, vector2d* r){
    const vector2d old = *v;
    v->x = old.x*r->x - old.y*r->y;
    v->y = old.y*r->x + old.x*r->y;
}

void vector2d_rotateInverse(vector2d* v, vector2d* r){
    const vector2d old = *v;
    v->x = old.x*r->x + old.y*r->y;
    v->y = old.y*r->x - old.x*r->y;
}

void vector2d_rotateTheta(vector2d* v, float theta){
    const vector2d old = *v;
    v->x = old.x*cosf(theta) - old.y*sinf(theta);
    v->y = old.y*cosf(theta) + old.x*sinf(theta);
}

void vector2d_rotateCenter(vector2d* v, vector2d* r, vector2d* c){
    vector_2d_sub(v, c);
    vector2d_rotate(v, r);
    vector_2d_add(v, c);
}

void vector2d_rotateCenterInverse(vector2d* v, vector2d* r, vector2d* c){
    vector_2d_sub(v, c);
    vector2d_rotateInverse(v, r);
    vector_2d_add(v, c);
}

bool intersectionPoint(vector2d* a, vector2d* b, vector2d* c, vector2d* d, vector2d* v){
    vector2d G = *a;
    vector2d H = *d;
    vector2d J = *c;
    vector_2d_sub(&H, c); // d-c
    if(H.x == 0){
        return false;
    }
    vector_2d_sub(&G, b); // a-b
    vector_2d_sub(&J, a); // c-a
    
    const float l = (H.x*G.y+(J.x-G.x)*H.y);
    if(l == 0){
        return false;
    }
    const float s = -(H.x*J.y)/l;
    const float t = -(s*G.x-J.x)/H.x;

    if(0 > s || s > 1 || 0 > t || t > 1){
        return false;
    }

    v->x = a->x + s*(b->x-a->x);
    v->y = a->y + s*(b->y-a->y);

    return true;
}