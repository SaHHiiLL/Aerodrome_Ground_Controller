#pragma once

#include <cstdlib>
#include <cstring>
#include <filesystem>

#include "raylib.h"

inline const std::filesystem::path AIRPORTS_DIR("UK-Sector-File/Airports");
inline const std::filesystem::path BASIC_FILE("Basic.txt");
inline const std::filesystem::path SMR_DIR("SMR");
inline const std::filesystem::path REGIONS_FILE(SMR_DIR / "Regions.txt");
inline const std::filesystem::path LABELS_FILE(SMR_DIR / "Labels.txt");
inline const std::filesystem::path GEO_FILE(SMR_DIR / "Geo.txt");

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
