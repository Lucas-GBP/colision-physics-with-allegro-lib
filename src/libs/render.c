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