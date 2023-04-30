
#include "cuboid.h"
#include <stdio.h>

int main(){

    struct Cuboid tegla;

    tegla = set_size();
    printf("\n");

    printf("a= %f, b= %f, magassag= %f\n",tegla.a,tegla.b,tegla.magassag);

    calc_volume(tegla);

    calc_surface(tegla);

    vannegyzet(tegla);

    return 0;
}