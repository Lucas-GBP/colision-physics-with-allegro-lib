#include "main.h"

#define QUANT 5000

int main(){
    inicialization();

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_DISPLAY* disp = al_create_display(1000, 700);
    ALLEGRO_FONT* font = al_create_builtin_font();

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool redraw = true;
    ALLEGRO_EVENT event;

    solid_object* objects[QUANT];
    for(uint64_t i = 0; i < QUANT; i++){
        objects[i] = random_object(WIDTH, HEIGHT, Circle);
    }

    solid_object obj = {
        .position = {WIDTH/2-50,HEIGHT/2-50},
        .velocity = {0,0},
        .axie_velocity = 0,
        .colision_reaction = NULL,
        .mass = 1,
        .shape_type = Circle,
        .circle = {
            .radius = 50
        }
    };

    al_start_timer(timer);
    double old_time = al_get_time();
    int fps_counter = 0;
    double fps = 0;
    while(true){
        al_wait_for_event(queue, &event);

        if(event.type == ALLEGRO_EVENT_TIMER){
            redraw = true;
        } else if((event.type == ALLEGRO_EVENT_KEY_DOWN) || (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)){
            break;
        }

        if(redraw && al_is_event_queue_empty(queue)){
            al_clear_to_color(al_map_rgb(0, 0, 0));

            draw_object(&obj, al_map_rgb(255, 255, 255));
            update_physics(objects, QUANT, WIDTH, HEIGHT);
            for(int i = 0; i < QUANT; i++){
                draw_object(objects[i], al_map_rgb(0, 255, 255));
            }

            al_draw_textf(font, al_map_rgb(255, 255, 255), 5, 5, ALLEGRO_ALIGN_LEFT, "%lf", fps);
            al_flip_display();

            //FPS Count
            fps_counter++;
            if(fps_counter >= 5){
                double new_time = al_get_time();
                fps = fps_counter/((new_time - old_time));
                old_time = new_time;
                fps_counter = 0;
            }

            redraw = false;
        }
    }

    for(int i = 0; i < QUANT; i++){
        free(objects[i]);
    }

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}

void inicialization(){
    srand((unsigned int)time(NULL));
    al_init();
    al_install_keyboard();
    al_init_primitives_addon();
}