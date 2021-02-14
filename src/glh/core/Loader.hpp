#ifndef LOADER_HPP
#define LOADER_HPP

#include <glad/glad.c>
#include <string>

namespace glad
{
static bool loaded = false;

const bool isLoaded()
{
    return loaded;
}

bool load()
{
    if(!loaded) {
        loaded = gladLoadGL();
        return loaded;
    } else
        return true;
}

std::string getOpenGLVersion()
{
    return std::to_string(GLVersion.major) + "." + std::to_string(GLVersion.minor);
}

const int getMajorVersion() {
    return GLVersion.major;
}

const int getMinorVersion() {
    return GLVersion.minor;
}

}

#endif // LOADER_HPP
