#pragma once

#include <bits/stdc++.h>
using namespace std;
#include "suffix_tree_recheck.hpp"

/// &TRD_BEGIN
inline bool example_suffix_tree() {
    ST tree("banana$");  // уникальный символ завершает суффиксы
    int edge = tree.get(0, 'b');  // 0 — корень, -1 — нет ребра
    return edge >= 0 && tree.s.substr(tree.l[edge], tree.len(edge)) == "banana$";
}
/// &TRD_END
