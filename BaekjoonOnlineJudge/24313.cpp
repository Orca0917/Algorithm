#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int a1, a0, c, n0;
    cin >> a1 >> a0 >> c >> n0;

    // f(n) <= c x g(n) 을 만족하는 c와 n0 존재. where, n >= n0
    // f(n) = a1n + a0

    cout << (a1 * n0 + a0 <= c * n0 && c >= a1? 1 : 0);
    
    return 0;
}