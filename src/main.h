#ifndef MAIN_H
#define MAIN_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "libs/physics.h"
#include "libs/render.h"

#define DEBUG

#define WIDTH 1000
#define HEIGHT 700
#define SOLID_OBJ_QUANT 1000
#define UI_OBJ_QUANT 2
#define FPS_LIST_QUANT 100

void inicialization();
void changeStateButton(button* b);

#endif