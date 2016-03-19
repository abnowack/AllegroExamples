#ifndef ALLEGROEXAMPLES_TILE_MAP_H
#define ALLEGROEXAMPLES_TILE_MAP_H

#include "sprite.h"

struct tile_map {
    struct sprite_map* smap;
    unsigned int nx;
    unsigned int ny;
    unsigned int **tiles;
};

struct tile_map* tile_map_create(struct sprite_map* smap, unsigned int nx, unsigned int ny) {
    struct tile_map* tmap = malloc(sizeof(struct tile_map));
    tmap->smap = smap;
    tmap->nx = nx;
    tmap->ny = ny;
    tmap->tiles = malloc(sizeof(unsigned int*) * ny);
    for (unsigned int iy = 0; iy < ny; iy++) {
        tmap->tiles[iy] = malloc(sizeof(unsigned int) * nx);
    }

    return tmap;
}

void tile_map_draw(struct tile_map* tmap, unsigned int x, unsigned int y) {
    for (unsigned int iy = 0; iy < tmap->ny; iy++) {
        for (unsigned int ix = 0; ix < tmap->nx; ix++) {
            unsigned int xpos = ix * tmap->smap->frame_dx;
            unsigned int ypos = iy * tmap->smap->frame_dy;
            sprite_map_draw(tmap->smap, tmap->tiles[iy][ix], xpos, ypos);
        }
    }
}

#endif //ALLEGROEXAMPLES_TILE_MAP_H
