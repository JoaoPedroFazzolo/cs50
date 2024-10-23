#include <cs50.h>
#include <stdio.h>
int height = 0;
int main(void)
{
    do
    {
        height = get_int("What's the height: ");
    }
    while (height < 1 || height > 8);
    // Making bricks
    for (int i = 0; i < height; i++)
    {
        // left spaces
        for (int j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }

        // left bricks
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }

        // between spaces
        printf("  ");

        // right bricks
        for (int l = 0; l <= i; l++)
        {
            printf("#");
        }
        // next line
        printf("\n");
    }
}
