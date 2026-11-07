#pragma once

#include <bits/stdc++.h>
using namespace std;
#include "aho_corasick_recheck.hpp"

/// &TRD_BEGIN
inline bool example_aho_corasick() {
    Aho aho;  // непустые шаблоны из a..z
    int id = aho.add_pattern("ab");
    aho.build();  // после всех добавлений
    int state = aho.go(aho.go(0, 'a'), 'b');
    return aho.get_matches(state) == std::vector<int>{id};
}
/// &TRD_END
