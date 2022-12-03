#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

struct tri {
    int like;
    int val;
    int index;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        int n; cin >> n;
        vector<tri> A(n);
        for (tri &a : A) cin >> a.val;
        for (int i = 0; i < n; ++i) {
            char c; cin >> c;
            A[i].like = c - '0';
            A[i].index = i;
        }

        sort(A.begin(), A.end(), [](const tri &a, const tri &b) {
            if (a.like == b.like)
                return a.val > b.val;
            return a.like > b.like;
        });

        int R = n;

        for (int i = 0; i < n; ++i) {
            A[i].val = R--;
        }

        sort(A.begin(), A.end(), [](const tri &a, const tri &b) {
            return a.index < b.index;
        });

        for (tri a : A) cout << a.val << " ";
        cout << "\n";
    }
    
    return 0;
}