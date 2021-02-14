#include "Model.hpp"
#include <glm/gtc/matrix_transform.hpp>

glh::Model::Model()
    : mPosition(0.f)
    , mRotationAxis(0.f, 0.f, 1.f)
    , mRotation(0.f)
    , mScaleAxis(1.f, 1.f, 1.f)
    , mScale(1.f)
    , mMatrix(1.f)
    , updateMatrix(true)
{
}

glh::Model::~Model()
{
}

const glm::mat4& glh::Model::getMatrix()
{
    if(updateMatrix) {
        computeMatrix();
    }
    
    return mMatrix;
}

const glm::vec3& glh::Model::getPosition() const
{
    return mPosition;
}

void glh::Model::setPosition(const glm::vec3& position)
{
    mPosition = position;
    updateMatrix = true;
}

void glh::Model::setPosition(const float x,const float y,const float z)
{
    setPosition(glm::vec3(x, y, z));
}

const glm::vec3& glh::Model::getRotationAxis() const
{
    return mPosition;
}

void glh::Model::setRotationAxis(const glm::vec3& axis)
{
    mRotationAxis = axis;
    updateMatrix = true;
}

void glh::Model::setRotationAxis(const float x,const float y,const float z)
{
    setRotationAxis(glm::vec3(x, y, z));
}

const glm::vec3& glh::Model::getScaleAxis() const
{
    return mScaleAxis;
}

void glh::Model::setScaleAxis(const glm::vec3& axis)
{
    mScaleAxis = axis;
    updateMatrix = true;
}

void glh::Model::setScaleAxis(const float x,const float y,const float z)
{
    setScaleAxis(glm::vec3(x, y, z));
}

    const float glh::Model::getRotation() const
    {
        return mRotation;
    }
    
    void glh::Model::setRotation(const float rotation)
    {
        mRotation = rotation;
        updateMatrix = true;
    }

    const float glh::Model::getScale() const
    {
        return mScale;
    }
    
    void glh::Model::setScale(const float scale)
    {
        mScale = scale;
        updateMatrix = true;
    }
    
    void glh::Model::computeMatrix()
    {
        mMatrix = glm::mat4(1.f);
        mMatrix = glm::translate(mMatrix, mPosition);
        mMatrix = glm::scale(mMatrix, mScaleAxis * mScale);
        mMatrix = glm::rotate(mMatrix, glm::radians(mRotation), mRotationAxis);

        updateMatrix = false;
    }