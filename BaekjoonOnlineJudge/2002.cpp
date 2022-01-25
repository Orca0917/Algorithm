#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    map<string, int> m;
    queue<string> q;

    bool hasPassed[1001];
    memset(hasPassed, false, sizeof(hasPassed));

    for (int i = 0; i < n; ++i) {
        string name; cin >> name;
        q.push(name);
        m[name] = i;
    }

    int answer = 0;
    for (int i = 0; i < n; ++i) {
        string target; cin >> target;

        if (hasPassed[m[target]]) continue;

        if (q.front() == target) {
            hasPassed[m[target]] = true;
            q.pop();
        } else {
            hasPassed[m[target]] = true;
            ++answer;
        }

        while (!q.empty() && hasPassed[m[q.front()]])
            q.pop();
    }

    cout << answer << "\n";

    return 0;
}