def fib(n):
    if n == 0: return 0
    if n == 1: return 1
    prev = 1
    cur = 1
    for _ in range(2, n):
        cur += prev
        prev = cur - prev
    return cur

n = int(input())
print(fib(n))
