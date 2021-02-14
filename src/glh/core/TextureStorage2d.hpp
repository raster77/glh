#ifndef TEXTURESTORAGE2D_HPP
#define TEXTURESTORAGE2D_HPP

#include "AbstractTexture.hpp" // Base class: glh::AbstractTexture
#include <string>

namespace glh
{

class TextureStorage2d : public glh::AbstractTexture
{
public:
    TextureStorage2d();
    ~TextureStorage2d();

    void loadFromFile(const std::string& fileName);
    void texture2d(const int width,
        const int height,
        const GLenum internalFormat,
        const GLenum format,
        const GLenum glType,
        void* data);
    void generateMipMap();

};
}

#endif // TEXTURESTORAGE2D_HPP
