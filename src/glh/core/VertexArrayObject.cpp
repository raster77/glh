#include "VertexArrayObject.hpp"
#include <glad/glad.h>

glh::VertexArrayObject::VertexArrayObject()
    : GlObject()
{
}

glh::VertexArrayObject::~VertexArrayObject()
{
    destroy();
}

void glh::VertexArrayObject::bind()
{
    glBindVertexArray(mId);
}
void glh::VertexArrayObject::create()
{
    if(mId == 0) {
        glGenVertexArrays(1, &mId);
    }
    bind();
}
void glh::VertexArrayObject::destroy()
{
    if(mId > 0) {
        glDeleteVertexArrays(1, &mId);
        mId = 0;
    }
}
void glh::VertexArrayObject::unbind()
{
    glBindVertexArray(0);
}
