#include<../global.h>
#include<camera.h>

Camera* init_camera(i16 near, i16 far, f32 aspect_ratio)
{
    Camera res;
    res.near = near;
    res.far = far;
    res.aspect_ratio = aspect_ratio;
    mat4x4_identity(res.view);
    return &res;
}

void use_camera(Camera* camera)
{
    memcpy(global.window.renderer.view, camera->view, sizeof(camera->view));
}