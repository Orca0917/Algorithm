#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define MOD 1234567891

using namespace std;

int N; // numbers 배열의 크기
int L; // 구하고 싶은 동민수열의 길이
int uniq_num = 0;

int start_end[8][8];
ll memo[1000][8][8];

set<string> seen_list;
map<int, int> mp;


ll dp(int length, int start, int end) {

    // 기저사례
    if (length == 0) return 0;
    else if (length == 1) return start_end[start][end];
    
    // length가 너무 클 수 있기 때문에 mapping 진행
    auto it = mp.find(length);
    if (it == mp.end()) mp[length] = uniq_num++;
    
    int idx = mp[length];
    
    // memoization
    ll &ret = memo[idx][start][end];
    if (ret != -1) return ret;
    
    // divide & conquer
    int half_length = (int)(length / 2);
    ret = (dp(half_length, start, 4) * dp(length - half_length, 4, end)) % MOD;
    ret += (dp(half_length, start, 7) * dp(length - half_length, 7, end)) % MOD;

    return ret = ret % MOD;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> L;

    // 1. initialize
    memset(start_end, 0, sizeof(start_end));
    memset(memo, -1, sizeof(memo));

    // 2. numbers 배열 입력받기
    for (int i = 0; i < N; ++i) {
        string num; cin >> num;

        // 4와 7 이외의 숫자가 포함된 경우 pass
        bool has_other_num = false;
        for (char digit : num) {
            if (digit != '4' && digit != '7') {
                has_other_num = true;
                break;
            }
        }
        if (has_other_num) continue;
        
        // 이미 입력된 숫자인 경우 pass
        if (seen_list.find(num) != seen_list.end()) continue;
        seen_list.insert(num);

        int start_i = num[0] - '0';
        int end_i = num.back() - '0';
        start_end[start_i][end_i] += 1; // += 1
    }

    // 3. answer 구하기
    ll answer = dp(L, 4, 4) + dp(L, 4, 7) + dp(L, 7, 4) + dp(L, 7, 7);
    cout << answer % MOD << "\n";
    
    return 0;
}