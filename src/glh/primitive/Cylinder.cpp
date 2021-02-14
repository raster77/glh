#include "Cylinder.hpp"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>

glh::primitive::Cylinder::Cylinder()
    : Primitive()
{
}

glh::primitive::Cylinder::~Cylinder()
{
}

void glh::primitive::Cylinder::create(const float radiusTop,
    const float radiusBottom,
    const float height,
    const std::size_t radialSegments,
    const std::size_t heightSegments,
    const bool openEnded,
    const float thetaStart,
    const float thetaLength)
{
    mPositions.clear();
    mNormals.clear();
    mUvs.clear();
    mIndices.clear();

    this->radiusTop = radiusTop;
    this->radiusBottom = radiusBottom;
    this->height = height;
    this->thetaStart = thetaStart;
    this->thetaLength = thetaLength;
    this->radialSegments = radialSegments;
    this->heightSegments = heightSegments;

    std::vector<std::vector<unsigned int>> indexArray;
    halfHeight = height * 0.5f;
    index = 0;

    // this will be used to calculate the normal
    float slope = (radiusBottom - radiusTop) / height;

    for(std::size_t y = 0; y <= heightSegments; y++) {
        std::vector<unsigned int> indexRow;
        float v = static_cast<float>(y) / static_cast<float>(heightSegments);
        // calculate the radius of the current row
        float radius = v * (radiusBottom - radiusTop) + radiusTop;
        for(std::size_t x = 0; x <= radialSegments; x++) {
            float u = static_cast<float>(x) / static_cast<float>(radialSegments);
            float theta = u * thetaLength + thetaStart;
            float sinTheta = std::sin(theta);
            float cosTheta = std::cos(theta);
            glm::vec3 tmp(radius * sinTheta, -v * height + halfHeight, radius * cosTheta);
            float angle = glm::angle(glm::vec3(10.f, 2.f, 4.f), tmp);
            tmp *= angle;
            // vertex
            mPositions.emplace_back(radius * sinTheta);
            mPositions.emplace_back(-v * height + halfHeight);
            mPositions.emplace_back(radius * cosTheta);

            // normal
            glm::vec3 normal = glm::normalize(glm::vec3(sinTheta, slope, cosTheta));
            mNormals.emplace_back(normal.x);
            mNormals.emplace_back(normal.y);
            mNormals.emplace_back(normal.z);

            // uv
            mUvs.emplace_back(u);
            mUvs.emplace_back(1.f - v);

            // save index of vertex in respective row
            indexRow.emplace_back(index++);
        }

        // now save this.vertices of the row in our index array
        indexArray.emplace_back(indexRow);
    }

    for(std::size_t x = 0; x < radialSegments; x++) {
        for(std::size_t y = 0; y < heightSegments; y++) {
            // we use the index array to access the correct indices
            unsigned int a = indexArray[y][x];
            unsigned int b = indexArray[y + 1][x];
            unsigned int c = indexArray[y + 1][x + 1];
            unsigned int d = indexArray[y][x + 1];

            // faces
            mIndices.emplace_back(a);
            mIndices.emplace_back(b);
            mIndices.emplace_back(d);
            mIndices.emplace_back(b);
            mIndices.emplace_back(c);
            mIndices.emplace_back(d);
        }
    }

    if(!openEnded) {
        if(radiusTop > 0)
            generateCap(true);
        if(radiusBottom > 0)
            generateCap(false);
    }
}

void glh::primitive::Cylinder::generateCap(const bool top)
{

    std::size_t centerIndexStart = 0, centerIndexEnd = 0;
    float radius = (top == true) ? radiusTop : radiusBottom;
    float sign = (top == true) ? 1.f : -1.f;

    // save the index of the first center vertex
    centerIndexStart = index;

    // first we generate the center vertex data of the cap.
    // because the geometry needs one set of uvs per face,
    // we must generate a center vertex per face/segment

    for(std::size_t x = 1; x <= radialSegments; x++) {
        // vertex
        mPositions.emplace_back(0.f);
        mPositions.emplace_back(halfHeight * sign);
        mPositions.emplace_back(0.f);
        // normal
        mNormals.emplace_back(0.f);
        mNormals.emplace_back(sign);
        mNormals.emplace_back(0.f);
        // uv
        mUvs.emplace_back(0.5f);
        mUvs.emplace_back(0.5f);
        // increase index
        index++;
    }

    // save the index of the last center vertex
    centerIndexEnd = index;

    // now we generate the surrounding vertices, normals and uvs
    for(std::size_t x = 0; x <= radialSegments; x++) {
        float u = static_cast<float>(x) / static_cast<float>(radialSegments);
        float theta = u * thetaLength + thetaStart;
        float cosTheta = std::cos(theta);
        float sinTheta = std::sin(theta);
        // vertex
        mPositions.emplace_back(radius * sinTheta);
        mPositions.emplace_back(halfHeight * sign);
        mPositions.emplace_back(radius * cosTheta);
        // normal
        mNormals.emplace_back(0.f);
        mNormals.emplace_back(sign);
        mNormals.emplace_back(0.f);
        // uv
        mUvs.emplace_back((cosTheta * 0.5f) + 0.5f);
        mUvs.emplace_back((sinTheta * 0.5f * sign) + 0.5f);
        // increase index
        index++;
    }

    // generate indices
    for(std::size_t x = 0; x < radialSegments; x++) {
        std::size_t c = centerIndexStart + x;
        std::size_t i = centerIndexEnd + x;

        if(top) {
            // face top
            mIndices.emplace_back(i);
            mIndices.emplace_back(i + 1);
            mIndices.emplace_back(c);
        } else {
            // face bottom
            mIndices.emplace_back(i + 1);
            mIndices.emplace_back(i);
            mIndices.emplace_back(c);
        }
    }
}