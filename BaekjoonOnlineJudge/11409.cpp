#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

string s;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> s;

    ll answer = 0;
    for (char c : s) {
        int digit = c - '0';
        answer += digit * digit * digit * digit * digit;
    }

    cout << answer << "\n";

    return 0;
}