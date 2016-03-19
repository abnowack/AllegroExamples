#ifndef ALLEGROEXAMPLES_ASSETS_H
#define ALLEGROEXAMPLES_ASSETS_H

struct sprite_map_asset {
    char file_path[20];
    unsigned int frame_nx;
    unsigned int frame_ny;
    unsigned int frame_dx;
    unsigned int frame_dy;
};

struct assets {
    struct sprite_map_asset warrior;
} assets = {
        {
                "assets/warrior.png",
                21, 7, 15, 12,
        }
};

#endif //ALLEGROEXAMPLES_ASSETS_H
