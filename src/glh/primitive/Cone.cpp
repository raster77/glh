#include "Cone.hpp"
#include "Cylinder.hpp"

glh::primitive::Cone::Cone()
    : Primitive()
{
}

glh::primitive::Cone::~Cone()
{
}

void glh::primitive::Cone::create(const float radiusBottom,
    const float height,
    const std::size_t radialSegments,
    const std::size_t heightSegments,
    const float thetaStart,
    const float thetaLength)
{
    mPositions.clear();
    mNormals.clear();
    mUvs.clear();
    mIndices.clear();
    
    float r = radiusBottom < 0.1f ? 0.1f : radiusBottom;
    
    glh::primitive::Cylinder cylinder;
    cylinder.create(0.001f, r, height, radialSegments, heightSegments, false, thetaStart, thetaLength);

    mPositions = cylinder.getPositions();
    mNormals = cylinder.getNormals();
    mUvs = cylinder.getUvs();
    mIndices = cylinder.getIndices();
}
