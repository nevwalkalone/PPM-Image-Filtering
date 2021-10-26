#pragma once
#include "Filter.h"
#include "vec3.h"
#include <math.h>

class FilterGamma :public Filter {
private:
	
	float g;
	
public:
	//FilterGamma default constructor
	FilterGamma() :Filter() {}
	Image operator <<(const Image& image) {
	
		Image filter = image;
		
		vector<Color>* v = (vector<Color>*)filter.getRawDataPtr();
		
		for (int i = 0; i < v->size(); i++) {
			v->at(i).x = pow(v->at(i).x, g);
			v->at(i).y = pow(v->at(i).y, g);
			v->at(i).z = pow(v->at(i).z, g);
			

		}
		
		return filter;
	}
	float getG() {
		return g;
	}
	void setG(const float& value) {
		g = value;
	}

};