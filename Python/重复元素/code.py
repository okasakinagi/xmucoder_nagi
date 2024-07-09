s = input().split(" ")
out = []
for i in s:
    if s.count(i) >= 2:
        if out.count(i) == 0:
            out.append(i)
for i in range(0, len(out) - 1):
    print(out[i], end=" ")
print(out[len(out) - 1])
