#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
#define cpx complex<double>

using namespace std;


void FFT(vector<cpx> &f, bool do_inv) {
    int n = (int)f.size();

    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        while (!((j ^= bit) & bit)) bit >>= 1;
        if (i < j) swap(f[i], f[j]);
    }

    for (int i = 1; i < n; i <<= 1) {
        double x = (do_inv ? M_PI / i : -M_PI / i);
        cpx w = cpx(cos(x), sin(x));
        for (int j = 0; j < n; j += i << 1) {
            cpx p = cpx(1, 0);
            for (int k = 0; k < i; ++k) {
                cpx temp = f[i + j + k] * p;
                f[i + j + k] = f[j + k] - temp;
                f[j + k] += temp;
                p *= w;
            }
        }
    }

    if (do_inv)
        for (int i = 0; i < n; ++i)
            f[i] /= n;
}

vector<cpx> multiply(vector<cpx> a, vector<cpx> b) {
    int n = 1;
    while (n <= a.size() || n <= b.size()) n <<= 1;
    n <<= 1;

    a.resize(n);
    b.resize(n);
    vector<cpx> ret(n);

    FFT(a, false);
    FFT(b, false);

    for (int i = 0; i < n; ++i) ret[i] = a[i] * b[i];

    FFT(ret, true);

    for (int i = 0; i < n; ++i)
        ret[i] = cpx(round(ret[i].real()), round(ret[i].imag()));

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    vector<cpx> b1(60'001, cpx(0, 0));
    vector<bool> b2(60'001, false);
    vector<cpx> b3(60'001, cpx(0, 0));

    int w1; cin >> w1;
    while (w1--) {
        int x; cin >> x; x += 30000;
        b1[x] = cpx(1, 0);
    }

    int w2; cin >> w2;
    while (w2--) {
        int x; cin >> x; x += 30000;
        b2[x] = true;
    }

    int w3; cin >> w3;
    while (w3--) {
        int x; cin >> x; x += 30000;
        b3[x] = cpx(1, 0);
    }

    // 첫번째 장벽과 3번째 장벽에 대해 convolution 연산 진행 
    // FFT 사용해서 O(NlogN) 에 진행 : N <= 50,000
    vector<cpx> ret = multiply(b1, b3);


    // FFT의 결과의 실수부를 2로 나눈 값이 2번째 장벽에 구멍이 존재하는지 확인
    int answer = 0;
    for (int i = 0; i < ret.size(); ++i) {
        int val = (int)round(ret[i].real());
        if (val > 0 && (i % 2 == 0) && b2[i / 2]) answer += val;
    }

    cout << answer << "\n";
    
    return 0;
}