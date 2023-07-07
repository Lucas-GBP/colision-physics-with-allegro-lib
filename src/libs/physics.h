#ifndef PHYSICS_H
#define PHYSICS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include "vectors.h"

enum shapeTypes {Circle, Rectangle};

typedef struct circleShape{
	float radius;
} circleShape;
typedef struct rectangleShape{
	float width_2; 
	float height_2;
} rectangleShape;

typedef union Shapes {
	struct circleShape circle;
	struct rectangleShape rectangle;
} Shapes;

typedef struct solidObject {
	vector2d position;    //Center of mass
    vector2d velocity;    //Velocity vector
	vector2d rotation;    //Unitary rotation vector
	float inverseMass;    //mass^{-1}
	float theta;          //Rotation Angle 
	float omega;          //Angular Aceleration
	
	enum shapeTypes shapeType; // 
	union {
		struct circleShape circle;
		struct rectangleShape rectangle;
	} ;           //
} solidObject;
typedef solidObject solid_object;

//
// Functions
//

//
// Create a object
solidObject* create_solidObject(
    float x, float y,
    float vx, float vy,
    float imass,
    float theta, float omega,
    enum shapeTypes shapeType,
    float radius,
    float width_2, float height_2
);
void destroy_solid_object(solid_object* object);
solid_object* random_object(int width, int height, enum shapeTypes shapeType);
void generic_colision_reaction(solid_object* object);
void print_solid_object(solid_object* object);
//
// Physics stuff
void move_object(solid_object* object);
bool detectColision(solidObject* a, solidObject* b);
bool detectColision_CircleCircle(solidObject* a, solidObject* b);
bool detectColision_RectangleRectangle(solidObject* a, solidObject* b);
bool detectColision_RectangleCircle(solidObject* r, solidObject* c);
void update_physics(solid_object* objects[], int obj_quant, int width, int height);
void updateRotationVector(solidObject* obj);

#endif