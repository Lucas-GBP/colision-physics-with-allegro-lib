#ifndef PHYSICS_H
#define PHYSICS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

enum shape_types {Rectangle, Circle};

struct rectangle_shape{
    uint16_t width;
    uint16_t height;
};

struct circle_shape{
    uint16_t radius;
};

struct solid_object{
    int32_t position[2];
    int16_t velocity[2];
    int16_t axie_velocity;
    void (*colision_reaction)(void*);
    uint16_t mass;
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
    int32_t x, int32_t y,
    int16_t vx, int16_t vy,
    int16_t axie_v,
    void (*colision_reaction)(void*),
    uint16_t mass,
    enum shape_types shape_type,
    union shapes shape
);
void destroy_solid_object(solid_object* object);
solid_object* copy_solid_object(solid_object* object);
solid_object* random_object(int32_t width, int32_t height, enum shape_types shape_type);
void generic_colision_reaction(solid_object* object);
void print_solid_object(solid_object* object);
void move_object(solid_object* object);
bool border_colision_detection(solid_object* object, int32_t width, int32_t height);
bool border_colision_handling(solid_object* object, int32_t width, int32_t height);
void update_physics(solid_object* objects[], int obj_quant, uint32_t width, uint32_t height);

#endif