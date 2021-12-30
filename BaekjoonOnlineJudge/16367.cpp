#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;
const int max_vertex = 5000 * 2 + 2;
vector<int> discovered(max_vertex, -1), sccid(max_vertex, -1);
vector<int> adj[max_vertex];
stack<int> st;

int discoverNum = 0, sccNum = 0;
int n, m;

int scc(int here) {
    int ret = discovered[here] = discoverNum++;
    st.push(here);

    for (int there : adj[here]) {
        if (discovered[there] == -1) ret = min(ret, scc(there));
        else if (sccid[there] == -1) ret = min(ret, discovered[there]);
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

vector<int> tarjanSCC() {
    for (int node = 2; node <= 2 * n + 1; ++node)
        if (discovered[node] == -1)
            scc(node);

    for (int i = 2; i <= n * 2; i += 2)
        if (sccid[i] == sccid[i + 1])
            return vector<int> ();

    vector<int> result(n + 1, -1);
    vector<pii> order;
    for (int i = 1; i <= 2 * n + 1; ++i)
        order.push_back({-sccid[i], i});
    sort(order.begin(), order.end());

    for (int i = 0; i < (int)order.size(); ++i) {
        int node = order[i].second / 2;
        int isTrue = order[i].second % 2 == 0;

        if (result[node] != -1) continue;
        result[node] = !isTrue;
    }
    
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;
    
    vector<int> selection(3);
    char color;

    auto getNode = [](int x) -> pii {
        int notx;
        if (x < 0) {
            x = -x * 2 + 1;
            notx = x - 1;
        } else {
            x = x * 2;
            notx = x + 1;
        }
        return {x, notx};
    };

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < 3; ++j) {
            cin >> selection[j] >> color;
            if (color == 'R') selection[j] *= -1;
        }

        pii s1 = getNode(selection[0]);
        pii s2 = getNode(selection[1]);
        pii s3 = getNode(selection[2]);

        adj[s1.second].emplace_back(s2.first);
        adj[s1.second].emplace_back(s3.first);
        adj[s2.second].emplace_back(s1.first);
        adj[s2.second].emplace_back(s3.first);
        adj[s3.second].emplace_back(s1.first);
        adj[s3.second].emplace_back(s2.first);
    }

    vector<int> answer = tarjanSCC();
    if (answer.size() == 0) cout << "-1\n";
    else {
        for (int i = 1; i <= n; ++i)
            if (answer[i] == 0) cout << 'R';
            else if (answer[i] == 1) cout << 'B';
        cout << "\n";
    }

    return 0;
}