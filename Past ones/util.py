def display(arr, start, end):
    while start <= end:
        sign, digit, first_operand, second_operand, third_operand = decode_instruction(
            arr[start])
        print(f"{str_memory(start)}: {sign}{digit} {str_memory(first_operand)} {str_memory(second_operand)} {str_memory(third_operand)}")
        start += 1


def decode_instruction(instruction):

    if instruction >= 0:
        sign = '+'
    else:
        sign = '-'
    instruction = abs(instruction)
    third_operand = int(instruction % 1000)
    second_operand = int((instruction / 1000) % 1000)
    first_operand = int((instruction / 1000000) % 1000)
    digit = int(abs(instruction / 1000000000))
    return sign, digit, first_operand, second_operand, third_operand


def find_index(arrs, index_to_search, target):
    for i, arr in enumerate(arrs):
        if arr[index_to_search] == target:
            return i


def str_memory(index):

    if index < 10:
        return '00'+str(index)
    elif index < 100:
        return '0'+str(index)
    return str(index)
