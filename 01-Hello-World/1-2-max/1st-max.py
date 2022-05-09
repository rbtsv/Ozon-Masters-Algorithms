import sys
input = sys.stdin.buffer.readline


def read_int():
    return int(input())


n = read_int()
m = read_int()

for _ in range(n-1):
    m = max(m, read_int())

print(m)
