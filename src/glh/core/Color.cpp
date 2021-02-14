#include "Color.hpp"

glh::Color::Color()
    : mRed(1)
    , mGreen(1)
    , mBlue(1)
    , mAlpha(1)
{
}

glh::Color::Color(const unsigned char red, const unsigned char green, const unsigned char blue, const unsigned char alpha)
    : mRed(red)
    , mGreen(green)
    , mBlue(blue)
    , mAlpha(alpha)
{
}

glh::Color::Color(const float red, const float green, const float blue, const float alpha)
    : mRed(red * 255)
    , mGreen(green * 255)
    , mBlue(blue * 255)
    , mAlpha(alpha * 255)
{
}

glh::Color::~Color()
{
}

const unsigned char glh::Color::getRed() const
{
    return mRed;
}

void glh::Color::setRed(const unsigned char red)
{
    mRed = red;
}

const unsigned char glh::Color::getGreen() const
{
    return mGreen;
}

void glh::Color::setGreen(const unsigned char green)
{
    mGreen = green;
}

const unsigned char glh::Color::getBlue() const
{
    return mBlue;
}

void glh::Color::setBlue(const unsigned char blue)
{
    mBlue = blue;
}

const unsigned char glh::Color::getAlpha() const
{
    return mAlpha;
}

void glh::Color::setAlpha(const unsigned char alpha)
{
    mAlpha = alpha;
}

glm::vec4 glh::Color::getGlColor()
{
    float r = static_cast<float>(mRed) / 255.f;
    float g = static_cast<float>(mGreen) / 255.f;
    float b = static_cast<float>(mBlue) / 255.f;
    float a = static_cast<float>(mAlpha) / 255.f;

    return glm::vec4(r, g, b, a);
}