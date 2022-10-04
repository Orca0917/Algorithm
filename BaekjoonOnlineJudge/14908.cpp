#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int N;  // 작업의 수
vector<pair<double, int>> tasks;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N;
    tasks.resize(N);
    for (int i = 0; i < N; ++i) {
        int t, s; cin >> t >> s;
        tasks[i] = {t / (double)s, i + 1};
    }
    
    sort(tasks.begin(), tasks.end());

    for (pii e : tasks) cout << e.second << " ";

    return 0;
}