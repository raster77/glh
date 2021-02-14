#include "FpsCamera.hpp"
#include <glm/glm.hpp>


glh::FpsCamera::FpsCamera()
    : mPosition(0.f, 0.f, 0.f)
    , mFront(0.f, 0.f, -1.f)
    , mWorldUp(0.f, 1.f, 0.f)
    , oldMousePos(0.f)
    , mMaxMouseDelta(10.f)
    , mYaw(-90.f)
    , mPitch(0.f)
    , mMoveSpeed(2.5f)
    , mMouseSensitivity(0.25f)
    , mZoom(45.f)
{
    updateVectors();
}

glh::FpsCamera::~FpsCamera()
{
}

glm::mat4 glh::FpsCamera::getViewMatrix()
{
    return glm::lookAt(mPosition, mPosition + mFront, mUp);
}

void glh::FpsCamera::mouseMove(float x, float y, bool constrainPitch)
{
    mousePos = glm::vec2(x, y);

    float xoffset = (mousePos.x - oldMousePos.x);
    float yoffset = (oldMousePos.y - mousePos.y);

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

    // mYaw += xoffset;
    mYaw = glm::mod(mYaw + xoffset, 360.0f);
    mPitch += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if(constrainPitch) {
        if(mPitch > 89.0f)
            mPitch = 89.0f;
        if(mPitch < -89.0f)
            mPitch = -89.0f;
    }

    oldMousePos = mousePos;

    // Update Front, Right and Up Vectors using the updated Eular angles
    updateVectors();
}

void glh::FpsCamera::mouseScroll(float offset)
{
    mZoom += offset;
    if(mZoom <= 1.f)
        mZoom = 1.f;
    if(mZoom >= 45.f)
        mZoom = 45.f;
}

void glh::FpsCamera::moveForward(const float deltaTime)
{
    mPosition += mFront * (mMoveSpeed * deltaTime);
}

void glh::FpsCamera::moveBackward(const float deltaTime)
{
    mPosition -= mFront * (mMoveSpeed * deltaTime);
}

void glh::FpsCamera::moveLeft(const float deltaTime)
{
    mPosition -= mRight * (mMoveSpeed * deltaTime);
}

void glh::FpsCamera::moveRight(const float deltaTime)
{
    mPosition += mRight * (mMoveSpeed * deltaTime);
}

void glh::FpsCamera::setMouseSensitivity(const float sensitivity)
{
    mMouseSensitivity = sensitivity;
}

void glh::FpsCamera::setMoveSpeed(const float speed)
{
    mMoveSpeed = speed;
}

const float glh::FpsCamera::getMaxMouseDelta()
{
    return mMaxMouseDelta;
}

void glh::FpsCamera::setMaxMouseDelta(const float delta)
{
    mMaxMouseDelta = delta;
}

const float glh::FpsCamera::getZoom()
{
    return mZoom;
}

void glh::FpsCamera::setZoom(const float zoom)
{
    mZoom = zoom;
    updateVectors();
}

const float glh::FpsCamera::getYaw()
{
    return mYaw;
}

void glh::FpsCamera::setYaw(const float yaw)
{
    mYaw = yaw;
    updateVectors();
}

const float glh::FpsCamera::getPitch()
{
    return mPitch;
}

void glh::FpsCamera::setPitch(const float pitch)
{
    mPitch = pitch;
    updateVectors();
}

const glm::vec3& glh::FpsCamera::getPosition()
{
    return mPosition;
}

void glh::FpsCamera::setPosition(const glm::vec3& position)
{
    mPosition = position;
    updateVectors();
}

void glh::FpsCamera::setPosition(const float x, const float y, const float z)
{
    setPosition(glm::vec3(x, y, z));
}

const glm::vec3& glh::FpsCamera::getFront()
{
    return mFront;
}

void glh::FpsCamera::setFront(const glm::vec3& front)
{
    mFront = front;
}

const glm::vec3& glh::FpsCamera::getUp()
{
    return mUp;
}

void glh::FpsCamera::setUp(const glm::vec3& up)
{
    mUp = up;
}

const glm::vec3& glh::FpsCamera::getRight()
{
    return mRight;
}

void glh::FpsCamera::setRight(const glm::vec3& right)
{
    mRight = right;
}

const glm::vec3& glh::FpsCamera::getWorldUp()
{
    return mWorldUp;
}

void glh::FpsCamera::setWorldUp(const glm::vec3& worldUp)
{
    mWorldUp = worldUp;
}

void glh::FpsCamera::updateVectors()
{
    // Calculate the new Front vector
    glm::vec3 front;
    front.x = std::cos(glm::radians(mYaw)) * std::cos(glm::radians(mPitch));
    front.y = std::sin(glm::radians(mPitch));
    front.z = std::sin(glm::radians(mYaw)) * std::cos(glm::radians(mPitch));
    mFront = glm::normalize(front);
    // Also re-calculate the Right and Up vector
    mRight = glm::normalize(glm::cross(mFront, mWorldUp));
    mUp = glm::normalize(glm::cross(mRight, mFront));
}
