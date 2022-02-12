#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, m; cin >> n >> m;
    vector<int> x, y;
    for (int i = 0; i < n; ++i) {
        int x_, y_; cin >> x_ >> y_;
        x.push_back(x_);
        y.push_back(y_);
    }
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());

    ll sum = 0;
    int curx = 0, cury = 0;

    for (int iter = 0; iter < m; ++iter) {
        char c; cin >> c;
        if (c == 'S') cury += 1;
        else if (c == 'J') cury -= 1;
        else if (c == 'I') curx += 1;
        else curx -= 1;
        
        if (iter == 0) {
            for (int iter_ = 0; iter_ < n; ++iter_) {
                sum += abs(x[iter_] - curx);
                sum += abs(y[iter_] - cury);
            }
        } else { // 1, 0 -> 1, 1
            if (c == 'S') {
                int left = lower_bound(y.begin(), y.end(), cury) - y.begin();
                int right = n - left;
                sum += left - right;
            } else if (c == 'J') {
                int left = lower_bound(y.begin(), y.end(), cury + 1) - y.begin();
                int right = n - left;
                sum += right - left;
            } else if (c == 'I') {
                int down = lower_bound(x.begin(), x.end(), curx) - x.begin();
                int up = n - down;
                sum += down - up;
            } else {
                int down = lower_bound(x.begin(), x.end(), curx + 1) - x.begin();
                int up = n - down;
                sum += up - down;
            }
        }

        cout << sum << "\n";
    }
    return 0;
}