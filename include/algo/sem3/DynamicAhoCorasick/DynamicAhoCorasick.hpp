#include <vector>
#include <string>
#include <queue>
#include <cstring>

using namespace std;

using ll = long long;

struct AhoCorasick {
    static const int ALPHABET = 26;
    struct Node {
        int next[ALPHABET];   // переходы автомата
        int go[ALPHABET];     // реальные переходы в боре
        int link = 0;         // суфф ссылка
        int up = 0;           // сжатая суфф ссылка (ведёт до ближайшего терминала)
        int cnt = 0;          // кол-во терминальных вершин в поддереве суф ссылок
        int pattern_ind = -1; // индекс паттерна

        Node() {
            fill(next, next + ALPHABET,  -1);
            fill(go, go + ALPHABET, -1);
        }
    };

    vector<Node> nodes;
    bool built = false;

    AhoCorasick() {
        clear();
    }

    inline void clear() {
        nodes.clear();
        nodes.emplace_back();
        built = false;
    }

    inline int get_char(char c) {
        return c - 'a';
    }

    void add_pattern(const string& s, int id=0) {
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
            int v = q.front(); q.pop();
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
    ll count_matches(int v) const {
        return nodes[v].cnt;
    }
    
    int next_state(int v, char c) {
        return nodes[v].next[get_char(c)];
    }
};

struct DynamicAho {
    struct Layer {
        AhoCorasick aho;
        vector<string> words;
        
        void clear() {
            aho.clear();
            words.clear();
        }
    };
    vector<Layer> layers; // инвариант - если layers[i] не пуст, то в нём 2^i строк
    
    // добавление строки: O(|S| * log N)
    void add_string(const string& s) {
        vector<string> current_words = {s};
        int i = 0;
        
        // Ищем свободный слой, собираем слова из занятых
        while (i < int(layers.size()) && !layers[i].words.empty()) {
            // сливаем слова на этом уровне
            current_words.insert(current_words.end(), 
                                 layers[i].words.begin(), 
                                 layers[i].words.end());
            layers[i].clear();
            i++;
        }

        // если вышли за пределы вектора, добавляем новый слой
        if (i == int(layers.size())) {
            layers.emplace_back();
        }

        // Строим новый слой (бит становится 1)
        layers[i].words = current_words;
        for (const string& w : layers[i].words) {
            layers[i].aho.add_pattern(w);
        }
        layers[i].aho.build();
    }

    // общее количество вхождений всех паттернов в текст O(|Text| * log N)
    ll count_total_matches(const string& text) {
        ll ans = 0;
        for (auto& layer : layers) {
            if (layer.words.empty()) continue;

            int v = 0;
            for (char c : text) {
                v = layer.aho.next_state(v, c);
                ans += layer.aho.count_matches(v);
            }
        }
        return ans;
    }
};


// добавить s
// удалить s
// найти кол-во вхождений строк из множества в s
// https://codeforces.com/problemset/problem/710/F?f0a28=1
// void example() {
//     int m;
//     cin >> m;
//     DynamicAho daho_added, daho_removed;
//     while (m--) {
//         int type; string s;
//         cin >> type >> s;
//         if (type == 1) {
//             daho_added.add_string(s);
//         } else if (type == 2) {
//             daho_removed.add_string(s);
//         } else {
//             cout << daho_added.count_total_matches(s) - daho_removed.count_total_matches(s) << "\n";
//         }
//     }
// }
