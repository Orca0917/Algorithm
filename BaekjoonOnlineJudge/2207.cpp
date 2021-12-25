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

using namespace std;

int n, m;
vector<int> adj[20002];
vector<int> discovered(20002, -1), sccid(20002, -1);
int vertexNum = 0, sccNum = 0;

stack<int> st;

int scc(int here) {
    int ret = discovered[here] = vertexNum++;
    st.push(here);

    for (int there : adj[here]) {
        if (discovered[there] == -1)
            ret = min(ret, scc(there));
        else if(sccid[there] == -1)
            ret = min(ret, discovered[there]);
    }

    if (ret == discovered[here]) {
        while (true) {
            int x = st.top(); st.pop();
            sccid[x] = sccNum;
            if (x == here) break;
        }
        ++sccNum;
    }

    return ret;
}

bool tarjanSCC() {
    for (int i = 2; i <= n * 2 + 1; ++i) {
        if (discovered[i] == -1)
            scc(i);
    }

    for (int i = 2; i <= n * 2 + 1; i += 2) {
        if (sccid[i] == sccid[i + 1])
            return false;
    }

    return true;
}  

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        int x, y; cin >> x >> y;
        int notx, noty;

        if (x < 0) {
            notx = -x * 2;
            x = -x * 2 + 1;
        } else {
            notx = x * 2 + 1;
            x = x * 2;
        }

        if (y < 0) {
            noty = -y * 2;
            y = -y * 2 + 1;
        } else {
            noty = y * 2 + 1;
            y = y * 2;
        }

        adj[noty].push_back(x);
        adj[notx].push_back(y);
    }

    bool result = tarjanSCC();

    if (result) cout << "^_^\n";
    else cout << "OTL\n";

    return 0;
}