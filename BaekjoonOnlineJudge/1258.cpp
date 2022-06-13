#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 202
using namespace std;

int n; // # of students, # of problems <= 100
vector<int> adj[MAX];
int capacity[MAX][MAX], flow[MAX][MAX], cost[MAX][MAX];
int dist[MAX];

bool isin_queue[MAX];

int MCMF(int source, int sink)
{
    int max_cost = 0;

    while (true)
    {

        // initialize
        memset(dist, -1, sizeof(dist));
        memset(isin_queue, false, sizeof(isin_queue));

        vector<int> parent(MAX, -1);
        // parent[source] = source;

        queue<int> q;
        q.push(source);

        isin_queue[source] = true;
        dist[source] = 0;

        while (!q.empty())
        {
            int here = q.front();
            q.pop();
            isin_queue[here] = false;

            for (int there : adj[here])
            {
                bool distance_result = (dist[there] == -1 || dist[there] > dist[here] + cost[here][there]);
                if (capacity[here][there] - flow[here][there] > 0 && distance_result)
                {
                    parent[there] = here;
                    dist[there] = dist[here] + cost[here][there];

                    if (isin_queue[there])
                        continue;

                    isin_queue[there] = true;
                    q.push(there);
                }
            }
        }

        if (parent[sink] == -1)
            break;

        int amount = 1e9;

        for (int node = sink; node != source; node = parent[node])
        {
            amount = min(amount, capacity[parent[node]][node] - flow[parent[node]][node]);
        }

        for (int node = sink; node != source; node = parent[node])
        {
            flow[parent[node]][node] += amount;
            flow[node][parent[node]] -= amount;
            max_cost += cost[parent[node]][node];
        }
    }

    return max_cost;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // initialize
    memset(capacity, 0, sizeof(capacity));
    memset(flow, 0, sizeof(flow));
    memset(cost, 0, sizeof(cost));

    cin >> n;

    int source = 0, sink = 201;

    for (int student = 1; student <= n; ++student)
    {

        adj[source].push_back(student);
        adj[student].push_back(source);
        capacity[source][student] = 1;

        for (int problem = 101; problem <= 100 + n; ++problem)
        {
            cin >> cost[student][problem];
            cost[problem][student] = -cost[student][problem];

            adj[student].push_back(problem);
            adj[problem].push_back(student);
            capacity[student][problem] = 1;
        }
    }

    for (int problem = 101; problem <= 100 + n; ++problem)
    {
        adj[problem].push_back(sink);
        adj[sink].push_back(problem);
        capacity[problem][sink] = 1;
    }

    // minimum cost maximum flow (MCMF)
    cout << MCMF(source, sink) << "\n";

    return 0;
}