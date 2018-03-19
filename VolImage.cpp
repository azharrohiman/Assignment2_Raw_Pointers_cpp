// VolImage.cpp - implementation file for database() functions

#include "VolImage.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
// for testing
#include <vector>

using namespace RHMMUH005;
using namespace std;

namespace RHMMUH005 {

	// default constructor
	VolImage::VolImage() {
		VolImage::width = 10;
	}

	// destructor
	VolImage::~VolImage() {

	}

	// populate the object with images in stack and
	// set member variables
	bool VolImage::readImages(string baseName) {
		return false;
	}

	// compute difference map and write out
	void VolImage::diffmap(int sliceI, int sliceJ, string output_prefix) {

	}

	// extract slice sliceId and write to output
	void VolImage::extract(int sliceId, string output_prefix) {

	}

	// number of bytes used to store image data bytes
	// and pointers (ignore vector<> container, dims etc)
	int VolImage::volImageSize(void) {
		return 0;
	}

	int VolImage::getWidth() {
		return VolImage::width;
	}

};

int main(int argc, char* argv[]) {

	cout << argc << endl;
	cout << argv[0] << endl;

	VolImage vol1;
	cout << vol1.VolImage::getWidth() << endl;
	return 0;
}


