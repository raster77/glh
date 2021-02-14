#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP

#include "AbstractTexture.hpp" // Base class: glh::AbstractTexture
#include <string>

namespace glh
{

class Texture2d : public glh::AbstractTexture
{
public:
    Texture2d();
    ~Texture2d();
    
    void loadFromFile(const std::string& fileName);
    void texture2d(const int width, const int height, const GLenum internalFormat, const GLenum format, const GLenum glType, void* data);
    void generateMipMap();

};

}

#endif // TEXTURE2D_HPP
