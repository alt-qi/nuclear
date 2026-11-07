#ifdef NUCLEAR_TRD_EXAMPLE
#include <cmath>
using ld = long double;
using ll = long long;
inline bool eq(ld a, ld b);
#endif

/// &TRD_BEGIN
/// @author unknown
/// @brief Точка и векторы.
const ld pi = acos(-1);
const ld eps = 1e-12;

struct point {
    ld x, y;
    point() {}
    point(ld x, ld y): x(x), y(y) {}
    point operator +(const point& a) const {
        return point(x + a.x, y + a.y);
    }
    point operator -(const point& a) const {
        return point(x - a.x, y - a.y);
    }
    ld sq2() {
        return x * x + y * y;
    }
    ld len() {
        return sqrt(sq2());
    }
    ld operator *(const point& a) {
        return x * a.x + y * a.y;
    }
    point operator *(ll val) {
        return point(x * val, y * val);
    }
    ld operator %(const point& a) { // векторное произведение
        return x * a.y - y * a.x;
    }
    bool operator ==(const point& a) const {
        return eq(x, a.x) && eq(y, a.y);
    }
    point rotate90() {
        return point(y, -x);
    }
    point rotate270() {
        return point(-y, x);
    }
    point rot(ld angle) {
        return point(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
    }
    point norm() {
        return point(x / len(), y / len());
    }
    point resize(ld val) {
        return point(x * val, y * val);
    }
};

// Пример использования
inline bool example_point() {
    point a(0, 0), b(3, 0), c(0, 4);
    point ab = b - a, ac = c - a;
    return (ab % ac) == 12 && ab * ac == 0;  // поворот влево, угол 90°
}
/// &TRD_END

#ifdef NUCLEAR_TRD_EXAMPLE
inline bool eq(ld a, ld b) { return std::abs(a - b) < eps; }
#endif
