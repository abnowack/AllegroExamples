#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "assets.h"
#include "sprite.h"

int main(int argc, char **argv) {
    ALLEGRO_DISPLAY *display = NULL;

    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro\n");
        return -1;
    }

    if (!al_init_image_addon()) {
        fprintf(stderr, "failed to initialize al_init_image_addon\n");
        return -1;
    }

    display = al_create_display(640, 480);

    struct sprite_map_asset warrior_asset = {
            .file_path = "assets/warrior.png",
            .frame_nx = 21,
            .frame_ny = 7,
            .frame_dx = 12,
            .frame_dy = 15
    };
    struct sprite_map* warrior_smap = sprite_map_create(warrior_asset);

    unsigned int run_frames[6] = {2, 3, 4, 5, 6, 7};
    struct animation_sequence* warrior_run = animation_sequence_create("run", 1, run_frames, 6);

    unsigned int death_frames

    struct animation* run_animation = animation_create(warrior_smap, warrior_run);

    for (unsigned int i = 0; i < 20; i++) {
        al_clear_to_color(al_map_rgb(0, 0, 0));

        animation_draw(run_animation, 100, 100);

        al_flip_display();

        animation_step_frame(run_animation);
        al_rest(0.5);
    }

    al_flip_display();

    al_destroy_display(display);
    return 0;
}