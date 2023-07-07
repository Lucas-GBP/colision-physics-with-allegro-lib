#include "render.h"

visibleObject* create_visibleObject(solidObject* obj, ALLEGRO_COLOR fill){
    visibleObject* vis = malloc(sizeof(visibleObject));

    vis->fillColor = fill;
    vis->object = obj;

    return vis;
}

void draw_object(visibleObject* object){
    switch (object->object->shapeType){
    case Rectangle:
        /*al_draw_rectangle(
            object->object->position.x-object->object->rectangle.width_2, 
            object->object->position.y-object->object->rectangle.height_2,
            object->object->position.x+object->object->rectangle.width_2,
            object->object->position.y+object->object->rectangle.height_2,
            al_map_rgb(255, 255, 255),
            1
        );*/
        draw_rectangle(object);

        break;
    case Circle:
        al_draw_filled_circle(
            object->object->position.x,
            object->object->position.y,
            object->object->circle.radius,
            object->fillColor
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

void draw_rectangle(visibleObject* object){
    vector2d leftTop = {
        .x = object->object->position.x - object->object->rectangle.width_2,
        .y = object->object->position.y - object->object->rectangle.height_2
    };
    vector2d leftBottom = {
        .x = object->object->position.x - object->object->rectangle.width_2,
        .y = object->object->position.y + object->object->rectangle.height_2
    };
    vector2d rightTop = {
        .x = object->object->position.x + object->object->rectangle.width_2,
        .y = object->object->position.y - object->object->rectangle.height_2
    };
    vector2d rightBottom = {
        .x = object->object->position.x + object->object->rectangle.width_2,
        .y = object->object->position.y + object->object->rectangle.height_2
    };

    vector2d_rotateCenter(&leftTop, &object->object->rotation, &object->object->position);
    vector2d_rotateCenter(&leftBottom, &object->object->rotation, &object->object->position);
    vector2d_rotateCenter(&rightTop, &object->object->rotation, &object->object->position);
    vector2d_rotateCenter(&rightBottom, &object->object->rotation, &object->object->position);


    al_draw_filled_triangle(
        leftTop.x, leftTop.y,
        leftBottom.x, leftBottom.y,
        rightTop.x, rightTop.y,
        object->fillColor
    );
    al_draw_filled_triangle(
        rightBottom.x, rightBottom.y,
        leftBottom.x, leftBottom.y,
        rightTop.x, rightTop.y,
        object->fillColor
    );
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