#ifndef CUBE_HPP
#define CUBE_HPP

#include "glh/primitive/Primitive.hpp"
#include <glm/glm.hpp>
#include <vector>

namespace glh
{

namespace primitive
{

    class Cube : public glh::primitive::Primitive
    {
    public:
        Cube();
        ~Cube();

        void create(const glm::vec3& size = glm::vec3(1.f), const glm::ivec3& scale = glm::ivec3(1));
    private:

        std::size_t vertexIndex;

        void makePlane(const float u,
            const float v,
            const float w,
            const float su,
            const float sv,
            const float nu,
            const float nv,
            const float pw,
            const float flipu,
            const float flipv);
    };
}
}

#endif // CUBE_HPP
