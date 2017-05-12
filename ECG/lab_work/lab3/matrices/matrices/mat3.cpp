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

		vec3 v;
		v.x = srcVector.x*matrixData[0] + srcVector.y*matrixData[3] + srcVector.z*matrixData[6];
		v.y = srcVector.x*matrixData[1] + srcVector.y*matrixData[4] + srcVector.z*matrixData[7];
		v.z = srcVector.x*matrixData[2] + srcVector.y*matrixData[5] + srcVector.z*matrixData[8];
		return v;

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
		mat3 inv, adj, t;
		float invdet = 1 / determinant();
		inv.matrixData[0] = (at(1, 1)*at(2, 2) - at(2, 1)*at(1, 2))*invdet;
		inv.matrixData[1] = -(at(0, 1)*at(2, 2) - at(0, 2)*at(2, 1))*invdet;
		inv.matrixData[2] = (at(0, 1)*at(1, 2) - at(0, 2)*at(1, 1))*invdet;
		inv.matrixData[3] = -(at(1, 0)*at(2, 2) - at(1, 2)*at(2, 0))*invdet;
		inv.matrixData[4] = (at(0, 0)*at(2, 2) - at(0, 2)*at(2, 0))*invdet;
		inv.matrixData[5] = -(at(0, 0)*at(1, 2) - at(1, 0)*at(0, 2))*invdet;
		inv.matrixData[6] = (at(1, 0)*at(2, 1) - at(2, 0)*at(1, 1))*invdet;
		inv.matrixData[7] = -(at(0, 0)*at(2, 1) - at(2, 0)*at(0, 1))*invdet;
		inv.matrixData[8] = (at(0, 0)*at(1, 1) - at(1, 0)*at(0, 1))*invdet;
		inv = inv.transpose();
		return inv;

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