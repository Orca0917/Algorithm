#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 250

using namespace std;

int n, m, f;
vector<int> adj[MAX];
int capacity[MAX][MAX], flow[MAX][MAX];

pii network_flow(int source, int sink) {
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
    
    cin >> n;

    while (n--) {

        memset(capacity, 0, sizeof(capacity));
        memset(flow, 0, sizeof(flow));
        for (int i = 0; i < MAX; ++i) adj[i].clear();


        cin >> m >> f;
        // male : 1 <= m <= 100
        // female : 101 <= f <= 150

        int source = 0, sink = 200;

        // linking source to male
        for (int male = 1; male <= m; ++male) {
            adj[source].push_back(male);
            adj[male].push_back(source);
            capacity[source][male] = 1;    
        }

        // linking male to female
        for (int female = 101; female <= 100 + f; ++female) {
            int k; cin >> k;
            while (k--) {
                int male; cin >> male;
                male += 1;

                adj[female].push_back(male);
                adj[male].push_back(female);
            }
        }

        // linking feamle to sink
        for (int female = 101; female <= 100 + f; ++female) {
            adj[female].push_back(sink);
            adj[sink].push_back(female);
            capacity[female][sink] = 1e9;
        }

        int lo = 1, hi = 200, answer = 1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            for (int female = 101; female <= 100 + f; ++female) {
                for (int there : adj[female]) {
                    if (there == sink) continue;
                    capacity[there][female] = mid;
                }
            }

            int result = network_flow(source, sink);
            if (result == m) {
                answer = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }

        for (int female = 101; female <= 100 + f; ++female) {
            for (int there : adj[female]) {
                if (there == sink) continue;
                capacity[there][female] = answer;
            }
        }

        int result = network_flow(source, sink);
        if (result != m) cout << "impossible\n";
        else cout <<  << "\n";
    }    
    
    return 0;
}