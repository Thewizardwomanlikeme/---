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
    int height;

    while (true)
    {
        height = get_int("enter the height: ");

        if (height < 1 || height > 8)
        {
            printf("the height must be between 1 to 8\n");
        }
        else
        {
            return height;
        }
    }
}

void print_pyramid(int h)
{
    for (int row = 1; row < h + 1; row++)
    {
        for (int col = row; col < h; col++)
        {
            printf(" "); 
        }
        for (int col = 0; col < row; col++)
        {
            printf("#");
        }
        printf("\n");
    }
}
