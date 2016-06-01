// author: Oleksii Zhogan (alexzhogan@gmail.com)

#ifndef __OPENGL_OBJECT_HPP__
#define __OPENGL_OBJECT_HPP__

#include <core/DEFS.hpp>
#include <openGL/openGL.hpp>

#include <cassert>

class LIB_EXPORT_CONV SharedObject {
public:

    // TODO: Move to other file?

    SharedObject() : refCount(0) {}
    virtual ~SharedObject() { assert(refCount == 0 && "Deleting refferd resource"); }

    void ref() { refCount++; }
    void unref() { assert(refCount > 0 && "Too many unref"); refCount--;}
    int getRefCount() { return refCount; }
    bool isReffed() const { return refCount == 0; }

private:

    SharedObject(const SharedObject&);
    SharedObject& operator=(SharedObject&);

    int refCount;
};


class LIB_EXPORT_CONV OpenGLObject : public SharedObject {
public:

    virtual ~OpenGLObject();

    bool isValid();
    bool isBounded();
    void bind();
    void unbind();

    GLuint getID() const;

protected:

    OpenGLObject();

    virtual bool makeIsBoundCheck() = 0;
    virtual bool makeCheck()        = 0;
    virtual bool makeBind()         = 0;
    virtual bool makeUnbind()       = 0;
    virtual bool makeFree()         = 0;

protected:

    void resetID();
    void replaceToID(OpenGLObject&& object);

    GLuint objID;

private:

     OpenGLObject(const OpenGLObject&);
     OpenGLObject& operator=(const OpenGLObject&);
};

#endif /* __OPENGL_OBJECT_HPP__ */