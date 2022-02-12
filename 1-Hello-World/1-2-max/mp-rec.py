import sys
input = sys.stdin.buffer.readline


def read_int():
    return int(input())


def max12(n, m1, m2):
    if n == 0:
        return m1, m2
    c = read_int()
    if c > m1:
        return max12(n-1, c, m1)
    return max12(n-1, m1, max(c, m2))

n = read_int()
m1, m2 = read_int(), read_int()
m1, m2 = max12(n-2, max(m1, m2), min(m1, m2))

print(m1*m2)
