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

Texture::Texture(const char* filename, GLenum texType, GLenum texFormat) : 
    OpenGLObject(),
    Resource(),
    w(0),
    h(0),
    texUnitType(texType),
    texUnitFrmt(texFormat) {

    int tComps = 0;
    int tCompsReq = getCompRequires(texFormat);
    unsigned char* buffer = loadImage(getFullPath(filename), w, h, tComps, tCompsReq);
    if(buffer == nullptr) {
        reset();
        return;
    }
    assert(tComps == tCompsReq && "Loaded invalid image format");

    GLenum imageFrmt = GL_NONE;
    switch (tComps)
    {
    case 3:
        imageFrmt = GL_RGB;
        break;
    case 4:
        imageFrmt = GL_RGBA;
        break;
    default:
        reset();
        return;
    }

    GLuint texUnitID = 0;
    glGenTextures(1, &texUnitID);
    glBindTexture(texType, texUnitID);
    switch (texType)
    {
    case GL_TEXTURE_2D:
        glTexImage2D(texType, 0, texFormat, w, h, 0, imageFrmt, GL_UNSIGNED_BYTE, buffer);
    default:
        break;
    }
    freeImage(buffer);

    glBindTexture(texType, 0);
    holdID(texUnitID);
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

}

void Texture::setWrapS(GLenum wrapType) {
    makeBind(getID());
    glTexParameteri(texUnitType, GL_TEXTURE_WRAP_S, wrapType);
    makeUnbind(getID());
}

void Texture::setWrapT(GLenum wrapType) {
    makeBind(getID());
    glTexParameteri(texUnitType, GL_TEXTURE_WRAP_T, wrapType);
    makeUnbind(getID());
}

void Texture::setWrapR(GLenum wrapType) {
    makeBind(getID());
    glTexParameteri(texUnitType, GL_TEXTURE_WRAP_R, wrapType);
    makeUnbind(getID());
}

void Texture::setBorderColor() {
}

void Texture::setMinFilter(GLenum filterType) {
    makeBind(getID());
    glTexParameteri(texUnitType, GL_TEXTURE_MIN_FILTER, filterType);
    makeUnbind(getID());
}

void Texture::setMagFilter(GLenum filterType) {
    makeBind(getID());
    glTexParameteri(texUnitType, GL_TEXTURE_MAG_FILTER, filterType);
    makeUnbind(getID());
}