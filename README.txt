-----------------------------------
Files in this directory
-----------------------------------
brain_mri_raws/ folder - contains test data header (.dat) and binary (.raw) files.

MRI_originals_png/ folder - contains png picture files of the test data in
brain_mri_raws folder.

VolImage.cpp - source file containing the body of method signatures in
VolImage.h for Volumetric Image manipulation using raw pointers.

VolImage.h - method headers for source file VolImage.cpp.

main.cpp - driver source file for VolImage (The Volumetric Image Manipulation
Tool) methods containing the menu interface and main() method.

Makefile - makefile to compile source files and get: volimage, main.o and VolImage.o

-----------------------------------
Running volimage
-----------------------------------
Open this directory in terminal.

Run the following commands:
make clean
make
make run

*make run will run the executable volimage 4 times:
-> with no arguments, just basename
-> with arguments for difference map operation [-d 11 10 diffmap]
-> with arguments for extract operation [-x 12 extract]
-> with arguments for extract row operation [-g 20]
---The above values for the operation arguments were used for test run---

The following files will be created:
For difference map operation:
->diffmap.dat
->diffmap.raw

For extract operation:
->extract.dat
->extract.raw

For extract row operation:
->output.dat
->output.raw

-----------------------------------
Checking outputted files
-----------------------------------
Run this command in terminal:
make check

This will check the 3 outputted binary(.raw) files:
First it will open diffmap.raw with the python program viewer.py.

To check the second extract.raw file, close the viewer GUI of diffmap.raw.
This will open extract.raw file in another viewer GUI.

To check the third and last output.raw file, close the viewer GUI of extract.raw.
This will open output.raw file in another viewer GUI.

-----------------------------------
Running volimage with own arguments
-----------------------------------
Open terminal in this directory.

To run volimage with own arguments, type in a command in the following form:
./volimage <imageBase> [-d i j output_file_name] [-x i output_file_name] [-g i]

To run this command with available test data, run any of the following commands:
./volimage brain_mri_raws/MRI
./volimage brain_mri_raws/MRI -d [i] [j] [output_file_name]
./volimage brain_mri_raws/MRI -x [i] [output_file_name]
./volimage brain_mri_raws/MRI -g [i]
*arguments in [] must be filled in by user's choice.

-g operations will always be outputted to the filename sequence "output":
output.dat and output.raw
