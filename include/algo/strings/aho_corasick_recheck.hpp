#ifdef NUCLEAR_TRD_EXAMPLE
#include <bits/stdc++.h>
using namespace std;
#endif

/// &TRD_BEGIN
/// @author Не указан в исходном файле
/// @brief Ахо — Корасик RECHECK.
/// @date 2026-11-06
/// @note Дата переноса; код из приложенного файла без изменений.

struct Aho {
    const int A = 26;
    int node_cnt, pattern_cnt;
    vector<vector<int>> next;
    vector<vector<int>> terminals;
    vector<int> suf_link, terminal_link;

    Aho() : node_cnt(0), pattern_cnt(0) { node(); }

    int node() {
        next.emplace_back(A);
        terminals.emplace_back();
        suf_link.emplace_back();
        terminal_link.emplace_back();
        return node_cnt++;
    }

    inline int get(char c) {
        return c - 'a';
    }

    int add_pattern(const string &s) {
        int v = 0;
        for (auto c: s) {
            if (!next[v][get(c)]) next[v][get(c)] = node();
            v = next[v][get(c)];
        }
        terminals[v].emplace_back(pattern_cnt);
        return pattern_cnt++;
    }

    void build() {
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int par = q.front();
            q.pop();
            for (int c = 0; c < A; ++c) {
                int child = next[par][c];
                if (!child) {
                    next[par][c] = next[suf_link[par]][c];
                    continue;
                }
                // set suffix link
                if (par == 0) suf_link[child] = 0;
                else suf_link[child] = next[suf_link[par]][c];

                // set terminal link
                if (terminals[suf_link[child]].empty()) terminal_link[child] = terminal_link[suf_link[child]];
                else terminal_link[child] = suf_link[child];

                q.push(child);
            }
        }
    }

    int go(int v, char c) {
        return next[v][get(c)];
    }

    // get all matches ending at given position
    vector<int> get_matches(int v) {
        vector<int> res;
        while (v) {
            for (auto match: terminals[v]) res.emplace_back(match);
            v = terminal_link[v];
        }
        return res;
    }
};
/// &TRD_END

/// &TRD_EXAMPLE_BEGIN
// Пример использования
inline bool example_aho_corasick() {
    Aho aho;  // непустые шаблоны из a..z
    int id = aho.add_pattern("ab");
    aho.build();  // после всех добавлений
    int state = aho.go(aho.go(0, 'a'), 'b');
    return aho.get_matches(state) == std::vector<int>{id};
}
/// &TRD_EXAMPLE_END
