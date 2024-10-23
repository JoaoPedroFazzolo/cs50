#include <cs50.h>
#include <stdio.h>
bool luhn_algorithm(long number);
string card_flag(long number);
int main(void)
{
    long credit_number = get_long("What's your credit card number? ");
    if (luhn_algorithm(credit_number))
    {
        string card_type = card_flag(credit_number);
        printf("%s", card_type);
    }
    else
    {
        printf("INVALID\n");
    }
}

bool luhn_algorithm(long number)
{
    int sum = 0;
    int digit_count = 0;

    while (number > 0)
    {
        int digit = number % 10;

        if (digit_count % 2 == 1)
        {
            digit *= 2;
            if (digit > 9)
            {
                digit = digit / 10 + digit % 10;
            }
        }
        sum += digit;
        digit_count++;
        number /= 10;
    }
    return (sum % 10 == 0);
}

string card_flag(long number)
{
    int first_digit, second_digit = 0;
    int digitCount = 0;

    while (number > 0)
    {
        second_digit = first_digit;
        first_digit = number % 10;
        number /= 10;
        digitCount++;
    }

    if (((digitCount == 13) || (digitCount == 16)) && (first_digit == 4))
    {
        return "VISA\n";
    }
    else if ((digitCount == 16) && (first_digit == 5) && (second_digit >= 1 && second_digit <= 5))
    {
        return "MASTERCARD\n";
    }
    else if ((digitCount == 15) && (first_digit == 3) && ((second_digit == 4) || (second_digit == 7)))
    {
        return "AMEX\n";
    }
    else
    {
        return "INVALID\n";
    }
}
