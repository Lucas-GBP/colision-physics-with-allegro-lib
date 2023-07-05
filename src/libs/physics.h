#ifndef PHYSICS_H
#define PHYSICS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

enum shape_types {Rectangle, Circle};

struct rectangle_shape{
    float width;
    float height;
};

struct circle_shape{
    float radius;
};

struct solid_object{
    float position[2];
    float velocity[2];
    float axie_velocity;
    void (*colision_reaction)(void*);
    float mass;
    enum shape_types shape_type;
    union{
        struct rectangle_shape rectangle;
        struct circle_shape circle;
    };
}; typedef struct solid_object solid_object;

union shapes{
    struct rectangle_shape rectangle;
    struct circle_shape circle;
};

solid_object* create_solid_object(
    float x, float y,
    float vx, float vy,
    float axie_v,
    void (*colision_reaction)(void*),
    float mass,
    enum shape_types shape_type,
    union shapes shape
);
void destroy_solid_object(solid_object* object);
solid_object* random_object(int width, int height, enum shape_types shape_type);
void generic_colision_reaction(solid_object* object);
void print_solid_object(solid_object* object);
void move_object(solid_object* object);
bool border_colision_detection(solid_object* object, int width, int height);
bool border_colision_handling(solid_object* object, int width, int height);
void update_physics(solid_object* objects[], int obj_quant, int width, int height);

#endif