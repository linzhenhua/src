#include <iostream>
#include <string>

#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <assert.h>
#include <unistd.h>

int getch(void) 
{
    int c=0;
    struct termios org_opts, new_opts;
    int res=0;

    //-----  store old settings -----------
    res=tcgetattr(STDIN_FILENO, &org_opts);
    assert(res==0);

    //---- set new terminal parms --------
    memcpy(&new_opts, &org_opts, sizeof(new_opts));
    new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
    c=getchar();

    //------  restore old settings ---------
    res=tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);assert(res==0);

    return c;
}

int main(void)
{
    char ch;
    std::string str;

    int i = 0;
    while(i != 10)
    {
        fflush(stdin);
        ch = (char)getch();
        std::cout << '*';
        str.append(1u, ch);
        ++i;
        std::cout << ch << std::endl;
    }
    std::cout << std::endl;

    std::cout << str << std::endl;

    return 0;
}
