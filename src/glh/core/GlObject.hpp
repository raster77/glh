#ifndef GLOBJECT_HPP
#define GLOBJECT_HPP

#include <string>

namespace glh
{
/**
 * @class GlObject
 * @author thierry
 * @date 04/08/19
 * @file GlObject.hpp
 * @brief
 *  Abstract class for OpenGL object
 */
class GlObject
{
public:
    GlObject();
    virtual ~GlObject() = 0;

    GlObject(const GlObject&) = delete;
    GlObject& operator = (const GlObject&) = delete;
    GlObject(GlObject&&) = default;
    GlObject& operator = (GlObject&&) = default;

    virtual void create() = 0;
    virtual void destroy() = 0;
    virtual void bind() = 0;
    virtual void unbind() = 0;

    /**
     * @brief get id of object
     * @return unsigned int id
     */
    const unsigned int getId() const;

    /**
     * @brief get id of object as int
     * @return int id
     */
    const int getIdAsInt() const;

protected:

    unsigned int mId;

    /**
     * @brief Check for an OpenGL error
     * @param message
     */
    void checkGlError(const std::string& message);

};
}

#endif // GLOBJECT_HPP
