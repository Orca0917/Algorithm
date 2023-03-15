#include <bits/stdc++.h>
#define pii pair<int, int>
#define tiii tuple<int, int, int>
#define ll long long

using namespace std;

int num_hole;
int target;

vector<tiii> holes;
vector<bool> vis(50000, false);

int bfs() {
    
    queue<tiii> q;
    q.push({0, 0, 0}); 
    
    int x, y, id;
    while (!q.empty()) {
        tie(x, y, id) = q.front(); q.pop();
        if (y == target) return id;

        auto lo = lower_bound(holes.begin(), holes.end(), tiii(x - 2, 0, 0), [](const tiii &hole1, const tiii &hole2) {
            return get<0>(hole1) < get<0>(hole2);
        });

        auto hi = upper_bound(holes.begin(), holes.end(), tiii(x + 2, 0, 0), [](const tiii &hole1, const tiii &hole2) {
            return get<0>(hole1) < get<0>(hole2);
        });

        for (auto it = lo; it < hi; ++it) {
            if (abs(get<1>(*it) - y) <= 2 && !vis[it - holes.begin()]) {
                vis[it - holes.begin()] = true;
                q.push({get<0>(*it), get<1>(*it), id + 1});
            }
        }
    }

    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> num_hole >> target;
    
    for (int i = 0; i < num_hole; ++i) {
        int x, y; cin >> x >> y;
        holes.push_back({x, y, i});
    }

    sort(holes.begin(), holes.end());

    cout << bfs() << "\n";
    
    return 0;
}