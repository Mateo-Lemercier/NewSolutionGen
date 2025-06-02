#include "SolutionGen.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <conio.h>
#include <windows.h>
#include "define.h"
namespace fs = std::filesystem;


int SolutionGen::Run( int const argc, char* argv[] ) { return s_instance.InternalRun( argc, argv ); }


SolutionGen::SolutionGen()
{
    HANDLE const hConsole = GetStdHandle( STD_OUTPUT_HANDLE );

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo( hConsole, &cursorInfo );
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo( hConsole, &cursorInfo );
}



int SolutionGen::InternalRun( int const argc, char* argv[] )
{
    if ( argc != 1 ) ERROR( "Just double click on the executable." )

    for ( auto const& entry : fs::directory_iterator( "./" ) )
    {
        if ( entry.is_directory() == false ) continue;
        std::string const potentialSolution = entry.path().filename().string();
        if ( fs::exists( potentialSolution + "/config/settings.json" ) == false ) continue;
        m_validSolutions.push_back( potentialSolution );
    }

    int result = SelectBetweenOptions( { "make existing solution", "edit existing solution", "create new solution" } );

    return 0;
}


int SolutionGen::SelectBetweenOptions( std::vector<std::string> const& options )
{
    unsigned char optionCount = static_cast<unsigned char>( options.size() );
    unsigned char selector = 0;
    while ( true )
    {
        system( "cls" );

        for ( unsigned char i = 0; i < optionCount; i++ )
        {
            if ( i == selector ) std::cout << ">";
            else std::cout << STYLE( "2;37" );
            std::cout << "  " << options[i] << "\n" STYLE_RESET;
        }

        bool update = false;
        while ( update == false )
        {
            if ( _kbhit() == false ) continue;

            switch ( unsigned char const input = static_cast<unsigned char>( _getch() ) )
            {
                case Keys::UP_ARROW:
                    if ( selector == 0 ) break;
                    selector--;
                    update = true;
                    break;

                case Keys::DOWN_ARROW:
                    if ( selector >= optionCount-1 ) break;
                    selector++;
                    update = true;
                    break;

                default: break;
            }
        }
    }
}


// int SolutionGen::SetSolutionPath( std::string const& solutionPath )
// {
//     if ( fs::exists( solutionPath ) == false ) ERROR( "Couldn't find the given path : " << solutionPath )
//     
//     m_solutionPath = solutionPath;
//
//     m_binPath    = solutionPath + "/bin";
//     m_configPath = solutionPath + "/config";
//     m_idePath    = solutionPath + "/ide";
//     m_libPath    = solutionPath + "/lib";
//     m_resPath    = solutionPath + "/res";
//     m_srcPath    = solutionPath + "/src";
// }


SolutionGen SolutionGen::s_instance = SolutionGen();