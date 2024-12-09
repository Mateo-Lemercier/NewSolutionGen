#include "NumberToHex.h"
#include <iostream>


void NumberToHex( unsigned short const number, std::string& appendTo )
{
    for ( int i = 0; i < 4; ++i )
    {
        unsigned short temp = number;
        temp <<= 4*i;
        temp >>= 4*3;
        char character = static_cast<char>( temp );
        if ( character < 10 ) character += '0';
        else character += 'A' - 10;
        appendTo += character;
    }
}