CC=g++

volimage: VolImage.o
	$(CC) VolImage.o -o volimage

VolImage.o: VolImage.cpp VolImage.h
	$(CC) -c VolImage.cpp

run: volimage
	./volimage "brain_mri_raws"

clean:
	rm *.o volimage
