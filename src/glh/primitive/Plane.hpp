#ifndef PLANE_HPP
#define PLANE_HPP

#include "glh/primitive/Primitive.hpp"
#include <glm/glm.hpp>
#include <vector>

/*
     model = glm::rotate(model, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f));
 */

namespace glh
{

namespace primitive
{

    class Plane : public glh::primitive::Primitive
    {
    public:
        Plane();
        ~Plane();

        void create();
        
        void setSize(const float x, const float y);
        void setSizeX(const float x);
        const float getSizeX() const;
        void setSizeY(const float y);
        const float getSizeY() const;
        
        void setScale(const std::size_t x, const std::size_t y);
        void setScaleX(const std::size_t x);
        const std::size_t getScaleX() const;
        void setScaleY(const std::size_t y);
        const std::size_t getScaleY() const;

    private:
        float mSizeX;
        float mSizeY;
        std::size_t mScaleX;
        std::size_t mScaleY;
    };
}
}

#endif // PLANE_HPP
