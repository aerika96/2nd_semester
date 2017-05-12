#include "vec4.h"

namespace egc {

    vec4& vec4::operator =(const vec4 &srcVector){
		this->x = srcVector.x;
		this->y = srcVector.y;
		this->z = srcVector.z;
		this->w = srcVector.w;
		return *this;
	}
	vec4 vec4::operator +(const vec4& srcVector) const {
		vec4 vec;
		vec.x = this->x + srcVector.x;
		vec.y = this->y + srcVector.y;
		vec.z = this->z + srcVector.z;
		vec.w = this->w + srcVector.w;
		return vec;
	}
	vec4& vec4::operator +=(const vec4& srcVector) {
		this->x += srcVector.x;
		this->y += srcVector.y;
		this->z += srcVector.z;
		this->w += srcVector.w;
		return *this;
	}

    vec4 vec4::operator *(float scalarValue) const{
		vec4 vec;
		vec.x = this->x * scalarValue;
		vec.y = this->y * scalarValue;
		vec.z = this->z * scalarValue;
		vec.w = this->w * scalarValue;
		return vec;
	}

    vec4 vec4::operator -(const vec4& srcVector) const{
		vec4 vec;
		vec.x = this->x - srcVector.x;
		vec.y = this->y - srcVector.y;
		vec.z = this->z - srcVector.z;
		vec.w = this->w - srcVector.w;
		return vec;

	}

    vec4& vec4::operator -=(const vec4& srcVector){
		this->x -= srcVector.x;
		this->y -= srcVector.y;
		this->z -= srcVector.z;
		this->w -= srcVector.w;
		return *this;
	}

    vec4& vec4::operator -(){
		this->x = -this->x;
		this->y = -this->y;
		this->z = -this->z;
		this->w = -this->w;
		return *this;
	}

    float vec4::length() const{
		return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2) + pow(this->w, 2));
	}

    vec4& vec4::normalize(){
		float vec_length = this->length();
		this->x /= vec_length;
		this->y /= vec_length;
		this->z /= vec_length;
		this->w /= vec_length;
		return *this;
	}
}
