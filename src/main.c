#include "main.h"

#define QUANT 1000

vector_2d_int mouse;

int main(){
    inicialization();

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_DISPLAY* disp = al_create_display(1000, 700);
    ALLEGRO_FONT* font = al_create_builtin_font();

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool redraw = true;
    ALLEGRO_EVENT event;

    ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR blue = al_map_rgb(0, 0, 255);
    ALLEGRO_COLOR green = al_map_rgb(255, 0, 0);

    interactable_ui ui_elements[] = {
        {
            .type = Button,
            .button = {
                .state = Standbye,
                .arguments = 0,
                .function = 0,
                .position = {
                    .x = 0,
                    .y = 60
                },
                .width = 50,
                .height = 50,
                .color = {
                    white,
                    blue,
                    green
                }
                
            }
        },
        {
            .type = Button,
            .button = {
                .state = Standbye,
                .arguments = 0,
                .function = 0,
                .position = {
                    .x = 60,
                    .y = 60
                },
                .width = 50,
                .height = 50,
                .color = {
                    white,
                    blue,
                    green
                }
                
            }
        }
    };

    solid_object* objects[QUANT];
    for(uint64_t i = 0; i < QUANT; i++){
        objects[i] = random_object(WIDTH, HEIGHT, Circle);
    }

    int fps_counter = 0;
    double fps = 0;

    al_start_timer(timer);
    double old_time = al_get_time();
    while(true){
        al_wait_for_event(queue, &event);

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            break;
        }

        switch (event.type){
            case ALLEGRO_EVENT_TIMER:
                redraw = true;
                break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                mouse.x = event.mouse.x;
                mouse.y = event.mouse.y;
                break;
        }

        if(redraw && al_is_event_queue_empty(queue)){
            al_clear_to_color(al_map_rgb(0, 0, 0));

            update_physics(objects, QUANT, WIDTH, HEIGHT);
            for(int i = 0; i < QUANT; i++){
                draw_object(objects[i], al_map_rgb(0, 255, 255));
            }


            vector_2d_int p = {0,0};
            al_draw_textf(font, al_map_rgb(255, 255, 255), 5, 5, ALLEGRO_ALIGN_LEFT, "%lf", fps);

            //FPS Count
            fps_counter++;
            if(fps_counter >= 5){
                double new_time = al_get_time();
                fps = fps_counter/((new_time - old_time));
                old_time = new_time;
                fps_counter = 0;
            }

            draw_ui(ui_elements, 2);

            al_flip_display();
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
    al_install_mouse();
    al_install_keyboard();
    al_init_primitives_addon();
}