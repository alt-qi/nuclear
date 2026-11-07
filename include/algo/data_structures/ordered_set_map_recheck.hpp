/// &TRD_BEGIN
/// @author Не указан в исходном файле
/// @brief Ordered set/map RECHECK.
/// @date 2026-11-06
/// @note Дата переноса; код из приложенного файла без изменений.

// g++ -std=gnu++17 -O2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template<class T, class cmp = less<T>>
using ordered_set = tree<T, null_type, cmp, rb_tree_tag, tree_order_statistics_node_update>;

template<class K, class V, class cmp = less<K>>
using ordered_map = tree<K, V, cmp, rb_tree_tag, tree_order_statistics_node_update>;
/// &TRD_END

/// &TRD_EXAMPLE_BEGIN
// Пример использования
inline bool example_ordered_map() { ordered_map<int, int> m;
    m[8] = 4; m[3] = 2;
    return m.order_of_key(8) == 1 && m.find_by_order(0)->first == 3; }
/// &TRD_EXAMPLE_END
