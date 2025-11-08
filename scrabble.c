#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int compute_score1(string word1);
int compute_score2(string word2);
void winner(int score1, int score2);

int main(void)
{
    // Prompt the user for two words
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Compute the score of each word
    int score1 = compute_score1(word1);
    int score2 = compute_score2(word2);

    // Print the winner
    winner(score1, score2);
}

int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score1(string word1)
{
    int score1 = 0;
    for (int i = 0, len = strlen(word1); i < len; i++)
    {
        if (isupper(word1[i]))
        {
            score1 += POINTS[word1[i] - 'A'];
        }
        else if (islower(word1[i]))
        {
            score1 += POINTS[word1[i] - 'a'];
        }
        else if (!isalpha(word1[i]))
        {
            score1 += 0;
        }
    }
    return score1;
}

int compute_score2(string word2)
{
    int score2 = 0;
    for (int i = 0, len = (strlen(word2)); i < len; i++)
    {
        if (isupper(word2[i]))
        {
            score2 += POINTS[word2[i] - 'A'];
        }
        else if (islower(word2[i]))
        {
            score2 += POINTS[word2[i] - 'a'];
        }
        else if (!isalpha(word2[i]))
        {
            score2 += 0;
        }
    }
    return score2;
}

void winner(int score1, int score2)
{
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}
