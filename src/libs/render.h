#ifndef RENDER_H
#define RENDER_H

#include <allegro5\allegro_primitives.h>
#include "physics.h"

#define FPS_SAMPLE 3

void draw_object(solid_object* object, ALLEGRO_COLOR color);

#endif