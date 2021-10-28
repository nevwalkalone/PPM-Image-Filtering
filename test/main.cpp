#include "FilterLinear.h"
#include "FilterGamma.h"
#include "image.h"

bool Isdigit(const string& temp,int* count_dots) {
	for (int i = 0; i < temp.length();i++) {
		
		if ((temp[i] == '.') &&(*count_dots==0) &&((i>0) &&(i<temp.length()-1))){
			*count_dots++;
			continue;
		}
		else if ((temp[i] == '-') && (i==0)) {
			
			continue;
		}
		else{ 
			if (!isdigit(temp[i])) {
				
				return false;

			}
		}
	}
	return true;
}

int main(int argc, char* argv[]) {
	
	if (argc < 6) {
		cerr << "Filter Format not correct" << endl;
		return -1;
	}
	string filename = argv[argc - 1];
	
	if (filename.find("ppm") == string::npos) {
		cerr << "Ppm file not found. Extension of the file to be filtered must be ppm(lowercase)."<<endl;
		return -1;
	}
	
	string temp = argv[1];
	if (temp != "filter") {
		
		cerr << "Filter Format not correct" << endl;
		return -1;
	}
	temp = argv[2];
	if (temp != "-f") {
		cerr << "Filter Format not correct" << endl;
		return -1;
	}
	
	Image new_image;
	
	if (!new_image.load(filename, "ppm")) {
		return -1;
	}
	
	int i = 3;
	string holder;
	
	int count_dots = 0;
	while (i < argc-1) {
		holder = argv[i];
		if (holder == "-f") {
			i++;
		}
		else if (holder == "gamma") {
			
			temp = argv[i + 1];
			
			if (!Isdigit(temp,&count_dots)) {
				cerr << "FilterGamma Format not correct" << endl;
				return -1;
			}
			count_dots = 0;
			FilterGamma gamma;
			gamma.setG(atof(argv[i + 1]));
			new_image = gamma << new_image;
			if (i + 2 < argc - 1) {
				temp = argv[i + 2];
				if (temp != "-f") {
					cerr << "Filter Format not correct" << endl;
					return -1;
				}
			}
			
			
			i += 2;
		}
		else if(holder == "linear") {
			
			if (i + 6 >= argc - 1) {
				cerr << "FilterLinear Format not correct." << endl;
				return -1;
			}
			for (int j = i + 1; j <= i + 6; j++){
				
				temp=argv[j];
				
				if (!Isdigit(temp,&count_dots)) {
					cerr << "FilterLinear Format not correct." << endl;
					return -1;
				}
				count_dots = 0;
			}
			
			FilterLinear linear;
			linear.setVec3a(atof(argv[i + 1]), atof(argv[i + 2]), atof(argv[i + 3]));
			linear.setVec3c(atof(argv[i + 4]), atof(argv[i + 5]), atof(argv[i + 6]));
			new_image = linear << new_image;
			
			if (i + 7 < argc - 1) {
				temp = argv[i + 7];
				if (temp != "-f") {
					cerr << "Filter Format not correct" << endl;
					return -1;
				}
			}
			i += 7;
		}
		else {
			
			cerr << "Filter Format not correct." << endl;
			return -1;
		}
		
	}
	string name = "filtered_";
	name.append(filename); 
	if (!new_image.save(name, "ppm")) {
		cerr << "Filtering of: "<<filename<< " was unsuccessful." << endl;
		return -1;
	}
	
	cout << "Filtering of " << filename << " was successful. " << name << " has been created." << endl;

	return 0;

}