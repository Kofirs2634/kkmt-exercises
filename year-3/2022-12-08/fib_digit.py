def fib_digit(n):
    if n == 0: return 0
    if n == 1: return 1
    prev = 1
    cur = 1
    for _ in range(2, n):
        _t = cur
        cur = (cur + prev) % 10
        prev = _t
    return cur

n = int(input())
print(fib_digit(n))
