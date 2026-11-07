/// &TRD_BEGIN
/// @author Не указан в исходном файле
/// @brief Диниц O(V²E) RECHECK.
/// @date 2026-11-06
/// @note Дата переноса; код из приложенного файла без изменений.

#include <bits/stdc++.h>
using namespace std;

struct Dinic {
    using ll = long long;

    struct Edge {
        int to;
        ll cap;
        int rev;
    };

    int n;
    vector<vector<Edge>> g;
    vector<int> level;
    vector<int> it;

    Dinic(int n) : n(n), g(n), level(n), it(n) {}

    void add_edge(int u, int v, ll cap) {
        Edge a{v, cap, (int)g[v].size()};
        Edge b{u, 0,   (int)g[u].size()};
        g[u].push_back(a);
        g[v].push_back(b);
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (const Edge &e : g[v]) {
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] >= 0;
    }

    ll dfs(int v, int t, ll f) {
        if (v == t) return f;
        for (int &i = it[v]; i < (int)g[v].size(); ++i) {
            Edge &e = g[v][i];
            if (e.cap > 0 && level[e.to] == level[v] + 1) {
                ll pushed = dfs(e.to, t, min(f, e.cap));
                if (pushed > 0) {
                    e.cap -= pushed;
                    g[e.to][e.rev].cap += pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }

    ll max_flow(int s, int t) {
        const ll INF = (ll)4e18;
        ll flow = 0;
        while (bfs(s, t)) {
            fill(it.begin(), it.end(), 0);
            ll f;
            while ((f = dfs(s, t, INF)) > 0) {
                flow += f;
            }
        }
        return flow;
    }
};

// Пример использования
inline bool example_dinic() {
    Dinic flow(3);  // вершины 0..2
    flow.add_edge(0, 1, 3); flow.add_edge(1, 2, 2);  // дуги, ёмкости
    return flow.max_flow(0, 2) == 2;  // исток, сток
}
/// &TRD_END
