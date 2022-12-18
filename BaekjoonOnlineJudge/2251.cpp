#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

bool vis[201][201][201];
vector<int> capacity(3);
set<int> s;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    for (int i = 0; i < 3; ++i) cin >> capacity[i];

    memset(vis, false, sizeof(vis));
    queue<tuple<int, int, int>> q;
    q.push({0, 0, capacity[2]});

    vector<int> here(3);
    while (!q.empty()) {
        tie(here[0], here[1], here[2]) = q.front(); q.pop();

        if (here[0] == 0) s.insert(here[2]);

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (i == j) continue;
                vector<int> there(here.begin(), here.end());
                int amount = min(here[i], capacity[j] - here[j]);
                there[i] = here[i] - amount;
                there[j] = here[j] + amount;
                if (vis[there[0]][there[1]][there[2]]) continue;
                q.push({there[0], there[1], there[2]});
                vis[there[0]][there[1]][there[2]] = true;
            }
        }
    }   

    for (int e : s) cout << e << " ";
    
    return 0;
}