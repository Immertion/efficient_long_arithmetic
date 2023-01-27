#ifndef LONG_ARIFMETIC
#define LONG_ARIFMETIC

#include "iostream"
#include "math.h"
#include "vector"
#include "fstream"
#include "ccomplex"
#include <chrono>
#include <gmpxx.h>

using namespace std;

const string ZERO_FOR_FFT = "";
const int BASE = 100000000;
const int EXECUTION_TIME = 2000;
const int MAX_USE_NAIVE_MUL = 0;
const double PI = acos(-1);
typedef complex<double> cd;
typedef vector<cd> vcd;

struct big_integer{

    string convert;
    vector<int> numbers;
    bool sign = false;

private:

    void _ShiftRight();
    void _ConversionNumberBase();
    template<typename T>
    vector<cd> _FastFourierTransform(vector<T> p, cd w);
    vector<cd> _Transformation();
    big_integer _Interpolation(vector<cd> p);
    big_integer DifferenceBigNumbers (big_integer &operand_second);
    big_integer _PolyMultiplication(big_integer &operand_second);
    big_integer _LongOnShortMultiplication(big_integer second_number, int b);
    vector<int> _NormalizeFastFourierTransform();

public:
    /* Удаление лидирующих нулей */
    void RemoveLeadingZeros();
    void NumberExpansion(int length);
    /* Вывод длинного числа */
    void PrintBigNumber(fstream &fout);
    /* Считывание длинного числа */
    void ReadingBigNumber(string &number);
    bool operator ==(big_integer &operand_second);
    bool operator <(big_integer &operand_second);
    bool operator <=(big_integer& operand_second);
    bool operator >(big_integer& operand_second);
    bool operator >=(big_integer& operand_second);
    /* Сложение длинных чисел */
    big_integer AdditionBigNumbers(big_integer &operand_second);
    /* Вычитание длинных чисел */
    big_integer SubtractionBigNumbers(big_integer &second_operand);
    /* Базовое O(n^2) умножение длинных чисел */
    big_integer BasicMultiplicationBigNumbers (big_integer &operand_second);
    /* Быстрое O(nlog(n)) умножение длинных чисел */
    big_integer FastFourierTransformMultiplicationBigNumbers(big_integer &operand_second);
    /* Деление длинных чисел */
    big_integer DivisionBigNumbers(big_integer &operand_second);
    };

#endif