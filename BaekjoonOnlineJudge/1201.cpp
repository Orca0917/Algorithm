/*
 * author: 0917jong
 * date: 2021-12-16
 */

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k; cin >> n >> m >> k;

    if (m + k - 1 > n || n > m * k) {
        cout << -1 << "\n";
        return 0;
    }

    vector<int> a(n);
    for (int i = 0; i < n; ++i) a[i] = i + 1;

    /*
     * Solution 
     * - 배열을 M개의 분리된 집합으로 나눈다.
     * - 그 중, 가장 긴 길이는 K이어야 한다.
     * - 각 분리된 집합의 배열을 뒤집는다. (reverse)
    */

    for (int i = 1, idx = 0; i <= m; ++i) {
        int sub = min(idx + k, n - m + i);
        reverse(a.begin() + idx, a.begin() + sub);
        idx = sub;
    }
    for (int i = 0; i < n; ++i) cout << a[i] << " ";
    cout << "\n";

    return 0;
}