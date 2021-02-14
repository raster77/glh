#ifndef COLOR_HPP
#define COLOR_HPP

#include <glm/glm.hpp>
#include <glm/vec4.hpp>

namespace glh
{

class Color
{
public:
    Color();
    Color(const unsigned char red, const unsigned char green, const unsigned char blue, const unsigned char alpha);
    Color(const float red, const float green, const float blue, const float alpha);
    ~Color();
    
    const unsigned char getRed() const;
    void setRed(const unsigned char red);
    
    const unsigned char getGreen() const;
    void setGreen(const unsigned char green);
    
    const unsigned char getBlue() const;
    void setBlue(const unsigned char blue);
    
    const unsigned char getAlpha() const;
    void setAlpha(const unsigned char alpha);
    
    glm::vec4 getGlColor();

private:
    unsigned char mRed;
    unsigned char mGreen;
    unsigned char mBlue;
    unsigned char mAlpha;

};

}

#endif // COLOR_HPP
