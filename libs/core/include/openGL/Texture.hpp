// author: Oleksii Zhogan (alexzhogan@gmail.com)

#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__

#include <openGL/OpenGLObject.hpp>
#include <core/Resouce.hpp>

class LIB_EXPORT_CONV Texture : public OpenGLObject, public Resource {
public:

    typedef Texture* PtrType;

    Texture(const char* filename, GLenum texType);
    Texture(Texture&& texture);
    Texture& operator=(Texture&& texture);
    ~Texture();

    void generateMipmaps();
    void setWrapS(GLenum wrapType);
    void setWrapT(GLenum wrapType);
    void setWrapR(GLenum wrapType);
    void setBorderColor();
    void setMinFilter(GLenum filterType);
    void setMagFilter(GLenum filterType);

    void getType() const;
    void getFormat() const;

    int width() const;
    int heigth() const;

protected:

    void reset();

    bool makeIsBoundCheck();
    bool makeCheck();
    bool makeBind();
    bool makeUnbind();
    bool makeFree();

private:

    int w;
    int h;

    GLenum texUnitType;
    GLenum texUnitFrmt;
};

#endif /* __TEXTURE_HPP__ */