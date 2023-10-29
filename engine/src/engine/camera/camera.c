#include "../global.h"
#include "camera.h"

Camera* camera_init(i16 near, i16 far, f32 aspect_ratio)
{
    Camera* res = (Camera *) malloc(sizeof(Camera*));
    res->near = near;
    res->far = far;
    res->aspect_ratio = aspect_ratio;
    mat4x4_identity(res->view);
    return res;
}

void camera_use(Camera* camera)
{
    memcpy(global.window.renderer.view, camera->view, sizeof(camera->view));
}

void camera_move(Camera* camera,vec2 pos)
{
    mat4x4_translate(camera->view,pos[0],pos[1],0);
}