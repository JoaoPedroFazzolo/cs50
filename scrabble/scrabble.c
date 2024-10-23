#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int compute_score(string a);
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    // Prompt the user for two words
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Compute the score of each word
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);
    // Print the winner

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
        (score1 = score2);
    {
        printf("Tie!");
    }
}

int compute_score(string a)
{
    int sum = 0;
    for (int i = 0, len = strlen(a); i < len; i++)
    {
        if isupper (a[i])
        {
            sum += POINTS[a[i] - 'A'];
        }
        else
        {
            sum += POINTS[a[i] - 'a'];
        }
    }
    return sum;
}
