#include "efficient-long-arithmetic.h"


void test_logic(){
    int tests = 16;
    vector<int> wrong_test;
    struct big_integer first_operand;
    struct big_integer second_operand;
    struct big_integer answer;
    string Operator;

    fstream fin_logic_answer("tests\\answer.txt", ios::in);
    fstream fin_logic("tests\\in.txt", ios::in);


    fout << "The logic test has begun" << endl;
    for (int i = 1; i <= tests; i++){

        fin_logic >> first_operand.convert >> Operator >> second_operand.convert;
        fin_logic_answer >> answer.convert;


        if (Operator == "*" && max(first_operand.convert.size(), second_operand.convert.size()) > MAX_USE_NAIVE_MUL){
            if (first_operand.convert.size() >= second_operand.convert.size()) first_operand.convert = zero_dpf + first_operand.convert;
            else second_operand.convert = zero_dpf + second_operand.convert;
        }


        reading_big(first_operand);
        reading_big(second_operand);
        reading_big(answer);


        if (Operator == "+") {
            if (first_operand.sign && !second_operand.sign || !first_operand.sign && second_operand.sign){
                first_operand = subtraction_big(first_operand, second_operand);
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

        else if (Operator == "-") {

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
                first_operand = subtraction_big(first_operand, second_operand);
            }
            if (first_operand.numbers.size() == 1 && first_operand.numbers[0] == 0){
                first_operand.sign = 0;
            }
        }

        else if (Operator == "*") {
            auto n = max(first_operand.numbers.size(), second_operand.numbers.size());
            extend_number(first_operand.numbers, n);
            extend_number(second_operand.numbers, n);
            if (n < MAX_USE_NAIVE_MUL) {
                first_operand = basic_multiply(first_operand, second_operand);

            } else {
                first_operand = fft_multiply(first_operand, second_operand);
            }
            if (first_operand.sign && !second_operand.sign || !first_operand.sign && second_operand.sign){
                first_operand.sign = true;
            }
        }

        else if (Operator == "//"){
            first_operand = division_big(first_operand, second_operand);
        }

        remove_leading_zeros(first_operand.numbers);
        if (first_operand.sign == false && first_operand.numbers.empty()){
            first_operand.sign = true;
        }


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

    fin_logic_answer.close();
    fin_logic.close();
}

void time_test(){
    int tests = 12;
    vector<int> wrong_test;
    struct big_integer first_operand;
    struct big_integer second_operand;
    struct big_integer answer;
    string Operator;

    fstream fin_eff_answer("tests\\answer2.txt", ios::in);
    fstream fin_eff("tests\\in2.txt", ios::in);


    fout << "The effectiv test has begun" << endl;

    int start_time;
    int end_time;


    for (int i = 1; i <= tests; i++){

        fin_eff >> first_operand.convert >> Operator >> second_operand.convert;
        fin_eff_answer >> answer.convert;


        if (Operator == "*" && max(first_operand.convert.size(), second_operand.convert.size()) > MAX_USE_NAIVE_MUL){
            if (first_operand.convert.size() >= second_operand.convert.size()) first_operand.convert = zero_dpf + first_operand.convert;
            else second_operand.convert = zero_dpf + second_operand.convert;
        }


        reading_big(first_operand);
        reading_big(second_operand);
        reading_big(answer);

        start_time =  clock();
        if (Operator == "+") {
            if (first_operand.sign && !second_operand.sign || !first_operand.sign && second_operand.sign){
                first_operand = subtraction_big(first_operand, second_operand);
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

        else if (Operator == "-") {

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
                first_operand = subtraction_big(first_operand, second_operand);
            }
            if (first_operand.numbers.size() == 1 && first_operand.numbers[0] == 0){
                first_operand.sign = 0;
            }
        }

        else if (Operator == "*") {
            auto n = max(first_operand.numbers.size(), second_operand.numbers.size());
            extend_number(first_operand.numbers, n);
            extend_number(second_operand.numbers, n);
            if (n < MAX_USE_NAIVE_MUL) {
                first_operand = basic_multiply(first_operand, second_operand);

            } else {
                first_operand = fft_multiply(first_operand, second_operand);
            }
            if (first_operand.sign && !second_operand.sign || !first_operand.sign && second_operand.sign){
                first_operand.sign = true;
            }
        }

        else if (Operator == "//"){
            first_operand = division_big(first_operand, second_operand);
        }

        remove_leading_zeros(first_operand.numbers);
        if (first_operand.numbers[first_operand.numbers.size() - 1] == 0 || first_operand.numbers.empty() || tests == 4){
            first_operand.sign = false;
        }
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

    fin_eff_answer.close();
    fin_eff.close();
}
