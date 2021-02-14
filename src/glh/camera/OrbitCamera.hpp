#ifndef ORBITCAMERA_HPP
#define ORBITCAMERA_HPP

#include <glm/glm.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace glh
{

class OrbitCamera
{
public:
    OrbitCamera();
    ~OrbitCamera();

    void mouseMove(const float x, const float y);
    void mouseWheel(const float offset);
    const glm::mat4 getViewMatrix() const;

    void setMouseSensitivity(const float sensitivity);
    void setMoveSpeed(const float speed);
    
    const float getYaw() const;
    void setYaw(const float yaw);

    const float getPitch() const;
    void setPitch(const float pitch);

    const float getMaxMouseDelta();
    void setMaxMouseDelta(const float delta);

    const glm::mat4& getProjection() const;
    void setProjection(const float fov, const float aspectRatio, const float nearPlane, const float farPlane);
    void setProjection(const glm::mat4& projection);

    const glm::vec3& getDistance() const;
    void setDistance(const glm::vec3& position);
    void setDistance(const float x, const float y, const float z);

    const glm::vec3& getPosition() const;

    const glm::vec3& getTarget() const;
    void setTarget(const glm::vec3& target);
    void setTarget(const float x, const float y, const float z);

private:
    const glm::vec3 up;
    glm::mat4 mProjection;
    glm::vec3 mPosition;
    glm::vec3 mDistance;
    glm::vec3 mTarget;

    glm::vec2 mousePos;
    glm::vec2 oldMousePos;
    float mMaxMouseDelta;

    float mYaw;
    float mPitch;
    float distance;

    float mMoveSpeed;
    float mMouseSensitivity;
    
    void update();
    float constraintYaw(const float yaw);
    float constraintPitch(const float pitch);

};

}

#endif // ORBITCAMERA_HPP
