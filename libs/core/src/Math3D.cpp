// author: Oleksii Zhogan (alexzhogan@gmail.com)

#include <graphics/Math3D.hpp>

Quad::Quad() :
    origX(0.f),
    origY(0.f),
    width(0.f),
    height(0.f) {
}

Quad::Quad(float origX, float origY, float width, float height) :
    origX(origX),
    origY(origY),
    width(width),
    height(height) {
}

Quad::Quad(const Quad& quad) :
    Quad(quad.origX, quad.origY, quad.width, quad.height) {
}

Quad::~Quad() {
}

Quad& Quad::operator=(const Quad& quad) {
    origX = quad.origX;
    origY = quad.origY;
    width = quad.width;
    height = quad.height;
    return *this;
}