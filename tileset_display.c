#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

const int SCREEN_W = 600;
const int SCREEN_H = 400;
const int tw = 50;

const int tmap[8][12] =
        {{}}

void draw_tile(ALLEGRO_BITMAP *im, unsigned int si, unsigned int sj, unsigned int sw, unsigned int di, unsigned int dj, unsigned int dw) {
    al_draw_scaled_bitmap(im, 17 * si + 1, 17 * sj + 1, 16, 16, dw * di, dw * dj, dw, dw, 0);
}

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
    image = al_load_bitmap("share/zelda_tileset.bmp");
    if (!image) {
        fprintf(stderr, "failed to load image\n");
        al_destroy_display(display);
        return -1;
    }

    // Draw bitmap onto display
    draw_tile(image, 13, 7, 16, 0, 0, tw);
    draw_tile(image, 14, 7, 16, 1, 0, tw);
    draw_tile(image, 15, 7, 16, 2, 0, tw);

    draw_tile(image, 13, 8, 16, 0, 1, tw);
    draw_tile(image, 14, 8, 16, 1, 1, tw);
    draw_tile(image, 15, 8, 16, 2, 1, tw);

    draw_tile(image, 13, 8, 16, 0, 2, tw);
    draw_tile(image, 14, 6, 16, 1, 2, tw);
    draw_tile(image, 15, 8, 16, 2, 2, tw);

    draw_tile(image, 13, 8, 16, 0, 3, tw);
    draw_tile(image, 13, 6, 16, 1, 3, tw);
    draw_tile(image, 15, 8, 16, 2, 3, tw);

    draw_tile(image, 13, 9, 16, 0, 4, tw);
    draw_tile(image, 14, 9, 16, 1, 4, tw);
    draw_tile(image, 15, 9, 16, 2, 4, tw);
//    al_draw_bitmap(image, 200, 200, 0);
    al_flip_display();
    al_rest(5);

    al_destroy_bitmap(image);
    al_destroy_display(display);

    return 0;
}