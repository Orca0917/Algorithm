import math

n = int(input())
q = int(math.sqrt(n))

if q * q == n:
    print (q)
else:
    print (q + 1)

