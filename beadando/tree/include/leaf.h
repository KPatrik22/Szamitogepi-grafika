#ifndef LEAF_H
#define LEAF_H

#include <obj/model.h>

#include "texture.h"
#include "utils.h"
#include "camera.h"
#include <stdbool.h>

typedef struct Leaf
{
    GLuint texture_id;
    Model model;
    vec3 pos;
    vec3 speed;

} Leaf;

void init_leaf(Leaf* leaf);

void leaf_kezdo(Leaf* leaf);

void set_leaf_speedz(Leaf* leaf, double speed);

void move_leaf(Leaf* leaf, double time);

#endif /*LEAF_H*/