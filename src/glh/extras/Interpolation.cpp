#include "Interpolation.hpp"

template <typename T>
T cubicBezierP0(const T& t, const T& p) {
    T k = 1 - t;
    return k * k * k * p;
}

template <typename T>
T cubicBezierP1(const T& t, const T& p) {
    T k = 1 - t;
    return 3 * k * k * t * p;
}

template <typename T>
T cubicBezierP2(const T& t, const T& p) {
    return 3 * (1 - t) * t * t * p;
}

template <typename T>
T cubicBezierP3(const T& t, const T& p) {
    return t * t * t * p;
}

template <typename T>
T cubicBezier(T t, const T& p0, const T& p1, const T& p2, const T& p3)
{
    return cubicBezierP0(t, p0) + cubicBezierP1(t, p1) + cubicBezierP2(t, p2) + cubicBezierP3(t, p3);
}