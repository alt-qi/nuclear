#pragma once

#include <bits/stdc++.h>
using namespace std;
#include "min_cost_max_flow_recheck.hpp"

/// &TRD_BEGIN
inline bool example_mcmf() {
    MCMF net(3);
    net.add_edge(0, 1, 3, 1); net.add_edge(1, 2, 3, 2);  // ёмкость, цена
    auto [flow, cost] = net.solve(0, 2, 2);  // исток, сток, лимит
    return flow == 2 && cost == 6;
}
/// &TRD_END
