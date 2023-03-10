#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define S 1
#define E -1

using namespace std;

vector<pii> bldg;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int num_buildings; cin >> num_buildings;
    for (int i = 0; i < num_buildings; ++i) {
        int s, h, e; cin >> s >> h >> e;
        bldg.push_back({s, h});
        bldg.push_back({e, -h});
    }

    sort(bldg.begin(), bldg.end());
    bldg.push_back({2e9, 2e9});

    int xpos = bldg[0].first;
    int now_height = -1;

    multiset<int> ms;
    ms.insert(0);
    int index = 0;

    while (index < 2 * num_buildings) {
        while (xpos == bldg[index].first) {
            int h = bldg[index].second;
            if (h < 0) ms.erase(ms.find(-h));
            else ms.insert(h);
            ++index;
        }

        int new_height = *prev(ms.end());
        if (new_height != now_height) {
            cout << xpos << ' ' << new_height << ' ';
            now_height = new_height;
        }
        xpos = bldg[index].first;
    }
    
    return 0;
}