#pragma once
#include "array2d.h"
#include "vec3.h"
#include "imageio.h"
#include "ppm.h"
using namespace math;

typedef Vec3<float> Color;

namespace image {

	class Image : public Array2D<Color>, public ImageIO {	
	
	public:
		//Image default constructor calling Array constructor
		Image() :Array2D(0, 0, 0) {}
		
		//Image constructor calling Array constructor
		Image(unsigned int width, unsigned int height, const Color* data_ptr) :Array2D(width, height,data_ptr) {}
			
		//Image copy constructor calling Array2D Copy Constructor
		Image(const Image& src) :Array2D(src) {}
		
	
		bool load(const string& filename, const string& format) {

			// only ppm format allowed
			if (!format._Equal("ppm")) {
				cerr << "File format to be loaded must be ppm." << endl;
				return false;
			}

			float* array; 
			char filename2[50];
			strcpy_s(filename2, filename.c_str());
			array=ReadPPM(filename2, (int*)&width, (int*)&height);
			
			if (array == nullptr) {
				return false;
			}
			// storing image data to the buffer
			for (int i = 0; i < 3 * width * height; i += 3) {
				Color v(*(array + i), *(array + i + 1), *(array + i + 2));
				buffer.push_back(v);
			}

			// deleting the object that was dynamically created in ReadPPM
			delete[] array;
			return true;
		}
	
		bool save(const string& filename, const string& format) {

			// only ppm format allowed
			if (!format._Equal("ppm")) {
				cerr << "File format to be written must be ppm." << endl;
				return false;
			}
			// creating the data array for ReadPPM
			float width_to_float = static_cast<float>(width);
			float height_to_float = static_cast<float>(height);
			float size = 3 * width_to_float * height_to_float;
			float* data =new float[size];
			for (int i = 0; i < buffer.size(); i++) {
				data[3 * i] = buffer.at(i).x;
				data[3 * i + 1] = buffer.at(i).y;
				data[3 * i + 2] = buffer.at(i).z;
			}
			// converting string filename to char for ReadPPM
			char filename_to_char[50];
			strcpy_s(filename_to_char, filename.c_str());

			// WritePPM will return true if the process was
			// successful, false otherwise
			bool state= WritePPM(data, width, height, filename_to_char);

			// deleting the object that was dynamically created
			delete[] data;
			return state;
		}
	};
}