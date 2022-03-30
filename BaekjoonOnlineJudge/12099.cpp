#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, q; cin >> n >> q;
    vector<pii> v(n);
    for (pii &e : v) cin >> e.first >> e.second;

    sort(v.begin(), v.end());

    while (q--) {
        int lo_a, hi_a, lo_b, hi_b;
        cin >> lo_a >> hi_a >> lo_b >> hi_b;

        // 매운맛 수치 만족하는 구간 찾기 [lo1, hi1]
        int lo1 = lower_bound(v.begin(), v.end(), make_pair(lo_a, 0), [](const pii &left, const pii &right) {
            return left.first < right.first;
        }) - v.begin();
        int hi1 = upper_bound(v.begin(), v.end(), make_pair(hi_a, 0), [](const pii &left, const pii &right) {
            return left.first < right.first;
        }) - v.begin() - 1;

        vector<pii> temp(v.begin() + lo1, v.begin() + hi1 + 1);
        sort(temp.begin(), temp.end(), [](const pii &a, const pii &b) {
            return a.second < b.second;
        });

        // 단맛 수치 만족하는 구간 찾기 [lo2, hi2]
        int lo2 = lower_bound(temp.begin(), temp.end(), make_pair(0, lo_b), [](const pii &left, const pii &right) {
            return left.second < right.second;
        }) - temp.begin();
        int hi2 = upper_bound(temp.begin(), temp.end(), make_pair(0, hi_b), [](const pii &left, const pii &right) {
            return left.second < right.second;
        }) - temp.begin() - 1;

        cout << hi2 - lo2 + 1 << "\n";
    } 
    return 0;
}