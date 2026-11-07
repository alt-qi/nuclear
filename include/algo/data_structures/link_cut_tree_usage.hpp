#pragma once

#include "link_cut_tree.hpp"

/// &TRD_BEGIN
inline bool example_link_cut() {
    splay::Node a(2), b(3), c(5);
    splay::lct::link(&a, &b); splay::lct::link(&b, &c);
    splay::lct::make_root(&a); splay::lct::expose(&c);
    bool sum_ok = c.sm == 10;  // сумма на пути a..c
    splay::lct::cut(&b, &c);  // передаём концы существующего ребра
    splay::lct::make_root(&a); splay::lct::expose(&b);
    return sum_ok && b.sm == 5;
}
/// &TRD_END
