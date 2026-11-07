#ifdef NUCLEAR_TRD_EXAMPLE
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int N = 16;
#endif

/// &TRD_BEGIN
/// @author Не указан в исходном файле
/// @brief HLD RECHECK.
/// @date 2026-11-06
/// @note Дата переноса; код из приложенного файла без изменений.

int n, q;
vector<int> g[N];
ll vertex_value[N];
int sz[N];
int par[N];

void calc_sz(int v, int p_node = 0) {
    par[v] = p_node;
    sz[v] = 1;
    
    int heavy_child_candidate = -1;
    int max_sz_child = 0;

    for (int i = 0; i < g[v].size(); ++i) {
        int& u = g[v][i];
        if (u == p_node) continue;
        
        calc_sz(u, v);
        sz[v] += sz[u];
        
        if (sz[u] > max_sz_child) {
            max_sz_child = sz[u];
        }
    }
    
    for (int i = 0; i < g[v].size(); ++i) {
        int u = g[v][i];
        if (u == p_node) continue;
        if (sz[u] == max_sz_child && max_sz_child > 0) {
            swap(g[v][0], g[v][i]);
            break; 
        }
    }
    if (!g[v].empty() && g[v][0] == p_node) {
        for(int i = 1; i < g[v].size(); ++i) {
            if(g[v][i] != p_node) {
                swap(g[v][0], g[v][i]);
                break;
            }
        }
    }
}

int timer;
int tin[N];
int tout[N];
int head[N];

void mark_vertexes(int v, int p_node, bool heavy_way) {
    tin[v] = timer++;
    if (heavy_way) {
        head[v] = head[p_node];
    } else {
        head[v] = v;
    }

    if (!g[v].empty() && g[v][0] != p_node) {
        mark_vertexes(g[v][0], v, true);
    }

    for (int i = 0; i < g[v].size(); ++i) {
        int u = g[v][i];
        if (u == p_node || u == g[v][0]) continue;
        mark_vertexes(u, v, false);
    }
    tout[v] = timer;
}

class Node {
public:
    ll value;
    Node(ll x = 0) : value(x) {}
};

ostream& operator<<(ostream& out, const Node& nd) {
    out << nd.value;
    return out;
}

Node nll_node(0);

Node t[2 * N];
Node a[N + 1];

Node combine(Node l, Node r) {
    return Node(l.value + r.value);
}

void build(int v_seg, int vl, int vr) {
    if (vl + 1 == vr) {
        t[v_seg] = a[vl];
        return;
    }
    int vm = vl + (vr - vl) / 2;
    build(2 * v_seg, vl, vm);
    build(2 * v_seg + 1, vm, vr);
    t[v_seg] = combine(t[2 * v_seg], t[2 * v_seg + 1]);
}

void update(int v_seg, int vl, int vr, int index_to_update, Node new_val_node) {
    if (vl + 1 == vr) {
        t[v_seg] = new_val_node;
        return;
    }
    int vm = vl + (vr - vl) / 2;
    if (index_to_update < vm) {
        update(2 * v_seg, vl, vm, index_to_update, new_val_node);
    } else {
        update(2 * v_seg + 1, vm, vr, index_to_update, new_val_node);
    }
    t[v_seg] = combine(t[2 * v_seg], t[2 * v_seg + 1]);
}

Node get(int v_seg, int vl, int vr, int ql, int qr_inclusive) {
    if (ql > qr_inclusive) return nll_node;

    if (ql <= vl && (vr - 1) <= qr_inclusive) {
        return t[v_seg];
    }
    if ((vr - 1) < ql || qr_inclusive < vl) {
        return nll_node;
    }

    int vm = vl + (vr - vl) / 2;
    Node left_res = get(2 * v_seg, vl, vm, ql, qr_inclusive);
    Node right_res = get(2 * v_seg + 1, vm, vr, ql, qr_inclusive);
    return combine(left_res, right_res);
}

bool ancestor(int v_anc, int u_desc) {
    if (v_anc == 0) return true;
    if (u_desc == 0) return false;
    return tin[v_anc] <= tin[u_desc] && tin[u_desc] < tout[v_anc];
}

ll get_way_value(int cur_a, int cur_b) {
    ll result = 0;
    
    int original_a = cur_a;
    int original_b = cur_b;

    while (!ancestor(head[cur_a], original_b)) {
        if (cur_a == 0) break;
        result += get(1, 1, n + 1, tin[head[cur_a]], tin[cur_a]).value;
        cur_a = par[head[cur_a]];
    }
    
    while (!ancestor(head[cur_b], original_a)) {
        if (cur_b == 0) break;
        result += get(1, 1, n + 1, tin[head[cur_b]], tin[cur_b]).value;
        cur_b = par[head[cur_b]];
    }

    if (tin[cur_a] > tin[cur_b]) {
        swap(cur_a, cur_b);
    }
    result += get(1, 1, n + 1, tin[cur_a], tin[cur_b]).value;
    
    return result;
}

void build_hld() {
    calc_sz(1, 0);

    timer = 1;
    mark_vertexes(1, 0, false);

    for (int i = 1; i <= n; ++i) {
        a[tin[i]] = Node(vertex_value[i]);
    }
    build(1, 1, n + 1);
}

void solve() {
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        cin >> vertex_value[i + 1];
    }

    for (int i = 0; i < n - 1; ++i) {
        int v, u;
        cin >> v >> u;
        v++; u++;
        g[v].push_back(u);
        g[u].push_back(v);
    }

    build_hld();

    while (q--) {
        int type;
        cin >> type;
        if (type == 0) {
            int ind, x;
            cin >> ind >> x;
            ind++;

            vertex_value[ind] += (ll)x;
            update(1, 1, n + 1, tin[ind], Node(vertex_value[ind]));
        } else {
            int v, u;
            cin >> v >> u;
            v++; u++;
            cout << get_way_value(v, u) << "\n";
        }
    }
}

// Пример использования
inline bool example_hld() {
    n = 2; g[1] = {2}; g[2] = {1};  // вершины с единицы
    vertex_value[1] = 3; vertex_value[2] = 5;
    build_hld();  // корень 1
    bool ok = get_way_value(1, 2) == 8;  // сумма на пути
    update(1, 1, n + 1, tin[2], Node(9));  // заменить вес вершины 2
    return ok && get_way_value(1, 2) == 12;
}
/// &TRD_END
