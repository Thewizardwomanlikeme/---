#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int coloumn = 0; coloumn < width; coloumn++)
        {
            int red = image[row][coloumn].rgbtRed;
            int green = image[row][coloumn].rgbtGreen;
            int blue = image[row][coloumn].rgbtBlue;
            float avg = (blue + green + red) / (float) 3.0;
            int new_color = round(avg);
            if (new_color > 255)
                new_color = 255;
            image[row][coloumn].rgbtRed = new_color;
            image[row][coloumn].rgbtGreen = new_color;
            image[row][coloumn].rgbtBlue = new_color;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int coloumn = 0; coloumn < width; coloumn++)
        {
            int originalRed = image[row][coloumn].rgbtRed;
            int originalGreen = image[row][coloumn].rgbtGreen;
            int originalBlue = image[row][coloumn].rgbtBlue;
            float sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
            float sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            float sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;
            int new_red = round(sepiaRed);
            int new_green = round(sepiaGreen);
            int new_blue = round(sepiaBlue);
            if (new_red > 255)
                new_red = 255;
            if (new_green > 255)
                new_green = 255;
            if (new_blue > 255)
                new_blue = 255;
            image[row][coloumn].rgbtRed = new_red;
            image[row][coloumn].rgbtGreen = new_green;
            image[row][coloumn].rgbtBlue = new_blue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int coloumn = 0; coloumn < width / 2; coloumn++)
        {
            RGBTRIPLE temp = image[row][coloumn];
            image[row][coloumn] = image[row][width - 1 - coloumn];
            image[row][width - 1 - coloumn] = temp;
        }
    }
    return;
}

RGBTRIPLE calculate(int max, int rows, int cols, int i, int j, RGBTRIPLE image[rows][cols],
                    RGBTRIPLE box[])
{
    int red_sum = 0, blue_sum = 0, green_sum = 0;

    for (int k = 0; k < max; k++)
    {
        red_sum += box[k].rgbtRed;
        blue_sum += box[k].rgbtBlue;
        green_sum += box[k].rgbtGreen;
    }

    int avg_red = red_sum / max;
    int avg_green = green_sum / max;
    int avg_blue = blue_sum / max;

    image[i][j].rgbtRed = avg_red;
    image[i][j].rgbtGreen = avg_green;
    image[i][j].rgbtBlue = avg_blue;

    return image[i][j];
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red_sum = 0, green_sum = 0, blue_sum = 0;
            int count = 0;

            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    int ni = i + k;
                    int nj = j + l;

                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        red_sum += copy[ni][nj].rgbtRed;
                        green_sum += copy[ni][nj].rgbtGreen;
                        blue_sum += copy[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            image[i][j].rgbtRed = round((float) red_sum / count);
            image[i][j].rgbtGreen = round((float) green_sum / count);
            image[i][j].rgbtBlue = round((float) blue_sum / count);
        }
    }
    return;
}
