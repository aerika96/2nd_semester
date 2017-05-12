#include"vec3.h"

namespace egc {


	vec3& vec3::operator=(const vec3& srcVector) {  // :: apartine clasei
		this->x = srcVector.x;
		this->y = srcVector.y;
		this->z = srcVector.z;
		return *this;
	}

	vec3 vec3::operator+(const vec3 &srcVector)const {
		vec3 vec;
		vec.x = this->x + srcVector.x;
		vec.y = this->y + srcVector.y;
		vec.z = this->z + srcVector.z;
		return vec;
	}

	vec3 vec3::operator-(const vec3 &srcVector)const {
		vec3 vec;
		vec.x = this->x - srcVector.x;
		vec.y = this->y - srcVector.y;
		vec.z = this->z - srcVector.z;
		return vec;
	}

	vec3 vec3::operator*(float scalarValue)const {
		vec3 vec;
		vec.x = this->x * scalarValue;
		vec.y = this->y* scalarValue;
		vec.z = this->z*scalarValue;
		return vec;
	}

	vec3& vec3::operator+=(const vec3 & srcVector) {
		this->x += srcVector.x;
		this->y += srcVector.y;
		this->z += srcVector.z;
		return *this;
	}

	vec3& vec3::operator-=(const vec3 &srcVector) {
		this->x -= srcVector.x;
		this->y -= srcVector.y;
		this->z -= srcVector.z;
		return *this;
	}

	vec3& vec3::operator-() {
		this->x = -1 * (this->x);
		this->y = -1 * (this->y);
		this->z = -1 * (this->z);
		return *this;
	}

	float vec3::length() const {
		return sqrt(pow(this->x, 2) + pow(this->y, 2)+ pow(this->z,2));

	}

	vec3&  vec3::normalize() {
		float v_length = this->length();
		this->x = this->x / v_length;
		this->y = this->y / v_length;
		this->z = this->z / v_length;
		return *this;
	}

	float dotProduct(const vec3& v1, const vec3& v2) {
		float result = v1.x*v2.x + v2.y*v1.y+ v2.z*v1.z;
		return result;

	}

	vec3 crossProduct(const vec3& v1, const vec3& v2) {
		vec3 result;
		result.x = v1.y*v2.z - v1.z * v2.y;
		result.y = v1.z*v2.x - v1.x*v2.z;
		result.z = v1.x*v2.y - v1.y*v2.x;
		return result;
	}


}