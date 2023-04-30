#include <stdio.h>
#include <stdlib.h>

struct Cuboid set_size();
void calc_volume(struct Cuboid tegla);
void calc_surface(struct Cuboid tegla);
void vannegyzet(struct Cuboid tegla);

struct Cuboid{
    float a;
    float b;
    float magassag;
}Cuboid;

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
struct Cuboid set_size(){
    struct Cuboid tegla;
    int jo_e;
    do
    {
        jo_e = 1;
        printf("Adja meg a Cuboid adatait: \n");
        printf("a= ");
        if(scanf("%f", &tegla.a) != 1)
        {
            jo_e = 0;
            printf("Rossz input!");
        }
        printf("b= ");
        if(scanf("%f", &tegla.b) != 1)
        {
            jo_e = 0;
            printf("Rossz input!");
        }
        printf("magassag= ");
        if(scanf("%f", &tegla.magassag) != 1)
        {
            jo_e = 0;
            printf("Rossz input!");
        }
        
        while(getchar() != '\n');
    }
    while(!jo_e);
    return tegla;
}
void calc_volume(struct Cuboid tegla){
    printf("Terfogat= %fcm^3\n",tegla.a * tegla.b * tegla.magassag);
}
void calc_surface(struct Cuboid tegla){
    float a = 2 * (tegla.a * tegla.magassag + tegla.b * tegla.magassag + tegla.a * tegla.b);
    printf("Felszin= %fcm^2\n",a);
}
void vannegyzet(struct Cuboid tegla){
    if(tegla.a == tegla.b || tegla.a == tegla.magassag || tegla.b == tegla.magassag){
        printf("Van negyzet alaku lapja!");
    }
    else{
        printf("Nincs negyzet alaku lapja!");
    }
    
}