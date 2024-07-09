judge = input()
M = []
for i in range(12):
    s = list(map(float, input().split(" ")))
    M.append(s)
sum = 0.0
for i in range(1, 12):
    for j in range(0, i):
        sum += float(M[j][i])
if judge == "M":
    print("%.1f" % (sum / 66.0))
elif judge == "S":
    print("%.1f" % sum)
else:
    pass
