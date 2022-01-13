#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; cin >> n;
    vector<int> A(n);
    for (auto &a : A) cin >> a;

    deque<int> dq;

    // 1 : 제일 위의 카드 1장을 바닥에 내려 놓는다.
    // 2 : 위에서 두번재 카드를 바닥에 내려 놓는다. (카드가 2장 이상)
    // 3 : 제일 밑에카드를 바닥에 내려 놓는다. (카드가 3장 이상)

    int x = 1;
    for (int i = n - 1; i >= 0; --i) {
        int skill = A[i];
        if (skill == 1) {
            dq.push_front(x++);
        } else if (skill == 2) {
            int k = dq.front(); dq.pop_front();
            dq.push_front(x++);
            dq.push_front(k);
        } else if (skill == 3) {
            dq.push_back(x++);
        }
    }

    for (auto &d : dq) cout << d << " ";
    cout << "\n";
    return 0;
}