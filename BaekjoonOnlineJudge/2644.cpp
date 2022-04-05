#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

vector<int> adj[101];

int bfs(int start, int end) {
    queue<pii> q;
    vector<bool> vis(101, false);

	q.push({start, 0});
    vis[start] = true;

    int cur, dist;
	while (!q.empty()) {
        tie(cur, dist) = q.front(); q.pop();
        if (cur == end) return dist;

        for (int there : adj[cur]) {
            if (vis[there]) continue;
            q.push({there, dist + 1});
            vis[there] = true;
        }
	}

    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int num_people; cin >> num_people;
	int start, end; cin >> start >> end;

	int num_rel; cin >> num_rel;
	for (int i = 0; i < num_rel; i++) {
		int h1, h2; cin >> h1 >> h2;
		adj[h1].push_back(h2);
		adj[h2].push_back(h1);
	}

    cout << bfs(start, end) << "\n";

    return 0;
}