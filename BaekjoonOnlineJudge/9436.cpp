#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n;
    while (cin >> n && n) {
        int t; cin >> t;
        deque<int> li;
        vector<int> val(n + 1, 0);
        for (int i = 1; i <= n; ++i) li.push_back(i);

        while (true) {
            for (int i = 1; i <= t; ++i) {
                val[li.front()] += 1;
                li.push_back(li.front());
                li.pop_front();
            }
            li.pop_back();
            
            bool all_same = true;
            for (int i = 0; i < li.size() - 1 && all_same; ++i) {
                if (val[li[i]] != val[li[i + 1]]) all_same = false;
            }

            if (all_same) break;
        }

        cout << li.size() << " " << val[li.front()] << "\n";
    }
    
    return 0;
}