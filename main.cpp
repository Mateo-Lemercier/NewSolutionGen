#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include "main.h"
#include "Settings.h"
#include "SolutionGenerator.h"



int Help( int const argc, char *argv[] )
{
    if ( argc == 2 )
    {
        std::cout << HELP_START << HELP_MESSAGE;
        return 0;
    }

    if ( argc != 3 ) return 1;

    std::cout << HELP_START;

    if ( std::string const& action = argv[2]; action == "help" ) std::cout << HELP_HELP;
    else if ( action == "create" ) std::cout << HELP_CREATE;
    else if ( action == "make" ) std::cout << HELP_MAKE;
    else if ( action == "addProject" ) std::cout << HELP_ADD_PROJECT;
    else if ( action == "addDependency" ) std::cout << HELP_ADD_DEPENDENCY;
    else if ( action == "addPort" ) std::cout << HELP_ADD_PORT;
    else return 1;

    return 0;
}

int Create( int const argc, char *argv[] )
{
    if ( argc < 4 ) return 1;

    std::string const& repositoryName = argv[2];
    std::string const& solutionName = argv[3];
    std::string projectName = solutionName;
    std::vector<std::string> dependencies;
    bool pch = false;
    bool vcpkg = false;
    bool lib = false;
    bool window = false;

    if ( argc != 4 )
    {
        unsigned char startIndex = 4;

        if ( std::string const& argv4 = argv[4];
             argv4[0] != '-' )
        {
            projectName = argv4;
            startIndex++;

            dependencies.reserve( argc-5 );

            for ( unsigned char i = 5; i < argc; i++, startIndex++ )
            {
                std::string const& argvi = argv[i];
                
                if ( argvi[0] == '-' ) break;
                
                dependencies.push_back( argvi );
            }
        }

        for ( unsigned char i = startIndex; i < argc; i++ )
        {
            if ( std::string const& argvi = argv[i]; argvi == "-pch" ) pch = true;
            else if ( argvi == "-vcpkg" ) vcpkg = true;
            else if ( argvi == "-lib" ) lib = true;
            else if ( argvi == "-window" ) window = true;
            else return 1;
        }
    }

    CHECK_FOR_ERROR( CreateRepository( repositoryName, solutionName, projectName, pch, vcpkg, lib, window ) )

    CHECK_FOR_ERROR( AddDependency( repositoryName, projectName, dependencies ) )

    CHECK_FOR_ERROR( MakeSolution( repositoryName, false, true ) )

    return 0;
}

int Make( int const argc, char *argv[] )
{
    if ( argc < 3 ) return 1;

    std::string const& repositoryName = argv[2];
    bool clear = false;
    bool open = false;

    if ( argc != 3 )
    {
        unsigned char startIndex = 3;

        if ( std::string const& argv3 = argv[3];
             argv3[0] != '-' )
            startIndex++;

        for ( unsigned char i = startIndex; i < argc; i++ )
        {
            if ( std::string const& argvi = argv[i]; argvi == "-clear" ) clear = true;
            else if ( argvi == "-open" ) open = true;
            else return 1;
        }

        if ( startIndex == 4 )
        {
            CHECK_FOR_ERROR( MakeSolution( repositoryName, argv[3], clear, open ) )
            return 0;
        }
    }

    SolutionGenerator::CheckVersion( repositoryName );

    CHECK_FOR_ERROR( MakeSolution( repositoryName, clear, open ) )

    return 0;
}

int AddProject( int const argc, char* argv[] )
{
    if ( argc < 4 ) return 1;

    std::string const& repositoryName = argv[2];
    std::string const& projectName = argv[3];
    std::vector<std::string> dependencies;
    bool startup = false;
    bool pch = false;
    bool vcpkg = false;
    bool lib = false;
    bool window = false;

    if ( argc != 4 )
    {
        unsigned char startIndex = 4;

        if ( std::string const& argv4 = argv[4];
             argv4[0] != '-' )
        {
            dependencies.reserve( argc-4 );

            for ( unsigned char i = 4; i < argc; i++, startIndex++ )
            {
                std::string const& argvi = argv[i];
                
                if ( argvi[0] == '-' ) break;
                
                dependencies.push_back( argvi );
            }
        }
        
        for ( unsigned char i = startIndex; i < argc; i++ )
        {
            if ( std::string const& argvi = argv[i]; argvi == "-startup" ) startup = true;
            else if ( argvi == "-pch" ) pch = true;
            else if ( argvi == "-vcpkg" ) vcpkg = true;
            else if ( argvi == "-lib" ) lib = true;
            else if ( argvi == "-window" ) window = true;
            else return 1;
        }
    }

    SolutionGenerator::CheckVersion( repositoryName );

    CHECK_FOR_ERROR( CreateProject( repositoryName, projectName, startup, pch, vcpkg, lib, window ) )

    CHECK_FOR_ERROR( AddDependency( repositoryName, projectName, dependencies ) )

    CHECK_FOR_ERROR( MakeSolution( repositoryName, false, false ) )

    return 0;
}

int AddDependency( int const argc, char* argv[] )
{
    if ( argc < 5 ) return 1;

    std::vector<std::string> dependencies;
    dependencies.reserve( argc-4 );

    for ( unsigned char i = 4; i < argc; i++ )
        dependencies.push_back( argv[i] );

    std::string const& repositoryName = argv[2];

    SolutionGenerator::CheckVersion( repositoryName );

    CHECK_FOR_ERROR( AddDependency( repositoryName, argv[3], dependencies ) )

    return 0;
}


int AddPortVcpkg( int const argc, char* argv[] )
{
    if ( argc < 5 ) return 1;

    std::vector<std::string> ports;
    ports.reserve( argc-4 );

    for ( unsigned char i = 4; i < argc; i++ )
        ports.push_back( argv[i] );

    std::string const& repositoryName = argv[2];

    SolutionGenerator::CheckVersion( repositoryName );

    CHECK_FOR_ERROR( AddPortVcpkg( repositoryName, argv[3], ports ) )

    return 0;
}



int main( int const argc, char *argv[] )
{
    srand( time( nullptr ) );
    
    if ( argc == 1 )
    {
        // SolutionGenerator.exe
        return 0;
    }

    std::string const& action = argv[1];
    if ( action == "-help" ) return Help( argc, argv );
    if ( action == "-create" ) return Create( argc, argv );
    if ( action == "-make") return Make( argc, argv );
    if ( action == "-addProject" ) return AddProject( argc, argv );
    if ( action == "-addDependency" ) return AddDependency( argc, argv );
    if ( action == "-addPort" ) return AddPortVcpkg( argc, argv );

    return 0;
}