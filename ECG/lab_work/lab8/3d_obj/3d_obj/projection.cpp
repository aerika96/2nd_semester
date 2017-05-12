//
//  projection.cpp
//  Lab8_TODO
//
//  Copyright © 2016 CGIS. All rights reserved.
//

#include "projection.h"

namespace egc {
    mat4 defineViewTransformMatrix(int startX, int startY, int width, int height)
    {
        mat4 viewTransformMatrix;

		mat4 T = translate(1.0f, -1.0f, 0.0f);
		mat4 M;
		M.at(1, 1) = -1.0f;
		mat4 S = scale(width / 2, height / 2, 1.0f);
		mat4 T2 = translate(startX, startY, 1);

		viewTransformMatrix = T2 * S * M *T;
        
        return viewTransformMatrix;
    }
    
    mat4 defineCameraMatrix(Camera myCamera)
    {
        mat4 cameraMatrix;

		vec3 e = myCamera.cameraPosition;
		vec3 g = myCamera.cameraTarget - e ;
		vec3 t = myCamera.cameraUp;

		vec3 w = g;
		w.normalize;
		


        
        return cameraMatrix;
    }
    
    mat4 definePerspectiveProjectionMatrix(float fov, float aspect, float zNear, float zFar)
    {
        mat4 perspectiveMatrix;
        
        return perspectiveMatrix;
    }
    
    void perspectiveDivide(vec4 &inputVertex)
    {
        
    }
}