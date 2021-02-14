#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include "GlObject.hpp" // Base class: glh::GlObject
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <string>

namespace glh
{

class ShaderProgram : public glh::GlObject
{
public:
    ShaderProgram();
    ~ShaderProgram();

    void loadFromMemory(const std::string& memVertexShader, const std::string& memFragShader);
    void loadFromFile(const std::string& vertexShader, const std::string& fragShader);

    GLint getUniform(const std::string& name) const;

    template <typename T>
    void setUniform(const std::string& name, const T& value) const
    {
        setUniform(getUniform, value);
    }

    void setUniform(const std::string& name, const int value) const;
    void setUniform(const std::string& name, const unsigned int value) const;
    void setUniform(const std::string& name, const float value) const;
    void setUniform(const std::string& name, const float v1, const float v2) const;
    void setUniform(const std::string& name, const float v1, const float v2, const float v3) const;
    void setUniform(const std::string& name, const float v1, const float v2, const float v3, const float v4) const;
    void setUniform(const std::string& name, const bool value) const;
    void setUniform(const std::string& name, const glm::vec2& v) const;
    void setUniform(const std::string& name, const glm::vec3& v) const;
    void setUniform(const std::string& name, const glm::vec4& v) const;
    void setUniform(const std::string& name, const glm::mat2& mat2) const;
    void setUniform(const std::string& name, const glm::mat3& mat3) const;
    void setUniform(const std::string& name, const glm::mat4& mat4) const;

    void bind() final;
    void create() final;
    void destroy() final;
    void unbind() final;

private:
    unsigned int loadFromMemory(const std::string& s, GLenum shaderType);
    std::string loadFromFile(const std::string& fileName);
    bool checkCompileErrors(GLuint shader, const std::string& errorType, const bool program = false);
    std::string typeToStr(GLenum shaderType);
    mutable std::map<std::string, GLint> uniformsCache;
    std::vector<unsigned int> uniformBlockIndex;
};
}

#endif // SHADERPROGRAM_HPP
