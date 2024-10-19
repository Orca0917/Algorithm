#include <bits/stdc++.h>

using namespace std;

string addStrings(const string& a, const string& b) {
    string result;
    int carry = 0;
    int i = a.length() - 1, j = b.length() - 1;

    while (i >= 0 || j >= 0 || carry) {
        int digitA = (i >= 0) ? a[i--] - '0' : 0;
        int digitB = (j >= 0) ? b[j--] - '0' : 0;
        int sum = digitA + digitB + carry;
        result.push_back(sum % 10 + '0');
        carry = sum / 10;
    }

    reverse(result.begin(), result.end());
    return result;
}

bool isLess(const string& a, const string& b) {
    if (a.length() != b.length()) return a.length() < b.length();
    return a < b;
}

bool isLessOrEqual(const string& a, const string& b) {
    if (a.length() != b.length()) return a.length() < b.length();
    return a <= b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string lowerBound, upperBound;

    while (cin >> lowerBound >> upperBound) {
        if (lowerBound == "0" && upperBound == "0") break;

        int count = 0;
        string fib1 = "0", fib2 = "1";
        string fibNext = "1";

        // lowerBound보다 큰 첫 번째 피보나치 수 찾기
        while (isLess(fibNext, lowerBound)) {
            fib1 = fib2;
            fib2 = fibNext;
            fibNext = addStrings(fib1, fib2);
        }

        // upperBound 이하의 모든 피보나치 수 세기
        while (isLessOrEqual(fibNext, upperBound)) {
            ++count;
            fib1 = fib2;
            fib2 = fibNext;
            fibNext = addStrings(fib1, fib2);
        }

        cout << count << "\n";
    }

    return 0;
}
