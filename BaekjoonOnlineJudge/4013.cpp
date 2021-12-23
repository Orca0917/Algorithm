#include <bits/stdc++.h>
#define ll long long
using namespace std;

// 교차로의 수와 도로의 수
int n, m;
// 교차로 연결 정보를 가진 인접 리스트 생성
vector<int> adj[500001];
vector<int> sccGraph[500001];
vector<int> balance(500001, 0);
vector<ll> memo(500001, -1);

vector<bool> isRestaurant(500001, false);

vector<int> sccID(500001, -1);
vector<int> discovered(500001, -1);
vector<ll> accSum(500001, 0);
int sccNumber = 0, discoverNumber = 0;

stack<int> st;

// 출발장소와 레스토랑의 개수
int s, p;

int scc(int here) {
    int ret = discovered[here] = discoverNumber++;
    st.push(here);

    for (int there : adj[here]) {
        if (discovered[there] == -1)
            ret = min(ret, scc(there));
        else if (sccID[there] == -1)
            ret = min(ret, discovered[there]);
    }

    if (ret == discovered[here]) {
        while (true) {
            int now = st.top(); st.pop();
            sccID[now] = sccNumber;
            if (now == here) break;
        }
        ++sccNumber;
    }
    return ret;
}

void tarjanSCC() {
    for (int i = 1; i <= n; ++i)
        if (discovered[i] == -1)
            scc(i);

    // make scc graph
    for (int here = 1; here <= n; ++here)
        for (auto there : adj[here])
            if (sccID[here] != sccID[there])
                sccGraph[sccID[here]].push_back(sccID[there]);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int from, to; cin >> from >> to;
        adj[from].push_back(to);
    }

    for (int i = 1; i <= n; ++i)
        cin >> balance[i];
    
    cin >> s >> p;
    for (int i = 0; i < p; ++i) {
        int restaurant; cin >> restaurant;
        isRestaurant[restaurant] = true;
    }

    tarjanSCC();

    for (int i = 1; i <= n; ++i) {
        accSum[sccID[i]] += balance[i];
    }

    s = sccID[s];
    memo[s] = accSum[s];

    for (int here = s; here > 0; --here) {
        if (memo[here] == -1) continue;
        for (auto there: sccGraph[here]) {
            memo[there] = max(memo[there], memo[here] + accSum[there]);
        }
    }

    ll answer = 0;
    for (int i = 1; i <= n; ++i)
        if (isRestaurant[i])
            answer = max(answer, memo[sccID[i]]);
    
    cout << answer << "\n";

    return 0;
}