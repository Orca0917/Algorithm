#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<int> adj[1000001], sccadj[1000001];
vector<int> discovered(1000001, -1), sccid(1000001, -1);
int sccnum = 0, disnum = 0;
stack<int> st;
int n, m;

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

vector<int> tarjanSCC() {
    for (int i = 1; i <= n; ++i)
        if (discovered[i] == -1)
            scc(i);

    vector <int> inDegree(sccnum, 0);
    for (int i = 1; i <= n; ++i)
        for (int there : adj[i])
            if (sccid[i] != sccid[there]) {
                sccadj[sccid[i]].push_back(sccid[there]);
                inDegree[sccid[there]]++;
            }
    
    vector<int> result;
    for (int i = 0; i < sccnum; ++i)
        if (inDegree[i] == 0) result.push_back(i);

    vector<int> answer;
    if (result.size() != 1) return answer;
    else {
        for (int i = 1; i <= n; ++i) {
            if (sccid[i] == result[0])
                answer.push_back(i);
        }
        return answer;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    while (m--) {
        int from, to; cin >> from >> to;
        adj[from].push_back(to);
    }    

    vector<int> result = tarjanSCC();

    cout << result.size() << "\n";
    for (int e : result) cout << e << " ";
    cout << "\n";
    
    return 0;
}