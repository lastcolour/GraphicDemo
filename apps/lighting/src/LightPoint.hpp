#ifndef __LIGHT_CUBE_HPP__
#define  __LIGHT_CUBE_HPP__

#include <GraphicsItem.hpp>

#include <openGL/VAOPipeline.hpp>

#include <memory>

class LightPoint : public GraphicsItem {
public:

    LightPoint(const char* vertShader, const char* fragShader);
    virtual ~LightPoint();

    void render();
    void update(float timeP);
    void setCameraMat(const GLfloat* cameraMat) const;

protected:

    std::unique_ptr<VAOPipeline> vaoPtr;

};

#endif /* __LIGHT_CUBE_HPP__ */