def gcd(a, b):
    while a != 0 and b != 0:
        if a > b: a %= b
        else: b %= a
    return a + b

a, b = map(int, input().split())
print(gcd(a, b))
