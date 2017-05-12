/*
	Author: David
*/

#include "mat3.h"


namespace egc {
	mat3& mat3::operator =(const mat3& srcMatrix) {
		for (int i = 0; i < 9; i++) {
			this->matrixData[i] = srcMatrix.matrixData[i];
		}
		return *this;
	}

	mat3 mat3::operator *(float scalarValue) const {
		mat3 mat;

		for (int i = 0; i < 9; i++) {
			mat.matrixData[i] = this->matrixData[i] * scalarValue;
		}
		return mat;
	}
	mat3 mat3::operator +(const mat3& srcMatrix) const {
		mat3 mat;

		for (int i = 0; i < 9; i++) {
			mat.matrixData[i] = this->matrixData[i] + srcMatrix.matrixData[i];
		}

		return mat;
	}
	float& mat3::at(int i, int j) {
		return this->matrixData[i + 3*j];
	}

	const float& mat3::at(int i, int j) const {
		return this->matrixData[i + 3*j];
	}
	mat3 mat3::operator *(const mat3& srcMatrix) const {
		mat3 mat;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				mat.at(i, j) = 0;
				for (int k = 0; k < 3; k++) {
					mat.at(i, j) += this->at(i, k) * srcMatrix.at(k, j);
				}
			}
		}

		return mat;
	}
	vec3 mat3::operator *(const vec3& srcVector) const {
		vec3 vec;
		vec.x = this->at(0, 0) * srcVector.x + this->at(0, 1) * srcVector.y + this->at(0, 2) * srcVector.z;
		vec.y = this->at(1, 0) * srcVector.x + this->at(1, 1) * srcVector.y + this->at(1, 2) * srcVector.z;
		vec.z = this->at(2, 0) * srcVector.x + this->at(2, 1) * srcVector.y + this->at(2, 2) * srcVector.z;

		return vec;
	}

	float mat3::partDeterminant(int row, int col) const{
		float aux[4];
		int k = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (row != i && col != j) {
					aux[k] = this->at(i, j);
					k++;
				}
			}
		}
		return aux[0] * aux[3] - aux[1] * aux[2];
	}

	float inline getSign(int i, int j) {
		return ((i + j) % 2) ? -1.0f : 1.0f;
	}

	float mat3::determinant() const {
		float det = 0;
		for (int i = 0; i < 3; i++) {
			det +=  getSign(0, i) * this->at(0, i) * this->partDeterminant(0, i);
		}

		return det;
	}

	mat3 mat3::inverse() const {
		mat3 mat;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				mat.at(j, i) = getSign(i, j) * this->partDeterminant(i, j);
			}
		}
		float determinant = this->determinant();
		mat = mat * (1 / determinant);

		return mat;
	}
	mat3 mat3::transpose() const {
		mat3 mat;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				mat.at(i, j) = this->at(j, i);
			}
		}

		return mat;
	}
}