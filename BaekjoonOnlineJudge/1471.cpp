#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<int> adj[200001], sccadj[200001];
vector<int> sccid(200001, -1), discovered(200001, -1);
vector<int> memo(200001, -1);
vector<int> sccSize(200001, 0);
stack<int> st;
int sccnum = 0, disnum = 0;
int n;

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
            ++sccSize[sccnum];
            if (x == here) break;
        }
        ++sccnum;
    }

    return ret;
}

int dfs(int here) {
    if (sccadj[here].size() == 0) return sccSize[here];

    int &ret = memo[here];
    if (ret != -1) return ret;

    ret = 1;
    for (int there : sccadj[here])
        ret = max(ret, dfs(there) + sccSize[here]);
    
    return ret;
}

int tarjanSCC() {
    for (int i = 1; i <= n; ++i) {
        if (discovered[i] == -1)
            scc(i);
    }

    for (int i = 1; i <= n; ++i) {
        for (int there : adj[i]) {
            if (sccid[there] != sccid[i]) {
                sccadj[sccid[i]].push_back(sccid[there]);
            }
        }
    }

    int answer = 0;
    for (int i = 0; i < sccnum; ++i) {
        if (memo[i] == -1) {
            answer = max(dfs(i), answer);
        }
    }

    return answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    auto getSum = [](int x) -> int {
        int ret = 0;
        while (x > 0) {
            ret += x % 10;
            x /= 10;
        }
        return ret;
    };

    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int dest = i + getSum(i);
        if (getSum(i) == n) continue;

        if (dest > n) dest %= n;
        adj[i].push_back(dest);
    }

    int result = tarjanSCC();
    cout << result << "\n";
    
    return 0;
}