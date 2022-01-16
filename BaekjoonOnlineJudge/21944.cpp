#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct Tri {
    int problem; 
    int level;
    int group;
};

struct cmp1 { // recommendation1, 2
    bool operator() (Tri a, Tri b) {
        if (a.level == b.level) return a.problem > b.problem;
        return a.level > b.level;
    }
};

struct cmp2 { // recommendation3
    bool operator() (Tri a, Tri b) {
        return a.problem < b.problem;
    }
};

pii cache[100001];

int n, m;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(cache, -1, sizeof(cache));

    set<Tri, cmp1> s1[101];
    set<Tri, cmp1> s2;
    set<Tri, cmp2> s3[101];

    cin >> n;
    for (int i = 0; i < n; ++i) {
        int p, l, g; cin >> p >> l >> g;
        s1[g].insert({p, l, g});
        s2.insert({p, l, g});
        s3[l].insert({p, l, g});
        cache[p] = {l, g};
    }

    cin >> m;
    while (m--) {
        string command; cin >> command;
        int p, l, g, x;
        if (command == "recommend") {
            cin >> g >> x;
            if (x == 1) {
                auto it = s1[g].begin();
                cout << it -> problem << "\n";
            } else if (x == -1) {
                auto it = s1[g].end();
                --it;
                cout << it -> problem << "\n";
            }
        } else if (command == "recommend2") {
            cin >> x;
            if (x == 1) {
                auto it = s2.begin();
                cout << it -> problem << "\n";
            }
            else {
                auto it = s2.end();
                --it;
                cout << it -> problem << "\n";
            }
        } else if (command == "recommend3") {
            cin >> x >> l;
            if (x == 1) {
                bool hasFound = false;
                for (int i = l; i <= 100; ++i) {
                    if (!s3[i].empty()) {
                        hasFound = true;
                        cout << s3[i].begin()->problem << "\n";
                        break;
                    }
                }
                if (hasFound == false) cout << "-1\n";

            } else if (x == -1) {
                bool hasFound = false;
                for (int i = l - 1; i > 0; --i) {
                    if (!s3[i].empty()) {
                        hasFound = true;
                        auto it = s3[i].end();
                        --it;
                        cout << it->problem << "\n";
                        break;
                    }
                }
                if (hasFound == false) cout << "-1\n";
            }
        } else if (command == "add") {
            cin >> p >> l >> g;
            s1[g].insert({p, l, g});
            s2.insert({p, l, g});
            s3[l].insert({p, l, g});
            cache[p] = {l, g};
        } else if (command == "solved") {
            cin >> p;
            s1[cache[p].second].erase({p, cache[p].first, cache[p].second});
            s2.erase({p, cache[p].first, cache[p].second});
            s3[cache[p].first].erase({p, cache[p].first, cache[p].second});
            cache[p] = {-1, -1};
        }
    }

    return 0;
}