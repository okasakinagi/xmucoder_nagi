a, b = map(int, input().split(" "))
std = [4.00, 4.50, 5.00, 2.00, 1.50]
print("Total: $ %.2f" % (std[a - 1] * b))
