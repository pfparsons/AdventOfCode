from pathlib import Path

input_path = (Path(__file__)
              .parent
              .joinpath("input.txt")
            )

def outer_digits(line: str):
    digits = []

    # digits 0 to 9 are in ascii range 48 to 57
    ascii_0 = ord("0")
    ascii_9 = ord("9")

    digit_words = (
        'one',
        'two',
        'three',
        'four',
        'five',
        'six',
        'seven',
        'eight',
        'nine',
    )

    for i, c in enumerate(line):

        x = ord(c)
        if x >= ascii_0 and x <= ascii_9:
            digits.append(int(c))
        else:
            for y, word in enumerate(digit_words):
                if line[i:].startswith(word):
                    digits.append(y + 1)
    
    n = len(digits)

    if n > 0:
        if n == 1:
            return (digits[0],digits[0])        
        elif n > 1:
            return (digits[0], digits[n - 1])
    else:
        raise ValueError(f"Bad Line: {line}")

sum = 0
with open(input_path) as file:
    for line in file:
        digits = outer_digits(line[:-1])
        value = 10 * digits[0] + digits[1]
        sum += value
        print(f"{line[:-1]} => {digits} => {value} => Sum: {sum}")

print("---------------------------------------------")
print(sum)
