#include "physics.h"

#define MAX_RANDOM_SIZE 6

solid_object* create_solid_object(
    float x, float y,
    float vx, float vy,
    float axie_v,
    void (*colision_reaction)(void*),
    float mass,
    enum shape_types shape_type,
    union shapes shape
){
    struct solid_object* object = malloc(sizeof(struct solid_object));
    object->position[0] = x;
    object->position[1] = y;
    object->velocity[0] = vx;
    object->velocity[1] = vy;
    object->axie_velocity = axie_v;
    object->colision_reaction = colision_reaction;
    object->mass = mass;
    object->shape_type = shape_type;
    
    switch (object->shape_type){
        case Rectangle:
            object->rectangle.width = shape.rectangle.width;
            object->rectangle.height = shape.rectangle.height;
            break;
        case Circle:
            object->circle.radius = shape.circle.radius;
            break;
    }

    return object;
}

solid_object* random_object(int width, int height, enum shape_types shape_type){
    struct solid_object* object = malloc(sizeof(struct solid_object));

    object->shape_type = shape_type;
    switch (object->shape_type){
        case Rectangle:
            object->rectangle.width = (float)(rand()%MAX_RANDOM_SIZE+1);
            object->rectangle.height = (float)(rand()%MAX_RANDOM_SIZE+1);
            object->position[0] = (float)(rand()%(width-(int)object->rectangle.width+1));
            object->position[1] = (float)(rand()%(height-(int)object->rectangle.height+1));
            break;
        case Circle:
            object->circle.radius = (float)(rand()%(MAX_RANDOM_SIZE/2)+1);
            object->position[0] = (float)(rand()%(width-(int)object->circle.radius*2+1));
            object->position[1] = (float)(rand()%(height-(int)object->circle.radius*2+1));
            break;
    }
    object->velocity[0] = (float)(rand()%16-8);
    object->velocity[1] = (float)(rand()%16-8);
    object->axie_velocity = 0;
    object->colision_reaction = (void (*)(void *))generic_colision_reaction;
    object->mass = 0;

    return object;
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
        object->position[0],object->position[1],
        object->velocity[0], object->velocity[1],
        object->mass,
        object->shape_type     
    );
}

void move_object(solid_object* object){
    object->position[0] += object->velocity[0];
    object->position[1] += object->velocity[1];
}

bool border_colision_detection(solid_object* object, int width, int height){
    switch (object->shape_type){
    case Rectangle:
        if(
            object->position[0] <= 0 ||
            object->position[0] + object->rectangle.width >= width ||
            object->position[1] <= 0 ||
            object->position[1] + object->rectangle.height >= height
        ){return true;}
        break;
    case Circle:
        if(
            object->position[0] <= 0 ||
            object->position[1] <= 0 ||
            object->position[0] + object->circle.radius*2 >= width ||
            object->position[1] + object->circle.radius*2 >= height
        ){return true;}
        break;;
    }
    
    return false;
}

bool border_colision_handling(solid_object* object, int width, int height){
    if(border_colision_detection(object, width, height)){
        switch (object->shape_type){
        case Rectangle:
            if(object->position[0] < 0){
                object->velocity[0] = -object->velocity[0];
                object->position[0] = 0;
            } else if (object->position[0] + object->rectangle.width > width){
                object->velocity[0] = -object->velocity[0];
                object->position[0] = (float)width - object->rectangle.width;
            }
            
            if (object->position[1] < 0){
               object->velocity[1] = -object->velocity[1];
               object->position[1] = 0;
            } else if (object->position[1] + object->rectangle.height > height){
                object->velocity[1] = -object->velocity[1];
                object->position[1] = (float)height - object->rectangle.height;
            }
            break;
        case Circle:
            if(object->position[0] < 0){
                object->velocity[0] = -object->velocity[0];
                object->position[0] = 0;
            } else if((object->position[0] + object->circle.radius*2) > width){
                object->velocity[0] = -object->velocity[0];
                object->position[0] = (float)width - (object->circle.radius*2);
            }

            if(object->position[1] < 0){
                object->velocity[1] = -object->velocity[1];
                object->position[1] = 0;
            } else if((object->position[1] + object->circle.radius*2) > height){
                object->velocity[1] = -object->velocity[1];
                object->position[1] = (float)height - (object->circle.radius*2);
            }
            break;
        }

        return true;
    }
    return false;
}

void update_physics(solid_object* objects[], int obj_quant, int width, int height){
    for(int i = 0; i < obj_quant; i++){
        move_object(objects[i]);
        border_colision_handling(objects[i], width, height);
    }
}
