#include <bits/stdc++.h>
using namespace std;

int find_f(vector<int> &arr, int x) {
    if (arr[x] == x) return x;
    else return arr[x] = find_f(arr, arr[x]);
}

void union_f(vector<int> &arr, vector<int> &height, int x, int y) {
    x = find_f(arr, x), y = find_f(arr, y);
    if (height[x] > height[y]) swap(x, y);
    arr[x] = y;
    if (height[x] == height[y]) ++height[y];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m1, m2; cin >> n >> m1 >> m2;
    vector<int> g1(n + 1), g2(n + 1);
    vector<int> h1(n + 1, 0), h2(n + 1, 0);
    for (int i = 1; i <= n; ++i)
        g1[i] = g2[i] = i;

    for (int i = 0; i < m1; ++i) {
        int u, v; cin >> u >> v;
        union_f(g1, h1, u, v);
    }

    for (int i = 0; i < m2; ++i) {
        int u, v; cin >> u >> v;
        union_f(g2, h2, u, v);
    }

    vector<pair<int, int>> answer;
    for (int u = 1; u <= n; ++u) 
        for (int v = 1; v <= n; ++v) {
            if ((find_f(g1, u) != find_f(g1, v)) && (find_f(g2, u) != find_f(g2, v))) {
                union_f(g1, h1, u, v);
                union_f(g2, h2, u, v);
                answer.emplace_back(u, v);
            }
        }
    cout << answer.size() << "\n";
    for (auto e : answer) cout << e.first << " " << e.second << "\n";
    return 0;
}