#pragma once
#include "Image.h"
using namespace image;



virtual class Filter {
protected:
	Filter() {
		
	}
public:
	virtual Image operator <<(const Image& image) = 0;

};