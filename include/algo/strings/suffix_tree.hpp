#ifdef NUCLEAR_TRD_EXAMPLE
#include <bits/stdc++.h>
using namespace std;
#endif

/// &TRD_BEGIN
/// @author unknown
/// @brief Суффиксное дерево RECHECK.
struct State {
    int v;
    int pos;
    State(int v = 0, int pos = 0) : v(v), pos(pos) {}
};

struct ST {
    vector<map<char, int>> next;
    vector<int> link, par;
    vector<int> l, r;
    State ptr;
    int sz;
    string s;

    int &get(int v, char c) {
        if (!next[v].count(c)) next[v][c] = -1;
        return next[v][c];
    }

    int node() {
        next.emplace_back();
        link.emplace_back(-1);
        par.emplace_back(-1);
        l.emplace_back(0);
        r.emplace_back(0);
        return sz++;
    }

    ST(string s) : ptr(0, 0), sz(0), s(s) {
        node();
        for (int i = 0; i < (int)s.size(); ++i) add(i);
    }

    int len(int v) {
        return r[v] - l[v];
    }

    State go(State st, int from, int to) {
        while (from < to) {
            if (st.pos == len(st.v)) {
                st = State(get(st.v, s[from]), 0);
                if (st.v == -1) return st;
            } else {
                if (s[l[st.v] + st.pos] != s[from]) return {-1, -1};
                if (to - from < len(st.v) - st.pos)
                    return {st.v, st.pos + to - from};
                from += len(st.v) - st.pos;
                st.pos = len(st.v);
            }
        }
        return st;
    }

    int split(State st) {
        if (st.pos == len(st.v)) return st.v;
        if (st.pos == 0) return par[st.v];

        int cur = st.v;
        int mid = node();
        get(par[cur], s[l[cur]]) = mid;
        get(mid, s[l[cur] + st.pos]) = cur;

        l[mid] = l[cur];
        r[mid] = l[cur] + st.pos;
        l[cur] += st.pos;

        par[mid] = par[cur];
        par[cur] = mid;
        return mid;
    }

    int get_link(int v) {
        if (link[v] != -1) return link[v];
        if (par[v] == -1) return 0;
        int to = get_link(par[v]);
        return link[v] = split(go(State(to, len(to)), l[v] + (par[v] == 0), r[v]));
    }

    void add(int pos) {
        while (true) {
            State nptr = go(ptr, pos, pos + 1);
            if (nptr.v != -1) {
                ptr = nptr;
                return;
            }
            int mid = split(ptr);
            int leaf = node();
            l[leaf] = pos;
            r[leaf] = (int)s.size();
            par[leaf] = mid;
            get(mid, s[pos]) = leaf;

            ptr.v = get_link(mid);
            ptr.pos = len(ptr.v);
            if (!mid) break;
        }
    }
};

// Пример использования
inline bool example_suffix_tree() {
    ST tree("banana$");  // уникальный символ завершает суффиксы
    int edge = tree.get(0, 'b');  // 0 — корень, -1 — нет ребра
    return edge >= 0 && tree.s.substr(tree.l[edge], tree.len(edge)) == "banana$";
}
/// &TRD_END
