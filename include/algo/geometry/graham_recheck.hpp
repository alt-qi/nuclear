#ifdef NUCLEAR_TRD_EXAMPLE
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;
using ld = long double;
constexpr ld EPS = 1e-12L;
#endif

/// &TRD_BEGIN
/// @author Не указан в исходном файле
/// @brief Выпуклая оболочка Грэхема O(NlogN) RECHECK.
/// @date 2026-11-06
/// @note Дата переноса; код из приложенного файла без изменений.

struct r
{
    ld x, y;
    r(ld a, ld b) : x(a), y(b) {}
    r() : x(0), y(0) {}
    ld len() {return hypot(x, y);}
};

ld operator^(r a, r b) {return a.x * b.y - b.x * a.y;}
r operator-(r a, r b) {return {a.x - b.x, a.y - b.y};}
bool operator==(r a, r b) {return a.x == b.x && a.y == b.y;}

vector<r> graham(vector<r> points) {
    r p0(points[0].x, points[0].y);
    for (r p : points) {
        if (p.y < p0.y || p.y == p0.y && p.x < p0.x) {
            p0 = p;
        }
    }

    sort(points.begin(), points.end(), [&] (r a, r b) {
        return abs((a - p0) ^ (b - p0)) < EPS && (a - p0).len() > (b - p0).len() || ((a - p0) ^ (b - p0)) > 0;
    });
    
    vector<r> hull;
    for (r p : points) {
        while (hull.size() >= 2) {
            r new_vec = p - hull.back();
            r last_vec = hull.back() - hull[hull.size() - 2];
            if ((last_vec ^ new_vec) < 0 || abs(last_vec ^ new_vec) < EPS)
                hull.pop_back();
            else 
                break;
        }
        hull.push_back(p);
    }

    return hull;
}

// Пример использования
inline bool example_graham() {
    auto hull = graham({{0, 0}, {4, 0}, {0, 4}, {1, 1}});
    return hull.size() == 3;  // (1, 1) внутри
}
/// &TRD_END
