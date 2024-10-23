#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");

    // Check if the file was opened successfully
    if (card == NULL)
    {
        fprintf(stderr, "Could not open file %s\n", argv[1]);
        return 2;
    }

    // Create a buffer for a block of data
    uint8_t buffer[512];

    // Counter to keep track of JPEGs found
    int jpeg_count = 0;

    // File pointer for the current JPEG
    FILE *jpeg = NULL;

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, 512, card) == 512)
    {
        // Check for the start of a new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If it's not the first JPEG, close the previous one
            if (jpeg != NULL)
            {
                fclose(jpeg);
            }

            // Create a new JPEG file
            char filename[8];
            sprintf(filename, "%03d.jpg", jpeg_count);
            jpeg = fopen(filename, "w");

            // Check if the file was created successfully
            if (jpeg == NULL)
            {
                fclose(card);
                fprintf(stderr, "Could not create JPEG file %s\n", filename);
                return 3;
            }

            // Increment JPEG counter
            jpeg_count++;
        }

        // Write the buffer to the current JPEG file
        if (jpeg != NULL)
        {
            fwrite(buffer, 1, 512, jpeg);
        }
    }

    // Close any remaining files
    if (jpeg != NULL)
    {
        fclose(jpeg);
    }

    // Close the memory card
    fclose(card);

    return 0;
}
