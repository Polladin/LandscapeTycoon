

CC=g++

CFLAGS=-c -Wall

all: LandscapeTycoon


LandscapeTycoon: main.o add_functions.o
	$(CC) main.o add_functions.o -o LandscapeTycoon.exe
	
main.o: ../src/main/main.cpp ../src/map/Map.h ../src/test/add_functions.h ../src/common/common.h
	$(CC) $(CFLAGS) ../src/main/main.cpp 
	
add_functions.o: ../src/test/add_functions.cpp ../src/test/add_functions.h ../src/common/common.h
	$(CC) $(CFLAGS) ../src/test/add_functions.cpp
	