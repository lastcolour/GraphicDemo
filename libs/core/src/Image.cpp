#include <core/Image.hpp>

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_JPEG
#define STBI_ONLY_PNG
#define STBI_FAILURE_USERMSG

#include <stb_image.h>
#include <string>

Image::Image(const char* filename, bool flipped /* =false */) : 
    Resource(),
    w(0),
    h(0),
    comps(0),
    buffer(nullptr) {
    if(flipped) {
        stbi_set_flip_vertically_on_load(true);
    }
    std::string tPath = getFullPath(filename);
    tPath = tPath + "/" + filename;
    buffer = stbi_load(filename, &w, &h, &comps, 0);
    if(buffer == nullptr) {
        std::cerr << "[Image] Can't load image from: " << filename;
        std::cerr << "\n[Image] Problem: " << stbi_failure_reason() << std::endl;
    }

    stbi_set_flip_vertically_on_load(false);
}

Image::~Image() {
    if(buffer != nullptr) {
        stbi_image_free(buffer);
    }
}

unsigned char* Image::data() const {
    return buffer;
}

int Image::components() const {
    return comps;
}

int Image::heigth() const {
    return h;
}

int Image::width() const{
    return w;
}

bool Image::isValid() const {
    return buffer != nullptr;
}