#stores g++ compilier as variable for use 
CC=g++

#creates a executable using the given target files
calc: stringCalc.cpp
	$(CC) stringCalc.cpp -o calc

run:
	./calc

#clears all .o files and the created main executable
clean:
	rm -rf *.o calc