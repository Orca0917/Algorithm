#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct EDGE {
    int p1;
    int p2;
    double dist;
};

struct POINT {
    double x;
    double y;
    int index;
};

vector<EDGE> lines;
vector<int> parent(101, 0);
vector<POINT> p;

int _find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = _find(parent[x]);
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

    int N; cin >> N;
    for (int i = 0; i < N; ++i) {
        double x, y; cin >> x >> y;
        p.push_back({x, y, i});
        parent[i] = i;
    }

    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            POINT u = p[i];
            POINT v = p[j];

            double dist = (u.x - v.x) * (u.x - v.x) + (u.y - v.y) * (u.y - v.y);
            dist = (double)sqrt(dist);

            lines.push_back({u.index, v.index, dist});
        }
    }

    sort(lines.begin(), lines.end(), [](const EDGE &a, const EDGE &b) -> bool {
        return a.dist < b.dist;
    });

    double answer = 0;
    int cnt = 0;

    for (int i = 0; cnt < N - 1; ++i) {
        int x = lines[i].p1;
        int y = lines[i].p2;
        double dist = lines[i].dist;

        if (_find(x) == _find(y)) continue;

        answer += dist;
        ++cnt;
        _union(x, y);
    }

    // cout << fixed;
    // cout.precision(2);
    cout << answer << "\n";

    return 0;
}