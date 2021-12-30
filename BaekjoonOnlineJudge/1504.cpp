// Online C++ compiler to run C++ program online

#include <bits/stdc++.h>

#define ll long long

#define pii pair<long long, int>

using namespace std;

int n, m;

int p1, p2;

const ll inf = 9999999999;

vector<pair<int, int>> adj[801];

ll dijkstra(int start, int end) {

    vector<ll> dist(n + 1, inf);

    priority_queue<pii> pq;

    pq.emplace(0, start);

    

    dist[start] = 0;

    

    while(!pq.empty()) {

        int here = pq.top().second;

        ll cost = -pq.top().first;

        pq.pop();

        

        if (dist[here] < cost) continue;

        

        for (pair<int, int> there : adj[here]) {

            int next = there.first;

            ll nextcost = 1LL * there.second + cost;

            

            if (dist[next] > nextcost) {

                dist[next] = nextcost;

                pq.emplace(-nextcost, next);

            }

        }

    }

    

    return dist[end];

}

int main() {

    ios_base::sync_with_stdio(false);

    cin.tie(nullptr);

    cout.tie(nullptr);

    

    cin >> n >> m;

    

    for (int i = 0; i < m; ++i) {

        int from, to, cost;

        cin >> from >> to >> cost;

        

        adj[from].emplace_back(to, cost);

        adj[to].emplace_back(from, cost);

    }

    

    cin >> p1 >> p2;

    

    ll res1 = dijkstra(1, p1);

    ll mid = dijkstra(p1, p2);

    ll res2 = dijkstra(p2, n);

    

    ll res3 = dijkstra(1, p2);

    ll res4 = dijkstra(p1, n);

    

    if ((res1 + res2 > inf && res3 + res4 > inf) || mid == inf )

        cout << "-1\n";

    else

        cout << min(res1 + res2, res3 + res4) + mid << "\n";

        

    return 0;

}