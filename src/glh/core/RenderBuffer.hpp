#ifndef RENDERBUFFER_HPP
#define RENDERBUFFER_HPP

#include "AbstractRenderBuffer.hpp" // Base class: glh::AbstractRenderBuffer

namespace glh
{

class RenderBuffer : public glh::AbstractRenderBuffer
{
public:
    RenderBuffer();
    RenderBuffer(const unsigned int width, const unsigned int height);
    RenderBuffer(const unsigned int width, const unsigned int height, const GLenum internatFormat);
    ~RenderBuffer();
    
    void create(const unsigned int width, const unsigned int height, const GLenum internatFormat);
    void create() final;

};

}

#endif // RENDERBUFFER_HPP
