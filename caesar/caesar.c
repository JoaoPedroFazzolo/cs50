#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    // Make sure program was run with just one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    if (only_digits(argv[1]))
    {
        printf("Usage: ./caesar key coloque apenas numero\n");
        return 1;
    }

    // Convert argv[1] from a `string` to an `int`
    int key = atoi(argv[1]);

    // Prompt user for plaintext
    string plaintext = get_string("plaintext:  ");
    // For each character in the plaintext:
    int lenght = strlen(plaintext);
    // Rotate the character if it's a letter
    char encrypted_text[lenght + 1];
    for (int i = 0; i < lenght; i++)
    {
        char encrypted_char = rotate(plaintext[i], key);
        encrypted_text[i] = encrypted_char;
    }
    encrypted_text[lenght] = '\0';
    printf("ciphertext: %s\n", encrypted_text);
    return 0;
}

// Make sure every character in argv[1] is a digit
bool only_digits(string s)
{
    int lenght = strlen(s);
    for (int i = 0; i < lenght; i++)
    {
        if (s[i] < '0' || s[i] > '9')
            return true;
    }
    return false;
}

char rotate(char c, int n)
{
    if (isupper(c))
    {
        return ((c - 'A' + n) % 26) + 'A';
    }
    else if (islower(c))
    {
        return ((c - 'a' + n) % 26) + 'a';
    }
    else
    {
        return c; // Não criptografa caracteres não alfabéticos
    }
}
