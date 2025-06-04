#include "exercise.h"

struct Coordinate new_coord(int x, int y, int z) {
    coordinate_t c = {
        .x = x,
        .y = y,
        .z = z
    };
    return c;
}

struct Coordinate scale_coordinate(coordinate_t coord, int factor) {
    coordinate_t scaled = {
        .x = coord.x * factor,
        .y = coord.y * factor,
        .z = coord.z * factor
    };
    return scaled;
}


