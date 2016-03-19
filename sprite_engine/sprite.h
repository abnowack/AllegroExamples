#ifndef ALLEGROEXAMPLES_SPRITE_H_H
#define ALLEGROEXAMPLES_SPRITE_H_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "assets.h"

struct sprite_map {
    ALLEGRO_BITMAP *image;
    unsigned int frame_nx;
    unsigned int frame_ny;
    unsigned int frame_dx;
    unsigned int frame_dy;
};

struct sprite_map *sprite_map_create(struct sprite_map_asset asset) {
    struct sprite_map *smap = malloc(sizeof(struct sprite_map));

    smap->image = al_load_bitmap(asset.file_path);
    smap->frame_nx = asset.frame_nx;
    smap->frame_ny = asset.frame_ny;
    smap->frame_dx = asset.frame_dx;
    smap->frame_dy = asset.frame_dy;
}

void sprite_map_draw_framexy(struct sprite_map* smap, unsigned int frame_ix, unsigned int frame_iy, unsigned int x, unsigned int y) {
    unsigned int frame_xpixel = smap->frame_dx * frame_ix;
    unsigned int frame_ypixel = smap->frame_dy * frame_iy;
    al_draw_bitmap_region(smap->image, frame_xpixel, frame_ypixel, smap->frame_dx, smap->frame_dy, x, y, 0);
}

void sprite_map_draw(struct sprite_map* smap, unsigned int frame, unsigned int x, unsigned int y) {
    unsigned int frame_ix = frame % smap->frame_nx;
    unsigned int frame_iy = frame / smap->frame_nx;
    sprite_map_draw_framexy(smap, frame_ix, frame_iy, x, y);
}

struct animation_sequence {
    unsigned int repeat;
    char name[20];
    unsigned int *frames;
    unsigned int nframes;
};

struct animation_sequence* animation_sequence_create(char *name, unsigned int repeat, unsigned int* frames, unsigned int nframes) {
    struct animation_sequence* anim_seq = malloc(sizeof(struct animation_sequence));
    strcpy(anim_seq->name, name);
    anim_seq->repeat = repeat;
    anim_seq->frames = malloc(nframes * sizeof(unsigned int));
    for (unsigned int i = 0; i < nframes; i++) anim_seq->frames[i] = frames[i];
    anim_seq->nframes = nframes;

    return anim_seq;
}

struct animation {
    struct sprite_map* smap;
    struct animation_sequence* anim_seq;
    unsigned int frame_index;
};

struct animation* animation_create(struct sprite_map* smap, struct animation_sequence* anim_seq) {
    struct animation* anim = malloc(sizeof(struct animation));
    anim->smap = smap;
    anim->anim_seq = anim_seq;
    anim->frame_index = 0;
}

void animation_step_frame(struct animation* anim) {
    if (anim->frame_index < (anim->anim_seq->nframes-1))
        anim->frame_index++;
    else if (anim->frame_index == (anim->anim_seq->nframes - 1)) {
        if (anim->anim_seq->repeat > 0)
            anim->frame_index = 0;
    }
}

void animation_draw(struct animation* anim, unsigned int x, unsigned int y) {
    unsigned int frame = anim->anim_seq->frames[anim->frame_index];
    sprite_map_draw(anim->smap, frame, x, y);
}

#endif //ALLEGROEXAMPLES_SPRITE_H_H
