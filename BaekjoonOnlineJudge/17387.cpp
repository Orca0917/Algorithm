#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int ccw(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3) {
    ll tmp1 = x1 * y2 + x2 * y3 + x3 * y1;
    ll tmp2 = y1 * x2 + y2 * x3 + y3 * x1;

    ll result = tmp1 - tmp2;
    if (result > 0) return 1;
    else if (result < 0) return -1;
    else return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    pair<ll, ll> p1, p2, p3, p4;
    cin >> p1.first >> p1.second;
    cin >> p2.first >> p2.second;
    cin >> p3.first >> p3.second;
    cin >> p4.first >> p4.second;

    int ccw1 = ccw(p1.first, p1.second, p2.first, p2.second, p3.first, p3.second);
    int ccw2 = ccw(p1.first, p1.second, p2.first, p2.second, p4.first, p4.second);
    int ccw3 = ccw(p3.first, p3.second, p4.first, p4.second, p1.first, p1.second);
    int ccw4 = ccw(p3.first, p3.second, p4.first, p4.second, p2.first, p2.second);

    bool answer = (ccw1 * ccw2 <= 0) && (ccw3 * ccw4 <= 0);

    if (ccw1 * ccw2 == 0 && ccw3 * ccw4 == 0) {
        if (p1 > p2) swap(p1, p2);
        if (p3 > p4) swap(p3, p4);
        if (p2 < p3 || p1 > p4) answer = false;
    }

    cout << (int)answer << "\n";
    return 0;
}