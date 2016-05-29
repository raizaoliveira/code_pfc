all:
	gcc -c inaudio.c -Wall -Wextra
	gcc -c fft.c -Wall -Wextra
	gcc -c frame.c -Wall -Wextra
	gcc -c split.c -Wall -Wextra
	gcc -c linklist.c -Wall -Wextra
	gcc -c compare.c -Wall -Wextra
	gcc -c dir.c
	gcc -c link.c -Wall -Wextra
	ar rcs liblink.a *.o
	gcc -o mfcc main.c -L. -llink -ldl -lm -lasound -lpthread -Wall -Wextra

clean:
	rm main *~
