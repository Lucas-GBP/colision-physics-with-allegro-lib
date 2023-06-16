#include "physics.h"

#define MAX_RANDOM_SIZE 6

solid_object* create_solid_object(
    int32_t x, int32_t y,
    int16_t vx, int16_t vy,
    int16_t axie_v,
    void (*colision_reaction)(void*),
    uint16_t mass,
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

solid_object* copy_solid_object(solid_object* object){
    struct solid_object* copy = malloc(sizeof(struct solid_object));
    copy->position[0] = object->position[0];
    copy->position[1] = object->position[1];
    copy->velocity[0] = object->velocity[0];
    copy->velocity[1] = object->velocity[1];
    copy->mass = object->mass;
    copy->shape_type = object->shape_type;
    
    switch (copy->shape_type){
        case Rectangle:
            copy->rectangle.width = object->rectangle.width;
            copy->rectangle.height = object->rectangle.height;
            break;
        case Circle:
            copy->circle.radius = object->circle.radius;
            break;
    }

    return copy;

}

solid_object* random_object(int32_t width, int32_t height, enum shape_types shape_type){
    struct solid_object* object = malloc(sizeof(struct solid_object));

    object->shape_type = shape_type;
    switch (object->shape_type){
        case Rectangle:
            object->rectangle.width = (uint16_t)(rand()%MAX_RANDOM_SIZE+1);
            object->rectangle.height = (uint16_t)(rand()%MAX_RANDOM_SIZE+1);
            object->position[0] = rand()%(width-object->rectangle.width+1);
            object->position[1] = rand()%(height-object->rectangle.height+1);
            break;
        case Circle:
            object->circle.radius = (uint16_t)(rand()%(MAX_RANDOM_SIZE/2)+1);
            object->position[0] = rand()%(width-object->circle.radius*2+1);
            object->position[1] = rand()%(height-object->circle.radius*2+1);
            break;
    }
    object->velocity[0] = (int16_t)(rand()%16-8);
    object->velocity[1] = (int16_t)(rand()%16-8);
    object->axie_velocity = 0;
    object->colision_reaction = generic_colision_reaction;
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
    printf("x:%i\ty:%i\nv_x:%i\tv_y:%i\nmass:%i\nshape:%i\nheight:%i\twidth:%i\n",
        object->position[0],object->position[1],
        object->velocity[0], object->velocity[1],
        object->mass,
        object->shape_type,
        object->rectangle.height, object->rectangle.width       
    );
}

void move_object(solid_object* object){
    object->position[0] += object->velocity[0];
    object->position[1] += object->velocity[1];
}

bool border_colision_detection(solid_object* object, int32_t width, int32_t height){
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

bool border_colision_handling(solid_object* object, int32_t width, int32_t height){
    if(border_colision_detection(object, width, height)){
        switch (object->shape_type){
        case Rectangle:
            if(object->position[0] < 0){
                object->velocity[0] = -object->velocity[0];
                object->position[0] = 0;
            } else if (object->position[0] + object->rectangle.width > width){
                object->velocity[0] = -object->velocity[0];
                object->position[0] = width - object->rectangle.width;
            }
            
            if (object->position[1] < 0){
               object->velocity[1] = -object->velocity[1];
               object->position[1] = 0;
            } else if (object->position[1] + object->rectangle.height > height){
                object->velocity[1] = -object->velocity[1];
                object->position[1] = height - object->rectangle.height;
            }
            break;
        case Circle:
            if(object->position[0] < 0){
                object->velocity[0] = -object->velocity[0];
                object->position[0] = 0;
            } else if((int32_t)(object->position[0] + object->circle.radius*2) > width){
                object->velocity[0] = -object->velocity[0];
                object->position[0] = width - (int32_t)(object->circle.radius*2);
            }

            if(object->position[1] < 0){
                object->velocity[1] = -object->velocity[1];
                object->position[1] = 0;
            } else if((int32_t)(object->position[1] + object->circle.radius*2) > height){
                object->velocity[1] = -object->velocity[1];
                object->position[1] = height - (int32_t)(object->circle.radius*2);
            }
            break;
        }

        return true;
    }
    return false;
}

void update_physics(solid_object* objects[], int obj_quant, uint32_t width, uint32_t height){
    for(int i = 0; i < obj_quant; i++){
        move_object(objects[i]);
        border_colision_handling(objects[i], width, height);
    }
}
