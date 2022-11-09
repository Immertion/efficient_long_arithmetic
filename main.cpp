#include <bits/stdc++.h>
#include <chrono>
using namespace std;

const string zero_dpf = "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
const int base = 10;
const double pi = acos(-1);
typedef vector<int> longnum;
typedef complex<double> cd;
typedef vector<cd> vcd;

fstream fin_answer("answer.txt", ios::in);
fstream fin("in.txt", ios::in);
fstream fout("out.txt", ios::out);

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void print_big(longnum &a){
    if (a.empty()){
        fout << "0";
    }
    else{
        fout << a.back();
    }
    for (int i = a.size() - 2; i >= 0; i--){
        fout <<  a[i];
    }
}

longnum reading_big(string &str, longnum &a){
    for (int i = str.length() - 1; i >= 0; i -= 1){
        a.push_back(static_cast<int>(str[i]) - 48);
    }
    return a;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
longnum addition_big(longnum &a, longnum &b){
    int length;
    if (a.size() > b.size()) {
        length = a.size() + 1;
        while (a.size() != b.size()){
            b.push_back(0);

        }
    }
    else {
        length = b.size() + 1;
        while (a.size() != b.size()){
            a.push_back(0);

        }
    }
    b.push_back(0);
    a.push_back(0);
    for (int ix = 0; ix < length; ix++)
    {
        b[ix] += a[ix];
        b[ix + 1] += (b[ix] / 10);
        b[ix] %= 10;
    }
    if (b[length - 1] == 0)
        length--;

    return b;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
longnum difference (longnum x, longnum y, longnum z, int length)
{
    while (x.size() != y.size()){
        y.push_back(0);
    }


    for (int ix = 0; ix < length; ix++)
    {
        if (x[ix] >= y[ix]){
            z[ix] = x[ix] - y[ix];
        }
        else{
            x[ix + 1] -= 1;
            z[ix] = x[ix] + 10 - y[ix];
        }
    }
    return z;

}

longnum differnt_big(longnum &a, longnum &b, bool &flag){
    int k = 3;
    int length = a.size();
    if (a.size() > b.size())
    {
        length = a.size();
        k = 1;
    }
    else
    if (b.size() > a.size())
    {
        length = b.size();
        k = 2;
    }
    else
        for (int ix = length - 1; ix > 0; ix++)
        {
            if (a[ix] > b[ix])
            {
                k = 1;
                break;
            }

            if(b[ix] > a[ix])
            {
                k = 2;
                break;
            }
        }

    longnum c(length);
    if (k == 1) {
        return difference(a, b, c, length);
    }
    if (k == 2){
        flag = true;
        return difference(b, a, c, length);
    }
    if (k == 3){
        return difference(a, b, c, length);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void extend_vec(vector<int>& v, size_t len) {
    while (len & (len - 1)) {
        ++len;
    }

    v.resize(len);
}

vector<int> naive_mul(const vector<int>& x, const vector<int>& y) {
    auto len = x.size();
    vector<int> res(2 * len);

    for (auto i = 0; i < len; ++i) {
        for (auto j = 0; j < len; ++j) {
            res[i + j] += x[i] * y[j];
        }
    }

    return res;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
longnum karatsuba(longnum &a, longnum &b){

    int halfN = max(a.size(), b.size());

    longnum res(2 * halfN);

    if (min(a.size(), b.size()) == 2) return naive_mul(a, b);

    int k = halfN / 2;

    longnum Ar {a.begin(), a.begin() + k};
    longnum Al {a.begin() + k, a.end()};
    longnum Br {b.begin(), b.begin() + k};
    longnum Bl {b.begin() + k, b.end()};

    longnum P1 = karatsuba(Al, Bl);
    longnum P2 = karatsuba(Ar, Br);

    longnum Alr(k);
    longnum Blr(k);

    for (int i = 0; i < k; ++i){
        Alr[i] = Al[i] + Ar[i];
        Blr[i] = Bl[i] + Br[i];
    }

    longnum P3 = karatsuba(Alr, Blr);

    for (auto i = 0; i < halfN; ++i) {
        P3[i] -= P2[i] + P1[i];
    }

    for (auto i = 0; i < halfN; ++i) {
        res[i] = P2[i];
    }

    for (auto i = halfN; i < 2 * halfN; ++i) {
        res[i] = P1[i - halfN];
    }

    for (auto i = k; i < halfN + k; ++i) {
        res[i] += P3[i - k];
    }

    return res;

}

void normalize(longnum &a){
    for (int i = a.size() - 1; i >= 0; i--){
        if (a[i] == 0){
            a.pop_back();
        }
        else{
            break;
        }
    }
}

void finalize(vector<int>& res) {
    for (auto i = 0; i < res.size(); ++i) {
        res[i + 1] += res[i] / base;
        res[i] %= base;
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ДПФ
template<typename T>

vector<cd> fft(vector<T> p, cd w) {
    int n = p.size();
    if (n == 1) {
        return {p[0]};
    }
    else {
        vector<T> AB[2];
        for (int i = 0; i < n; i++)
            AB[i % 2].push_back(p[i]);
        auto A = fft(AB[0], w * w);
        auto B = fft(AB[1], w * w);
        vector<cd> res(n);
        cd wt = 1;
        int k = n / 2;
        for (int i = 0; i < n; i++) {
            res[i] = A[i % k] + wt * B[i % k];
            wt *= w;
        }
        return res;
    }
}

vector<cd> evaluate(vector<int> p) {
    while (__builtin_popcount(p.size()) != 1)
        p.push_back(0);
    return fft(p, polar(1., 2 * pi / p.size()));
}

vector<int> interpolate(vector<cd> p) {
    int n = p.size();
    auto inv = fft(p, polar(1., -2 * pi / n));
    vector<int> res(n);
    for(int i = 0; i < n; i++)
        res[i] = round(real(inv[i]) / n);
    return res;
}

vector<int> poly_multiply(vector<int> a, vector<int> b) {
    vcd A = evaluate(a);
    vcd B = evaluate(b);
    for (int i = 0; i < A.size(); i++)
        A[i] *= B[i];
    return interpolate(A);
}
vector<int> normalize_dpf(vector<int> a) {
    int carry = 0;
    for (int &x : a) {
        x += carry;
        carry = x / base;
        x %= base;
    }
    while (carry > 0) {
        a.push_back(carry % base);
        carry /= base;
    }
    return a;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
longnum division_big(longnum &a, long long int b) {
    int carry = 0;
    for (int i = (int) a.size() - 1; i >= 0; --i) {
        long long cur = a[i] + carry * 1ll * base;
        a[i] =  int(cur / b);
        carry = int(cur % b);
    }
    while (a.size() > 1 && a.back() == 0)
        a.pop_back();
    return a;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    longnum a, b, answer;
    string str_b, str_answer, str_a;

    char str_operand;
    int division_b;
    int tests = 0;
    vector<int> wrong;
    bool flag;
    while (tests != 13 ) {
        tests += 1;
        flag = false;
        fin >> str_a >> str_operand;
        if (str_operand == '/') fin >> division_b;
        else fin >> str_b;
        str_a = zero_dpf + str_a;
        fin_answer >> str_answer;
        a = reading_big(str_a, a);
        b = reading_big(str_b, b);
        answer = reading_big(str_answer, answer);

        if (str_operand == '+') {
            a = addition_big(a, b);
        }
        else if (str_operand == '-') {

            a = differnt_big(a, b, flag);
            if (flag == true) {
                fout << '-';
            }
        }
        else if (str_operand == '*') {
            auto n = max(a.size(), b.size());
            extend_vec(a, n);
            extend_vec(b, n);
            if (n < 100) {
                a = naive_mul(a, b);
                finalize(a);
            } else {
                a = normalize_dpf(poly_multiply(a, b));
            }
        }
        else if (str_operand == '/'){
            division_big(a, division_b);
        }

        normalize(a);
        if (a.empty()){
            a.push_back(0);
        }
        if (a == answer) {

        }
        else {
            wrong.push_back(tests);
            fout << "wrong ";
            print_big(a);
            fout << ": Answer - ";
            print_big(answer);
            fout << endl;
        }
        a.clear();
        b.clear();
        answer.clear();
    }
    if (wrong.empty()){
        fout << "OK";
    }
    else {
        fout << "wrong test: ";
        for (int i = 0; i < wrong.size(); i++) {
            if (i >= 1){
                fout << ", ";
            }
            fout << wrong[i];
        }
    }

    fin.close();
    fout.close();
}
