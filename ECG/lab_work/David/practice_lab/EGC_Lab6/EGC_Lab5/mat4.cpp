/*
	Author: David
*/

#include "mat4.h"
#include "mat3.h"

namespace egc {
	mat4& mat4::operator =(const mat4& srcMatrix) {
		for (int i = 0; i < 16; i++) {
			this->matrixData[i] = srcMatrix.matrixData[i];
		}

		return *this;
	}

	mat4 mat4::operator *(float scalarValue) const {
		mat4 mat;
		for (int i = 0; i < 16; i++) {
			mat.matrixData[i] = this->matrixData[i] * scalarValue;
		}

		return mat;
	}

	mat4 mat4::operator *(const mat4& srcMatrix) const {
		mat4 mat;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				mat.at(i, j) = 0;
				for (int k = 0; k < 4; k++) {
					mat.at(i, j) += this->at(i, k) * srcMatrix.at(k, j);
				}
			}
		}

		return mat;
	}

	vec4 mat4::operator *(const vec4& srcVector) const {
		vec4 vec;
		vec.x = this->at(0, 0) * srcVector.x + this->at(0, 1) * srcVector.y + this->at(0, 2) * srcVector.z + this->at(0, 3) * srcVector.w;
		vec.y = this->at(1, 0) * srcVector.x + this->at(1, 1) * srcVector.y + this->at(1, 2) * srcVector.z + this->at(1, 3) * srcVector.w;
		vec.z = this->at(2, 0) * srcVector.x + this->at(2, 1) * srcVector.y + this->at(2, 2) * srcVector.z + this->at(2, 3) * srcVector.w;
		vec.w = this->at(3, 0) * srcVector.x + this->at(3, 1) * srcVector.y + this->at(3, 2) * srcVector.z + this->at(3, 3) * srcVector.w;
		
		return vec;
	}

	mat4 mat4::operator +(const mat4& srcMatrix) const{
		mat4 mat;
		for (int i = 0; i < 16; i++) {
			mat.matrixData[i] = this->matrixData[i] + srcMatrix.matrixData[i];
		}

		return mat;
	}

	float& mat4::at(int i, int j) {
		return this->matrixData[i + 4 * j];
	}

	const float& mat4::at(int i, int j) const {
		return this->matrixData[i + 4 * j];
	}

	mat3 mat4::createPartMatrix(int row, int col) const{
		mat3 partMat;
		int k = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (row != i && col != j) {
					partMat.at(k / 3, k % 3) = this->at(i, j);
					k++;
				}
			}
		}

		return partMat;
	}

	float inline getSign(int i, int j) {
		return ((i + j) % 2) ? -1.0f : 1.0f;
	}

	float mat4::determinant() const {
		float det = 0;

		for(int i = 0; i < 4; i++) {
			det += getSign(0, i) * createPartMatrix(0, i).determinant();
		}

		return det;
	}
	mat4 mat4::inverse() const {
		mat4 mat;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				mat.at(j, i) = getSign(i, j) * createPartMatrix(i, j).determinant();
			}
		}
		float determinant = this->determinant();
		mat = mat * (1 / determinant);

		return mat;
	}

	mat4 mat4::transpose() const {
		mat4 mat;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				mat.at(i, j) = this->at(j, i);
			}
		}

		return mat;
	}
}
