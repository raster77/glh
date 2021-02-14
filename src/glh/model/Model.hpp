#ifndef MODEL_HPP
#define MODEL_HPP

#include <glm/glm.hpp>

namespace glh
{

class Model
{
public:
    Model();
    ~Model();
    
    const glm::mat4& getMatrix();

    const glm::vec3& getPosition() const;
    void setPosition(const glm::vec3& position);
    void setPosition(const float x,const float y,const float z);

    const glm::vec3& getRotationAxis() const;
    void setRotationAxis(const glm::vec3& axis);
    void setRotationAxis(const float x,const float y,const float z);

    const float getRotation() const;
    void setRotation(const float rotation);

    const glm::vec3& getScaleAxis() const;
    void setScaleAxis(const glm::vec3& axis);
    void setScaleAxis(const float x,const float y,const float z);

    const float getScale() const;
    void setScale(const float scale);

private:
    glm::vec3 mPosition;
    glm::vec3 mRotationAxis;
    float mRotation;
    glm::vec3 mScaleAxis;
    float mScale;
    glm::mat4 mMatrix;
    bool updateMatrix;
    
    void computeMatrix();

};

}

#endif // MODEL_HPP
