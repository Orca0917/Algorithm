#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

#define MAX 20001

using namespace std;

int n, m; 
vector<int> adj[MAX], sccadj[MAX];

vector<int> sccid(MAX, -1), discovered(MAX, -1), outDeg(MAX, 0), inDeg(MAX, 0);
int sccnum = 0, discovernum = 0;
stack<int> st;

void init() {
    for (int i = 0; i < MAX; ++i) {
        adj[i].clear();
        sccadj[i].clear();
    }

    fill(sccid.begin(), sccid.end(), -1);
    fill(discovered.begin(), discovered.end(), -1);
    fill(outDeg.begin(), outDeg.end(), 0);
    fill(inDeg.begin(), inDeg.end(), 0);
}

int scc(int here) {
    int ret = discovered[here] = discovernum++;
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

int tarjanSCC() {
    sccnum = 0, discovernum = 0;

    for (int here = 1; here <= n; ++here)
        if (discovered[here] == -1)
            scc(here);

    for (int here = 1; here <= n; ++here)
        for (int there : adj[here])
            if (sccid[here] != sccid[there]) {
                ++outDeg[sccid[here]];
                ++inDeg[sccid[there]];
            }

    if (sccnum == 1) return 0;
    
    int in = 0, out = 0;
    for (int here = 0; here < sccnum; ++here) {
        if (outDeg[here] == 0) ++out;
        if (inDeg[here] == 0) ++in;
    }


    return max(in, out);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int testcase; cin >> testcase;
    while (testcase--) {
        init();

        cin >> n >> m;

        for (int i = 0; i < m; ++i) {
            int from, to; cin >> from >> to;
            adj[from].push_back(to);
        }

        cout << tarjanSCC() << "\n";
    }

    return 0;
}