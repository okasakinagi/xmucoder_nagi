def C(m: int, n: int):
    fenzi, fengmu = 1, 1
    for i in range(n, n - m, -1):
        fenzi *= i
    for i in range(1, m + 1, 1):
        fengmu *= i
    return fenzi / fengmu


m, n = map(int, input().split(" "))
print(int(C(n - 1, m + n - 2)))
