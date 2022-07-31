#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int N; cin >> N;
    queue<int> q;

    string opt;
    int value;

    while (N--) {

        cin >> opt;

        if (opt == "push") {
            cin >> value;
            q.push(value);
        }
        else if (opt == "pop") {
            if (q.empty()) cout << "-1\n";
            else {
                cout << q.front() << "\n";
                q.pop();
            }
        }
        else if (opt == "size") cout << q.size() << "\n";
        else if (opt == "empty") cout << q.empty() << "\n";
        else if (opt == "front") {
            if (q.empty()) cout << "-1\n";
            else cout << q.front() << "\n";
        }
        else if (opt == "back") {
            if (q.empty()) cout << "-1\n";
            else cout << q.back() << "\n";
        }
    }
    return 0;
}