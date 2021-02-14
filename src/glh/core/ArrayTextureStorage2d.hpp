#ifndef ARRAYTEXTURESTORAGE2D_HPP
#define ARRAYTEXTURESTORAGE2D_HPP

#include "AbstractTexture.hpp" // Base class: glh::AbstractTexture

namespace glh
{

class ArrayTextureStorage2d : public glh::AbstractTexture
{
public:
    ArrayTextureStorage2d();
    ~ArrayTextureStorage2d();

    void create(const int level, const unsigned int width, const unsigned int height, const int depth, const GLenum internalFormat = GL_RGBA8);
    void add(const unsigned int layer, void* data, const GLenum format = GL_RGBA, const GLenum glType = GL_UNSIGNED_BYTE);
    void addFromFile(const unsigned int layer, const std::string fileName, const GLenum format = GL_RGBA, const GLenum glType = GL_UNSIGNED_BYTE);

};

}

#endif // ARRAYTEXTURESTORAGE2D_HPP
