#pragma once

#include <cstdlib>
#include <cstring>

#include "raylib.h"

inline Font *raylib_font = nullptr;

inline void Load_Font() {
    auto temp = LoadFont("./resource/Roboto-Medium.ttf");
    raylib_font = static_cast<Font *>(malloc(sizeof(Font)));
    memcpy(raylib_font, &temp, sizeof(Font));
}

inline void Unload_Font() {
    UnloadFont(*raylib_font);
    free(raylib_font);
}

inline Font *Get_Font() {
    if (raylib_font == NULL) {
        Load_Font();
    }
    return raylib_font;
}
