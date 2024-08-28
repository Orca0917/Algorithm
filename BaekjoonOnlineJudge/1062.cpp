#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

vector<int> ch2int(26, -1);  // 알파벳을 인덱스로 변환하기 위한 벡터

// 'a', 'n', 't', 'i', 'c' 를 제외한 문자들을 인덱스로 변환
void char_to_index() {
    int index = 0;
    for (char c = 'a'; c <= 'z'; ++c) {
        if (c == 'a' || c == 'n' || c == 't' || c == 'i' || c == 'c')
            continue;
        ch2int[c - 'a'] = index++;
    }
}

// 주어진 단어가 현재 배운 문자들로 읽을 수 있는지 판단
bool can_read(string &word, int learned_bits) {
    for (char c : word) {
        if (c == 'a' || c == 'n' || c == 't' || c == 'i' || c == 'c')
            continue;

        // 배우지 못한 문자가 있다면 false 반환
        if (!(learned_bits & (1 << ch2int[c - 'a'])))
            return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // 'antic' 제외한 문자들의 인덱스를 설정
    char_to_index();

    int n, k; 
    cin >> n >> k;

    // k가 5보다 작으면 아무것도 읽을 수 없으므로 0 출력
    if (k < 5) {
        cout << 0;
        return 0;
    }

    int nk = k - 5;  // 'antic'을 제외한 배울 수 있는 문자 개수
    vector<string> words(n);
    for (string &word : words) 
        cin >> word;

    int answer = 0;
    vector<int> indices(21);  // 'antic' 제외한 21개의 문자들 인덱스

    iota(indices.begin(), indices.end(), 0);

    // nk개의 문자를 선택하는 조합을 탐색
    for (int i = 0; i < (1 << 21); ++i) {
        if (__builtin_popcount(i) != nk) 
            continue;

        int learned_bits = i;

        int res = 0;
        for (string &word : words) {
            if (can_read(word, learned_bits)) 
                ++res;
        }

        answer = max(answer, res);
    }

    cout << answer;
    return 0;
}
