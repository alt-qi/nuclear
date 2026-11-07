#pragma once

#include "dsu.hpp"

/// &TRD_BEGIN
inline bool example_dsu() {
    DSU groups(4);  // вершины 0..3
    groups.unite(0, 1); groups.unite(1, 2);
    return groups.same(0, 2) && groups.size(1) == 3 && !groups.same(0, 3);
}
/// &TRD_END
