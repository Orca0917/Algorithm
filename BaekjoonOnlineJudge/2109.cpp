/*
 * author: 0917jong
 * date: 2021-12-04
 */

#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<pii> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i].second >> a[i].first;
    
    sort(a.begin(), a.end(), [&](const pii a, const pii b){
        return a.first > b.first;
    });

    priority_queue<int> pq;
    int k = 0, answer = 0;
    for (int i = 10000; i >= 1; --i) {
        while (k < n && a[k].first == i) {
            pq.push(a[k].second);
            k++;
        }
        if (!pq.empty()) {
            answer += pq.top();
            pq.pop();
        }
    }
    cout << answer << "\n";
    return 0;
}
