import sys
from typing import List

input = sys.stdin.readline

n: int = 0
n = map(int, input().rstrip())

answer: List[int] = [0] * n

for i in range(n):
    arr: List[int] = map(int, input().rstrip().split())
    for idx, number in enumerate(arr):
        answer[i] |= number
        answer[idx] |= number

for e in answer:
    print (e, end=' ')

