#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 2003
using namespace std;

int n, m;
vector<int> adj[MAX];
vector<int> discovered(MAX, -1), sccid(MAX, -1);
stack<int> st;
int sccnum = 0, disnum = 0;
int scc(int here) {
    int ret = discovered[here] = disnum++;
    st.push(here);

    for (int there : adj[here]) {
        if (discovered[there] == -1) ret = min(ret, scc(there));
        else if (sccid[there] == -1) ret = min(ret, discovered[there]);
    }

    if (ret == discovered[here]) {
        while (true) {
            int x = st.top(); st.pop();
            sccid[x] = sccnum;
            if (x == here) break;
        }
        ++sccnum;
    }

    return ret;
}

bool tarjanSCC() {
    sccnum = disnum = 0;
    for (int i = 2; i <= 2 * n + 1; ++i)
        if (discovered[i] == -1)
            scc(i);

    for (int i = 2; i <= 2 * n; i += 2)
        if (sccid[i] == sccid[i + 1])
            return false;

    return true;
}   

void init() {
    for (int i = 0; i < MAX; ++i)
        adj[i].clear();
    fill(discovered.begin(), discovered.end(), -1);
    fill(sccid.begin(), sccid.end(), -1);    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    auto func = [](int x) -> pii {
        int notx;
        if (x < 0) {
            x = -2 * x + 1;
            notx = x - 1;
        } else {
            x = 2 * x;
            notx = x + 1;
        }
        return {x, notx};
    };

    while (cin >> n >> m) {
        init();

        for (int i = 0; i < m; ++i) {
            int p1, p2;

            cin >> p1 >> p2;
            pii a = func(p1);
            pii b = func(p2);

            adj[a.second].push_back(b.first);
            adj[b.second].push_back(a.first);
        }

        bool result = tarjanSCC();
        cout << result << "\n";
    }

    return 0;
}