s = input()
out = []
for i in s:
    if s.count(i) == 1:
        out.append(i)

for i in range(0, len(out) - 1):
    print(out[i], end=" ")
print(out[len(out) - 1])
