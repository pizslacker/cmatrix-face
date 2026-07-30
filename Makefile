cmatrix-face: cmatrix-face.c
	gcc -Wall -Wextra -O2 -o cmatrix-face cmatrix-face.c -lncurses
	strip cmatrix-face

clean:
	rm -f cmatrix-face