// UNTESTED
// @alt-qi

using namespace std;
using i64 = int64_t;

namespace splay {
    struct Node {
        Node *l = nullptr, *r = nullptr, *p = nullptr;
        i64 v = 0;

        Node(i64 v) : v(v) {}
    };

    void rotate(Node* t) {
        Node* p = t->p;
        Node* g = p->p;

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
        if (g) {
            if (g->l == p) g->l = t;
            else g->r = t;
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
        while (t && t->r) {
            t = t->r;
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

        t1 = max(t1);
        t1->r = t2;
        t2->p = t1;

        return t1;
    }

    Node* find(Node* t, i64 x) {
        if (t == nullptr) {
            return nullptr;
        }

        Node* last = t;
        while (t) {
            last = t;
            if (t->v == x) break;
            if (x < t->v) {
                t = t->l;
            } else {
                t = t->r;
            }
        }

        return splay(last);
    }

    pair<Node*, Node*> split(Node* t, i64 x) {
        if (!t) {
            return {nullptr, nullptr};
        }

        t = find(t, x);

        if (t->v >= x) {
            Node* l = t->l;
            t->l = nullptr;
            if (l) {
                l->p = nullptr;
            }

            return {l, t};
        } else {
            Node* r = t->r;
            t->r = nullptr;
            if (r) {
                r->p = nullptr;
            }

            return {t, r};
        }
    }
}
