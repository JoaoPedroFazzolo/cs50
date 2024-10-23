#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

float count_letters(string text, int str_length);
float count_words(string text, int str_length);
float count_sentences(string text, int str_length);
const int m = 100;

int main(void)
{
    // Prompt the user for some text
    string text = get_string("Text: ");
    int length = strlen(text);
    // Count the number of letters, words, and sentences in the text
    int letters = count_letters(text, length);
    int words = count_words(text, length);
    int sentences = count_sentences(text, length);
    // Compute the Coleman-Liau index
    float L = ((100.0 / words) * letters);
    float S = ((100.0 / words) * sentences);
    float index = 0.0588 * L - 0.296 * S - 15.8;
    index = round(index);
    // Print the grade level
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) index);
    }
}

float count_letters(string text, int str_length)
{
    int count = 0;
    for (int i = 0; i < str_length; i++)
    {
        if (isalpha(text[i]) != 0)
        {
            count++;
        }
    }

    return count;
}

float count_words(string text, int str_length)
{
    int count = 0;
    for (int i = 0; i < str_length; i++)
    {
        if (isspace(text[i]) != 0)
        {
            count++;
        }
    }
    return count + 1;
}

float count_sentences(string text, int str_length)
{
    int count = 0;
    for (int i = 0; i < str_length; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}
