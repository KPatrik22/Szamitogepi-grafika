#include "leaf.h"

void init_leaf(Leaf *leaf)
{
    load_model(&(leaf->model), "assets/models/leaf.obj");
    leaf->texture_id = load_texture("assets/textures/leaf.png");

    leaf->pos.x = 0;
    leaf->pos.y = 1;
    leaf->pos.z = 2.5;

    leaf->speed.x = 0.0;
    leaf->speed.y = 0.0;
    leaf->speed.z = 0.0;

}

void leaf_kezdo(Leaf *leaf)
{
    leaf->pos.x = 0; 
    leaf->pos.y = 1;
    leaf->pos.z = 2.5;
    leaf->speed.z = 0.0;
}

void set_leaf_speedz(Leaf *leaf, double speed)
{
    leaf->speed.z = speed;
}

void move_leaf(Leaf *leaf, double time)
{
    leaf->pos.x += leaf->speed.x * time;
    leaf->pos.y += leaf->speed.y * time;
    leaf->pos.z += leaf->speed.z * time;

}