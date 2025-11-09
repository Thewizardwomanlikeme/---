#include <cs50.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define blocksize 512
uint8_t buffer[blocksize];

bool check_jpeg_header(void)
{
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
    {
        return true;
    }
    return false;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open file");
        return 1;
    }
    FILE *img = NULL;
    char filename[8];
    int count = 0;
    while (fread(buffer, 1, blocksize, card) == blocksize)
    {
        if (check_jpeg_header())
        {
            if (img != NULL)
            {
                fclose(img);
            }

            sprintf(filename, "%03i.jpg", count++);
            img = fopen(filename, "w");
            if (img == NULL)
            {
                printf("Could not create output file\n");
                fclose(card);
                return 1;
            }
        }
        if (img != NULL)
        {
            fwrite(buffer, 1, 512, img);
        }
    }
    if (img != NULL)
    {
        fclose(img);
    }
    fclose(card);
}
