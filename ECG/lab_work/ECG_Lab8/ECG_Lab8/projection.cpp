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
		mat4 T1 = translate(1.0f, -1.0f, 0.0f);
		mat4 M;
		M.at(1, 1) = -1.0f;
		mat4 S = scale(width / 2, height / 2, 1);
		mat4 T2 = translate(startX, startY, 1);

		viewTransformMatrix = T2 * S * M * T1;
        return viewTransformMatrix;
    }
    
    mat4 defineCameraMatrix(Camera myCamera)
    {
        mat4 cameraMatrix;

		vec3 e = myCamera.cameraPosition;
		vec3 g = myCamera.cameraTarget - e;
		vec3 t = myCamera.cameraUp;
        
		vec3 w = g;
		w.normalize();

		vec3 u = crossProduct(t, w);
		u.normalize();

		vec3 v = crossProduct(w, u);

		mat4 coord;

		coord.at(0, 0) = u.x;
		coord.at(0, 1) = u.y;
		coord.at(0, 2) = u.z;

		coord.at(1, 0) = v.x;
		coord.at(1, 1) = v.y;
		coord.at(1, 2) = v.z;

		coord.at(2, 0) = w.x;
		coord.at(2, 1) = w.y;
		coord.at(2, 2) = w.z;

		mat4 T = translate(-e);

		cameraMatrix = coord * T;
        return cameraMatrix;
    }
    
    mat4 definePerspectiveProjectionMatrix(float fov, float aspect, float zNear, float zFar)
    {
		float tan = tanf(fov/2);
        mat4 perspectiveMatrix;
		perspectiveMatrix.at(0, 0) /= aspect * tan;
		perspectiveMatrix.at(1, 1) /= tan;
		perspectiveMatrix.at(2, 2) = (zFar + zNear) / (zNear - zFar);
		perspectiveMatrix.at(2, 3) = (2 * zFar * zNear) / (zFar - zNear);
		perspectiveMatrix.at(3, 2) = 1;
		perspectiveMatrix.at(3, 3) = 0;
        
        return perspectiveMatrix;
    }
    
    void perspectiveDivide(vec4 &inputVertex)
    {
		inputVertex.x /= inputVertex.w;
		inputVertex.y /= inputVertex.w;
		inputVertex.z /= inputVertex.w;
		inputVertex.w /= inputVertex.w;
    }
}