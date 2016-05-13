// author: Oleksii Zhogan (alexzhogan@gmail.com)

#include <openGL/Texture.hpp>

#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_JPEG
#define STBI_ONLY_PNG
#define STBI_FAILURE_USERMSG
#include <stb_image.h>

unsigned char* loadImage(const char* filename, int& width, int& height, int& comps, int comp_req) {
    stbi_set_flip_vertically_on_load(true);
    unsigned char* buffer = stbi_load(filename, &width, &height, &comps, comp_req);
    if(buffer == nullptr) {
        std::cerr << "[Image] Can't load image from: " << filename;
        std::cerr << "\n[Image] Problem: " << stbi_failure_reason() << std::endl;
    }
    stbi_set_flip_vertically_on_load(false);
    return buffer;
}

void freeImage(unsigned char* buffer) {
    if(buffer != nullptr) {
        stbi_image_free(buffer);
    }
}

int getCompRequires(GLenum texFormat) {
    switch (texFormat)
    {
    case GL_RGB:
        return 3;
    case GL_RGBA:
        return 4;
    default:
        assert(0 && "Unkown texture format");
        return 0;
    }
}

// TODO: Implemt class with ref and unref methods for shared object holding 

Texture::Texture(const char* filename, GLenum texType) :
    OpenGLObject(),
    Resource(),
    w(0),
    h(0),
    texUnitType(texType),
    texUnitFrmt(GL_NONE) {

    int tComps = 0;
    unsigned char* buffer = loadImage(getFullPath(filename), w, h, tComps, 0);
    if(buffer == nullptr) {
        reset();
        return;
    }
    switch (tComps)
    {
    case 3:
        texUnitFrmt = GL_RGB;
        break;
    case 4:
        texUnitFrmt = GL_RGBA;
        break;
    default:
        freeImage(buffer);
        assert(0 && "Loaded texture with invalid image format");
        reset();
        return;
    }

    GLuint texUnitID = 0;
    glGenTextures(1, &texUnitID);
    glBindTexture(texType, texUnitID);
    switch (texType)
    {
    case GL_TEXTURE_2D:
        glTexImage2D(texType, 0, texUnitFrmt, w, h, 0, texUnitFrmt, GL_UNSIGNED_BYTE, buffer);
    default:
        break;
    }
    freeImage(buffer);

    glBindTexture(texType, 0);
    holdID(texUnitID);
    CHECK_OPENGL_STATUS("Texture:Texture");
}

Texture::Texture(Texture&& texture) :
    OpenGLObject(),
    Resource(),
    w(texture.w),
    h(texture.h),
    texUnitType(texture.texUnitType),
    texUnitFrmt(texture.texUnitFrmt) {

    replaceTo(std::move(texture));
    texture.reset();
}

Texture& Texture::operator=(Texture&& texture) {
    if(this == &texture) {
        return *this;
    }

    w = texture.w;
    h = texture.h;
    texUnitType = texture.texUnitType;
    texUnitFrmt =texture.texUnitFrmt;

    replaceTo(std::move(texture));
    texture.reset();
    return *this;
}

Texture::~Texture() {
    if(getID() == 0) {
        return;
    }
    if(makeIsBoundCheck(getID())) {
        makeUnbind(getID());
    }
    makeFree(getID());
    CHECK_OPENGL_STATUS("Texture:~Texture");
}

int Texture::heigth() const {
    return h;
}

int Texture::width() const{
    return w;
}

bool Texture::makeIsBoundCheck(GLuint resourceID) {
    GLint tTexID = 0;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &tTexID);
    return tTexID == resourceID;
}

bool Texture::makeCheck(GLuint resourceID) {
    return resourceID != 0;
}

bool Texture::makeBind(GLuint resourceID) {
    glBindTexture(texUnitType, resourceID);
    return true;
}

bool Texture::makeUnbind(GLuint resourceID) {
    glBindTexture(texUnitType, 0);
    return true;
}

bool Texture::makeFree(GLuint resourceID) {
    glDeleteTextures(1, &resourceID);
    return true;
}

void Texture::reset() {
    resetID();
    h = 0;
    w = 0;
    texUnitType = GL_NONE;
    texUnitFrmt = GL_NONE;
}

void Texture::generateMipmaps() {
    makeBind(getID());
    glGenerateMipmap(texUnitType);
    makeUnbind(getID());
    CHECK_OPENGL_STATUS("Texture::generateMipmaps");
}

void Texture::setWrapS(GLenum wrapType) {
    makeBind(getID());
    glTexParameteri(texUnitType, GL_TEXTURE_WRAP_S, wrapType);
    makeUnbind(getID());
    CHECK_OPENGL_STATUS("Texture:setWrapS");
}

void Texture::setWrapT(GLenum wrapType) {
    makeBind(getID());
    glTexParameteri(texUnitType, GL_TEXTURE_WRAP_T, wrapType);
    makeUnbind(getID());
    CHECK_OPENGL_STATUS("Texture:setWrapT");
}

void Texture::setWrapR(GLenum wrapType) {
    makeBind(getID());
    glTexParameteri(texUnitType, GL_TEXTURE_WRAP_R, wrapType);
    makeUnbind(getID());
    CHECK_OPENGL_STATUS("Texture:setWrapR");
}

void Texture::setBorderColor() {
}

void Texture::setMinFilter(GLenum filterType) {
    makeBind(getID());
    glTexParameteri(texUnitType, GL_TEXTURE_MIN_FILTER, filterType);
    makeUnbind(getID());
    CHECK_OPENGL_STATUS("Texture:setMinFilter");
}

void Texture::setMagFilter(GLenum filterType) {
    makeBind(getID());
    glTexParameteri(texUnitType, GL_TEXTURE_MAG_FILTER, filterType);
    makeUnbind(getID());
    CHECK_OPENGL_STATUS("Texture:setMagFilter");
}