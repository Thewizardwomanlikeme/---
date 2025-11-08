#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long retrieve_credit_number(void);
int calculate_luhn_product_total(long credit);
int calculate_luhn_others_total(long credit);
void initial_check(int num, long credit);
void check_card_type(int num, long credit, int length);

int main(void)
{
    bool invalid = false;
    long credit = retrieve_credit_number();
    int first_total = calculate_luhn_product_total(credit);
    int next_total = calculate_luhn_others_total(credit);
    int final_total = first_total + next_total;
    char creditt[20];
    sprintf(creditt, "%ld", credit);
    int length = strlen(creditt);
    int num = final_total % 10;
    initial_check(num, credit);
    check_card_type(num, credit, length);
}

long retrieve_credit_number(void)
{
    string credit;
    int length;
    long c = 0;
    bool running;
    do
    {
        running = true;
        credit = get_string("credit number: ");
        length = strlen(credit);
        for (int i = 0; i < length; i++)
        {
            if (!isdigit(credit[i]))
            {
                running = false;
            }
        }
    }
    while (length == 0 || running == false);
    if (length == 13 || length == 16 || length == 15)
    {
        c = strtol(credit, NULL, 10);
    }
    return c;
}

int calculate_luhn_product_total(long credit)
{
    int total = 0;
    while (credit > 0)
    {
        credit = credit / 10;
        int num = credit % 10;
        num *= 2;
        if (num > 9)
        {
            int sum = 0;
            int numm;
            while (num > 0)
            {
                numm = num % 10;
                sum += numm;
                num = num / 10;
            }
            total += sum;
        }
        total += num;
        credit = credit / 10;
    }
    return total;
}

int calculate_luhn_others_total(long credit)
{
    int total = 0;
    int num;
    while (credit > 0)
    {
        num = credit % 10;
        total += num;
        credit = credit / 100;
    }
    return total;
}

void initial_check(int num, long credit)
{
    int total = 0;
    do
    {
        int credit_digit = credit % 10;
        total += credit_digit;
        credit = credit / 10;
    }
    while (credit > 0);
    if (total == 0 || num != 0)
    {
        printf("INVALID\n");
    }
}

void check_for_AMEX(long credit, int length)
{
    if (length == 15)
    {
        int nnum = credit / pow(10, 13);
        if (nnum == 34 || nnum == 37)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}

void check_for_VISA_or_MASTERCARD(int length, long credit)
{
    bool printing = false;
    int nuum = credit / pow(10, 14);
    int numm = credit / pow(10, 15);
    int mastercard[] = {51, 52, 53, 54, 55};
    if (length == 13)
    {
        printf("VISA\n");
    }
    else if (length == 16)
    {

        if (numm == 4)
        {
            printf("VISA\n");
            printing = true;
        }
        for (int i = 0; i < 6; i++)
        {
            if (nuum == mastercard[i])
            {
                printf("MASTERCARD\n");
                printing = true;
            }
        }
        if (printing == false)
        {
            printf("INVALID\n");
        }
    }
}

void check_card_type(int num, long credit, int length)
{
    if (num == 0)
    {
        check_for_AMEX(credit, length);
        check_for_VISA_or_MASTERCARD(length, credit);
    }
}
