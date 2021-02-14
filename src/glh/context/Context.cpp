#include "Context.hpp"

glh::Context::Context()
    : mDepthBits(24)
    , mStencilBits(8)
    , mOpenGLMajorVersion(4)
    , mOpenGLMinorVersion(3)
    , mAntialiasingLevel(0)
    , mDebug(true)
    , mWindowWidth(1280)
    , mWindowHeight(720)
{
}

glh::Context::~Context()
{
}

    const unsigned int glh::Context::getDepthBits() const
    {
        return mDepthBits;
    }
    
    void glh::Context::setDepthBits(const unsigned int depthBits)
    {
        mDepthBits = depthBits;
    }
    
    const unsigned int glh::Context::getStencilBits() const
    {
        return mStencilBits;
    }
    
    void glh::Context::setStencilBits(const unsigned int stencilBits)
    {
        mStencilBits = stencilBits;
    }
    
    const unsigned int glh::Context::getOpenGLMajorVersion() const
    {
        return mOpenGLMajorVersion;
    }
    
    void glh::Context::setOpenGLMajorVersion(const unsigned int openGLMajorVersion)
    {
        mOpenGLMajorVersion = openGLMajorVersion;
    }
    
    const unsigned int glh::Context::getOpenGLMinorVersion() const
    {
        return mOpenGLMinorVersion;
    }
    
    void glh::Context::setOpenGLMinorVersion(const unsigned int openGLMinorVersion)
    {
        mOpenGLMinorVersion = openGLMinorVersion;
    }
    
    const unsigned int glh::Context::getAntialiasingLevel() const
    {
        return mAntialiasingLevel;
    }
    
    void glh::Context::setAntialiasingLevel(const unsigned int antialiasingLevel)
    {
        mAntialiasingLevel = antialiasingLevel;
    }
    
    const bool glh::Context::getDebug() const
    {
        return mDebug;
    }
    
    void glh::Context::setDebug(const bool debug)
    {
        mDebug = debug;
    }
    
    const unsigned int glh::Context::getWindowWidth() const
    {
        return mWindowWidth;
    }
    
    void glh::Context::setWindowWidth(const unsigned int windowWidth)
    {
        mWindowWidth = windowWidth;
    }
    
    const unsigned int glh::Context::getWindowHeight() const
    {
        return mWindowHeight;
    }
    
    void glh::Context::setWindowHeight(const unsigned int windowHeight)
    {
        mWindowHeight = windowHeight;
    }
