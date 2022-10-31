#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, x;
    while (cin >> n >> x) {
        cout << x / (n + 1) << "\n";
    }
    
    return 0;
}