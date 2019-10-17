# Makefile for Assignemnt 2
# 27 Mar 2018
# Tony Guo
# GXXHEN001

volimage: main.o
	g++ -o volimage main.o VolImage.o -std=c++11

main.o: main.cpp VolImage.o
	g++ -c -o main.o main.cpp -std=c++11

VolImage.o: VolImage.cpp VolImage.h
	g++ -c -o VolImage.o VolImage.cpp -std=c++11

run:
	./volimage brain_mri_raws/MRI
	./volimage brain_mri_raws/MRI -d 11 10 diffmap
	./volimage brain_mri_raws/MRI -x 12 extract
	./volimage brain_mri_raws/MRI -g 20

check:
	python viewer.py diffmap.raw 429 303
	python viewer.py extract.raw 429 303
	python viewer.py output.raw 429 123

clean:
	@rm -f *.o volimage *.dat *.raw
