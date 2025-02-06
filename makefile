move: main.o
	g++ main.o -o move

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o move
