#include "Application.hpp"
#include "Coordinate.hpp"
#include "spdlog/spdlog.h"
#include <ostream>

int main() {
#ifdef DEBUG
    spdlog::set_level(spdlog::level::trace);
    spdlog::debug("Debug mode enabled");
#endif

    Application app;
    app.run();
}
