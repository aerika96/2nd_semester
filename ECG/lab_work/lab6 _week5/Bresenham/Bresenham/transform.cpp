
#include "transform.h"

namespace egc{
	
	mat3 translate(const vec2 translateArray) {
		mat3 matr;
		for (int i = 0; i < 9; i++) { 
			matr.matrixData[i] = 0;
		}
		matr.matrixData[0] = 1;
		matr.matrixData[4] = 1;
		matr.matrixData[8] = 1;
		matr.matrixData[6] = translateArray.x;
		matr.matrixData[7] = translateArray.y;
		return matr;
	}
	mat3 translate(float tx, float ty) {
		mat3 matr;
		for (int i = 0; i < 9; i++) {
			matr.matrixData[i] = 0;
		}
		matr.matrixData[0] = 1;
		matr.matrixData[4] = 1;
		matr.matrixData[8] = 1;
		matr.matrixData[6] = tx;
		matr.matrixData[7] = ty;
		return matr;

	}
	mat3 scale(const vec2 scaleArray) {
		mat3 matr;
		for (int i = 0; i < 9; i++) {
			matr.matrixData[i] = 0;
		}
		matr.matrixData[8] = 1;
		matr.matrixData[0] = scaleArray.x;
		matr.matrixData[4] = scaleArray.y;
		return matr;
	}


	mat3 scale(float sx, float sy){
		mat3 matr;
		for (int i = 0; i < 9; i++) {
			matr.matrixData[i] = 0;
		}
		matr.matrixData[8] = 1;
		matr.matrixData[0] = sx;
		matr.matrixData[4] = sy;
		return matr;
	}

	mat3 rotate(float angle) {
		float aux = angle*PI / 180;
		mat3 matr;
		for (int i = 0; i < 9; i++) {
			matr.matrixData[i] = 0;
		}
		matr.matrixData[0] = cos(aux);
		matr.matrixData[1] = sin(aux);
		matr.matrixData[3] = -1 * sin(aux);
		matr.matrixData[4] = cos(aux);
		matr.matrixData[8] = 1;
		return matr;
	}


	mat4 translate(const vec3 translateArray) {
		mat4 matr;
		for (int i = 0; i < 16; i++) {
			if (i % 5 == 0) {
				matr.matrixData[i] = 1;
			}
			else {
				matr.matrixData[i] = 0;
			}
		}
		matr.matrixData[12] = translateArray.x;
		matr.matrixData[13] = translateArray.y;
		matr.matrixData[14] = translateArray.z;
		return matr;
	}

	mat4 translate(float tx, float ty, float tz) {
		mat4 matr;
		for (int i = 0; i < 16; i++) {
			if (i % 5 == 0) {
				matr.matrixData[i] = 1;
			}
			else {
				matr.matrixData[i] = 0;
			}
		}
		matr.matrixData[12] = tx;
		matr.matrixData[13] = ty;
		matr.matrixData[14] = tz;
		return matr;
	}

	mat4 scale(const vec3 scaleArray) {
		mat4 matr;
		for (int i = 0; i < 15; i++) {
				matr.matrixData[i] = 0;
		
		}
		matr.matrixData[15] = 1;
		matr.matrixData[0] = scaleArray.x;
		matr.matrixData[5] = scaleArray.y;
		matr.matrixData[10] = scaleArray.z;
		return matr;

	}

	mat4 scale(float sx, float sy, float sz) {
		mat4 matr;
		for (int i = 1; i < 15; i++) {
			matr.matrixData[i] = 0;

		}
		matr.matrixData[15] = 1;
		matr.matrixData[0] = sx;
		matr.matrixData[5] = sy;
		matr.matrixData[10] = sz;
		return matr;
	}

	mat4 rotateX(float angle) {
		mat4 matr;
		float aux = angle*PI / 180;
		for (int i = 1; i < 15; i++) {
			matr.matrixData[i] = 0;

		}
		matr.matrixData[0] = 1;
		matr.matrixData[15] = 1;
		matr.matrixData[5] = cos(aux);
		matr.matrixData[6] = sin(aux);
		matr.matrixData[9] = -1 * sin(aux);
		matr.matrixData[10] = cos(aux);
		return matr;
	}

	mat4 rotateY(float angle) {
		mat4 matr;
		float aux = angle*PI / 180;
		for (int i = 0; i < 16; i++) {
			matr.matrixData[i] = 0;

		}
		matr.matrixData[5] = 1;
		matr.matrixData[15] = 1;
		matr.matrixData[0] = cos(aux);
		matr.matrixData[8] = sin(aux);
		matr.matrixData[2] = -1 * sin(aux);
		matr.matrixData[10] = cos(aux);
		return matr;
	
	}
	mat4 rotateZ(float angle) {
		mat4 matr;
		float aux = angle*PI / 180;
		for (int i = 0; i < 16; i++) {
			matr.matrixData[i] = 0;

		}
		matr.matrixData[10] = 1;
		matr.matrixData[15] = 1;
		matr.matrixData[0] = cos(aux);
		matr.matrixData[1] = sin(aux);
		matr.matrixData[4] = -1 * sin(aux);
		matr.matrixData[5] = cos(aux);
		return matr;

	}
}