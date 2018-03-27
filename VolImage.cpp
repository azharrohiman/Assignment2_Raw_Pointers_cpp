// VolImage.cpp - implementation file for database() functions

#include "VolImage.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
// for testing
#include <vector>
#include <sys/stat.h>
#include <sys/types.h>

using namespace RHMMUH005;
using namespace std;

namespace RHMMUH005 {

	// default constructor
	VolImage::VolImage() {
		VolImage::width = 0;
		VolImage::height = 0;
	}

	// destructor
	VolImage::~VolImage() {
		for (int i = 0; i < VolImage::slices.size(); i++) {
			for (int j = 0; j < VolImage::height; j++) {
				delete [] VolImage::slices[i][j];
			}
			delete [] VolImage::slices[i];
		}
	}

	// populate the object with images in stack and
	// set member variables
	bool VolImage::readImages(string baseName) {
		int numberOfImages;
		vector<string> tokens;
		string word;
		string fileName = baseName + "/MRI.data";
		ifstream file(fileName);

		if (!file) {
			return false;
		}

		while (getline(file, word, ' ')) {
			tokens.push_back(word);
		}

		VolImage::width = atoi(tokens[0].c_str());
		VolImage::height = atoi(tokens[1].c_str());

		numberOfImages = atoi(tokens.back().c_str());

		for (int i = 0; i < numberOfImages; i++) {
			baseName = "brain_mri_raws";
			string rawFileName = "MRI";
			rawFileName = rawFileName + to_string(i) + ".raw";
			string rawtemp = baseName + "/" + rawFileName;

			ifstream in;
			in.open(rawtemp);

			unsigned char** rows = new unsigned char*[VolImage::height];
			for (int j = 0; j < VolImage::height; j++) {

				rows[j] = new unsigned char[VolImage::width];
				for (int k = 0; k < VolImage::width; k++) {
					rows[j][k] = (unsigned char)(in.get());
				}
			}

			VolImage::slices.push_back(rows);
		}
		return true;
	}

	// compute difference map and write out
	void VolImage::diffmap(int sliceI, int sliceJ, string output_prefix) {
		ofstream output;
		output.open(output_prefix + ".raw");

		for (int i = 0; i < VolImage::height; i++) {
			for (int j = 0; j < VolImage::width; j++) {
				output << (unsigned char) (abs((float) VolImage::slices[sliceI][i][j] - (float) VolImage::slices[sliceJ][i][j])/2);
			}
		}
		output.close();
	}

	// extract slice sliceId and write to output
	void VolImage::extract(int sliceId, string output_prefix) {

		string output_prefix_path = output_prefix + "/" + output_prefix + ".dat";
		const char* datPath = output_prefix_path.c_str();
		ofstream file(datPath);
		file << VolImage::width << " " << VolImage::height << " 1";
		file.close();
		cout << output_prefix << ".dat file created" << endl;

		string output_prefix_raw = output_prefix + "/" + output_prefix + ".raw";
		const char* rawPath = output_prefix_raw.c_str();
		ofstream rawFile(rawPath);

		for (int i = 0; i < VolImage::height; i++) {
			for (int j = 0; j < VolImage::width; j++) {
				rawFile << VolImage::slices[sliceId][i][j];
			}
		}
		rawFile.close();
	}

	// number of bytes used to store image data bytes
	// and pointers (ignore vector<> container, dims etc)
	int VolImage::volImageSize(void) {
		int length = sizeof(slices);
		return length;
	}

};

int main(int argc, char* argv[]) {

	VolImage volObj;

	if (argc == 2) {
		if (volObj.VolImage::readImages(argv[1])) {
			int numberOfImages;
			vector<string> tokens;
			string word;
			string fileName = (string)argv[1] + "/MRI.data";
			ifstream file(fileName);

			if (!file) {
				return false;
			}

			while (getline(file, word, ' ')) {
				tokens.push_back(word);
			}

			numberOfImages = atoi(tokens.back().c_str());
			cout << "Number of images: " << numberOfImages << endl;
			cout << "Number of bytes required: " << volObj.VolImage::volImageSize() << endl;
		}
		return 0;
	}

	string baseName = argv[1];

	if (!volObj.VolImage::readImages(baseName)) {
		cout << "Couldn't open file" << endl;
	}
	else {
		cout << "Reading images..." << endl;
	}

	if (argc == 5) {
		int sliceID = atoi(argv[3]);
		mkdir("output", ACCESSPERMS);
		cout << "Extracting Slice " << argv[3] << endl;
		volObj.VolImage::extract(sliceID, argv[4]);
	}

	if (argc == 6) {
		int sliceI = atoi(argv[3]);
		int sliceJ = atoi(argv[4]);
		cout << "Computing difference map between " << argv[3] << " and " << argv[4] << endl;
		volObj.VolImage::diffmap(sliceI, sliceJ, argv[5]);
	}

	return 0;
}


