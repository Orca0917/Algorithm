memo = [[-1] * 2001 for _ in range(2001)]

def dp(n, k):
    if n == k: return 1
    elif n < k: return 0
    
    if memo[n][k] != -1: return memo[n][k]
    
    memo[n][k] = 1 # base
    for i in range(k, n + 1):
        memo[n][k] += dp(n - i, i + 1)
        
    return memo[n][k]


testcase = int(input())

for _ in range(testcase):
    N = int(input())
    result = dp(N, 1)
    print (result % 100999)
  