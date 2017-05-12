#include <algorithm>
#include <iostream>
#include "vec3.h"
#include "mat3.h"

namespace egc {

	mat3& mat3:: operator =(const mat3& srcMatrix) {
		for (int i = 0; i < 9; i++) {
			this->matrixData[i] = srcMatrix.matrixData[i];
		}

		return *this;

	}

	mat3 mat3:: operator *(float scalarValue)const {
		mat3 matrix;
		for (int i = 0; i < 9; i++) {
			matrix.matrixData[i] = this->matrixData[i] * scalarValue;
		}
		return matrix;
	}

	mat3 mat3:: operator *(const mat3& srcMatrix)const {
		mat3 matrix;
		for (int i = 0;i < 3; i++) {
			for (int j = 0;j < 3; j++) {
				matrix.matrixData[j * 3 + i] = 0;
				for (int k = 0; k < 3; k++) {
					matrix.matrixData[j * 3 + i] += this->matrixData[k * 3 + i] * srcMatrix.matrixData[j * 3 + k];
				}
			}
		}
		return matrix;
	}

	vec3 mat3 :: operator*(const vec3& srcVector)const {
		vec3 vector;
		for (int i = 0; i < 3; i++) {
			vector.x = 0;
			vector.y = 0;
			vector.z = 0;
		}
		for (int j = 0; j < 9; j++) {
				if (j % 3 == 0) {
					if (j / 3 == 0) vector.x = vector.x + this->matrixData[j] * srcVector.x;
					if (j / 3 == 1) vector.x = vector.x + this->matrixData[j] * srcVector.y;
					else vector.x = vector.x + this->matrixData[j] * srcVector.z;
				}
				else if (j % 3 == 1) {
					if (j / 3 == 0) vector.y = vector.y + this->matrixData[j] * srcVector.x;
					if (j / 3 == 1) vector.y = vector.y + this->matrixData[j] * srcVector.y;
					else vector.z = vector.z + this->matrixData[j] * srcVector.z;
				}
				else {
					if (j / 3 == 0) vector.z = vector.z + this->matrixData[j] * srcVector.x;
					if (j / 3 == 1) vector.z = vector.z + this->matrixData[j] * srcVector.y;
					else vector.z = vector.z + this->matrixData[j] * srcVector.z;
				}
		}
		return vector;

	}
	mat3 mat3 :: operator+(const mat3& srcMatrix)const {
		mat3 matrix;
		for (int i = 0; i < 9; i++) {
			matrix.matrixData[i] = this->matrixData[i] + srcMatrix.matrixData[i];
		}
		return matrix;
	}

	float& mat3::at(int i, int j) {

			for (int l = 0; l < 9; l++) {
				if (l % 3 == i && l / 3 == j ) {
					return this->matrixData[l];
				}
			}
	}

	const float& mat3::at(int i, int j)const {


		for (int l = 0; l < 9; l++) {
			if (l % 3 == i && l / 3 == j) {
				return this->matrixData[l];
			}
		}
	}

	float mat3::determinant()const {
		return matrixData[0] * matrixData[4] * matrixData[8]
			+ matrixData[1] * matrixData[5] * matrixData[6]
			+ matrixData[2] * matrixData[3] * matrixData[7]
			- matrixData[6] * matrixData[4] * matrixData[2]
			- matrixData[7] * matrixData[5] * matrixData[0]
			- matrixData[8] * matrixData[3] * matrixData[1];
	}
	mat3 mat3::inverse() const {
		mat3 matrix;
		float invDet = 1 / this->determinant();
		matrix = this->transpose();
		matrix.matrixData[0] = matrix.matrixData[4] * matrix.matrixData[8] - matrix.matrixData[5] * matrix.matrixData[7];
		matrix.matrixData[3] = -1 * (matrix.matrixData[1] * matrix.matrixData[8] - matrix.matrixData[2] * matrix.matrixData[7]);
		matrix.matrixData[6]=matrix. matrixData[1] * matrix.matrixData[5] - matrix.matrixData[2] * matrix.matrixData[4];
		matrix.matrixData[1] = -1*(matrix.matrixData[3] * matrix.matrixData[8] - matrix.matrixData[5] * matrix.matrixData[6]);
		matrix.matrixData[4] = matrix.matrixData[0] * matrix.matrixData[8] - matrix.matrixData[2] * matrix.matrixData[6];
		matrix.matrixData[7] = -1*(matrix.matrixData[0] * matrix.matrixData[5] - matrix.matrixData[2] * matrix.matrixData[3]);
		matrix.matrixData[2] = matrix.matrixData[3] * matrix.matrixData[7] - matrix.matrixData[4] * matrix.matrixData[6];
		matrix.matrixData[5] =-1*( matrix.matrixData[0] * matrix.matrixData[7] - matrix.matrixData[1] * matrix.matrixData[6]);
		matrix.matrixData[8] = matrix.matrixData[0] * matrix.matrixData[4] - matrix.matrixData[1] * matrix.matrixData[3];
		matrix=matrix.operator*(invDet);
		return matrix;

	}
	mat3 mat3::transpose() const {
		mat3 matrix;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				matrix.matrixData[3*j+i] = this->matrixData[j+3*i];
			}
		}
		return matrix;
	}



}