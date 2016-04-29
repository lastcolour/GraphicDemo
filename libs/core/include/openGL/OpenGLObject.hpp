// author: Oleksii Zhogan (alexzhogan@gmail.com)

#ifndef __OPENGL_OBJECT_HPP__
#define __OPENGL_OBJECT_HPP__

#include <core/DEFS.hpp>
#include <openGL/openGL.hpp>

class LIB_EXPORT_CONV OpenGLObject {
public:

    virtual ~OpenGLObject();

    bool isValid();
    bool isBounded();
    void bind();
    void unbind();

protected:

    OpenGLObject();

    virtual bool makeIsBoundCheck(GLuint resourceID) = 0;
    virtual bool makeCheck(GLuint resourceID)        = 0;
    virtual bool makeBind(GLuint resourceID)         = 0;
    virtual bool makeUnbind(GLuint resourceID)       = 0;
    virtual bool makeFree(GLuint resourceID)         = 0;

    void holdID(GLuint resourceID);
    void replaceID(OpenGLObject&& resourceID);
    GLuint getID() const;

private:

     OpenGLObject(const OpenGLObject&);
     OpenGLObject& operator=(const OpenGLObject&);

     GLuint resID;
};

#endif /* __OPENGL_OBJECT_HPP__ */