#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int D, P, Q; cin >> D >> P >> Q;

    int answer = 0;
    if (D % P == 0 || D % Q == 0) answer = D;
    else {
        if (P < Q) swap(P, Q);

        // P만 사용하는 경우
        int onlyP = (int)ceil(D / (double)P) * P;
        int max_iter = onlyP / P;
        answer = onlyP;
        
        for (int i = 1; i <= max_iter; ++i) {
            int left = onlyP - P * i;
            if ((D - left) % Q == 0) {
                answer = D;
                break;
            }

            // 부족한 값을 Q의 배수로 채워준다.
            left += (int)ceil((D - left) / (double)Q) * Q;
            if (answer == left) break;
            answer = min(answer, left);
        }
    }

    cout << answer << "\n";

    return 0;
}