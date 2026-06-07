// TESTED ON https://codeforces.com/gym/103997/problem/A
// @alt-qi

using namespace std;
using i64 = int64_t;

// TODO: refactor :(
namespace splay {
    const int inf = 1e9;
    struct Node {
        Node *l = nullptr;
        Node *r = nullptr;
        Node *p = nullptr;

        i64 sz = 0, v = 0, mn = 0;

        bool rev = false;  // reverse (lazy prop)
        i64 to_add = 0;  // add (lazy prop)

        Node(i64 v) : v(v), mn(v), sz(1) {}
    };

    void push(Node* t) {
        if (!t) {
            return;
        }

        if (t->rev) {
            swap(t->l, t->r);
            if (t->l) t->l->rev ^= 1;
            if (t->r) t->r->rev ^= 1;
            t->rev = false;
        }

        t->mn += t->to_add;
        t->v += t->to_add;
        if (t->l) {
            t->l->to_add += t->to_add;
        }
        if (t->r) {
            t->r->to_add += t->to_add;
        }
        t->to_add = 0;
    }

    void pull(Node* t) {
        if (!t) {
            return;
        }

        push(t);

        t->sz = 1 + (t->l ? t->l->sz : 0) + (t->r ? t->r->sz : 0);
        t->mn = t->v;
        if (t->l) {
            push(t->l);
            t->mn = min(t->mn, t->l->mn);
        }
        if (t->r) {
            push(t->r);
            t->mn = min(t->mn, t->r->mn);
        }
    }

    void rotate(Node* t) {
        Node* p = t->p;
        Node* g = p->p;

        if (g) push(g);
        push(p);
        push(t);

        if (p->l == t) {
            p->l = t->r;
            if (p->l) p->l->p = p;
            t->r = p;
        } else {
            p->r = t->l;
            if (p->r) p->r->p = p;
            t->l = p;
        }

        p->p = t;
        t->p = g;
        pull(p);
        pull(t);

        if (g) {
            if (g->l == p) g->l = t;
            else g->r = t;
            pull(g);
        }
    }

    Node* splay(Node* t) {
        while (t && t->p) {
            Node *p = t->p, *g = t->p->p;
            if (!g) {
                rotate(t);
            } else if ((g->l == p) ^ (p->l == t)) {
                rotate(t);
                rotate(t);
            } else {
                rotate(p);
                rotate(t);
            }
        }
        return t;
    }

    Node* max(Node* t) {
        if (!t) {
            return nullptr;
        }

        push(t);
        while (t->r) {
            t = t->r;
            push(t);
        }
        splay(t);
        return t;
    }

    Node* merge(Node* t1, Node* t2) {
        if (!t1) {
            return t2;
        }
        if (!t2) {
            return t1;
        }

        push(t1);
        push(t2);

        t1 = max(t1);
        t1->r = t2;
        t2->p = t1;
        pull(t1);

        return t1;
    }

    Node* get(Node* t, i64 i) {
        if (!t || i >= t->sz) {
            return nullptr;
        }

        while (t) {
            push(t);
            i64 leftsz = (t->l ? t->l->sz : 0);
            if (i < leftsz) {
                t = t->l;
            } else if (i == leftsz) {
                return splay(t);
            } else {
                i -= leftsz + 1;
                t = t->r;
            }
        }

        return nullptr;
    }

    pair<Node*, Node*> split(Node* t, i64 cnt) {
        if (!t) {
            return {nullptr, nullptr};
        }
        if (cnt >= t->sz) {
            return {t, nullptr};
        }

        t = get(t, cnt);

        Node *l = t->l, *r = t;
        if (l) {
            l->p = nullptr;
        }
        if (r) {
            r->l = nullptr;
            pull(r);
        }

        return {l, r};
    }

    void remove(Node* t) {
        if (!t) {
            return;
        }

        if (t->p) {
            if (t->p->l == t) {
                t->p->l = nullptr;
            } else {
                t->p->r = nullptr;
            }
        }

        remove(t->l);
        remove(t->r);
        delete t;
    }

    void traverse(Node* t) {
        if (!t) return;

        push(t);
        traverse(t->l);
        cout << t->v << " ";
        traverse(t->r);
    }

    Node* create(i64 v) {
        return new Node(v);
    }
}
