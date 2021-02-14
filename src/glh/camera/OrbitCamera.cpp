#include "OrbitCamera.hpp"
#include <glm/gtx/euler_angles.hpp>
#include <algorithm>
#include <iostream>
glh::OrbitCamera::OrbitCamera()
    : up(0.f, 1.f, 0.f)
    , mProjection(1.f)
    , mPosition(0.f)
    , mDistance(0.f)
    , mTarget(0.f)
    , oldMousePos(0.f)
    , mMaxMouseDelta(10.f)
    , mYaw(0.f)
    , mPitch(0.f)
    , mMoveSpeed(2.5f)
    , mMouseSensitivity(0.5f)
{
    update();
}

glh::OrbitCamera::~OrbitCamera()
{
}

void glh::OrbitCamera::mouseWheel(const float offset)
{
    mDistance -= glm::vec3(offset);
    update();
}

void glh::OrbitCamera::mouseMove(const float x, const float y)
{

    mousePos = glm::vec2(x, y);

    float xoffset = (mousePos.x - oldMousePos.x);
    if(std::abs(xoffset) < 2.f)
        xoffset = 0;
    float yoffset = (oldMousePos.y - mousePos.y);
    if(std::abs(yoffset) < 2.f)
        yoffset = 0;

    if(xoffset > mMaxMouseDelta)
        xoffset = mMaxMouseDelta;
    else if(xoffset < -mMaxMouseDelta)
        xoffset = -mMaxMouseDelta;

    if(yoffset > mMaxMouseDelta)
        yoffset = mMaxMouseDelta;
    else if(yoffset < -mMaxMouseDelta)
        yoffset = -mMaxMouseDelta;

    xoffset *= mMouseSensitivity;
    yoffset *= mMouseSensitivity;

    mYaw = constraintYaw(mYaw + xoffset);

    mPitch = constraintPitch(mPitch + yoffset);

    oldMousePos = mousePos;

    update();

}

void glh::OrbitCamera::update()
{
    float rx = std::cos(glm::radians(mYaw)) * std::cos(glm::radians(mPitch));
    float ry = std::sin(glm::radians(mPitch));
    float rz = std::sin(glm::radians(mYaw)) * std::cos(glm::radians(mPitch));

    mPosition = mDistance * glm::vec3(rx, ry, rz);
}

const glm::mat4 glh::OrbitCamera::getViewMatrix()  const
{
    return glm::lookAt(mPosition, mTarget, up);
}

const glm::mat4& glh::OrbitCamera::getProjection() const
{
    return mProjection;
}

void glh::OrbitCamera::setProjection(const float fov, const float aspectRatio, const float nearPlane, const float farPlane)
{
    mProjection = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

void glh::OrbitCamera::setProjection(const glm::mat4& projection)
{
    mProjection = projection;
}

const glm::vec3& glh::OrbitCamera::getPosition() const
{
    return mPosition;
}

void glh::OrbitCamera::setDistance(const float x, const float y, const float z)
{
    setDistance(glm::vec3(x, y, z));
}

const glm::vec3& glh::OrbitCamera::getDistance() const
{
    return mDistance;
}

void glh::OrbitCamera::setDistance(const glm::vec3& distance)
{
    mDistance = distance;
    update();
}

const glm::vec3& glh::OrbitCamera::getTarget() const
{
    return mTarget;
}

void glh::OrbitCamera::setTarget(const glm::vec3& target)
{
    mTarget = target;
    update();
}

void glh::OrbitCamera::setTarget(const float x, const float y, const float z)
{
    setTarget(glm::vec3(x, y, z));
}

void glh::OrbitCamera::setMouseSensitivity(const float sensitivity)
{
    mMouseSensitivity = sensitivity;
}

void glh::OrbitCamera::setMoveSpeed(const float speed)
{
    mMoveSpeed = speed;
}

const float glh::OrbitCamera::getMaxMouseDelta()
{
    return mMaxMouseDelta;
}

void glh::OrbitCamera::setMaxMouseDelta(const float delta)
{
    mMaxMouseDelta = delta;
}

const float glh::OrbitCamera::getYaw() const
{
    return mYaw;
}

void glh::OrbitCamera::setYaw(const float yaw)
{
    mYaw = constraintYaw(yaw);
    update();
}

const float glh::OrbitCamera::getPitch() const
{
    return mPitch;
}
void glh::OrbitCamera::setPitch(const float pitch)
{
    mPitch = constraintPitch(pitch);
    update();
}

float glh::OrbitCamera::constraintYaw(const float yaw)
{
    float v = yaw;
    if(v > 360.f) {
        v = 0.f;
    } else if(v < 0.f) {
        v = 360.f;
    }
    
    return v;
}
float glh::OrbitCamera::constraintPitch(const float pitch)
{
    float v = pitch;
    if(v > 89.f) {
        v = 89.f;
    } else  if(v < -89.f) {
        v = -89.f;
    }
    
    return v;
}
