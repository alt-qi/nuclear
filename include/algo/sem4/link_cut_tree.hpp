// TESTED ON https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum
// @alt-qi

using namespace std;
using i64 = int64_t;

// TODO: refactor + comments
namespace splay {
    const int inf = 1e9;
    struct Node {
        Node *l = nullptr;
        Node *r = nullptr;
        Node *p = nullptr;

        i64 sz = 0, v = 0, sm = 0;

        bool rev = false;  // reverse (lazy prop)
        i64 to_add = 0;  // add (lazy prop)

        Node(i64 v) : v(v), sm(v), sz(1) {}
    };


    bool is_root(Node* t) {
        return (!t->p || t->p->l != t && t->p->r != t);
    }

    void push(Node* t) {
        if (t->rev) {
            swap(t->l, t->r);
            if (t->l) t->l->rev ^= 1;
            if (t->r) t->r->rev ^= 1;
            t->rev = false;
        }

        t->sm += t->to_add * t->sz;
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
        push(t);

        t->sz = 1 + (t->l ? t->l->sz : 0) + (t->r ? t->r->sz : 0);
        t->sm = t->v;
        if (t->l) {
            push(t->l);
            t->sm += t->l->sm;
        }
        if (t->r) {
            push(t->r);
            t->sm += t->r->sm;
        }
    }

    void rotate(Node* t) {
        Node* p = t->p;
        Node* g = p->p;
        bool is_p_root = is_root(p);

        if (!is_p_root) push(g);
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

        if (!is_p_root) {
            if (g->l == p) g->l = t;
            else g->r = t;
            pull(g);
        }
    }

    void push_all(Node* t) {
        if (!is_root(t)) {
            push_all(t->p);
        }
        push(t);
    }

    Node* splay(Node* t) {
        push_all(t);
        while (!is_root(t)) {
            Node *p = t->p, *g = t->p->p;
            if (is_root(p)) {
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

    // create new tree with one node
    Node* create(i64 v) {
        return new Node(v);
    }

    namespace lct {
        void expose(Node* v) {
            Node *last = nullptr, *cur = v;
            while (cur != nullptr) {
                splay(cur);
                cur->r = last;
                pull(cur);
                last = cur;
                cur = cur->p;
            }
            splay(v);
        }

        void make_root(Node* v) {
            expose(v);
            v->rev = true;
            push(v);
        }

        void link(Node* v, Node* u) {
            make_root(v);
            v->p = u;
        }

        void cut(Node* v) {
            expose(v);
            Node* u = v->l;
            if (u) {
                u->p = nullptr;
                v->l = nullptr;
                pull(v);
            }
        }

        void cut(Node* v, Node* u) {
            make_root(v);
            expose(u);
            v->p = nullptr;
            u->l = nullptr;
            pull(u);
        }
    }
}
