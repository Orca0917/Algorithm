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
        vector<int> a(n);
        for (int &e : a) cin >> e;

        int answer = 0;
        int x = a[n - 1];
        int M = *max_element(a.begin(), a.end());

        for (int i = n - 1; i >= 0; --i) {
            if (a[i] > x) {
                x = a[i];
                ++answer;
            }

            if (x == M) break;
        }  

        cout << answer << "\n";  
    }
       
    return 0;
}