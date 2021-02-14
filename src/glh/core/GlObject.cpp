#include "GlObject.hpp"
#include <glad/glad.h>
#include <iostream>

glh::GlObject::GlObject()
    : mId(0)
{
}

glh::GlObject::~GlObject()
{
}

const unsigned int glh::GlObject::getId() const
{
    return mId;
}

const int glh::GlObject::getIdAsInt() const
{
    return static_cast<int>(mId);
}

void glh::GlObject::checkGlError(const std::string& message)
{
    GLenum error = glGetError();
    while(error != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << error << " - " << message << std::endl;
        error = glGetError();
    }
}