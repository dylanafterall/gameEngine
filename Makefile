#    Dylan Campbell
#    campbell.dyl@gmail.com
#    gameEngine

CC = g++
CFLAGS = -std=c++17 -Wall
INC_PATH = -I"./src/headers/" -I"./lib/"
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua5.3 -lspdlog

TARGET = bin/engine
SRC_FILES = src/*.cpp
OBJ_FILES = obj/main.o \
			obj/game.o

#-------------------------------------------------------------------------------
# make                  makes executable
# make build			makes all (missing/old) obj files and executable
# make run              executes binary
# make clean            removes all object files and executable
# make check			checks executable for memory errors via valgrind
#-------------------------------------------------------------------------------


# make -------------------------------------------------------------------------
engine :
	$(CC) $(CFLAGS) $(INC_PATH) $(SRC_FILES) $(LIBS) -o $(TARGET)


# make build -------------------------------------------------------------------
build : $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LIBS) -o $(TARGET)

obj/main.o : src/main.cpp
	$(CC) $(CFLAGS) $(INC_PATH) -c src/main.cpp -o obj/main.o

obj/game.o : src/game.cpp src/headers/game.h
	$(CC) $(CFLAGS) $(INC_PATH) -c src/game.cpp -o obj/game.o


# make run ---------------------------------------------------------------------
run :
	$(TARGET)

# make clean -------------------------------------------------------------------
clean :
	rm -f $(TARGET) $(OBJ_FILES)

# make check -------------------------------------------------------------------
check :
	valgrind --leak-check=full $(TARGET)
