#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

vector<ll> arr;
int N;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    while (cin >> N && N) {
        // initialize
        arr.clear();

        // input
        arr.resize(N);

        ll answer = -1e9;
        ll accm = 0;
        for (int i = 0; i < N; ++i) {
            int k; cin >> k;
            accm += k;
            answer = max(answer, accm);
            accm = max(accm, 0LL);
        }

        cout << answer << "\n";
    }
    
    return 0;
}