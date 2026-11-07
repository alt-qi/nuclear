/// &TRD_BEGIN
/// @author Не указан в исходном файле
/// @brief Декартово дерево (явное/неявное, sum + size) RECHECK.
/// @date 2026-11-06
/// @note Дата переноса; код из приложенного файла без изменений.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;

struct treap {
    struct node {
        ll x, sum, sz; ull y;
        node *l, *r;
        node(): x(0), sum(0), sz(0), y(0), l(nullptr), r(nullptr) {}
    };

    static const int maxn = 300000 + 10;

    node pool[maxn];
    int nodesz = 0;
    mt19937_64 rng;
    node* root = nullptr;

    treap(): rng((uint64_t)chrono::steady_clock::now().time_since_epoch().count()) {}

    node* getnode(ll x = 0) {
        node* p = &pool[nodesz++];
        p->x = x; p->sum = x; p->sz = 1; p->l = p->r = nullptr; p->y = rng();
        return p;
    }

    ll getsum(node* v) const { return v ? v->sum : 0; }
    ll getsz(node* v)  const { return v ? v->sz  : 0; }

    void updatesum(node* v) { v->sum = getsum(v->l) + getsum(v->r) + v->x; }
    void updatesz(node* v)  { v->sz  = getsz(v->l)  + getsz(v->r)  + 1; }

    void update(node* v) {
        if (!v) return;
        updatesz(v);
        updatesum(v);
    }

    // < x , >= x
    void split(node* v, node*& l, node*& r, ll x) {
        if (!v) { l = r = nullptr; return; }
        if (v->x < x) {
            split(v->r, v->r, r, x);
            l = v; update(l);
        } else {
            split(v->l, l, v->l, x);
            r = v; update(r);
        }
    }

    void merge(node*& v, node* l, node* r) {
        if (!l || !r) { v = l ? l : r; return; }
        if (l->y > r->y) {
            merge(l->r, l->r, r);
            v = l; update(v);
        } else {
            merge(r->l, l, r->l);
            v = r; update(v);
        }
    }

    // [1, k] + [k + 1, ... ]
    void splitk(node* v, node*& l, node*& r, ll k) {
        if (!v || k == 0) { l = nullptr; r = v; return; }
        if (k - getsz(v->l) - 1 >= 0) {
            splitk(v->r, v->r, r, k - getsz(v->l) - 1);
            l = v; update(l);
        } else {
            splitk(v->l, l, v->l, k);
            r = v; update(r);
        }
    }

    void insert(ll x) {
        node *t1 = nullptr, *t3 = nullptr, *t2 = getnode(x);
        split(root, t1, t3, x);
        merge(root, t1, t2);
        merge(root, root, t3);
    }

    void erase_value(ll x) {
        node *t1 = nullptr, *t2 = nullptr, *t3 = nullptr;
        split(root, t1, t2, x);
        split(t2, t2, t3, x + 1);
        merge(root, t1, t3);
    }

    int kth(int k) {
        node *t1 = nullptr, *t2 = nullptr, *t3 = nullptr;
        splitk(root, t2, t3, k);
        splitk(t2, t1, t2, k - 1);
        int res = t2->x;
        merge(root, t1, t2);
        merge(root, root, t3);
        return res;
    }

    void print_inorder(node* v) {
        if (!v) return;
        print_inorder(v->l);
        cout << v->x << ' ';
        print_inorder(v->r);
    }

    int size() const { return (int)getsz(root); }
    ll sum()  const { return getsum(root); }
};
/// &TRD_END

/// &TRD_EXAMPLE_BEGIN
// Пример использования
inline bool example_treap() {
    auto t = std::make_unique<treap>();  // большой пул выделяем в куче
    t->insert(2); t->insert(5); t->insert(5);
    bool ok = t->kth(1) == 2 && t->sum() == 12;  // ранг с единицы
    t->erase_value(5);  // удаляет все копии
    return ok && t->size() == 1;
}
/// &TRD_EXAMPLE_END
