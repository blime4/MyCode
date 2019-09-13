even_numbers = [x for x in range(5) if x%2 == 0]  # [0, 2, 4]
squares = [x*x for x in range(5)] # [0, 1, 4, 9, 16]
ecen_squares = [x*x for x in even_numbers] # [0, 4, 16]

print(even_numbers,squares,ecen_squares)

square_dict = {x:x for x in range(5)}
square_set = {x*x for x in [1,-1]}

print(square_dict,square_set)

zerores = [0 for _ in even_numbers]

print(zerores)

# 列表解析可以包括多个 for 语句:

pairs = [(x,y) for x in range(10) for y in range(10)]
print(pairs)


increasing_pairs = [(x,y) for x in range(10) for y in range(x+1,10)]
print(increasing_pairs)