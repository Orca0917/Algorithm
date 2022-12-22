#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int answer = 1;

    vector<int> n(5);
    for (int i = 0; i < 5; ++i) cin >> n[i];

    while (true) {
        int cnt = 0;
        for (int i = 0; i < 5; ++i) if (answer % n[i] == 0) ++cnt;
        if (cnt >= 3) break;
        ++answer;
    }
    
    cout << answer << "\n";
    
    return 0;
}