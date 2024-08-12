#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

struct Nadori {
    ll sum;
    ll mul = 0;
};

int parent[200001];
Nadori nadori[200001];

int n;  // 나도리의 수
int q;  // 쿼리의 수

int _find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = _find(parent[x]);
}

ll _union(int x, int y) {
    x = _find(x);
    y = _find(y);

    if (x == y) return nadori[y].mul;

    parent[x] = y;

    nadori[y].mul = nadori[y].mul + nadori[x].mul + nadori[y].sum * nadori[x].sum;  // 나도리 합
    nadori[y].sum = nadori[y].sum + nadori[x].sum;

    return nadori[y].mul;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    for (int i = 0; i <= 200000; ++i) parent[i] = i;
    
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> nadori[i].sum;

    while (q--) {
        int a, b; cin >> a >> b;
        cout << _union(a, b) << "\n";
    }
    
    return 0;
}