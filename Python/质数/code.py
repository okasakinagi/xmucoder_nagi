def prime(a: int):
    for i in range(2, int(a**0.5) + 1):
        if a % i == 0:
            return False
    return True


N = int(input())
for i in range(N):
    a = int(input())
    if prime(a):
        print(str(a) + " is prime")
    else:
        print(str(a) + " is not prime")
