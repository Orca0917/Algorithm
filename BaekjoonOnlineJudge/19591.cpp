#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

#define FIRST 1
#define SECOND 2
#define SAME 3

using namespace std;

int op_cmp(char a, char b) {

    if (a == '*' || a == '/') {
        if (b == '*' || b == '/') return SAME;
        return FIRST;
    }
    else {
        if (b == '*' || b == '/') return SECOND;
        return SAME;
    }
}


ll calc(ll x, char op, ll y) {
    if (op == '+') return x + y;
    else if (op == '-') return x - y;
    else if (op == '*') return x * y;
    else if (op == '/') return x / y;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    deque<ll> numbers;
    deque<char> operands;
    
    string eq; cin >> eq;

    bool first_neg = (eq[0] == '-');
    if (first_neg) eq.erase(eq.begin());

    ll num = 0;
    for (char c : eq) {
        if ('0' <= c && c <= '9') {
            num *= 10;
            num += (c - '0');
        } else {
            if (first_neg) num *= -1;
            first_neg = false;

            numbers.push_back(num);
            num = 0;
            operands.push_back(c);
        }
    }

    if (first_neg) num *= -1;
    numbers.push_back(num);

    while ((int)numbers.size() >= 2) {
        int prior = op_cmp(operands.front(), operands.back());
        if (prior == FIRST) {
            ll x = numbers.front(); numbers.pop_front();
            ll y = numbers.front(); numbers.pop_front();
            char op = operands.front(); operands.pop_front();
            ll result = calc(x, op, y);
            numbers.push_front(result);
        } 
        else if (prior == SECOND) {
            ll y = numbers.back(); numbers.pop_back();
            ll x = numbers.back(); numbers.pop_back();
            char op = operands.back(); operands.pop_back();
            ll result = calc(x, op, y);
            numbers.push_back(result);
        }
        else if (prior == SAME) {
            ll x1 = numbers[0];
            ll y1 = numbers[1];
            char op1 = operands.front();

            int last = numbers.size() - 1;
            ll x2 = numbers[last - 1];
            ll y2 = numbers[last];
            char op2 = operands.back();

            ll result1 = calc(x1, op1, y1);
            ll result2 = calc(x2, op2, y2);

            if (result1 >= result2) {
                numbers.pop_front();
                numbers.pop_front();
                operands.pop_front();
                numbers.push_front(result1);
            } else {
                numbers.pop_back();
                numbers.pop_back();
                operands.pop_back();
                numbers.push_back(result2);
            }
        }
    }

    cout << numbers.front() << "\n";
    
    return 0;
}