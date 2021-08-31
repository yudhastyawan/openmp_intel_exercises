fname=05_mandel

all:
	gcc -xc -Wall -g -fopenmp $(fname).c -lm -o $(fname).out
	./$(fname).out

clean:
	rm -rf *.out