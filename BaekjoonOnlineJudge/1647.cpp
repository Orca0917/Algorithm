#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MAX 100'001

using namespace std;

struct EDGE {
    int u;
    int v;
    int cost;
};

int N;  // 집의 개수
int M;  // 길의 개수

vector<EDGE> edges;
int parent[MAX];

int _find(int x) {
    if (parent[x] == x) return x;
    else return parent[x] = _find(parent[x]);
}

void _union(int x, int y) {
    x = _find(x);
    y = _find(y);

    if (x == y) return;

    parent[x] = y;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;

    for (int i = 1; i <= N; ++i) parent[i] = i;

    for (int i = 0; i < M; ++i) {
        int u, v, c; cin >> u >> v >> c;
        edges.push_back({u, v, c});
    }

    sort(edges.begin(), edges.end(), [](const EDGE &a, const EDGE &b) -> bool {
        return a.cost < b.cost;
    });

    int selected = 0;
    ll answer = 0;
    for (int i = 0; i < M && selected < N - 2; ++i) {
        EDGE e = edges[i];
        if (_find(e.u) == _find(e.v)) continue;

        _union(e.u, e.v);
        answer += e.cost;
        ++selected;
    }

    cout << answer << "\n";

    return 0;
}