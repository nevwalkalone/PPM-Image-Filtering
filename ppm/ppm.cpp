#include "ppm.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/*
Comments can be found in ppm.h
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
				cerr << " Could not process "<< filename << ". Width must be numerical." << endl;
				return nullptr;
			}
		}
		

		*w = stoi(word);
		file >> word;
		for (int i = 0; i < word.length(); i++) {
			if (!isdigit(word[i])) {
				cerr << "Height must be numerical" << endl;
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

		size_t size = 3 * (*w) * (*h);
		unsigned char* buffer = new unsigned char[size];
		file.read((char*)buffer, size);
		float* pointer = new float[size];

		for (int i = 0; i < size; i++) {
			pointer[i] = buffer[i] / 255.f;
		}
		
		delete[] buffer;
		file.close();
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

		file << "P6" << "\n" << w << "\n" << h << "\n" << 255<<"\n";
		size_t size = 3 * w * h;
		int val;
		

		for (int i = 0; i < size; i++) {
			
			val = data[i] * 255;
			file.put(val);
		}

		file.close();
		return true;
	}

}