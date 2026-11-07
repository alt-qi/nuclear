#pragma once

#include <cmath>
using ld = long double;
using ll = long long;
inline bool eq(ld a, ld b);
#include "point_recheck.hpp"
inline bool eq(ld a, ld b) { return std::abs(a - b) < eps; }

/// &TRD_BEGIN
inline bool example_point() {
    point a(0, 0), b(3, 0), c(0, 4);
    point ab = b - a, ac = c - a;
    return (ab % ac) == 12 && ab * ac == 0;  // поворот влево, угол 90°
}
/// &TRD_END
