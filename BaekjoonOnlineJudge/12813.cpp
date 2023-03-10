#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    string A, B;
    vector<string> answer(5);

    cin >> A >> B;
    for (int i = 0; i < A.length(); ++i) {
        int a = A[i] - '0';
        int b = B[i] - '0';
        answer[0].push_back((a & b) + '0');
        answer[1].push_back((a | b) + '0');
        answer[2].push_back((a ^ b) + '0');
        answer[3].push_back((!a) + '0');
        answer[4].push_back((!b) + '0');
    }

    for (int i = 0; i < 5; ++i)
        cout << answer[i] << "\n";

    
    return 0;
}