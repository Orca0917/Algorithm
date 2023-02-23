from typing import List
import sys

num_operation: int = int(sys.stdin.readline())
mask: int = 0

for _ in range(num_operation):
    cmd: List = sys.stdin.readline().split()
    command: str = cmd[0]

    if len(cmd) == 2:
        value: int = int(cmd[1])
    
    if command == "add":
        mask = mask | (1 << value)
    
    elif command == "remove":
        mask = mask & ~(1 << value)

    elif command == "check":
        print (1 if (mask & (1 << value)) else 0)

    elif command == "toggle":
        mask = mask ^ (1 << value)

    elif command == "all":
        mask = (1 << 21) - 1

    elif command == "empty":
        mask = 0
