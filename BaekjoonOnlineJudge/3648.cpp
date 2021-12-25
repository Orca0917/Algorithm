/**
 * @file problemSolving.cpp
 * @author 0917jong / dbwhdans / killerWhale0917.github.io
 * @brief 
 * @version 0.1
 * @date 2021-12-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n;
int m;

vector<int> sccid(2005, -1), discovered(2005, -1);
int sccNum = 0, vertexNum = 0;
vector<int> adj[2005];
stack<int> st;

pii change(int x) {
    int notx;

    if (x < 0) {
        notx = -x * 2;
        x = -x * 2 + 1;
    } else {
        notx = x * 2 + 1;
        x = x * 2;
    }

    return {x, notx};
}

int scc(int here) {
    int ret = discovered[here] = vertexNum++;
    st.push(here);

    for (int there : adj[here]) {
        if (discovered[there] == -1)
            ret = min(ret, scc(there));
        else if (sccid[there] == -1)
            ret = min(ret, discovered[there]);
    }

    if (ret == discovered[here]) {
        while (true) {
            int now = st.top(); st.pop();
            sccid[now] = sccNum;
            if (now == here) break;
        }
        ++sccNum;
    }

    return ret;
}

bool tarjanSCC() {
    for (int i = 2; i <= (n + 1) * 2; ++i)
        if (discovered[i] == -1)
            scc(i);

    bool ret = true;
    for (int i = 2; i <= (n + 1) * 2 && ret; i += 2)
        if (sccid[i] == sccid[i + 1])
            ret = false;

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (cin >> n >> m) {
        fill(sccid.begin(), sccid.end(), -1);
        fill(discovered.begin(), discovered.end(), -1);
        sccNum = 0, vertexNum = 0;
        for (int i = 0; i < 2005; ++i) adj[i].clear();

        adj[3].push_back(2);
        for (int i = 0; i < m; ++i) {
            pii a, b; cin >> a.first >> b.first;

            a = change(a.first);
            b = change(b.first);

            adj[a.second].push_back(b.first);
            adj[b.second].push_back(a.first);
        }

        bool result = tarjanSCC();

        cout << (result ? "yes" : "no") << "\n";
    }

    return 0;
}