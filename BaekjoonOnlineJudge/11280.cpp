/**
 * @file problemSolving.cpp
 * @author 0917jong / dbwhdans / killerWhale0917.github.io
 * @brief 
 * @version 0.1
 * @date 2021-12-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <bits/stdc++.h>
#define ll long long
using namespace std;

vector<int> adj[20022];
vector<int> sccId, discovered;
stack<int> st;
int sccCounter, vertexCounter;
int n, m, sz;

int scc(int here) {
    int ret = discovered[here] = vertexCounter++;
    st.push(here);
    for (auto there : adj[here]) {
        if (discovered[there] == -1)
            ret = min(ret, scc(there));
        else if (sccId[there] == -1)
            ret = min(ret, discovered[there]);
    }

    if (ret == discovered[here]) {
        while (true) {
            int t = st.top(); st.pop();
            sccId[t] = sccCounter;
            if (t == here) break;
        }
        sccCounter++;
    }
    return ret;
}

vector<int> tarjanSCC() {
    sz = ((n + 1) << 1) + 1;
    sccId = discovered = vector<int>(sz, -1);
    sccCounter = vertexCounter = 1;
    for (int i = 2; i < sz; ++i)
        if (discovered[i] == -1)
            scc(i);
    return sccId;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    for (int q = 0; q < m; ++q) {
        int i, j, ni, nj; cin >> i >> j;

        if (i < 0) {
            i = -i * 2 + 1;
            ni = i - 1;
        } else {
            i = i * 2;
            ni = i + 1;
        }

        if (j < 0) {
            j = -j * 2 + 1;
            nj = j - 1;
        } else {
            j = j * 2;
            nj = j + 1;
        }

        adj[ni].push_back(j);
        adj[nj].push_back(i);
    }

    tarjanSCC();
    int answer = 1;
    for (int i = 2; i < sz && answer; i += 2) {
        if (sccId[i] == sccId[i + 1])
            answer = 0;
    }

    cout << answer << "\n";
    return 0;
}