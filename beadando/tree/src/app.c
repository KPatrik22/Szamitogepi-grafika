#include "app.h"
#include "leaf.h"

#include <SDL2/SDL_image.h>

float shake_amount = 0.0f;
float shake_frequency = 10.0f;

bool leaf_falling = false;
bool fogDensityEnabled = true;

float min = 0.2f;
float max = 2.0f;
float current_x, current_y = 1.5f;

void init_app(App* app, int width, int height)
{
    int error_code;
    int inited_loaders;

    app->is_running = false;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0) {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return;
    }

    app->window = SDL_CreateWindow(
        "Tree",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_OPENGL);
    if (app->window == NULL) {
        printf("[ERROR] Unable to create the application window!\n");
        return;
    }

    inited_loaders = IMG_Init(IMG_INIT_PNG);
    if (inited_loaders == 0) {
        printf("[ERROR] IMG initialization error: %s\n", IMG_GetError());
        return;
    }

    app->gl_context = SDL_GL_CreateContext(app->window);
    if (app->gl_context == NULL) {
        printf("[ERROR] Unable to create the OpenGL context!\n");
        return;
    }

    init_opengl();
    reshape(width, height);

    init_camera(&(app->camera));
    init_scene(&(app->scene));

    app->is_running = true;
}

void init_opengl()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.1, 0.1, 0.1, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(
        -.08, .08,
        -.06, .06,
        .1, 10
    );
}

void handle_app_events(App* app)
{
    SDL_Event event;
    static bool is_mouse_down = false;
    static int mouse_x = 0;
    static int mouse_y = 0;
    int x;
    int y;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:
                app->is_running = false;
                break;
            case SDL_SCANCODE_W:
                set_camera_speed(&(app->camera), 1);
                break;
            case SDL_SCANCODE_S:
                set_camera_speed(&(app->camera), -1);
                break;
            case SDL_SCANCODE_A:
                set_camera_side_speed(&(app->camera), 1);
                break;
            case SDL_SCANCODE_D:
                set_camera_side_speed(&(app->camera), -1);
                break;
            case SDL_SCANCODE_P:
                if(app->scene.lighting_level <= 1)
                {
                    app->scene.lighting_level += 0.2f;
                }
                set_lighting(app->scene.lighting_level);
                break;
            case SDL_SCANCODE_O:
                if(app->scene.lighting_level >= -0.2f)
                {
                    app->scene.lighting_level -= 0.2f;
                }
                set_lighting(app->scene.lighting_level);
                break;
            case SDL_SCANCODE_F1:
                if (app->scene.helpmenu_bool)
                {
                    app->scene.helpmenu_bool = false;
                  
                }
                else
                {
                    app->scene.helpmenu_bool = true;
                }
                break;
            case SDL_SCANCODE_K:
                fogDensityEnabled = !fogDensityEnabled;
                if (fogDensityEnabled) {
                    glFogf(GL_FOG_DENSITY, 0.5f); 
                } else {
                    glFogf(GL_FOG_DENSITY, 0.0f);
                } 
                break;
            case SDL_SCANCODE_1:
                shake_amount += 0.01f;
                break;
            case SDL_SCANCODE_2:
                shake_amount = 0.0f;
                break;
            case SDL_SCANCODE_3:
                leaf_falling = false;
                generate_random_coordinates(&current_x, &current_y, min, max);
                leaf_falling = true;
                break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_S:
                set_camera_speed(&(app->camera), 0);
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_D:
                set_camera_side_speed(&(app->camera), 0);
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            is_mouse_down = true;
            break;
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&x, &y);
            if (is_mouse_down) {
                rotate_camera(&(app->camera), mouse_x - x, mouse_y - y);
            }
            mouse_x = x;
            mouse_y = y;
            break;
        case SDL_MOUSEBUTTONUP:
            is_mouse_down = false;
            break;
        case SDL_QUIT:
            app->is_running = false;
            break;
        default:
            break;
        }
    }
}

void update_scene(Scene* scene)
{
    
}

void generate_random_coordinates(float *x, float *y, float min, float max) {
    *x = ((float)rand() / RAND_MAX) * (max - min) + min;
    *y = ((float)rand() / RAND_MAX) * (max - min) + min;
}

void update_app(App* app)
{
    double current_time;
    double elapsed_time;

    current_time = (double)SDL_GetTicks() / 1000;
    elapsed_time = current_time - app->uptime;
    app->uptime = current_time;

    update_camera(&(app->camera), elapsed_time);
    update_scene(&(app->scene));

    if (leaf_falling == true) 
    {
        app->scene.leaf.pos.x = current_x;
        app->scene.leaf.pos.y = current_y;
        app->scene.leaf.speed.z = -1.0;
        move_leaf(&(app->scene.leaf), elapsed_time);
    }
    else 
    {
        leaf_falling = false;
        leaf_kezdo(&(app->scene.leaf));
    }

    if (shake_amount > 0.0f) {
        float displacement = shake_amount * sin(SDL_GetTicks() / shake_frequency);
        
        for (int i = 0; i < app->scene.tree.n_vertices; ++i) {
            app->scene.tree.vertices[i].x += displacement;
            app->scene.tree.vertices[i].y += displacement;
            app->scene.tree.vertices[i].z += displacement;
        }
    }

    if(app->scene.leaf.pos.z < 0) 
    {
        leaf_falling = false;
        leaf_kezdo(&(app->scene.leaf));
    }
}

void render_app(App* app)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    set_view(&(app->camera));
    render_scene(&(app->scene));
    glPopMatrix();

    if (app->camera.is_preview_visible) {
        show_texture_preview();
    }

    SDL_GL_SwapWindow(app->window);
}

void destroy_app(App* app)
{
    if (app->gl_context != NULL) {
        SDL_GL_DeleteContext(app->gl_context);
    }

    if (app->window != NULL) {
        SDL_DestroyWindow(app->window);
    }

    SDL_Quit();
}
