#pragma once

#include "segment_tree_recheck.hpp"

/// &TRD_BEGIN
inline bool example_segment_tree() {
    SegTree tree(std::vector<long long>{2, 4, 1});
    tree.add(0, 2, 3);  // [0, 2) -> {5, 7, 1}
    return tree.getmax(1, 3) == 7;
}
/// &TRD_END
