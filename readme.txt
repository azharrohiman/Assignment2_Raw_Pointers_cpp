Muhammad Azhar Rohiman - RHMMUH005. CSC3022H - Assignment 2.

VolImage.cpp: contains all methods that handles extraction, computation of difference map.

VolImage.h: header file for VolImage.cpp, contains definitions of methods' headers

Instructions on how to compile, run and use the program:

1) cd to folder containing cpp and h files. 'cd Assignment2'

2) you may have to extract the brain_mri_raws.tar.gz file since it will be in the tarball

3) type 'make' command in terminal to create object and executable files

4) type 'make clean' to remove object, executable and other unnecessary files

5) there are several ways to run the program as arguments may be used or not

   i) to run the program without arguments, type 'make run' or './volimage brain_mri_raws'

  ii) to run the difference map method, type 'make diffmap' - this will run the command in the makefile which only computes the slices 20 to 30 as default
      To use a different set of slices, as an exmaple, type './volimage brain_mri_raws -d 50 70 output'. This will create a raw file in the current directory.

 iii) to run the extract method, type 'make extract' - this will run the command in the makefile which only extracts the slice 10.
      To use a different slice, as an example, type '/volimage brain_mri_raws -x 100 output'.
      As specified in the pdf, an output sequence is required (not sure what that means), therefore I create a directory each time extract() is called
      The output.dat and output.raw files can be found in the output folder which will be in the current directory. To access the files, please use the path to
      output. Thank you.

Feel free to contact me on rhmmuh005@myuct.ac.za if you encounter any issue. Thank you.
