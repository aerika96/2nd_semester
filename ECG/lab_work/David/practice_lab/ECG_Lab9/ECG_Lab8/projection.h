//
//  projection.h
//  Lab8_TODO
//
//  Copyright © 2016 CGIS. All rights reserved.
//

#pragma once

#include "vec3.h"
#include "vec4.h"
#include "mat4.h"
#include "camera.h"
#include "transform.h"

namespace egc {
    mat4 defineViewTransformMatrix(int startX, int startY, int width, int height);
    mat4 defineCameraMatrix(Camera myCamera);
    mat4 definePerspectiveProjectionMatrix(float fov, float aspect, float zNear, float zFar);
    void perspectiveDivide(vec4 &inputVertex);
}