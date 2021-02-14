#ifndef OBJREADER_HPP
#define OBJREADER_HPP

#include <string>
#include <vector>

namespace glh
{

class ObjReader
{
public:

    struct Mesh {
        Mesh(const std::string& name)
            : mName(name)
        {
        }

        const std::string& getName() const
        {
            return mName;
        }

        const std::vector<float>& getVertices()
        {
            return mVertices;
        }

        const std::vector<float>& getUvs()
        {
            return mUvs;
        }

        const std::vector<float>& getNormals()
        {
            return mNormals;
        }

        void addVertices(const float value)
        {
            mVertices.emplace_back(value);
        }

        void addVertices(const float x, const float y, const float z)
        {
            mVertices.emplace_back(x);
            mVertices.emplace_back(y);
            mVertices.emplace_back(z);
        }

        void addUvs(const float value)
        {
            mUvs.emplace_back(value);
        }

        void addUvs(const float x, const float y)
        {
            mUvs.emplace_back(x);
            mUvs.emplace_back(y);
        }

        void addNormals(const float value)
        {
            mNormals.emplace_back(value);
        }

        void addNormals(const float x, const float y, const float z)
        {
            mNormals.emplace_back(x);
            mNormals.emplace_back(y);
            mNormals.emplace_back(z);
        }

    private:
        std::string mName;
        std::vector<float> mVertices;
        std::vector<float> mUvs;
        std::vector<float> mNormals;
    };

    ObjReader();
    ~ObjReader();

    bool load(const std::string& objFile);
    std::vector<Mesh>& getMeshes()
    {
        return mMeshes;
    }
    
    std::vector<float> getAllMeshesPositions();
    std::vector<float> getAllMeshesNormals();
    std::vector<float> getAllMeshesUvs();

private:
    struct Face {
        int vertex;
        int uv;
        int normal;
        Face()
            : vertex(-1)
            , uv(-1)
            , normal(-1)
        {
        }
    };

    std::vector<Mesh> mMeshes;
    std::vector<std::string> split(const std::string& s, const char delimiter);
};
}

#endif // OBJREADER_HPP
