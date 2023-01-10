/* Этот файл содержит C++ библиотеку с длинной арифметикой

    - Импорт в проект: #include "efficient-long-arithmetic.h"

    - Создание длинного числа: struct big_integer operand;

    - Сложение: addition_big(first_operand, second_operand);

    - Вычитание: subtraction_big(first_operand, second_operand);

    - Базовое умножение O(n^2): basic_multiply(first_operand, second_operand);

    - Быстрое умножение O(n^log(n)): fft_multiply(first_operand, second_operand);

    - Деление: division_big(first_operand, second_operand);

    - Вывод длинного числа: print_big(operand);

    - Запись длинного числа: reading_big(operand);
*/

#include "iostream"
#include "math.h"
#include "vector"
#include "fstream"
#include "ccomplex"
#include <chrono>

using namespace std;

fstream fout("tests\\out.txt", ios::out);
const string zero_dpf = "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
const int BASE = 10;
const int EXECUTION_TIME = 2000;
const int MAX_USE_NAIVE_MUL = 1000;
const double PI = acos(-1);
typedef vector<int> longnum;
typedef complex<double> cd;
typedef vector<cd> vcd;

struct big_integer{
    string convert;
    longnum numbers;
    bool sign = false;
};


void print_big(big_integer &operand){
    if (operand.sign){
        fout << '-';
    }
    for (int i = operand.numbers.size() - 1; i >= 0; i--){
        fout <<  operand.numbers[i];
    }
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

    if (operand_first.numbers != operand_second.numbers){
        return false;
    }
    for (int i = operand_first.numbers.size() - 1; i == 0; --i){
        if (operand_first.numbers.size() != operand_second.numbers.size()){
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

    operand_second.sign = operand_first.sign;
    return operand_second;
}


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


big_integer subtraction_big(big_integer &operand_first, big_integer &operand_second){
    remove_leading_zeros(operand_first.numbers);
    remove_leading_zeros(operand_second.numbers);

    if (operand_first > operand_second) {
        operand_first.sign = false;
        return difference(operand_first, operand_second);
    }
    else{
        operand_second.sign = true;
        return difference(operand_second, operand_first);
    }
}


void extend_number(longnum& v, size_t len) {
    while (len & (len - 1)) {
        ++len;
    }
    v.resize(len);
}


void conversion_to_the_number_system(longnum& res) {
    for (auto i = 0; i < res.size(); ++i) {
        res[i + 1] += res[i] / BASE;
        res[i] %= BASE;
    }
}


big_integer basic_multiply(big_integer& number_first, big_integer& number_second) {
    auto len = number_first.numbers.size();
    big_integer res;
    res.numbers.resize(2*len);

    for (auto i = 0; i < len; ++i) {
        for (auto j = 0; j < len; ++j) {
            res.numbers[i + j] += number_first.numbers[i] * number_second.numbers[j];
        }
    }
    conversion_to_the_number_system(res.numbers);
    return res;
}


//
//longnum karatsuba_multiply(longnum &number_first, longnum &number_second){
//
//    int halfN = max(number_first.size(), number_second.size());
//
//    longnum res(2 * halfN);
//
//    if (min(number_first.size(), number_second.size()) == 2) return basic_multiply(number_first, number_second);
//
//    int k = halfN / 2;
//
//    longnum Ar {number_first.begin(), number_first.begin() + k};
//    longnum Al {number_first.begin() + k, number_first.end()};
//    longnum Br {number_second.begin(), number_second.begin() + k};
//    longnum Bl {number_second.begin() + k, number_second.end()};
//
//    longnum P1 = karatsuba_multiply(Al, Bl);
//    longnum P2 = karatsuba_multiply(Ar, Br);
//
//    longnum Alr(k);
//    longnum Blr(k);
//
//    for (int i = 0; i < k; ++i){
//        Alr[i] = Al[i] + Ar[i];
//        Blr[i] = Bl[i] + Br[i];
//    }
//
//    longnum P3 = karatsuba_multiply(Alr, Blr);
//
//    for (auto i = 0; i < halfN; ++i) {
//        P3[i] -= P2[i] + P1[i];
//    }
//
//    for (auto i = 0; i < halfN; ++i) {
//        res[i] = P2[i];
//    }
//
//    for (auto i = halfN; i < 2 * halfN; ++i) {
//        res[i] = P1[i - halfN];
//    }
//
//    for (auto i = k; i < halfN + k; ++i) {
//        res[i] += P3[i - k];
//    }
//
//    return res;
//
//}


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


vector<cd> transformation(longnum &p) {
    while (__builtin_popcount(p.size()) != 1)
        p.push_back(0);
    return fft(p, polar(1., 2 * PI / p.size()));
}


big_integer interpolation(vector<cd> p) {
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
    vcd A = transformation(operand_first.numbers);
    vcd B = transformation(operand_second.numbers);
    for (int i = 0; i < A.size(); i++)
        A[i] *= B[i];
    return interpolation(A);
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


longnum long_on_short_multiply(longnum a, int b) {
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


void shift_right(longnum &cur) {
    if (cur.size() == 0) {
        cur.push_back(0);
        return;
    }
    cur.push_back(cur[cur.size() - 1]);
    for (size_t i = cur.size() - 2; i > 0; --i) {
        cur[i] = cur[i - 1];
    }
    cur[0] = 0;
}


big_integer division_big(big_integer &first_operand, big_integer &second_operand)
{
    big_integer res;
    big_integer curent;
    res.numbers.resize(first_operand.numbers.size());

    for (int i = first_operand.numbers.size() - 1; i >= 0; i--) {

        shift_right(curent.numbers);
        curent.numbers[0] = first_operand.numbers[i];
        remove_leading_zeros(curent.numbers);
        int x = 0;
        int l = 0, r = 10;
        while (l <= r) {
            int m = (l + r) / 2;
            big_integer cur;
            cur.numbers = long_on_short_multiply(second_operand.numbers, m);

            if (cur <= curent) {
                x = m;
                l = m + 1;
            }
            else {
                r = m - 1;
            }
        }
        res.numbers[i] = x;
        big_integer tmp;
        tmp.numbers = long_on_short_multiply(second_operand.numbers, x);
        curent = subtraction_big(curent, tmp);

    }
    remove_leading_zeros(res.numbers);
    return res;
}



