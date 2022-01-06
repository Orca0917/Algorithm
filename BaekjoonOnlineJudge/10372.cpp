#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;

    int h = 0, m = 0;
    int cnt[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

    while (h <= 24) {
        string sh, sm;
        if (h < 10) sh = "0" + to_string(h);
        else sh = to_string(h);

        if (m < 10) sm = "0" + to_string(m);
        else sm = to_string(m);

        int temp = cnt[sh[0] - '0'] + cnt[sh[1] - '0'] + cnt[sm[0] - '0'] + cnt[sm[1] - '0'];
        if (temp == n) {
            cout << sh << ":" << sm << "\n";
            return 0;
        }

        ++m;
        if (m == 60) {
            ++h;
            m = 0;
        }
    }

    cout << "Impossible\n";

    return 0;
}