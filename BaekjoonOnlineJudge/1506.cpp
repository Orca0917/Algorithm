#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<int> cost(101, 0);
vector<int> adj[101];
vector<int> sccid(101, -1), discovered(101, -1);
int sccnum = 0, discovernum = 0;
stack<int> st;

int n;

int scc(int here) {
    int ret = discovered[here] = discovernum++;
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

int tarjanSCC() {

    for (int i = 0; i < n; ++i) {
        if (discovered[i] == -1)
            scc(i);
    }

    vector<int> minCost(sccnum, 1000000);
    for (int i = 0; i < n; ++i) {
        minCost[sccid[i]] = min(minCost[sccid[i]], cost[i]);
    }

    return accumulate(minCost.begin(), minCost.end(), 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> cost[i];
    }

    for (int i = 0; i < n; ++i) {
        char c;
        for (int j = 0; j < n; ++j) {
            cin >> c;
            if (c == '1') adj[i].push_back(j);
        }
    }

    cout << tarjanSCC() << "\n";

    return 0;
}