#ifndef CAPSULE_HPP
#define CAPSULE_HPP

#include "glh/primitive/Primitive.hpp"
#include <glm/glm.hpp>

namespace glh
{

namespace primitive
{

    class Capsule : public glh::primitive::Primitive
    {
    public:
        Capsule();
        ~Capsule();

        void create(const float radius = 0.5f,
            const float height = 1.f,
            const std::size_t numSubdivisionsHeight = 12,
            const std::size_t numSegments = 12);

    private:
        void calculateRing(const std::size_t segments, const float radius, const float height, const float r, const float y, const float dy);
    };
}
}

#endif // CAPSULE_HPP
