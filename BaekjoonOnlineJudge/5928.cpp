#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    ll time_start = 60 * 24 * 11 + 60 * 11 + 11;
    int a, b, c; cin >> a >> b >> c;
    ll time_end = 60 * 24 * a + 60 * b + c;

    ll answer = 0;
    if (time_start > time_end) answer = -1;
    else answer = time_end - time_start;

    cout << answer << "\n";

    return 0;
}