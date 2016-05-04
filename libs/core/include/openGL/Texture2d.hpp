// author: Oleksii Zhogan (alexzhogan@gmail.com)

#ifndef __TEXTURE_2D_HPP__
#define __TEXTURE_2D_HPP__

#include <openGL/OpenGLObject.hpp>
#include <core/Resouce.hpp>

class LIB_EXPORT_CONV Texture2d : public OpenGLObject, public Resource {
public:

    // TODO: Create base class for texture

    typedef Texture2d* PtrType;

    Texture2d(const char* filename);
    ~Texture2d();

    int width() const;
    int heigth() const;

protected:

    unsigned char* loadImage(const char* imagePath);
    void freeImage(unsigned char* buffer);

    bool makeIsBoundCheck(GLuint resourceID);
    bool makeCheck(GLuint resourceID);
    bool makeBind(GLuint resourceID);
    bool makeUnbind(GLuint resourceID);
    bool makeFree(GLuint resourceID);

private:

    int w;
    int h;
    int comps;
};

#endif /* __TEXTURE_2D_HPP__ */