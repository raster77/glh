#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Primitive.hpp" // Base class: glh::primitive::Primitive

namespace glh
{

namespace primitive
{

    class Sphere : public glh::primitive::Primitive
    {
    public:
        Sphere();
        ~Sphere();
        
        void create(const float radius = 1.f, const std::size_t xSegments = 16, const std::size_t ySegments = 16);
    };
}
}

#endif // SPHERE_HPP
