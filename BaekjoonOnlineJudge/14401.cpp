#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct EDGE {
    int city1;
    int city2;
    ll cost;
};

struct POSITION {
    ll x;
    ll y;
    int city;
};

int n, m, edge_cnt = 0;
ll answer = 0;

vector<POSITION> coord;
vector<EDGE> road;
vector<int> parent;

// union-find : find function
int find_f(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find_f(parent[x]);
}

// union-find : union function
void union_f(int x, int y) {
    x = find_f(x);
    y = find_f(y);
    if (x == y) return;
    parent[x] = y;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // n : 도시의 수
    // m : 이미 건설된 도로의 수    
    cin >> n >> m;

    // 각 도시의 좌표 정보 입력
    parent.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        ll x, y; cin >> x >> y;
        coord.push_back({x, y, i});
        parent[i] = i;
    }

    // 좌표 정렬
    sort(coord.begin(), coord.end(), [](const POSITION &a, const POSITION &b) -> bool {
        if (a.x == b.x) return a.y < b.y;
        return a.x < b.x;
    });

    // 도시 사이에 건설할 수 있는 모든 도로 정보 계산
    // 사이에 다른 도시가 존재하는 경우 제외.
    for (int i = 0; i < n; ++i) {
        set<double> s;
        for (int j = i + 1; j < n; ++j) {
            POSITION city1 = coord[i];
            POSITION city2 = coord[j];

            double alpha = (city2.y - city1.y) / (double)(city2.x - city1.x);
            // cout << alpha << "\n";

            if (s.find(alpha) != s.end()) continue; // 이미 다른 도시가 포함되어 있음
            s.insert(alpha);

            ll dist = (city1.x - city2.x) * (city1.x - city2.x) + (city1.y - city2.y) * (city1.y - city2.y);
            road.push_back({city1.city, city2.city, dist});
        }
    }

    // cost가 비싼 순으로 정렬
    sort(road.begin(), road.end(), [](const EDGE &a, const EDGE &b) -> bool {
        return a.cost > b.cost;
    });

    // 이미 건설되어 있는 도로의 정보 입력
    // 간선이 추가될 때마다 edge_cnt 업데이트
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        if (find_f(u) == find_f(v)) continue;
        union_f(u, v);
        ++edge_cnt;
    }

    // MST : Minimum Spanning Tree
    int idx = 0;
    while (edge_cnt < n - 1) {
        EDGE e = road[idx++];
        if (find_f(e.city1) == find_f(e.city2)) continue;
        union_f(e.city1, e.city2);
        answer += e.cost;
        ++edge_cnt;
    }

    cout << answer << "\n";
    
    return 0;
}