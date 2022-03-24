#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX_STUDENT 1001
#define INF 1234567890
using namespace std;

int n; // # of students
int p; // # of cables
int k; // # of free cables

vector<pii> adj[MAX_STUDENT];

bool check(int mid) {
    int dist[MAX_STUDENT];
    fill(dist, dist + MAX_STUDENT, INF);

    priority_queue<pii> pq;
    pq.push({0, 1});
    dist[1] = 0;

    while (!pq.empty()) {
        int cost = -pq.top().first;
        int here = pq.top().second;
        pq.pop();

        if (dist[here] < cost) continue;

        for (pii thereInfo : adj[here]) {
            int there = thereInfo.first;
            int new_cost = cost + (thereInfo.second > mid);

            if (new_cost < dist[there]) {
                dist[there] = new_cost;
                pq.push({-new_cost, there});
            }
        }
    }

    return dist[n] <= k;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> p >> k;

    for (int cable = 0; cable < p; ++cable) {
        int computer1, computer2, price;
        cin >> computer1 >> computer2 >> price;

        adj[computer1].push_back({computer2, price});
        adj[computer2].push_back({computer1, price});
    }

    int lo = 0, hi = 1e7, answer = -1;

    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (check(mid)) {
            answer = mid;
            hi = mid - 1;
        } else
            lo = mid + 1;
    }

    cout << answer << "\n";
    return 0;
}