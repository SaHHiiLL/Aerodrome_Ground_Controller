CC=clang++
TARGET=build
SRC=src
CPP_FILES=$(shell find src/ -name '*.cpp')

RAYLIB_PATH=./libs/raylib-5.0_linux_amd64
RAYLIB_STATIC_FLAGS=-L$(RAYLIB_PATH)/lib -l:libraylib.a -lm
RAYLIB_INCLUDE=-I$(RAYLIB_PATH)/include

TRIANGLE_PATH=-L./libs/triangulation
TRIANGLE_PATH_INCLUDE=-I./libs/triangulation
TRIANGLE_CPP_FILE=./libs/triangulation/delaunator.cpp

BUILD_CMD=$(CC) -ggdb -o $(TARGET)/main $(CPP_FILES) $(RAYLIB_STATIC_FLAGS) $(RAYLIB_INCLUDE) $(TRIANGLE_PATH) $(TRIANGLE_PATH_INCLUDE) $(TRIANGLE_CPP_FILE)

RAYLIB_DOWNLOAD_PATH=https://github.com/raysan5/raylib/releases/download/5.0/raylib-5.0_linux_amd64.tar.gz
RAYLIB_TAR_NAME=raylib-5.0_linux_amd64.tar.gz
LIBS=./libs


all:
	# Download dep if it does not exists -- Kind of a poor mans way of checking it
	# TODO: introduce sha1 hash and check if it's correct
	@if [ ! -d "$(LIBS)" ]; then			\
		$(MAKE) download_raylib; 			\
		$(MAKE) download_triangulation; 	\
	fi										

	$(MAKE) complie_command
	$(MAKE) target
	$(MAKE) main

main: $(CPP_FILES)
	$(BUILD_CMD)

target:
	mkdir -p $(TARGET)

clean:
	rm -rf build
	rm -rf libs
	rm compile_commands.json

download_raylib:
	@echo "[+]INFO: Downloading Raylib..."
	@mkdir -p $(LIBS)
	wget -q -O $(LIBS)/$(RAYLIB_TAR_NAME) $(RAYLIB_DOWNLOAD_PATH)
	tar -xvf $(LIBS)/$(RAYLIB_TAR_NAME) --directory=$(LIBS)/

download_triangulation:
	@echo "[+]INFO: Downlaoding Triangulation Library..."
	@mkdir -p $(LIBS)/
	@mkdir -p $(LIBS)/triangulation/
	wget -q -O $(LIBS)/triangulation/delaunator.cpp https://raw.githubusercontent.com/SaHHiiLL/delaunator-cpp/refs/heads/master/src/delaunator.cpp
	wget -q -O $(LIBS)/triangulation/delaunator.hpp https://raw.githubusercontent.com/SaHHiiLL/delaunator-cpp/refs/heads/master/include/delaunator.hpp

# Dev setup
setup: download_raylib download_triangulation complie_command

# Sets up the compile_command.json file for clang lsp 
complie_command:
	@(ls compile_commands.json >> /dev/null 2>&1 ) || bear -- $(BUILD_CMD) 
