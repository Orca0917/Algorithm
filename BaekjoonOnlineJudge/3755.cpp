#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;


bool alive[1000001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    priority_queue<pii> pq_high, pq_low;
    memset(alive, false, sizeof(alive));

    int opt;
    while (cin >> opt && opt) {
        if (opt == 1) {
            int num, prior; cin >> num >> prior;
            pq_high.push({prior, num});
            pq_low.push({-prior, num});
            alive[num] = true;
        }

        else if (opt == 2) {
            while (!pq_high.empty() && !alive[pq_high.top().second]) pq_high.pop();
            if (pq_high.empty()) cout << "0\n";
            else {
                cout << pq_high.top().second << "\n";
                alive[pq_high.top().second] = false;
                pq_high.pop();
            }
        }

        else if (opt == 3) {
            while (!pq_low.empty() && !alive[pq_low.top().second]) pq_low.pop();
            
            if (pq_low.empty()) cout << "0\n";
            else {
                cout << pq_low.top().second << "\n";
                alive[pq_low.top().second] = false;
                pq_low.pop();
            }
        }
    }
    
    return 0;
}