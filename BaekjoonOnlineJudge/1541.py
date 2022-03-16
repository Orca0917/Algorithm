expression = list(input())

answer = 0
oper = 1
number_str = '0'

# minus 뒤에 나오는 수는 모두 빼는 것으로 생각해도 좋다.

for token in expression:
    
    if token.isdigit():
        number_str += token
    else:
        answer += oper * int(number_str)
        number_str = '0'
        
        # minus !
        if token == '-':
            oper = -1

# for last number    
answer += oper * int(number_str)

print (answer)