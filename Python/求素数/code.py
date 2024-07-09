def prime(a: int):
    for i in range(2, int(a**0.5) + 1):
        if a % i == 0:
            return False
    return True


N = int(input())
for i in range(2, N + 1):
    if prime(i):
        print(i, end=" ")
