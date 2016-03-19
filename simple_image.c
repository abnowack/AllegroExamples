#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

const int SCREEN_W = 640;
const int SCREEN_H = 480;

int main(int argc, char **argv) {
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_BITMAP *image = NULL;

    // Initialize Allegro Library
    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro\n");
        return -1;
    }
    // Initialize image display library
    if (!al_init_image_addon()) {
        fprintf(stderr, "failed to initialize al_init_image_addon\n");
        return -1;
    }
    // Create Display
    display = al_create_display(SCREEN_W, SCREEN_H);
    if (!display) {
        fprintf(stderr, "failed to create display\n");
        return -1;
    }
    // Create Bitmap
    image = al_load_bitmap("share/paper_mario.png");
    if (!image) {
        fprintf(stderr, "failed to load image\n");
        al_destroy_display(display);
        return -1;
    }
    // Draw bitmap onto display
    al_draw_bitmap(image, 200, 200, 0);
    al_flip_display();
    al_rest(2);

    al_destroy_bitmap(image);
    al_destroy_display(display);

    return 0;
}