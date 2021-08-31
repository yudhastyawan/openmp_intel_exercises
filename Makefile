fname=07_prod_cons

all:
	gcc -xc -Wall -g -fopenmp $(fname).c -lm -o $(fname).out
	./$(fname).out

clean:
	rm -rf *.out