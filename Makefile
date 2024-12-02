CC=clang++
TARGET=build
SRC=src
CPP_FILES=$(shell fd .cpp $(SRC)/ -t f --color=never)

RAYLIB_PATH=./libs/raylib-5.0
RAYLIB_STATIC_FLAGS=-L$(RAYLIB_PATH)/lib -l:libraylib.a -lm
RAYLIB_INCLUDE=-I$(RAYLIB_PATH)/include

TRIANGLE_PATH=-L./libs/triangulation
TRIANGLE_PATH_INCLUDE=-I./libs/triangulation

BUILD_CMD=$(CC) -O0 -o $(TARGET)/main $(CPP_FILES) $(RAYLIB_STATIC_FLAGS) $(RAYLIB_INCLUDE) $(TRIANGLE_PATH) $(TRIANGLE_PATH_INCLUDE)

all: setup target main

main: $(CPP_FILES)
	$(BUILD_CMD)

target:
	mkdir -p $(TARGET)

clean:
	rm -rf build
	rm compile_commands.json

GREEN='\033[0;32m'
NC='\033[0m'

setup: 
	@(ls compile_commands.json >> /dev/null 2>&1 && printf "\n$(GREEN)compile_command.json Already exists$(NC)\n\n") || bear -- $(BUILD_CMD) 
