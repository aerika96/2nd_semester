#include "clip.h"
#include <algorithm>

namespace egc {

	vec3 calculateNormal(vec3 p1, vec3 p2)
	{
		float dx = p2.x - p1.x;
		float dy = p2.y - p1.y;
		vec3 vec = vec3(-dy, dx, 0);

		vec = vec.normalize();
		return vec;
	}
	std::vector<vec3> caluculateNormals(std::vector<vec3> points)
	{
		std::vector<vec3> normals;
		int size = points.size();
		for(int i = 0; i < size; i++) {
			vec3 begP = points[i];
			vec3 endP = points[(i + 1) % size];
			vec3 normal = calculateNormal(begP, endP);
			normals.push_back(normal);
		}

		return normals;
	}

	int checkPointInPolygon(std::vector<vec3> points, vec3 p)
	{
		std::vector<vec3> normals = caluculateNormals(points);
		for(int i = 0; i < normals.size(); i++) {
			float dotProd = dotProduct(normals[i], p - points[i]);
			if (dotProd > 0) {
				return 0;
			}
		}
		return 1;
	}

	int lineClip_CyrusBeck(std::vector<vec3> clipWindow, vec3& p1, vec3& p2)
	{
		if (p1 == p2) {
			if (checkPointInPolygon(clipWindow, p1) == 1) {
				return 0;
			}
			return -1;
		}
		std::vector<vec3> normals = caluculateNormals(clipWindow);
		float tE = 0;
		float tL = 1;
		float t;
		for(int i = 0; i < normals.size(); i++) {
			vec3 D = p2 - p1;
			float dotProd = egc::dotProduct(normals[i], D);
			if (dotProd != 0) {
				t = -dotProduct(normals[i], p1 - clipWindow[i]) / dotProd;
			}
			if (dotProd > 0) {
				//potentially leaving
				tL = std::min(tL, t);
			}
			else {
				//pontentially entering
				tE = std::max(tE, t);
			}
		}
		if (tE > tL) {
			//could not clip
			return -1;
		}
		//sucess, calculating new point coordinates
		vec3 newP1 = p2 * tE + p1 * (1 - tE);
		vec3 newP2 = p2 * tL + p1 * (1 - tL);
		p1 = newP1;
		p2 = newP2;
		return 0;
	}


    std::vector<int> computeCSCode(std::vector<vec3> clipWindow, const vec3 p)
	{
		std::vector<int> codes;
		codes.reserve(4);
		if (p.y < clipWindow[0].y) {
			codes.push_back(1);
		}
		else {
			codes.push_back(0);
		}

		if (p.y > clipWindow[1].y) {
			codes.push_back(1);
		}
		else {
			codes.push_back(0);
		}

		if (p.x > clipWindow[2].x) {
			codes.push_back(1);
		}
		else {
			codes.push_back(0);
		}

		if (p.x < clipWindow[0].x) {
			codes.push_back(1);
		}
		else {
			codes.push_back(0);
		}

		return codes;
	}
    bool simpleRejection(std::vector<int> cod1, std::vector<int> cod2)
	{
		for(int i = 0; i < cod1.size() && i < cod2.size(); i++) {
			if (cod1[i] == 1 && cod2[i] == 1) {
				return true;
			}
		}
		return false;
	}

	bool insideClippingWindow(std::vector<int> codes)
	{
		for(int i = 0; i < codes.size(); i++) {
			if (codes[i] != 0) {
				return false;
			}
		}
		return true;
	}

    bool simpleAcceptance(std::vector<int> cod1, std::vector<int> cod2)
	{
		return insideClippingWindow(cod1) && insideClippingWindow(cod2);
	}
    int lineClip_CohenSutherland(std::vector<vec3> clipWindow, vec3& p1, vec3& p2)
	{
		while (true) {
			std::vector<int> cod1 = computeCSCode(clipWindow, p1);
			std::vector<int> cod2 = computeCSCode(clipWindow, p2);
			bool rejected = simpleRejection(cod1, cod2);
			if (rejected) {
				return -1;
			}
			bool display = simpleAcceptance(cod1, cod2);
			if (display) {
				return 0;
			}
			if (insideClippingWindow(cod1)) {
				std::vector<int> tmp = cod1;
				cod1 = cod2;
				cod2 = tmp;

				vec3 ptmp = p1;
				p1 = p2;
				p2 = ptmp;
			}

			if (cod1[0] == 1 && p2.y != p1.y) {
				p1.x = p1.x + (p2.x - p1.x) * (clipWindow[0].y - p1.y) / (p2.y - p1.y);
				p1.y = clipWindow[0].y;
			}
			else if (cod1[1] == 1 && p2.y != p1.y){
				p1.x = p1.x + (p2.x - p1.x) * (clipWindow[1].y - p1.y) / (p2.y - p1.y);
				p1.y = clipWindow[1].y;
			}else if (cod1[2] == 1 && p2.x != p1.x) {
				p1.y = p1.y + (p2.y - p1.y) * (clipWindow[2].x - p1.x) / (p2.x - p1.x);
				p1.x = clipWindow[2].x;
			}else if (cod1[3] == 1 && p2.x != p1.x) {
				p1.y = p1.y + (p2.y - p1.y) * (clipWindow[0].x - p1.x) / (p2.x - p1.x);
				p1.x = clipWindow[0].x;
			}

		}
	}
}

