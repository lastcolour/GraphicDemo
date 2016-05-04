#include <openGL/Texture2d.hpp>

#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_JPEG
#define STBI_ONLY_PNG
#define STBI_FAILURE_USERMSG
#include <stb_image.h>

Texture2d::Texture2d(const char* filename) : 
    OpenGLObject(),
    Resource(),
    w(0),
    h(0),
    comps(0) {
    unsigned char* buffer = loadImage(filename);
    if(buffer == nullptr) {
        return;
    }
    GLuint texUnitID = 0;
    glGenTextures(1, &texUnitID);
    glBindTexture(GL_TEXTURE_2D, texUnitID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
    glGenerateMipmap(GL_TEXTURE_2D);
    freeImage(buffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
    holdID(texUnitID);
}

Texture2d::~Texture2d() {
}

 unsigned char* Texture2d::loadImage(const char* filename) {
    stbi_set_flip_vertically_on_load(true);
    std::string tPath = getFullPath(filename);
    unsigned char* buffer = stbi_load(tPath.c_str(), &w, &h, &comps, 3);
    if(buffer == nullptr) {
        std::cerr << "[Image] Can't load image from: " << tPath;
        std::cerr << "\n[Image] Problem: " << stbi_failure_reason() << std::endl;
    }
    stbi_set_flip_vertically_on_load(false);
    return buffer;
}


void Texture2d::freeImage(unsigned char* buffer) {
    if(buffer != nullptr) {
        stbi_image_free(buffer);
    }
}

int Texture2d::heigth() const {
    return h;
}

int Texture2d::width() const{
    return w;
}

bool Texture2d::makeIsBoundCheck(GLuint resourceID) {
    GLint tTexID = 0;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &tTexID);
    return tTexID == resourceID;
}

bool Texture2d::makeCheck(GLuint resourceID) {
    return resourceID == 0;
    return true;
}

bool Texture2d::makeBind(GLuint resourceID) {
    glBindTexture(GL_TEXTURE_2D, resourceID);
    return true;
}

bool Texture2d::makeUnbind(GLuint resourceID) {
    glBindTexture(GL_TEXTURE_2D, 0);
    return true;
}

bool Texture2d::makeFree(GLuint resourceID) {
    glDeleteTextures(1, &resourceID);
    return true;
}