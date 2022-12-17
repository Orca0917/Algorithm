#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int n, k; 
vector<int> adj[10];
set<vector<int>> s;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> n >> k;

    vector<int> cubes(n);
    for (int &cube_val : cubes) cin >> cube_val;

    for (int i = 0; i < k; ++i) {
        int adj_num; cin >> adj_num;
        while (adj_num--) {
            int cube; cin >> cube;
            adj[i].push_back(cube);
        }
    }

    queue<pair<vector<int>, int>> q;
    q.push({cubes, 0});
    s.insert(cubes);

    int answer = -1;
    while (!q.empty()) {
        vector<int> now(q.front().first.begin(), q.front().first.end());
        int cnt = q.front().second;
        q.pop();

        int adj_num = now[0];
        bool all_same = true;
        for (int e : now) if (e != adj_num) all_same = false;
        if (all_same) {
            answer = cnt;
            break;
        }

        for (int i = 0; i < k; ++i) {
            vector<int> there = now;
            for (int cube : adj[i]) {
                there[cube - 1] += (i + 1);
                there[cube - 1] %= 5;
            }
            if (s.find(there) != s.end()) continue;
            q.push({there, cnt + 1});
            s.insert(there);
        }
    }   

    cout << answer << "\n";

    return 0;
}