#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n, q;
vector<pii> coord;
vector<double> psum, rev_psum;

double get_dist(int id1, int id2) {
    pii a = coord[id1];
    pii b = coord[id2];

    ll sq2 = 1LL * (a.first - b.first) * (a.first - b.first);
    sq2 += 1LL * (a.second - b.second) * (a.second - b.second);

    double ret = (double)sqrt(sq2);
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cout.precision(14);

    cin >> n >> q;
    coord.resize(n + 1);
    for (int i = 1; i <= n; ++i) cin >> coord[i].first;
    for (int i = 1; i <= n; ++i) cin >> coord[i].second;

    psum.resize(n + 1);
    psum[1] = 0;

    rev_psum.resize(n + 1);
    psum[n] = 0;

    for (int i = 2; i <= n; ++i) {
        double dist = get_dist(i - 1, i);
        if (coord[i - 1].second < coord[i].second) dist *= 3.0;
        else if (coord[i - 1].second == coord[i].second) dist *= 2.0;
        psum[i] = psum[i - 1] + dist;
    }

    for (int i = n - 1; i >= 1; --i) {
        double dist = get_dist(i, i + 1);
        if (coord[i + 1].second < coord[i].second) dist *= 3.0;
        else if (coord[i + 1].second == coord[i].second) dist *= 2.0;
        rev_psum[i] = rev_psum[i + 1] + dist;
    }

    while (q--) {
        int a, b; cin >> a >> b;
        if (a < b) cout << psum[b] - psum[a] << "\n";
        else cout << rev_psum[b] - rev_psum[a] << "\n";
    }
    
    return 0;
}