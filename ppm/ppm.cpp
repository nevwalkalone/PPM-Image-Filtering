#include "ppm.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/*
Comments regarding these 2 functions can be found in ppm.h
*/

namespace image {

	float* ReadPPM(const char *filename, int *w, int *h) {
		
		ifstream file(filename, ios::binary);

		// file could not be opened, so a null ptr is returned
		if (!file.is_open()) {
			cerr << "Could not open " << filename << endl;
			return nullptr;
		}

		string word;
		file >> word;
		if (!word._Equal("P6")) {
			cerr << "Could not process "<< filename<< ". Only P6 Format allowed." << endl;
			return nullptr;
		}

		file >> word;
		for (int i = 0; i < word.length(); i++) {
			if (!isdigit(word[i])) {
				cerr << "Could not process "<< filename << ". Width must be numerical." << endl;
				return nullptr;
			}
		}
		
		*w = stoi(word);
		file >> word;
		for (int i = 0; i < word.length(); i++) {
			if (!isdigit(word[i])) {
				cerr << "Could not process " << filename << "Height must be numerical." << endl;
				return nullptr;
			}
		}
		
		*h = stoi(word);
		file >> word;
		
		for (int i = 0; i < word.length(); i++) {
			if (!isdigit(word[i])) {
				cerr << "Max value for each pixel must be numerical" << endl;
				return nullptr;
			}
		}
		
		if (stoi(word) > 255 || stoi(word) < 0) {
			cerr << "Max value for each pixel must be between 0 and 255" << endl;
			return nullptr;
		}

		// ignoring the /n character
		file.ignore(1);

	
		int size = 3 * (*w) * (*h);

		unsigned char* buffer = new unsigned char[size];

		// reading all data into the buffer
		file.read((char*)buffer, size);
		file.close();

		// memory must be released from the caller
		float* pointer = new float[size];

		// values must be in the range [0,1], tha'ts why we divide by 255
		for (int i = 0; i < size; i++) {
			pointer[i] = buffer[i] / 255.f;
		}

		// buffer no longer needed, releasing memory
		delete[] buffer;

		return pointer;
	}



	bool WritePPM(const float* data, int w, int h, const char* filename) {
		
		if (data == nullptr) {
			cerr << "No data given to write in a new file." << endl;
			return false;
		}

		ofstream file(filename, ios::binary);
		if (!file.is_open()) {
			cerr << "Could not open" << filename << endl;
			return false;
		}

		// Creating PPM header which contains the width, height
		// and the maximum value for a pixel (255) in this order.
		file << "P6" << "\n" << w << "\n" << h << "\n" << 255<<"\n";
		int size = 3 * w * h;
		int val;
		
		// writing data to the file, we multiply by 255
		// because the values must be in the [0,255] range
		for (int i = 0; i < size; i++) {
			val = data[i] * 255;
			file.put(val);
		}

		file.close();
		return true;
	}

}