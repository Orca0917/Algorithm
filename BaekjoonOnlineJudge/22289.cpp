#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define cpx complex<double>
#define PI acos(-1)

using namespace std;

void FFT(vector<cpx> &f, bool do_inv) {
    int n = f.size();
    
    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        while (!((j ^= bit) & bit)) bit >>= 1;
        if (i < j) swap(f[i], f[j]);
    }

    for (int i = 1; i < n; i *= 2) {
        double x = (do_inv ? M_PI / i : -M_PI / i);
        cpx w = cpx(cos(x), sin(x));
        for (int j = 0; j < n; j += i << 1) {
            cpx p = cpx(1, 0);
            for (int k = 0; k < i; ++k) {
                cpx tmp = f[i + j + k] * p;
                f[i + j + k] = f[j + k] - tmp;
                f[j + k] += tmp;
                p *= w;
            }
        }
    }

    if (do_inv)
        for (int i = 0; i < n; ++i) f[i] /= n;
}


vector<cpx> multiply(vector<cpx> a, vector<cpx> b) {
    int n = 1;
    while (n <= a.size() || n <= b.size()) n <<= 1;
    n <<= 1;

    a.resize(n);
    b.resize(n);
    vector<cpx> c(n);

    FFT(a, false);
    FFT(b, false);

    for (int i = 0; i < n; ++i) c[i] = a[i] * b[i];

    FFT(c, true);
    for (int i = 0; i < n; ++i) {
        c[i] = cpx(round(c[i].real()), round(c[i].imag()));
    }
    return c;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    string num1, num2;
    cin >> num1 >> num2;

    vector<cpx> a, b;

    for (char c : num1) a.push_back(cpx(c - '0', 0));
    for (char c : num2) b.push_back(cpx(c - '0', 0));

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    vector<cpx> ret = multiply(a, b);
    string answer = "";
    int n = 0;
    for (int i = 0; i < ret.size(); ++i) {
        int x = (int)ret[i].real();
        n += x;
        answer.push_back((n % 10) + '0');
        n /= 10;
    }

    if (n != 0) answer.push_back((n % 10) + '0');
    while (answer.back() == '0') answer.pop_back();

    if (answer.empty()) answer = "0";
    reverse(answer.begin(), answer.end());
    cout << answer << "\n";
    
    return 0;
}