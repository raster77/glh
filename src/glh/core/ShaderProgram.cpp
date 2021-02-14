#include "ShaderProgram.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <vector>

glh::ShaderProgram::ShaderProgram()
    : GlObject()
{
}

glh::ShaderProgram::~ShaderProgram()
{
    destroy();
}

void glh::ShaderProgram::loadFromMemory(const std::string& memVertexShader, const std::string& memFragShader)
{

    unsigned int vertexShader = 0;
    unsigned int fragmentShader = 0;

    if(!memVertexShader.empty())
        vertexShader = loadFromMemory(memVertexShader, GL_VERTEX_SHADER);

    if(!memFragShader.empty())
        fragmentShader = loadFromMemory(memFragShader, GL_FRAGMENT_SHADER);

    mId = glCreateProgram();

    if(vertexShader > 0)
        glAttachShader(mId, vertexShader);
    if(fragmentShader > 0)
        glAttachShader(mId, fragmentShader);

    glLinkProgram(mId);
    checkCompileErrors(mId, "PROGRAM SHADER", true);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    int nbAttribs;
    int nbUniforms;
    int nbUniformBlocks;
    glGetProgramiv(mId, GL_ACTIVE_ATTRIBUTES, &nbAttribs);
    glGetProgramiv(mId, GL_ACTIVE_UNIFORMS, &nbUniforms);
    glGetProgramiv(mId, GL_ACTIVE_UNIFORM_BLOCKS, &nbUniformBlocks);
    std::vector<unsigned int> uniformIndices;
    std::vector<char> uniformNames;

    uniformIndices.reserve(nbUniforms);
    uniformNames.reserve(1024);

    GLint size;
    GLint bufSize = sizeof(char) * 1024;
    GLenum type;

    for(std::size_t i = 0; i < static_cast<std::size_t>(nbUniforms); ++i) {
        uniformNames.clear();
        glGetActiveUniform(mId, i, bufSize, nullptr, &size, &type, &uniformNames.front());
        std::string name = &uniformNames.front();

        if(size > 1 && name.find("[") != std::string::npos) {
            std::size_t start = name.find("[") + 1;
            std::string tmp = name.substr(0, start - 1) ;

            for(int j = 0; j < size; ++j) {
                std::string s = tmp + "[" + std::to_string(j) + "]";
                
                if(uniformsCache.find(s) == uniformsCache.end()) {
                    GLint v = glGetUniformLocation(getId(), s.c_str());
                    uniformsCache.insert(std::pair<std::string, GLint>(&s.front(), v));
                }
            }
        } else {
            if(uniformsCache.find(name) == uniformsCache.end()) {
                GLint v = glGetUniformLocation(mId, &uniformNames.front());
                uniformsCache.insert(std::pair<std::string, GLint>(name, v));
            }
        }
    }
    
    for(std::size_t i = 0; i < static_cast<std::size_t>(nbUniformBlocks); ++i) {
        uniformNames.clear();
        glGetActiveUniformBlockName(mId, i, bufSize, &size, &uniformNames.front());
//        uniformBlockIndex.emplace_back(i);
        glUniformBlockBinding(mId, i, 0);
        std::string name = &uniformNames.front();
        uniformsCache.insert(std::pair<std::string, GLint>(name, i));
    }
}

void glh::ShaderProgram::loadFromFile(const std::string& vertexShader, const std::string& fragShader)
{
    std::string vSource;
    std::string vFrag;

    if(!vertexShader.empty())
        vSource = loadFromFile(vertexShader);

    if(!fragShader.empty())
        vFrag = loadFromFile(fragShader);

    loadFromMemory(vSource, vFrag);
}

void glh::ShaderProgram::bind()
{
    if(mId > 0) {
        glUseProgram(mId);
    }
}

void glh::ShaderProgram::create()
{
    if(mId == 0) {
        mId = glCreateProgram();
        checkGlError("glh::ShaderProgram::create");
        bind();
    }
}

void glh::ShaderProgram::destroy()
{
    if(mId > 0) {
        unbind();
        glDeleteProgram(mId);
        mId = 0;
    }
}

void glh::ShaderProgram::unbind()
{
    glUseProgram(0);
}

GLint glh::ShaderProgram::getUniform(const std::string& name) const
{
    return uniformsCache[name];
}

void glh::ShaderProgram::setUniform(const std::string& name, const int value) const
{
    glUniform1i(getUniform(name), value);
}

void glh::ShaderProgram::setUniform(const std::string& name, const unsigned int value) const
{
    glUniform1ui(getUniform(name), value);
}

void glh::ShaderProgram::setUniform(const std::string& name, const float v1, const float v2) const
{
    glUniform2f(getUniform(name), v1, v2);
}

void glh::ShaderProgram::setUniform(const std::string& name, const float v1, const float v2, const float v3) const
{
    glUniform3f(getUniform(name), v1, v2, v3);
}

void glh::ShaderProgram::setUniform(const std::string& name, const float v1, const float v2, const float v3, const float v4) const
{
    glUniform4f(getUniform(name), v1, v2, v3, v4);
}

void glh::ShaderProgram::setUniform(const std::string& name, const float value) const
{
    glUniform1f(getUniform(name), value);
}

void glh::ShaderProgram::setUniform(const std::string& name, const bool value) const
{
    glUniform1i(getUniform(name), static_cast<int>(value));
}

void glh::ShaderProgram::setUniform(const std::string& name, const glm::vec2& v) const
{
    setUniform(name, v.x, v.y);
}

void glh::ShaderProgram::setUniform(const std::string& name, const glm::vec3& v) const
{
        glUniform3fv(getUniform(name), 1, &v[0]);
}

void glh::ShaderProgram::setUniform(const std::string& name, const glm::vec4& v) const
{
    glUniform4fv(getUniform(name), 1, &v[0]);
}

void glh::ShaderProgram::setUniform(const std::string& name, const glm::mat2& mat2) const
{
    glUniformMatrix2fv(getUniform(name), 1, GL_FALSE, glm::value_ptr(mat2));
}

void glh::ShaderProgram::setUniform(const std::string& name, const glm::mat3& mat3) const
{
    glUniformMatrix3fv(getUniform(name), 1, GL_FALSE, glm::value_ptr(mat3));
}

void glh::ShaderProgram::setUniform(const std::string& name, const glm::mat4& mat4) const
{
    glUniformMatrix4fv(getUniform(name), 1, GL_FALSE, glm::value_ptr(mat4));
}

unsigned int glh::ShaderProgram::loadFromMemory(const std::string& s, GLenum shaderType)
{
    unsigned int shader;
    std::string error = typeToStr(shaderType);
    if(shaderType == GL_VERTEX_SHADER)
        shader = glCreateShader(GL_VERTEX_SHADER);
    else
        shader = glCreateShader(GL_FRAGMENT_SHADER);

    const char* shaderSource = s.c_str();

    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);
    checkCompileErrors(shader, error);

    return shader;
}

std::string glh::ShaderProgram::loadFromFile(const std::string& fileName)
{
    std::ifstream shaderFile;
    std::stringstream ss;
    shaderFile.open(fileName);
    ss << shaderFile.rdbuf();
    shaderFile.close();
    return ss.str();
}

bool glh::ShaderProgram::checkCompileErrors(GLuint shader, const std::string& errorType, const bool program)
{
    GLint success;
    GLint length;
    std::vector<char> infoLog;

    if(program) {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &length);
            infoLog.resize(length);
            glGetProgramInfoLog(shader, length, &length, &infoLog.front());
            throw std::runtime_error(std::string(
                                         "glh::Shader: ERROR::PROGRAM_LINKING_ERROR of type: " + errorType + "\n" + &infoLog.front()));
            return false;
        }
    } else {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
            infoLog.resize(length);
            glGetShaderInfoLog(shader, length, &length, &infoLog.front());
            throw std::runtime_error(std::string(
                                         "glh::Shader : ERROR::SHADER_COMPILATION_ERROR of type: " + errorType + "\n" + &infoLog.front()));
            return false;
        }
    }
    return true;
}

std::string glh::ShaderProgram::typeToStr(GLenum shaderType)
{
    switch(shaderType) {
    case GL_FRAGMENT_SHADER:
        return "FRAGMENT SHADER";
        break;

    case GL_GEOMETRY_SHADER:
        return "GEOMETRY SHADER";
        break;

    case GL_VERTEX_SHADER:
        return "VERTEX SHADER";
        break;

    default:
        return "";
    }
}
