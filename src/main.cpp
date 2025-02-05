#include "Application.hpp"

int main() {
#ifdef DEBUG
    spdlog::set_level(spdlog::level::trace);
    spdlog::debug("Debug mode enabled");
#endif
    Application app;
    app.run();
}
