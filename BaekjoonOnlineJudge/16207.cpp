#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    ll answer = 0;

    priority_queue<int, vector<int>, less<int>> pq;
    while (n--) {
        int x; cin >> x;
        pq.push(x);   
    }

    int cand = -1;
    while ((cand != -1 && pq.size() >= 2) || (pq.size() >= 4)) {
        if (cand == -1) {
            int temp1 = -pq.top(); pq.pop();
            int temp2 = -pq.top(); pq.pop();
            if (abs(temp1 - temp2) <= 1) cand = temp2;
            else pq.push(-temp2);
        }
        else {
            int temp1 = -pq.top(); pq.pop();
            int temp2 = -pq.top(); pq.pop();
            if (abs(temp1 - temp2) <= 1) {
                answer += 1LL * cand * temp2;
                cand = -1;
            }
            else pq.push(-temp2);
        }
    }

    cout << answer << "\n";
    
    return 0;
}