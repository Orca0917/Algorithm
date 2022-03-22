#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

bool has_number[2'222'222];
bool flag[2'222'222];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    memset(has_number, false, sizeof(has_number));
    memset(flag, false, sizeof(flag));
    int n; cin >> n;

    vector<int> a(n);
    for (int &e: a) {
        cin >> e;
        has_number[e] = true;
    }

    if (!has_number[0]) cout << 0 << "\n";
    else if (!has_number[1]) cout << 1 << "\n";
    else {
        for (int i = 1; i < 2'222'222; ++i) {
            for (int j = 1; j < 2'222'222 && has_number[i]; ++j) {
                if (i * j > 2'222'222) break;
                if (!has_number[j]) continue;
                flag[i * j] = true;
            }
        }

        for (int i = 2; ; ++i) {
            if (flag[i] == false) {
                cout << i << "\n";
                break;
            }
        }
    }
    return 0;
}