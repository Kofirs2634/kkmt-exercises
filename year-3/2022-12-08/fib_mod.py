from functools import reduce
from sympy import factorint, lcm
def A001175(n):
    if n == 1:
        return 1
    f = factorint(n)
    if len(f) > 1:
        return reduce(lcm, (A001175(a**f[a]) for a in f))
    else:
        k, x = 1, [1, 1]
        while x != [0, 1]:
            k += 1
            x = [x[1], (x[0]+x[1]) % n]
        return k # Chai Wah Wu, Jul 17 2019

def fib(n, m):
    a = 0
    b = 1
    l = [0]
    while n > 1:
        a, b = b, a + b
        l.append(a % m)
        n -= 1
    return l

def fib_mod(n, m):
    period = A001175(m)
    purged = n % period
    modulo = fib(period, m)
    return modulo[purged]

n, m = map(int, input().split())
print(fib_mod(n, m))
