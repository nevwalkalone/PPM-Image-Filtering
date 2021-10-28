#pragma once
#include "array2d.h"
#include <iostream>

using namespace std;

/* Implementing array2d's methods. Comments regarding each method
* can be found in array2d.h
*/

namespace math {

		template <typename T>
		const unsigned int Array2D<T>::getWidth() const {
			return width;
		}

		template <typename T>
		const unsigned int Array2D<T>::getHeight() const {
			return height;
		}

		template <typename T>
		T* Array2D<T>::getRawDataPtr() {
			return (T*)&buffer;
		}

		template <typename T>
		void Array2D<T>::setData(const T* const& data_ptr) {
			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++) {
					buffer.push_back(data_ptr[i * width + j]);
				}
			}
			
		}

		template <typename T>
		T& Array2D<T>::operator () (unsigned int x, unsigned int y) {
			//if ((x >= 0) && (x < height) && ((y >= 0) && (y < width))) {
				return buffer[x * width + y];
			//}
		}
		

		template <typename T>
		Array2D<T>::Array2D(unsigned int width, unsigned int height, const T* data_ptr) {
			
			this->width = width;
			this->height = height;
			
			if (data_ptr != nullptr) {
				setData(data_ptr);	
			}
			else {
				buffer.resize(height * width);
			}
		}

		template <typename T>
		Array2D<T>::Array2D(const Array2D& src) {
			
			height = src.height;
			width = src.width;
			vector<T> v(src.buffer);
			buffer = v;
		}

		template <typename T>
		Array2D<T>::~Array2D() {

		}

		template<typename T>
		Array2D<T>& Array2D<T>::operator=(const Array2D& right) {

			if (&right == this) {
				return *this;
			}

			height = right.height;
			width = right.width;
			vector<T> v(right.buffer);
			buffer = v;
			
			return *this;
		}
	
}