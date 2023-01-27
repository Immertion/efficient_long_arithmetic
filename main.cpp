#include "efficient-long-arithmetic.h"

void big_integer::PrintBigNumber(fstream &fout){
    if (sign){
        fout << '-';
    }
    for (int i = numbers.size() - 1; i >= 0; i--){
        fout <<  numbers[i];
    }
}

void big_integer::RemoveLeadingZeros(){
    for (int i = numbers.size() - 1; i >= 0; i--){
        if (numbers[i] == 0){
            numbers.pop_back();
        }
        else{
            break;
        }
    }
    if (numbers.empty()){
        numbers.push_back(0);
    }
}

void big_integer::ReadingBigNumber(string &number){
    convert = number;
    if (convert[0] == '-'){
        sign = true;
        convert.erase(0,1);
    }
    for (int i = convert.length() - 1; i >= 0; i --){
        numbers.push_back(static_cast<int>(convert[i]) - 48);
    }
}


bool big_integer::operator ==(big_integer &operand_second){
    if (numbers != operand_second.numbers){
        return false;
    }
    for (int i = numbers.size() - 1; i == 0; --i){
        if (numbers.size() != operand_second.numbers.size()){
            return false;
        }
    }
    return true;
}

bool big_integer::operator <(big_integer &operand_second){
    if (operator==(operand_second)) return false;

    if (numbers.size() != operand_second.numbers.size()) {
        return numbers.size() < operand_second.numbers.size();
    }
    else {
        for (int i = numbers.size() - 1; i >= 0; --i) {
            if (numbers[i] != operand_second.numbers[i]) return numbers[i] < operand_second.numbers[i];
        }
        return false;
    }
}

bool big_integer::operator <=(big_integer& operand_second){
    return (operator<(operand_second) || operator==(operand_second));
}

bool big_integer::operator >(big_integer& operand_second){
    return !(operator<=(operand_second));
}

bool big_integer::operator>=(big_integer &operand_second) {
    return !(operator<(operand_second));
}

big_integer big_integer::AdditionBigNumbers(big_integer &operand_second){
    int length;
    if (numbers.size() > operand_second.numbers.size()) {
        length = numbers.size() + 1;
        while (numbers.size() != operand_second.numbers.size()){
            operand_second.numbers.push_back(0);
        }
    }
    else {
        length = operand_second.numbers.size() + 1;
        while (numbers.size() != operand_second.numbers.size()){
            numbers.push_back(0);
        }
    }
    operand_second.numbers.push_back(0);
    numbers.push_back(0);
    for (int i = 0; i < length; i++)
    {
        operand_second.numbers[i] += numbers[i];
        operand_second.numbers[i + 1] += (operand_second.numbers[i] / BASE);
        operand_second.numbers[i] %= BASE;
    }

    operand_second.sign = sign;
    operand_second.RemoveLeadingZeros();
    return operand_second;
}

big_integer big_integer::DifferenceBigNumbers (big_integer &operand_second){
    big_integer result;

    result.numbers.resize(numbers.size());
    while (numbers.size() != operand_second.numbers.size()){
        operand_second.numbers.push_back(0);
    }
    for (int i = 0; i < numbers.size(); i++)
    {
        if (numbers[i] >= operand_second.numbers[i]){
            result.numbers[i] = numbers[i] - operand_second.numbers[i];
        }
        else{
            numbers[i + 1] -= 1;
            result.numbers[i] = numbers[i] + BASE - operand_second.numbers[i];
        }
    }
    result.sign = sign;
    result.RemoveLeadingZeros();
    return result;
}

big_integer big_integer::SubtractionBigNumbers(big_integer &operand_second){
    RemoveLeadingZeros();
    operand_second.RemoveLeadingZeros();

    if (operator>(operand_second)) {
        sign = false;
        return DifferenceBigNumbers(operand_second);
    }
    else{
        operand_second.sign = true;
        return operand_second.DifferenceBigNumbers(*this);
    }
}

void big_integer::NumberExpansion(int length){
    while (length & (length - 1)) ++length;
    numbers.resize(length);
}

void big_integer::_ConversionNumberBase(){
    for (auto i = 0; i < numbers.size(); ++i) {
        numbers[i + 1] += numbers[i] / BASE;
        numbers[i] %= BASE;
    }
}

big_integer big_integer::BasicMultiplicationBigNumbers (big_integer &operand_second){
    big_integer result;
    result.numbers.resize(2 * numbers.size());
    for (auto i = 0; i < numbers.size(); ++i) {
        for (auto j = 0; j < numbers.size(); ++j) {
            result.numbers[i + j] += numbers[i] * operand_second.numbers[j];
        }
    }
    result._ConversionNumberBase();
    return result;
}

template<typename T>
vector<cd> big_integer::_FastFourierTransform(vector<T> p, cd w){
    int n = p.size();
    if (n == 0) return {};

    if ((n & (n - 1)) != 0) {
        int size = 1;
        while (size < n)
            size *= 2;
        p.resize(size);
    }

    if (n == 1) {
        return {p[0]};
    }
    else {
        vector<T> A, B;
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) A.push_back(p[i]);
            else B.push_back(p[i]);
        }
        auto Af = big_integer::_FastFourierTransform(A, w * w);
        auto Bf = big_integer::_FastFourierTransform(B, w * w);
        vcd result(n);
        cd wt = 1;
        int k = n / 2;
        for (int i = 0; i < n; i++) {
            result[i] = Af[i % k] + wt * Bf[i % k];
            wt *= w;
        }
        return result;
    }
}

vcd big_integer::_Transformation(){
    while (__builtin_popcount(numbers.size()) != 1)
        numbers.push_back(0);
    return _FastFourierTransform(numbers, polar(1., 2 * PI / numbers.size()));
}

big_integer big_integer::_Interpolation(vector<cd> p){
    int n = p.size();
    auto inv = _FastFourierTransform(p, polar(1., -2 * PI / n));
    vector<int> res(n);
    big_integer result;
    for(int i = 0; i < n; i++)
        res[i] = floor(real(inv[i]) / n + 0.5);
    result.numbers = res;
    return result;
}

big_integer big_integer::_PolyMultiplication(big_integer &operand_second){
    vcd A = _Transformation();
    vcd B = operand_second._Transformation();

    // handle size mismatch
    int size = max(A.size(), B.size());
    if (A.size() < size) A.resize(size);
    if (B.size() < size) B.resize(size);

    for (int i = 0; i < size; i++)
        A[i] *= B[i];

    big_integer result = _Interpolation(A);
    return result;
}

vector<int> big_integer::_NormalizeFastFourierTransform(){
    int carry = 0;
    for (int i = 0; i < numbers.size(); i++) {
        int x = numbers[i] + carry;
        carry = x / BASE;
        numbers[i] = x % BASE;
    }
    while (carry > 0) {
        numbers.push_back(carry % BASE);
        carry /= BASE;
    }
    int i = numbers.size() - 1;
    while (i > 0 && numbers[i] == 0) {
        numbers.pop_back();
        i--;
    }
    return numbers;
}


big_integer big_integer::FastFourierTransformMultiplicationBigNumbers(big_integer &operand_second){
    numbers.resize(pow(2,ceil(log2(numbers.size()))) + 1);
//    operand_second.numbers.resize(pow(2,ceil(log2(operand_second.numbers.size()))) + 1);
    big_integer result = _PolyMultiplication(operand_second);
    result.numbers = result._NormalizeFastFourierTransform();
//    RemoveLeadingZeros();
    return result;
}

big_integer big_integer::_LongOnShortMultiplication(big_integer operand_second, int b){
    int carry = 0;
    for (size_t i = 0; i < operand_second.numbers.size() || carry; ++i) {
        if (i == operand_second.numbers.size())
            operand_second.numbers.push_back(0);
        long long cur = carry + operand_second.numbers[i] * 1ll * b;
        operand_second.numbers[i] = int(cur % BASE);
        carry = int(cur / BASE);
    }
    while (operand_second.numbers.size() > 1 && operand_second.numbers.back() == 0)
        operand_second.numbers.pop_back();
    return operand_second;
}

void big_integer::_ShiftRight(){
    if (numbers.size() == 0) {
        numbers.push_back(0);
        return;
    }
    numbers.push_back(numbers[numbers.size() - 1]);
    for (size_t i = numbers.size() - 2; i > 0; --i) {
        numbers[i] = numbers[i - 1];
    }
    numbers[0] = 0;
}

big_integer big_integer::DivisionBigNumbers(big_integer &operand_second){
    big_integer result;
    big_integer curent;
    result.numbers.resize(numbers.size());

    for (int i = numbers.size() - 1; i >= 0; i--) {
        curent._ShiftRight();
        curent.numbers[0] = numbers[i];
        curent.RemoveLeadingZeros();
        int x = 0;
        int l = 0, r = BASE;
        while (l <= r) {
            int m = (l + r) / 2;
            big_integer cur;
            cur = _LongOnShortMultiplication(operand_second, m);
            if (cur <= curent) {
                x = m;
                l = m + 1;
            }
            else {
                r = m - 1;
            }
        }
        result.numbers[i] = x;
        big_integer tmp;
        tmp = _LongOnShortMultiplication(operand_second, x);
        curent = curent.SubtractionBigNumbers(tmp);
    }
    result.RemoveLeadingZeros();
    return result;
}

void test_logic(){
    int tests = 24;
    vector<int> wrong_test;
    struct big_integer first_operand;
    struct big_integer second_operand;
    struct big_integer answer;
    string Operator;
    string first_number;
    string second_number;
    string answer_number;

    fstream fout("tests\\out.txt", ios::out);
    fstream fin_logic_answer("tests\\answer.txt", ios::in);
    fstream fin_logic("tests\\in.txt", ios::in);


    fout << "The logic test has begun" << endl;
    for (int i = 1; i <= tests; i++){

        fin_logic >> first_number >> Operator >> second_number;
        fin_logic_answer >> answer_number;



        if (Operator == "*" && max(first_operand.convert.size(), second_operand.convert.size()) > MAX_USE_NAIVE_MUL){
            if (first_operand.convert.size() >= second_operand.convert.size()) first_operand.convert = ZERO_FOR_FFT + first_operand.convert;
            else second_operand.convert = ZERO_FOR_FFT + second_operand.convert;
        }

        first_operand.ReadingBigNumber(first_number);
        second_operand.ReadingBigNumber(second_number);
        answer.ReadingBigNumber(answer_number);

        if (Operator == "+") {
            if (first_operand.sign && !second_operand.sign || !first_operand.sign && second_operand.sign){
                first_operand = first_operand.SubtractionBigNumbers(second_operand);
            }
            else {
                if (first_operand.sign && second_operand.sign) {
                    first_operand.sign = true;
                }
                else{
                    first_operand.sign = false;
                }
                first_operand = first_operand.AdditionBigNumbers(second_operand);
            }
            if (first_operand.numbers.size() == 1 && first_operand.numbers[0] == 0){
                first_operand.sign = false;
            }
        }

        else if (Operator == "-") {

            if (first_operand.sign && !second_operand.sign || !first_operand.sign && second_operand.sign){
                if (first_operand.sign && !second_operand.sign) {
                    first_operand.sign = true;
                }
                else{
                    first_operand.sign = false;
                }
                first_operand = first_operand.AdditionBigNumbers(second_operand);
            }
            else {

                first_operand = first_operand.SubtractionBigNumbers(second_operand);
            }
            if (first_operand.numbers.size() == 1 && first_operand.numbers[0] == 0){
                first_operand.sign = false;
            }
        }

        else if (Operator == "*") {
            auto n = max(first_operand.numbers.size(), second_operand.numbers.size());
            first_operand.NumberExpansion(n);
            second_operand.NumberExpansion(n);
            if (n < MAX_USE_NAIVE_MUL) {
                first_operand = first_operand.BasicMultiplicationBigNumbers(second_operand);
            }
            else {
                first_operand = first_operand.FastFourierTransformMultiplicationBigNumbers(second_operand);
            }
            if (first_operand.sign && !second_operand.sign || !first_operand.sign && second_operand.sign){
                first_operand.sign = true;
            }
        }

        else if (Operator == "//"){
            first_operand = first_operand.DivisionBigNumbers(second_operand);
        }

        first_operand.RemoveLeadingZeros();
        if (first_operand.sign == false && first_operand.numbers.empty()){
            first_operand.sign = true;
        }


        if (first_operand.numbers != answer.numbers || answer.sign != first_operand.sign ) {
            wrong_test.push_back(i);
            fout << i << ") wrong answer ";
            if (first_operand.numbers != answer.numbers || answer.sign != first_operand.sign){
                first_operand.PrintBigNumber(fout);
                fout << ": correct answer ";
                answer.PrintBigNumber(fout);
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

    fin_logic_answer.close();
    fin_logic.close();
}

void time_test(){
    int tests = 20;
    vector<int> wrong_test;
    struct big_integer first_operand;
    struct big_integer second_operand;
    struct big_integer answer;
    string Operator;
    string first_number;
    string second_number;
    string answer_number;


    fstream fout("tests\\out.txt", ios::out);
    fstream fin_eff_answer("tests\\answer2.txt", ios::in);
    fstream fin_eff("tests\\in2.txt", ios::in);


    fout << "The efficient test has begun" << endl;

    int start_time;
    int end_time;


    for (int i = 1; i <= tests; i++){

        fin_eff >> first_number >> Operator >> second_number;
        fin_eff_answer >> answer_number;

        if (Operator == "*" && max(first_number.size(), second_number.size()) > MAX_USE_NAIVE_MUL){
            if (first_number.size() >= second_number.size()) first_number = ZERO_FOR_FFT + first_number;
            else second_number = ZERO_FOR_FFT + second_number;
        }

        first_operand.ReadingBigNumber(first_number);
        second_operand.ReadingBigNumber(second_number);
        answer.ReadingBigNumber(answer_number);

        start_time =  clock();
        if (Operator == "+") {
            if (first_operand.sign && !second_operand.sign || !first_operand.sign && second_operand.sign){
                first_operand = first_operand.SubtractionBigNumbers(second_operand);
            }
            else {
                if (first_operand.sign && second_operand.sign) {
                    first_operand.sign = true;
                }
                else{
                    first_operand.sign = false;
                }
                first_operand = first_operand.AdditionBigNumbers(second_operand);
            }
            if (first_operand.numbers.size() == 1 && first_operand.numbers[0] == 0){
                first_operand.sign = 0;
            }
        }

        else if (Operator == "-") {

            if (first_operand.sign && !second_operand.sign || !first_operand.sign && second_operand.sign){
                if (first_operand.sign && !second_operand.sign) {
                    first_operand.sign = true;
                }
                else{
                    first_operand.sign = false;
                }
                first_operand = first_operand.AdditionBigNumbers(second_operand);
            }
            else {
                first_operand = first_operand.SubtractionBigNumbers(second_operand);
            }
            if (first_operand.numbers.size() == 1 && first_operand.numbers[0] == 0){
                first_operand.sign = 0;
            }
        }

        else if (Operator == "*") {
            auto n = max(first_operand.numbers.size(), second_operand.numbers.size());
            first_operand.NumberExpansion(n);
            second_operand.NumberExpansion(n);
            if (n < MAX_USE_NAIVE_MUL) {
                first_operand = first_operand.BasicMultiplicationBigNumbers(second_operand);
            } else {
                first_operand = first_operand.FastFourierTransformMultiplicationBigNumbers(second_operand);
            }
            if (first_operand.sign && !second_operand.sign || !first_operand.sign && second_operand.sign){
                first_operand.sign = true;
            }
        }

        else if (Operator == "//"){
            first_operand = first_operand.DivisionBigNumbers(second_operand);
        }

        first_operand.RemoveLeadingZeros();
        if (first_operand.numbers[first_operand.numbers.size() - 1] == 0 || first_operand.numbers.empty()){
            first_operand.sign = false;
        }
        end_time = clock();


        if (first_operand.numbers != answer.numbers || answer.sign != first_operand.sign || end_time - start_time >= EXECUTION_TIME) {
            wrong_test.push_back(i);
            fout << i << ") wrong answer ";
            if (first_operand.numbers != answer.numbers || answer.sign != first_operand.sign){
                first_operand.PrintBigNumber(fout);
                fout << ": correct answer ";
                answer.PrintBigNumber(fout);

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
    fout << "the efficient test is completed" << endl;

    fin_eff_answer.close();
    fin_eff.close();
}

int main()
{
    fstream fout("tests\\out.txt", ios::out);
    fstream tout("tests\\tout1.txt",ios::out);
//    test_logic();
//    time_test();
    tout << "digit time" << endl;

    string aa = "1";
    srand(time(0));
    for (int i = 1; i < 10000; i+= 100){
        big_integer a, b;
        a.ReadingBigNumber(aa);
        b = a;
        for (int j = 0; j < 100; j++) {
            int digit = 1 + rand() % 8;
            aa += to_string(digit);
        }
        auto start = chrono::steady_clock::now();
        for(int l = 0; l < 5; l++){
        a.DivisionBigNumbers(b);
        }
        auto end = chrono::steady_clock::now();
        auto time = chrono::duration_cast<chrono::microseconds>(end - start);
        tout << i << " " << (time.count() / 5) << endl;
//        a.PrintBigNumber(fout);
        fout << endl;
    }



}
