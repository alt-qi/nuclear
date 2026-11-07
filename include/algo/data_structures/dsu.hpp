#pragma once

/// &TRD_BEGIN
/// @author OpenAI Codex
/// @brief DSU со сжатием путей и объединением по размеру.
/// @date 2026-11-07

#include <numeric>
#include <utility>
#include <vector>

// Вершины 0..n-1. Изначально каждая в отдельной компоненте.
class DSU {
    std::vector<int> parent_, size_;

public:
    explicit DSU(int n) : parent_(n), size_(n, 1) {
        std::iota(parent_.begin(), parent_.end(), 0);
    }

    int find(int v) {
        if (parent_[v] != v) parent_[v] = find(parent_[v]);
        return parent_[v];
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (size_[a] < size_[b]) std::swap(a, b);
        parent_[b] = a;
        size_[a] += size_[b];
        return true;
    }

    bool same(int a, int b) { return find(a) == find(b); }
    int size(int v) { return size_[find(v)]; }
};
/// &TRD_END
