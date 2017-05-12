#pragma once
#include <iostream>
#include <vector>
#include "include\SDL.h"
#include "vec3.h"
#include "clip.h"
#include <algorithm>

namespace egc {

	vec3 calculateNorm(vec3 p1, vec3 p2) {
		vec3 result;
		float dx = p2.x - p1.x;
		float dy = p2.y - p1.y;
		result = vec3(-dy, dx, 0);
		result.normalize();
		return result;
	}

	std::vector<vec3> calculateAllNorms(std::vector<vec3> pointarray) {
		std::vector<vec3>result;
		for (int i = 0; i < pointarray.size(); i++) {
			egc::vec3 begp = pointarray[i];
			egc::vec3 endp = pointarray[(i + 1) % pointarray.size()];
			egc::vec3 norm = calculateNorm(begp, endp);
			result.push_back(norm);
		}
		return result;
	}
	

	int checkIfInside(std::vector<vec3> clipWindow, vec3 p) {
		std:: vector<vec3> norms = calculateAllNorms(clipWindow);
		for (int i = 0; i < norms.size(); i++) {
			if (dotProduct(norms[i],p-clipWindow[i]) > 0) {

				return 0;
			}
		}
		return 1;
	}

	int lineClip_CyrusBeck(std::vector<vec3> clipWindow, vec3& p1, vec3& p2) {
		
		if (p1 == p2) {
			if (checkIfInside(clipWindow,p1) == 1) {
				return 0;
			}
			return -1;
		}

		else {
			std::vector<egc::vec3>norms = calculateAllNorms(clipWindow);
			float tE = 0;
			float tL = 1;
			float t;

			for (int i = 0; i < norms.size(); i++) {
				vec3 D = p2 - p1;
				float dotProd = dotProduct(norms[i], D);
				if (dotProd == 0) {
					return -1;
				}
				else {
					t = -dotProduct(norms[i],p1-clipWindow[i]) / dotProd;
				}
				if (dotProd > 0) {
					tL = std::min(tL, t);
				}
				else
					tE = std::max(tE, t);

			}
			if (tE > tL) {
				return -1;
			}
			else {
				vec3 newP1 = p2*tE + p1*(1 - tE);
				vec3 newP2 = p2*tL + p1*(1 - tL);
				p1 = newP1;
				p2 = newP2;
				return 0;
			}
		}
	}


	std::vector<int> computeCSCode(std::vector<vec3> clipWindow, const vec3 p) {
		std::vector <int> result;
		result.reserve(4);
		if (p.y < clipWindow[0].y) {
			result.push_back(1);
		}
		else result.push_back(0);
		if (p.y > clipWindow[1].y) {
			result.push_back(1);
		}
		else result.push_back(0);
		if (p.x > clipWindow[2].x) {
			result.push_back(1);
		}
		else result.push_back(0);
		if (p.x < clipWindow[0].x) {
			result.push_back(1);
		}
		else result.push_back(0);

		return result;
	}

	bool insideClippingWindow(std::vector<int> cod) {
		for (int i = 0; i < cod.size(); i++) {
			if (cod[i] == 1) {
				return false;
			}
		}
		return true;
	}

	bool simpleRejection(std::vector<int> cod1, std::vector<int> cod2) {
		for (int i = 0; i < cod1.size(); i++) {
			if (cod1[i] == 1 && cod2[i] == 1) {
				return true;
			}
		}
		return false;
	}


	bool simpleAcceptance(std::vector<int> cod1, std::vector<int> cod2) {
		for (int i = 0; i < cod1.size(); i++) {
			if (cod1[1] == 1 || cod2[i] == 1) {
				return false;
			}
		}
		return true;
	}

	int lineClip_CohenSutherland(std::vector<vec3> clipWindow, vec3& p1, vec3& p2) {
		
		while (true) {
			std::vector<int>code1 = computeCSCode(clipWindow,p1);
			std::vector<int>code2 = computeCSCode(clipWindow, p2);
			if (simpleRejection(code1, code2)) {
				return -1;

			}
			else if (simpleAcceptance(code1, code2)) {
					return 0;
				}
			if (insideClippingWindow(code1)) {
				std::vector<int>aux = code1;
				code1 = code2;
				code2 = aux;

				vec3 point = p1;
				p1 = p2;
				p2 = point;

			}
			if (code1[0] == 1 && p2.y != p1.y) {
				p1.x = p1.x + (p2.x - p1.x)*(clipWindow[0].y - p1.y) / (p2.y - p1.y);
				p1.y = clipWindow[0].y;
			}
			if (code1[1] == 1 && p2.y != p1.y) {
				p1.x = p1.x + (p2.x - p1.x)*(clipWindow[1].y - p1.y) / (p2.y - p1.y);
				p1.y = clipWindow[1].y;
			}
			if (code1[2] == 1 && p2.x != p1.x) {
				p1.y = p1.y + (p2.y - p1.y)*(clipWindow[2].x - p1.x) / (p2.x - p1.x);
				p1.x = clipWindow[2].x;
			}
			if (code1[3] == 1 && p2.x != p1.x) {
				p1.y = p1.y + (p2.y - p1.y)*(clipWindow[0].x - p1.x) / (p2.x - p1.x);
				p1.x = clipWindow[0].x;
			}


		}
	}
}