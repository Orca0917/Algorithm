#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int N, M, K, answer = 0;
string A[51];
vector<int> candidate;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N >> M;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    cin >> K;

    for (int i = 0; i < N; ++i) {
        int cnt = 0;
        for (int j = 0; j < M; ++j) 
            if (A[i][j] == '0') ++cnt;
        if (cnt <= K && (K - cnt) % 2 == 0)
            candidate.push_back(i);
    }

    for (int i = 0; i < candidate.size(); ++i) {
        int cnt = 0;
        for (int j = i; j < candidate.size(); ++j) {
            if (A[candidate[i]] == A[candidate[j]]) ++cnt;
        }
        answer = max(answer, cnt);
    }

    cout << answer << "\n";

    return 0;
}