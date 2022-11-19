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

fstream fin_eff_answer("tests\\answer2.txt", ios::in);
fstream fin_eff("tests\\in2.txt", ios::in);
fstream fin_logic_answer("tests\\answer.txt", ios::in);
fstream fin_logic("tests\\in.txt", ios::in);
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

void test_logic(int tests, big_integer &first_operand, big_integer &second_operand, big_integer &answer,char Operator){
    fout << "The logic test has begun" << endl;
    for (int i = 1; i <= tests; i++){

        fin_logic >> first_operand.convert >> Operator >> second_operand.convert;
        fin_logic_answer >> answer.convert;


        if (Operator == '*' && max(first_operand.convert.size(), second_operand.convert.size()) > MAX_USE_NAIVE_MUL){
            if (first_operand.convert.size() >= second_operand.convert.size()) first_operand.convert = zero_dpf + first_operand.convert;
            else second_operand.convert = zero_dpf + second_operand.convert;
        }
//        Operator == '/' ?  fin >> division_b : fin >> second_operand.convert;

        reading_big(first_operand);
        reading_big(second_operand);
        reading_big(answer);


        if (Operator == '+') {
            if (first_operand.sign && !second_operand.sign || !first_operand.sign && second_operand.sign){
                first_operand = differnt_big(first_operand, second_operand);
            }
            else {
                if (first_operand.sign && second_operand.sign) {
                    first_operand.sign = true;
                }
                else{
                    first_operand.sign = false;
                }
                first_operand = addition_big(first_operand, second_operand);
            }
            if (first_operand.numbers.size() == 1 && first_operand.numbers[0] == 0){
                first_operand.sign = 0;
            }
        }

        else if (Operator == '-') {

            if (first_operand.sign && !second_operand.sign || !first_operand.sign && second_operand.sign){
                if (first_operand.sign && !second_operand.sign) {
                    first_operand.sign = true;
                }
                else{
                    first_operand.sign = false;
                }
                first_operand = addition_big(first_operand, second_operand);
            }
            else {
                first_operand = differnt_big(first_operand, second_operand);
            }
            if (first_operand.numbers.size() == 1 && first_operand.numbers[0] == 0){
                first_operand.sign = 0;
            }
        }

        else if (Operator == '*') {
            auto n = max(first_operand.numbers.size(), second_operand.numbers.size());
            extend_vec(first_operand.numbers, n);
            extend_vec(second_operand.numbers, n);
            if (n < MAX_USE_NAIVE_MUL) {
                first_operand.numbers = naive_mul(first_operand.numbers, second_operand.numbers);

            } else {
                first_operand = fft_multiply(first_operand, second_operand);
            }
            if (first_operand.sign && !second_operand.sign || !first_operand.sign && second_operand.sign){
                first_operand.sign = true;
            }
        }

        else if (Operator == '/'){
//            division_big(first_operand.numbers, division_b);
//            first_operand = big_division(first_operand, second_operand);
        }

        remove_leading_zeros(first_operand.numbers);


        if (first_operand.numbers != answer.numbers || answer.sign != first_operand.sign ) {
            wrong_test.push_back(i);
            fout << i << ") wrong answer ";
            if (first_operand.numbers != answer.numbers || answer.sign != first_operand.sign){
                print_big(first_operand);
                fout << ": correct answer ";
                print_big(answer);
                fout << endl;
            }

        }
        else{
            fout << i << ") OK" << endl;
        }

        first_operand = {};
        second_operand = {};
        answer = {};
    }

    if (wrong_test.empty()){
        fout << "OK" << endl;
    }
    else {
        fout << "wrong test: ";
        for (int i = 0; i < wrong_test.size(); i++) {
            if (i >= 1){
                fout << ", ";
            }
            fout << wrong_test[i];
        }
        fout << endl;
    }
    fout << "the logic test is completed" << endl;
}

void test_eff(int tests, big_integer &first_operand, big_integer &second_operand, big_integer &answer,char Operator){
    fout << "The effectiv test has begun" << endl;

    int start_time;
    int end_time;


    for (int i = 1; i <= tests; i++){

        fin_eff >> first_operand.convert >> Operator >> second_operand.convert;
        fin_eff_answer >> answer.convert;


        if (Operator == '*' && max(first_operand.convert.size(), second_operand.convert.size()) > MAX_USE_NAIVE_MUL){
            if (first_operand.convert.size() >= second_operand.convert.size()) first_operand.convert = zero_dpf + first_operand.convert;
            else second_operand.convert = zero_dpf + second_operand.convert;
        }
//        Operator == '/' ?  fin >> division_b : fin >> second_operand.convert;

        reading_big(first_operand);
        reading_big(second_operand);
        reading_big(answer);

        start_time =  clock();
        if (Operator == '+') {
            if (first_operand.sign && !second_operand.sign || !first_operand.sign && second_operand.sign){
                first_operand = differnt_big(first_operand, second_operand);
            }
            else {
                if (first_operand.sign && second_operand.sign) {
                    first_operand.sign = true;
                }
                else{
                    first_operand.sign = false;
                }
                first_operand = addition_big(first_operand, second_operand);
            }
            if (first_operand.numbers.size() == 1 && first_operand.numbers[0] == 0){
                first_operand.sign = 0;
            }
        }

        else if (Operator == '-') {

            if (first_operand.sign && !second_operand.sign || !first_operand.sign && second_operand.sign){
                if (first_operand.sign && !second_operand.sign) {
                    first_operand.sign = true;
                }
                else{
                    first_operand.sign = false;
                }
                first_operand = addition_big(first_operand, second_operand);
            }
            else {
                first_operand = differnt_big(first_operand, second_operand);
            }
            if (first_operand.numbers.size() == 1 && first_operand.numbers[0] == 0){
                first_operand.sign = 0;
            }
        }

        else if (Operator == '*') {
            auto n = max(first_operand.numbers.size(), second_operand.numbers.size());
            extend_vec(first_operand.numbers, n);
            extend_vec(second_operand.numbers, n);
            if (n < MAX_USE_NAIVE_MUL) {
                first_operand.numbers = naive_mul(first_operand.numbers, second_operand.numbers);

            } else {
                first_operand = fft_multiply(first_operand, second_operand);
            }
            if (first_operand.sign && !second_operand.sign || !first_operand.sign && second_operand.sign){
                first_operand.sign = true;
            }
        }

        else if (Operator == '/'){
//            division_big(first_operand.numbers, division_b);
//            first_operand = big_division(first_operand, second_operand);
        }

        remove_leading_zeros(first_operand.numbers);
        end_time = clock();


        if (first_operand.numbers != answer.numbers || answer.sign != first_operand.sign || end_time - start_time >= EXECUTION_TIME) {
            wrong_test.push_back(i);
            fout << i << ") wrong answer ";
            if (first_operand.numbers != answer.numbers || answer.sign != first_operand.sign){
                print_big(first_operand);
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
            fout << i << ") OK" << endl;
        }

        first_operand = {};
        second_operand = {};
        answer = {};
    }

    if (wrong_test.empty()){
        fout << "OK" << endl;
    }
    else {
        fout << "wrong test: ";
        for (int i = 0; i < wrong_test.size(); i++) {
            if (i >= 1){
                fout << ", ";
            }
            fout << wrong_test[i];
        }
        fout << endl;
    }
    fout << "the effectiv test is completed" << endl;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    struct big_integer first_operand;
    struct big_integer second_operand;
    struct big_integer answer;


    char Operator;
    int division_b;
    int tests_logic = 15;
    int tests_eff = 9;


    test_logic(tests_logic,first_operand,second_operand,answer,Operator);

    test_eff(tests_eff,first_operand,second_operand,answer,Operator);

    fin_logic.close();
    fin_logic_answer.close();
    fin_eff_answer.close();
    fin_eff.close();
    fout.close();
}
