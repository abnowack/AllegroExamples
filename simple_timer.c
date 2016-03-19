#include <stdio.h>
#include <allegro5/allegro.h>

const float FPS = 60;

int main(int argc, char **argv) {
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    bool redraw = true;

    // Initialize Allegro Library
    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro\n");
        return -1;
    }
    // Create Timer, generating events FPS times per second
    timer = al_create_timer(1.0 / FPS);
    if (!timer) {
        fprintf(stderr, "failed to create timer\n");
        return -1;
    }
    // Create Display
    display = al_create_display(640, 480);
    if (!display) {
        fprintf(stderr, "failed to create display\n");
        return -1;
    }
    // Create Event Queue
    event_queue = al_create_event_queue();
    if (!event_queue) {
        fprintf(stderr, "failed to create event_queue\n");
        al_destroy_display(display);
        return -1;
    }

    // Tie events from display to the event queue
    al_register_event_source(event_queue, al_get_display_event_source(display));
    // And from the timer
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();
    al_start_timer(timer);

    while (true) {
        ALLEGRO_EVENT ev;
        // Timer is ticking, dont worry about timeouts
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER) {
            redraw = true;
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        // An empty queue is important when we have multiple events stacked up to handle
        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_flip_display();
        }
    }

    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}