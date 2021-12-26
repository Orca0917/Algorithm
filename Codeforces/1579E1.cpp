#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        int n; cin >> n;
        deque<int> dq;

        for (int i = 0; i < n; ++i) {
            int elem; cin >> elem;
            if (dq.empty()) dq.push_back(elem);
            else {
                if (dq.front() < elem) dq.push_back(elem);
                else dq.push_front(elem);
            }
        }   

        while (!dq.empty()) {
            cout << dq.front() << " ";
            dq.pop_front();
        }

        cout << "\n";
    }
    
    return 0;
}