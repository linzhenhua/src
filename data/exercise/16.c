#include <stdio.h>
#include <unistd.h>
 
void delay_play(char *str)
{
    while(*str)
    {
        putchar(*str++);
        fflush(stdout);
        usleep(1000000);
    }
}
 
int main(void)
{
    char *text = "I am chinese";
 
    for(;;)
    {
        delay_play(text);
        puts("");
    }
  
    return 0;
}
