// author: Oleksii Zhogan

#include <core/Surface.hpp>

Application* Surface::appListener = nullptr;

Surface::Surface(Application* app) {
    appListener = app;
}

Surface::~Surface() {
}
