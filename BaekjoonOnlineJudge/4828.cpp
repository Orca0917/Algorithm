#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

string check_syntax(string s) {
    stack<string> st;
    int slen = (int)s.length();

    for (int i = 0; i < slen; ++i) {

        // 닫는 태그
        if (s[i] == '<') {
            if (i + 1 < slen && s[i + 1] == '/') {

                // 닫는 태그 생성
                string close_tag = "";
                while (i < slen && s[i] != '>') close_tag += s[i++];
                close_tag += s[i];

                // CASE1. 닫는 태그와 맞는 여는 태그가 없는 경우
                if (st.empty()) return "invalid";
                
                // 이전 태그와 비교
                string prev_tag = st.top();
                bool do_match = true;
                for (int j = 2; j < prev_tag.length() && do_match; ++j)
                    if (prev_tag[j - 1] != close_tag[j])
                        return "invalid"; 

                // CASE2. 이전 태그와 맞지 않거나, 부적절한 닫는 태그
                if (close_tag[close_tag.length() - 2] == '/') return "invalid"; 
                else st.pop();
            } 

            // 여는 태그
            else {

                // 여는 태그 생성
                string open_tag = "";
                while (i < slen && s[i] != '>') open_tag += s[i++];
                open_tag += s[i];

                int otag_len = open_tag.length();

                // CASE1. < > or < / > : 태그에 대한 이름 지정이 없음
                if (otag_len == 2 || (otag_len == 3 && open_tag[otag_len - 2] == '/')) return "invalid"; 

                // 여는 태그의 이름이 소문자 또는 숫자로만 구성되어 있는지 확인
                for (int j = 1; j < otag_len - 1; ++j)
                    if (('a' <= open_tag[j] && open_tag[j] <= 'z') || ('0' <= open_tag[j] && open_tag[j] <= '9')) ;
                    else {
                        if (open_tag[j] == '/' && j == otag_len - 2) ;
                        else return "invalid"; 
                    }

                // 여는 태그 스택에 삽입
                if (open_tag[otag_len - 2] != '/') st.push(open_tag);
            }
        }

        else if (s[i] == '&') {
            
            // amp 가 포함된 태그 생성
            string token = "";
            while (i < slen && s[i] != ';') token += s[i++];
            token += s[i];

            if (token == "&lt;" || token == "&gt;" || token == "&amp;") ;
            else if (token[1] == 'x') {
                if (token.length() % 2 == 0 || token.length() == 3) return "invalid"; 
                for (int j = 2; j < token.length() - 1; ++j) {
                    if (('a' <= token[j] && token[j] <= 'f') || ('A' <= token[j] && token[j] <= 'F') ||('0' <= token[j] && token[j] <= '9')) ;
                    else return "invalid"; 
                }
            } 
            
            else return "invalid";
        }

        else if (s[i] == '>') return "invalid";
    }

    
    if (st.empty()) return "valid";
    else return "invalid";

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    string s;
    while(getline(cin, s)) cout << check_syntax(s) << "\n";

    return 0;
}