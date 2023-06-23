#ifndef RENDER_H
#define RENDER_H

#include <allegro5\allegro5.h>
#include <allegro5\events.h>
#include <allegro5\allegro_primitives.h>

#include "physics.h"
#include "vectors.h"

enum button_state {Standbye, Hover, Hold};
struct button{
    struct {float x; float y;} position;
    float width;
    float height;
    void(*function)(void*);
    void* arguments;
    char* label;
    enum button_state state;
    ALLEGRO_COLOR color[3]; //A diferent color for each "button_State"

};typedef struct button button;

enum ui_types {Button, DragNDrop};

struct interactable_ui{
    enum ui_types type;
    union{
        button button;
    };
    
};typedef struct interactable_ui interactable_ui;


void draw_object(solid_object* object, ALLEGRO_COLOR color);
void draw_ui_element(interactable_ui* obj);
void draw_ui(interactable_ui obj[], unsigned int quant);


#endif