#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include "leaf.h"

#include <obj/model.h>

typedef struct Scene
{
    Model tree;
    Leaf leaf;
    Material material;
    GLuint tree_texture_id;
    GLuint leaf_texture_id;
    float lighting_level;
    GLfloat fogColor[4];
    bool helpmenu_bool;
    GLuint helpmenu_t;
    vec3* initial_tree_vertices;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting(float lighting_level);

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Update the scene.
 */
void update_scene(Scene* scene);

/**
 * Render the scene objects.
 */
void render_scene(const Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

#endif /* SCENE_H */
