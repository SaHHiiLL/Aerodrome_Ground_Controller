PROJECT_ROOT_DIR		?=$(shell pwd)
TARGET					?=$(PROJECT_ROOT_DIR)/build
TARGET_DEBUG			?=$(PROJECT_ROOT_DIR)/debug
SRC						?=$(PROJECT_ROOT_DIR)/src
CPP_FILES				?=$(shell find src/ -mindepth 1 -name '*.cpp')
HPP_FILES				?=$(shell find src/ -mindepth 1 -name '*.hpp')
LIBS					?=$(PROJECT_ROOT_DIR)/libs

RAYLIB_VERSION			?=5.0
RAYLIB_PATH				?=$(LIBS)/raylib-$(RAYLIB_VERSION)_linux_amd64
RAYLIB_DOWNLOAD_URL		?=https://github.com/raysan5/raylib/releases/download/$(RAYLIB_VERSION)/raylib-$(RAYLIB_VERSION)_linux_amd64.tar.gz
RAYLIB_TAR_NAME			?=raylib-$(RAYLIB_VERSION)_linux_amd64.tar.gz
RAYLIB_DIR_PATH 		?=$(LIBS)/raylib-$(RAYLIB_VERSION)_linux_amd64

SPDLOG_VERSION			?=ae1de0dc8cf480f54eaa425c4a9dc4fef29b28ba
SPDLOG_GIT_URL			?=https://github.com/gabime/spdlog.git
SPDLOG_DOWNLOAD_PATH	?=$(LIBS)/spdlog

all: $(CPP_FILES) $(HPP_FILES)
	@if [ ! -d "$(LIBS)" ]; then			\
		$(MAKE) download_raylib; 			\
		$(MAKE) download_triangulation; 	\
		$(MAKE) download_lexer.h;			\
		$(MAKE) download_rlImGuiBridge; 	\
		$(MAKE) download_spdlogs; 			\
	fi										

	$(MAKE) target
	cmake -S $(PROJECT_ROOT_DIR) -B $(TARGET)
	## Call the make file inside 
	cmake --build $(TARGET) -j8

debug: $(CPP_FILES) $(HPP_FILES)
	@if [ ! -d "$(LIBS)" ]; then			\
		$(MAKE) download_raylib; 			\
		$(MAKE) download_triangulation; 	\
		$(MAKE) download_lexer.h;			\
		$(MAKE) download_rlImGuiBridge; 	\
	fi										
	$(MAKE) target_debug
	cmake -S $(PROJECT_ROOT_DIR) -B debug
	cmake -DCMAKE_BUILD_TYPE=Debug debug
	## Call the make file inside 
	cmake --build $(TARGET) -j10

main: $(CPP_FILES)
	$(BUILD_CMD)

target:
	@mkdir -p $(TARGET)

lib_dir:
	@mkdir -p $(LIBS)

target_debug:
	@mkdir -p debug

clean:
	rm -rf $(TARGET)
	rm -rf $(LIBS)

download_raylib: lib_dir
	@echo "[+]INFO: Downloading Raylib..."
	wget -q -O $(LIBS)/$(RAYLIB_TAR_NAME) $(RAYLIB_DOWNLOAD_URL)
	tar -xvf $(LIBS)/$(RAYLIB_TAR_NAME) --directory=$(LIBS)/
	mv $(RAYLIB_DIR_PATH) $(LIBS)/raylib

download_spdlogs: lib_dir
	git clone $(SPDLOG_GIT_URL) $(SPDLOG_DOWNLOAD_PATH)

download_triangulation: lib_dir
	@echo "[+]INFO: Downloading Triangulation Library..."
	@mkdir -p $(LIBS)/triangulation/
	wget -q -O $(LIBS)/triangulation/delaunator.cpp https://raw.githubusercontent.com/SaHHiiLL/delaunator-cpp/refs/heads/master/src/delaunator.cpp
	wget -q -O $(LIBS)/triangulation/delaunator.hpp https://raw.githubusercontent.com/SaHHiiLL/delaunator-cpp/refs/heads/master/include/delaunator.hpp

download_lexer.h: lib_dir
	git clone https://github.com/SaHHiiLL/Lexer.cpp.git
	mv Lexer.cpp $(LIBS)/lexer

download_rlImGuiBridge: lib_dir
	git clone https://github.com/SaHHiiLL/rlImGuiBridge.git
	mv rlImGuiBridge $(LIBS)/imgui
	make -C $(LIBS)/imgui

dev_setup: lib_dir download_raylib download_triangulation download_lexer.h download_rlImGuiBridge download_spdlogs
