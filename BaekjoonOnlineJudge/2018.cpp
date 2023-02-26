#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    
    int answer = 0;
    for (int start = 1; start <= n; ++start) {
        int temp = start;
        for (int adder = 1; temp < n; ++adder) {
            temp += start + adder;
        }
        if (temp == n) ++answer;
    }

    cout << answer << "\n";
    
    return 0;
}