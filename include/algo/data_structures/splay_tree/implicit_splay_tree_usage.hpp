#pragma once

#include "implicit_splay_tree.hpp"

/// &TRD_BEGIN
inline bool example_implicit_splay() {
    Node* root = merge(create(2), create(5));
    auto [first, rest] = split(root, 1);  // отделяем один элемент
    rest->to_add += 3; push(rest);
    root = merge(first, rest);
    root = get(root, 1);  // индекс с нуля, сохраняем новый корень
    bool ok = root->v == 8 && root->mn == 2;
    remove(root);
    return ok;
}
/// &TRD_END
