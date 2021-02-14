#ifndef PATHCAMERA_HPP
#define PATHCAMERA_HPP

#include <glm/glm.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

namespace glh
{

class PathCamera
{
public:
    PathCamera();
    ~PathCamera();
    
    void update(const float dt);
    const glm::mat4 getViewMatrix() const;
    
    const glm::mat4& getProjection() const;
    void setProjection(const float fov, const float aspectRatio, const float nearPlane, const float farPlane);
    void setProjection(const glm::mat4& projection);

    const glm::vec3& getPosition() const;
    void setPosition(const glm::vec3& position);
    void setPosition(const float x, const float y, const float z);

    const glm::vec3& getDestination() const;
    void setDestination(const glm::vec3& destination);
    void setDestination(const float x, const float y, const float z);
    void addDestination(const glm::vec3& destination);
    
    const glm::vec3& getTarget() const;
    void setTarget(const glm::vec3& target);
    void setTarget(const float x, const float y, const float z);
    
    const float getVelocity() const;
    void setVelocity(const float velocity);

private:
    const glm::vec3 up;
    glm::mat4 mProjection;
    glm::vec3 mPosition;
    glm::vec3 mDestination;
    glm::vec3 mTarget;
    float mVelocity;
    float mMinDist;
    std::size_t indexDest;
    
    std::vector<glm::vec3> destinations;

};

}

#endif // PATHCAMERA_HPP
