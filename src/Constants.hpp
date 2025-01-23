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

inline const float EARTH_RADIUS_METERS = 6378137.0f;
inline float DRAW_SCALE = 0.013;
inline float FONT_SCALE = 1;

inline Font *RAYLIB_FONT = nullptr;

inline void load_font() {
    auto temp = LoadFont("./resource/Roboto-Medium.ttf");
    RAYLIB_FONT = new Font{};
    memcpy(RAYLIB_FONT, &temp, sizeof(Font));
}

inline void unload_font() {
    UnloadFont(*RAYLIB_FONT);
    delete RAYLIB_FONT;
}

inline Font *get_font() {
    if (RAYLIB_FONT == nullptr) {
        load_font();
    }
    return RAYLIB_FONT;
}
