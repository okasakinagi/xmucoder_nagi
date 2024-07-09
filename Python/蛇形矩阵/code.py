n, m = map(int, input().split(" "))
# n, m = 3, 3
out = []
for i in range(n):
    out.append([])
    for j in range(m):
        out[i].append(0)
a = 1
n_copy, m_copy = n - 1, m - 1
n_zero, m_zero = 0, -1
i, j = n_zero, m_zero
while a <= n * m:
    if i == n_zero:
        if j == m_zero:
            m_zero += 1
            for j in range(m_zero, m_copy + 1):
                out[i][j] = a
                a += 1
            continue
        elif j == m_copy:
            n_zero += 1
            for i in range(n_zero, n_copy + 1):
                out[i][j] = a
                a += 1
            continue
    elif i == n_copy:
        if j == m_copy:
            m_copy -= 1
            for j in range(m_copy, m_zero - 1, -1):
                out[i][j] = a
                a += 1
            continue
        elif j == m_zero:
            n_copy -= 1
            for i in range(n_copy, n_zero - 1, -1):
                out[i][j] = a
                a += 1
            continue
for i in range(n):
    for j in range(m - 1):
        print(out[i][j], end=" ")
    print(out[i][m - 1])
