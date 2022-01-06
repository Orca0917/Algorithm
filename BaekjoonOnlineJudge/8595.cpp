#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    ll answer = 0;

    int number = 0;
    for (int i = 0; i < n; ++i) {
        char c; cin >> c;
        if ('0' <= c && c <= '9') {
            number = number * 10 + c - '0';
        } else {
            answer += number;
            number = 0;
        }
    }

    if (number != 0) answer += number;

    cout << answer << "\n";
    return 0;
}