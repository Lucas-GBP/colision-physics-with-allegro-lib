#include "main.h"

#define SOLID_OBJ_QUANT 1000

int main(){
    inicialization();

    // Allegro Variables
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_DISPLAY* disp = al_create_display(1000, 700);
    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_EVENT event;

    //Allegro - registering event sources
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    
    //User input variables
    bool pressed_keys[ALLEGRO_KEY_MAX];
    bool pressed_mouse[3];
    ALLEGRO_MOUSE_EVENT mouse;
    mouse.x = 0;
    mouse.y = 0;

    // Alocanting physical objects
    solid_object* objects[SOLID_OBJ_QUANT];
    for(uint64_t i = 0; i < SOLID_OBJ_QUANT; i++){
        objects[i] = random_object(WIDTH, HEIGHT, Circle);
    }

    // Loop variables
    al_start_timer(timer);
    double old_time = al_get_time();
    int fps_counter = 0;
    double fps = 0;
    bool redraw = true;
    bool loop = true;

    while(loop){
        // Waiting for any event to happen (timer, keyboard, mouse, ext...)
        al_wait_for_event(queue, &event);

        // Processing diferent event types
        switch (event.type){
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            loop = false;
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            pressed_keys[event.keyboard.keycode] = true;
            break;
        case ALLEGRO_EVENT_KEY_UP:
            pressed_keys[event.keyboard.keycode] = false;
            break;
        case ALLEGRO_EVENT_MOUSE_AXES:
            mouse = event.mouse;
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            mouse = event.mouse;
            if(event.mouse.button < 3)
                pressed_mouse[event.mouse.button] = true;
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            mouse = event.mouse;
            if(event.mouse.button < 3)
                pressed_mouse[event.mouse.button] = false;
            break;
        case ALLEGRO_EVENT_TIMER:
            redraw = true;
            break;
        }

        // Executed each time event when as the last event
        if(redraw && al_is_event_queue_empty(queue)){
            // Clean buffer
            al_clear_to_color(al_map_rgb(0, 0, 0));

            // Update all physical bodies
            update_physics(objects, SOLID_OBJ_QUANT, WIDTH, HEIGHT);

            //
            //Draw all elements
            //

            // Physics elements
            for(int i = 0; i < SOLID_OBJ_QUANT; i++){
                draw_object(objects[i], al_map_rgb(0, 255, 255));
            }
            //FPS
            al_draw_textf(font, al_map_rgb(255, 255, 255), 5, 5, ALLEGRO_ALIGN_LEFT, "%lf", fps);
            // Mouse position
            al_draw_textf(
                font, 
                al_map_rgb(255, 255, 255), 
                (float)(mouse.x+20), 
                (float)(mouse.y+20), 
                ALLEGRO_ALIGN_LEFT,
                "%i  %i",
                mouse.x, mouse.y
            );

            //Draw buffer on the screen
            al_flip_display();

            //FPS calculation
            fps_counter++;
            if(fps_counter >= FPS_SAMPLE){
                double new_time = al_get_time();
                fps = fps_counter/(new_time - old_time);
                old_time = new_time;
                fps_counter = 0;
            }

            //restar counting
            redraw = false;
        }
    }

    for(int i = 0; i < SOLID_OBJ_QUANT; i++){
        free(objects[i]);
    }

    //Destroing allegro events
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
    al_install_mouse();
    al_init_primitives_addon();

    return;
}