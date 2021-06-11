run:main.o kfft.o
	gcc -o run main.o kfft.o  -lm
main.o:xx5.c kfft.h
	gcc -c  xx5.c -o main.o -lm

kfft.o:kfft.c kfft.h
	gcc -c  kfft.c  -lm -o kfft.o
clean:
	rm *.o
