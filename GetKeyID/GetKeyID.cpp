#include <iostream>
#include <conio.h>


int main()
{
    while ( true )
    {
        if ( _kbhit() == false ) continue;

        int const input = _getch();

        std::cout << static_cast<char>(input) << ": " << input << '\n';
    }
}