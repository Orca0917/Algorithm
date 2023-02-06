// 아호코라식 (aho corasick)
#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

struct Trie {
    Trie *go['z' - 'a' + 1];
    Trie *fail;
    bool is_output;

    // Constructor
    Trie() {
        fill (go, go + 'z' - 'a' + 1, nullptr);
        is_output = false;
    }

    // Destructor
    ~Trie() {
        for (int i = 0; i < 'z' - 'a' + 1; ++i)
            if (go[i]) delete go[i];
    }

    // Insertion
    void insert(const char *key) {
        if (*key == '\0') {
            is_output = true;
            return;
        }

        int next = *key - 'a';
        if (!go[next]) go[next] = new Trie();
        go[next]->insert(key + 1);
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;

    Trie *root = new Trie();
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        root->insert(s.c_str());
    }

    queue<Trie*> que;
    root->fail = root;
    que.push(root);

    // Make a fail path
    while (!que.empty()) {
        Trie *cur_c = que.front(); que.pop();

        for (int i = 0; i < 'z' - 'a' + 1; ++i) {
            Trie *nxt_c = cur_c->go[i];
            if (!nxt_c) continue;
            if (cur_c == root) nxt_c->fail = root;    // root->fail = root
            else {
                Trie *failure = cur_c->fail;
                while (failure != root && !failure->go[i])
                    failure = failure->fail;
                if (failure->go[i]) failure = failure->go[i];   // fail(px) = go(fail(p), x)
                nxt_c->fail = failure;
            }
            if (nxt_c->fail->is_output) nxt_c->is_output = true;
            que.push(nxt_c);
        }
    }

    int q; cin >> q;
    for (int i = 0; i < q; ++i) {
        string s; cin >> s;

        Trie *cur = root;
        bool ans = false;
        for (int j = 0; j < s.length() && !ans; ++j) {
            int nxt = s[j] - 'a';
            while (cur != root && !cur->go[nxt]) cur = cur->fail;
            if (cur->go[nxt]) cur = cur->go[nxt];
            if (cur->is_output) ans = true;
        }

        cout << (ans ? "YES" : "NO") << "\n";
    }
    delete root;
    
    return 0;
}