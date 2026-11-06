/// &TRD_BEGIN
/// @author Не указан в исходном файле
/// @brief Точка и векторы RECHECK.
/// @date 2026-11-06
/// @note Дата переноса; код из приложенного файла без изменений.

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
/// &TRD_END
