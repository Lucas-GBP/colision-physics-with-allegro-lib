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
    void (*functionHover)(struct button*);
    void (*funtionClick)(struct button*);
    void* arguments;
    char* label;
    enum button_state state;
    ALLEGRO_COLOR color; //A diferent color for each "button_State"

};typedef struct button button;

enum ui_types {Button, DragNDrop, UiQuant};

struct interactable_ui{
    enum ui_types type;
    bool (*isHover)(struct interactable_ui*, ALLEGRO_MOUSE_EVENT*);
    union{
        button button;
    };
    
};typedef struct interactable_ui interactable_ui;


#define FPS_SAMPLE 3

void draw_object(solid_object* object, ALLEGRO_COLOR color);
void draw_ui_element(interactable_ui* obj);
void draw_ui(interactable_ui* obj[], unsigned int quant);
bool isHoverButton(struct interactable_ui* button, ALLEGRO_MOUSE_EVENT* mouse);

#endif