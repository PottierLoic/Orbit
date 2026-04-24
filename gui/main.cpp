#include "app.hpp"

#include <iostream>

int main() {
    try {
        App app(1280, 720, "Orbit");
        app.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}