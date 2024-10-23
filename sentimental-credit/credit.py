from cs50 import get_int


def luhn_algorithm(card_number):
    digits = [int(digit) for digit in str(card_number)][::-1]

    for i in range(1, len(digits), 2):
        digits[i] *= 2
        digits[i] = (digits[i] % 10) + (digits[i] // 10)

    total = sum(digits)
    return total % 10 == 0


def get_card_type(card_number):
    length = len(str(card_number))
    if length == 15 and (str(card_number)[:2] == '34' or str(card_number)[:2] == '37'):
        return "AMEX"
    elif length == 16 and 51 <= int(str(card_number)[:2]) <= 55:
        return "MASTERCARD"
    elif (length == 13 or length == 16) and str(card_number)[0] == '4':
        return "VISA"
    else:
        return "INVALID"


card_number = get_int("Number: ")

if luhn_algorithm(card_number):
    card_type = get_card_type(card_number)
    print(card_type)
else:
    print("INVALID")
