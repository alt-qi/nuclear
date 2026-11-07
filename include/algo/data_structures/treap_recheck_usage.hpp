#pragma once

#include "treap_recheck.hpp"

/// &TRD_BEGIN
inline bool example_treap() {
    auto t = std::make_unique<treap>();  // большой пул выделяем в куче
    t->insert(2); t->insert(5); t->insert(5);
    bool ok = t->kth(1) == 2 && t->sum() == 12;  // ранг с единицы
    t->erase_value(5);  // удаляет все копии
    return ok && t->size() == 1;
}
/// &TRD_END
