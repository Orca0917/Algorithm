#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define INF 1e9
#define MAX 102
using namespace std;

int n; // # of cars <= 50
int t; // threshold of speed
int f; // maximum cost of fee

vector<int> adj[MAX];

int capacity[MAX][MAX], flow[MAX][MAX], cost[MAX][MAX];
int start_time[MAX], end_time[MAX];
bool isin_queue[MAX];


int MCMF(int source, int sink) {

    memset(flow, 0, sizeof(flow));

    int max_cost = 0;
    int cnt_flow = 0;

    while (true) {
        
        memset(isin_queue, false, sizeof(isin_queue));

        vector<int> parent(MAX, -1);
        vector<int> dist(MAX, INF);
        queue<int> q;

        parent[source] = source;
        q.push(source);

        dist[source] = 0;
        isin_queue[source] = true;

        while (!q.empty()) {
            int here = q.front(); q.pop();
            isin_queue[here] = false;

            for (int there : adj[here]) {
                bool dist_check = (dist[there] > dist[here] + cost[here][there]);
                if (dist_check && capacity[here][there] - flow[here][there] > 0) {
                    dist[there] = dist[here] + cost[here][there];
                    parent[there] = here;

                    if (isin_queue[there]) continue;
                    isin_queue[there] = true;
                    q.push(there);
                }
            }
        }

        if (parent[sink] == -1) break;

        int amount = 1e9;
        for (int node = sink; node != source; node = parent[node])
            amount = min(amount, capacity[parent[node]][node] - flow[parent[node]][node]);

        for (int node = sink; node != source; node = parent[node]) {
            flow[parent[node]][node] += amount;
            flow[node][parent[node]] -= amount;
            max_cost += amount * cost[parent[node]][node];
        }

        ++cnt_flow;
    }

    // has exact n increasing path
    if (cnt_flow == n) return max_cost;
    else return -1;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int source = 0, sink = 101;

    memset(capacity, 0, sizeof(capacity));
    memset(cost, 0, sizeof(cost));

    cin >> n;
    
    // source -> start_cars (time)
    for (int car_left = 1; car_left <= n; ++car_left) {
        cin >> start_time[car_left];

        adj[source].push_back(car_left);
        adj[car_left].push_back(source);
        capacity[source][car_left] = 1;
    }

    // end_cars -> sink (time)
    for (int car_right = 51; car_right <= 50 + n; ++car_right) {
        cin >> end_time[car_right];

        adj[car_right].push_back(sink);
        adj[sink].push_back(car_right);
        capacity[car_right][sink] = 1;
    }

    cin >> t >> f;

    // start_cars -> end_cars (time)
    for (int left_car = 1; left_car <= n; ++left_car) {
        for (int right_car = 51; right_car <= 50 + n; ++right_car) {

            if (end_time[right_car] - start_time[left_car] <= 0) continue;

            adj[left_car].push_back(right_car);
            adj[right_car].push_back(left_car);
            capacity[left_car][right_car] = 1;

            int elapsed_time = end_time[right_car] - start_time[left_car];
            int c = min(f, (elapsed_time - t) * (elapsed_time - t));
            if (elapsed_time >= t) c = 0;

            cost[left_car][right_car] = c;
            cost[right_car][left_car] = -c;
        }
    }

    // calculate minimum fee
    int minimum_fee = MCMF(source, sink);
    if (minimum_fee < 0) {
        cout << "-1\n";
        return 0;
    }

    // calculate maximum fee = calculate minimum fee with negative costs * -1
    for (int left_car = 1; left_car <= n; ++left_car) {
        for (int right_car = 51; right_car <= 50 + n; ++right_car) {
            cost[left_car][right_car] *= -1;
            cost[right_car][left_car] *= -1;
        }
    }

    int maximum_fee = -MCMF(source, sink);
    cout << minimum_fee << " " << maximum_fee << "\n";

    return 0;
}