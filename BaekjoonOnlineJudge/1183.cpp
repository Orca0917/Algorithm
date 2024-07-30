#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    deque<int> v;
    for (int i = 0; i < n; ++i) {
        int a, b; cin >> a >> b;
        int val = b - a;
        v.push_back(val);
    }

    sort(v.begin(), v.end());

    while (v.size() > 2) {
        v.pop_front();
        v.pop_back();
    }
    
    cout << v.back() - v.front() + 1 << "\n";

    return 0;
}