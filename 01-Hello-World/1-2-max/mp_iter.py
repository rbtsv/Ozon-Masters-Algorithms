import sys
input = sys.stdin.buffer.readline


def read_int():
    return int(input())


n = read_int()
m1, m2 = read_int(), read_int()
m1, m2 = max(m1, m2), min(m1, m2)

for _ in range(n-2):
    c = read_int()
    if c > m1:
        m2 = m1
        m1 = c
    else:
        m2 = max(c, m2)

print(m1*m2)
