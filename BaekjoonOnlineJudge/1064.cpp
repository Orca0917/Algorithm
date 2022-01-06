#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

long double getDist(pii &a, pii &b) {
    long double dist = (b.first - a.first) * (b.first - a.first) + (b.second - a.second) * (b.second - a.second);
    return sqrt(dist) * 1L;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cout.precision(16);

    vector<pii> pos(3);
    for (int i = 0; i < 3; ++i) cin >> pos[i].first >> pos[i].second;
    sort(pos.begin(), pos.end(), [](const pii &a, const pii &b) {
        if (a.first == b.first) return a.second < b.second;
        return a.first < b.first;
    });

    pii A = pos[0], B = pos[1], C = pos[2];
    if ((A.first == B.first && B.first == C.first) || (A.second == B.second && B.second == C.second)) {
        cout << "-1\n";
        return 0;
    }

    if (abs(B.second - C.second) * abs(C.first - A.first) == abs(C.first - B.first) * abs(A.second - C.second)) {
        cout << "-1\n";
        return 0;
    }

    vector<long double> result;
    result.push_back((getDist(A, B) + getDist(A, C)) * 2);
    result.push_back((getDist(A, B) + getDist(B, C)) * 2);
    result.push_back((getDist(A, C) + getDist(B, C)) * 2);

    sort(result.begin(), result.end());
    cout << result.back() - result.front() << "\n";
    return 0;
}