#ifdef NUCLEAR_TRD_EXAMPLE
#include <bits/stdc++.h>
using namespace std;
#endif

/// &TRD_BEGIN
/// @author egor
struct AhoCorasick {
    static const int ALPHABET = 26;
    struct Node {
        int next[ALPHABET];    // переходы автомата
        int go[ALPHABET];      // реальные переходы в боре
        int link = 0;          // суфф ссылка
        int up = 0;            // сжатая суфф ссылка (ведёт до ближайшего терминала)
        int cnt = 0;           // кол-во терминальных вершин в поддереве суф ссылок
        int pattern_ind = -1;  // индекс паттерна

        Node() {
            fill(next, next + ALPHABET, -1);
            fill(go, go + ALPHABET, -1);
        }
    };

    vector<Node> nodes;
    bool built = false;

    AhoCorasick() { clear(); }

    inline void clear() {
        nodes.clear();
        nodes.emplace_back();
        built = false;
    }

    inline int get_char(char c) { return c - 'a'; }

    void add_pattern(const string& s, int id = 0) {
        int v = 0;
        for (char c : s) {
            int x = get_char(c);
            if (nodes[v].go[x] == -1) {
                nodes[v].go[x] = nodes.size();
                nodes.emplace_back();
            }
            v = nodes[v].go[x];
        }
        nodes[v].cnt++;
        nodes[v].pattern_ind = id;
    }

    void build() {
        queue<int> q;
        // обрабатываем соседей корня
        for (int c = 0; c < ALPHABET; ++c) {
            if (nodes[0].go[c] != -1) {
                nodes[0].next[c] = nodes[0].go[c];
                q.push(nodes[0].go[c]);
            } else {
                nodes[0].next[c] = 0;
            }
        }

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            int u = nodes[v].link;

            // проталкиваем терминальность
            nodes[v].up = (nodes[u].cnt > 0) ? u : nodes[u].up;
            nodes[v].cnt += nodes[u].cnt;

            for (int c = 0; c < ALPHABET; ++c) {
                if (nodes[v].go[c] != -1) {
                    // вычисляем суфф сылку для ребёнка
                    int to = nodes[v].go[c];
                    nodes[v].next[c] = to;
                    nodes[to].link = nodes[u].next[c];
                    q.push(to);
                } else {
                    nodes[v].next[c] = nodes[u].next[c];
                }
            }
        }
        built = true;
    }

    // кол-во совпадений, заканчивающихся в текущем символе
    ll count_matches(int v) const { return nodes[v].cnt; }

    int next_state(int v, char c) { return nodes[v].next[get_char(c)]; }
};
// &TRD_END
