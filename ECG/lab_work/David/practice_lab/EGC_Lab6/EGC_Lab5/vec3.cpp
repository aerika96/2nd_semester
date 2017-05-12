#include "vec3.h"

namespace egc {

    vec3& vec3::operator =(const vec3 &srcVector){
		this->x = srcVector.x;
		this->y = srcVector.y;
		this->z = srcVector.z;
		return *this;
	}
	vec3 vec3::operator +(const vec3& srcVector) const {
		vec3 vec;
		vec.x = this->x + srcVector.x;
		vec.y = this->y + srcVector.y;
		vec.z = this->z + srcVector.z;
		return vec;
	}
	vec3& vec3::operator +=(const vec3& srcVector) {
		this->x += srcVector.x;
		this->y += srcVector.y;
		this->z += srcVector.z;
		return *this;
	}

    vec3 vec3::operator *(float scalarValue) const{
		vec3 vec;
		vec.x = this->x * scalarValue;
		vec.y = this->y * scalarValue;
		vec.z = this->z * scalarValue;
		return vec;
	}

    vec3 vec3::operator -(const vec3& srcVector) const{
		vec3 vec;
		vec.x = this->x - srcVector.x;
		vec.y = this->y - srcVector.y;
		vec.z = this->z - srcVector.z;
		return vec;

	}

    vec3& vec3::operator -=(const vec3& srcVector){
		this->x -= srcVector.x;
		this->y -= srcVector.y;
		this->z -= srcVector.z;
		return *this;
	}

    vec3& vec3::operator -(){
		this->x = -this->x;
		this->y = -this->y;
		this->z = -this->z;
		return *this;
	}

    float vec3::length() const{
		return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
	}

    vec3& vec3::normalize(){
		float vec_length = this->length();
		this->x /= vec_length;
		this->y /= vec_length;
		this->z /= vec_length;
		return *this;
	}

	float dotProduct(const vec3& v1, const vec3& v2) {
		return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
	}
	vec3 crossProduct(const vec3& v1, const vec3& v2) {
		vec3 vec;
		vec.x = v1.y*v2.z - v1.z*v2.y;
		vec.y = v1.z*v2.x - v1.x*v2.z;
		vec.z = v1.x*v2.y - v1.y*v2.x;
		return vec;
	}
}