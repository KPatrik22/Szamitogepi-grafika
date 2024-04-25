#include "scene.h"
#include "leaf.h"
#include <obj/load.h>
#include <obj/model.h>
#include <obj/draw.h>

void init_scene(Scene* scene)
{
    load_model(&(scene->tree), "assets/models/tree2.obj");
    scene->tree_texture_id = load_texture("assets/textures/tree2.jpg");

    scene->helpmenu_t = load_texture("assets/textures/helpmenu_v2.png");

    init_leaf(&(scene->leaf));

    scene->material.ambient.red = 1.0;
    scene->material.ambient.green = 1.0;
    scene->material.ambient.blue = 1.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 1.0;
    scene->material.specular.green = 1.0;
    scene->material.specular.blue = 1.0;

    scene->material.shininess = 0.0;
    scene->lighting_level = 0.0;

    scene->fogColor[0] = 0.5f;
    scene->fogColor[1] = 0.5f;
    scene->fogColor[2] = 0.5f;
    scene->fogColor[3] = 1.0f;
    glEnable(GL_FOG);
    glFogf(GL_FOG_DENSITY, 0.0f);
    glFogfv(GL_FOG_COLOR, scene->fogColor);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    set_lighting(scene->lighting_level);
    scene->helpmenu_bool = false;

    scene->initial_tree_vertices = malloc(scene->tree.n_vertices * sizeof(vec3));
    if (scene->initial_tree_vertices == NULL) {
        // Handle memory allocation failure
        return;
    }
    
    for (int i = 0; i < scene->tree.n_vertices; ++i) {
        for (int i = 0; i < scene->tree.n_vertices; ++i) {
        scene->initial_tree_vertices[i].x = scene->tree.vertices[i].x;
        scene->initial_tree_vertices[i].y = scene->tree.vertices[i].y;
        scene->initial_tree_vertices[i].z = scene->tree.vertices[i].z;
    }
    }
}

void set_lighting(float lighting_level)
{
    float ambient_light[] = { lighting_level, lighting_level, lighting_level, 1.0f };
    float diffuse_light[] = { lighting_level, lighting_level, lighting_level, 1.0f };
    float specular_light[] = { lighting_level, lighting_level, lighting_level, 1.0f };
    float position[] = { 0.0f, 0.0f, 3.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void helpmenu(GLuint tid)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBindTexture(GL_TEXTURE_2D, tid);
    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-2.0, 2.0, -3);
    glTexCoord2f(1, 0);
    glVertex3f(2.0, 2.0, -3);
    glTexCoord2f(1, 1);
    glVertex3f(2.0, -2.0, -3);
    glTexCoord2f(0, 1);
    glVertex3f(-2.0, -2.0, -3);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

//void update_scene(Scene* scene){}

void render_scene(const Scene* scene)
{
    GLfloat light_position[] = { 0.0, 0, 3, 2.0f };
    GLfloat light_direction[] = { 0.0f, 0.0f, -1.0f };
    GLfloat light_color[] = { 1.0f, 1.0f, 1.0f, 2.0f };
    GLfloat spot_cutoff = 45.0f;
    GLfloat spot_exponent = 2.0f;
    
    set_material(&(scene->material));
    
    glBindTexture(GL_TEXTURE_2D, scene->tree_texture_id);
    glPushMatrix();
    draw_model(&(scene->tree));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(scene->leaf.pos.x, scene->leaf.pos.y, scene->leaf.pos.z);
    glScalef(0.5,0.5,0.5);
    glBindTexture(GL_TEXTURE_2D, scene->leaf.texture_id);
    draw_model(&(scene->leaf.model));
    glPopMatrix();

    if(scene->helpmenu_bool == true)
    {
        helpmenu(scene->helpmenu_t);
    }    

    draw_origin();
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}
