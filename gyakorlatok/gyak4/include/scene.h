#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include <stdio.h>
#include <math.h>
typedef struct Scene
{
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

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

/**
 * Draw the triangles.
 */
void draw_triangles();
/**
 * Draw the circle.
 */
void draw_circle(float center_x, float center_y, float center_z, float radius, int segments);


#endif /* SCENE_H */