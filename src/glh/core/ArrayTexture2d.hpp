#ifndef ARRAYTEXTURE2D_HPP
#define ARRAYTEXTURE2D_HPP

#include "AbstractTexture.hpp" // Base class: glh::AbstractTexture

namespace glh
{

class ArrayTexture2d : public glh::AbstractTexture
{
public:
    ArrayTexture2d();
    ~ArrayTexture2d();
              
    void create(const unsigned int width, const unsigned int height, const unsigned int layers, const GLint internalFormat = GL_RGB, const GLenum format = GL_RGB, const GLenum glType = GL_UNSIGNED_BYTE);

    void add(const unsigned int layer, void* data, const GLenum format = GL_RGBA, const GLenum glType = GL_UNSIGNED_BYTE);
    void addFromFile(const unsigned int layer, const std::string fileName, const GLenum format = GL_RGBA, const GLenum glType = GL_UNSIGNED_BYTE);
    void generateMipMap();
};

}

#endif // ARRAYTEXTURESTORAGE2D_HPP
