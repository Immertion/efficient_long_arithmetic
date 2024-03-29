import sys
import random
sys.set_int_max_str_digits(600000)

in_txt = open(r'cmake-build-debug\tests\in.txt', 'r')
ans_txt = open(r'cmake-build-debug\tests\answer.txt', 'w')

tests_logic = 23

for i in range(tests_logic):
    string = in_txt.readline()
    example = string.split()
    ans = eval(f"{example[0]} {example[1]} {example[2]}")
    ans_txt.write(str(ans))
    ans_txt.write("\n")


in_txt.close()
ans_txt.close() 


in_txt = open(r'cmake-build-debug\tests\in2.txt', 'w')

tests_eff = 5

for i in range (tests_eff):
    random.seed(100 + i)
    a = random.randint(1,10**50000)
    in_txt.write(str(a))
    in_txt.write(" + ")
    random.seed(100 + 2*i)
    a = random.randint(1,10**50000)
    in_txt.write(str(a))
    in_txt.write("\n")

for i in range (tests_eff):
    random.seed(10 + i)
    a = random.randint(1,10**50000)
    in_txt.write(str(a))
    in_txt.write(" - ")
    random.seed(10 + 2*i)
    a = random.randint(1,10**50000)
    in_txt.write(str(a))
    in_txt.write("\n")

for i in range (tests_eff):
    random.seed(1000 + i)
    a = random.randint(1,10**30000)
    in_txt.write(str(a))
    in_txt.write(" * ")
    random.seed(1000 + 2*i)
    a = random.randint(1,10**30000)
    in_txt.write(str(a))
    in_txt.write("\n")

for i in range (tests_eff):
    random.seed(10000 + i)
    a = random.randint(1,10**9000)
    in_txt.write(str(a))
    in_txt.write(" // ")
    random.seed(10000 + 2*i)
    a = random.randint(1,10**1000)
    in_txt.write(str(a))
    in_txt.write("\n")

in_txt.close()

in_txt = open(r'cmake-build-debug\tests\in2.txt', 'r')
ans_txt = open(r'cmake-build-debug\tests\answer2.txt', 'w')

for i in range(tests_eff * 4):
    string = in_txt.readline()
    example = string.split()
    ans = eval(f"{example[0]} {example[1]} {example[2]}")
    ans_txt.write(str(ans))
    ans_txt.write("\n")



in_txt.close()
ans_txt.close() 

