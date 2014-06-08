exe: main.cpp Red.o
	g++ -g -o exe main.cpp Red.o

Red.o: Red.h Red.cpp
	g++ -c Red.cpp
clean:
	rm *.o
	rm *~
	rm exe
