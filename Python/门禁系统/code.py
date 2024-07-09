n = int(input())
reader = list(map(int, input().split(" ")))
time = []
for i in range(n):
    if i > 0:
        print(" ", end="")
    count = 1
    for j in range(i):
        if reader[j] == reader[i]:
            count += 1
    print(count, end="")
