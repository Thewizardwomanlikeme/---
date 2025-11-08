#include <cs50.h>
#include <stdio.h>

int get_height(void);
void print_pyramid(int h);

int main(void)
{
    int h = get_height();
    print_pyramid(h);
}

int get_height(void)
{
    int h;
    do
    {
        h = get_int("enter the height: ");
    }
    while (1 > h || h > 8);
    return h;
}

void print_pyramid(int h)
{
    int row, col;
    for (row = 1; row < h + 1; row++)
    {
        for (col = row; col < h; col++)
        {
            printf(" ");
        }
        for (col = 0; col < row; col++)
        {
            printf("#");
        }
        printf("  ");

        for (col = 0; col < row; col++)
        {
            printf("#");
        }
        printf("\n");
    }
}

       