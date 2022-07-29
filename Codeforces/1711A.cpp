#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int N;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        cin >> N;

        vector<int> answer(N);

        for (int i = 1; i < N; ++i) answer[i] = i;
        answer[0] = N;

        for (int e : answer) cout << e << " ";

        cout << "\n";
    }
    return 0;
}