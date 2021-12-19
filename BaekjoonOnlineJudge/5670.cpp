/**
 * @file problemSolving.cpp
 * @author 0917jong / dbwhdans / killerWhale0917.github.io
 * @brief 
 * @version 0.1
 * @date 2021-12-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include <bits/stdc++.h>

using namespace std;

int answer = 0;
vector<string> words;

struct TrieNode {
    TrieNode* children[26];
    int childCount;
    bool terminal;

    TrieNode(): childCount(0), terminal(false) {
        memset(children, 0, sizeof(children));
    }

    ~TrieNode() {
        for (int i = 0; i < 26; ++i)
            if (children[i])
                delete children[i];
    }

    void insert(const char *key) {
        if (*key == 0) terminal = true;
        else {
            int next = *key - 'a';
            if (children[next] == NULL) {
                children[next] = new TrieNode();
                ++childCount;
            }
            children[next]->insert(key + 1);
        }
    }

    int find(const char *key) {
        if (*key == 0) return 0; // 문자열의 종료 시점

        int next = *key - 'a';
        if (childCount >= 2 || (childCount == 1 && terminal))
            return children[next]->find(key + 1) + 1;
        else
            return children[next]->find(key + 1);
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed;
    cout.precision(2);

    int n;
    while (cin >> n) {
        words.clear();
        answer = 0;

        words.resize(n);
        TrieNode root = TrieNode();
        for (auto &e : words) {
            cin >> e;
            root.insert(e.c_str()); // string -> const char
        }

        for (auto &e : words) {
            answer += root.find(e.c_str());
            if (root.childCount == 1) ++answer;
        }

        cout << answer / (double)n << "\n";
    }

    return 0;
}