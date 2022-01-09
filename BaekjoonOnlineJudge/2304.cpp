#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    vector<int> A(1001, 0);
    int m = 2000, M = 0;
    pii lim = {0, 0};

    for (int i = 0; i < n; ++i) {
        int l, h; cin >> l >> h;
        A[l] = h;
        m = min(m, l);
        M = max(M, l);

        if (lim.first < h) {
            lim.first = h;
            lim.second = l;
        }
    }

    stack<int> left, right;
    for (int i = m; i <= lim.second; ++i) {
        if (left.empty()) left.push(A[i]);
        else {
            if (left.top() > A[i]) left.push(left.top());
            else left.push(A[i]);
        }
    }
    
    for (int i = M; i > lim.second; --i) {
        if (right.empty()) right.push(A[i]);
        else {
            if (right.top() > A[i]) right.push(right.top());
            else right.push(A[i]);
        }
    }

    int answer = 0;
    while (!left.empty()) {
        answer += left.top();
        left.pop();
    }

    while (!right.empty()) {
        answer += right.top();
        right.pop();
    }

    cout << answer << "\n";

    return 0;
}