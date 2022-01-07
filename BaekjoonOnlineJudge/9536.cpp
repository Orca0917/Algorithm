#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int testcase; cin >> testcase;
    string buf; getline(cin, buf);

    while (testcase--) {
        string sen; getline(cin, sen);
        vector<string> v;

        while (true) {
            string sounds; getline(cin, sounds);
            if (sounds == "what does the fox say?") break;

            string token; int cnt = 0;
            istringstream ss(sounds);
            while (getline(ss, token, ' ')) {
                ++cnt;
                if (cnt == 3) v.push_back(token);
            }
        }

        istringstream sstream(sen);
        string word;
        vector<string> answer;
        while (getline(sstream, word, ' ')) {
            bool flag = false;
            for (int i = 0; i < v.size(); ++i)
                if (word == v[i])
                    flag = true;
            if (!flag) answer.push_back(word);
        }

        for (string e : answer) cout << e << " ";
    }
    
    return 0;
}