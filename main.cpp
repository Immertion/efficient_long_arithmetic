#include "efficient-long-arithmetic.h"

void big_integer::PrintBigNumber(fstream &fout){
    if (this->sign){
        fout << '-';
    }
    for (int i = this->numbers.size() - 1; i >= 0; i--){
        fout <<  this->numbers[i];
    }
}

void big_integer::RemoveLeadingZeros(){
    for (int i = this->numbers.size() - 1; i >= 0; i--){
        if (this->numbers[i] == 0){
            this->numbers.pop_back();
        }
        else{
            break;
        }
    }
    if (this->numbers.empty()){
        this->numbers.push_back(0);
    }
}

void big_integer::ReadingBigNumber(){
    if (this->convert[0] == '-'){
        this->sign = true;
        this->convert.erase(0,1);
    }
    for (int i = this->convert.length(); i > 0; i -= 9){
//        this->numbers.push_back(static_cast<int>(this->convert[i]) - 48);
        if (i < 9) {
            this->numbers.push_back(atoi(convert.substr(0, i).c_str()));
        }
        else{
            this->numbers.push_back(atoi(convert.substr(i - 9, i).c_str()));
        }
    }
}


bool big_integer::operator ==(big_integer &operand_second){
    if (this->numbers != operand_second.numbers){
        return false;
    }
    for (int i = this->numbers.size() - 1; i == 0; --i){
        if (this->numbers.size() != operand_second.numbers.size()){
            return false;
        }
    }
    return true;
}

bool big_integer::operator <(big_integer &operand_second){
    if (this->operator==(operand_second)) return false;

    if (this->numbers.size() != operand_second.numbers.size()) {
        return this->numbers.size() < operand_second.numbers.size();
    }
    else {
        for (int i = this->numbers.size() - 1; i >= 0; --i) {
            if (this->numbers[i] != operand_second.numbers[i]) return this->numbers[i] < operand_second.numbers[i];
        }
        return false;
    }
}

bool big_integer::operator <=(big_integer& operand_second){
    return (this->operator<(operand_second) || operator==(operand_second));
}

bool big_integer::operator >(big_integer& operand_second){
    return !(this->operator<=(operand_second));
}

bool big_integer::operator>=(big_integer &operand_second) {
    return !(this->operator<(operand_second));
}

big_integer big_integer::AdditionBigNumbers(big_integer &operand_second){
    int length;
    if (this->numbers.size() > operand_second.numbers.size()) {
        length = this->numbers.size() + 1;
        while (this->numbers.size() != operand_second.numbers.size()){
            operand_second.numbers.push_back(0);
        }
    }
    else {
        length = operand_second.numbers.size() + 1;
        while (this->numbers.size() != operand_second.numbers.size()){
            this->numbers.push_back(0);
        }
    }
    operand_second.numbers.push_back(0);
    this->numbers.push_back(0);
    for (int i = 0; i < length; i++)
    {
        operand_second.numbers[i] += this->numbers[i];
        operand_second.numbers[i + 1] += (operand_second.numbers[i] / BASE);
        operand_second.numbers[i] %= BASE;
    }

    operand_second.sign = this->sign;
    return operand_second;
}

big_integer big_integer::DifferenceBigNumbers (big_integer &operand_second){
    big_integer result;

    result.numbers.resize(this->numbers.size());
    while (this->numbers.size() != operand_second.numbers.size()){
        operand_second.numbers.push_back(0);
    }
    for (int i = 0; i < this->numbers.size(); i++)
    {
        if (this->numbers[i] >= operand_second.numbers[i]){
            result.numbers[i] = this->numbers[i] - operand_second.numbers[i];
        }
        else{
            this->numbers[i + 1] -= 1;
            result.numbers[i] = this->numbers[i] + 10 - operand_second.numbers[i];
        }
    }
    result.sign = this->sign;
    result.RemoveLeadingZeros();
    return result;
}

big_integer big_integer::SubtractionBigNumbers(big_integer &operand_second){
    RemoveLeadingZeros();
    operand_second.RemoveLeadingZeros();

    if (this->operator>(operand_second)) {
        this->sign = false;
        return this->DifferenceBigNumbers(operand_second);
    }
    else{
        operand_second.sign = true;
        return operand_second.DifferenceBigNumbers(*this);
    }
}

void big_integer::NumberExpansion(int length){
    while (length & (length - 1)) ++length;
    this->numbers.resize(length);
}

void big_integer::_ConversionNumberSystem(){
    for (auto i = 0; i < this->numbers.size(); ++i) {
        this->numbers[i + 1] += this->numbers[i] / BASE;
        this->numbers[i] %= BASE;
    }
}

big_integer big_integer::BasicMultiplicationBigNumbers (big_integer &operand_second){
    big_integer result;
    result.numbers.resize(2 * this->numbers.size());
    for (auto i = 0; i < this->numbers.size(); ++i) {
        for (auto j = 0; j < this->numbers.size(); ++j) {
            result.numbers[i + j] += this->numbers[i] * operand_second.numbers[j];
        }
    }
    result._ConversionNumberSystem();
    return result;
}

template<typename T>
vector<cd> big_integer::_FastFourierTransform(vector<T> p, cd w){
    int n = p.size();
    if (n == 1) {
        return {p[0]};
    }
    else {
        vector<T> AB[2];
        for (int i = 0; i < n; i++)
            AB[i % 2].push_back(p[i]);
        auto A = this->_FastFourierTransform(AB[0], w * w);
        auto B = this->_FastFourierTransform(AB[1], w * w);
        vcd result(n);
        cd wt = 1;
        int k = n / 2;
        for (int i = 0; i < n; i++) {
            result[i] = A[i % k] + wt * B[i % k];
            wt *= w;
        }
        return result;
    }
}

vcd big_integer::_Transformation(){
    while (__builtin_popcount(this->numbers.size()) != 1)
        this->numbers.push_back(0);
    return this->_FastFourierTransform(this->numbers, polar(1., 2 * PI / this->numbers.size()));
}

big_integer big_integer::_Interpolation(vector<cd> p){
    int n = p.size();
    auto inv = this->_FastFourierTransform(p, polar(1., -2 * PI / n));
    vector<int> res(n);
    big_integer result;
    for(int i = 0; i < n; i++)
        res[i] = round(real(inv[i]) / n);
    result.numbers = res;
    return result;
}

big_integer big_integer::_PolyMultiplication(big_integer &operand_second){
    vcd A = this->_Transformation();
    vcd B = operand_second._Transformation();
    for (int i = 0; i < A.size(); i++)
        A[i] *= B[i];
    return this->_Interpolation(A);
}

vector<int> big_integer::_NormalizeFastFourierTransform(){
    int carry = 0;
    for (int &x : this->numbers) {
        x += carry;
        carry = x / BASE;
        x %= BASE;
    }
    while (carry > 0) {
        this->numbers.push_back(carry % BASE);
        carry /= BASE;
    }
    return this->numbers;
}

big_integer big_integer::FastFourierTransformMultiplicationBigNumbers(big_integer &operand_second){
    big_integer result = this->_PolyMultiplication(operand_second);
    result.numbers = result._NormalizeFastFourierTransform();
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
    if (this->numbers.size() == 0) {
        this->numbers.push_back(0);
        return;
    }
    this->numbers.push_back(this->numbers[this->numbers.size() - 1]);
    for (size_t i = this->numbers.size() - 2; i > 0; --i) {
        this->numbers[i] = this->numbers[i - 1];
    }
    this->numbers[0] = 0;
}

big_integer big_integer::DivisionBigNumbers(big_integer &operand_second){
    big_integer result;
    big_integer curent;
    result.numbers.resize(this->numbers.size());

    for (int i = this->numbers.size() - 1; i >= 0; i--) {

        curent._ShiftRight();
        curent.numbers[0] = this->numbers[i];
        curent.RemoveLeadingZeros();
        int x = 0;
        int l = 0, r = BASE;
        while (l <= r) {
            int m = (l + r) / 2;
            big_integer cur;
            cur = this->_LongOnShortMultiplication(operand_second, m);
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
        tmp = this->_LongOnShortMultiplication(operand_second, x);
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

    fstream fout("tests\\out.txt", ios::out);
    fstream fin_logic_answer("tests\\answer.txt", ios::in);
    fstream fin_logic("tests\\in.txt", ios::in);


    fout << "The logic test has begun" << endl;
    for (int i = 1; i <= tests; i++){

        fin_logic >> first_operand.convert >> Operator >> second_operand.convert;
        fin_logic_answer >> answer.convert;


        if (Operator == "*" && max(first_operand.convert.size(), second_operand.convert.size()) > MAX_USE_NAIVE_MUL){
            if (first_operand.convert.size() >= second_operand.convert.size()) first_operand.convert = zero_for_dpf + first_operand.convert;
            else second_operand.convert = zero_for_dpf + second_operand.convert;
        }

        first_operand.ReadingBigNumber();
        second_operand.ReadingBigNumber();
        answer.ReadingBigNumber();

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

    fstream fout("tests\\out.txt", ios::out);
    fstream fin_eff_answer("tests\\answer2.txt", ios::in);
    fstream fin_eff("tests\\in2.txt", ios::in);


    fout << "The efficient test has begun" << endl;

    int start_time;
    int end_time;


    for (int i = 1; i <= tests; i++){

        fin_eff >> first_operand.convert >> Operator >> second_operand.convert;
        fin_eff_answer >> answer.convert;


        if (Operator == "*" && max(first_operand.convert.size(), second_operand.convert.size()) > MAX_USE_NAIVE_MUL){
            if (first_operand.convert.size() >= second_operand.convert.size()) first_operand.convert = zero_for_dpf + first_operand.convert;
            else second_operand.convert = zero_for_dpf + second_operand.convert;
        }

        first_operand.ReadingBigNumber();
        second_operand.ReadingBigNumber();
        answer.ReadingBigNumber();

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
        if (first_operand.numbers[first_operand.numbers.size() - 1] == 0 || first_operand.numbers.empty() || tests == 4){
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

//    test_logic();
//    time_test();

    big_integer a, b;
    a.convert = "12345678912345678";
    a.ReadingBigNumber();
    a.PrintBigNumber(fout);

}
