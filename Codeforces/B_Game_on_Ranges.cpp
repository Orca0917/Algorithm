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
        deque<pii> A;
        for (int i = 0; i < n; ++i) {
            int start, end; cin >> start >> end;
            A.push_back({start, end});
        }

        sort(A.begin(), A.end(), [](const pii &a, const pii &b) {
            if (a.first == b.first)
                return a.second - a.first > b.second - b.first;
            return a.first < b.first;
        });

        while (!A.empty()) {
            int start = A.front().first;
            int end = A.front().second;
            A.pop_front();

            if (start == end) {
                cout << start << " " << end << " " << start << "\n";
                continue;
            }

            int result = 0;
            if (start == A.front().first) result = A.front().second + 1;
            else result = start;
            cout << start << " " << end << " " << result << "\n";
        }
        cout << "\n";
    }
       
    return 0;
}