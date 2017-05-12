#include<C:\Users\AErika\Documents\2nd\2nd_sem\ECG\lab_work\lab3\matOp\matOp\vec4.h>

namespace egc {


	vec4& vec4::operator=(const vec4& srcVector) {  // :: apartine clasei
		this->x = srcVector.x;
		this->y = srcVector.y;
		this->z = srcVector.z;
		this->w = srcVector.w;
		return *this;
	}

	vec4 vec4::operator+(const vec4 &srcVector)const {
		vec4 vec;
		vec.x = this->x + srcVector.x;
		vec.y = this->y + srcVector.y;
		vec.z = this->z + srcVector.z;
		vec.w = this->w + srcVector.w;
		return vec;
	}

	vec4 vec4::operator-(const vec4 &srcVector)const {
		vec4 vec;
		vec.x = this->x - srcVector.x;
		vec.y = this->y - srcVector.y;
		vec.z = this->z - srcVector.z;
		vec.w = this->w - srcVector.w;
		return vec;
	}

	vec4 vec4::operator*(float scalarValue)const {
		vec4 vec;
		vec.x = this->x * scalarValue;
		vec.y = this->y* scalarValue;
		vec.z = this->z*scalarValue;
		vec.w = this->w*scalarValue;
		return vec;
	}

	vec4& vec4::operator+=(const vec4 & srcVector) {
		this->x += srcVector.x;
		this->y += srcVector.y;
		this->z += srcVector.z;
		this->w += srcVector.w;
		return *this;
	}

	vec4& vec4::operator-=(const vec4 &srcVector) {
		this->x -= srcVector.x;
		this->y -= srcVector.y;
		this->z -= srcVector.z;
		this->w -= srcVector.w;
		return *this;
	}

	vec4& vec4::operator-() {
		this->x = -1 * (this->x);
		this->y = -1 * (this->y);
		this->z = -1 * (this->z);
		this->w = -1 * (this->w);
		return *this;
	}

	float vec4::length() const {
		return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2)+pow(this->w,2));

	}

	vec4&  vec4::normalize() {
		float v_length = this->length();
		this->x = this->x / v_length;
		this->y = this->y / v_length;
		this->z = this->z / v_length;
		this->w = this->w / v_length;
		return *this;
	}

	/*float dotProduct(const vec4& v1, const vec4& v2) {
		float result = v1.x*v2.x + v2.y*v1.y + v2.z*v1.z+v2.w*v1.w;
		return result;

	}*/

	


}