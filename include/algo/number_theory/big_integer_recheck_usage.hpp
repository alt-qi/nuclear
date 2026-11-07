#pragma once

#include "big_integer_recheck.hpp"

/// &TRD_BEGIN
inline bool example_big_integer() {
    Big a("1000000000000000000000000");  // неотрицательные числа
    auto [q, r] = a.divmod(3u);  // частное Big, остаток uint32_t
    return r == 1 && cmp(q * Big(3) + Big(r), a) == 0;
}
/// &TRD_END
