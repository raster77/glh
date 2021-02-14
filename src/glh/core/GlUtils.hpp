#ifndef GLUTILS_HPP
#define GLUTILS_HPP

#include <glad/glad.h>
#include <iostream>
#include <string>

namespace glh
{

void checkGlError(const std::string& message)
{
    GLenum error = glGetError();
    while(error != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << error << " - " << message << std::endl;
        error = glGetError();
    }
}

void debugCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    GLchar const* message,
    void const* user_param)
{
    
    if(id == 131185) {
        return;
    }
    
    std::string msgSource;
    switch(source) {
    case GL_DEBUG_SOURCE_API:
        msgSource = "WINDOW_SYSTEM";
        break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        msgSource = "SHADER_COMPILER";
        break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        msgSource = "THIRD_PARTY";
        break;
    case GL_DEBUG_SOURCE_APPLICATION:
        msgSource = "APPLICATION";
        break;
    case GL_DEBUG_SOURCE_OTHER:
        msgSource = "OTHER";
        break;
    }

    std::string msgType;
    switch(type) {
    case GL_DEBUG_TYPE_ERROR:
        msgType = "ERROR";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        msgType = "DEPRECATED_BEHAVIOR";
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        msgType = "UNDEFINED_BEHAVIOR";
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        msgType = "PORTABILITY";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        msgType = "PERFORMANCE";
        break;
    case GL_DEBUG_TYPE_OTHER:
        msgType = "OTHER";
        break;
    }

    std::string msgSeverity;
    switch(severity) {
    case GL_DEBUG_SEVERITY_LOW:
        msgSeverity = "LOW";
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        msgSeverity = "MEDIUM";
        break;
    case GL_DEBUG_SEVERITY_HIGH:
        msgSeverity = "HIGH";
        break;
    }

    std::cout << msgSource << ", " << msgType << ", " << msgSeverity << ", " << id << ": " << message << std::endl;
}
}

#endif // GLUTILS_HPP
