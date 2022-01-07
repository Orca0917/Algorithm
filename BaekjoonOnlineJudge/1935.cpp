#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

stack<string> st;
vector<int> x;

bool isNumber(string s) {
    if (s == "+" || s == "-" || s == "/" || s == "*") return false;
    return true;
}

void check() {
    while (st.size() >= 3) {
        if (!isNumber(st.top())) break;
        string n1 = st.top(); st.pop();

        if (!isNumber(st.top())) {
            st.push(n1);
            break;
        }
        string n2 = st.top(); st.pop();

        if (isNumber(st.top())) {
            st.push(n2);
            st.push(n1);
            break;
        }

        string op = st.top(); st.pop();
        double d1 = stod(n1);
        double d2 = stod(n2);

        if (op == "+") st.push(to_string(d1 + d2));
        else if (op == "-") st.push(to_string(d1 - d2));
        else if (op == "*") st.push(to_string(d1 * d2));
        else if (op == "/") st.push(to_string(d1 / d2));
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n; cin >> n;
    string s; cin >> s;
    x.resize(n, 0);

    for (int &e : x) cin >> e;

    for (int i = s.length() - 1; i >= 0; --i) {
        char val = s[i];
        if ('A' <= val && val <= 'Z')
            st.push(to_string(x[val - 'A']));
        else 
            st.push(string(1, val));

        if (st.size() >= 3) {
            check();
        }
    }

    cout.setf(ios::fixed);
    cout.precision(2);
    cout << stod(st.top()) << "\n";
    return 0;
}