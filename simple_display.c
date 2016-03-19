#include <stdio.h>
#include <allegro5/allegro.h> // required for all allegro programs, must be with main function

int main(int argc, char **argv) {
    ALLEGRO_DISPLAY *display = NULL;

    // Initialize Allegro Library
    if(!al_init()) {
        fprintf(stderr, "failed to initialize allegro\n");
        return -1;
    }
    // Create Display
    display = al_create_display(640, 480);
    if (!display) {
        fprintf(stderr, "failed to create display\n");
        return -1;
    }
    // Clear Display to a color
    al_clear_to_color(al_map_rgb(0,0,0));
    // Put drawn display (buffer) into display within the window on screen
    al_flip_display();
    al_rest(1);

    // Flip between colors
    // red
    al_clear_to_color(al_map_rgb(255, 0, 0));
    al_flip_display();
    al_rest(1);
    // green
    al_clear_to_color(al_map_rgb(0, 255, 0));
    al_flip_display();
    al_rest(1);
    // blue
    al_clear_to_color(al_map_rgb(0, 0, 255));
    al_flip_display();
    al_rest(1);

    al_destroy_display(display);

    return 0;
}