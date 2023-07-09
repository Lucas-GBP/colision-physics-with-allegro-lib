#include "main.h"

int main(){
    inicialization();

    int width = WIDTH;
    int height = HEIGHT;
    // Some constants
    const ALLEGRO_COLOR colorWhite = al_map_rgb(255, 255, 255);
    const ALLEGRO_COLOR colorblack = al_map_rgb(0, 0, 0);
    const ALLEGRO_COLOR colorCyan = al_map_rgb(0, 255, 255);
    const ALLEGRO_COLOR colorMagenta = al_map_rgb(255, 0, 255);
    const ALLEGRO_COLOR colorYellow = al_map_rgb(255, 255, 0);
    const ALLEGRO_COLOR colorRed = al_map_rgb(255, 0, 0);
    const ALLEGRO_COLOR colorGreen = al_map_rgb(0, 255, 0);
    const ALLEGRO_COLOR colorBlue = al_map_rgb(0, 0, 255);

    // Allegro Variables
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_DISPLAY* disp = al_create_display(width, height);
    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_EVENT event;

    //Allegro - registering event sources
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    
    //User input variables
    bool pressed_keys[ALLEGRO_KEY_MAX] = {false};
    bool pressed_mouse[3];
    ALLEGRO_MOUSE_EVENT mouse;
    mouse.x = 0;
    mouse.y = 0;

    // Alocating physical objects
    solidObject* objects[SOLID_OBJ_QUANT] = {
        create_solidObject(
            (float)(width/2), (float)(height/2),
            0, 0,
            1,
            0, 0,
            Rectangle,
            30,
            100, 100     
        ),
        create_solidObject(
            (float)(width/2-200), (float)(height/2),
            0, 0,
            1,
            0, 0,
            Circle,
            50,
            10, 10     
        )
    };
    visibleObject* visibleObjects[SOLID_OBJ_QUANT];
    for(int i = 0; i < SOLID_OBJ_QUANT; i++){
        visibleObjects[i] = create_visibleObject(objects[i], colorCyan);
    }
    vector2d colisionPoint = {
        .x = (float)width/2,
        .y = (float)height/2
    };

    // Alocating Ui Elements
    interactable_ui* uiElements[UI_OBJ_QUANT] = {
    };

    // Loop variables
    al_start_timer(timer);
    double old_time = al_get_time();
    int fps_counter = 0;
    double fps = 0;
    uint8_t fps_list[FPS_LIST_QUANT] = {0};

    bool redraw = true;
    bool uiUpdate = false;
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
            uiUpdate = true;
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            mouse = event.mouse;
            if(event.mouse.button < 3)
                pressed_mouse[event.mouse.button] = true;
            uiUpdate = true;
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            mouse = event.mouse;
            if(event.mouse.button < 3)
                pressed_mouse[event.mouse.button] = false;
            uiUpdate = true;
            break;
        case ALLEGRO_EVENT_TIMER:
            redraw = true;
            break;
        }

        // Update ui elements
        if(uiUpdate){
            for(int i = 0; i < UI_OBJ_QUANT; i++){
                if(uiElements[i]->isHover(uiElements[i], &mouse)){
                    switch (uiElements[i]->type){
                    case Button:
                        if(pressed_mouse[1]){
                            uiElements[i]->button.funtionClick(&uiElements[i]->button);
                            pressed_mouse[1] = false;
                        }
                        break;
                    case UiQuant:
                        break;
                    }
                }
            }

            uiUpdate = false;
        }

        // Executed each time event when as the last event
        if(redraw && al_is_event_queue_empty(queue)){
            // Clean buffer
            al_clear_to_color(colorblack);

            // Update all physical bodies
            if(pressed_keys[ALLEGRO_KEY_UP]){
                objects[1]->position.y -= 5;
            }
            if(pressed_keys[ALLEGRO_KEY_DOWN]){
                objects[1]->position.y += 5;
            }
            if(pressed_keys[ALLEGRO_KEY_LEFT]){
                objects[1]->position.x -= 5;
            }
            if(pressed_keys[ALLEGRO_KEY_RIGHT]){
                objects[1]->position.x += 5;
            }
            if(pressed_keys[ALLEGRO_KEY_G]){
                objects[1]->theta += 0.02f;
                updateRotationVector(objects[1]);
            }
            if(pressed_keys[ALLEGRO_KEY_R]){
                objects[0]->theta += 0.02f;
                updateRotationVector(objects[0]);
            }
            if(pressed_keys[ALLEGRO_KEY_ESCAPE]){
                loop = false;
            }

            update_physics(objects, SOLID_OBJ_QUANT, width, height);

            if(detectColision(objects[0], objects[1], &colisionPoint)){
                visibleObjects[1]->fillColor = colorMagenta;
            } else {
                visibleObjects[1]->fillColor = colorCyan;
            }


            //
            //Draw all elements
            //
            // Physics elements
            for(int i = 0; i < SOLID_OBJ_QUANT; i++){
                draw_object(visibleObjects[i]);
            }
            #ifdef DEBUG_PHYSICS
            al_draw_filled_circle(colisionPoint.x, colisionPoint.y, 3, colorRed);
            #endif
            // UI Elements
            draw_ui(uiElements, UI_OBJ_QUANT);

            #ifdef DEBUG
            {
                //FPS
                al_draw_textf(font, colorWhite, 5, 5, ALLEGRO_ALIGN_LEFT, "%lf", fps);
                //FPS grath
                const int gx = 5;
                const int gy = 35;
                const int gw = 100;
                const int gh = 65;
                al_draw_line((float)gx, (float)gy, (float)gx, (float)(gy+gh), colorWhite, 1);
                al_draw_line((float)gx, (float)(gy+gh), (float)(gx+gw), (float)(gy+gh), colorWhite, 1);
                for(int i = 0; i < FPS_LIST_QUANT-1; i++){
                    al_draw_line(
                        (float)(gx+i),
                        (float)(gy+gh-fps_list[i]),
                        (float)(gx+1+i),
                        (float)(gy+gh-fps_list[i+1]),
                        colorMagenta,
                        1
                    );
                }
                // Mouse position
                al_draw_textf(
                    font, 
                    colorWhite, 
                    (float)(mouse.x+20), 
                    (float)(mouse.y+20), 
                    ALLEGRO_ALIGN_LEFT,
                    "%i  %i",
                    mouse.x, mouse.y
                );
                // mouse buttons
                for(int i = 0; i < 3; i++){
                    if(pressed_mouse[i]){
                        int mx = mouse.x+20;
                        int my = mouse.y+5;
                        al_draw_filled_rectangle(
                            (float)(mx+10*i),
                            (float)(my),
                            (float)(mx+(i+1)*10),
                            (float)(my+10),
                            colorWhite
                        );
                    }
                }
            }
            #endif
            //Draw buffer on the screen
            al_flip_display();

            //FPS calculation
            fps_counter++;
            if(fps_counter >= FPS_SAMPLE){
                double new_time = al_get_time();
                fps = fps_counter/(new_time - old_time);
                old_time = new_time;
                fps_counter = 0;

                for(int i = 0; i < FPS_LIST_QUANT-1; i++){
                    fps_list[i] = fps_list[i+1];
                }
                fps_list[FPS_LIST_QUANT-1] = (uint8_t)fps;
            }
            //restar counting
            redraw = false;
        }
    }

    for(int i = 0; i < SOLID_OBJ_QUANT; i++){
        free(objects[i]);
        free(visibleObjects[i]);
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
    al_install_mouse();
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();

    return;
}

void changeStateButton(button* b){
    if(b->state == Standbye){
        b->state = Hover;
        b->color = al_map_rgb(0, 255, 255);

        return;
    }
    if(b->state == Hover){
        b->state = Standbye;
        b->color = al_map_rgb(255, 0, 255);

        return;
    }
};