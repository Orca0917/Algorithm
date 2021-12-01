#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>

#define INF 1234567890
#define pii pair<int, int>
#define ll long long
#define MOD 1'000'000'007

using namespace std;

vector<int> getPI(const string &needle) {
    int n = needle.length();
    vector<int> pi(n, 0);
    int begin = 1, matched = 0;
    while (begin + matched < n) {
        if (needle[begin + matched] == needle[matched]) {
            ++matched;
            pi[begin + matched - 1] = matched;
        } else {
            if (matched == 0) ++begin;
            else {
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];
            }
        }
    }
    return pi;
}

bool kmpSearch(const string &hayStack, const string &needle) {
    int n = hayStack.length(), m = needle.length();
    vector<int> pi = getPI(needle);

    int begin = 0, matched = 0;
    while (begin <= n - m) {
        if (matched < m && hayStack[begin + matched] == needle[matched]) {
            ++matched;
            if (matched == m) {
                return true;
            }
        } else {
            if (matched == 0) ++begin;
            else {
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];
            }
        }
    }

    return false;
}

int testcase;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> testcase;
    while (testcase--) {
        int n; cin >> n;
        string s; cin >> s;
        vector<string> candidate;
        candidate.push_back("aa");
        candidate.push_back("aba");
        candidate.push_back("aca");
        candidate.push_back("abca");
        candidate.push_back("acba");
        candidate.push_back("abbacca");
        candidate.push_back("accabba");
        // ABBACCA
        // ABBABBACCACCA
        int answer = -1;
        for (int i = 0; i < 7; ++i) {
            if (kmpSearch(s, candidate[i])) {
                answer = candidate[i].length();
                break;
            }
        }
        cout << answer << "\n";
    }

    return 0;
}