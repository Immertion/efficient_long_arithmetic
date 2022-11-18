#include "iostream"
#include "math.h"
#include "vector"
#include "fstream"
#include "ccomplex"
#include <chrono>

using namespace std;


const string zero_dpf = "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
const int BASE = 10;
const int EXECUTION_TIME = 2000;
vector<int> wrong_test;
const int MAX_USE_NAIVE_MUL = 1000;
const double PI = acos(-1);
typedef vector<int> longnum;
typedef complex<double> cd;
typedef vector<cd> vcd;

fstream fin_answer("tests\\answer.txt", ios::in);
fstream fin("tests\\in.txt", ios::in);
fstream fout("tests\\out.txt", ios::out);

struct big_integer{
    string convert;
    longnum numbers;
    bool sign = false;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void print_big(big_integer &operand){
    if (operand.sign){
        fout << '-';
    }
    for (int i = operand.numbers.size() - 1; i >= 0; i--){
        fout <<  operand.numbers[i];
    }
}

void reading_big(big_integer &operand){
    if (operand.convert[0] == '-'){
        operand.sign = true;
        operand.convert.erase(0,1);
    }
    for (int i = operand.convert.size() - 1; i >= 0; i--){
        operand.numbers.push_back(static_cast<int>(operand.convert[i]) - 48);
    }
}
bool operator ==(big_integer &operand_first, big_integer &operand_second) {
    if (operand_first.numbers.size() != operand_second.numbers.size()){
        return false;
    }
    for (int i = operand_first.numbers.size(); i > 0; i--){
        if (operand_first.numbers[i] != operand_second.numbers[0]){
            return false;
        }
    }
    return true;
}

bool operator <(big_integer &operand_first, big_integer &operand_second) {
    if (operand_first == operand_second) return false;

    else {
        if (operand_first.numbers.size() != operand_second.numbers.size()) {
            return operand_first.numbers.size() < operand_second.numbers.size();
        }
        else {
            for (long long i = operand_first.numbers.size() - 1; i >= 0; --i) {
                if (operand_first.numbers[i] != operand_second.numbers[i]) return operand_first.numbers[i] < operand_second.numbers[i];
            }

            return false;
        }
    }
}

bool operator <=(big_integer& operand_first, big_integer& operand_second) {
    return (operand_first < operand_second || operand_first == operand_second);
}

bool operator >(big_integer& operand_first, big_integer& operand_second) {
    return !(operand_first <= operand_second);
}

bool operator >=(big_integer& operand_first, big_integer& operand_second) {
    return !(operand_first < operand_second);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
big_integer addition_big(big_integer &operand_first, big_integer &operand_second){
    int length;
    if (operand_first.numbers.size() > operand_second.numbers.size()) {
        length = operand_first.numbers.size() + 1;
        while (operand_first.numbers.size() != operand_second.numbers.size()){
            operand_second.numbers.push_back(0);
        }
    }
    else {
        length = operand_second.numbers.size() + 1;
        while (operand_first.numbers.size() != operand_second.numbers.size()){
            operand_first.numbers.push_back(0);
        }
    }
    operand_second.numbers.push_back(0);
    operand_first.numbers.push_back(0);
    for (int i = 0; i < length; i++)
    {
        operand_second.numbers[i] += operand_first.numbers[i];
        operand_second.numbers[i + 1] += (operand_second.numbers[i] / BASE);
        operand_second.numbers[i] %= BASE;
    }
    if (operand_second.numbers[length - 1] == 0)
        length--;

    operand_second.sign = operand_first.sign;
    return operand_second;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
big_integer difference (big_integer &operand_first, big_integer &operand_second){
    big_integer result;
    result.numbers.resize(operand_first.numbers.size());
    while (operand_first.numbers.size() != operand_second.numbers.size()){
        operand_second.numbers.push_back(0);
    }


    for (int i = 0; i < operand_first.numbers.size(); i++)
    {
        if (operand_first.numbers[i] >= operand_second.numbers[i]){
            result.numbers[i] = operand_first.numbers[i] - operand_second.numbers[i];
        }
        else{
            operand_first.numbers[i + 1] -= 1;
            result.numbers[i] = operand_first.numbers[i] + 10 - operand_second.numbers[i];
        }
    }
    result.sign = operand_first.sign;
    return result;

}

big_integer differnt_big(big_integer &operand_first, big_integer &operand_second){

    if (operand_first > operand_second) {
        operand_first.sign = false;
        return difference(operand_first, operand_second);
    }
    else{
        operand_second.sign = true;
        return difference(operand_second, operand_first);
    }

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void extend_vec(longnum& v, size_t len) {
    while (len & (len - 1)) {
        ++len;
    }
    v.resize(len);
}

void finalize(longnum& res) {
    for (auto i = 0; i < res.size(); ++i) {
        res[i + 1] += res[i] / BASE;
        res[i] %= BASE;
    }
}

longnum naive_mul(longnum& number_first, longnum& number_second) {
    auto len = number_first.size();
    longnum res(2 * len);

    for (auto i = 0; i < len; ++i) {
        for (auto j = 0; j < len; ++j) {
            res[i + j] += number_first[i] * number_second[j];
        }
    }
    finalize(res);
    return res;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
longnum karatsuba(longnum &number_first, longnum &number_second){

    int halfN = max(number_first.size(), number_second.size());

    longnum res(2 * halfN);

    if (min(number_first.size(), number_second.size()) == 2) return naive_mul(number_first, number_second);

    int k = halfN / 2;

    longnum Ar {number_first.begin(), number_first.begin() + k};
    longnum Al {number_first.begin() + k, number_first.end()};
    longnum Br {number_second.begin(), number_second.begin() + k};
    longnum Bl {number_second.begin() + k, number_second.end()};

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

void remove_leading_zeros(longnum &operand){
    for (int i = operand.size() - 1; i >= 0; i--){
        if (operand[i] == 0){
            operand.pop_back();
        }
        else{
            break;
        }
    }
    if (operand.empty()){
        operand.push_back(0);
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

vector<cd> evaluate(longnum &p) {
    while (__builtin_popcount(p.size()) != 1)
        p.push_back(0);
    return fft(p, polar(1., 2 * PI / p.size()));
}

big_integer interpolate(vector<cd> p) {
    int n = p.size();
    auto inv = fft(p, polar(1., -2 * PI / n));
    vector<int> res(n);
    big_integer result;
    for(int i = 0; i < n; i++)
        res[i] = round(real(inv[i]) / n);
    result.numbers = res;
    return result;
}

big_integer poly_multiply(big_integer &operand_first, big_integer &operand_second) {
    vcd A = evaluate(operand_first.numbers);
    vcd B = evaluate(operand_second.numbers);
    for (int i = 0; i < A.size(); i++)
        A[i] *= B[i];
    return interpolate(A);
}
longnum normalize_dpf(longnum a) {
    int carry = 0;
    for (int &x : a) {
        x += carry;
        carry = x / BASE;
        x %= BASE;
    }
    while (carry > 0) {
        a.push_back(carry % BASE);
        carry /= BASE;
    }
    return a;
}

big_integer fft_multiply(big_integer &operand_first, big_integer &operand_second){
    operand_first = poly_multiply(operand_first, operand_second);
    operand_first.numbers = normalize_dpf(operand_first.numbers);
    return operand_first;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
longnum division_big(longnum &a, long long int b) {
    int carry = 0;
    for (int i = (int) a.size() - 1; i >= 0; --i) {
        long long cur = a[i] + carry * 1ll * BASE;
        a[i] =  int(cur / b);
        carry = int(cur % b);
    }
    while (a.size() > 1 && a.back() == 0)
        a.pop_back();
    return a;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

//doesnt work


void shift_right(longnum &a) {
    if (a.size() == 0) {
        a.push_back(0);
        return;
    }
    a.push_back(a[a.size() - 1]);
    for (size_t i = a.size() - 2; i > 0; --i) a[i] = a[i - 1];
    a[0] = 0;
}

longnum waste_multiply(longnum &a, int b) {
    int carry = 0;
    for (size_t i = 0; i < a.size() || carry; ++i) {
        if (i == a.size())
            a.push_back(0);
        long long cur = carry + a[i] * 1ll * b;
        a[i] = int(cur % BASE);
        carry = int(cur / BASE);
    }
    while (a.size() > 1 && a.back() == 0)
        a.pop_back();
    return a;
}



//big_integer big_division(big_integer first_number, big_integer second_number){
//    big_integer tmp;
//    tmp.numbers.resize(first_number.numbers.size() - second_number.numbers.size() + 1);
//    for (int i = tmp.numbers.size() - 1;  i >= 0; i--){
//        longnum res = naive_mul(tmp.numbers,second_number.numbers);
//        while (need_bool(res, first_number.numbers)){
//            tmp.numbers[i]++;
//            res = naive_mul(tmp.numbers,second_number.numbers);
//        }
//        tmp.numbers[i]--;
//    }
//    while (tmp.numbers.size() > 1 && !tmp.numbers.back()){
//        tmp.numbers.pop_back();
//    }
//    return tmp;
//}



////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    struct big_integer first;
    struct big_integer second;
    struct big_integer answer;

    int start_time;
    int end_time;
    char str_operand;
    int division_b;
    int tests = 0;



    while (tests != 1 ) {
        tests += 1;


        fin >> first.convert >> str_operand >> second.convert;
        fin_answer >> answer.convert;


        if (str_operand == '*' && max(first.convert.size(), second.convert.size()) > MAX_USE_NAIVE_MUL){
            if (first.convert.size() >= second.convert.size()) first.convert = zero_dpf + first.convert;
            else second.convert = zero_dpf + second.convert;
        }
//        str_operand == '/' ?  fin >> division_b : fin >> second.convert;

        reading_big(first);
        reading_big(second);
        reading_big(answer);

        start_time =  clock();


        if (str_operand == '+') {
            if (first.sign && !second.sign || !first.sign && second.sign){
                first = differnt_big(first, second);
            }
            else {
                if (first.sign && second.sign) {
                    first.sign = true;
                }
                else{
                    first.sign = false;
                }
                first = addition_big(first, second);
            }
            if (first.numbers.size() == 1 && first.numbers[0] == 0){
                first.sign = 0;
            }
        }

        else if (str_operand == '-') {
            if (first.sign && !second.sign || !first.sign && second.sign){
                if (first.sign && !second.sign) {
                    first.sign = true;
                }
                else{
                    first.sign = false;
                }
                first = addition_big(first, second);
            }
            else {
                first = differnt_big(first, second);
            }
            if (first.numbers.size() == 1 && first.numbers[0] == 0){
                first.sign = 0;
            }
        }

        else if (str_operand == '*') {
            auto n = max(first.numbers.size(), second.numbers.size());
            extend_vec(first.numbers, n);
            extend_vec(second.numbers, n);
            if (n < MAX_USE_NAIVE_MUL) {
                first.numbers = naive_mul(first.numbers, second.numbers);

            } else {
                first = fft_multiply(first, second);
            }
            if (first.sign && !second.sign || !first.sign && second.sign){
                first.sign = true;
            }
        }

        else if (str_operand == '/'){
//            division_big(first.numbers, division_b);
//            first = big_division(first, second);
        }

        remove_leading_zeros(first.numbers);

        end_time = clock();
//        cout << end_time - start_time << " " << tests << endl;
        if (first.numbers != answer.numbers || answer.sign != first.sign || end_time - start_time >= EXECUTION_TIME) {
            wrong_test.push_back(tests);
            fout << tests  << ") wrong answer ";
            if (first.numbers != answer.numbers || answer.sign != first.sign){
                print_big(first);
                fout << ": correct answer ";
                print_big(answer);
                fout << endl;
            }
            else if (end_time - start_time >= EXECUTION_TIME) {
                fout << end_time - start_time << "(ms)";
                fout << ": Time Limit" << endl;
            }
        }
        else{
            fout << tests << ") OK" << endl;
        }

        first = {};
        second = {};
        answer = {};
    }

    cout << 1ll;

    if (wrong_test.empty()){
        fout << "OK";
    }
    else {
        fout << "wrong test: ";
        for (int i = 0; i < wrong_test.size(); i++) {
            if (i >= 1){
                fout << ", ";
            }
            fout << wrong_test[i];
        }
    }


    fin.close();
    fout.close();
}
