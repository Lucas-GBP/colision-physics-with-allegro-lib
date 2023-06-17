#ifndef RENDER_H
#define RENDER_H

#include <allegro5\allegro5.h>
#include <allegro5\events.h>
#include <allegro5\allegro_primitives.h>

#include "physics.h"
#include "vectors.h"

void draw_object(solid_object* object, ALLEGRO_COLOR color);
void draw_button(vector_2d_int* position, vector_2d_int* mouse, int width, int height);

#endif