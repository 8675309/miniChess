FLAGS=-g -Wall
CC=g++ 
OUTPUT=-o chess.exe


all: chess

memcheck: chess
	valgrind --log-file=memcheck.log ./chess.exe
	

chess : main.cpp move.cpp states.cpp square.cpp
	$(CC) $(FLAGS) $(OUTPUT) main.cpp move.cpp states.cpp square.cpp

clean :
	rm -f *.o *.out *.exe
