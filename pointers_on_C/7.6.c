/*
 * =====================================================================================
 *
 *       Filename:  7.6.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年08月05日 21时12分28秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  guojun (jun_guo), jun_guo@dtri.com
 *        Company:  DT Research
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *digits[] = {" ", "ONE ", "TWO ", "THREE ", "FOUR ", "FIVE ", "SIX ",
                        "SEVEN ", "EIGHT ", "NINE ", "TEN ", "ELEVEN ", "TWELVE ",
                        "THIRTEEN ", "FOURTEEN ", "FIFTEEN ", "SIXTEEN ", "SEVENTEEN ",
                        "EIGHTEEN ", "NINETEEN "};
static char *tens[] = {" ", " ", "TWENTY ", "THIRTY ", "FORTY ", "FIFTY ", "SIXTY ",
                      "SEVENTY ", "EIGHTY ", "NINETY "};
static char *magnitudes[] = {" ", "THOUSAND ", "MILLION ", "BILLION "};

static void do_one_group(unsigned int amount, char *buffer, char **magnitude);
void written_amoubnt(unsigned int amount, char *buffer);

static void do_one_group(unsigned int amount, char *buffer, char **magnitude)
{
    int value;

    value = amount / 1000;
    if(value > 0)
        do_one_group(value, buffer, magnitude + 1);

    amount %= 1000;
    value = amount / 100;
    if(value > 0)
    {
        strcat(buffer, digits[value]);
        strcat(buffer, "HUNDRED ");
    }
    value = amount % 100;
    if(value >= 20)
    {
        strcat(buffer, tens[value / 10]);
        value %= 10;
    }
    if(value > 0)
        strcat(buffer, digits[value]);
    if(amount > 0)
        strcat(buffer, *magnitude);
}

void written_amoubnt(unsigned int amount, char *buffer)
{
    if(amount == 0)
    {
        strcpy(buffer, "ZERO");
    }
    else
    {
        *buffer = '\0';
        do_one_group(amount, buffer, magnitudes);
    }
}

int main(int argc, char **argv)
{
    unsigned int amount = 16312;
    char buffer[100];
    written_amoubnt(amount, buffer);

    printf("%s\n", buffer);

    return 0;
}
