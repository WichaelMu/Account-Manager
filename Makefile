all: a clean

a: Assessment3.o vigenerecipher.o input.o quicksort.o filehandler.o
	gcc -Wall -Werror -ansi -o a.out Assessment3.o vigenerecipher.o input.o quicksort.o filehandler.o

vigenerecipher.o: vigenerecipher.c vigenerecipher.h
	gcc -c vigenerecipher.c

input.o: input.c input.h
	gcc -c input.c

quicksort.o: quicksort.c quicksort.h
	gcc -c quicksort.c

filehandler.o: filehandler.c filehandler.h
	gcc -c filehandler.c

Assessment3.o: Assessment3.c
	gcc -c Assessment3.c

clean:
	rm *.o
