#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 250

using namespace std;

int testcase, m, f;
vector<int> adj[MAX];
int capacity[MAX][MAX], flow[MAX][MAX];

int network_flow(int source, int sink) {
    memset(flow, 0, sizeof(flow));

    int max_flow = 0;
    while (true) {
        vector<int> parent(MAX, -1);
        parent[source] = source;

        queue<int> q;
        q.push(source);

        while (!q.empty() && parent[sink] == -1) {
            int here = q.front(); q.pop();
            for (int there : adj[here]) {
                if (capacity[here][there] - flow[here][there] > 0 && parent[there] == -1) {
                    parent[there] = here;
                    q.push(there);
                }
            }
        }

        if (parent[sink] == -1) break;

        int amount = 1;
        for (int node = sink; node != source; node = parent[node]) {
            flow[parent[node]][node] += amount;
            flow[node][parent[node]] -= amount;
        }
        max_flow += amount;
    }

    return max_flow;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> testcase;
    while (testcase--) {

        // 변수 초기화
        memset(capacity, 0, sizeof(capacity));
        memset(flow, 0, sizeof(flow));
        for (int i = 0; i < MAX; ++i) adj[i].clear();

        // 남자의 수, 여자의 수 입력
        cin >> m >> f;

        int source = 0, sink = 200;

        // SOURCE -> 남자
        for (int male = 1; male <= m; ++male) {
            adj[source].push_back(male);
            adj[male].push_back(source);
            capacity[source][male] = 1;    
        }

        // 남자 -> 여자
        for (int female = 101; female <= 100 + f; ++female) {
            int want_date; cin >> want_date;
            while (want_date--) {
                int male; cin >> male;
                male += 1;

                adj[female].push_back(male);
                adj[male].push_back(female);
                capacity[male][female] = 1;
            }
        }

        // 여자 -> SINK
        for (int female = 101; female <= 100 + f; ++female) {
            adj[female].push_back(sink);
            adj[sink].push_back(female);
            capacity[female][sink] = 1e9;
        }

        int result = network_flow(source, sink);
        if (result != m) {
            cout << "impossible\n";
            continue;
        }


        // 한 명의 여자가 최대 몇 명의 남자와 데이트를 할 것인지 결정
        int lo = 1, hi = 200, answer = 1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            for (int female = 101; female <= 100 + f; ++female) {
                capacity[female][sink] = mid;
            }

            int result = network_flow(source, sink);
            if (result == m) {
                answer = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        
        cout << answer << "\n";
    }    
    
    return 0;
}