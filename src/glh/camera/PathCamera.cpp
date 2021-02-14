#include "PathCamera.hpp"
#include <iostream>

glh::PathCamera::PathCamera()
    : up(0.f, 1.f, 0.f)
    , mProjection(1.f)
    , mPosition(0.f)
    , mDestination(0.f)
    , mTarget(0.f)
    , mVelocity(5.f)
    , mMinDist(0.1f)
    , indexDest(0)
{
}

glh::PathCamera::~PathCamera()
{
}

void glh::PathCamera::update(const float dt)
{
    if(glm::distance(mPosition, mDestination) > mMinDist) {
        mPosition += glm::normalize(mDestination - mPosition) * (mVelocity * dt);
    } else {
        if(indexDest + 1 < destinations.size()) {
            indexDest++;
            mDestination = destinations[indexDest];
        }
    }
}

const glm::mat4 glh::PathCamera::getViewMatrix()  const
{
    return glm::lookAt(mPosition, mTarget, up);
}

const glm::mat4& glh::PathCamera::getProjection() const
{
    return mProjection;
}

void glh::PathCamera::setProjection(const float fov, const float aspectRatio, const float nearPlane, const float farPlane)
{
    mProjection = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

void glh::PathCamera::setProjection(const glm::mat4& projection)
{
    mProjection = projection;
}

const glm::vec3& glh::PathCamera::getPosition() const
{
    return mPosition;
}

void glh::PathCamera::setPosition(const glm::vec3& position)
{
    mPosition = position;
}

void glh::PathCamera::setPosition(const float x, const float y, const float z)
{
    setPosition(glm::vec3(x, y, z));
}

const glm::vec3& glh::PathCamera::getDestination() const
{
    return mDestination;
}

void glh::PathCamera::setDestination(const glm::vec3& destination)
{
    mDestination = destination;
}

void glh::PathCamera::setDestination(const float x, const float y, const float z)
{
    setDestination(glm::vec3(x, y, z));
}

void glh::PathCamera::addDestination(const glm::vec3& destination)
{
    if(destinations.empty()) {
        mDestination = destination;
    }
    destinations.emplace_back(destination);
}

const glm::vec3& glh::PathCamera::getTarget() const
{
    return mTarget;
}

void glh::PathCamera::setTarget(const glm::vec3& target)
{
    mTarget = target;
}

void glh::PathCamera::setTarget(const float x, const float y, const float z)
{
    setTarget(glm::vec3(x, y, z));
}

const float glh::PathCamera::getVelocity() const
{
    return mVelocity;
}

void glh::PathCamera::setVelocity(const float velocity)
{
    mVelocity = velocity;
}
