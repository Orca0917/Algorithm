// 아호코라식 (aho corasick)
#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

map<char, int> mp;

struct Trie {
    Trie *go[4];
    Trie *fail;
    bool is_output;

    // Constructor
    Trie() {
        fill (go, go + 4, nullptr);
        is_output = false;
    }

    // Destructor
    ~Trie() {
        for (int i = 0; i < 4; ++i)
            if (go[i]) delete go[i];
    }

    // Insertion
    void insert(const char *key) {
        if (*key == '\0') {
            is_output = true;
            return;
        }

        int next = mp[*key];
        if (!go[next]) go[next] = new Trie();
        go[next]->insert(key + 1);
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    mp['A'] = 0;
    mp['G'] = 1;
    mp['C'] = 2;
    mp['T'] = 3;

    int testcase; cin >> testcase;
    while (testcase--) {
        int n, m; cin >> n >> m;
        string dna; cin >> dna;
        string marker; cin >> marker;
        
        Trie *root = new Trie();

        set<string> disease;

        int len = marker.length();
        for (int i = 0; i < len; ++i) {
            for (int j = i + 1; j < len; ++j) {
                string rev_str = marker;
                reverse(rev_str.begin() + i, rev_str.begin() + j + 1);
                disease.insert(rev_str);
            }
        }

        root->insert(marker.c_str());
        for (string ss : disease) root->insert(ss.c_str());

        queue<Trie*> q;
        root->fail = root;
        q.push(root);

        // Make a fail path
        while (!q.empty()) {
            Trie *cur_c = q.front(); q.pop();

            for (int i = 0; i < 4; ++i) {
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
                q.push(nxt_c);
            }
        }

        int answer = 0;
        Trie *cur = root;
        for (int j = 0; j < dna.length(); ++j) {
            int nxt = mp[dna[j]];
            while (cur != root && !cur->go[nxt]) cur = cur->fail;
            if (cur->go[nxt]) cur = cur->go[nxt];
            if (cur->is_output) answer += 1;
        }

        delete root;
        cout << answer << "\n";
    }
    
    return 0;
}