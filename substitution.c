#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
bool success = true;
bool running = true;
string get_key(int argc, string argv[]);
void rotate(string key);

int main(int argc, string argv[])
{
    string key = get_key(argc, argv);
    if (success == false && running == true)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (running == false)
    {
        return 1;
    }
    rotate(key);
    free(key);
    return 0;
}

string get_key(int argc, string argv[])
{
    char *key = malloc(26 * sizeof(char));
    if (key == NULL)
    {
        printf("Memory allocation failed\n");
        success = false;
    }
    if (argc == 2)
    {
        bool seen[60];
        for (int j = 0; j < 60; j++)
        {
            seen[j] = false;
        }
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (isalpha(argv[1][i]))
            {
                int index;
                if (isupper(argv[1][i]))
                {
                    index = argv[1][i] - 'A';
                }
                else
                {
                    index = argv[1][i] - 'a';
                }
                if (seen[index] == true)
                {
                    success = false;
                }
                else
                {
                    char c[2] = {argv[1][i], '\0'};
                    strncat(key, c, 1);
                    seen[index] = true;
                }
            }
            else
            {
                success = false;
            }
        }
        if (strlen(key) != 26 && success == true)
        {
            printf("Key must contain 26 characters.\n");
            running = false;
        }
    }
    else
    {
        success = false;
    }
    return key;
}

void rotate(string key)
{
    string plaintext = get_string("plaintext:  ");
    printf("ciphertext: ");
    char cipher[100] = "";
    int j;
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                j = plaintext[i] - 'A';
                char c[2] = {toupper(key[j]), '\0'};
                strncat(cipher, c, 1);
            }
            else
            {
                j = plaintext[i] - 'a';
                char c[2] = {tolower(key[j]), '\0'};
                strncat(cipher, c, 1);
            }
        }
        else
        {
            char c[2] = {plaintext[i], '\0'};
            strncat(cipher, c, 1);
        }
    }
    printf("%s\n", cipher);
}
