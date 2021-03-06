#    Dylan Campbell
#    campbell.dyl@gmail.com
#    gameEngine

CC = g++
CFLAGS = -std=c++17 
INC_PATH = -I"./lib/" -I"./src/headers/"
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua5.3 -lspdlog

TARGET = bin/engine
SRC_FILES = src/*.cpp
OBJ_FILES = obj/main.o \
			obj/game.o \
			obj/ecs.o \
			obj/assetstore.o


#-------------------------------------------------------------------------------
# make                  makes executable
# make build			makes all (missing/old) obj files and executable
# make run              executes binary
# make clean            removes all object files and executable
# make memcheck			checks memory-management (leaks, mem access, bad free's)
# make cachegrind		checks cache-profiling (simulates caches to find misses)
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

obj/ecs.o : src/ecs.cpp src/headers/ecs.h
	$(CC) $(CFLAGS) $(INC_PATH) -c src/ecs.cpp -o obj/ecs.o

obj/assetstore.o : src/assetstore.cpp src/headers/assetstore.h
	$(CC) $(CFLAGS) $(INC_PATH) -c src/assetstore.cpp -o obj/assetstore.o


# make run ---------------------------------------------------------------------
run :
	$(TARGET)

# make clean -------------------------------------------------------------------
clean :
	rm -f $(TARGET) $(OBJ_FILES)

# make memcheck ----------------------------------------------------------------
memcheck :
	valgrind --leak-check=yes $(TARGET)

# make cachegrind --------------------------------------------------------------
cachegrind :
	valgrind --tool=cachegrind $(TARGET)
