#pragma once

#include <cassert>
#include <utility>
#include <vector>

/// &TRD_BEGIN
/// @author Автор исходника не указан. Переработка Codex.
/// @brief HLD. Сумма весов вершин на пути с точечными обновлениями.
/// @date 2026-11-07
/// @note Построение O(n), обновление O(log n), запрос O(log^2 n), память O(n).

class HLD {
    int n;
    vector<int> parent, depth, head, pos;
    vector<long long> tree;

    // Сумма на полуинтервале [l, r) в порядке декомпозиции.
    long long range_sum(int l, int r) const {
        long long sum = 0;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2) sum += tree[l++];
            if (r % 2) sum += tree[--r];
        }
        return sum;
    }

public:
    // Связное неориентированное дерево. Вершины от 0 до n - 1.
    HLD(const vector<vector<int>>& graph,
        const vector<long long>& values, int root = 0)
        : n(static_cast<int>(graph.size())), parent(n, -1), depth(n),
          head(n), pos(n), tree(2 * n) {
        assert(0 <= root && root < n && values.size() == graph.size());

        vector<int> order{root}, size(n, 1), heavy(n, -1);
        order.reserve(n);
        for (int i = 0; i < static_cast<int>(order.size()); ++i) {
            int v = order[i];
            for (int u : graph[v]) {
                if (u == parent[v]) continue;
                parent[u] = v;
                depth[u] = depth[v] + 1;
                order.push_back(u);
            }
        }

        // Снизу вверх выбираем ребёнка с наибольшим поддеревом.
        for (int i = n - 1; i > 0; --i) {
            int v = order[i], p = parent[v];
            size[p] += size[v];
            if (heavy[p] == -1 || size[v] > size[heavy[p]]) heavy[p] = v;
        }

        // Сначала нумеруем тяжёлую цепь, затем лёгкие поддеревья.
        order.resize(1);
        for (int timer = 0; !order.empty();) {
            int h = order.back();
            order.pop_back();
            for (int v = h; v != -1; v = heavy[v]) {
                head[v] = h;
                pos[v] = timer++;
                tree[n + pos[v]] = values[v];
                for (int u : graph[v]) {
                    if (u != parent[v] && u != heavy[v]) order.push_back(u);
                }
            }
        }
        for (int i = n - 1; i > 0; --i) tree[i] = tree[2 * i] + tree[2 * i + 1];
    }

    void set(int v, long long value) {
        int i = n + pos[v];
        tree[i] = value;
        for (i /= 2; i > 0; i /= 2) tree[i] = tree[2 * i] + tree[2 * i + 1];
    }

    void add(int v, long long delta) {
        set(v, tree[n + pos[v]] + delta);
    }

    long long path_sum(int u, int v) const {
        long long sum = 0;
        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]]) swap(u, v);
            sum += range_sum(pos[head[u]], pos[u] + 1);
            u = parent[head[u]];
        }
        if (pos[u] > pos[v]) swap(u, v);
        return sum + range_sum(pos[u], pos[v] + 1);
    }
};

// Пример использования.
inline bool example_hld() {
    HLD hld({{1}, {0}}, {3, 5});
    hld.add(1, 4);
    hld.set(0, -2);
    return hld.path_sum(0, 1) == 7;
}
/// &TRD_END
