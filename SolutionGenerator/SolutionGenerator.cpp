#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <windows.h>
#include "Utils.h"
#include "Settings.h"
#include "SolutionGenerator.h"
namespace fs = std::filesystem;
namespace SolutionGenerator {



std::string GenerateGuid()
{
    std::string result;
    Utils::NumberToHex( rand(), result );
    Utils::NumberToHex( rand(), result );
    result += '-';
    Utils::NumberToHex( rand(), result );
    result += '-';
    Utils::NumberToHex( rand(), result );
    result += '-';
    Utils::NumberToHex( rand(), result );
    result += '-';
    Utils::NumberToHex( rand(), result );
    Utils::NumberToHex( rand(), result );
    Utils::NumberToHex( rand(), result );
    return result;
}



void CheckVersion( std::string const& repositoryName )
{
    std::string const configPath = repositoryName + "/config/settings.json";
    
    std::ifstream settingsFileRead( configPath );
    nlohmann::json settingsJson = nlohmann::json::parse( settingsFileRead );
    settingsFileRead.close();

    nlohmann::json& version = settingsJson["version"];
    bool versionChanged = false;
    
    if ( version == VERSION ) return;

    if ( version == 1.17 )
    {
        versionChanged = true;

        std::string startupProject = static_cast<std::map<std::string, nlohmann::json>>( settingsJson["projects"] ).begin()->first;

        while ( true )
        {
            std::string answer;
            std::cout << FG_INPUT
                "Your project is being updated to the latest version (" VERSION ")."                    "\n"
                "The startup project was set to " + startupProject + ", do you want to keep it ? (o/n)" "\n" STYLE_RESET;
            std::cin >> answer;

            if ( answer == "o" || answer == "O" ) break;

            if ( answer != "n" && answer != "N" ) continue;

            do {
                std::cout << FG_INPUT "\nPlease, type the name of the project you want to set as the startup project : " STYLE_RESET;
                std::cin >> startupProject;
            } while ( settingsJson["projects"].contains( startupProject ) == false );

            break;
        }
        
        settingsJson["startup_project"] = startupProject;

        CreateBats( repositoryName );
        
        for ( auto const& project : static_cast<std::map<std::string, nlohmann::json>>( settingsJson["projects"] ) )
        {
            if ( project.second["lib"] ) continue;

            CreateBats(repositoryName, project.first );
        }
    }

    if ( versionChanged || version == "1.17.1" )
    {
        versionChanged = true;

        std::map<std::string, nlohmann::json> const& projects = settingsJson["projects"];
        
        for ( auto const& project : projects )
            settingsJson["projects"][project.first]["dependents"] = std::vector<std::string>();

        for ( auto const& project : projects )
        {
            if ( project.second["lib"] && project.second["window"] )
            {
                std::string answer;

                while ( true )
                {
                    std::cout << FG_INPUT "Project (" + project.first + ") has both lib and window enabled which is not supported.\nWhich one do you want to disable ? (lib/window)\n" STYLE_RESET;
                    std::cin >> answer;

                    if ( answer == "lib" )
                    {
                        DisableLibProperty( settingsJson, repositoryName, project.first );
                        break;
                    }

                    if ( answer != "window" ) continue;

                    settingsJson["projects"][project.first]["window"] = false;
                    break;
                }
            }
            
            for ( nlohmann::json const& dependency : project.second["dependencies"] )
            {
                std::string const& dependencyName = dependency;
                if ( settingsJson["projects"][dependencyName]["vcpkg"] && project.second["vcpkg"] == false )
                    EnableVcpkgProperty( settingsJson, repositoryName, project.first );
                settingsJson["projects"][dependencyName]["dependents"].push_back( project.first );
            }    
        }
        // // TODO Add "filters" property to every single project settings
    }

    if ( versionChanged || version == "1.17.2" )
    {
        versionChanged = true;

        for ( auto const& project : static_cast<std::map<std::string, nlohmann::json>>( settingsJson["projects"] ) )
        {
            for ( std::vector<std::string> dependencies = project.second["dependencies"],
                                             dependents = project.second["dependents"];
                  std::string const& dependency : dependencies )
            {
                if ( std::find( dependents.begin(), dependents.end(), dependency ) == dependents.end() )
                {
                    while ( true )
                    {
                        std::string answer;

                        std::cout << FG_INPUT "There is a looping dependency between project " << project.first << " and project " << dependency << "\n"
                                              "From which project do you want to remove the dependency ? (" << project.first << " = 1, " << dependency << " = 2)\n" STYLE_RESET;
                        std::cin >> answer;

                        if ( answer == "1" || answer == project.first )
                        {
                            RemoveDependency( settingsJson, project.first, dependency );
                            break;
                        }

                        if ( answer != "2" && answer != dependency ) continue;

                        RemoveDependency( settingsJson, dependency, project.first );
                        break;
                    }

                    continue;
                }

                if ( dependency == project.first )
                    RemoveDependency( settingsJson, project.first, dependency );
            }
        }
    }

    if ( versionChanged || version == "1.17.3" )
    {
        fs::remove_all( repositoryName + "/bin" );
        fs::create_directory( repositoryName + "/bin" );
        
        CreateBats( repositoryName );
        
        std::map<std::string, nlohmann::json> const& projects = settingsJson["projects"];
        for ( auto const& project : projects )
        {
            settingsJson["projects"][project.first]["preprocessorDefinitions"] = std::vector<std::string>();
            settingsJson["projects"][project.first]["additionalIncludeDirectories"] = std::vector<std::string>();
            settingsJson["projects"][project.first]["additionalLibraryDirectories"] = std::vector<std::string>();
            settingsJson["projects"][project.first]["additionalDependencies"] = std::vector<std::string>();

            if ( project.second["lib"] ) continue;

            CreateBats( repositoryName, project.first );
        }
    }

    version = VERSION;

    std::ofstream settingsFileWrite( configPath );
    settingsFileWrite << std::setw(4) << settingsJson;
    settingsFileWrite.close();

    std::cout << FG_SUCCESS "settings.json updated to version " VERSION "\n" STYLE_RESET;
}






int CreateRepository( std::string const& repositoryName,
                      std::string const& solutionName,
                      std::string const& projectName,
                      bool const pch,
                      bool const vcpkg,
                      bool const lib,
                      bool const window )
{
    ERROR_IF( fs::exists( repositoryName ) == false && fs::create_directory( repositoryName ) == false,
              "Could not create repository folder\n" )

    ERROR_IF( fs::exists( repositoryName + "/src" ),
              "There is already a Solution Generated repository named " + repositoryName + "\n" )

    ERROR_IF( fs::create_directory( repositoryName + "/bin" ) == false, "Could not create bin folder\n" )
    ERROR_IF( fs::create_directory( repositoryName + "/config" ) == false, "Could not create config folder\n" )
    ERROR_IF( fs::create_directory( repositoryName + "/res" ) == false, "Could not create res folder\n" )
    ERROR_IF( fs::create_directory( repositoryName + "/src" ) == false, "Could not create src folder\n" )

    std::ofstream gitignore( repositoryName + "/.gitignore" );
    gitignore << "ide";
    gitignore.close();

    std::cout << FG_SUBSUCCESS ".gitignore created successfully\n" STYLE_RESET;

    std::cout << FG_SUCCESS "Repository (" + repositoryName + ") created successfully\n" STYLE_RESET;

    std::ofstream config( repositoryName + "/config/settings.json" );
    config << CONFIG_SETTINGS( solutionName, GenerateGuid() );
    config.close();

    std::cout << FG_SUBSUCCESS "settings.json created successfully\n" STYLE_RESET;

    ERROR_IF( CreateBats( repositoryName ), "Could not create make.bat file\n" )

    std::cout << FG_SUCCESS "Solution (" + solutionName + ") created successfully\n" STYLE_RESET;

    CHECK_FOR_ERROR( CreateProject( repositoryName, projectName, true, pch, vcpkg, lib, window ) )

    return 0;
}



int CreateBats( std::string const& repositoryName )
{
    std::ofstream makeFileWrite( repositoryName + "/bin/make.bat" );
    makeFileWrite <<
        "cd ../.."                            "\n"
        "SolutionGenerator.exe -make " + repositoryName;
    makeFileWrite.close();

    std::cout << FG_SUBSUCCESS "make.bat created successfully\n" STYLE_RESET;

    std::ofstream makeClearFileWrite( repositoryName + "/bin/make-clear.bat" );
    makeClearFileWrite <<
        "cd ../.."                                       "\n"
        "SolutionGenerator.exe -make " + repositoryName + " -clear";
    makeClearFileWrite.close();

    std::cout << FG_SUBSUCCESS "make-clear.bat created successfully\n" STYLE_RESET;
    
    return 0;
}



int CreateProject( std::string const& repositoryName,
                   std::string const& projectName,
                   bool const startup,
                   bool const pch,
                   bool const vcpkg,
                   bool const lib,
                   bool const window )
{
    ERROR_IF( lib && window, "You can't have a static library project also be a window project\n" )
    
    CHECK_FOR_ERROR( CreateProjectConfig( repositoryName, projectName, startup, pch, vcpkg, lib, window ) )

    CHECK_FOR_ERROR( CreateProjectSrc( repositoryName, projectName, pch, lib, window ) )

    ERROR_IF( fs::create_directory( repositoryName + "/res/" + projectName ) == false,
              "Could not create project (" + projectName + ") res folder\n" )

    if ( lib == false ) CHECK_FOR_ERROR( CreateBats( repositoryName, projectName ) )

    std::cout << FG_SUCCESS "Project (" + projectName + ") created successfully\n" STYLE_RESET;

    return 0;
}



int RenameProject( std::string const& repositoryName,
                   std::string const& projectName,
                   std::string const& newName )
{
    std::string const configPath = repositoryName + "/config";
    std::string const settingsPath = configPath + "/settings.json";

    std::ifstream settingsFileRead( settingsPath );
    nlohmann::json settingsJson = nlohmann::json::parse( settingsFileRead );
    settingsFileRead.close();

    ERROR_IF( settingsJson["projects"].contains( projectName ) == false, "Project (" + projectName + ") doesn't exist in this repository (" + repositoryName + ")\n" )
    ERROR_IF( settingsJson["projects"].contains( newName ), "Project (" + newName + ") already exists in this repository (" + repositoryName + ")\n" )
    ERROR_IF( projectName == newName, "The name " + projectName + " is the same as " + newName + "...\n" )

    settingsJson["projects"][newName] = settingsJson["projects"][projectName];
    settingsJson["projects"].erase( projectName );

    for ( nlohmann::json const& dependent : settingsJson["projects"][newName]["dependents"] )
    {
        std::vector<std::string> dependencies = settingsJson["projects"][dependent]["dependencies"];
        std::replace( dependencies.begin(), dependencies.end(), projectName, newName );
    }

    for ( nlohmann::json const& dependent : settingsJson["projects"][newName]["dependencies"] )
    {
        std::vector<std::string> dependents = settingsJson["projects"][dependent]["dependents"];
        std::replace( dependents.begin(), dependents.end(), projectName, newName );
    }

    std::error_code error;
    fs::rename( repositoryName + "/src/" + projectName, repositoryName + "/src/" + newName, error );
    ERROR_IF( error, "Project (" + projectName + ")'s src folder could not be renamed\n" )

    fs::rename( repositoryName + "/res/" + projectName, repositoryName + "/res/" + newName, error );
    ERROR_IF( error, "Project (" + projectName + ")'s res folder could not be renamed\n" )

    if ( settingsJson["projects"][newName]["vcpkg"] )
    {
        fs::rename( configPath + "/" + projectName, configPath + "/" + newName, error );
        ERROR_IF( error, "Project (" + projectName + ")'s config folder could not be renamed\n" )
    }

    if ( settingsJson["projects"][newName]["lib"] == false )
    {
        std::string projectNameLowerCase = projectName;
        std::string newNameLowerCase = newName;
        std::transform( projectNameLowerCase.begin(), projectNameLowerCase.end(), projectNameLowerCase.begin(), [](unsigned char const c){ return std::tolower(c); } );
        std::transform( newNameLowerCase.begin(), newNameLowerCase.end(), newNameLowerCase.begin(), [](unsigned char const c){ return std::tolower(c); } );
        
        ERROR_IF( fs::remove( repositoryName + "/bin/make-" + projectNameLowerCase + ".bat" ) == false, "Project (" + projectName + ")'s make.bat could not be deleted\n" )
        ERROR_IF( fs::remove( repositoryName + "/bin/make-" + projectNameLowerCase + "-clear.bat" ) == false, "Project (" + projectName + ")'s make-clear.bat could not be deleted\n" )

        CHECK_FOR_ERROR( CreateBats( repositoryName, newName ) )
    }

    std::ofstream settingsFileWrite( settingsPath );
    settingsFileWrite << std::setw(4) << settingsJson;
    settingsFileWrite.close();

    std::cout << FG_SUCCESS "Project (" + projectName + ") was renamed " + newName + " successfully\n" STYLE_RESET;

    return 0;
}



int RemoveProject( std::string const& repositoryName,
                   std::string const& projectName )
{
    std::string const settingsPath = repositoryName + "/config/settings.json";

    std::ifstream settingsFileRead( settingsPath );
    nlohmann::json settingsJson = nlohmann::json::parse( settingsFileRead );
    settingsFileRead.close();

    ERROR_IF( settingsJson["projects"].size() == 1, "Project (" + projectName + ") can't be removed because it's the last project of the solution\n" )
    ERROR_IF( settingsJson["projects"].contains( projectName ) == false, "Project (" + projectName + ") doesn't exist in this repository (" + repositoryName + ")\n" )

    if ( std::vector<std::string> const& dependents = settingsJson["projects"][projectName]["dependents"];
         dependents.empty() == false )
    {
        while ( true )
        {
            std::string answer;
            std::cout << FG_INPUT "Project (" + projectName + ") has dependents, do you wish to continue and remove their dependency to this project ? (o/n)\n" STYLE_RESET;
            std::cin >> answer;

            if ( answer == "o" || answer == "O" ) break;

            if ( answer != "n" && answer != "N" ) continue;

            return 1;
        }

        for ( std::string const& dependent : dependents )
            CHECK_FOR_ERROR( RemoveDependency( settingsJson, dependent, projectName ) )
    }

    CHECK_FOR_ERROR( RemoveDependency( repositoryName, projectName, settingsJson["projects"][projectName]["dependencies"] ) )

    if ( settingsJson["projects"][projectName]["vcpkg"] ) CHECK_FOR_ERROR( DisableVcpkgProperty( settingsJson, repositoryName, projectName ) )
    
    std::error_code error;
    fs::remove_all( repositoryName + "/src/" + projectName, error );
    ERROR_IF( error, "Could not delete project (" + projectName + ")'s src folder\n" )
        
    std::cout << FG_SUBSUCCESS "Project (" + projectName + ")'s src folder deleted successfully\n" STYLE_RESET;

    fs::remove_all( repositoryName + "/res/" + projectName, error );
    ERROR_IF( error, "Could not delete project (" + projectName + ")'s res folder\n" )
        
    std::cout << FG_SUBSUCCESS "Project (" + projectName + ")'s res folder deleted successfully\n" STYLE_RESET;

    if ( settingsJson["projects"][projectName]["lib"] == false )
        CHECK_FOR_ERROR( DeleteBats( repositoryName, projectName ) )

    settingsJson["projects"].erase( projectName );

    if ( settingsJson["startup_project"] == projectName )
        settingsJson["startup_project"] = static_cast<std::map<std::string, nlohmann::json>>( settingsJson["projects"] ).begin()->first;

    std::ofstream settingsFileWrite( settingsPath );
    settingsFileWrite << std::setw(4) << settingsJson;
    settingsFileWrite.close();
    
    std::cout << FG_SUCCESS "Project (" + projectName + ") successfully deleted\n" STYLE_RESET;
    
    return 0;
}



int CreateBats( std::string const& repositoryName,
                std::string const& projectName )
{
    std::string projectNameLowerCase = projectName;
    std::transform( projectNameLowerCase.begin(), projectNameLowerCase.end(), projectNameLowerCase.begin(), [](unsigned char const c){ return std::tolower(c); } );
    
    std::ofstream makeFileWrite( repositoryName + "/bin/make-" + projectNameLowerCase + ".bat" );
    makeFileWrite <<
        "cd ../.."                                                "\n"
        "SolutionGenerator.exe -make " + repositoryName + " " + projectName;
    makeFileWrite.close();

    std::cout << FG_SUBSUCCESS "make-" + projectNameLowerCase + ".bat created successfully\n" STYLE_RESET;

    std::ofstream makeClearFileWrite( repositoryName + "/bin/make-" + projectNameLowerCase + "-clear.bat" );
    makeClearFileWrite <<
        "cd ../.."                                                           "\n"
        "SolutionGenerator.exe -make " + repositoryName + " " + projectName + " -clear";
    makeClearFileWrite.close();

    std::cout << FG_SUBSUCCESS "make-" + projectNameLowerCase + "-clear.bat created successfully\n" STYLE_RESET;

    return 0;
}



int DeleteBats( std::string const& repositoryName,
                std::string const& projectName )
{
    std::string projectNameLowerCase = projectName;
    std::transform( projectNameLowerCase.begin(), projectNameLowerCase.end(), projectNameLowerCase.begin(), [](unsigned char const c){ return std::tolower(c); } );

    if ( std::string const makeBatPath = repositoryName + "/bin/make-" + projectNameLowerCase + ".bat";
         fs::exists( makeBatPath ) )
    {
        ERROR_IF( fs::remove( makeBatPath ) == false, "Could not delete make-" + projectNameLowerCase + ".bat\n" )
        std::cout << FG_SUBSUCCESS "make-" + projectNameLowerCase + ".bat deleted successfully\n" STYLE_RESET;
    }

    if ( std::string const makeClearBatPath = repositoryName + "/bin/make-" + projectNameLowerCase + "-clear.bat";
         fs::exists( makeClearBatPath ) )
    {
        ERROR_IF( fs::remove( makeClearBatPath ) == false, "Could not delete make-" + projectNameLowerCase + "-clear.bat\n" )
        std::cout << FG_SUBSUCCESS "make-" + projectNameLowerCase + "-clear.bat deleted successfully\n" STYLE_RESET;
    }

    return 0;
}



int CreateProjectConfig( std::string const& repositoryName,
                         std::string const& projectName,
                         bool const startup,
                         bool const pch,
                         bool const vcpkg,
                         bool const lib,
                         bool const window )
{
    std::string const settingsPath = repositoryName + "/config/settings.json";
    
    std::ifstream settingsFileRead( settingsPath );
    nlohmann::json settingsJson = nlohmann::json::parse( settingsFileRead );
    settingsFileRead.close();

    ERROR_IF( settingsJson["projects"].contains( projectName ), "Project (" + projectName + ") already exists in this repository (" + repositoryName + ")\n" )

    if ( vcpkg ) CHECK_FOR_ERROR( CreateVcpkgJson( repositoryName, projectName ) )

    std::string guid = GenerateGuid();

    settingsJson["projects"][projectName] = nlohmann::json::parse( PROJECT_CONFIG );
    settingsJson["projects"][projectName]["guid"] = guid;
    settingsJson["projects"][projectName]["pch"] = pch;
    settingsJson["projects"][projectName]["vcpkg"] = vcpkg;
    settingsJson["projects"][projectName]["lib"] = lib;
    settingsJson["projects"][projectName]["window"] = window;

    std::ofstream settingsFileWrite( settingsPath );
    settingsFileWrite << std::setw(4) << settingsJson;
    settingsFileWrite.close();

    std::cout << FG_SUBSUCCESS "Project (" + projectName + ") successfully added to settings.json\n" STYLE_RESET;

    if ( startup ) CHECK_FOR_ERROR( EditProperties( repositoryName, projectName, std::vector<std::string>(), true, false, false, false, false ) )

    return 0;
}



int CreateVcpkgJson( std::string const& repositoryName,
                     std::string const& projectName )
{
    std::string const configPath = repositoryName + "/config";
    std::string const projectConfigPath = configPath + "/" + projectName;

    if ( std::string const vcpkgConfigPath = configPath + "/vcpkg-configuration.json";
         fs::exists( vcpkgConfigPath ) == false )
    {
        std::ofstream vcpkgConfigurationFileWrite( vcpkgConfigPath );
        vcpkgConfigurationFileWrite << VCPKG_CONFIGURATION;
        vcpkgConfigurationFileWrite.close();

        std::cout << FG_SUBSUCCESS "vcpkg-configuration.json created successfully\n" STYLE_RESET;
    }

    ERROR_IF( fs::exists( projectConfigPath ) == false && fs::create_directory( projectConfigPath ) == false,
              "Could not create project (" + projectName + ") config folder\n" )

    std::ofstream vcpkgFileWrite( projectConfigPath + "/vcpkg.json" );
    vcpkgFileWrite << VCPKG_JSON;
    vcpkgFileWrite.close();

    std::cout << FG_SUBSUCCESS "Project (" + projectName + ")'s vcpkg.json created successfully\n" STYLE_RESET;

    return 0;
}



int CreateProjectSrc( std::string const& repositoryName,
                      std::string const& projectName,
                      bool const pch,
                      bool const lib,
                      bool const window )
{
    std::string const srcPath = repositoryName + "/src/" + projectName;

    ERROR_IF( fs::create_directory( srcPath ) == false,
              "Could not create project (" + projectName + ") src folder\n" )

    std::string maincppContent;

    if ( pch ) // pch == true
    {
        std::string pchhContent;

        if ( window ) // window == true
        {
            pchhContent = PCH_H_WINDOW;
            maincppContent = MAIN_CPP_PCH_WINDOW;
        }
        else // window == false
        {
            pchhContent = PCH_H;
            maincppContent = MAIN_CPP_PCH;
        }

        std::ofstream pchhFileWrite( srcPath + "/pch.h" );
        pchhFileWrite << pchhContent;
        pchhFileWrite.close();

        std::cout << FG_SUBSUCCESS "Project (" + projectName + ") pch.h created successfully\n" STYLE_RESET;

        std::ofstream pchcppFileWrite( srcPath + "/pch.cpp" );
        pchcppFileWrite << PCH_CPP;
        pchcppFileWrite.close();

        std::cout << FG_SUBSUCCESS "Project (" + projectName + ") pch.cpp created successfully\n" STYLE_RESET;
    }
    else maincppContent = window ? MAIN_CPP_WINDOW : MAIN_CPP; // pch == false

    if ( lib == false ) // lib == false
    {
        std::ofstream mainhFileWrite( srcPath + "/main.h" );
        mainhFileWrite << MAIN_H;
        mainhFileWrite.close();

        std::cout << FG_SUBSUCCESS "Project (" + projectName + ") main.h created successfully\n" STYLE_RESET;

        std::ofstream maincppFileWrite( srcPath + "/main.cpp" );
        maincppFileWrite << maincppContent;
        maincppFileWrite.close();

        std::cout << FG_SUBSUCCESS "Project (" + projectName + ") main.cpp created successfully\n" STYLE_RESET;
    }
    
    return 0;
}






int EditProperties( std::string const& repositoryName,
                    std::string const& projectName,
                    std::vector<std::string> const& dependencies,
                    bool const startup,
                    bool const changePch,
                    bool const changeVcpkg,
                    bool const changeLib,
                    bool const changeWindow )
{
    std::string const settingsPath = repositoryName + "/config/settings.json";

    std::ifstream settingsFileRead( settingsPath );
    nlohmann::json settingsJson = nlohmann::json::parse( settingsFileRead );
    settingsFileRead.close();

    if ( startup )
    {
        settingsJson["startup_project"] = projectName;
        std::cout << FG_SUBSUCCESS "Project (" + projectName + ") successfully set as startup project\n" STYLE_RESET;
    }

    for ( std::string const& dependency : dependencies )
    {
        bool alreadyDependent = false;

        for ( nlohmann::json const& currentDependency : settingsJson["projects"][projectName]["dependencies"] )
            if ( static_cast<std::string>( currentDependency ) == dependency )
                alreadyDependent = true;

        if ( alreadyDependent )
        {
            CHECK_FOR_ERROR( RemoveDependency( settingsJson, projectName, dependency ) )
            continue;
        }

        CHECK_FOR_ERROR( AddDependency( settingsJson, repositoryName, projectName, dependency ) )
    }

    bool const pch = settingsJson["projects"][projectName]["pch"];
    bool const vcpkg = settingsJson["projects"][projectName]["vcpkg"];
    bool const lib = settingsJson["projects"][projectName]["lib"];
    bool window = settingsJson["projects"][projectName]["window"];

    ERROR_IF( ( ( changeLib == false && lib ) || ( changeLib && lib == false ) ) && ( ( changeWindow == false && window ) || ( changeWindow && window == false ) ),
              "You can't have a static library project also be a window project\n" )

    if ( changeWindow )
    {
        window = window == false;
        settingsJson["projects"][projectName]["window"] = window;
    }

    if ( changePch )
    {
        if ( pch == false ) { CHECK_FOR_ERROR( EnablePchProperty( settingsJson, repositoryName, projectName, window ) ) }
        else { CHECK_FOR_ERROR( DisablePchProperty( settingsJson, repositoryName, projectName ) ) }
    }

    if ( changeVcpkg )
    {
        if ( vcpkg == false ) { CHECK_FOR_ERROR( EnableVcpkgProperty( settingsJson, repositoryName, projectName ) ) }
        else { CHECK_FOR_ERROR( DisableVcpkgProperty( settingsJson, repositoryName, projectName ) ) }
    }

    if ( changeLib )
    {
        if ( lib == false ) { CHECK_FOR_ERROR( EnableLibProperty( settingsJson, repositoryName, projectName ) ) }
        else { CHECK_FOR_ERROR( DisableLibProperty( settingsJson, repositoryName, projectName ) ) }
    }

    std::ofstream settingsFileWrite( settingsPath );
    settingsFileWrite << std::setw(4) << settingsJson;
    settingsFileWrite.close();

    return 0;
}



int EnablePchProperty( nlohmann::json& settingsJson,
                       std::string const& repositoryName,
                       std::string const& projectName,
                       bool const window )
{
    std::string const srcPath = repositoryName + "/src/" + projectName;
    
    if ( std::string const pchhPath = srcPath + "/pch.h";
         fs::exists( pchhPath ) == false )
    {
        std::ofstream pchhFileWrite( pchhPath );
        pchhFileWrite << ( window ? PCH_H_WINDOW : PCH_H );
        pchhFileWrite.close();

        std::cout << FG_SUBSUCCESS "Project (" + projectName + ")'s pch.h created successfully\n" STYLE_RESET;
    }

    if ( std::string const pchcppPath = srcPath + "/pch.cpp";
         fs::exists( pchcppPath ) == false )
    {
        std::ofstream pchcppFileWrite( pchcppPath );
        pchcppFileWrite << PCH_CPP;
        pchcppFileWrite.close();

        std::cout << FG_SUBSUCCESS "Project (" + projectName + ")'s pch.cpp created successfully\n" STYLE_RESET;
    }

    settingsJson["projects"][projectName]["pch"] = true;

    // std::cout << FG_SUCCESS "Project (" + projectName + ")'s pch enabled successfully\n" STYLE_RESET;

    return 0;
}



int DisablePchProperty( nlohmann::json& settingsJson,
                        std::string const& repositoryName,
                        std::string const& projectName )
{
    std::string answer;

    while ( true )
    {
        std::cout << FG_INPUT "Do you want to delete the pch.h and pch.cpp files ? (o/n)\n" STYLE_RESET;
        std::cin >> answer;

        if ( answer == "o" || answer == "O" ) break;

        if ( answer != "n" && answer != "N" ) continue;

        settingsJson["projects"][projectName]["pch"] = false;

        return 0;
    }

    std::string const srcPath = repositoryName + "/src/" + projectName;

    if ( std::string const pchhPath = srcPath + "/pch.h";
         fs::exists( pchhPath ) )
    {
        ERROR_IF( fs::remove( pchhPath ) == false, "Could not delete project (" + projectName + ")'s pch.h\n" )
        std::cout << FG_SUBSUCCESS "Project (" + projectName + ")'s pch.h deleted successfully\n" STYLE_RESET;
    }
            
    if ( std::string const pchcppPath = srcPath + "/pch.cpp";
         fs::exists( pchcppPath ) )
    {
        ERROR_IF( fs::remove( pchcppPath ) == false, "Could not delete project (" + projectName + ")'s pch.cpp\n" )
        std::cout << FG_SUBSUCCESS "Project (" + projectName + ")'s pch.cpp deleted successfully\n" STYLE_RESET;
    }

    settingsJson["projects"][projectName]["pch"] = false;

    // std::cout << FG_SUCCESS "Project (" + projectName + ")'s pch disabled successfully\n" STYLE_RESET;

    return 0;
}



int EnableVcpkgProperty( nlohmann::json& settingsJson,
                         std::string const& repositoryName,
                         std::string const& projectName )
{
    CHECK_FOR_ERROR( CreateVcpkgJson( repositoryName, projectName ) )

    settingsJson["projects"][projectName]["vcpkg"] = true;

    for ( nlohmann::json const& dependent : settingsJson["projects"][projectName]["dependents"] )
        if ( settingsJson["projects"][dependent]["vcpkg"] == false )
            CHECK_FOR_ERROR( EnableVcpkgProperty( settingsJson, repositoryName, dependent ) )

    return 0;
}



int DisableVcpkgProperty( nlohmann::json& settingsJson,
                          std::string const& repositoryName,
                          std::string const& projectName )
{
    for ( nlohmann::json const& dependency : settingsJson["projects"][projectName]["dependencies"] )
    {
        std::string const& dependencyName = dependency;
        ERROR_IF( settingsJson["projects"][dependencyName]["vcpkg"], "You cannot disable project (" + projectName + ")'s vcpkg because it has a dependency that requires vcpkg (" + dependencyName + ")\n" )
    }
    
    if ( std::string const projectConfigPath = repositoryName + "/config/" + projectName;
         fs::exists( projectConfigPath ) )
    {
        std::error_code error;
        fs::remove_all( projectConfigPath, error ); // TODO CHANGE IF I ADD MORE STUFF TO THE PROJECT CONFIG FOLDER
        ERROR_IF( error, "Could not delete project (" + projectName + ")'s vcpkg.json\n" )
        
        std::cout << FG_SUBSUCCESS "Project (" + projectName + ")'s vcpkg.json deleted successfully\n" STYLE_RESET;
    }

    settingsJson["projects"][projectName]["vcpkg"] = false;

    // std::cout << FG_SUCCESS "Project (" + projectName + ")'s vcpkg disabled successfully\n" STYLE_RESET;

    return 0;
}



int EnableLibProperty( nlohmann::json& settingsJson,
                       std::string const& repositoryName,
                       std::string const& projectName )
{
    CHECK_FOR_ERROR( DeleteBats( repositoryName, projectName ) )

    settingsJson["projects"][projectName]["lib"] = true;
    
    return 0;
}



int DisableLibProperty( nlohmann::json& settingsJson,
                        std::string const& repositoryName,
                        std::string const& projectName )
{
    CHECK_FOR_ERROR( CreateBats( repositoryName, projectName ) )
            
    settingsJson["projects"][projectName]["lib"] = false;
    
    return 0;
}



int AddDependency( nlohmann::json& settingsJson,
                   std::string const& repositoryName,
                   std::string const& projectName,
                   std::string const& dependency )
{
    std::vector<std::string> dependencyDependencies = settingsJson["projects"][dependency]["dependencies"];
    ERROR_IF( settingsJson["projects"][dependency]["lib"] == false, "You can't add a non-library project (" + dependency + ") as a dependency\n" )
    ERROR_IF( std::find( dependencyDependencies.begin(), dependencyDependencies.end(), projectName ) != dependencyDependencies.end(), "Projects can't have looping dependencies (project " + dependency + " already depends on project " + projectName + ")\n" )
    ERROR_IF( dependency == projectName, "You can't make a project (" + projectName + ") depends on itself\n" )

    if ( settingsJson["projects"][dependency]["vcpkg"] && settingsJson["projects"][projectName]["vcpkg"] == false )
        CHECK_FOR_ERROR( EnableVcpkgProperty( settingsJson, repositoryName, projectName ) )

    settingsJson["projects"][projectName]["dependencies"].push_back( dependency );
    settingsJson["projects"][dependency]["dependents"].push_back( projectName );

    std::cout << FG_SUCCESS "Project (" + projectName + ") successfully added project (" + dependency + ") as a dependency\n" STYLE_RESET;

    return 0;
}



int AddDependency( std::string const& repositoryName,
                   std::string const& projectName,
                   std::vector<std::string> const& dependencies )
{
    std::string const settingsPath = repositoryName + "/config/settings.json";

    std::ifstream settingsFileRead( settingsPath );
    nlohmann::json settingsJson = nlohmann::json::parse( settingsFileRead );
    settingsFileRead.close();

    for ( std::string const& dependency : dependencies )
        CHECK_FOR_ERROR( AddDependency( settingsJson, repositoryName, projectName, dependency ) )

    std::ofstream settingsFileWrite( settingsPath );
    settingsFileWrite << std::setw(4) << settingsJson;
    settingsFileWrite.close();

    return 0;
}



int RemoveDependency( nlohmann::json& settingsJson,
                      std::string const& projectName,
                      std::string const& dependency )
{
    std::vector<std::string> dependencies = settingsJson["projects"][projectName]["dependencies"];
    dependencies.erase( std::remove( dependencies.begin(), dependencies.end(), dependency ), dependencies.end() );
    settingsJson["projects"][projectName]["dependencies"] = dependencies;

    std::vector<std::string> dependents = settingsJson["projects"][dependency]["dependents"];
    dependents.erase( std::remove( dependents.begin(), dependents.end(), projectName ), dependents.end() );
    settingsJson["projects"][dependency]["dependents"] = dependents;

    std::cout << FG_SUCCESS "Project (" + projectName + ") successfully removed project (" + dependency + ") as a dependency\n" STYLE_RESET;
    
    return 0;
}



int RemoveDependency( std::string const& repositoryName,
                      std::string const& projectName,
                      std::vector<std::string> const& dependencies )
{
    std::string const settingsPath = repositoryName + "/config/settings.json";

    std::ifstream settingsFileRead( settingsPath );
    nlohmann::json settingsJson = nlohmann::json::parse( settingsFileRead );
    settingsFileRead.close();

    for ( std::string const& dependency : dependencies )
        CHECK_FOR_ERROR( RemoveDependency( settingsJson, projectName, dependency ) )

    std::ofstream settingsFileWrite( settingsPath );
    settingsFileWrite << std::setw(4) << settingsJson;
    settingsFileWrite.close();

    return 0;
}



int AddPortVcpkg( nlohmann::json& settingsJson,
                  nlohmann::json& vcpkgJson,
                  std::string const& repositoryName,
                  std::string const& projectName,
                  std::string const& port )
{
    if ( settingsJson["projects"][projectName]["vcpkg"] == false )
        CHECK_FOR_ERROR( EnableVcpkgProperty( settingsJson, repositoryName, projectName ) )

    for ( auto const& existingPort : vcpkgJson["dependencies"] )
        ERROR_IF( static_cast<std::string>( existingPort ) == port,
                  "Port (" + port + ") is already added to project (" + projectName + ")\n" )

    vcpkgJson["dependencies"].push_back( port );

    std::cout << FG_SUBSUCCESS "Port (" + port + ") successfully added to project (" + projectName + ")\n" STYLE_RESET;

    return 0;
}



int AddPortVcpkg( std::string const& repositoryName,
                  std::string const& projectName,
                  std::vector<std::string> const& ports )
{
    std::ifstream settingsFileRead( repositoryName + "/config/settings.json" );
    nlohmann::json settingsJson = nlohmann::json::parse( settingsFileRead );
    settingsFileRead.close();

    std::ifstream vcpkgFileRead( repositoryName + "/config/" + projectName + "/vcpkg.json" );
    nlohmann::json vcpkgJson = nlohmann::json::parse( vcpkgFileRead );
    vcpkgFileRead.close();
    
    for ( std::string const& port : ports )
        CHECK_FOR_ERROR( AddPortVcpkg( settingsJson, vcpkgJson, repositoryName, projectName, port ) )

    std::ofstream vcpkgFileWrite( repositoryName + "/config/" + projectName + "/vcpkg.json" );
    vcpkgFileWrite << std::setw(4) << vcpkgJson;
    vcpkgFileWrite.close();

    return 0;
}






int MakeSolution( std::string const& repositoryName,
                  bool const clear,
                  bool const open )
{
    std::ifstream settingsFile( repositoryName + "/config/settings.json" );
    nlohmann::json settingsJson = nlohmann::json::parse( settingsFile );
    settingsFile.close();

    std::vector<std::array<std::string, 2>> projects;
    for ( auto const& project : static_cast<std::map<std::string, nlohmann::json>>( settingsJson["projects"] ) )
    {
        std::string const& projectName = project.first;

        if ( settingsJson["startup_project"] == projectName )
        {
            projects.insert( projects.begin(), std::array{ projectName, static_cast<std::string>( project.second["guid"] ) } );
            continue;
        }

        projects.push_back( std::array{ projectName, static_cast<std::string>( project.second["guid"] ) } );
    }

    CHECK_FOR_ERROR( MakeSolution( repositoryName, projects, settingsJson, clear, open ) )

    return 0;
}



int MakeSolution( std::string const& repositoryName,
                  std::string const& projectName,
                  bool const clear,
                  bool const open )
{
    std::ifstream settingsFile( repositoryName + "/config/settings.json" );
    nlohmann::json settingsJson = nlohmann::json::parse( settingsFile );
    settingsFile.close();

    std::vector projects { std::array{ projectName, static_cast<std::string>( settingsJson["projects"][projectName]["guid"] ) } };
    for ( nlohmann::basic_json<> const& dependency: settingsJson["projects"][projectName]["dependencies"] )
    {
        std::string const& dependencyName = dependency;
        projects.push_back( std::array{ dependencyName, static_cast<std::string>( settingsJson["projects"][dependencyName]["guid"] ) } );
    }

    CHECK_FOR_ERROR( MakeSolution( repositoryName, projects, settingsJson, clear, open ) )

    return 0;
}



int MakeSolution( std::string const& repositoryName,
                  std::vector<std::array<std::string, 2>>& projects,
                  nlohmann::json const& settingsJson,
                  bool const clear,
                  bool const open )
{
    if ( std::string const idePath = repositoryName + "/ide";
        fs::exists( idePath ) )
    {
        if ( clear )
        {
            std::error_code error;
            fs::remove_all( idePath, error );
            ERROR_IF( error, "Could not delete ide folder\n" )

            std::cout << FG_SUBSUCCESS "ide folder deleted successfully\n" STYLE_RESET;

            ERROR_IF( fs::create_directory( idePath ) == false, "Could not create ide folder\n" )
        }
    }
    else ERROR_IF( fs::create_directory( idePath ) == false, "Could not create ide folder\n" )

    std::string projectsForSln;
    std::string globalSection;

    for ( std::array<std::string, 2> const& project : projects )
    {
        std::string const& projectName = project[0];
        std::string const& projectGui = project[1];

        CHECK_FOR_ERROR( MakeProject( repositoryName, projectName, settingsJson ) )
    
        projectsForSln += "Project(\"{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}\") = \"" + projectName + "\", \"" + projectName + "\\" + projectName + ".vcxproj\", \"{" + projectGui + "}\""                 "\n";
        AddDependenciesToSln( settingsJson, projectName, projectsForSln, projects );
        projectsForSln += "EndProject"                                                                                                                                                                    "\n";
    
        globalSection += PROJECT_GLOBAL_SECTION( projectGui );
    }

    std::string const& solutionName = settingsJson[ "solution_name" ];
    std::string const& solutionGuid = settingsJson[ "solution_guid" ];
    
    std::ofstream sln( repositoryName + "/ide/" + solutionName + ".sln" );
    sln << SLN( projectsForSln, globalSection, solutionGuid );
    sln.close();
    
    std::cout << FG_SUBSUCCESS + solutionName + ".sln created successfully\n" STYLE_RESET;
    
    std::cout << FG_SUCCESS "Solution (" + solutionName + ") made (-make) successfully\n" STYLE_RESET;

    if ( open ) ShellExecuteA( nullptr, "open", fs::absolute( repositoryName + "/ide" ).string().c_str(), nullptr, nullptr, SW_SHOWNORMAL );

    return 0;
}



int AddDependenciesToSln( nlohmann::json const& settingsJson,
                          std::string const& projectName,
                          std::string& projectsForSln,
                          std::vector<std::array<std::string, 2>>& projects )
{
    nlohmann::json const& dependencies = settingsJson["projects"][projectName]["dependencies"];

    if ( dependencies.empty() ) return 0;
    
    projectsForSln += "\t""ProjectSection(ProjectDependencies) = postProject"                                                                                                                             "\n";
    for ( nlohmann::json const& dependency: dependencies )
    {
        std::string const& dependencyName = dependency;
        std::string const& dependencyGui = settingsJson["projects"][dependencyName]["guid"];
        projectsForSln += "\t""\t""{" + dependencyGui + "} = {" + dependencyGui + "}"                                                                                                                     "\n";

        bool alreadyAdded = false;
        for ( std::array<std::string, 2> const& project : projects )
        {
            if ( project[0] != dependencyName ) continue;
        
            alreadyAdded = true;
            break;
        }

        if ( alreadyAdded ) continue;

        projects.push_back( std::array{ dependencyName, dependencyGui } );
    }
    projectsForSln += "\t""EndProjectSection"                                                                                                                                                             "\n";

    return 0;
}



int MakeProject( std::string const& repositoryName,
                 std::string const& projectName,
                 nlohmann::json const& settingsJson )
{
    std::string const ideProjectPath = repositoryName + "/ide/" + projectName;

    ERROR_IF( fs::exists( ideProjectPath ) == false && fs::create_directory( ideProjectPath ) == false,
              "Could not create ide project (" + projectName + ") folder\n" )

    std::string const& guid = settingsJson["projects"][projectName]["guid"];

    bool const pch = settingsJson["projects"][projectName]["pch"];
    bool const vcpkg = settingsJson["projects"][projectName]["vcpkg"];
    bool const lib = settingsJson["projects"][projectName]["lib"];
    bool const window = settingsJson["projects"][projectName]["window"];

    std::string const precompiledHeader = pch ? "Use" : "NotUsing";
    std::string const vcpkgEnabled = vcpkg ? "true" : "false";
    std::string const configurationType = lib ? "StaticLibrary" : "Application";
    std::string preprocessorDefinitions = window ? ( lib ? "_LIB;" : "_WINDOWS;" ) : "_CONSOLE;";
    std::string const subSystem = window ? "Windows" : "Console";

    std::string additionalIncludeDirectories;
    std::string additionalLibraryDirectories;
    std::string additionalDependencies;
    std::string projectReferences;

    std::vector<std::string> const& preprocessorDefinitionsList = settingsJson["projects"][projectName]["preprocessorDefinitions"];
    for ( std::string const& preprocessorDefinition : preprocessorDefinitionsList )
        preprocessorDefinitions += preprocessorDefinition + ";";

    std::vector<std::string> const& additionalIncludeDirectoriesList = settingsJson["projects"][projectName]["additionalIncludeDirectories"];
    for ( std::string const& additionalIncludeDirectory : additionalIncludeDirectoriesList )
        additionalIncludeDirectories += additionalIncludeDirectory + ";";

    std::vector<std::string> const& additionalLibraryDirectoriesList = settingsJson["projects"][projectName]["additionalLibraryDirectories"];
    for ( std::string const& additionalLibraryDirectory : additionalLibraryDirectoriesList )
        additionalLibraryDirectories += additionalLibraryDirectory + ";";

    std::vector<std::string> const& additionalDependenciesList = settingsJson["projects"][projectName]["additionalDependencies"];
    for ( std::string const& additionalDependency : additionalDependenciesList )
        additionalDependencies += additionalDependency + ";";

    for ( nlohmann::json const& dependency : settingsJson["projects"][projectName]["dependencies"] )
    {
        std::string const& dependencyName = dependency;
        std::string const& dependencyGuid = settingsJson["projects"][dependencyName]["guid"];

        additionalIncludeDirectories += "$(SolutionDir)..\\src\\" + dependencyName + ";";
        additionalLibraryDirectories += "$(SolutionDir)" + dependencyName + "\\$(Platform)\\$(Configuration);";
        additionalDependencies += dependencyName + ".lib;";

        projectReferences +=
            "        <ProjectReference Include=\"$(SolutionDir)\\" + dependencyName + "\\" + dependencyName + ".vcxproj\">"                                                                               "\n"
            "            <Project>{" + dependencyGuid + "}</Project>"                                                                                                                                     "\n"
            "        </ProjectReference>"                                                                                                                                                                 "\n";
    }

    std::string clIncludes;
    std::string clCompiles;
    std::string clIncludesFilters;
    std::string clCompilesFilters;
    
    CHECK_FOR_ERROR( AddSrcToVcxproj( repositoryName + "\\src\\", projectName, clIncludes, clCompiles, clIncludesFilters, clCompilesFilters ) )
    
    std::string images;
    std::string nones;
    std::string imagesFilters;
    std::string nonesFilters;

    CHECK_FOR_ERROR( AddResToVcxproj( repositoryName + "\\res\\", projectName, images, nones, imagesFilters, nonesFilters ) )

    std::string const vcxprojPath = ideProjectPath + "/" + projectName + ".vcxproj";
    
    std::ofstream vcxprojFileWrite( vcxprojPath );
    vcxprojFileWrite << VCXPROJ(
        guid,
        configurationType,
        vcpkgEnabled,
        projectName,
        preprocessorDefinitions,
        precompiledHeader,
        additionalIncludeDirectories,
        subSystem,
        additionalLibraryDirectories,
        additionalDependencies,
        clIncludes,
        clCompiles,
        images,
        nones,
        projectReferences );
    vcxprojFileWrite.close();
    
    std::cout << FG_SUBSUCCESS + projectName + ".vcxproj created successfully\n" STYLE_RESET;

    std::ofstream vcxprojFiltersFileWrite( vcxprojPath + ".filters" );
    vcxprojFiltersFileWrite << VCXPROJ_FILTERS(
        clIncludesFilters,
        clCompilesFilters,
        imagesFilters,
        nonesFilters );
    vcxprojFiltersFileWrite.close();
    
    std::cout << FG_SUBSUCCESS + projectName + ".vcxproj.filters created successfully\n" STYLE_RESET;
    
    std::cout << FG_SUCCESS "Project (" + projectName + ") made (-make) successfully\n" STYLE_RESET;

    return 0;
}



int AddSrcToVcxproj( std::string const& srcPath,
                     std::string const& subFolder,
                     std::string& clIncludes,
                     std::string& clCompiles,
                     std::string& clIncludesFilters,
                     std::string& clCompilesFilters )
{
    if ( fs::exists( srcPath ) == false ) return 0;

    if ( fs::exists( srcPath + subFolder ) == false ) return 0;

    for ( auto const& entry : fs::directory_iterator( srcPath + subFolder ) )
    {
        if ( entry.is_directory() )
        {
            AddSrcToVcxproj( srcPath, subFolder + "\\" + entry.path().filename().string(), clIncludes, clCompiles, clIncludesFilters, clCompilesFilters );
            continue;
        }

        if ( std::string const& fileExtension = entry.path().extension().string();
             fileExtension == ".h" ||
             fileExtension == ".hpp" ||
             fileExtension == ".tpp" ||
             fileExtension == ".inl" )
        {
            clIncludes += "        <ClInclude Include=\"$(SolutionDir)..\\src\\" + subFolder + "\\" + entry.path().filename().string() + "\" />"                                                          "\n";
            clIncludesFilters +=
                "        <ClInclude Include=\"$(SolutionDir)..\\src\\" + subFolder + "\\" + entry.path().filename().string() + "\">"                                                                      "\n"
                "            <Filter>Header Files</Filter>"                                                                                                                                               "\n"
                "        </ClInclude>"                                                                                                                                                                    "\n";
        }

        else if ( fileExtension == ".c" ||
                  fileExtension == ".cpp" )
        {
            std::string const& fileName = entry.path().filename().string();

            if ( fileName == "pch.cpp" )
            {
                clCompiles += CLCOMPILE_PCH_CPP( subFolder, fileName );
                continue;
            }

            clCompiles += "        <ClCompile Include=\"$(SolutionDir)..\\src\\" + subFolder + "\\" + fileName + "\" />"                                                                                  "\n";
            clCompilesFilters +=
                "        <ClCompile Include=\"$(SolutionDir)..\\src\\" + subFolder + "\\" + fileName + "\">"                                                                                              "\n"
                "            <Filter>Source Files</Filter>"                                                                                                                                               "\n"
                "        </ClCompile>"                                                                                                                                                                    "\n";
        }
    }

    return 0;
}



int AddResToVcxproj( std::string const& resPath,
                     std::string const& subFolder,
                     std::string& images,
                     std::string& nones,
                     std::string& imagesFilters,
                     std::string& nonesFilters )
{
    if ( fs::exists( resPath ) == false ) return 0;

    if ( fs::exists( resPath + subFolder ) == false ) return 0;
    
    for ( auto const& entry : fs::directory_iterator( resPath + subFolder ) )
    {
        if ( entry.is_directory() )
        {
            AddResToVcxproj( resPath, subFolder + "\\" + entry.path().filename().string(), images, nones, imagesFilters, nonesFilters );
            continue;
        }

        if ( std::string const& fileExtension = entry.path().extension().string();
             fileExtension == ".png" ||
             fileExtension == ".jpg" ||
             fileExtension == ".jpeg" ||
             fileExtension == ".dds" ||
             fileExtension == ".bmp" ||
             fileExtension == ".tif" ||
             fileExtension == ".tiff" ||
             fileExtension == ".gif" ||
             fileExtension == ".ico" ||
             fileExtension == ".svg" )
        {
            images += "        <Image Include=\"$(SolutionDir)..\\res\\" + subFolder + "\\" + entry.path().filename().string() + "\" />"                                                                  "\n";
            imagesFilters +=
                "        <Image Include=\"$(SolutionDir)..\\res\\" + subFolder + "\\" + entry.path().filename().string() + "\">"                                                                          "\n"
                "            <Filter>Images</Filter>"                                                                                                                                                     "\n"
                "        </Image>"                                                                                                                                                                        "\n";
        }

        else
        {
            nones += "        <None Include=\"$(SolutionDir)..\\res\\" + subFolder + "\\" + entry.path().filename().string() + "\" />"                                                                    "\n";
            nonesFilters +=
                "        <None Include=\"$(SolutionDir)..\\res\\" + subFolder + "\\" + entry.path().filename().string() + "\">"                                                                           "\n"
                "            <Filter>Resource Files</Filter>"                                                                                                                                             "\n"
                "        </None>"                                                                                                                                                                         "\n";
        }
    }

    return 0;
}



}