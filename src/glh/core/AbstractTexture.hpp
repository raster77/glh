#ifndef ABSTRACTTEXTURE_HPP
#define ABSTRACTTEXTURE_HPP

#include "GlObject.hpp" // Base class: glh::GlObject
#include <glad/glad.h>

namespace glh
{

class AbstractTexture : public glh::GlObject
{
public:
    AbstractTexture();
    virtual ~AbstractTexture() = 0;

    void bind() final;
    void unbind() final;
    void create() final;
    void destroy() final;
    void bindTextureUnit();
    
    void setParameter(const GLenum property, const int value);
    void setParameter(const GLenum property, const float value);
    const GLenum getTextureUnit() const;
    void setTextureUnit(const GLenum textureUnit) ;
    const int getWidth() const;
    const int getHeight() const;
    const GLenum getTarget() const;

protected:
    GLenum mTextureUnit;
    GLenum mTarget;
    GLenum mInternalFormat;
    int mWidth;
    int mHeight;
};

}

#endif // ABSTRACTTEXTURE_HPP
