#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int nn, kk;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> nn >> kk;

    int res = 1;
    for (int i = 2; i <= nn; ++i)
        res = (res + kk - 1) % i + 1;
    cout << res << "\n";
    
    return 0;
}