#include "render.h"

void draw_object(solid_object* object, ALLEGRO_COLOR color){
    switch (object->shape_type){
    case Rectangle:
        al_draw_filled_rectangle(
            (float)object->position[0], (float)object->position[1],
            (float)(object->position[0]+object->rectangle.width),
            (float)(object->position[1]+object->rectangle.height),
            color
        );
        break;
    case Circle:
        al_draw_filled_circle(
            (float)(object->position[0]+object->circle.radius),
            (float)(object->position[1]+object->circle.radius),
            (float)object->circle.radius,
            color
        );
        break;
    }
}

void draw_button(vector_2d_int* position, vector_2d_int* mouse, int width, int height){
    ALLEGRO_COLOR color;
    if(mouse->x >= position->x && mouse->y >= position->y &&
        mouse->x <= position->x+width && mouse->y <= position->y+height
    ){
        color = al_map_rgb(255, 255, 255);
    } else {
        color = al_map_rgb(0, 255, 0);
    }

    al_draw_filled_rectangle(
        position->x,
        position->y,
        width,
        height,
        color
    );
}