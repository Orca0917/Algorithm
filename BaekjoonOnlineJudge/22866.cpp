#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    stack<pii> left, right;

    int num_bldg; cin >> num_bldg;
    vector<int> bldg(num_bldg + 1);
    for (int i = 1; i <= num_bldg; ++i) cin >> bldg[i];

    vector<pii> result(num_bldg + 1, {1e9, 0});
    for (int i = 1; i <= num_bldg; ++i) {
        while (!left.empty() && left.top().second <= bldg[i]) left.pop();
        if (!left.empty()) {
            int prev_dist = abs(result[i].first - i);
            int curr_dist = abs(left.top().first - i);
            if (prev_dist > curr_dist) result[i].first = left.top().first;
        }
        result[i].second += (int)left.size();
        left.push({i, bldg[i]});
    }

    for (int i = num_bldg; i >= 1; --i) {
        while (!right.empty() && right.top().second <= bldg[i]) right.pop();
        if (!right.empty()) {
            int prev_dist = abs(result[i].first - i);
            int curr_dist = abs(right.top().first - i);
            if (prev_dist > curr_dist) result[i].first = right.top().first;
        }
        result[i].second += (int)right.size();
        right.push({i, bldg[i]});
    }

    for (int i = 1; i <= num_bldg; ++i) {
        cout << result[i].second;
        if (result[i].second) cout << " " << result[i].first;
        cout << "\n";
    }
    
    return 0;
}