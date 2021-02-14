#include "Plane.hpp"

glh::primitive::Plane::Plane()
    :   Primitive()
    , mSizeX(1.f)
    , mSizeY(1.f)
    , mScaleX(1)
    , mScaleY(1)
{
}

glh::primitive::Plane::~Plane()
{
}

void glh::primitive::Plane::create()
{
    mPositions.clear();
    mNormals.clear();
    mUvs.clear();
    mIndices.clear();

    for(std::size_t iy = 0; iy <= mScaleY; iy++) {
        for(std::size_t ix = 0; ix <= mScaleX; ix++) {
            std::size_t u = ix / mScaleX;
            std::size_t v = iy / mScaleY;
            float x = -mSizeX * 0.5f + u * mSizeX; // starts on the left
            float y = mSizeY * 0.5f - v * mSizeY;  // starts at the top

            mPositions.emplace_back(x);
            mPositions.emplace_back(y);
            mPositions.emplace_back(0.f);

            mNormals.emplace_back(0.f);
            mNormals.emplace_back(0.f);
            mNormals.emplace_back(1.f);

            mUvs.emplace_back(u * mScaleX);
            mUvs.emplace_back((1.f - v) * mScaleY);

            if(iy < mScaleY && ix < mScaleX) {
                mIndices.emplace_back(iy * (mScaleX + 1) + ix);
                mIndices.emplace_back((iy + 1) * (mScaleX + 1) + ix + 1);
                mIndices.emplace_back(iy * (mScaleX + 1) + ix + 1);
                mIndices.emplace_back((iy + 1) * (mScaleX + 1) + ix + 1);
                mIndices.emplace_back(iy * (mScaleX + 1) + ix);
                mIndices.emplace_back((iy + 1) * (mScaleX + 1) + ix);
            }
        }
    }
}

void glh::primitive::Plane::setSize(const float x, const float y)
{
    mSizeX = x;
    mSizeY = y;
}

void glh::primitive::Plane::setSizeX(const float x)
{
    mSizeX = x;
}
const float glh::primitive::Plane::getSizeX() const
{
    return mSizeX;
}
void glh::primitive::Plane::setSizeY(const float y)
{
    mSizeY = y;
}
const float glh::primitive::Plane::getSizeY() const
{
    return mSizeY;
}

void glh::primitive::Plane::setScale(const std::size_t x, const std::size_t y)
{
    mScaleX = x;
    mScaleY = y;
}
void glh::primitive::Plane::setScaleX(const std::size_t x)
{
    mScaleX = x;
}
const std::size_t glh::primitive::Plane::getScaleX() const
{
    return mScaleX;
}
void glh::primitive::Plane::setScaleY(const std::size_t y)
{
    mScaleY = y;
}
const std::size_t glh::primitive::Plane::getScaleY() const
{
    return mScaleY;
}