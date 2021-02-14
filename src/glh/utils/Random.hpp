#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <chrono>
#include <random>

namespace rnd
{

class Random
{
public:
    static Random& getInstance()
    {
        static rnd::Random instance;
        return instance;
    }

    int getUniformInt(const int min, const int max)
    {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(rndEngine);
    }

    float getUniformFloat(const float min, const float max)
    {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(rndEngine);
    }

    float getNormalFloat(const float mean, const float stddev)
    {
        std::normal_distribution<float> dist(mean, stddev);
        return dist(rndEngine);
    }

    float getFastFloat(const float min, const float max)
    {
        unsigned int a;
        mirand *= 16807;
        a = (mirand & 0x007fffff) | 0x40000000;
        
        //return static_cast<float>(*(static_cast<float*>(&a)) - 3.f) * (max - min) + min;
        return (static_cast<float>(*(&a)) - 3.f) * (max - min) + min;
        //return static_cast<float>(*(static_cast<float*>(&a)) - 3.f); // * (max - min) + min;
        //(*((float*)&a) - 3.f)  * (max - min) + min;
        //((*(static_cast<float>(a)) - 3.0f) * (max - min)) + min;
    }

private:
    std::mt19937 rndEngine;
    unsigned int mirand;

    Random()
        : rndEngine(std::chrono::high_resolution_clock::now().time_since_epoch().count())
        , mirand(1)
    {
    }

    ~Random()
    {
    }

    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;
    Random(Random&&) = delete;
    Random& operator=(Random&&) = delete;
};
}

#endif // RANDOM_HPP
