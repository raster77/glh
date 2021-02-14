#include "CubeMap.hpp"
#include "glh/core/Image.hpp"
#include <iostream>

glh::CubeMap::CubeMap()
    : mTextureId(0)
{
}

glh::CubeMap::~CubeMap()
{
    vao.destroy();
    vbo.destroy();
    glDeleteTextures(1, &mTextureId);
    shader.destroy();
}

void glh::CubeMap::setFaces(const glh::CubeMap::Faces& faces)
{
    mFaces = faces;
    setTextures();

    std::vector<float> vertices = { -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f };

    vao.create();
    vbo.create(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    vbo.setData(vertices);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    shader.loadFromMemory(getVertexShader(), getFragmentShader());
    shader.bind();
    shader.setUniform("cubeMap", static_cast<int>(mTextureId));
}

void glh::CubeMap::setTextures()
{
    glGenTextures(1, &mTextureId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, mTextureId);
    glTexStorage2D(GL_TEXTURE_CUBE_MAP, 1, GL_RGB8, 512, 512);

    loadTexture(mFaces.textureRight, 0);
    loadTexture(mFaces.textureLeft, 1);
    loadTexture(mFaces.textureTop, 2);
    loadTexture(mFaces.textureBottom, 3);
    loadTexture(mFaces.textureFront, 4);
    loadTexture(mFaces.textureBack, 5);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void glh::CubeMap::loadTexture(const std::string& fileName, const int index)
{
    glh::Image img;

    if(img.loadFromFile(fileName)) {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + index, 0, 0, 0, img.getWidth(), img.getHeight(), GL_RGBA,
            GL_UNSIGNED_BYTE, img.getPixelsPtr());
        //        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + index, 0, GL_RGBA, img.getWidth(), img.getHeight(), 0,
        //        GL_RGBA, GL_UNSIGNED_BYTE, img.getPixelsPtr());
    } else {
        std::cout << "error on " + fileName << std::endl;
    }
}

const int glh::CubeMap::getTextureId() const
{
    return static_cast<int>(mTextureId);
}

void glh::CubeMap::bindTextureUnit()
{
    glActiveTexture(GL_TEXTURE0 + mTextureId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, mTextureId);
}

void glh::CubeMap::render()
{
    // change depth function so depth test passes when values are equal to depth buffer's content
    glDepthFunc(GL_LEQUAL);

    vao.bind();

    glActiveTexture(GL_TEXTURE0 + mTextureId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, mTextureId);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    vao.unbind();
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    glDepthFunc(GL_LESS);
}

void glh::CubeMap::setProjection(const glm::mat4& projection)
{
    mProjection = projection;
    if(shader.getId() > 0) {
        shader.bind();
        shader.setUniform("projection", mProjection);
    }
}

void glh::CubeMap::setViewMatrix(const glm::mat4& viewMatrix)
{
    mView = glm::mat4(glm::mat3(viewMatrix));
    if(shader.getId() > 0) {
        shader.bind();
        shader.setUniform("view", mView);
    }
}

std::string glh::CubeMap::getFragmentShader()
{
    return "#version 330 core\n"
           "out vec4 FragColor;\n"
           "in vec3 TexCoords;\n"
           "uniform samplerCube cubeMap;\n"
           "void main()\n"
           "{\n"
           "    FragColor = texture(cubeMap, TexCoords);\n"
           "}\n";
}

std::string glh::CubeMap::getVertexShader()
{
    return "#version 330 core\n"
           "layout (location = 0) in vec3 aPos;\n"
           "out vec3 TexCoords;\n"

           "uniform mat4 projection;\n"
           "uniform mat4 view;\n"

           "void main()\n"
           "{\n"
           "    TexCoords = aPos;\n"
           "    vec4 pos = projection * view * vec4(aPos, 1.0);\n"
           "    gl_Position = pos.xyww;\n"
           "}\n";
}
