#include "physics.h"

#include "render.h"

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

bool detectColision(solidObject* a, solidObject* b, vector2d* colisionPoint){
    switch (a->shapeType){
    case Circle:
        switch (b->shapeType){
        case Circle:
            return detectColision_CircleCircle(a, b, colisionPoint);
        case Rectangle:
            return detectColision_RectangleCircle(b, a, colisionPoint);
        }

        break;
    case Rectangle:
        switch (b->shapeType){
        case Circle:
            return detectColision_RectangleCircle(a, b, colisionPoint);
        case Rectangle:
            return detectColision_RectangleRectangle(a, b, colisionPoint);
        }
        break;
    }

    return false;
}

//TODO point of colision
bool detectColision_CircleCircle(solidObject* a, solidObject* b, vector2d* colisionPoint){
    if(vector2d_distance(&a->position, &b->position) <= a->circle.radius+b->circle.radius){
        return true;
    }
	return false;
}

//TODO everything
bool detectColision_RectangleRectangle(solidObject* a, solidObject* b, vector2d* colisionPoint){
    vector2d bPost = b->position;
    vector2d bRot = b->rotation;
    vector2d_rotateCenterInverse(&bPost, &a->rotation, &a->position);
    vector2d_rotateInverse(&bRot, &a->rotation);
    
    float bigScale = (fabsf(bRot.x) + fabsf(bRot.y));
    float bigWidth_2 = b->rectangle.width_2*bigScale;
    float bigHeight_2 = b->rectangle.height_2*bigScale;

    #ifdef DEBUG_PHYSICS
    al_draw_rectangle(
        a->position.x-a->rectangle.width_2,
        a->position.y-a->rectangle.height_2,
        a->position.x+a->rectangle.width_2,
        a->position.y+a->rectangle.height_2,
        al_map_rgb(255, 255, 255),
        1
    );
    al_draw_rectangle(
        bPost.x - bigWidth_2,
        bPost.y - bigHeight_2,
        bPost.x + bigWidth_2,
        bPost.y + bigHeight_2,
        al_map_rgb(255, 255, 255),
        1
    );
    solidObject bProjection = *b;
    bProjection.position = bPost;
    bProjection.rotation = bRot;
    visibleObject obj = {
        .object = &bProjection,
        .fillColor = al_map_rgb(255, 255, 255)
    };
    draw_rectangle(&obj);
    #endif

    if(!(   //First collision detection Big B object
        a->position.x-a->rectangle.width_2 <= bPost.x + bigWidth_2 &&
        a->position.x+a->rectangle.width_2 >= bPost.x - bigWidth_2 &&
        a->position.y-a->rectangle.height_2 <= bPost.y + bigHeight_2 &&
        a->position.y+a->rectangle.height_2 >= bPost.y - bigHeight_2
    )){
        return false;
    }

    return true;
}

bool detectColision_RectangleCircle(solidObject* r, solidObject* c, vector2d* colisionPoint){
    vector2d cirPos = c->position; //Position relative to rectangle rotation axie
    vector2d_rotateCenterInverse(&cirPos, &r->rotation, &r->position);

    #ifdef DEBUG_PHYSICS
    al_draw_rectangle(
        r->position.x-r->rectangle.width_2, 
        r->position.y-r->rectangle.height_2,
        r->position.x+r->rectangle.width_2,
        r->position.y+r->rectangle.height_2,
        al_map_rgb(255, 255, 255),
        1
    );
    al_draw_circle(
        cirPos.x, cirPos.y,
        c->circle.radius,
        al_map_rgb(255, 255, 255),
        1
    );
    #endif

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

    #ifdef DEBUG_PHYSICS
    al_draw_line(
        cirPos.x, cirPos.y,
        test.x, test.y,
        al_map_rgb(255, 255, 255),
        1
    );
    al_draw_filled_circle(
        cirPos.x, cirPos.y,
        3,
        al_map_rgb(255, 0, 0)
    );
    al_draw_filled_circle(
        test.x, test.y,
        3,
        al_map_rgb(255, 0, 0)
    );
    #endif

    const float distance = vector2d_distance(&test, &cirPos);
    if(distance <= c->circle.radius){
        *colisionPoint = test;
        return true;
    }

    return false;
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