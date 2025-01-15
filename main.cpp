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
        std::cout << HELP_MESSAGE;
        return 0;
    }

    ERROR_IF( argc != 3, "Too many arguments\n" )

    if ( std::string const& action = argv[2]; action == "help" || action == "-help" ) std::cout << HELP_HELP;
    else if ( action == "create" || action == "-create" ) std::cout << HELP_CREATE;
    else if ( action == "make" || action == "-make" ) std::cout << HELP_MAKE;
    else if ( action == "add" || action == "-add" ) std::cout << HELP_ADD;
    else if ( action == "edit" || action == "-edit" ) std::cout << HELP_EDIT;
    else if ( action == "rename" || action == "-rename" ) std::cout << HELP_RENAME;
    else if ( action == "addPort" || action == "-addPort" ) std::cout << HELP_ADD_PORT;
    else if ( action == "remove" || action == "-remove" ) std::cout << HELP_REMOVE;
    else { ERROR_IF( true, "Invalid action\n" ) }

    return 0;
}



int Create( int const argc, char *argv[] )
{
    ERROR_IF( argc < 4, "Not enough arguments\n" )

    std::string const& repositoryName = argv[2];
    std::string const& solutionName = argv[3];
    std::string projectName = solutionName;
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

    std::cout << "\n";

    CHECK_FOR_ERROR( MakeSolution( repositoryName, false, true ) )

    return 0;
}



int Make( int const argc, char *argv[] )
{
    ERROR_IF( argc < 3, "Not enough arguments\n" )

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



int Add( int const argc, char* argv[] )
{
    ERROR_IF( argc < 4, "Not enough arguments\n" )

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

            for (; startIndex < argc; startIndex++ )
            {
                std::string const& argvi = argv[startIndex];
                
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

    return 0;
}



int Edit( int const argc, char* argv[] )
{
    ERROR_IF( argc < 5, "Not enough arguments\n" )

    std::string const& repositoryName = argv[2];
    std::string const& projectName = argv[3];
    std::vector<std::string> dependencies;
    bool startup = false;
    bool pch = false;
    bool vcpkg = false;
    bool lib = false;
    bool window = false;

    unsigned char startIndex = 4;

    if ( std::string const& argv4 = argv[4];
         argv4[0] != '-' )
    {
        dependencies.reserve( argc-4 );

        for (; startIndex < argc; startIndex++ )
        {
            std::string const& argvi = argv[startIndex];
                
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

    SolutionGenerator::CheckVersion( repositoryName );

    CHECK_FOR_ERROR( EditProperties( repositoryName, projectName, dependencies, startup, pch, vcpkg, lib, window ) )

    return 0;
}



int Rename( int const argc, char* argv[] )
{
    ERROR_IF( argc != 5, "Not enough arguments\n" )

    std::string const& repositoryName = argv[2];
    std::string const& projectName = argv[3];
    std::string const& newName = argv[4];

    SolutionGenerator::CheckVersion( repositoryName );

    CHECK_FOR_ERROR( RenameProject( repositoryName, projectName, newName ) )
}



int AddPortVcpkg( int const argc, char* argv[] )
{
    ERROR_IF( argc < 5, "Not enough arguments\n" )

    std::string const& repositoryName = argv[2];
    std::vector<std::string> ports;
    ports.reserve( argc-4 );

    for ( unsigned char i = 4; i < argc; i++ )
        ports.push_back( argv[i] );

    SolutionGenerator::CheckVersion( repositoryName );

    CHECK_FOR_ERROR( AddPortVcpkg( repositoryName, argv[3], ports ) )

    return 0;
}



int Remove( int const argc, char* argv[] )
{
    ERROR_IF( argc < 4, "Not enough arguments\n" )
    ERROR_IF( argc > 4, "To many arguments\n" )

    std::string const& repositoryName = argv[2];
    std::string const& projectName = argv[3];

    SolutionGenerator::CheckVersion( repositoryName );

    CHECK_FOR_ERROR( RemoveProject( repositoryName, projectName ) )
    
    return 0;
}



int main( int const argc, char *argv[] )
{
    srand( time( nullptr ) );
    
    if ( argc == 1 )
    {
        // SolutionGenerator.exe
        ERROR_IF( true, "Not enough arguments\n" )
    }
    
    std::string const& action = argv[1];
    if ( action == "-help" ) return Help( argc, argv );
    if ( action == "-create" ) return Create( argc, argv );
    if ( action == "-make") return Make( argc, argv );
    if ( action == "-add" ) return Add( argc, argv );
    if ( action == "-edit" ) return Edit( argc, argv );
    if ( action == "-rename" ) return Rename( argc, argv );
    if ( action == "-addPort" ) return AddPortVcpkg( argc, argv );
    if ( action == "-remove" ) return Remove( argc, argv );

    ERROR_IF( true, "Invalid action\n" )
}