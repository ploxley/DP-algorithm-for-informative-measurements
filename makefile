main: main.o find_the_submarine.o
	g++ main.o find_the_submarine.o -o main
	
find_the_submarine.o: find_the_submarine.cc find_the_submarine.h
	g++ -c find_the_submarine.cc -o find_the_submarine.o
	
main.o: main.cc find_the_submarine.h
	g++ -c main.cc -o main.o
	
clean: 
	rm main.o find_the_submarine.o main
