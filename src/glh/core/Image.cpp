#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "Image.hpp"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <sstream>

glh::Image::Image()
    : mWidth(0)
    , mHeight(0)
    , mChannels(0)
{
}

glh::Image::~Image()
{
}

void glh::Image::create(const int width, const int height, Color color)
{
    mWidth = width;
    mHeight = height;
    mPixels.clear();
    mPixels.resize(width * height * 4);
    std::size_t i = 0;
    while(i < mPixels.size()) {
        mPixels[i] = color.getRed();
        mPixels[i + 1] = color.getGreen();
        mPixels[i + 2] = color.getBlue();
        mPixels[i + 3] = color.getAlpha();
        i += 4;
    }
}

bool glh::Image::loadFromFile(const std::string& fileName)
{
    mPixels.clear();

    int width = 0;
    int height = 0;
    int channels = 0;

    mPixels.clear();
//    stbi_set_flip_vertically_on_load(true);
    unsigned char* datas = stbi_load(fileName.c_str(), &width, &height, &channels, STBI_rgb_alpha);

    if(datas) {
        mWidth = width;
        mHeight = height;
        mChannels = channels;

        if(mWidth && mHeight) {
            mPixels.resize(mWidth * mHeight * 4);
            std::memcpy(&mPixels.front(), datas, mPixels.size());
        }
        stbi_image_free(datas);
        return true;
    }
    return false;
}

bool glh::Image::saveToFile(const std::string& fileName)
{
    std::string ext = getExtension(fileName);

    if(!mPixels.empty() && (mWidth > 0) && (mHeight > 0)) {

        if(ext == "png")
            if(stbi_write_png(fileName.c_str(), mWidth, mHeight, 4, &mPixels[0], 0))
                return true;

        if(ext == "jpg" || ext == "jpeg")
            if(stbi_write_jpg(fileName.c_str(), mWidth, mHeight, 4, &mPixels[0], 90))
                return true;

        if(ext == "bmp")
            if(stbi_write_bmp(fileName.c_str(), mWidth, mHeight, 4, &mPixels[0]))
                return true;

        if(ext == "tga")
            if(stbi_write_tga(fileName.c_str(), mWidth, mHeight, 4, &mPixels[0]))
                return true;
    }
    return false;
}

const std::vector<unsigned char>& glh::Image::getPixels() const
{
    return mPixels;
}

unsigned char* glh::Image::getPixelsPtr()
{
    if (!mPixels.empty())
        return &mPixels[0];
    else
        return nullptr;
}

void glh::Image::setPixel(unsigned int x, unsigned int y, const glh::Color& color)
{
    unsigned char* pixel = &mPixels[(x + y * mWidth) * 4];
    *pixel++ = color.getRed();
    *pixel++ = color.getGreen();
    *pixel++ = color.getBlue();
    *pixel++ = color.getAlpha();
}

void glh::Image::setPixel(std::vector<unsigned char>& pixels)
{
    mPixels.clear();
    mPixels = pixels;
}


glh::Color glh::Image::getPixel(const int x, const int y)
{
    unsigned char* pixel = &mPixels[(x + y * mWidth) * 4];
    return glh::Color(pixel[0], pixel[1], pixel[2], pixel[3]);
}

void glh::Image::flipHorizontally()
{
    if (!mPixels.empty()) {
        int rowSize = mWidth * 4;

        for (int y = 0; y < mHeight; ++y) {
            std::vector<unsigned char>::iterator left = mPixels.begin() + y * rowSize;
            std::vector<unsigned char>::iterator right = mPixels.begin() + (y + 1) * rowSize - 4;

            for (int x = 0; x < mWidth / 2; ++x) {
                std::swap_ranges(left, left + 4, right);

                left += 4;
                right -= 4;
            }
        }
    }
}

void glh::Image::flipVertically()
{
    if (!mPixels.empty()) {
        int rowSize = mWidth * 4;

        std::vector<unsigned char>::iterator top = mPixels.begin();
        std::vector<unsigned char>::iterator bottom = mPixels.end() - rowSize;

        for (int y = 0; y < mHeight / 2; ++y) {
            std::swap_ranges(top, top + rowSize, bottom);

            top += rowSize;
            bottom -= rowSize;
        }
    }
}

const int& glh::Image::getWidth() const
{
    return mWidth;
}

const int& glh::Image::getHeight() const
{
    return mHeight;
}

const int& glh::Image::getChannels() const
{
    return mChannels;
}

std::string glh::Image::getExtension(const std::string& fileName)
{
    std::string str = fileName;
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    std::size_t dot = str.find_last_of('.');
    std::string ext = dot != std::string::npos ? str.substr(dot + 1) : "";

    return ext;
}

std::string glh::Image::getFileSignature(const std::string& fileName)
{
    std::ifstream in(fileName, std::ios::binary);
    std::string signature = "";
    if(in.good()) {
        in.seekg(0, std::ios::beg);
        unsigned char magic[4] = { 0 };
        in.read(reinterpret_cast<char*>(magic), sizeof(magic));
        in.close();
        std::stringstream ss;
        for(int i = 0; i < 4; ++i)
            ss << std::hex << (int)magic[i];
        signature = ss.str();
    }
    
    return signature;
}
