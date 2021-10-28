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
		//Image defaultconstructor calling Array constructor
		Image() :Array2D(0, 0, 0) {}
		
		//Image constructor calling Array constructor
		Image(unsigned int width, unsigned int height, const Color* data_ptr) :Array2D(width, height,data_ptr) {}
			
		//Image copy constructor calling Array2D Copy Constructor
		Image(const Image& src) :Array2D(src) {}
		
		//Array2D copy constructor called directly
		
		/*!
		 * Loads the image data from the specified file, if the extension of the filename matches the format string.
		 *
		 * Only the "ppm" extension is supported for now. The extension comparison should be case-insensitive.
		 *
		 * \param filename is the string of the file to read the array data from.
		 * \param format specifies the file format according to which the array data should be decoded from the file.
		 * Only the "ppm" format is a valid format string for now.
		 *
		 * \return true if the loading completes successfully, false otherwise.
		 */
		bool load(const string& filename, const string& format) {
			
			if (format != "ppm") {
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
			//storing image data to the buffer
			for (int i = 0; i < 3 * width * height; i += 3) {
				Color v(*(array + i), *(array + i + 1), *(array + i + 2));
				buffer.push_back(v);
			}

			// deleting the object that was dynamically created in ReadPPM
			delete[] array;
			return true;
		}
		
		/*!
		* Stores the image data to the specified file, if the extension of the filename matches the format string.
		*
		* Only the "ppm" extension is supported for now. The extension comparison should be case-insensitive.
		*
		* \param filename is the string of the file to write the array data to.
		* \param format specifies the file format according to which the array data should be encoded to the file.
		* Only the "ppm" format is a valid format string for now.
		*
		* \return true if the save operation completes successfully, false otherwise.
		*/
		bool save(const string& filename, const string& format) {
			//only ppm format allowed
			if (format != "ppm") {
				cerr << "File format to be written must be ppm." << endl;
				return false;
			}
			//creating the data array for ReadPPM
			float* data =new float[3 * width * height];
			for (int i = 0; i < buffer.size(); i++) {
				data[3 * i] = buffer.at(i).x;
				data[3 * i + 1] = buffer.at(i).y;
				data[3 * i + 2] = buffer.at(i).z;
			}
			//making the string filename to char for ReadPPM
			char filename2[50];
			strcpy_s(filename2, filename.c_str());
			bool state= WritePPM(data, width, height, filename2);
			delete[] data;
			return state;
		}
	};
}