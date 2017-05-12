#include "vec2.h"

namespace egc {
	

		vec2& vec2::operator=(const vec2& srcVector) {  // :: apartine clasei
			this->x = srcVector.x;
			this->y = srcVector.y;
			return *this;
		}

		vec2 vec2::operator+(const vec2 &srcVector)const {
			vec2 vec;
			vec.x = this->x + srcVector.x;
			vec.y = this->y + srcVector.y;
			return vec;
		}
	
		vec2 vec2::operator-(const vec2 &srcVector)const{
			vec2 vec;
			vec.x = this->x - srcVector.x;
			vec.y = this->y - srcVector.y;
			return vec;
		}

		vec2 vec2::operator*(float scalarValue)const {
			vec2 vec;
			vec.x = this->x * scalarValue;
			vec.y = this->y* scalarValue;
			return vec;
		}
		
		vec2& vec2::operator+=(const vec2 & srcVector) {
			this->x += srcVector.x;
			this->y += srcVector.y;
			return *this;
		}

		vec2& vec2::operator-=(const vec2 &srcVector) {
			this->x -= srcVector.x;
			this->y -= srcVector.y;
			return *this;
		}

		vec2& vec2::operator-() {
			this->x = -1 * (this->x);
			this->y = -1 * (this->y);
			return *this;
		}
		
		float vec2::length() const {
			return sqrt(pow(this->x, 2) + pow(this->y, 2));
			
		}

		vec2&  vec2::normalize() {
			float v_length = this->length();
			this->x = this->x / v_length;
			this->y = this->y / v_length;
			return *this;
		}

		float dotProduct(const vec2& v1, const vec2& v2){
			float result = v1.x*v2.x-v2.y*v1.y;
			return result;

		}
		
		
}