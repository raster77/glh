#include "ObjReader.hpp"
#include <fstream>
#include <sstream>

glh::ObjReader::ObjReader()
{
}

glh::ObjReader::~ObjReader()
{
}

bool glh::ObjReader::load(const std::string& objFile)
{
    std::ifstream infile(objFile);
    if(!infile.good()) {
        infile.close();
        return false;
    }

    std::string line;
    mMeshes.clear();
    Mesh* currentMesh = nullptr;

    std::vector<float> tmpVertices;
    std::vector<float> tmpUvs;
    std::vector<float> tmpNormals;

    while(std::getline(infile, line)) {
        std::istringstream iss(line);
        while(iss.good()) {
            std::string s;
            iss >> s;
            if(s == "o" || s == "g") {
                iss >> s;
                mMeshes.emplace_back(Mesh(s));
                currentMesh = &mMeshes.back();
            } else if(s == "v") {
                for(std::size_t i = 0; i < 3; ++i) {
                    iss >> s;
                    tmpVertices.emplace_back(std::stof(s));
                }
            } else if(s == "vt") {
                for(std::size_t i = 0; i < 2; ++i) {
                    iss >> s;
                    tmpUvs.emplace_back(std::stof(s));
                }
            } else if(s == "vn") {
                for(std::size_t i = 0; i < 3; ++i) {
                    iss >> s;
                    tmpNormals.emplace_back(std::stof(s));
                }
            } else if(s == "f") {
                std::vector<Face> tmpIndices;
                std::vector<Face> indices;

                while(iss.good()) {
                    iss >> s;

                    std::vector<std::string> faces = split(s, '/');

                    Face face = Face();
                    if(!faces[0].empty())
                        face.vertex = std::stoi(faces[0]) - 1;
                    if(!faces[1].empty())
                        face.uv = std::stoi(faces[1]) - 1;
                    if(!faces[2].empty())
                        face.normal = std::stoi(faces[2]) - 1;

                    tmpIndices.push_back(face);
                }

                for(std::size_t i = 0; i < 3; ++i) {
                    indices.emplace_back(tmpIndices[i]);
                }

                for(std::size_t i = 3; i < tmpIndices.size(); ++i) {
                    indices.emplace_back(tmpIndices[i - 3]);
                    indices.emplace_back(tmpIndices[i - 1]);
                    indices.emplace_back(tmpIndices[i]);
                }

                for(std::size_t i = 0; i < indices.size(); i++) {

                    if(!tmpVertices.empty() && indices[i].vertex >= 0) {
                        for(std::size_t j = 0; j < 3; j++)
                            currentMesh->addVertices(tmpVertices[indices[i].vertex * 3 + j]);
                    }

                    if(!tmpUvs.empty() && indices[i].uv >= 0) {
                        for(std::size_t j = 0; j < 2; j++)
                            currentMesh->addUvs(tmpUvs[indices[i].uv * 2 + j]);
                    }

                    if(!tmpNormals.empty() && indices[i].normal >= 0) {
                        for(std::size_t j = 0; j < 3; j++)
                            currentMesh->addNormals(tmpNormals[indices[i].normal * 3 + j]);
                    }
                }
            }
        }
    }

    return true;
}

std::vector<float> glh::ObjReader::getAllMeshesPositions()
{
    std::vector<float> v;
    for(Mesh& m : mMeshes) {
        v.insert(std::end(v), std::begin(m.getVertices()), std::end(m.getVertices()));
    }
    return v;
}

std::vector<float> glh::ObjReader::getAllMeshesNormals()
{
    std::vector<float> v;
    for(Mesh& m : mMeshes) {
        v.insert(std::end(v), std::begin(m.getNormals()), std::end(m.getNormals()));
    }
    return v;
}

std::vector<float> glh::ObjReader::getAllMeshesUvs()
{
    std::vector<float> v;
    for(Mesh& m : mMeshes) {
        v.insert(std::end(v), std::begin(m.getUvs()), std::end(m.getUvs()));
    }
    return v;
}

std::vector<std::string> glh::ObjReader::split(const std::string& s, const char delimiter)
{
    std::stringstream ss{ s };
    std::string token;
    std::vector<std::string> v;
    while(std::getline(ss, token, delimiter))
        v.emplace_back(token);

    return v;
}
