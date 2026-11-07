#ifdef NUCLEAR_TRD_EXAMPLE
#include <bits/stdc++.h>
using namespace std;
#endif

/// &TRD_BEGIN
/// @author unknown
/// @brief Min Cost Max Flow (MCMF).
struct MCMF {
    using ll = long long;
    static const ll INF = (1LL << 61);

    struct Edge {
        int from, to;
        ll cap, cost;
        Edge(int _from, int _to, ll _cap, ll _cost)
            : from(_from), to(_to), cap(_cap), cost(_cost) {}
    };

    int n, s, t;
    ll flow, min_cost;
    vector<vector<int>> g;
    vector<Edge> e;
    vector<ll> d, potential;
    vector<int> par;
    bool neg;

    MCMF(int _n = 0) { // 0-based
        init(_n);
    }

    void init(int _n) {
        n = _n + 10;
        g.assign(n, {});
        e.clear();
        potential.assign(n, 0);
        neg = false;
    }

    void add_edge(int u, int v, ll cap, ll cost, bool directed = true) {
        if (cost < 0) neg = true;
        int id = (int)e.size();
        g[u].push_back(id);
        e.emplace_back(u, v, cap, cost);
        g[v].push_back(id ^ 1);
        e.emplace_back(v, u, 0, -cost);
        if (!directed)
            add_edge(v, u, cap, cost, true);
    }

    bool dijkstra() {
        par.assign(n, -1);
        d.assign(n, INF);

        using P = pair<ll, int>;
        priority_queue<P, vector<P>, greater<P>> q;

        d[s] = 0;
        q.emplace(0, s);

        while (!q.empty()) {
            auto [dist, v] = q.top();
            q.pop();
            if (dist != d[v]) continue;
            for (int id : g[v]) {
                const Edge &ed = e[id];
                if (ed.cap <= 0) continue;
                int to = ed.to;
                ll w = ed.cost + potential[v] - potential[to];
                if (d[v] + w < d[to]) {
                    d[to] = d[v] + w;
                    par[to] = id;
                    q.emplace(d[to], to);
                }
            }
        }

        if (d[t] == INF) return false;

        // стандартное обновление потенциалов
        for (int i = 0; i < n; i++) {
            if (d[i] < INF)
                potential[i] += d[i];
        }

        return true;
    }

    ll send_flow(int v, ll cur) {
        if (par[v] == -1) return cur;
        int id = par[v];
        int from = e[id].from;
        ll f = send_flow(from, min(cur, e[id].cap));
        e[id].cap     -= f;
        e[id ^ 1].cap += f;
        min_cost      += f * e[id].cost; // оригинальная стоимость
        return f;
    }

    // возвращает {maxflow, mincost}
    pair<ll, ll> solve(int _s, int _t, ll goal = INF) {
        s = _s;
        t = _t;
        flow = 0;
        min_cost = 0;
        potential.assign(n, 0);

        if (neg) {
            // Bellman–Ford для стартовых потенциалов
            d.assign(n, INF);
            d[s] = 0;
            bool relax = true;
            for (int it = 0; it < n && relax; ++it) {
                relax = false;
                for (int v = 0; v < n; ++v) {
                    if (d[v] == INF) continue;
                    for (int id : g[v]) {
                        const Edge &ed = e[id];
                        if (ed.cap <= 0) continue;
                        int to = ed.to;
                        if (d[to] > d[v] + ed.cost) {
                            d[to] = d[v] + ed.cost;
                            relax = true;
                        }
                    }
                }
            }
            for (int i = 0; i < n; i++)
                if (d[i] < INF)
                    potential[i] = d[i];
        }

        while (flow < goal && dijkstra()) {
            flow += send_flow(t, goal - flow);
        }
        return {flow, min_cost};
    }
};

// Пример использования
inline bool example_mcmf() {
    MCMF net(3);
    net.add_edge(0, 1, 3, 1); net.add_edge(1, 2, 3, 2);  // ёмкость, цена
    auto [flow, cost] = net.solve(0, 2, 2);  // исток, сток, лимит
    return flow == 2 && cost == 6;
}
/// &TRD_END

#ifdef NUCLEAR_TRD_EXAMPLE
inline const MCMF::ll MCMF::INF;
#endif
