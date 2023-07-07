#include "physics.h"

#include <allegro5\allegro_primitives.h>

#define MAX_RANDOM_SIZE 6

solidObject* create_solidObject(
    float x, float y,
    float vx, float vy,
    float imass,
    float theta, float omega,
    enum shapeTypes shapeType,
    float radius,
    float width_2, float height_2
){
    solidObject* obj = malloc(sizeof(solidObject));

    obj->position.x = x;
    obj->position.y = y;
    obj->velocity.x = vx;
    obj->velocity.y = vy;
    obj->rotation.x = cosf(theta);
    obj->rotation.y = sinf(theta);
    obj->inverseMass = imass;
    obj->theta = theta;
    obj->omega = omega;
    obj->shapeType = shapeType;

    switch (obj->shapeType){
    case Circle:
        obj->circle.radius = radius;
        break;
    case Rectangle:
        obj->rectangle.width_2 = width_2;
        obj->rectangle.height_2 = height_2;
    }

    return obj;
}

void generic_colision_reaction(solid_object* object){
    printf("Object %p colided.\n", object);
    return;
}

void destroy_solid_object(solid_object* object){
    return free(object);
}

void print_solid_object(solid_object* object){
    printf("x:%f\ty:%f\nv_x:%f\tv_y:%f\nmass:%f\nshape:%i\n",
        object->position.x,object->position.y,
        object->velocity.x, object->velocity.y,
        object->inverseMass,
        object->shapeType
    );
}

void move_object(solid_object* object){
    object->position.x += object->velocity.x;
    object->position.y += object->velocity.y;
}

bool detectColision(solidObject* a, solidObject* b){
    switch (a->shapeType){
    case Circle:
        switch (b->shapeType){
        case Circle:
            return detectColision_CircleCircle(a, b);
        case Rectangle:
            return detectColision_RectangleCircle(b, a);
        }

        break;
    case Rectangle:
        switch (b->shapeType){
        case Circle:
            return detectColision_RectangleCircle(a, b);
        case Rectangle:
            return detectColision_RectangleRectangle(a, b);
        }
        break;
    }

    return false;
}

bool detectColision_CircleCircle(solidObject* a, solidObject* b){
	return (vector2d_distance(&a->position, &b->position) <= a->circle.radius+b->circle.radius);
}

//TODO
bool detectColision_RectangleRectangle(solidObject* a, solidObject* b){
    return false;
}

//TODO
bool detectColision_RectangleCircle(solidObject* r, solidObject* c){
    vector2d cirPos = c->position; //Position relative to rectangle rotation axie

    vector2d_rotateCenterInverse(&cirPos, &r->rotation, &r->position);

    al_draw_circle(
        cirPos.x, cirPos.y,
        c->circle.radius,
        al_map_rgb(255, 255, 255),
        1
    );

    vector2d test = cirPos;
    const float leftEdge = r->position.x - r->rectangle.width_2;
    const float rightEdge = r->position.x + r->rectangle.width_2;
    const float topEdge = r->position.y - r->rectangle.height_2;
    const float bottomEdge = r->position.y + r->rectangle.height_2;

    if(cirPos.x < leftEdge){
        test.x = leftEdge;
    } else if(cirPos.x > rightEdge){
        test.x = rightEdge;
    }
    if(cirPos.y < topEdge){
        test.y = topEdge;
    } else if(cirPos.y > bottomEdge){
        test.y = bottomEdge;
    }

    return (vector2d_distance(&test, &cirPos) <= r->circle.radius);
}

void update_physics(solid_object* objects[], int obj_quant, int width, int height){
    for(int i = 0; i < obj_quant; i++){
        move_object(objects[i]);
    }
}

void updateRotationVector(solidObject* obj){
    obj->rotation.x = cosf(obj->theta);
    obj->rotation.y = sinf(obj->theta);
}