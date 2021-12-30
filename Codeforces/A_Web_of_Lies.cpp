#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;
vector<int> inDeg;
vector<bool> alive;
int result;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m; cin >> n >> m;

    inDeg.resize(n + 1, 0);
    alive.resize(n + 1, true);
    result = n;

    for (int i = 0; i < m; ++i) {
        int from, to; cin >> from >> to;
        if (from < to) swap(from, to);
        ++inDeg[to];
        if (inDeg[to] > 0 && alive[to]) {
            --result;
            alive[to] = false;
        } 
    }

    int q; cin >> q;
    while (q--) {
        int option; cin >> option;
        if (option == 1) {
            int u, v; cin >> u >> v;
            if (u < v) swap(u, v);
            ++inDeg[v];
            if (inDeg[v] > 0 && alive[v]) {
                --result;
                alive[v] = false;
            }
        } else if (option == 2) {
            int u, v; cin >> u >> v;
            if (u < v) swap(u, v);
            --inDeg[v];
            if (inDeg[v] == 0) {
                ++result;
                alive[v] = true;
            }
        } else {
            cout << result << "\n";
        }
    }
    return 0;
}