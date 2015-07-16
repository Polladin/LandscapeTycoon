

CC=g++

CFLAGS=-c -Wall

SRC= 	../src/main/main.cpp \
	../src/test/add_functions.cpp \
	../src/algorithms/find_path.cpp \
	../src/dyn_obj/TMainDynObject.cpp \
	../src/map/Map.cpp \

OBJ=$(SRC:.cpp=.o)

TARGET=LandscapeTycoon 

all: $(SRC) $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
