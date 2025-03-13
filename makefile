all: sum-nbo

sum-nbo: main.o sum-nbo.o
	g++ -o sum-nbo main.o sum-nbo.o

main.o: main.cpp sum-nbo.h
	g++ -c -o main.o main.cpp

sum-nbo.o: sum-nbo.h sum-nbo.cpp
	g++ -c -o sum-nbo.o sum-nbo.cpp

clean:
	rm -f *.o
	rm -f sum-nbo
