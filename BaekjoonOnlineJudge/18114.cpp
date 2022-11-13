#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int N;  // 물건의 개수
int C;  // 무게

vector<int> items;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> N >> C;
    
    items.resize(N);
    for (int &item : items) cin >> item;

    sort(items.begin(), items.end());

    int answer = 0;
    if (*lower_bound(items.begin(), items.end(), C) == C) answer = 1;

    // items[i] + items[j] + items[k] == C 인 i, j, k 가 존재하는지 찾기
    for (int i = 0; i < N && !answer; ++i) {
        for (int j = i + 1; j < N && !answer; ++j) {
            int sum = items[i] + items[j];
            if (sum > C) break;
            else if (sum == C) answer = 1;
            else {
                int need = C - sum;
                if (*lower_bound(items.begin() + j + 1, items.end(), need) == need) answer = 1;
            }
        }
    }

PRINT:
    cout << answer << "\n";
    
    return 0;
}