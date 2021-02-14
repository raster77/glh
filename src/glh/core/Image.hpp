#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "Color.hpp"
#include <string>
#include <vector>

namespace glh
{

class Image
{
public:
    enum Format { DDS, PNG, JPG };

    Image();
    ~Image();

    void create(const int width, const int height, glh::Color color);
    bool loadFromFile(const std::string& fileName);
    bool saveToFile(const std::string& fileName);
    const std::vector<unsigned char>& getPixels() const;
    unsigned char* getPixelsPtr();

    glh::Color getPixel(const int x, const int y);
    void setPixel(unsigned int x, unsigned int y, const glh::Color& color);
    void setPixel(std::vector<unsigned char>& pixels);
    void flipHorizontally();
    void flipVertically();
    const int& getWidth() const;
    const int& getHeight() const;
    const int& getChannels() const;

private:
    int mWidth;
    int mHeight;
    int mChannels;
    std::vector<unsigned char> mPixels;
    std::string getExtension(const std::string& fileName);
    std::string getFileSignature(const std::string& fileName);
    const std::string PNG_SIG = "89504e47";
    const std::string DDS_SIG = "44445320";
    const std::string JPG_SIG = "ffd8ffe0";
};
}
#endif // IMAGE_HPP
