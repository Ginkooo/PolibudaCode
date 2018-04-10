nums = {
        1: 'I',
        5: 'V',
        10: 'X',
        50: 'L',
        100: 'C',
        500: 'D',
        1000: 'M'
        }

def find_max_char(n):
    max = 0
    for k, v in nums.items():
        if k > n:
            break
        max = k
    return nums[max]

num = input('Podaj liczbę: ')
num = int(num)
chars = []
while True:
    char = find_max_char(num)
    chars.append(char)
    for k, v in nums.items():
        if v == char:
            num -= k
    if num <= 0:
        break

print(''.join(chars))
