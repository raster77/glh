#ifndef CONE_HPP
#define CONE_HPP

#include "Primitive.hpp" // Base class: glh::primitive::Primitive

namespace glh
{

namespace primitive
{

    class Cone : public glh::primitive::Primitive
    {
    public:
        Cone();
        ~Cone();

        void create(const float radiusBottom = 1.f,
            const float height = 1.f,
            const std::size_t radialSegments = 16,
            const std::size_t heightSegments = 1,
            const float thetaStart = 0.f,
            const float thetaLength = 6.28318530718f);
    };
}
}

#endif // CONE_HPP
