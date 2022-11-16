
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

[*1.3 Неформальная постановка задачи*](#13-неформальная-постановка-задачи)

[*1.4 Обзор существующих методов*](#14-обзор-существующих-методов)

[*2 Требование к окружению*](#2-требование-к-окружению)

[*2.1 Требование к аппаратному обеспечению*](#21-требование-к-аппаратному-обеспечению)

[*2.2 Требование к программному обспечению*](#22-требование-к-программному-обспечению)

[*2.3 Требование к пользователям*](#23-требование-к-пользователям)

[*3. Формальное описание алгоритма*](#3-формальное-описание-алгоритма)

[*3.1 Длинная арифметика*](#31-длинная-арифметика)

[*4. Реализация проект*](#31-длинная-арифметика)

[*4.1 Сложение длинных чисел*](#41-сложение-длинных-чисел)

[*4.2 Вычитание длинных чисел*](#42-вычитание-длинных-чисел)

[*4.3 Умножение длинных чисел (базовый метод)*](#43-умножение-длинных-чисел-базовый-метод)

[*4.4 Умножение длинных чисел (Алгоритм Карацубы)*](#44-умножение-длинных-чисел-алгоритм-карацубы)

[*4.5 Умножение длинных чисел (Быстрое и Дискретное преобразование фурье, Алгоритм Кули-Тьюки)*](#45-умножение-длинных-чисел-быстрое-и-дискретное-преобразование-фурье-алгоритм-кули-тьюки)

[*Список литературы*](#список-литературы)

# Аннотация
В данном докладе рассматривается алгоритмы для быстрой длинной арифметики.

# 1. Введение

Решая задачи, многим из нас приходилось сталкиваться с тем, что нам просто не хватало размерностей типов для, казалось, простейших операций: сложение, вычитание и умножение. Все эти операции знакомы Вам с ранних классов. Но что делать, если одну из этих операций необходимо применить для огромных чисел, скажем так 1000 знаков или более… (насколько хватит фантазии!).
## 1.1 Применение

-  Составление кода для процессоров (микроконтроллеров) низкой разрядности. Например, микроконтроллеры серии AVR имеют АЦП с разрядностью 10 бит и регистры с разрядностью 8 бит. Этого недостаточно для обработки информации с АЦП; без длинной арифметики не обойтись;
-  Криптография. Большинство систем подписывания и шифрования данных используют целочисленную арифметику по модулю m, где m — очень большое натуральное число, не обязательно простое. Например, при реализации метода шифрования RSA, криптосистемы Рабина или схемы Эль-Гамаля требуется обеспечить точность результатов умножения и возведения в степень порядка $10^{309}$.
-  Математическое и финансовое ПО. Результат вычисления на бумаге должен совпадать с результатом работы компьютера с точностью до последнего разряда. В частности, калькулятор Windows (начиная с Windows 95) проводит четыре арифметических действия с намного большей точностью, чем позволяет процессор x86. Для научных и инженерных расчётов длинная арифметика применяется редко, так как ошибки во входных данных обычно намного больше, чем ошибки округления;
-  Спортивное программирование 

## 1.2 Глоссарий
1. Комплексное число — это выражение вида a + bi, где a, b — действительные числа, а i — так называемая мнимая единица, символ, квадрат которого равен –1, то есть i2 = –1. Число a называется действительной частью, а число b — мнимой частью комплексного числа z = a + bi. Если b = 0, то вместо a + 0i пишут просто a. Видно, что действительные числа — это частный случай комплексных чисел.
2. Мотивировка – рациональное объяснение субъектом причин действия посредством указания на социально приемлемые для него и его референтной группы обстоятельства, побудившие к выбору данного действия.

## 1.3  Неформальная постановка задачи
Необоходимо эффективно реализовать стурктуру данных под названием длинная арифметика

## 1.4 Обзор существующих методов

Существуют уже готовые алгоритмы длинной арифметики
- Библиотека "gmpxx.h" для gcc
- https://brestprog.by/topics/longarithmetics/

# 2. Требование к окружению


## 2.1 Требование к аппаратному обеспечению

- Персональный компьютер

## 2.2 Требование к программному обспечению

- Тестирующая система CATS
- Любой компилятор C++ (gcc)
- Git

## 2.3 Требование к пользователям

- Умение работать с командной строкой
- Умение пользоваться компилятором 

# 3. Формальное описание алгоритма

## 3.1 Длинная арифметика
---
Длинная арифметика — это набор программных средств (структуры данных и алгоритмы), которые позволяют работать с числами гораздо больших величин, чем это позволяют стандартные типы данных.
Цифры могут использоваться из той или иной системы счисления, обычно применяются десятичная система счисления и ее степени (десять тысяч, миллиард), либо двоичная система счисления.
Операции над числами в этом виде длинной арифметики производятся с помощью "школьных" алгоритмов сложения, вычитания, умножения, деления столбиком. Впрочем, к ним также применимы алгоритмы быстрого умножения: Быстрое преобразование Фурье и Алгоритм Карацубы.

Прежде всего необходимо понимать, что бесконечно длинное число можно представить только в виде динамического массива, что нам и предстоит сделать. Но даже, если числа представлять в виде динамических массивов, некоторые ограничения будут накладываться все равно. Например, длинна такого числа будет ограничена объемом памяти компьютера. Также следует понимать, что при использовании операций сложения и умножения, результат будет занимать больше места в памяти компьютера, нежели операнды.
Каждую арифметическую операцию рассмотрим отдельно

## 4. Реализация проекта

## 4.1 Сложение длинных чисел
---
Рассмотрим арифметическую операцию сложения, применяемую в длинной арифметике. Алгоритм этого нехитрого арифметического действия, на удивление, простой. Он выглядит так:

``` c++
// определяем длину массива суммы
if (size_a > size_b)
    length = size_a + 1;
else
    length = size_b + 1;
 
for (int ix = 0; ix < length; ix++)
{
    b[ix] += a[ix]; // суммируем последние разряды чисел
    b[ix + 1] += (b[ix] / 10); // если есть разряд для переноса, переносим его в следующий разряд
    b[ix] %= 10; // если есть разряд для переноса он отсекается
}
 
if (b[length - 1] == 0)
    length--;
```
“Виновники торжества” – то есть числа, которые мы будем складывать, предположительно записаны в массивы a и b. Необходимо учесть, что они записаны “зеркально”, то есть первый элемент массива соответствует последней цифре соответствующего числа, второй элемент – предпоследней, и т. д. Размеры длин чисел хранятся в переменных size_a и size_b, но Вы можете использовать любые другие. Вы конечно же задумались: “Зачем здесь оператор выбора if, строки 2–5?” или “Для чего он здесь?”. В этом блоке кода мы определяем максимальную длину числа, полученного в результате суммирования. Ведь, чаще всего суммируемые числа, разной длинны, одно больше, другое меньше, а нам нужно выделить память так, чтобы каждое число вместилось.
Далее, в алгоритме, делаем так, как нас учили на уроках математики: сначала складываем отдельные разряды, начиная с конца, строка 9; делим получившуюся сумму на 10 и получаем целую часть от деления на десять, которую мы сразу прибавляем к следующему разряду, строка 10.  В строке 11, мы отсекаем первый разряд полученного числа, если, конечно, он есть.
Вот и все. Главное не забыть, что число будет храниться в массиве b и выводить его следует с конца.

## 4.2 Вычитание длинных чисел
---
Вторая, наиболее используемая арифметическая операция – это вычитание. И эта часть статьи поможет Вам научиться писать алгоритмы вычитания больших и огромных чисел. 
Будем считать, что наши числа хранятся в массивах a и b, m и n – длинны этих чисел соответственно. Следует учесть, что числа записаны “зеркально”(см. выше). Конечно, если мы знаем какое число больше, то задача упрощается. Но мы можем и не знать этого. Тогда нам следует сперва найти, какое из чисел больше. Это нам понадобится для определения знака получившегося числа, то есть, если первое число меньше второго, то в ответе появится минус. И так, приступим к написанию первой части алгоритма, то есть определению большего числа. Алгоритм выглядит так:

``` c++
int k = 3; // если к == 3, значит числа одинаковой длинны
length = size_a;
if (size_a > size_b)
{
    length = size_a;
    k = 1; // если к == 1, значит первое число длиннее второго
}
else
    if (size_b > size_a)
    {
        length = size_b;
        k = 2; // если к == 2, значит второе число длиннее первого
    }
    else // если числа одинаковой длинны, то необходимо сравнить их веса
        for (int ix = 0; ix < length;) // поразрядное сравнение весов чисел
        {
            if (a[ix] > b[ix]) // если разряд первого числа больше
            {
                k = 1; // значит первое число длиннее второго
                break; // выход из цикла for
            }
 
            if(b[ix] > a[ix]) // если разряд второго числа больше
            {
                k = 2; // значит второе число длиннее первого
                break; // выход из цикла for
            }
        } // конец for
```

Сначала Вы можете увидеть, что переменной k придается значение 3. В данной части алгоритма переменная k является флагом результата проверки. Если числа равны, то k останется равно 3, если первое больше второго, то k примет значение 1, если второе больше первого, то k примет значение 2. Переменная length примет значение длинны большего числа. Теперь перейдем к обоснованию работоспособности этого алгоритма. Сравнение чисел происходит в два этапа. Сначала мы сравниваем длинны чисел: какое число длиннее, то и больше, строки 1 — 11. Если числа одинаковой длинны, то переходим к по разрядовому сравнению, строки 13 — 26. Начинаем по порядку сравнивать разряды начиная с самого старшего, так мы определим, больший вес числа. В этом и заключается суть и сложность первой части. Теперь перейдем ко второй части алгоритма — вычитание. Она выглядит так:

``` c++

int difference (int *x, int *y, int *z, int length)
{
    for (int ix = 0; ix < (length - 1); ix++) // проход по всем разрядам числа, начиная с последнего, не доходя до первого
    {
        if (ix < (length - 1)) // если текущий разряд чисел не первый
        {
            x[ix + 1]--; // в следующуем разряде большего числа занимаем 1.
            z[ix] += 10 + x[ix]; // в ответ записываем сумму значения текущего разряда большего числа и 10-ти
 
        } else  // если текущий разряд чисел - первый
                z[ix] += x[ix]; // в ответ суммируем значение текущего разряда большего числа
 
        z[ix] -= y[ix]; // вычитаем значение текущего разряда меньшего числа
 
        if (z[ix] / 10 > 0) // если значение в текущем разряде двухразрядное
        {
            z[ix + 1]++; // переносим единицу в старший разряд
            z[ix] %= 10; // в текущем разряде отсекаем ее
        }
    }
    return 0;
}
``` 
Для самого вычитания удобно написать функцию, ведь нам тогда не придется писать два алгоритма для двух случаев: когда первое число больше второго, и наоборот. В массиве x мы содержим большее число, в массиве y – меньшее, в массиве z – результат. Алгоритм довольно простой: для каждого разряда мы добавляем 10, с учетом вычитания из старшего разряда — 1. Это делается для упрощения вычитания разрядов. Эта операция делается лишь в том случае, когда рассматриваемый разряд не является последним в массиве (первым в числе). После вычитания разрядов мы проверяем получившееся число в данном разряде в массиве z. Ответ запишется в массив z, причем “зеркальным” (см. выше) способом. Процедуру следует вызывать следующим образом:

``` c++
if (k == 1) difference(a,b,c, length); - если первое число больше второго,
if (k == 2) difference(b,a,c, length); - если второе число больше первого.
``` 

Теперь ответ будет храниться в массиве c все в том же “зеркальном” порядке. Вот мы и научились вычитать большие числа.

## 4.3 Умножение длинных чисел (базовый метод)
---
``` c++
length = size_a + size_b + 1;
 
for (int ix = 0; ix < size_a; ix++)
    for (int jx = 0; jx < size_b; jx++)
        c[ix + jx - 1] += a[ix] * b[jx];
 
for (int ix = 0; ix < length; ix++)
{
    c[ix + 1] +=  c[ix] / 10;
    c[ix] %= 10;
}
 
while (c[length] == 0)
    length-- ;

``` 

Вот так выглядит алгоритм задачи. Теперь попробуем “это” разобрать, точнее разобраться, как это работает. Сначала у нас имелось два числа в массивах a и b все в том же “зеркальном” виде. Длинны чисел хранятся в переменных size_a и size_b. В переменной length хранится длинна результирующего числа. Она будет равна либо сумме длин первоначальных чисел, либо этой сумме увеличенной на единицу. Но так, как мы не знаем точной длинны полученного числа, то возьмем длину побольше, то есть второй вариант. Теперь после этих не хитрых подсчетов, приступим к перемножению чисел. Будем их перемножать так, как нас учили в школе. Для этого запускаем два цикла: один до size_a, другой до size_b. После этих циклов вы можете увидеть еще один до length. благодаря ему в записи числа в массиве, в каждой ячейке массива мы получаем по одной цифре полученного числа. Последний цикл нужен, что бы узнать точную длину полученного числа, ведь предположенная нами длина числа может быть больше действительной. Ответ будет храниться в массиве c, все в том же “зеркальном” виде.

## 4.4 Умножение длинных чисел (Алгоритм Карацубы)
---
### История алгоритма

В 1960 году Андрей Колмогоров проводил семинар, посвящённый математическим задачам кибернетики. Одной из рассматриваемых на семинаре задач стало умножение двух {n}-разрядных целых чисел. Основным известным методом умножения в то время было умножение «в столбик», которое при алгоритмической реализации требовало O( $n^{2}$ ) элементарных операций (сложений или умножений одноразрядных чисел). Колмогоров выдвинул гипотезу, что умножение «в столбик» является оптимальным алгоритмом умножения двух чисел в том смысле, что время работы любого метода умножения не меньше $n^{2}$ по порядку величины. На правдоподобность «гипотезы $n^{2}$» указывало то, что метод умножения «в столбик» известен не менее четырёх тысячелетий, и если бы был более быстрый метод умножения, то он, вероятно, уже был бы найден. Однако, через неделю 23-летний Анатолий Карацуба предложил новый метод умножения двух n-значных чисел с оценкой времени работы O( $n^{log_2⁡^3}$ ) и тем самым опроверг «гипотезу  $n^{2}$».
Метод Карацубы относится к алгоритмам вида «разделяй и властвуй», наравне с такими алгоритмами как двоичный поиск, быстрая сортировка и др. Формулы рекурсивного сведения, используемые в методе Карацубы, были известны ещё Чарльзу Бэббиджу, который, однако, не обратил внимания на возможность использования лишь трёх рекурсивных умножений вместо четырёх.

### Описание алгоритма

##### a) разбиваем числа по середине
##### b) перемножаем левые части первого и второго
##### c) перемножаем правые части части первого и второго
##### d) складываем левую и правую часть первого числа (также поступаем со вторым числом)
##### e) перемножаем эти суммы
##### f) считаем e – b – c
##### g) собираем итоговую сумму из b, c и f


<p align="center"><img src="Images\karazuba.png"></p>

Мы его брать не будем, так как он недостачно быстрый

## 4.5 Умножение длинных чисел (Быстрое и Дискретное преобразование фурье, Алгоритм Кули-Тьюки)
---
### История алгоритма

Алгоритм и его рекурсивная реализация были изобретены около 1805 года К. Гауссом при интерполировании траекторий астероидов Паллада и Юнона. Тогда открытие не получило широкого распространения и было опубликовано лишь после смерти учёного на новой латыни. Результат Гаусса несколько раз переоткрывался в различных формах в течение последующих 150 лет и стал популярным после публикации в 1965 году статьи Дж. Кули  (англ.)рус. из IBM и Дж. Тьюки из Принстона, в которой алгоритм был в очередной раз переоткрыт, а также описывалась удобная реализация для ЭВМ. 
Тот факт, что первооткрывателем алгоритма является Гаусс, был обнаружен лишь через несколько лет после публикации Кули и Тьюки. В своей статье они ссылались только на работу И. Дж. Гуда, в которой был описан алгоритм Гуда — Томаса. 

### Мотивировка

Основная задача, которая решается при помощи быстрого преобразования Фурье (Fast Fourier Transform, FFT) — это умножение многочленов за время O(nlogn) .

Как известно, многочлен степени строго меньше  однозначно определяется своими значениями в  (вообще говоря комплексных) точках. Действительно, если есть два различных многочлена с одинаковыми значениями в  точках, то их разность имеет  комплексных корней, причём она является ненулевым многочленом степени строго меньше , что противоречит основной теореме алгебры. С другой стороны, интерполяционный многочлен Лагранжа в явном виде предъявляет многочлен степени строго меньше  по значениям в  точках.

Таким образом, многочлены можно хранить не в виде вектора коэффициентов, а в виде набора значений в некоторых точках. Над многочленами в таком виде очень удобно производить арифметические операции, в том числе умножать их за время  (нужно просто перемножить значения в соответствующих точках). С другой стороны, непонятно, как считать значения в других точках, да и знать сами коэффициенты бывает полезно. А воостанавливать коэффициенты по значениям в некотором наборе точек сложно, тот же интерполяционный многочлен Лагранжа вычисляется за время . Да и многочлены нам обычно задаются в форме вектора коэффициентов, получить значеня в  произвольных точках вряд ли можно быстрее, чем за .

Хитрость FFT в том, что точки, в которых считаются значения многочлена, выбираются отнюдь не произвольным образом


### Интерполяция

**Теорема.** Пусть есть набор различных точек $x_0, x_1, \dots, x_{n}$. Многочлен степени $n$ однозначно задаётся своими значениями в этих точках. (Коэффициентов у этого многочлена столько же, сколько и точек — прим. К. О.)

**Доказательство** будет конструктивным — можно явным образом задать многочлен, который принимает заданные значения $y_0, y_1, \ldots, y_n$ в этих точках:

$$
y(x)=\sum\limits_{i=0}^{n}y_i\prod\limits_{j\neq i}\dfrac{x-x_j}{x_i-x_j}
$$

**Корректность.** Проверим, что в точке $x_i$ значение действительно будет равно $y$:

1. Для $i$-го слагаемого внутреннее произведение будет равно единице, если вместо $x$ подставить $x_i$: в этом случае просто перемножается $(n-1)$ единица. Эта единица помножится на $y_i$ и войдёт в сумму.

2. Для всех остальных слагаемых произведение занулится: один из множетелей будет равен $(x_i - x_i)$.

**Уникальность.** Предположим, есть два подходящих многочлена степени $n$ — $A(x)$ и $B(x)$. Рассмотрим их разность. В точках $x_i$ значение получившегося многочлена $A(x) - B(x)$ будет равняться нулю. Если так, то точки $x_i$ должны являться его корнями, и тогда разность можно записать так:

$$
A(x) - B(x) = \alpha \prod_{i=0}^n (x-x_i)
$$

для какого-то числа $\alpha$. Тут мы получаем противоречие: если раскрыть это произведение, то получится многочлен степени $n+1$, который нельзя получить разностью двух многочленов степени $n$.

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

**Основная идея алгоритма:** если мы знаем значения в каких-то различных $n + m$ точках для обоих многочленов $A$ и $B$, то, попарно перемножив их, мы за $O(n + m)$ операций можем получить значения в тех же точках для многочлена $A(x) B(x)$ — а с их помощью можно интерполяцией получить исходный многочлен и решить задачу.

``` c++
vector<int> poly_multiply(vector<int> a, vector<int> b) {
    vector<int> A = evaluate(a);
    vector<int> B = evaluate(b);
    for (int i = 0; i < A.size(); i++)
        A[i] *= B[i];
    return interpolate(A);
}
```

Если притвориться, что `evaluate` и `interpolate` работают за линейное время, то умножение тоже будет работать за линейное время.

К сожалению, непосредственное вычисление значений требует $O(n^2)$
операций, а интерполяция — как методом Гаусса, так и через символьное вычисление многочлена Лагранжа — и того больше, $O(n^3)$.

Но что, если бы мы могли вычислять значения в точках и делать интерполяцию быстрее?

## Комплексные числа

**Определение.** Комплексные числа — это числа вида $a + bi$, где $a$ и $b$ это обычные вещественные числа, а $i$ это так называемая мнимая единица: это число, для которого выполняется равенство $i^2 = -1$.

Комплексные числа ввели в алгебре, чтобы работать с корнями из отрицательных чисел: $i$ в каком-то смысле равно $\sqrt{-1}$. Так же, как и отрицательные числа, они как бы «не существуют» в реальном мире, а только в сознании математиков.

С комплексными числами можно работать почти так же, как с действительными. Они даже удобнее: все квадратные корни всегда извлекаются.

### Комплексная плоскость

Комплексные числа удобно изображать на плоскости в виде вектора $(a, b)$ и считать через них всякую геометрию.

<p align="center"><img src="Images\Complex_vector.png"></p>

**Модулем** комплексного числа называется действительное число $r = \sqrt{a^2 + b^2}$ . Геометрически, это длина вектора $(a, b)$.

**Аргументом** комплексного числа называется действительное число $\phi \in (-\pi, \pi]$, для которого выполнено $\tan \phi = \frac{b}{a}$. Геометрически, это значение угла между $(a, 0)$ и $(a, b)$. Для нуля — вектора $(0, 0)$ — аргумент не определён.

Таким образом комплексное число можно представить в полярных координатах: 

$$
a+bi = r ( \cos \phi + i \sin \phi )
$$

Подобное представление удобно по следующей причине: чтобы перемножить два комплексных числа, нужно перемножить их модули и сложить аргументы.

**Упражнение.** Докажите это.

### Формула эйлера

**Определим** число Эйлера $e$ как число со следующим свойством:

$$
e^{i\phi} = \cos \phi + i \sin \phi
$$

Просто введём такую нотацию для выражения $\cos \phi + i \sin \phi$. Не надо думать, почему это так.

Геометрически, все такие точки живут на единичном круге:

<p align="center"><img src="Images\roots_unity.png"></p>

Такая нотация удобна, потому что можно обращаться с $e^{i\phi}$ как с обычной экспонентой. Пусть мы, например, хотим перемножить два числа на единичном круге с аргументами $a$ и $b$. Тогда это можно записать так:

$$
(\cos a + i \sin a) \cdot (\cos b + i \sin b) = e^{i (a+b)}
$$

**Упражнение.** Проверьте это: раскройте скобки и проделайте немного алгебры.

### Корни из единицы

У комплексных чисел есть много других замечательных свойств, но нам для алгоритма на самом деле потребуется только следующее:

**Утверждение.** Для любого натурального $n$ есть ровно $n$ комплексных «корней из единицы», то есть чисел $w_k$, для которых выполнено:

$$
w_k^n = 1
$$

А именно, это будут числа вида:

$$
w_k = e^{i \tau \frac{k}{n}}
$$

где $\tau$ обозначает $2 \pi$, «целый круг». 

На комплексной плоскости эти числа располагаются на единичном круге на равном расстоянии друг от друга:

<p align="center"><img src="Images\roots_unity.png"></p>

Первый корень $w_1$ (точнее второй — единицу считаем нулевым корнем) называют *образующим корнем* степени $n$ из единицы. Возведение его в нулевую, первую, вторую и так далее степени порождает последовательность нужных корней единицы, при этом на $n$-ном элементе последовательность зацикливается:

$$
w_n = e^{i \tau \frac{n}{n}} = e^{i \tau} = e^{i \cdot 0} = w_0 = 1
$$

Будем обозначать $w_1$ как просто $w$.

**Упражнение.** Докажите, что других корней быть не может.

### Дискретное преобразование Фурье

*Дискретным преобразованием Фурье* называется вычисление значений многочлена в комплексных корнях из единицы:

$$
y_j = \sum_{k=0}^{n-1} x_n e^{i\tau \frac{kj}{n}} = \sum_{k=0}^{n-1} x_n w_1^{kj}
$$

*Обратным дискретным преобразованием Фурье* называется, как можно догадаться, обратная операция — интерполяция коэффициентов $x_i$ по значениям $X_i$.

$$
x_j = \frac{1}{n} \sum_{k=0}^{n-1} y_n e^{-i\tau \frac{kj}{n}} = \frac{1}{n} \sum_{k=0}^{n-1} y_n w_{n-1}^{kj}
$$

Почему эта формула верна? При вычислении ПФ мы практически применяем матрицу к вектору:

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

То есть преобразование Фурье — это просто линейная операция над вектором: $W a = y$. Значит, обратное преобразование можно записать так: $a = W^{-1}y$. 

Как будет выглядеть эта $W^{-1}$? Автор не будет пытаться изображать логичный способ рассуждений о её получении и сразу её приведёт:

$$
W^{-1} =
\dfrac 1 n\begin{pmatrix}
w^0 & w^0 & w^0 & w^0 & \dots & w^0 \\
w^0 & w^{-1} & w^{-2} & w^{-3} & \dots & w^{1} \\
w^0 & w^{-2} & w^{-4} & w^{-6} & \dots & w^{2} \\
w^0 & w^{-3} & w^{-6} & w^{-9} & \dots & w^{3} \\
\vdots & \vdots & \vdots & \vdots & \ddots & \vdots \\
w^0 & w^{1} & w^{2} & w^{3} & \dots & w^{-1}
\end{pmatrix}
$$

Проверим, что при перемножении $W$ и $W^{-1}$ действительно получается единичная матрица:

1. Значение $i$-того диагонального элемента будет равно $\frac{1}{n} \sum_k w^{ki} w^{-ki} = \frac{1}{n} n = 1$.

2. Значение любого недиагонального ($i \neq j$) элемента $(i, j)$ будет равно $\frac{1}{n} \sum_k w^{ik} w^{-jk} = \frac{1}{n} \sum_k w^k w^{i-j} = \frac{w^{i-j}}{n} \sum_k w^k = 0$, потому что все комплексные корни суммируются в ноль, то есть $\sum w^k = 0$ (см. картинку — там всё симметрично).

Внимательный читатель заметит симметричность форм $W$ и $W^{-1}$, а также формул для прямого и обратного преобразования. На самом деле, эта симметрия нам сильно упростит жизнь: для обратного преобразования Фурье можно использовать тот же алгоритм, только вместо $w^k$ использовать $w^{-k}$, а в конце результат поделить на $n$.

#### Зачем это надо?

Напомним, что мы изначально хотели перемножать многочлены следующим алгоритмом:

1. Посчитаем значения в $n+m$ каких-нибудь точках обоих многочленов

2. Перемножим эти значения за $O(n+m)$.

3. Интерполяцией получим многочлен-произведение.

В общем случае быстро посчитать интерполяцию и даже просто посчитать значения в точках нельзя, **но для корней единицы — можно**. Если научиться быстро считать значения в корнях и интерполировать (прямое и обратное преобразование Фурье), но мы можно решить исходную задачу.

Соответствующий алгоритм называется *быстрым преобразованием Фурье* (англ. *fast Fourier transform*). Он использует парадигму «разделяй-и-властвуй» и работает за $O(n \log n)$.

### Схема Кули-Тьюки

Обычно, алгоритмы «разделяй-и-властвуй» делят задачу на две половины: на первые $\frac{n}{2}$ элементов и вторые $\frac{n}{2}$ элементов. Здесь мы поступим по-другому: поделим все элементы на чётные и нечётные.

Представим многочлен в виде $P(x)=A(x^2)+xB(x^2)$, где $A(x)$ состоит из  коэффициентов при чётных степенях $x$, а $B(x)$ — из коэффициентов при нечётных.

Пусть $n = 2k$. Тогда заметим, что

$$
w^{2t}=w^{2t \bmod 2k}=w^{2(t \bmod k)}
$$

Зная это, исходную формулу для значения многочлена в точке $w^t$ можно записать так:

$$
P(w^t)
= A(w^{2t}) + w^t B(w^{2t})
= A\left(w^{2(t\bmod k)}\right)+w^tB\left(w^{2(t\bmod k)}\right)
$$

Ключевое замечание: корней вида $w^{2t}$ в два раза меньше, потому что $w^n = w^0$, и можно сказать, что.

У нас по сути в два раза меньше корней (но они так же равномерно распределены на единичной окружности) и в два раза меньше коэффициентов — мы только что успешно уменьшили нашу задачу в два раз.

Сам алгоритм заключается в следующем: рекурсивно посчитаем БПФ для многочленов $A$ и $B$ и объединим ответы с помощью формулы выше. При этом в рекурсии нам нужно считать значения на корнях степени не $n$, а $k = \frac{n}{2}$, то есть на всех «чётных» корнях степени $n$ (вида $w^{2t}$).

Заметим, что если $w$ это образующий корень степени $n = 2k$ из единицы, то $w^2$ будет образующим корнем степени $k$, то есть в рекурсию мы можем просто передать другое значение образующего корня.

Таким образом, мы свели преобразование размера $n$ к двум преобразованиям размера $\dfrac n 2$. Следовательно, общее время вычислений составит

$$
T(n)=2T\left(\dfrac n 2\right)+O(n)=O(n\log n)
$$

Заметим, что предположение о делимости $n$ на $2$ имело существенную роль. Значит, $n$ должно быть чётным на каждом уровне, кроме последнего, из чего следует, что $n$ должно быть степенью двойки.

### Реализация

```c++
typedef complex<double> ftype;
const double pi = acos(-1);

template<typename T>
vector<ftype> fft(vector<T> p, ftype w) {
    int n = p.size();
    if(n == 1)else { {
        return {p[0]};
    else {
        vector<T> AB[2];
        for(int i = 0; i < n; i++)
            AB[i % 2].push_back(p[i]);
        auto A = fft(AB[0], w * w);
        auto B = fft(AB[1], w * w);
        vector<ftype> res(n);
        ftype wt = 1;
        int k = n / 2;
        for(int i = 0; i < n; i++) {
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

Как обсуждалось выше, обратное преобразование Фурье удобно выразить через прямое:

``` c++
vector<int> interpolate(vector<ftype> p) {
    int n = p.size();
    auto inv = fft(p, polar(1., -2 * pi / n));
    vector<int> res(n);
    for(int i = 0; i < n; i++)
        res[i] = round(real(inv[i]) / n);
    return res;
}
```

Теперь мы умеем перемножать два многочлена за $O(n \log n)$:

```c++
vector<int> poly_multiply(vector<int> a, vector<int> b) {
    vector<int> A = fft(a);
    vector<int> B = fft(b);
    for (int i = 0; i < A.size(); i++)
        A[i] *= B[i];
    return interpolate(A);
}
```



### Тестирование эффективности


| N      | Базовый алгорити | Алгоритм Карацубы | Алгоритм  | Все доступы | Удаление  | Сумма  |
|--------|--------------|---------|--------|-------------|-----------|--------|
| 10     | 7           | 8       | 6      | 6           | 1         | 28     |
| 100    | 14          | 9       | 3      | 51          | 2         | 79     |
| 1000   | 20          | 26      | 5      | 934         | 5         | 990    |
| 10000  | 27          | 29      | 21     | 15980       | 6         | 16063  |
| 100000 | 34          | 32      | 9      | 229088      | 2         | 229165 |


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
