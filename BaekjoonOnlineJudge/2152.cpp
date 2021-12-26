/**
 * @file problemSolving.cpp
 * @author 0917jong / dbwhdans / killerWhale0917.github.io
 * @brief 
 * @version 0.1
 * @date 2021-12-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
 
using namespace std;
 
int n, m, s, t; // 도시의 수, 비행로의 수, 출발지, 도착지
vector<int> adj[100001], sccadj[100001];
vector<int> sccid(100001, -1), discovered(100001, -1), cnt(100001, 0);
int sccnum = 0, vertexnum = 0;
stack<int> st;
int memo[100001];

int scc(int here) {
    int ret = discovered[here] = vertexnum++;
    st.push(here);

    for (int there : adj[here]) {
        if (discovered[there] == -1)
            ret = min(ret, scc(there));
        else if (sccid[there] == -1)
            ret = min(ret, discovered[there]);
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

int dp(int node) {
    if (node == t) return cnt[node];

    int &ret = memo[node];
    if (ret != -1) return ret;

    ret = 0;
    for (int there : sccadj[node]) {
        ret = max(ret, dp(there) + cnt[node]);
    }

    return ret;
}

int tarjanSCC() {
    for (int i = 1; i <= n; ++i)
        if (discovered[i] == -1)
            scc(i);

    memset(memo, -1, sizeof(memo));

    for (int here = 1; here <= n; ++here) {
        // cout << here << " --> " << sccid[here] << "\n";
        for (int there : adj[here]) {
            if (sccid[here] != sccid[there])
                sccadj[sccid[here]].push_back(sccid[there]);
        }
    }

    for (int here = 1; here <= n; ++here)
        cnt[sccid[here]]++;
    
    s = sccid[s];
    memo[s] = cnt[s];
    for (int here = s; here >= 0; --here) {
        if (memo[here] == -1) continue;
        for (int there : sccadj[here]) {
            memo[there] = max(memo[there], memo[here] + cnt[there]);
        }
    }
    
    int ret = memo[sccid[t]];
    if (ret == -1) ret = 0;
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m >> s >> t;

    for (int i = 0; i < m; ++i) {
        int from, to; cin >> from >> to;
        adj[from].push_back(to);
    }

    cout << tarjanSCC() << "\n";
    return 0;
}