#include <algorithm>
#include <iostream>
#include "vec4.h"
#include "mat4.h"
#include "mat3.h"


namespace egc {

	mat4& mat4:: operator =(const mat4& srcMatrix) {
		for (int i = 0; i <16 ; i++) {
			this->matrixData[i] = srcMatrix.matrixData[i];
		}

		return *this;

	}

	mat4 mat4:: operator *(float scalarValue)const {
		mat4 matrix;
		for (int i = 0; i < 16; i++) {
			matrix.matrixData[i] = this->matrixData[i] * scalarValue;
		}
		return matrix;
	}

	mat4 mat4:: operator *(const mat4& srcMatrix)const {
		mat4 matrix;
		for (int i = 0;i < 4; i++) {
			for (int j = 0;j < 4; j++) {
				matrix.matrixData[j * 4 + i] = 0;
				for (int k = 0; k < 4; k++) {
					matrix.matrixData[j * 4 + i] += this->matrixData[k * 4 + i] * srcMatrix.matrixData[j * 4 + k];
				}
			}
		}
		return matrix;
	}

	vec4 mat4 :: operator*(const vec4& srcVector)const {

		vec4 v;
		v.x = srcVector.x*matrixData[0] + srcVector.y*matrixData[4] + srcVector.z*matrixData[8]+ srcVector.w *matrixData[12];
		v.y = srcVector.x*matrixData[1] + srcVector.y*matrixData[5] + srcVector.z*matrixData[9] + srcVector.w *matrixData[13];
		v.z = srcVector.x*matrixData[2] + srcVector.y*matrixData[6] + srcVector.z*matrixData[10] + srcVector.w *matrixData[14];
		v.w = srcVector.x*matrixData[3] + srcVector.y*matrixData[7] + srcVector.z*matrixData[11] + srcVector.w *matrixData[15];
		return v;

	}
	mat4 mat4 :: operator+(const mat4& srcMatrix)const {
		mat4 matrix;
		for (int i = 0; i < 16; i++) {
			matrix.matrixData[i] = this->matrixData[i] + srcMatrix.matrixData[i];
		}
		return matrix;
	}

	float& mat4::at(int i, int j) {

		for (int l = 0; l < 16; l++) {
			if (l % 4 == i && l / 4 == j) {
				return this->matrixData[l];
			}
		}
	}

	const float& mat4::at(int i, int j)const {


		for (int l = 0; l < 16; l++) {
			if (l % 4 == i && l / 4 == j) {
				return this->matrixData[l];
			}
		}
	}

	float mat4::determinant()const {
		float m0[] = { matrixData[5], matrixData[6], matrixData[7],
			matrixData[9], matrixData[10], matrixData[11],
			matrixData[13], matrixData[14], matrixData[15] };
		float m1[] = { matrixData[1], matrixData[2], matrixData[3],
			matrixData[9], matrixData[10], matrixData[11],
			matrixData[13], matrixData[14], matrixData[15] };
		float m2[] = { matrixData[1], matrixData[2], matrixData[3],
			matrixData[5], matrixData[6], matrixData[7],
			matrixData[13], matrixData[14], matrixData[15] };
		float m3[] = { matrixData[1], matrixData[2], matrixData[3],
			matrixData[5], matrixData[6], matrixData[7],
			matrixData[9], matrixData[10], matrixData[11] };
		mat3 minor0(m0), minor1(m1), minor2(m2), minor3(m3);

		return	matrixData[0] * minor0.determinant() -
			matrixData[4] * minor1.determinant() +
			matrixData[8] * minor2.determinant() -
			matrixData[12] * minor3.determinant();


	}
	mat4 mat4::inverse() const {
		float m0[] = { matrixData[5], matrixData[6], matrixData[7],
			matrixData[9], matrixData[10], matrixData[11],
			matrixData[13], matrixData[14], matrixData[15] };
		float m4[] = { matrixData[1], matrixData[2], matrixData[3],
			matrixData[9], matrixData[10], matrixData[11],
			matrixData[13], matrixData[14], matrixData[15] };
		float m8[] = { matrixData[1], matrixData[2], matrixData[3],
			matrixData[5], matrixData[6], matrixData[7],
			matrixData[13], matrixData[14], matrixData[15] };
		float m12[] = { matrixData[1], matrixData[2], matrixData[3],
			matrixData[5], matrixData[6], matrixData[7],
			matrixData[9], matrixData[10], matrixData[11] };

		float m1[] = { matrixData[4], matrixData[6], matrixData[7],
			matrixData[8], matrixData[10], matrixData[11],
			matrixData[12], matrixData[14], matrixData[15] };
		float m5[] = { matrixData[0], matrixData[2], matrixData[3],
			matrixData[8], matrixData[10], matrixData[11],
			matrixData[12], matrixData[14], matrixData[15] };
		float m9[] = { matrixData[0], matrixData[2], matrixData[3],
			matrixData[4], matrixData[6], matrixData[7],
			matrixData[12], matrixData[14], matrixData[15] };
		float m13[] = { matrixData[0], matrixData[2], matrixData[3],
			matrixData[4], matrixData[6], matrixData[7],
			matrixData[8], matrixData[10], matrixData[11] };

		float m2[] = { matrixData[4], matrixData[5], matrixData[7],
			matrixData[8], matrixData[9], matrixData[11],
			matrixData[12], matrixData[13], matrixData[15] };
		float m6[] = { matrixData[0], matrixData[1], matrixData[3],
			matrixData[8], matrixData[9], matrixData[11],
			matrixData[12], matrixData[13], matrixData[15] };
		float m10[] = { matrixData[0], matrixData[1], matrixData[3],
			matrixData[4], matrixData[5], matrixData[7],
			matrixData[12], matrixData[13], matrixData[15] };
		float m14[] = { matrixData[0], matrixData[1], matrixData[3],
			matrixData[4], matrixData[5], matrixData[7],
			matrixData[8], matrixData[9], matrixData[11] };

		float m3[] = { matrixData[4], matrixData[5], matrixData[6],
			matrixData[8], matrixData[9], matrixData[10],
			matrixData[12], matrixData[13], matrixData[14] };
		float m7[] = { matrixData[0], matrixData[1], matrixData[2],
			matrixData[8], matrixData[9], matrixData[10],
			matrixData[12], matrixData[13], matrixData[14] };
		float m11[] = { matrixData[0], matrixData[1], matrixData[2],
			matrixData[4], matrixData[5], matrixData[6],
			matrixData[12], matrixData[13], matrixData[14] };
		float m15[] = { matrixData[0], matrixData[1], matrixData[2],
			matrixData[4], matrixData[5], matrixData[6],
			matrixData[8], matrixData[9], matrixData[10] };

		mat3 min0(m0), min4(m4), min8(m8), min12(m12),
			min1(m1), min5(m5), min9(m9), min13(m13),
			min2(m2), min6(m6), min10(m10), min14(m14),
			min3(m3), min7(m7), min11(m11), min15(m15);
		float c[] = { min0.determinant(), -min4.determinant(), min8.determinant(), -min12.determinant(),
			-min1.determinant(), min5.determinant(), -min9.determinant(), min13.determinant(),
			min2.determinant(), -min6.determinant(), min10.determinant(), -min14.determinant(),
			-min3.determinant(), min7.determinant(), -min11.determinant(), min15.determinant() };

		float invdet = 1.0 / determinant();

		int i;
		for (i = 0; i < 16; i++)
			c[i] = c[i] * invdet;

		mat4 m(c);
		return m;
	}
	mat4 mat4::transpose() const {
		mat4 matrix;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				matrix.matrixData[4 * j + i] = this->matrixData[j + 4 * i];
			}
		}
		return matrix;
	}



}

