#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

stack<int> st[7];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n, p; cin >> n >> p;
    int answer = 0;
    for (int i = 0; i < n; ++i) {
        int line, pret; cin >> line >> pret;

        if (st[line].empty()) {
            st[line].push(pret);
            ++answer;
        } else {
            if (st[line].top() < pret) {
                st[line].push(pret);
                ++answer;
            } else if (st[line].top() > pret) {
                while (!st[line].empty() && st[line].top() > pret) {
                    st[line].pop(); ++answer;
                }

                if (st[line].empty()) {
                    st[line].push(pret);
                    ++answer;
                } else if (st[line].top() < pret) {
                    st[line].push(pret);
                    ++answer;
                }
            }
        }
    }

    cout << answer << "\n";
    return 0;
} 


// 5