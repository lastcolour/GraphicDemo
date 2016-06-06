#ifndef __SCENE_LIGHT_HPP__
#define __SCENE_LIGHT_HPP__

#include <graphics/SceneElement.hpp>

class LIB_EXPORT_CONV SceneLight : public SceneElement {
public:

    SceneLight();
    virtual ~SceneLight();

    virtual void setColor(const glm::vec4& color);

    virtual const glm::vec4& getColor() const;
    virtual glm::vec4& getColor();

private:

    glm::vec4 color;
};

#endif /* __SCENE_LIGHT_HPP__ */
