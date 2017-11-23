#include <string>
#include <curses.h>
#include <iostream>

#include <locale.h>

using namespace std;

string getpass(const char *prompt, bool show_asterisk=true)
{
    const char BACKSPACE=8;
    const char RETURN=10; // Note: 10 for curses, 13 for conio

    string password;
    unsigned char ch=0;

    printw(prompt);
    printw("\n");

    noecho(); // Disable echoing

    while((ch=getch())!=RETURN)
    {
        if(ch==BACKSPACE)
        {
            if(password.length()!=0)
            {
                if(show_asterisk)
                printw("\b \b");
                password.resize(password.length()-1);
            }
        }
        else if(ch!=27) // ignore 'escape' key
        {
            password+=ch;
            if(show_asterisk)
            printw("*");
        }
    }

    echo();
    printw("\n");
    return password;
}

int main()
{
    setlocale(LC_ALL, "");
    initscr();

    cout << "dddd" << endl;

    const char *correct_password="null";

    printw("Test 1: echoing enabled林振华\n");
    string password=getpass("Please enter the password: ",true); // Show asterisks
    if(password==correct_password)
        printw("Correct password!\n");
    else
        printw("Incorrect password. Try again\n");

    printw("\nTest 2: echoing disabled\n");
    password=getpass("Please enter the password: ",false); // Do not show asterisks
    if(password==correct_password)
        printw("Correct password");
    else
        printw("Incorrect password. Try again");

    printw("\n\nPress any key to continue...");
    getch();
    endwin();

    return 0;
}
