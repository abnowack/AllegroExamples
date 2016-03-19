#include <stdio.h>
#include <allegro5/allegro.h>

const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int BOUNCER_SIZE = 32;

int main(int argc, char **argv) {
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *bouncer = NULL;

    float bouncer_x = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
    float bouncer_y = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;
    float bouncer_dx = -4.0, bouncer_dy = 4.0;
    bool redraw = true;

    // Initialize Allegro Library
    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro\n");
        return -1;
    }
    // Initialize mouse
    if (!al_install_mouse()) {
        fprintf(stderr, "failed to initialize the mouse\n");
        return -1;
    }
    // Create Timer, generating events FPS times per second
    timer = al_create_timer(1.0 / FPS);
    if (!timer) {
        fprintf(stderr, "failed to create timer\n");
        return -1;
    }
    // Create Display
    display = al_create_display(SCREEN_W, SCREEN_H);
    if (!display) {
        fprintf(stderr, "failed to create display\n");
        al_destroy_timer(timer);
        return -1;
    }
    // Create Event Queue
    event_queue = al_create_event_queue();
    if (!event_queue) {
        fprintf(stderr, "failed to create event_queue\n");
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }
    // Create Bitmap
    bouncer = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
    if (!bouncer) {
        fprintf(stderr, "failed to create bouncer bitmap\n");
        al_destroy_display(display);
        al_destroy_timer(timer);
        al_destroy_event_queue(event_queue);
        return -1;
    }
    // Indicate we're drawing on the bouncer bitmap instead of display
    al_set_target_bitmap(bouncer);
    bool is_yellow = false;
    ALLEGRO_COLOR pink = al_map_rgb(255, 0, 255);
    ALLEGRO_COLOR yellow = al_map_rgb(255, 255, 0);
    al_clear_to_color(pink);
    // set target back on to screen buffer
    al_set_target_bitmap(al_get_backbuffer(display));

    // Tie events from display to the event queue
    al_register_event_source(event_queue, al_get_display_event_source(display));
    // And from the timer
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    // And the mouse
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();
    al_start_timer(timer);

    while (true) {
        ALLEGRO_EVENT ev;
        // Timer is ticking, dont worry about timeouts
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER) {
            redraw = true;
        } else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
                   ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
            bouncer_x = ev.mouse.x;
            bouncer_y = ev.mouse.y;
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        } else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            al_set_target_bitmap(bouncer);
            if (is_yellow) {
                al_clear_to_color(pink);
                is_yellow = false;
            } else {
                al_clear_to_color(yellow);
                is_yellow = true;
            }
            al_set_target_bitmap(al_get_backbuffer(display));
        }
        // An empty queue is important when we have multiple events stacked up to handle
        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);
            al_flip_display();
        }
    }

    al_destroy_bitmap(bouncer);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}