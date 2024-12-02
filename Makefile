CC=clang++
TARGET=build
SRC=src
CPP_FILES=$(shell fd .cpp $(SRC)/ -t f --color=never)

RAYLIB_PATH=./libs/raylib-5.0
RAYLIB_STATIC_FLAGS=-L$(RAYLIB_PATH)/lib -l:libraylib.a -lm
RAYLIB_INCLUDE=-I$(RAYLIB_PATH)/include

TRIANGLE_PATH=-L$./libs/triangulation
TRIANGLE_PATH_INCLUDE=-I$./libs/triangulation

all: target main

main: $(CPP_FILES)
	$(CC) -O0 -o $(TARGET)/main $(CPP_FILES) $(RAYLIB_STATIC_FLAGS) $(RAYLIB_INCLUDE) $(TRIANGLE_PATH) $(TRIANGLE_PATH_INCLUDE)

target:
	mkdir -p $(TARGET)
