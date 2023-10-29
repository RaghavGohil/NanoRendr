#pragma once

#include <linmath.h>
#include "../types.h"

typedef struct camera
{
    i16 near,far;
    f32 aspect_ratio;
    mat4x4 view;
}Camera;

Camera* camera_init(i16 near, i16 far, f32 aspect_ratio);

void camera_use(Camera* camera);
void camera_move(Camera* camera, vec2 pos);