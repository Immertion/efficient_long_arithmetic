
### МИНИСТЕРСТВО НАУКИ И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ

### Федеральное государственное автономное образовательное учреждение высшего образования

## Дальневосточный федеральный университет
### ИНСТИТУТ МАТЕМАТИКИ И КОМПЬЮТЕРНЫХ ТЕХНОЛОГИЙ
### Департамент математического и компьютерного моделирования
### ДОКЛАД о практическом задании по дисциплине АИСД

# Эффективная длинная арифметика (14)

### Сербинович Матвей Денисович, гр. Б9121-09.03.03пикд

### г. Владивосток, 2022

# Содержание

[*Содержание*](#содержание)

[*Аннотация*](#аннотация)

[*1. Введение*](#1-введение)

[*1.1 Применение*](#11-применение)

[*1.2 Глоссарий*](#12-глоссарий)

[*1.3 Обзор существующих алгоритмов*](#13-обзор-существующих-алгоритмов)

[*2 Формальная постановка задачи*](#2-формальная-постановка-задачи)

[*3. Формальное описание алгоритма*](#3-формальное-описание-алгоритма)

[*3.1 Длинная арифметика*](#31-длинная-арифметика)

[*4. Реализация проект*](#4-реализация-проекта)

[*4.1 Начальные данные*](#41-начальные-данные)

[*4.2 Сложение длинных чисел*](#42-сложение-длинных-чисел)

[*4.3 Вычитание длинных чисел*](#43-вычитание-длинных-чисел)

[*4.4.1 Умножение длинных чисел (базовый метод)*](#441-умножение-длинных-чисел-базовый-метод)

[*4.4.2 Умножение длинных чисел (Быстрое и Дискретное преобразование фурье, Алгоритм Кули-Тьюки)*](#442-умножение-длинных-чисел-быстрое-и-дискретное-преобразование-фурье-алгоритм-кули-тьюки)

[*4.5 Длинное деление чисел*](#45-длинное-деление)

[*5 Тестирование*](#5-тестирование)

[*Список литературы*](#список-литературы)

# 1 Введение

## 1.1 Длинная арифметика
Длинная арифметика — это набор программных средств (структуры данных и алгоритмы), которые позволяют работать с числами гораздо больших величин, чем это позволяют стандартные типы данных.
Цифры могут использоваться из той или иной системы счисления, обычно применяются десятичная система счисления и ее степени (десять тысяч, миллиард), либо двоичная система счисления.
Операции над числами в этом виде длинной арифметики могут производятся с помощью "школьных" алгоритмов сложения, вычитания, умножения, деления столбиком. Также, к ним также применимы алгоритмы быстрого умножения: Быстрое преобразование Фурье[] и Алгоритм Карацубы[] и т.д.

## 1.2 Применение

-  Составление кода для процессоров (микроконтроллеров) низкой разрядности. Например, микроконтроллеры серии AVR имеют АЦП с разрядностью 10 бит и регистры с разрядностью 8 бит. Этого недостаточно для обработки информации с АЦП; без длинной арифметики не обойтись;
-  Криптография. Большинство систем подписывания и шифрования данных используют целочисленную арифметику по модулю m, где m — очень большое натуральное число, не обязательно простое. Например, при реализации метода шифрования RSA, криптосистемы Рабина или схемы Эль-Гамаля требуется обеспечить точность результатов умножения и возведения в степень порядка $10^{309}$.
-  Математическое и финансовое ПО. Результат вычисления на бумаге должен совпадать с результатом работы компьютера с точностью до последнего разряда. В частности, калькулятор Windows (начиная с Windows 95) проводит четыре арифметических действия с намного большей точностью, чем позволяет процессор x86. Для научных и инженерных расчётов длинная арифметика применяется редко, так как ошибки во входных данных обычно намного больше, чем ошибки округления;
-  Спортивное программирование 

Источник [<a href="https://habr.com/ru/post/207754/" target="_blank">2</a>]


## 1.3 Глоссарий
1. База длинной арифметики - это максимальное число хранимое в массиве длинной арифметики(base)

2.  Комплексные числа — это числа вида $a + bi$, где $a$ и $b$ это обычные вещественные числа, а $i$ это так называемая мнимая единица: это число, для которого выполняется равенство $i^2 = -1$.

3. Разделяй и властвуй (англ. divide and conquer)  — парадигма разработки алгоритмов, заключающаяся в рекурсивном разбиении решаемой задачи на две или более подзадачи того же типа, но меньшего размера, и комбинировании их решений для получения ответа к исходной задаче


## 1.4 Обзор существующих алгоритмов

Существуют уже готовые алгоритмы длинной арифметики
- Библиотека "gmpxx.h" для gcc
- https://brestprog.by/topics/longarithmetics/

# 2. Формальная постановка задачи 

### В данной работе требуется 

 - Изучиить по литературным источникам и описать его в форме научного доклада
 - Реализовать структуру данных с использованием языков программирования С++ и Python
 - В моей длинной арифметике будет ограничение в 30000000 символов
 - Выполнить иследование данной стуртуры данных

# 3. Формальное описание алгоритма

## 3.1 Начальные данные

``` c++
struct big_integer{
    string convert;
    vector<int> numbers;
    bool sign = false;
    int BASE = 1000000000
};
```
Класс состоит из исходной структуры - строка, рабочей структуры - динамический массив и булевой переменной, которая хранит в себе знак числа

При преобразовании строки в массив мы будем хранить длинное число зеркально, то есть первый элеммент будет последним в массиве.

## 3.2 Сложение длинных чисел
---
Рассмотрим арифметическую операцию сложения, применяемую в длинной арифметике.
``` c++
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
```
Сначала складываем отдельные разряды, начиная с конца, делим получившуюся сумму на BASE и получаем целую часть от деления на BASE, которую мы сразу прибавляем к следующему разряду. Далее мы отсекаем первый разряд полученного числа, если, он есть. В самом конце определяем знак.

Источник [<a href="https://habr.com/ru/post/113642/" target="_blank">3</a>]


## 3.3 Вычитание длинных чисел
---
Для начала нужно определить какое из чисел больше, если числа одинаковой длинны, то переходим к по разрядоному сравнению

``` c++
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
```
Для каждого разряда мы добавляем 10, с учетом вычитания из старшего разряда единицу. Это делается для упрощения вычитания разрядов. Эта операция делается лишь в том случае, когда рассматриваемый разряд не является последним в массиве (первым в числе). 

``` c++
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
``` 
Источник [<a href="https://habr.com/ru/post/113642/" target="_blank">3</a>]

## 3.4 Умножение длинных чисел

### 3.4.1 Умножение длинных чисел (базовый метод)
---
Самый простой и не эффективный алгоритм умножения длинных чисел. Асиптотика O($n^2$)
``` c++
void conversion_to_the_number_system(longnum& res) {
    for (auto i = 0; i < res.size(); ++i) {
        res[i + 1] += res[i] / BASE;
        res[i] %= BASE;
    }
}

vector<int> naive_mul(longnum& number_first, longnum& number_second) {
    auto len = number_first.size();
    longnum res(2 * len);

    for (auto i = 0; i < len; ++i) {
        for (auto j = 0; j < len; ++j) {
            res[i + j] += number_first[i] * number_second[j];
        }
    }
    conversion_to_the_number_system(res);
    return res;
}

``` 
Создаём массив размером 2*len(где len длинна первого числа)
Функция conversion_to_the_number_system() переносит цифру если ячейка массива больше нашей базы
Первое число последовательно умножается на каждую цифру. Результат умножения на i-тую цифру прибавляется к общему результату со сдвигом на i – 1.

[3]
https://habr.com/ru/post/113642/

### 3.4.2 Умножение длинных чисел (Быстрое и Дискретное преобразование фурье, Алгоритм Кули-Тьюки)
---
#### История алгоритма

Алгоритм и его рекурсивная реализация были изобретены около 1805 года К. Гауссом при интерполировании траекторий астероидов Паллада и Юнона. Тогда открытие не получило широкого распространения и было опубликовано лишь после смерти учёного на новой латыни. Результат Гаусса несколько раз переоткрывался в различных формах в течение последующих 150 лет и стал популярным после публикации в 1965 году статьи Дж. Кули  (англ.)рус. из IBM и Дж. Тьюки из Принстона, в которой алгоритм был в очередной раз переоткрыт, а также описывалась удобная реализация для ЭВМ. 
Тот факт, что первооткрывателем алгоритма является Гаусс, был обнаружен лишь через несколько лет после публикации Кули и Тьюки. В своей статье они ссылались только на работу И. Дж. Гуда, в которой был описан алгоритм Гуда — Томаса. 

#### Основная цель

Основная задача, которая решается при помощи быстрого преобразования Фурье (Fast Fourier Transform, FFT) — это умножение многочленов за время O(nlogn) .

Многочлены можно хранить не в виде вектора коэффициентов, а в виде набора значений в некоторых точках. Над многочленами в таком виде очень удобно производить арифметические операции, в том числе умножать их за время  (нужно просто перемножить значения в соответствующих точках). С другой стороны, непонятно, как считать значения в других точках, да и знать сами коэффициенты бывает полезно. А воостанавливать коэффициенты по значениям в некотором наборе точек сложно, тот же интерполяционный многочлен Лагранжа вычисляется за время . Да и многочлены нам обычно задаются в форме вектора коэффициентов, получить значеня в  произвольных точках вряд ли можно быстрее, чем за .


#### Интерполяция

**Теорема.** Пусть есть набор различных точек $x_0, x_1, \dots, x_{n}$. Многочлен степени $n$ однозначно задаётся своими значениями в этих точках.

**Доказательство** будет конструктивным — можно явным образом задать многочлен, который принимает заданные значения $y_0, y_1, \ldots, y_n$ в этих точках:

$$
y(x)=\sum\limits_{i=0}^{n}y_i\prod\limits_{j\neq i}\dfrac{x-x_j}{x_i-x_j}
$$


Этот многочлен называется интерполяционным многочленом Лагранжа, а сама задача проведения многочлена через точки — интерполяцией.

<p align="center"><img src="Images\LagrangeInterpolatingPoly.gif"></p>

**Примечание.** На практике интерполяцию решают методом Гаусса: её можно свести к решению линейного уравнения $aX = y$, где $X$ это матрица следующего вида:

$$
\begin{pmatrix}
    1 & x_0 & x_0^2 & \ldots & x_0^n \\
    1 & x_1 & x_1^2 & \ldots & x_1^n \\
    \vdots & \vdots & \vdots & \ddots & \vdots \\
    1 & x_n & x_n^2 & \ldots & x_n^n \\
\end{pmatrix}
$$

Важный факт: многочлен можно однозначно задать не только своими коэффициентами, но также корнями и значениями хотя бы в $(n+1)$-ой точке.

#### Умножение через интерполяцию

Что происходит со значениями многочлена-произведения $A(x) B(x)$ в конкретной точке $x_i$? Оно просто становится равным $A(x_i) B(x_i)$.

**Основная идея алгоритма:** В каких-то различных $n + m$ точках для обоих многочленов $A$ и $B$, попарно перемножив их, мы за $O(n + m)$ операций получаем  значения в тех же точках для многочлена $A(x) B(x)$ — а с их помощью можно интерполяцией получить исходный многочлен и решить задачу.

``` c++
big_integer poly_multiply(big_integer &operand_first, big_integer &operand_second) {
    vcd A = evaluate(operand_first.numbers);
    vcd B = evaluate(operand_second.numbers);
    for (int i = 0; i < A.size(); i++)
        A[i] *= B[i];
    return interpolate(A);
}
```

#### Дискретное преобразование Фурье

*Дискретным преобразованием Фурье* называется вычисление значений многочлена в комплексных корнях из единицы:

$$
y_j = \sum_{k=0}^{n-1} x_n e^{i\tau \frac{kj}{n}} = \sum_{k=0}^{n-1} x_n w_1^{kj}
$$

*Обратным дискретным преобразованием Фурье* называется, обратная операция — интерполяция коэффициентов $x_i$ по значениям $X_i$.

$$
x_j = \frac{1}{n} \sum_{k=0}^{n-1} y_n e^{-i\tau \frac{kj}{n}} = \frac{1}{n} \sum_{k=0}^{n-1} y_n w_{n-1}^{kj}
$$

 При вычислении ПФ мы практически применяем матрицу к вектору:

$$
\begin{pmatrix}
w^0 & w^0 & w^0 & w^0 & \dots & w^0 \\
w^0 & w^1 & w^2 & w^3 & \dots & w^{-1} \\
w^0 & w^2 & w^4 & w^6 & \dots & w^{-2} \\
w^0 & w^3 & w^6 & w^9 & \dots & w^{-3} \\
\vdots & \vdots & \vdots & \vdots & \ddots & \vdots \\
w^0 & w^{-1} & w^{-2} & w^{-3} & \dots & w^1
\end{pmatrix}\begin{pmatrix} a_0 \\ a_1 \\ a_2 \\ a_3 \\ \vdots \\ a_{n-1}
\end{pmatrix} = \begin{pmatrix} y_0 \\ y_1 \\ y_2 \\ y_3 \\ \vdots \\ y_{n-1}
\end{pmatrix}
$$


#### Схема Кули-Тьюки

Обычно, алгоритмы «разделяй-и-властвуй» делят задачу на две половины: на первые $\frac{n}{2}$ элементов и вторые $\frac{n}{2}$ элементов. Здесь мы поступим по-другому: поделим все элементы на чётные и нечётные.

Представим многочлен в виде $P(x)=A(x^2)+xB(x^2)$, где $A(x)$ состоит из  коэффициентов при чётных степенях $x$, а $B(x)$ — из коэффициентов при нечётных.

Пусть $n = 2k$. Тогда 
$$
w^{2t}=w^{2t \bmod 2k}=w^{2(t \bmod k)}
$$

Ключевое замечание: корней вида $w^{2t}$ в два раза меньше, потому что $w^n = w^0$, и можно сказать, что.

Сам алгоритм заключается в следующем: рекурсивно считаем БПФ для многочленов $A$ и $B$ и объединим ответы с помощью формулы выше. При этом в рекурсии считаем значения на корнях степени не $n$, а $k = \frac{n}{2}$, то есть на всех «чётных» корнях степени $n$ (вида $w^{2t}$).

Таким образом, преобразование размера $n$ свели к двум преобразованиям размера $\dfrac n 2$. 
Общее время вычислений составит

$$
T(n)=2T\left(\dfrac n 2\right)+O(n)=O(n\log n)
$$

#### Реализация

```c++

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

vector<ftype> evaluate(vector<int> p) {
    while(__builtin_popcount(p.size()) != 1)
        p.push_back(0);
    return fft(p, polar(1., 2 * pi / p.size()));
}
```

Обратное преобразование Фурье удобно выразить через прямое:

``` c++
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
```

Источник [<a href="https://ru.wikibrief.org/wiki/Cooley%E2%80%93Tukey_FFT_algorithm" target="_blank">15</a>]

### 3.5 Длинное деление 
Начнем делить со старших разрядов. Нам нужно уменьшить текущее значение делимого на максимально возможное число делимым. Это максимальное значение будем искать бинарным поиском. Но сначала нам нужно определить функцию «сдвига» числа вправо, которая позволит нам перебирать разряды последовательно:
```c++
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
```
Опишем само деление 

```c++
big_integer division (big_integer &first_operand, big_integer &second_operand)
{
    big_integer res;
    big_integer curent;
    res.numbers.resize(first_operand.numbers.size());

    for (int i = first_operand.numbers.size() - 1; i >= 0; i--) {

        shift_right(curent.numbers);
        curent.numbers[0] = first_operand.numbers[i];
        remove_leading_zeros(curent.numbers);
        int x = 0;
        int l = 0, r = BASE;
        while (l <= r) {
            int m = (l + r) / 2;
            big_integer cur = second_operand * m;
            curr.numbers = cur;
            if (curr <= curent) {
                x = m;
                l = m + 1;
            }
            else {
                r = m - 1;
            }
        }
        res.numbers[i] = x;
        curent = curent - second_operand * x;

    }

    return res;
}
```
Источник [<a href="https://russianblogs.com/article/6737570753/" target="_blank">24</a>]


## 4 Реализация
Реализована структура 
```c++
struct big_integer{

}
```

Реализованы методы
```c++
    C++
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

```
Также вспомогательные методы
```c++
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
```

## 5 Тестирование

Тесты состоят из двух частей:

1) Тесты проверяющие на корректность операций длинной арифметики
2) Тесты проверяющие эффективность операций длинной арифметики
Для генерирования длинных чисел используюется функция random(seed) в ЯП "python"
Для проверки правильности ответов используется средства длинной арифметики в ЯП "python"





###### Анализ операции сложение
<div>
    <div style="display: flex; justify-content: center">
        <img  src="Images\add.png"/>
    </div>
    <p style="font-style: italic; text-align: center">Рисунок 1. График работы операции сложения</p>
</div>
Эксперментальное время линейное  - соответствует теоретической оценке O(n) 

###### Анализ операции вычитание
<div>
    <div style="display: flex; justify-content: center">
        <img  src="Images\sub.png"/>
    </div>
    <p style="font-style: italic; text-align: center">Рисунок 2. График работы операции вычитания</p>
</div>

Эксперментальное время линейное  - соответствует теоретической оценке O(n) 

###### Алогоритм Кули-Тьюки
<div>
    <div style="display: flex; justify-content: center">
        <img  src="Images\fft.png"/>
    </div>
    <p style="font-style: italic; text-align: center">Рисунок 3. График работы алгоритма Кули-Тьюки</p>
</div>

###### Базовое умножение
<div>
    <div style="display: flex; justify-content: center">
        <img  src="Images\basic.png"/>
    </div>
    <p style="font-style: italic; text-align: center">Рисунок 4. График работы базового умножения</p>
</div>

На основе 3 и 4 рисунков результат работы - алгоритм Кули-Тьюки опережает базовое умножение и соответствует теоретической оценке O(nlon(n)) 


# Заключение
В результате проведённой работы удалось:

- Изучить материалы по методам эффективной длинной арифметики
- Выбрать методы для каждой из операций длинной арифметики и реализовать на языках  С++ и Python
- Выполнить иследование выбранных методов на производительность

# Список литературы
---
1. https://habr.com/ru/post/124258
2.	https://ru.wikipedia.org/wiki/%D0%94%D0%BB%D0%B8%D0%BD%D0%BD%D0%B0%D1%8F_%D0%B0%D1%80%D0%B8%D1%84%D0%BC%D0%B5%D1%82%D0%B8%D0%BA%D0%B0#%D0%91%D0%B0%D0%B7%D0%BE%D0%B2%D1%8B%D0%B9
3.	https://cyberleninka.ru/article/n/dlinnaya-arifmetika-v-issledovaniyaah-statistiki-pervyh-tsifr-stepeney-dvoyki-chisel-fibonachchi-i-prostyh-chisel
4.	https://forany.xyz/a-836
5.	https://habr.com/ru/post/207754/
6.	https://habr.com/ru/post/113642/
7.	https://algorithmica.org/ru/fft
8.	https://parallel.ru/fpga/fft
9.	https://ru.wikipedia.org/wiki/%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%B4%D0%B5%D0%BB%D0%B5%D0%BD%D0%B8%D1%8F
10.	https://habr.com/ru/post/113642/
11.	https://um-nik.github.io/fft
12.	http://cppstudio.com/post/5036/
13.	https://ru.wikipedia.org/wiki/%D0%94%D0%B5%D0%BB%D0%B5%D0%BD%D0%B8%D0%B5_%D0%BC%D0%BD%D0%BE%D0%B3%D0%BE%D1%87%D0%BB%D0%B5%D0%BD%D0%BE%D0%B2
14.	https://algowiki-project.org/ru/%D0%9F%D1%80%D0%BE%D1%81%D1%82%D0%BE%D0%B9_%D0%B0%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%9A%D1%83%D0%BB%D0%B8-%D0%A2%D1%8C%D1%8E%D0%BA%D0%B8_%D0%B1%D1%8B%D1%81%D1%82%D1%80%D0%BE%D0%B3%D0%BE_%D0%BF%D1%80%D0%B5%D0%BE%D0%B1%D1%80%D0%B0%D0%B7%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D1%8F_%D0%A4%D1%83%D1%80%D1%8C%D0%B5_%D0%B4%D0%BB%D1%8F_%D1%81%D1%82%D0%B5%D0%BF%D0%B5%D0%BD%D0%B5%D0%B9_%D0%B4%D0%B2%D0%BE%D0%B9%D0%BA%D0%B8
15.	http://www.ict.nsc.ru/jct/getfile.php?id=1853
16.	https://kaf401.rloc.ru/DSP/FFTalg.pdf
17.	https://ru.wikibrief.org/wiki/Cooley%E2%80%93Tukey_FFT_algorithm
18.	https://ru.algorithmica.org/cs/numerical/newton/
19.	https://en.wikipedia.org/wiki/Cooley%E2%80%93Tukey_FFT_algorithm
20.	https://russianblogs.com/article/71671149759/
21.	https://ru.wikipedia.org/wiki/%D0%94%D0%B8%D1%81%D0%BA%D1%80%D0%B5%D1%82%D0%BD%D0%BE%D0%B5_%D0%BF%D1%80%D0%B5%D0%BE%D0%B1%D1%80%D0%B0%D0%B7%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D0%B5_%D0%A4%D1%83%D1%80%D1%8C%D0%B5
22.	https://ru.dsplib.org/content/dft/dft.html
23.	https://www.math.spbu.ru/ru/mmeh/AspDok/pub/2008/prosekov.pdfhttps://ru.wikipedia.org/wiki/%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%A4%D1%8E%D1%80%D0%B5%D1%80%D0%B0#:~:text=F%C3%BCrer's%20algorithm%20%E2%80%94%20%D0%B1%D1%8B%D1%81%D1%82%D1%80%D1%8B%D0%B9%20%D0%BC%D0%B5%D1%82%D0%BE%D0%B4%20%D1%83%D0%BC%D0%BD%D0%BE%D0%B6%D0%B5%D0%BD%D0%B8%D1%8F,%D0%A8%D1%82%D1%80%D0%B0%D1%81%D1%81%D0%B5%D0%BD%D0%B0%2C%20%D0%BE%D0%BF%D1%83%D0%B1%D0%BB%D0%B8%D0%BA%D0%BE%D0%B2%D0%B0%D0%BD%D0%BD%D1%8B%D0%B9%20%D0%B2%201971%20%D0%B3%D0%BE%D0%B4%D1%83.
24.	http://omega.sp.susu.ru/books/conference/PaVT2011/short/015.pdf
25.	https://russianblogs.com/article/6737570753/
26.	https://ru.wikipedia.org/wiki/%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%B4%D0%B5%D0%BB%D0%B5%D0%BD%D0%B8%D1%8F#%D0%94%D0%B5%D0%BB%D0%B5%D0%BD%D0%B8%D0%B5_%D0%BF%D1%83%D1%82%D1%91%D0%BC_%D0%B2%D1%8B%D1%87%D0%B8%D1%82%D0%B0%D0%BD%D0%B8%D0%B9
27.	https://intellect.icu/dlinnaya-arifmetika-s-primerami-na-si-8291
