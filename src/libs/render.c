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

void draw_ui_element(interactable_ui* obj){
    switch (obj->type){
    case Button:
        al_draw_filled_rectangle(
            (float)obj->button.position.x,
            (float)obj->button.position.y,
            (float)obj->button.position.x+obj->button.width,
            (float)obj->button.position.y+obj->button.height,
            obj->button.color
        );
        return;
    case UiQuant:
        break;
    }
}

void draw_ui(interactable_ui* obj[], unsigned int quant){
    for(unsigned int i = 0; i < quant; i++){
        draw_ui_element(obj[i]);
    }
}

bool isHoverButton(struct interactable_ui* element, ALLEGRO_MOUSE_EVENT* mouse){
    if(element->button.position.x <= mouse->x &&
        element->button.position.x + element->button.width >= mouse->x &&
        element->button.position.y <= mouse->y &&
        element->button.position.y + element->button.height >= mouse->y
    ){
        return true;
    }
    return false;
}