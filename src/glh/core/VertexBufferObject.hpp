#ifndef VERTEXBUFFEROBJECT_HPP
#define VERTEXBUFFEROBJECT_HPP

#include "GlObject.hpp" // Base class: glh::GlObject
#include <glad/glad.h>
#include <array>
#include <vector>

namespace glh
{

class VertexBufferObject : public glh::GlObject
{
public:
    VertexBufferObject();
    VertexBufferObject(GLenum target, GLenum usage);
    ~VertexBufferObject();

    void create(GLenum target, GLenum usage);
    void setTargetAndUsage(GLenum target, GLenum usage);
    void setTarget(GLenum target);
    const GLenum getTarget() const ;
    void setUsage(GLenum usage);
    const GLenum getUsage() const ;

    void setData(const void* data, const unsigned int size);

    template <typename T>
    void setData(const T& data)
    {
        setData(&data, static_cast<unsigned int>(sizeof(T)));
    }

    template <typename T>
    void setData(const std::vector<T>& data)
    {
        setData(&data.front(), static_cast<unsigned int>(data.size() * sizeof(T)));
    }

    template <typename T, std::size_t Count>
    void setData(const std::array<T, Count>& data)
    {
        setData(&data.front(), static_cast<unsigned int>(Count * sizeof(T)));
    }

    void setSubData(const unsigned int offset, const unsigned int size, const void* data);

    template <typename T> void setSubData(const unsigned int offset, const T& data)
    {
        setSubData(offset, static_cast<unsigned int>(sizeof(T)), &data);
    }

    template <typename T> void setSubData(const unsigned int offset, const std::vector<T>& data)
    {
        setSubData(offset, static_cast<unsigned int>(data.size() * sizeof(T)), &data.front());
    }

    template <typename T, std::size_t Count>
    void setSubData(const unsigned int offset, const std::array<T, Count>& data)
    {
        setSubData(offset, static_cast<unsigned int>(Count * sizeof(T)), &data.front());
    }
    
    void* mapBufferRange(const unsigned int offset, const unsigned int length, GLenum access);

    void bind() final;
    void bindRange(unsigned int index, unsigned int offset, unsigned int size);
    void create() final;
    void destroy() final;
    void unbind() final;

private:
    GLenum mTarget;
    GLenum mUsage;
};

}

#endif // VERTEXBUFFEROBJECT_HPP
