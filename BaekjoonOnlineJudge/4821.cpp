#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long

using namespace std;

int n;
regex comma(",");   // split(",") 를 위한 구분자
regex dash("-");    // split("-") 를 위한 구분자


// 주어진 문자열 s를 re를 기준으로 split한 결과를 string 벡터에 반환
vector<string> tokenizer(string s, regex re) {
    vector<string> ret;

    sregex_token_iterator it(s.begin(), s.end(), re, -1);
    sregex_token_iterator end;

    while (it != end) ret.push_back(*it++);
    return ret;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    

    // 테스트 케이스
    while (cin >> n && n != 0) {
        
        // 출력해야하는 페이지
        set<int> pages;

        // 페이지 구간 목록
        string s; cin >> s;

        // 요청한 구간들을 requests에 저장
        vector<string> requests = tokenizer(s, comma);

        // 각 구간에 대해서 parsing 시작
        for (string &request : requests) {
            vector<string> range = tokenizer(request, dash);

            int start = stoi(range.front());    // 시작 페이지
            int end = stoi(range.back());       // 끝 페이지
            end = min(n, end);                  // 유효한 페이지만 출력

            for (int i = start; i <= end; ++i) pages.insert(i);
        }

        cout << (int)pages.size() << "\n";
    }
    
    return 0;
}