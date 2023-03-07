#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int num_plant; cin >> num_plant;
    int num_jumps; cin >> num_jumps;
    string dirs; cin >> dirs;

    set<tuple<int, int, int>> ascend;    // AD
    set<tuple<int, int, int>> descend;   // BC

    int xx, yy;
    for (int i = 1; i <= num_plant; ++i) {
        int x, y; cin >> x >> y;
        ascend.insert({x - y, x, y});
        descend.insert({x + y, x, y});
        if (i == 1) { xx = x; yy = y; }
    }

    for (char dir : dirs) {
        int diff, x, y;
        if (dir == 'A') {
            auto it = ascend.find({xx - yy, xx, yy});
            if (it == prev(ascend.end())) continue;
            tie(diff, x, y) = *next(it);
            if (diff != xx - yy) continue;
            ascend.erase(it);
            descend.erase({xx + yy, xx, yy});
            xx = x; yy = y;
        }

        else if (dir == 'B') {
            auto it = descend.find({xx + yy, xx, yy});
            if (it == prev(descend.end())) continue;
            tie(diff, x, y) = *next(it);
            if (diff != xx + yy) continue;
            descend.erase(it);
            ascend.erase({xx - yy, xx, yy});
            xx = x; yy = y;
        }

        else if (dir == 'C') {
            auto it = descend.find({xx + yy, xx, yy});
            if (it == descend.begin()) continue;
            tie(diff, x, y) = *prev(it);
            if (diff != xx + yy) continue;
            descend.erase(it);
            ascend.erase({xx - yy, xx, yy});
            xx = x; yy = y;
        }

        else if (dir == 'D') {
            auto it = ascend.find({xx - yy, xx, yy});
            if (it == ascend.begin()) continue;
            tie(diff, x, y) = *prev(it);
            if (diff != xx - yy) continue;
            ascend.erase(it);
            descend.erase({xx + yy, xx, yy});
            xx = x; yy = y;
        }
    }

    cout << xx << " " << yy << "\n";

    return 0;
}