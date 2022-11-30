#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct NODE {
    map<string, NODE*> childs;

    void insert(queue<string> &q) {
        string now = q.front(); q.pop();

        if (childs.find(now) == childs.end())
            childs[now] = new NODE;

        if (!q.empty())
            childs[now]->insert(q);
    }

    void print(int level) {
        for (auto e : childs) {
            for (int i = 0; i < level; ++i) cout << "--";
            cout << e.first << "\n";
            e.second->print(level + 1);
        }
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    NODE *head = new NODE;

    while (n--) {
        int k; cin >> k;
        queue<string> q;
        while (k--) {
            string s; cin >> s; 
            q.push(s);
        }
        head->insert(q);
    }

    head->print(0);

    return 0;
}