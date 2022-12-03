#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    while (testcase--) {
        int n, a, b; cin >> n >> a >> b;

        if (abs(a - b) > 1 || a + b + 2 > n) {
            cout << "-1\n";
            continue;
        }
        
        int number;
        vector<int> answer(n);

        if (a == b) {

            number = n;
            for (int i = 0, cnt = 0; cnt < a + 1; i += 2, ++cnt)
                answer[i] = number--;
            for (int i = 1, cnt = 0; cnt < a + 1; i += 2, ++cnt)
                answer[i] = number--;
            for (int i = (a + 1) * 2; i < n; ++i)
                answer[i] = number--;

        } else if (a < b) {

            number = 1;
            for (int i = 1, cnt = 0; cnt < b; i += 2, ++cnt)
                answer[i] = number++;
            for (int i = 0, cnt = 0; cnt < b + 1; i += 2, ++cnt)
                answer[i] = number++;
            for (int i = 2 * b + 1; i < n; ++i)
                answer[i] = number++;

        } else if (a > b) {

            number = n;
            for (int i = 1, cnt = 0; cnt < a; i += 2, ++cnt)
                answer[i] = number--;
            for (int i = 0, cnt = 0; cnt < a + 1; i += 2, ++cnt)
                answer[i] = number--;
            for (int i = 2 * a + 1; i < n; ++i)
                answer[i] = number--;

        }

        for (int e : answer) cout << e << " ";
        cout << "\n";
    }
    
    return 0;
}