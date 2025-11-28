#include<iostream>

using ll = long long;

ll binpow(ll x, ll k) {
    if (k == 0) {
        return 1;
    }
    if (k % 2 == 0) {
        ll res = binpow(x, k / 2);
        return res * res;
    }
    return binpow(x, k - 1);
}
