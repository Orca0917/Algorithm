#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 300
#define INF 1e9

using namespace std;

int N, M;
vector<int> adj[MAX];
int capacity[MAX][MAX], flow[MAX][MAX], cost[MAX][MAX];
bool isin_queue[MAX];

int grade_statisfy_matrix[3][4] = {
    {4, 3, 2, 1},
    {8, 7, 6, 5},
    {12, 11, 10, 9}
};

int MCMF(int source, int sink) {
    int max_cost = 0;

    while (true) {
        vector<int> dist(MAX, INF);
        dist[source] = 0;

        vector<int> parent(MAX, -1);
        parent[source] = source;

        queue<int> q;
        q.push(source);

        memset(isin_queue, false, sizeof(isin_queue));
        isin_queue[source] = true;

        while (!q.empty()) {
            int here = q.front();
            q.pop();

            isin_queue[here] = false;
            for (int there : adj[here]) {
                if (capacity[here][there] - flow[here][there] > 0 && dist[there] > dist[here] + cost[here][there]) {
                    dist[there] = dist[here] + cost[here][there];
                    parent[there] = here;

                    if (isin_queue[there]) continue;
                    isin_queue[there] = true;
                    q.push(there);
                }
            }
        }

        if (parent[sink] == -1) break;

        int amount = INF;
        for (int node = sink; node != source; node = parent[node]) {
            amount = min(amount, capacity[parent[node]][node] - flow[parent[node]][node]);
        }

        // cout << "--amount " << amount << "\n";

        for (int node = sink; node != source; node = parent[node]) {
            flow[parent[node]][node] += amount;
            flow[node][parent[node]] -= amount;
            max_cost += amount * cost[parent[node]][node];
        }

        // cout << "--result " << max_cost << "\n";
    }

    return max_cost;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    while (true) {
        cin >> N >> M;

        // terminate condition
        if (N == 0 && M == 0) break;

        // init variables
        memset(capacity, 0, sizeof(capacity));
        memset(flow, 0, sizeof(flow));
        memset(cost, 0, sizeof(cost));
        for (int i = 0; i < MAX; ++i) adj[i].clear();

        // set source & sink node
        int source = 0, sink = 211;

        // link company to sink
        for (int company = 141; company <= 140 + N; ++company) {
            adj[company].push_back(sink);
            adj[sink].push_back(company);
            cin >> capacity[company][sink];
        }

        for (int student = 1; student <= M; ++student) {
            int grade; cin >> grade;

            // link source to student
            adj[source].push_back(student);
            adj[student].push_back(source);
            capacity[source][student] = 1;

            for (int priority = 0; priority <= 3; ++priority) {
                int company_idx; cin >> company_idx;
                ++company_idx;

                // link student to company
                adj[student].push_back(140 + company_idx);
                adj[140 + company_idx].push_back(student);

                cost[student][140 + company_idx] = -grade_statisfy_matrix[grade - 1][priority];
                cost[140 + company_idx][student] = grade_statisfy_matrix[grade - 1][priority];

                capacity[student][140 + company_idx] = 1;
            }
        }
        
         // get answer with negative MCMF (maximize cost)
        cout << -MCMF(source, sink) << "\n";    
    }

    
    return 0;
}