#ifndef TORUS_HPP
#define TORUS_HPP

#include "glh/primitive/Primitive.hpp"
#include <glm/glm.hpp>

namespace glh
{

namespace primitive
{

    class Torus : public glh::primitive::Primitive
    {
    public:
        Torus();
        ~Torus();

        void create(const float radius = 1.f,
            const float tubularRadius = 0.4f,
            const std::size_t radialSegments = 16,
            const std::size_t tubularSegments = 16,
            const float arc = 6.28318530718f);
    };
}
}

#endif // TORUS_HPP
