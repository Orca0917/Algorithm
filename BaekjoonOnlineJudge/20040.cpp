#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

vector<int> parent;

int find_f(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find_f(parent[x]);
}


bool union_f(int x, int y) {
    x = find_f(x);
    y = find_f(y);

    if (x == y) return true;
    if (x > y) swap(x, y);
    parent[x] = y;

    return false;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, m; cin >> n >> m;

    // 부모 정점 집합 초기화
    parent.resize(n);
    for (int i = 0; i < n; ++i) parent[i] = i;

    int round = 1, answer = 0;
    while (m--) {
        int u, v; cin >> u >> v;
        bool ret = union_f(u, v);
        if (ret && answer == 0) answer = round;
        ++round;
    }

    cout << answer << "\n";
    
    return 0;
}