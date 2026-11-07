/// &TRD_BEGIN
/// @author unknown
/// @brief Расширенный НОД и диофантово уравнение.
ll gcd(ll a, ll b, ll& x, ll& y) { // ax + by = c
    if (a == 0) {
        x = 0, y = 1;
        return b;
    }

    ll x1, y1;
    ll g = gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return g;
}
/// &TRD_END
