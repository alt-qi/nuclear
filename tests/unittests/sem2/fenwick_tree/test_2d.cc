#include <gtest/gtest.h>

#include <random>
#include <variant>

#include "algo/sem2/fenwick_tree/fenwick_tree_2d.hpp"

using namespace std;

struct GetQuery {
    int x0, y0, x1, y1;
};

struct AddQuery {
    int x, y, v;
};

template <typename T>
struct NaiveFenwickTree2D {
    int n, m;
    vector<vector<T>> t;

    NaiveFenwickTree2D(int n, int m) : n(n), m(m), t(n, vector<T>(m)) {}

    void Add(int x, int y, int v) { t[x][y] += v; }

    T Sum(int x0, int y0, int x1, int y1) {
        T sum = 0;
        for (int x = x0; x <= x1; x++) {
            for (int y = y0; y <= y1; y++) {
                sum += t[x][y];
            }
        }
        return sum;
    }
};

vector<variant<GetQuery, AddQuery>> generate_queries(int n, int m, int q,
                                                     default_random_engine& eng) {
    uniform_int_distribution<int> x_rand(0, n - 1), y_rand(0, m - 1), query_type(0, 1),
        add_value(0, 1e9);
    std::vector<variant<GetQuery, AddQuery>> queries;
    for (int i = 0; i < q; i++) {
        if (query_type(eng)) {
            int x0 = x_rand(eng);
            int x1 = x_rand(eng);
            int y0 = y_rand(eng);
            int y1 = y_rand(eng);

            if (x1 < x0) swap(x1, x0);
            if (y1 < y0) swap(y1, y0);
            queries.push_back(std::move(GetQuery{x0, y0, x1, y1}));
        } else {
            int x = x_rand(eng);
            int y = y_rand(eng);
            queries.push_back(std::move(AddQuery{x, y, add_value(eng)}));
        }
    }

    return queries;
}

bool random_test_compare_with_naive(int n, int m, int q, int seed) {
    FenwickTree2D<int64_t> tree(n, m);
    NaiveFenwickTree2D<int64_t> naive_tree(n, m);

    default_random_engine eng(seed);
    auto queries = generate_queries(n, m, q, eng);
    for (const auto& query : queries) {
        if (query.index() == 0) {
            auto [x0, y0, x1, y1] = get<GetQuery>(query);
            if (tree.Sum(x0, y0, x1, y1) != naive_tree.Sum(x0, y0, x1, y1)) return false;
        } else {
            auto [x, y, v] = get<AddQuery>(query);
            tree.Add(x, y, v);
            naive_tree.Add(x, y, v);
        }
    }

    return true;
}

TEST(FenwickTree2D, TestRandomSmall1) {
    ASSERT_TRUE(random_test_compare_with_naive(1, 1, 1, 1337));
}

TEST(FenwickTree2D, TestRandomSmall2) {
    ASSERT_TRUE(random_test_compare_with_naive(1, 2, 3, 236634));
}

TEST(FenwickTree2D, TestRandomSmall3) {
    ASSERT_TRUE(random_test_compare_with_naive(2, 1, 5, 3543234));
}

TEST(FenwickTree2D, TestRandomMedium1) {
    ASSERT_TRUE(random_test_compare_with_naive(50, 30, 5000, 543534));
}

TEST(FenwickTree2D, TestRandomMedium2) {
    ASSERT_TRUE(random_test_compare_with_naive(80, 40, 5000, 42342342));
}

TEST(FenwickTree2D, TestRandomMedium3) {
    ASSERT_TRUE(random_test_compare_with_naive(70, 70, 5000, 3543234));
}

TEST(FenwickTree2D, TestRandomBig1) {
    ASSERT_TRUE(random_test_compare_with_naive(1000, 1000, 300, 82736478));
}

TEST(FenwickTree2D, TestRandomBig2) {
    ASSERT_TRUE(random_test_compare_with_naive(500, 500, 1000, 42343223));
}

TEST(FenwickTree2D, TestRandomBig3) {
    ASSERT_TRUE(random_test_compare_with_naive(1000, 1000, 300, 92399238));
}
