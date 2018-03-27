CC=g++

volimage: VolImage.o
	$(CC) VolImage.o -o volimage

VolImage.o: VolImage.cpp VolImage.h
	$(CC) -c VolImage.cpp

run: volimage
	./volimage "brain_mri_raws"

diffmap: volimage
	./volimage "brain_mri_raws" -d 20 30 "output"

extract: volimage
	./volimage "brain_mri_raws" -x 10 "output"

clean:
	rm *.o volimage
