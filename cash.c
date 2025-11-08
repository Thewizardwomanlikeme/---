#include <cs50.h>
#include <stdio.h>

int get_change(void);
int calculate_quarters(int change);
int calculate_dimes(int change);
int calculate_nickels(int change);
int calculate_pennies(int change);
int calculate_sum(int quarters, int dimes, int nickles, int pennies);

int main(void)
{
    int change = get_change();
    int quarters = calculate_quarters(change);
    change = change - (25 * quarters);
    int dimes = calculate_dimes(change);
    change = change - (10 * dimes);
    int nickles = calculate_nickels(change);
    change = change - (5 * nickles);
    int pennies = calculate_pennies(change);

    int sum = calculate_sum(quarters, dimes, nickles, pennies);
    printf("the total number of coins required are %i\n", sum);
}

int get_change(void)
{
    int c;
    do
    {
        c = get_int("change owed: ");
    }
    while (c < 0);
    return c;
}

int calculate_quarters(int change)
{
    int quarter = 0;
    while (change >= 25)
    {
        quarter++;
        change -= 25;
    }
    return quarter;
}

int calculate_dimes(int change)
{
    int dimes = 0;
    while (change >= 10)
    {
        dimes++;
        change -= 10;
    }
    return dimes;
}

int calculate_nickels(int change)
{
    int nickles = 0;
    while (change >= 5)
    {
        nickles++;
        change -= 5;
    }
    return nickles;
}

int calculate_pennies(int change)
{
    int pennies = 0;
    while (change >= 1)
    {
        pennies++;
        change -= 1;
    }
    return pennies;
}

int calculate_sum(int quarters, int dimes, int nickles, int pennies)
{
    int sum = quarters + dimes + nickles + pennies;
    return sum;
}


