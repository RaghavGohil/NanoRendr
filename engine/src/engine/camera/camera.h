#pragma once

#include <linmath.h>
#include <../types.h>

typedef struct camera
{
    i16 near,far;
    f32 aspect_ratio;
    mat4x4 view;
}Camera;

Camera* init_camera(i16 near, i16 far, f32 aspect_ratio);

void use_camera(Camera* camera);