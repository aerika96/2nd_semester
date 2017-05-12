/*
	Created by David
*/

#include "transform.h"

namespace egc {
	mat3 translate(const vec2 translateArray) {
		mat3 trans_mat;

		trans_mat.at(0, 2) = translateArray.x;
		trans_mat.at(1, 2) = translateArray.y;

		return trans_mat;
	}
	mat3 translate(float tx, float ty) {
		mat3 trans_mat;

		trans_mat.at(0, 2) = tx;
		trans_mat.at(1, 2) = ty;

		return trans_mat;
	}
    
	mat3 scale(const vec2 scaleArray) {
		mat3 scale_mat;

		scale_mat.at(0, 0) = scaleArray.x;
		scale_mat.at(1, 1) = scaleArray.y;

		return scale_mat;
	}
	mat3 scale(float sx, float sy) {
		mat3 scale_mat;

		scale_mat.at(0, 0) = sx;
		scale_mat.at(1, 1) = sy;

		return scale_mat;
	}
    
	mat3 rotate(float angle) {
		mat3 rot_mat;
		double rad = (PI / 180)*angle;

		rot_mat.at(0, 0) = (float)cos(rad);
		rot_mat.at(0, 1) = -(float)sin(rad);
		rot_mat.at(1, 0) = (float)sin(rad);
		rot_mat.at(1, 1) = (float)cos(rad);

		return rot_mat;
	}

    //transformation matrices in 3D
	mat4 translate(const vec3 translateArray) {
		mat4 trans_mat;

		trans_mat.at(0, 3) = translateArray.x;
		trans_mat.at(1, 3) = translateArray.y;
		trans_mat.at(2, 3) = translateArray.z;

		return trans_mat;
	}
	mat4 translate(float tx, float ty, float tz) {
		mat4 trans_mat;

		trans_mat.at(0, 3) = tx;
		trans_mat.at(1, 3) = ty;
		trans_mat.at(2, 3) = tz;

		return trans_mat;
	}
    
	mat4 scale(const vec3 scaleArray) {
		mat4 scale_mat;

		scale_mat.at(0, 0) = scaleArray.x;
		scale_mat.at(1, 1) = scaleArray.y;
		scale_mat.at(2, 2) = scaleArray.z;

		return scale_mat;
	}
	mat4 scale(float sx, float sy, float sz) {
		mat4 scale_mat;

		scale_mat.at(0, 0) = sx;
		scale_mat.at(1, 1) = sy;
		scale_mat.at(2, 2) = sz;

		return scale_mat;
	}
    
	mat4 rotateX(float angle) {
		mat4 rotx_mat;

		double rad = (PI / 180)*angle;

		rotx_mat.at(1, 1) = (float)cos(rad);
		rotx_mat.at(1, 2) = -(float)sin(rad);
		rotx_mat.at(2, 1) = (float)sin(rad);
		rotx_mat.at(2, 2) = (float)cos(rad);

		return rotx_mat;
	}
	mat4 rotateY(float angle) {
		mat4 roty_mat;

		double rad = (PI / 180)*angle;

		roty_mat.at(0, 0) = (float)cos(rad);
		roty_mat.at(0, 2) = (float)sin(rad);
		roty_mat.at(2, 0) = -(float)sin(rad);
		roty_mat.at(2, 2) = (float)cos(rad);

		return roty_mat;
	}
	mat4 rotateZ(float angle) {
		mat4 rotz_mat;

		double rad = (PI / 180)*angle;

		rotz_mat.at(0, 0) = (float)cos(rad);
		rotz_mat.at(0, 1) = -(float)sin(rad);
		rotz_mat.at(1, 0) = (float)sin(rad);
		rotz_mat.at(1, 1) = (float)cos(rad);

		return rotz_mat;
	}
}