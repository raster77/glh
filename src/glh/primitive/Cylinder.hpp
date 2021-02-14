#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include "Primitive.hpp" // Base class: glh::primitive::Primitive

namespace glh
{

namespace primitive
{

    class Cylinder : public glh::primitive::Primitive
    {
    public:
        Cylinder();
        ~Cylinder();

        void create(const float radiusTop = 1.f,
            const float radiusBottom = 1.f,
            const float height = 1.f,
            const std::size_t radialSegments = 15,
            const std::size_t heightSegments = 1,
            const bool openEnded = false,
            const float thetaStart = 0.f,
            const float thetaLength = 6.28318530718f);

    private:
        float radiusTop;
        float radiusBottom;
        float height;
        float halfHeight;
        float thetaStart;
        float thetaLength;
        std::size_t index;
        std::size_t radialSegments;
        std::size_t heightSegments;
        void generateCap(const bool top);
    };
}
}

#endif // CYLINDER_HPP
