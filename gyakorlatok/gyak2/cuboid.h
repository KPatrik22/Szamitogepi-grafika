#ifndef CUBOID_H
#define CUBOID_H

struct Cuboid{
    float a;
    float b;
    float magassag;
}Cuboid;
struct Cuboid set_size();
void calc_volume(struct Cuboid tegla);
void calc_surface(struct Cuboid tegla);
void vannegyzet(struct Cuboid tegla);
#endif