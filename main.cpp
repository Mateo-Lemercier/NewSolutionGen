#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include "main.h"
#include "Settings.h"
#include "SolutionGenerator.h"



int Help()
{
    std::cout << HELP_MESSAGE;
    return 0;
}

int Create( int const argc, char *argv[] )
{
    if ( argc < 4 ) return 1;

    std::string projectName = argv[3];
    bool pch = false;
    bool vcpkg = false;
    bool lib = false;
    bool window = false;

    if ( argc != 4 )
    {
        if ( std::string const argv4 = argv[4]; argv4 == "-pch" ) pch = true;
        else if ( argv4 == "-vcpkg" ) vcpkg = true;
        else if ( argv4 == "-lib" ) lib = true;
        else if ( argv4 == "-window" ) window = true;
        else projectName = argv4;

        for ( int i = 5; i < argc; ++i )
        {
            if ( std::string const argvi = argv[i]; argvi == "-pch" ) pch = true;
            else if ( argvi == "-vcpkg" ) vcpkg = true;
            else if ( argvi == "-lib" ) lib = true;
            else if ( argvi == "-window" ) window = true;
            else return 1;
        }
    }

    if ( std::string const errorMessage = SolutionGenerator::CreateRepository( argv[2], argv[3], projectName, pch, vcpkg, lib, window );
        errorMessage.empty() == false )
    {
        std::cout << FG_RED << errorMessage << STYLE_RESET;
        return 1;
    }

    if ( std::string const errorMessage = SolutionGenerator::MakeSolution( argv[2], false, true );
        errorMessage.empty() == false )
    {
        std::cout << FG_RED << errorMessage << STYLE_RESET;
        return 1;
    }

    return 0;
}

int Make( int const argc, char *argv[] )
{
    if ( argc < 3 ) return 1;

    bool clear = false;
    bool open = false;

    if ( argc != 3 )
    {
        bool specifiedProject = false;

        if ( std::string const argvi = argv[3]; argvi == "-clear" ) clear = true;
        else if ( argvi == "-open" ) open = true;
        else specifiedProject = true;

        for ( int i = 4; i < argc; ++i )
        {
            if ( std::string const argvi = argv[i]; argvi == "-clear" ) clear = true;
            else if ( argvi == "-open" ) open = true;
            else return 1;
        }

        if ( specifiedProject )
        {
            if ( std::string const errorMessage = SolutionGenerator::MakeSolution( argv[2], argv[3], clear, open );
                errorMessage.empty() == false )
            {
                std::cout << FG_RED << errorMessage << STYLE_RESET;
                return 1;
            }

            return 0;
        }
    }

    if ( std::string const errorMessage = SolutionGenerator::MakeSolution( argv[2], clear, open );
        errorMessage.empty() == false )
    {
        std::cout << FG_RED << errorMessage << STYLE_RESET;
        return 1;
    }

    return 0;
}

int AddProject( int const argc, char* argv[] )
{
    if ( argc < 4 ) return 1;

    bool pch = false;
    bool vcpkg = false;
    bool lib = false;
    bool window = false;

    if ( argc != 4 )
    {
        for ( int i = 5; i < argc; ++i )
        {
            if ( std::string const argvi = argv[i]; argvi == "-pch" ) pch = true;
            else if ( argvi == "-vcpkg" ) vcpkg = true;
            else if ( argvi == "-lib" ) lib = true;
            else if ( argvi == "-window" ) window = true;
            else return 1;
        }
    }

    if ( std::string const errorMessage = SolutionGenerator::CreateProject( argv[2], argv[3], pch, vcpkg, lib, window );
        errorMessage.empty() == false )
    {
        std::cout << FG_RED << errorMessage << STYLE_RESET;
        return 1;
    }

    if ( std::string const errorMessage = SolutionGenerator::MakeSolution( argv[2], false, false );
        errorMessage.empty() == false )
    {
        std::cout << FG_RED << errorMessage << STYLE_RESET;
        return 1;
    }

    return 0;
}

int AddDependency( int const argc, char* argv[] )
{
    if ( argc < 5 ) return 1;

    std::vector<std::string> dependencies;
    dependencies.reserve( argc-4 );

    for ( int i = 4; i < argc; ++i )
        dependencies.push_back( argv[i] );

    if ( std::string const errorMessage = SolutionGenerator::AddDependenciesToProjectConfig( argv[2], argv[3], dependencies );
        errorMessage.empty() == false )
    {
        std::cout << FG_RED << errorMessage << STYLE_RESET;
        return 1;
    }

    return 0;
}


int AddPort( int const argc, char* argv[] )
{
    if ( argc < 5 ) return 1;

    // TODO

    return 0;
}



int main( int const argc, char *argv[] )
{
    srand( time( nullptr ) );
    
    if ( argc < 2 )
    {
        // SolutionGenerator.exe
        return 0;
    }

    if ( argv[1] == std::string( "-help" ) ) return Help();
    if ( argv[1] == std::string( "-create" ) ) return Create( argc, argv );
    if ( argv[1] == std::string( "-make") ) return Make( argc, argv );
    if ( argv[1] == std::string( "-addProject" ) ) return AddProject( argc, argv );
    if ( argv[1] == std::string( "-addDependency" ) ) return AddDependency( argc, argv );
    if ( argv[1] == std::string( "-addPort" ) ) return AddPort( argc, argv );

    return 0;
}