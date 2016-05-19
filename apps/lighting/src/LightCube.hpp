#ifndef __LIGHT_CUBE_HPP__
#define  __LIGHT_CUBE_HPP__

#include <openGL/VAOPipeline.hpp>

#include <memory>

class SceneObject {
public:

    virtual void setCameraMat(const GLfloat* cameraMat) const = 0;
};


class LightCube : public SceneObject {
public:

    LightCube(const char* vertShader, const char* fragShader);

    virtual ~LightCube();
    virtual void render();
    void setCameraMat(const GLfloat* cameraMat) const;

protected:

    std::unique_ptr<VAOPipeline> vaoPtr;

};

#endif /* __LIGHT_CUBE_HPP__ */