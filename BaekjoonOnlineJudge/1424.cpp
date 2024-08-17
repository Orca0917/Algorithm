#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; // 노래의 개수
    int l; // 노래의 길이 (초)
    int c; // CD의 용량 (초)

    cin >> n >> l >> c;

    int k = 1;
    while((k + 1) * l + k <= c && k < n) ++k;

    if (k % 13 == 0) k--;
    if (n % k == 0) cout << n / k;
    else if((n % k) % 13 == 0 && k - (n % k) == 1) cout << n / k + 2;
    else cout << n / k + 1;

    return 0;
}