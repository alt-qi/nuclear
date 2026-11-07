#pragma once

#include "explicit_splay_tree.hpp"

/// &TRD_BEGIN
inline bool example_explicit_splay() {
    splay::Node a(2), b(5);
    auto* root = splay::merge(&a, &b);  // слева ключи меньше
    root = splay::find(root, 5);  // сохраняем новый корень
    if (root->v != 5) return false;
    auto [less, rest] = splay::split(root, 5);  // < 5 и >= 5
    return less == &a && rest == &b;
}
/// &TRD_END
