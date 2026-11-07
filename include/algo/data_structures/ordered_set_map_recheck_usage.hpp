#pragma once

#include "ordered_set_map_recheck.hpp"

/// &TRD_BEGIN
inline bool example_ordered_map() { ordered_map<int, int> m;
    m[8] = 4; m[3] = 2;
    return m.order_of_key(8) == 1 && m.find_by_order(0)->first == 3; }
/// &TRD_END
