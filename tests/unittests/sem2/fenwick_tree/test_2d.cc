#include <gtest/gtest.h>
#include <random>
#include <variant>

#include "algo/sem2/fenwick_tree/fenwick_tree_2d.hpp"

using namespace std;

TEST(FenwickTree2D, TestSize1x1) {
    FenwickTree<int> tree(1, 1);

    EXPECT_EQ(tree.Sum(0, 0, 0, 0), 0);

    tree.Add(0, 0, 544);
    EXPECT_EQ(tree.Sum(0, 0, 0, 0), 544);

    tree.Add(0, 0, -544);
    EXPECT_EQ(tree.Sum(0, 0, 0, 0), 0);
}

TEST(FenwickTree2D, TestSize1x2) {
    FenwickTree<int> tree(1, 2);

    EXPECT_EQ(tree.Sum(0, 0, 0, 1), 0);

    tree.Add(0, 0, 544);
    tree.Add(0, 1, 501);
    EXPECT_EQ(tree.Sum(0, 0, 0, 0), 544);
    EXPECT_EQ(tree.Sum(0, 1, 0, 1), 501);
    EXPECT_EQ(tree.Sum(0, 0, 0, 1), 501 + 544);
}

TEST(FenwickTree2D, TestSize2x1) {
    FenwickTree<int> tree(2, 1);

    EXPECT_EQ(tree.Sum(0, 0, 1, 0), 0);

    tree.Add(0, 0, 544);
    tree.Add(1, 0, 501);
    EXPECT_EQ(tree.Sum(0, 0, 0, 0), 544);
    EXPECT_EQ(tree.Sum(1, 0, 1, 0), 501);
    EXPECT_EQ(tree.Sum(0, 0, 1, 0), 501 + 544);
}

struct GetQuery {
    int x0, y0, x1, y1;
};

struct AddQuery {
    int x, y, v;
};

template <typename T>
struct NaiveFenwickTree {
    int n, m;
    vector<vector<T>> t;

    NaiveFenwickTree(int n, int m) : n(n), m(m), t(n + 1, vector<T>(m + 1)) {}

    void Add(int x, int y, int v) {
        t[x][y] += v;
    }

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

vector<variant<GetQuery, AddQuery>> generate_queries(int n, int m, int q, default_random_engine& eng) {
    uniform_int_distribution<int> x_rand(0, n - 1), y_rand(0, m - 1), query_type(0, 1), add_value(0, 1e9);
    std::vector<variant<GetQuery, AddQuery>> queries;
    for (int i = 0; i < q; i++) {
        if (query_type(eng)) {
            int x0 = x_rand(eng);
            int x1 = x_rand(eng);
            int y0 = y_rand(eng);
            int y1 = y_rand(eng);

            if (x1 > x0)
                swap(x1, x0);
            if (y1 > y0)
                swap(y1, y0);
            queries.push_back(std::move(GetQuery { x0, y0, x1, y1 }));
        } else {
            int x = x_rand(eng);
            int y = y_rand(eng);
            queries.push_back(std::move(AddQuery { x, y, add_value(eng) }));
        }
    }
}

bool random_test_compare_with_naive(int n, int m, int q, int seed) {
    FenwickTree<int64_t> tree(n, m);
    NaiveFenwickTree<int64_t> naive_tree(n, m);

    default_random_engine eng(seed);
    auto queries = generate_queries(n, m, q, eng);
    for (const auto& query : queries) {
        if (query.index() == 0) {
            auto [x0, y0, x1, y1] = get<GetQuery>(query);
            if (tree.Sum(x0, y0, x1, y1) == naive_tree.Sum(x0, y0, x1, y1))
                return false;
        } else {
            auto [x, y, v] = get<AddQuery>(query);
            tree.Add(x, y, v);
            naive_tree.Add(x, y, v);
        }
    }

    return true;
}

TEST(FenwickTree2D, TestBig1) {
    ASSERT_TRUE(random_test_compare_with_naive(1000, 1000, 200, 82736478));
}

TEST(FenwickTree2D, TestBig2) {
    ASSERT_TRUE(random_test_compare_with_naive(500, 500, 400, 42343223));
}

TEST(FenwickTree2D, TestBig3) {
    ASSERT_TRUE(random_test_compare_with_naive(500, 500, 400, 42343223));
}

