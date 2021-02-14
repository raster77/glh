#ifndef CUBEMAP_HPP
#define CUBEMAP_HPP

#include "glh/core/VertexArrayObject.hpp"
#include "glh/core/VertexBufferObject.hpp"
#include "glh/core/ShaderProgram.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

namespace glh
{

class CubeMap
{
public:
    struct Faces {
        std::string textureRight;
        std::string textureLeft;
        std::string textureTop;
        std::string textureBottom;
        std::string textureFront;
        std::string textureBack;
        Faces()
            : textureRight("")
            , textureLeft("")
            , textureTop("")
            , textureBottom("")
            , textureFront("")
            , textureBack("")
        {}
    };

    CubeMap();
    ~CubeMap();

    void setFaces(const glh::CubeMap::Faces& faces);
    void setProjection(const glm::mat4& projection);
    void setViewMatrix(const glm::mat4& viewMatrix);
    const int getTextureId() const;
    void bindTextureUnit();
    void render();

private:
    glh::ShaderProgram shader;
    glh::VertexArrayObject vao;
    glh::VertexBufferObject vbo;
    unsigned int mTextureId;
    Faces mFaces;
    glm::mat4 mProjection;
    glm::mat4 mView;

    void loadTexture(const std::string& fileName, const int index);
    void setTextures();
    std::string getFragmentShader();
    std::string getVertexShader();

};

}

#endif // CUBEMAP_HPP
