#include <iostream>
#include <string>
#include <sstream>
#include "VolImage.h"

// Command line arguments
// argc: Number of parameters
// argv: Array of pointers to chars (strings).

using namespace std;

int main(int argc, char * argv[])
{
    //volimage <imageBase> [-d i j output_file_name] [-x i output_file_name] [-g i]

    //get basename
    string basename = string(argv[1]);
    //create volImage object and use basename
    VolImage vi;
    vi.readImages(basename);
    cout << "Number of bytes required: " << vi.volImageSize() << endl;
    cout << "---------------------------------------" << endl;
    //get operation
    if (argc>2) {
        string operation = string(argv[2]);
        if (operation=="-d") {
            //difference map [-d i j output_file_name]
            string sliceI = string(argv[3]);
            string sliceJ = string(argv[4]);
            string outFilename = string (argv[5]);

            int intI, intJ;

            istringstream issI(sliceI);
            issI >> intI;
            istringstream issJ(sliceJ);
            issJ >> intJ;

            vi.diffmap(intI,intJ,outFilename);
        } else if (operation=="-x"){
            //extract [-x i output_file_name]
            string sliceI = string(argv[3]);
            string outFilename = string (argv[4]);
            int intI;
            istringstream issI(sliceI);
            issI >> intI;

            vi.extract(intI, outFilename);

        } else if (operation=="-g"){
            //special extract [-g i]
            string sRow = string(argv[3]);
            int row;
            istringstream issI(sRow);
            issI >> row;

            vi.extractRow(row, "output");
        }
    }


    return 0;
}
