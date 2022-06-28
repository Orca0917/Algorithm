#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

void print(int a, int b, int c, int d) {
    cout << a << " " << b << " " << c << " " << d << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, m; cin >> n >> m;
    cout << n / 2 + m / 2 << "\n";

    for (int i = 2; i <= m; i += 2) print(1, i, n, i);
    for (int j = 2; j <= n; j += 2) print(j, 1, j, m);
    return 0;
}