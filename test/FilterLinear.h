#pragma once
#include "Filter.h"
#include "vec3.h"
#include <iostream>



class FilterLinear:public Filter {
private:
	Color a;
	Color c;
public:
	//FilterLinear default constructor
	FilterLinear() :Filter() {}
	Image operator <<(const Image& image) {
		Image filt = image;
		
		vector<Color>* v = (vector<Color>*)filt.getRawDataPtr();
		
		
		for (int i = 0; i < v->size(); i++) {
			
			v->at(i) = v->at(i)*a+c;
			v->at(i) = v->at(i).clampToLowerBound(0);
			v->at(i) = v->at(i).clampToUpperBound(1);
			
		}

		return filt;
	}

	Color getVec3a() {
		return a;
	}

	Color getVec3c() {
		return c;
	}

	void setVec3a(const float& value1, const float& value2, const float& value3) {
		a.x = value1;
		a.y = value2;
		a.z = value3;
		
	}

	void setVec3c(const float& value1, const float& value2, const float& value3) {

		c.x = value1;
		c.y = value2;
		c.z = value3;
	}
};