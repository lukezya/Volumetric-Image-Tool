#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "VolImage.h"

using namespace std;

//default constructor
VolImage::VolImage(): width(0), height(0){}

//destructor
VolImage::~VolImage() {
    //free dynamic memory - heap
    for (int i=0;i<slices.size();i++){
        for (int j=0;j<height;j++){
            delete [] slices[i][j];
        }
        delete [] slices[i];
    }

}

//populate the object with images in stack and set member variables
bool VolImage::readImages(std::string baseName) {
    //read header file first - width height noImages
    string headerFilename = baseName+".dat";
    ifstream ifsHeader(headerFilename);
    int noImages;
    if (!ifsHeader){
        //cerr << "Opening " << headerFilename << " failed :(" << endl;
        cout << "Opening " << headerFilename << " failed :(" << endl;
    } else {
        string line;
        getline(ifsHeader, line);
        istringstream issHeader(line);
        issHeader >> width >> height >> noImages;
    }
    ifsHeader.close();

    //read binary files
    for (int i=0;i<noImages;i++){
        string binaryFilename = baseName+to_string(i)+".raw";
        unsigned char** array = new unsigned char*[height];
        ifstream ifsBinary(binaryFilename,ios::in|ios::binary);
        for (int j=0;j<height;j++){
            array[j] = new unsigned char[width];
            ifsBinary.read(reinterpret_cast<char *>(array[j]), width);
        }
        ifsBinary.close();

        slices.push_back(array);
    }

    cout << "Finished loading " << noImages << " image slices into vector." << endl;
    cout << "---------------------------------------" << endl;
    cout << "Number of images: "<< noImages << endl;
}

//compute difference map and write out
void VolImage::diffmap(int sliceI, int sliceJ, std::string output_prefix) {
    //calculate difference map
    unsigned char ** diffSet = new unsigned char*[height];
    for (int i=0;i<height;i++){
        diffSet[i]=new unsigned char[width];
        for (int j=0;j<width;j++){
            diffSet[i][j] = (unsigned char)(abs((float)slices[sliceI][i][j]-(float)slices[sliceJ][i][j])/2);
        }
    }
    cout << "Difference map between " << sliceI << " and " << sliceJ << " computed ..." << endl;

    //write out
    //header .dat
    string outHeaderFilename = output_prefix + ".dat";
    ofstream ofsHeader(outHeaderFilename);
    ofsHeader << width  << " " << height << " " <<1<<endl;
    ofsHeader.close();

    cout << "Header file " << outHeaderFilename << " generated ..." << endl;

    //sequence .raw
    string outBinaryFilename = output_prefix + ".raw";
    ofstream ofsBinary(outBinaryFilename, ios::out|ios::binary);

    for (int k=0;k<height;k++){
        //ofsBinary.write(static_cast<const char *>(reinterpret_cast<const char *>(slices[sliceId][i])), width);
        ofsBinary.write(reinterpret_cast<const char *>(diffSet[k]), width);
    }
    ofsBinary.close();

    cout << "Binary file " << outBinaryFilename << " generated ..." << endl;
    cout << "Difference map operation finished executing." << endl;
}

//extract slice sliceId and write to output
void VolImage::extract(int sliceId, std::string output_prefix) {
    //header .dat
    string outHeaderFilename = output_prefix + ".dat";
    ofstream ofsHeader(outHeaderFilename);
    ofsHeader << width  << " " << height << " " <<1<<endl;
    ofsHeader.close();

    cout << "Header file " << outHeaderFilename << " generated ..." << endl;

    //sequence .raw
    string outBinaryFilename = output_prefix + ".raw";
    ofstream ofsBinary(outBinaryFilename, ios::out|ios::binary);

    for (int i=0;i<height;i++){
        //ofsBinary.write(static_cast<const char *>(reinterpret_cast<const char *>(slices[sliceId][i])), width);
        ofsBinary.write(reinterpret_cast<const char *>(slices[sliceId][i]), width);
    }
    ofsBinary.close();

    cout << "Binary file " << outBinaryFilename << " generated ..." << endl;
    cout << "Extract operation finished executing." << endl;
}

void VolImage::extractRow(int row, std::string output_prefix) {
    //header .dat
    string outHeaderFilename = output_prefix + ".dat";
    ofstream ofsHeader(outHeaderFilename);
    ofsHeader << width  << " " << slices.size() << " " <<1<<endl;
    ofsHeader.close();

    cout << "Header file " << outHeaderFilename << " generated ..." << endl;

    //sequence .raw
    string outBinaryFilename = output_prefix + ".raw";
    ofstream ofsBinary(outBinaryFilename, ios::out|ios::binary);

    for (int j=0;j<slices.size();j++){
        //ofsBinary.write(static_cast<const char *>(reinterpret_cast<const char *>(slices[sliceId][i])), width);
        ofsBinary.write(reinterpret_cast<const char *>(slices[j][row]), width);
    }

    ofsBinary.close();

    cout << "Binary file " << outBinaryFilename << " generated ..." << endl;
    cout << "Special extract row operation finished executing." << endl;
}

//number of bytes uses to store image data bytes and pointers (ignore vector<> container, dims etc)
int VolImage::volImageSize(void) {
    //sizeof(unsigned char)*width*height*noImages - image data
    //pointers - unsigned char **
    //         - unsigned char * x height
    int imgBytes = sizeof(unsigned char)*width*height*slices.size();
    int pterBytes = sizeof(unsigned char **)+ sizeof(unsigned char *)*height;
    return imgBytes + pterBytes;
}
