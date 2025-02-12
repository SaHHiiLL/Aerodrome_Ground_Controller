#include "Application.hpp"
#include "spdlog/spdlog.h"

int main() {
#ifdef DEBUG
    spdlog::set_level(spdlog::level::trace);
    spdlog::debug("Debug mode enabled");
    Coordinate a(51.5, 0);
    Coordinate b(38.8, -77.1);
    double x = a.get_distance_m(b);

    spdlog::info("{}", x);
#endif

    Application app;
    app.run();
}
