#ifdef NUCLEAR_TRD_EXAMPLE
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#endif

/// &TRD_BEGIN
/// @author Не указан в исходном файле
/// @brief Суффиксный автомат RECHECK.
/// @date 2026-11-06
/// @note Исправлены построение ссылок и подсчёт вхождений.

struct sufauto {
    vector<map<char, ll>> next;
    vector<ll> len, link;
 
    vector<ll> cnt;
 
    sufauto() {
        node();
    }
 
    int node(){
        next.emplace_back();
        len.push_back(0);
        link.push_back(-1);
        cnt.push_back(0); // cnt[i] = size(endpos i)
        return (int)next.size() - 1;
    }
 
    int add(int last, char ch) {
        int new_node = node();
        int sz = len.size();
        cnt[new_node] = 1;
        link[new_node] = 0;
        len[new_node] = len[last] + 1;
        for (int p = last; p != -1; p = link[p]) {
            if (!next[p].count(ch)) {
                next[p][ch] = new_node;
                continue;
            }
 
            int q = next[p][ch];
            if (len[p] + 1 == len[q]) {
                link[new_node] = q;
                break;
            }
 
            int clone_q = node();
            link[clone_q] = link[q];
            link[q] = clone_q;
            link[new_node] = clone_q;
            len[clone_q] = len[p] + 1;
            next[clone_q] = next[q];
            for (; p != -1; p = link[p]) {
                auto it = next[p].find(ch);
                if (it == next[p].end() || it->second != q) break;
                it->second = clone_q;
            }
            break;
        }
 
        return new_node;
    }
 
    void dfs_cnt(int v, vector<vector<ll>>& gr) {
        for (int u : gr[v]) dfs_cnt(u, gr);
        if (link[v] == -1) return;
        cnt[link[v]] += cnt[v];
    }
    
    
    void buildCnt() {
        int sz = len.size();
        vector<vector<ll>> gr(sz);
        for (int i = 1; i < sz; ++i) gr[link[i]].push_back(i); // дерево суф ссылок
        dfs_cnt(0, gr);
    }
};
/// &TRD_END

/// &TRD_EXAMPLE_BEGIN
// Пример использования
inline bool example_suffix_automaton() {
    sufauto sam;
    int last = 0;
    for (char c : std::string("ababa")) last = sam.add(last, c);
    sam.buildCnt();  // один раз после построения
    int v = sam.next[0].at('a');
    return sam.cnt[sam.next[v].at('b')] == 2;  // вхождения "ab"
}
/// &TRD_EXAMPLE_END
