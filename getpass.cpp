#include <iostream>
#include <conio.h>
#include <string>

using namespace std;

string getpass()
{
    const char BACKSPACE = 8;
    const char RETURN = 13;

    string password;
    unsigned char ch = 0;

    while ((ch = _getch()) != RETURN)
    {
        if (ch == BACKSPACE)
        {
            if (password.length() != 0)
            {
                cout << "\b";
                password.resize(password.length() - 1);
                cout << " \b";
            }
        }
        else
        {
            password += ch;
            cout << '*';
        }
    }
    cout << endl;
    return password;
}