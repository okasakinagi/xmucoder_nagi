def paixu(time: int, n: int, memory: list):
    if n == time:

        pr(memory, n)
    else:
        for i in range(1, n + 1):
            memory[time] = i
            paixu(time + 1, n, memory)


def pr(memory: list, n: int):
    for i in range(1, n + 1):
        if memory.count(i) >= 2:
            return
    for i in range(n - 1):
        print(memory[i], end=" ")
    print(memory[n - 1])


n = int(input())
memory = []
for i in range(n):
    memory.append(0)
paixu(0, n, memory)
