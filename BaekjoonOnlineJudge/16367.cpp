#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, m;
vector<int> adj[10005];
vector<int> discovered(10005, -1), sccid(10005, -1);
stack<int> st;
int disnum = 0, sccnum = 0;

int scc(int here) {
    int ret = discovered[here] = disnum++;
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
            if (here == x) break;
        }
        ++sccnum;
    }

    return ret;
}

bool tarjanSCC() {
    for (int i = 2; i <= 2 * n + 1; ++i) {
        if (discovered[i] == -1) 
            scc(i);
    }

    for (int i = 2; i <= 2 * n; i += 2) {
        if (sccid[i] == sccid[i + 1]) {
            return false;
        }
    }

    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> m;

    vector<int> selected(3);
    vector<char> color(3);

    for (int i = 0; i < m; ++i) {

        for (int j = 0; j < 3; ++j) {
            cin >> selected[j] >> color[j];
            if (color[j] == 'R') selected[j] = -selected[j];
        }

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

        pii s1 = getNode(selected[0]);
        pii s2 = getNode(selected[1]);
        pii s3 = getNode(selected[2]);

        adj[s1.second].push_back(s2.first);
        adj[s1.second].push_back(s3.first);

        adj[s2.second].push_back(s1.first);
        adj[s2.second].push_back(s3.first);

        adj[s3.second].push_back(s1.first);
        adj[s3.second].push_back(s2.first);

    }

    bool result = tarjanSCC();

    if (result) {
        vector<int> value(2 * n + 2, -1);
        vector<pii> order;
        for (int i = 1; i <= 2 * n + 1; ++i)
            order.push_back({-sccid[i], i});
        sort(order.begin(), order.end());

        for (int i = 0; i <= order.size(); ++i) {
            int vertex = order[i].second;
            int var = vertex / 2;
            bool isTrue = vertex % 2 == 0;
            if (value[var] != -1) continue;
            value[var] = !isTrue;
        }

        for (int i = 1; i <= n; ++i) {
            if (value[i] == 0) cout << 'R';
            else cout << 'B';
        }
        cout << "\n";
    } else {
        cout << "-1\n";
    }

    return 0;
}