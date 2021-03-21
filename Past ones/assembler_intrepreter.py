import math
from util import *

# This list contains the data memory
# for example index data_memory[1] is equal the content of the variable at memory location 001
data_memory = list()

symbol_dict = {"ASG": "+0", "ADD": "+1", "SUB": "-1", "MUL": "+2", "DIV": "-2", "SQR": "+3", "SQT": "-3",
               "EQL": "+4", "NEQ": "-4", "GTE": "+5", "LSS": "-5", "RDA": "+6", "WTA": "-6", "ITJ": "+7",
               "STP": "+9", "INP": "+8", "OUT": "-8"}

# This is a dictionary in which we store the label and its corresponding memory address
label_dict = {'000': '000'}

symbol_table = []

# read the symbolic version of the code from the file and store it an array
file_name = input("please input the name of the file: ")
with open(file_name) as file:
    lines = file.readlines()


ifp = open("output.txt", "w")
cnt = 0
# ---------- fill the data labels in label_dict & and load to data_memory
for i, line in enumerate(lines):
    if line == "\n":
        continue
    elif line == "END-OF-DATA\n":
        ifp.write("+9 999 999 999\n")

        start_c_memory = i+1
        break

    opcode, first_operand, second_operand, third_operand = tuple(
        line.split(sep=" "))
    if opcode == "DEC":
        # name = code line, size
        label_dict[first_operand] = str_memory(cnt)
        symbol_table.append([first_operand, str_memory(cnt), second_operand])

        size = int(second_operand)  # TKHRBI9A
        cnt += 1

    elif opcode == "NOP":
        exit()
    # TO-DO: ask END-OF-DATA or STP.
    elif opcode == "+0":
        ifp.write(line)
        if size != 1:
            data_memory.append([None]*size)
        else:
            data_memory.append(int(third_operand))

# ignore all of the empty lines
while lines[start_c_memory] == "\n":
    start_c_memory += 1

cnt = 0
index = start_c_memory
# --------fill the code labels in label_dict
while True:
    if lines[index] == "\n":
        index += 1
        continue
    opcode, first_operand, second_operand, third_operand = tuple(
        lines[index].split(sep=" "))
    index += 1
    if opcode == "LBL":
        label_dict[first_operand] = str_memory(cnt)
        cnt -= 1

    elif opcode == "STP":
        break
    elif opcode == "NOP":
        exit()
    cnt += 1

input_list = list()
# -------Take input and store it in input_list
while index != len(lines):
    opcode, _, _, third_operand = tuple(lines[index].split(sep=" "))
    if opcode == "+0":
        input_list.append(int(third_operand))
    index += 1


index = start_c_memory
instruction_list = list()  # code


# ---------------------- instruction array + output txt file ----------------
while True:
    opcode, first_operand, second_operand, third_operand = tuple(
        lines[index].split(sep=" "))
    index += 1
    if opcode == "LBL":
        continue
    elif opcode == "STP":
        ifp.write("+9 000 000 000\n")
        instruction_list.append(9000000000)
        break
    elif opcode == "NOP":
        exit()
    # write into the output.txt file
    ifp.write(symbol_dict[opcode]+" "+label_dict[first_operand] +
              " "+label_dict[second_operand]+" "+str_memory(int(label_dict[third_operand.strip()]))+"\n")
    # insert in the instruction_list the int version of the numeric code
    instruction_list.append(int(
        symbol_dict[opcode]+label_dict[first_operand]+label_dict[second_operand]+label_dict[third_operand.strip()]))

# --------------- print input in the file
while index != len(lines):

    if lines[index].startswith('+0'):
        ifp.write(lines[index])
    index += 1
ifp.close()


input_file_index = 0
ip = 0

# --------- Interpretation process
while ip != len(instruction_list):

    instruction = instruction_list[ip]

    ip += 1

    sign, digit, src, middle, dest = decode_instruction(
        instruction)

    if sign == '+':
        if digit == 0:
            data_memory[dest] = data_memory[src]
        elif digit == 1:
            data_memory[dest] = data_memory[src] + data_memory[middle]
        elif digit == 2:
            data_memory[dest] = data_memory[src] * data_memory[middle]
        elif digit == 3:
            data_memory[dest] = data_memory[src]*data_memory[src]
        elif digit == 4:
            if data_memory[src] == data_memory[middle]:
                ip = dest
                pass
        elif digit == 5:
            if data_memory[src] >= data_memory[middle]:
                ip = dest
                pass
        elif digit == 6:
            data_memory[dest] = data_memory[src][data_memory[middle]]
        elif digit == 7:
            data_memory[src] += 1
            if data_memory[src] < data_memory[middle]:
                ip = dest
                pass
        elif digit == 8:
            data_memory[dest] = int(input_list[input_file_index])
            input_file_index += 1

        elif digit == 9:
            break
    else:
        if digit == 0:
            print(f"invalid instruction: {instruction}")
            exit()
        elif digit == 1:
            data_memory[dest] = data_memory[src] - data_memory[middle]
        elif digit == 2:
            data_memory[dest] = data_memory[src] / data_memory[middle]
        elif digit == 3:
            data_memory[src] = math.sqrt(data_memory[src])
        elif digit == 4:
            if data_memory[src] != data_memory[middle]:
                ip = dest
        elif digit == 5:
            if data_memory[src] < data_memory[middle]:
                ip = dest
        elif digit == 6:
            data_memory[middle][data_memory[dest]] = data_memory[src]
        elif digit == 8:
            print(f"OUTPUT: {data_memory[src]}")
            pass

        elif digit == 9:
            pass

print('------ Memory Inspection Facility: -------------')
start = int(input("start: "))
end = int(input("end: "))
display(instruction_list, start, end)