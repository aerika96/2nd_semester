#pragma once
#include "vec3.h"
#include "clip.h"
#include <vector>

namespace egc {

	vec3 calculateNorm(vec3 p1, vec3 p2) {
		vec3 result;
		float dx = p2.x - p2.x;
		float dy = p2.y - p1.y;
		result = vec3(dx, dy, 0);
		result.normalize();
		return result;
	}

	std::vector<vec3> calculateAllNorms(std::vector<vec3> pointarray) {
		std::vector<vec3>result;
		for (int i = 1; i < pointarray.size(); i++) {
			result[i-1] = calculateNorm(pointarray[i - 1], pointarray[i]);
		}
		result[pointarray.size() - 1] = calculateNorm(pointarray[pointarray.size() - 1], pointarray[0]);
		return result;
	}
	std::vector<vec3> pEipoints(std::vector<vec3> pointarray) {
		std::vector<vec3> result;
		for (int i = 0; i < pointarray.size(); i++) {
			result[i] = pointarray[i];
		}
		return result;
	}

	int checkIfInside(std::vector<vec3> clipWindow, vec3 p) {
		std:: vector<vec3> norms = calculateAllNorms(clipWindow);
		for (int i = 0; i < norms.size(); i++) {
			vec3 D= 
			if (dotProduct(norms[i],p-clipWindow[i]) > 0) {

				return 0;
			}
		}
		return 1;
	}

	int lineClip_CyrusBeck(std::vector<vec3> clipWindow, vec3& p1, vec3& p2) {
		std::vector<vec3> norms = calculateAllNorms(clipWindow);
		float t;
		vec3 D = p2 - p1;
		vec3 D;
		if (p1.x == p2.x && p1.y == p2.y && p1.z == p2.z) {
			if (checkIfInside(clipWindow, p1) == 0) {
				return -1;
			}
			return 1;
		}
		else {
			float tE, tL;
			tE = 0;
			tL = 0;
			for (int i = 0; i < norms.size(); i++) {
				if (i != 0) {
					if (dotProduct(norms[i], D) != 0) {
						t=
					}
				}
				
			}
			

		}
	}

}