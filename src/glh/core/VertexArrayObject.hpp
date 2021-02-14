#ifndef VERTEXARRAYOBJECT_HPP
#define VERTEXARRAYOBJECT_HPP

#include "GlObject.hpp" // Base class: glh::GlObject

namespace glh
{

class VertexArrayObject : public glh::GlObject
{
public:
    VertexArrayObject();
    virtual ~VertexArrayObject();

    void bind() final;
    void create() final;
    void destroy() final;
    void unbind() final;

};

}

#endif // VERTEXARRAYOBJECT_HPP
