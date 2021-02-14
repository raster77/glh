#ifndef FPSCAMERA_HPP
#define FPSCAMERA_HPP

#include <vector>
#include <glm/glm.hpp>
#include <glm/detail/type_vec2.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace glh
{

class FpsCamera
{
public:
    enum Movement { Forward, Backward, Left, Right };

    FpsCamera();
    ~FpsCamera();

    glm::mat4 getViewMatrix();
    void mouseMove(float x, float y, bool constrainPitch = true);
    void mouseScroll(float offset);

    void setMouseSensitivity(const float sensitivity);
    void setMoveSpeed(const float speed);

    const float getMaxMouseDelta();
    void setMaxMouseDelta(const float delta);

    const float getZoom();
    void setZoom(const float zoom);

    const float getYaw();
    void setYaw(const float yaw);

    const float getPitch();
    void setPitch(const float pitch);

    const glm::vec3& getPosition();
    void setPosition(const glm::vec3& position);
    void setPosition(const float x, const float y, const float z);

    const glm::vec3& getFront();
    void setFront(const glm::vec3& front);

    const glm::vec3& getUp();
    void setUp(const glm::vec3& up);

    const glm::vec3& getRight();
    void setRight(const glm::vec3& right);

    const glm::vec3& getWorldUp();
    void setWorldUp(const glm::vec3& worldUp);

    void moveForward(const float deltaTime);
    void moveBackward(const float deltaTime);
    void moveLeft(const float deltaTime);
    void moveRight(const float deltaTime);

private:
    // FpsCamera Attributes
    glm::vec3 mPosition;
    glm::vec3 mFront;
    glm::vec3 mUp;
    glm::vec3 mRight;
    glm::vec3 mWorldUp;
    glm::vec2 mousePos;
    glm::vec2 oldMousePos;
    float mMaxMouseDelta;
    // Eular Angles
    float mYaw;
    float mPitch;
    // FpsCamera options
    float mMoveSpeed;
    float mMouseSensitivity;
    float mZoom;

    void updateVectors();
};
}

#endif // FPSCAMERA_HPP
