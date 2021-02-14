#ifndef CONTEXT_HPP
#define CONTEXT_HPP

namespace glh
{

class Context
{
public:
    Context();
    ~Context();
    
    const unsigned int getDepthBits() const;
    void setDepthBits(const unsigned int depthBits);
    
    const unsigned int getStencilBits() const;
    void setStencilBits(const unsigned int stencilBits);
    
    const unsigned int getOpenGLMajorVersion() const;
    void setOpenGLMajorVersion(const unsigned int openGLMajorVersion);
    
    const unsigned int getOpenGLMinorVersion() const;
    void setOpenGLMinorVersion(const unsigned int openGLMinorVersion);
    
    const unsigned int getAntialiasingLevel() const;
    void setAntialiasingLevel(const unsigned int antialiasingLevel);
    
    const bool getDebug() const;
    void setDebug(const bool debug);
    
    const unsigned int getWindowWidth() const;
    void setWindowWidth(const unsigned int windowWidth);
    
    const unsigned int getWindowHeight() const;
    void setWindowHeight(const unsigned int windowHeight);

private:
    unsigned int mDepthBits;
    unsigned int mStencilBits;
    unsigned int mOpenGLMajorVersion;
    unsigned int mOpenGLMinorVersion;
    unsigned int mAntialiasingLevel;
    bool mDebug;
    unsigned int mWindowWidth;
    unsigned int mWindowHeight;

};

}

#endif // CONTEXT_HPP
