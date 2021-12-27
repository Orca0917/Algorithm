#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;
int n, m; 
vector<int> adj[5001], sccadj[5001];
vector<int> sccid(5001, -1), discover(5001, -1);
stack<int> st;
int sccnum = 0, disnum = 0;

int scc(int here) {
    int ret = discover[here] = disnum++;
    st.push(here);
    
    for (int there : adj[here]) {
        if (discover[there] == -1)
            ret = min(ret, scc(there));
        else if (sccid[there] == -1)
            ret = min(ret, discover[there]);
    }

    if (ret == discover[here]) {
        while (true) {
            int x = st.top(); st.pop();
            sccid[x] = sccnum;
            if (x == here) break;
        }
        ++sccnum;
    }

    return ret;
}

void tarjanSCC() {
    sccnum = 0, disnum = 0;
    for (int i = 1; i <= n; ++i) {
        if (discover[i] == -1)
            scc(i);
    }

    vector<int> outDeg(5001, 0);
    vector<int> scclist[5001];

    for (int i = 1; i <= n; ++i) {
        scclist[sccid[i]].push_back(i);
        for (int there : adj[i]) {
            if (sccid[i] != sccid[there]) {
                sccadj[sccid[i]].push_back(sccid[there]);
                outDeg[sccid[i]]++;
            }
        }
    }

    vector<int> answer;
    for (int i = 0; i < sccnum; ++i) {
        if (outDeg[i] == 0)
            for (int j = 0; j < scclist[i].size(); ++j) {
                answer.push_back(scclist[i][j]);
            }
    }

    sort(answer.begin(), answer.end());

    for (int e : answer) cout << e << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (true) {
        cin >> n;
        if (n == 0) break;
        cin >> m;

        for (int i = 0; i < 5001; ++i) {
            adj[i].clear();
            sccadj[i].clear();
        }
        fill(sccid.begin(), sccid.end(), -1);
        fill(discover.begin(), discover.end(), -1);

        for (int i = 0; i < m; ++i) {
            int from, to; cin >> from >> to;
            adj[from].push_back(to);
        }

        tarjanSCC();
    }   
    return 0;
}