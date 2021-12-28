#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, m;
vector<int> adj[1001], sccadj[1001];
vector<int> dis(1001, -1), sccid(1001, -1), sccCount(1001, 0);
vector<int> maximum(1001, 0), minimum(1001, 0), maxi(1001, 0), mini(1001, 0);
int disnum = 0, sccnum = 0, pos = 0;
int memo[1001][1001];

stack<int> st;
int scc(int here) {
    int ret = dis[here] = disnum++;
    st.push(here);

    for (int there : adj[here]) {
        if (dis[there] == -1)
            ret = min(ret, scc(there));
        else if (sccid[there] == -1)
            ret = min(ret, dis[there]);
    }

    if (ret == dis[here]) {
        while (true) {
            int x = st.top(); st.pop();
            sccid[x] = sccnum;
            if (x == here) break;
        }
        ++sccnum;
    }
    return ret;
}

void dfs(int here) {
    for (int there : sccadj[here]) {
        maximum[here] += maximum[there];
    }
}

void tarjansCC() {
    for (int i = 1; i <= n; ++i)
        if (dis[i] == -1)
            scc(i);

    vector<int> inDeg(1001, 0);
    for (int here = 1; here <= n; ++here) {
        ++sccCount[sccid[here]];
        for (int there : adj[here]) {
            if (sccid[here] != sccid[there]) {
                sccadj[sccid[here]].push_back(sccid[there]);
                ++inDeg[sccid[there]];
            }
        }
    }

    
    for (int i = 0; i < sccnum; ++i) maximum[i] = minimum[i] = sccCount[i];
    for (int i = 0; i < sccnum; ++i) dfs(i);
    for (int i = 0; i < sccnum; ++i) {
        if (inDeg[i] == 0) {
            mini[pos] = minimum[i];
            maxi[pos] = maximum[i];
            ++pos;
        }
    }
}

int dp(int idx, int available) {
    if (idx >= pos) return 0;

    int &ret = memo[idx][available];
    if (ret != -1) return ret;

    ret = dp(idx + 1, available);
    if (available - mini[idx] >= 0) {
        for (int i = mini[idx]; i <= maxi[idx] && available - i >= 0; ++i) {
            ret = max(ret, dp(idx + 1, available - i) + i);
        }
    }
    return ret;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;

    for (int to = 1; to <= n; ++to) {
        int from; cin >> from;
        adj[from].push_back(to);
    }

    tarjansCC();

    memset(memo, -1, sizeof(memo));

    cout << dp(0, m) << "\n";

    return 0;
}