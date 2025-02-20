#pragma once

#include <cmath>
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

inline float FONT_SCALE = 1;
inline constexpr float EARTH_RADIUS_METERS = 6378137.0f;
inline constexpr float DEG_2_RAD = M_PI / 180;
inline constexpr float DRAW_SCALE = 0.013;

inline constexpr float AIRCRAFT_SPEED_KNOTS = 20;
inline constexpr float KNOTS_TO_METERS_PER_SECOND = 0.51444f;
inline constexpr float AIRCRAFT_SPEED_PIXEL_PER_SECOND =
    (AIRCRAFT_SPEED_KNOTS * KNOTS_TO_METERS_PER_SECOND);

inline Vector2 SCREEN_CENTER;

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
