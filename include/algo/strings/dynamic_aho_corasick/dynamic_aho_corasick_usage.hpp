#pragma once

#include "dynamic_aho_corasick.hpp"

/// &TRD_BEGIN
inline bool example_dynamic_aho() {
    DynamicAho aho; aho.add_string("aba");  // строки из a..z
    auto before = aho.count_total_matches("ababa");
    aho.add_string("ba");  // можно добавлять между запросами
    return before == 2 && aho.count_total_matches("ababa") == 4;
}
/// &TRD_END
