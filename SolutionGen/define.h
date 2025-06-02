#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED


// Normal - 0
// Bold - 1
// Dark - 2
// Underline - 4

// Black Foreground - 30
// Red Foreground - 31
// Green Foreground - 32
// Yellow Foreground - 33
// Blue Foreground - 34
// Magenta Foreground - 35
// Cyan Foreground - 36
// White Foreground - 37

// Black Background - 40
// Red Background - 41
// Green Background - 42
// Yellow Background - 43
// Blue Background - 44
// Magenta Background - 45
// Cyan Background - 46
// White Background - 47

#define STYLE( style ) "\033[" style "m"
#define STYLE_RESET STYLE( "0" )
#define FG_INPUT STYLE( "36" )

#define SUCCESS( message ) std::cout << STYLE( "32" ) << message << "\n" STYLE_RESET;
#define SUBSUCCESS( message ) std::cout << STYLE( "2;32" ) "  " << message << "\n" STYLE_RESET;
#define ERROR( message ) { std::cout << STYLE( "31" ) << message << "\n" STYLE_RESET; return 1; }


#endif