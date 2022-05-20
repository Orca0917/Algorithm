#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int fact(int n) {
    if (n == 1) return 1;
    return n * fact(n - 1);
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n; cin >> n;
    cout << fact(n);    
    return 0;
}