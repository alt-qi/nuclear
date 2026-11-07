#pragma once

#include "dinic_recheck.hpp"

/// &TRD_BEGIN
inline bool example_dinic() {
    Dinic flow(3);  // вершины 0..2
    flow.add_edge(0, 1, 3); flow.add_edge(1, 2, 2);  // дуги, ёмкости
    return flow.max_flow(0, 2) == 2;  // исток, сток
}
/// &TRD_END
