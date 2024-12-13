#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <windows.h>
#include "NumberToHex.h"
#include "Settings.h"
#include "SolutionGenerator.h"
namespace fs = std::filesystem;
namespace SolutionGenerator {



std::string GenerateGuid()
{
    std::string result;
    NumberToHex( rand(), result );
    NumberToHex( rand(), result );
    result += '-';
    NumberToHex( rand(), result );
    result += '-';
    NumberToHex( rand(), result );
    result += '-';
    NumberToHex( rand(), result );
    result += '-';
    NumberToHex( rand(), result );
    NumberToHex( rand(), result );
    NumberToHex( rand(), result );
    return result;
}



void CheckVersion( std::string const& repositoryName )
{
    std::string const configPath = repositoryName + "/config/settings.json";
    
    std::ifstream settingsFileRead( configPath );
    nlohmann::json settingsJson = nlohmann::json::parse( settingsFileRead );
    settingsFileRead.close();
    
    if ( settingsJson["version"] == VERSION ) return;

    if ( settingsJson["version"] == 1.17 )
    {
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
    }

    settingsJson["version"] = VERSION;

    std::ofstream settingsFileWrite( configPath );
    settingsFileWrite << std::setw(4) << settingsJson;
    settingsFileWrite.close();

    std::cout << FG_SUCCESS "settings.json updated to version " VERSION " !\n" STYLE_RESET;
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

    ERROR_IF( CreateBats( repositoryName ), "Could not create make.bat file\n" )

    std::cout << FG_SUCCESS "Repository (" + repositoryName + ") created successfully !\n" STYLE_RESET;

    CHECK_FOR_ERROR( CreateSolutionConfig( repositoryName, solutionName ) )

    std::cout << FG_SUCCESS "Solution (" + solutionName + ") config created successfully !\n" STYLE_RESET;

    CHECK_FOR_ERROR( CreateProject( repositoryName, projectName, true, pch, vcpkg, lib, window ) )

    std::cout << FG_SUCCESS "Project (" + projectName + ") created successfully !\n" STYLE_RESET;

    return 0;
}



int CreateBats( std::string const& repositoryName )
{
    std::ofstream make( repositoryName + "/bin/make.bat" );
    make <<
        "cd ../.."                            "\n"
        "SolutionGen.exe -make " + repositoryName;
    make.close();

    std::cout << FG_SUCCESS "make.bat created successfully !\n" STYLE_RESET;
    
    return 0;
}



int CreateBats( std::string const& repositoryName,
                std::string const& projectName )
{
    std::ofstream make( repositoryName + "/bin/make-" + projectName + ".bat" );
    make <<
        "cd ../.."                                                "\n"
        "SolutionGen.exe -make " + repositoryName + " " + projectName;
    make.close();

    std::cout << FG_SUCCESS "make-" + projectName + ".bat created successfully !\n" STYLE_RESET;

    return 0;
}



int CreateSolutionConfig( std::string const& repositoryName,
                          std::string const& solutionName )
{
    std::ofstream config( repositoryName + "/config/settings.json" );
    config << CONFIG_SETTINGS( solutionName, GenerateGuid() );
    config.close();
    
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
    ERROR_IF( CreateBats( repositoryName, projectName ), "Could not create make-" + projectName + ".bat file\n" )
    
    CHECK_FOR_ERROR( CreateProjectConfig( repositoryName, projectName, startup, pch, vcpkg, lib, window ) )

    CHECK_FOR_ERROR( CreateProjectSrc( repositoryName, projectName, pch, lib, window ) )

    ERROR_IF( fs::create_directory( repositoryName + "/res/" + projectName ) == false,
              "Could not create project (" + projectName + ") res folder\n" )

    std::cout << FG_SUCCESS "  Project (" + projectName + ") src files created successfully !\n" STYLE_RESET;

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

    std::string guid = GenerateGuid();

    settingsJson["projects"][projectName] = nlohmann::json::parse( PROJECT_CONFIG );
    settingsJson["projects"][projectName]["guid"] = guid;
    settingsJson["projects"][projectName]["pch"] = pch;
    settingsJson["projects"][projectName]["vcpkg"] = vcpkg;
    settingsJson["projects"][projectName]["lib"] = lib;
    settingsJson["projects"][projectName]["window"] = window;

    if ( startup ) settingsJson["startup_project"] = projectName;

    std::ofstream settingsFileWrite( settingsPath );
    settingsFileWrite << std::setw(4) << settingsJson;
    settingsFileWrite.close();

    std::cout << FG_SUCCESS " Project (" + projectName + ") successfully added to settings.json\n" STYLE_RESET;

    if ( vcpkg ) CHECK_FOR_ERROR( CreateVcpkgJson( repositoryName, projectName ) )

    return 0;
}



int CreateVcpkgJson( std::string const& repositoryName,
                     std::string const& projectName )
{
    std::string const configPath = repositoryName + "/config";
    std::string const vcpkgConfigPath = configPath + "/vcpkg-configuration.json";
    std::string const projectConfigPath = configPath + "/" + projectName;

    bool vcpkgConfigurationExists = false;
        
    std::ifstream vcpkgConfigurationRead( vcpkgConfigPath );
    vcpkgConfigurationExists = vcpkgConfigurationRead.good();
    vcpkgConfigurationRead.close();

    if ( vcpkgConfigurationExists == false )
    {
        std::ofstream vcpkgConfigurationWrite( vcpkgConfigPath );
        vcpkgConfigurationWrite << VCPKG_CONFIGURATION;
        vcpkgConfigurationWrite.close();

        std::cout << FG_SUCCESS "  vcpkg-configuration.json created successfully\n" STYLE_RESET;
    }

    ERROR_IF( fs::create_directory( projectConfigPath ) == false,
              "Could not create project (" + projectName + ") config folder\n" )

    std::ofstream vcpkgJson( projectConfigPath + "/vcpkg.json" );
    vcpkgJson << VCPKG_JSON;
    vcpkgJson.close();

    std::cout << FG_SUCCESS "  Project (" + projectName + ")'s vcpkg.json created successfully\n" STYLE_RESET;

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

        std::ofstream pchh( srcPath + "/pch.h" );
        pchh << pchhContent;
        pchh.close();

        std::ofstream pchcpp( srcPath + "/pch.cpp" );
        pchcpp << PCH_CPP;
        pchcpp.close();
    }
    else // pch == false
    {
        if ( window ) maincppContent = MAIN_CPP_WINDOW; // window == true
        else maincppContent = MAIN_CPP; // window == false
    }

    if ( lib == false ) // lib == false
    {
        std::ofstream mainh( srcPath + "/main.h" );
        mainh << MAIN_H;
        mainh.close();

        std::ofstream maincpp( srcPath + "/main.cpp" );
        maincpp << maincppContent;
        maincpp.close();
    }
    
    return 0;
}






int AddDependency( std::string const& repositoryName,
                   std::string const& projectName,
                   std::string const& dependency )
{
    std::ifstream settingsFileRead( repositoryName + "/config/settings.json" );
    nlohmann::json settingsJson = nlohmann::json::parse( settingsFileRead );
    settingsFileRead.close();

    if ( settingsJson["projects"][dependency]["lib"] == false )
    {
        std::cout << FG_ERROR "You can't add a non-library project (" + dependency + ") as a dependency\n" STYLE_RESET;
        return 1;
    }

    if ( settingsJson["projects"][dependency]["vcpkg"] )
    {
        if ( settingsJson["projects"][projectName]["vcpkg"] == false )
        {
            settingsJson["projects"][projectName]["vcpkg"] = true; // TODO Ask User Input

            std::string const projectConfigPath = repositoryName + "/config/" + projectName ;

            ERROR_IF( fs::create_directory( projectConfigPath ) == false,
                      "Could not create project (" + projectName + ") config folder\n" )

            std::ofstream vcpkgJson( projectConfigPath + "/vcpkg.json" );
            vcpkgJson << VCPKG_JSON;
            vcpkgJson.close();
        }
    }

    settingsJson["projects"][projectName]["dependencies"].push_back( dependency );

    std::ofstream settingsFileWrite( repositoryName + "/config/settings.json" );
    settingsFileWrite << std::setw(4) << settingsJson;
    settingsFileWrite.close();

    return 0;
}



int AddDependency( std::string const& repositoryName,
                   std::string const& projectName,
                   std::vector<std::string> const& dependencies )
{
    for ( std::string const& dependency : dependencies )
        CHECK_FOR_ERROR( AddDependency( repositoryName, projectName, dependency ) )
    return 0;
}



int AddPortVcpkg( std::string const& repositoryName,
                  std::string const& projectName,
                  std::string const& port )
{
    std::ifstream settingsFile( repositoryName + "/config/settings.json" );
    nlohmann::json settingsJson = nlohmann::json::parse( settingsFile );
    settingsFile.close();

    if ( settingsJson["projects"][projectName]["vcpkg"] == false )
    {
        std::string answer;

        std::cout << FG_INPUT "Project (" + projectName + ") doesn't have vcpkg, would you like to add it ? (o/n)\n" STYLE_RESET;
        std::cin >> answer;

        ERROR_IF( answer == "n" || answer == "N", "Port addition aborted\n" )
        ERROR_IF( answer != "o" && answer != "O", "Port addition aborted : you didn't answer\n" )

        settingsJson["projects"][projectName]["vcpkg"] = true;

        CHECK_FOR_ERROR( CreateVcpkgJson( repositoryName, projectName ) )
    }

    std::ifstream vcpkgFileRead( repositoryName + "/config/" + projectName + "/vcpkg.json" );
    nlohmann::json vcpkgJson = nlohmann::json::parse( vcpkgFileRead );
    vcpkgFileRead.close();

    for ( auto const& existingPort : vcpkgJson["dependencies"] )
        ERROR_IF( static_cast<std::string>( existingPort ) == port,
                  "Port (" + port + ") is already added to project (" + projectName + ")" )

    vcpkgJson["dependencies"].push_back( port );

    std::ofstream vcpkgFileWrite( repositoryName + "/config/" + projectName + "/vcpkg.json" );
    vcpkgFileWrite << std::setw(4) << vcpkgJson;
    vcpkgFileWrite.close();

    std::cout << FG_SUCCESS "Port (" + port + ") successfully added to project (" + projectName + ")\n" STYLE_RESET;

    return 0;
}



int AddPortVcpkg( std::string const& repositoryName,
                  std::string const& projectName,
                  std::vector<std::string> const& ports )
{
    for ( std::string const& port : ports )
        CHECK_FOR_ERROR( AddPortVcpkg( repositoryName, projectName, port ) )
    return 0;
}







int MakeSolution( std::string const& repositoryName,
                  bool const clear,
                  bool const open )
{
    if ( std::string const idePath = repositoryName + "/ide";
        fs::exists( idePath ) )
    {
        if ( clear )
        {
            fs::remove_all( idePath );
            ERROR_IF( fs::create_directory( idePath ) == false, "Could not create ide folder\n" )
        }
    }
    else ERROR_IF( fs::create_directory( idePath ) == false, "Could not create ide folder\n" )

    std::ifstream settingsFile( repositoryName + "/config/settings.json" );
    nlohmann::json settingsJson = nlohmann::json::parse( settingsFile );
    settingsFile.close();

    std::vector<std::array<std::string, 2>> projects;
    for ( auto const& project : static_cast<std::map<std::string, nlohmann::json>>( settingsJson["projects"] ) )
    {
        std::string const& projectName = project.first;

        if ( settingsJson["startup_project"] == projectName )
        {
            projects.insert( projects.begin(), std::array<std::string, 2>{ projectName, project.second["guid"] } );
            continue;
        }

        projects.push_back( std::array<std::string, 2>{ projectName, project.second["guid"] } );
    }

    CHECK_FOR_ERROR( MakeSolution( repositoryName, projects, settingsJson ) )

    if ( open ) ShellExecuteA( nullptr, "open", fs::absolute( repositoryName + "/ide" ).string().c_str(), nullptr, nullptr, SW_SHOWNORMAL );

    return 0;
}



int MakeSolution( std::string const& repositoryName,
                  std::string const& projectName,
                  bool const clear,
                  bool const open )
{
    if ( std::string const idePath = repositoryName + "/ide";
        fs::exists( idePath ) )
    {
        if ( clear )
        {
            fs::remove_all( idePath );
            ERROR_IF( fs::create_directory( idePath ) == false, "Could not create ide folder\n" )
        }
    }
    else ERROR_IF( fs::create_directory( idePath ) == false, "Could not create ide folder\n" )

    std::ifstream settingsFile( repositoryName + "/config/settings.json" );
    nlohmann::json settingsJson = nlohmann::json::parse( settingsFile );
    settingsFile.close();

    std::vector projects { std::array<std::string, 2>{ projectName, settingsJson["projects"][projectName]["guid"] } };
    for ( nlohmann::basic_json<> const& dependency: settingsJson["projects"][projectName]["dependencies"] )
    {
        std::string const& dependencyName = static_cast<std::string>( dependency );
        projects.push_back( std::array<std::string, 2>{ dependencyName, settingsJson["projects"][dependencyName]["guid"] } );
    }

    CHECK_FOR_ERROR( MakeSolution( repositoryName, projects, settingsJson ) )

    if ( open ) ShellExecuteA( nullptr, "open", fs::absolute( repositoryName + "/ide" ).string().c_str(), nullptr, nullptr, SW_SHOWNORMAL );

    return 0;
}



int MakeSolution( std::string const& repositoryName,
                  std::vector<std::array<std::string, 2>>& projects,
                  nlohmann::json const& settingsJson )
{
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
    std::string const precompiledHeader = pch ? "Use" : "NotUsing";

    bool const vcpkg = settingsJson["projects"][projectName]["vcpkg"];
    std::string const vcpkgEnabled = vcpkg ? "true" : "false";

    bool const lib = settingsJson["projects"][projectName]["lib"];
    std::string const configurationType = lib ? "StaticLibrary" : "Application";

    bool const window = settingsJson["projects"][projectName]["window"];
    std::string const preprocessorDefinitions = window ? ( lib ? "LIB" : "WINDOWS" ) : "CONSOLE";
    std::string const subSystem = window ? "Windows" : "Console";

    std::string additionalIncludeDirectories;
    std::string additionalLibraryDirectories;
    std::string additionalDependencies;
    std::string projectReferences;

    for ( nlohmann::json const& dependency : settingsJson["projects"][projectName]["dependencies"] )
    {
        std::string const& dependencyName = static_cast<std::string>( dependency );
        std::string const& dependencyGuid = settingsJson["projects"][dependencyName]["guid"];

        additionalIncludeDirectories += "$(SolutionDir)..\\src\\" + dependencyName + ";";
        additionalLibraryDirectories += "$(SolutionDir)" + dependencyName + "\\$(Platform)\\$(Configuration);";
        additionalDependencies += dependencyName + ".lib;";

        projectReferences +=
            "        <ProjectReference Include=\"$(SolutionDir)\\" + dependencyName + "\\" + dependencyName + ".vcxproj\">"                                                                               "\n"
            "            <Project>{" + dependencyGuid + "}</Project>"                                                                                                                                     "\n"
            "        </ProjectReference>"                                                                                                                                                                 "\n";
    }

    std::ofstream vcxproj( ideProjectPath + "/" + projectName + ".vcxproj" );
    vcxproj << VCXPROJ_1( guid, configurationType, vcpkgEnabled, projectName, preprocessorDefinitions, precompiledHeader, additionalIncludeDirectories, subSystem, additionalLibraryDirectories, additionalDependencies );
    CHECK_FOR_ERROR( AddSrcToVcxproj( repositoryName + "\\src\\", projectName, vcxproj ) )
    CHECK_FOR_ERROR( AddResToVcxproj( repositoryName + "\\res\\", projectName, vcxproj ) )
    vcxproj << VCXPROJ_2( projectReferences );
    vcxproj.close();

    return 0;
}



int AddSrcToVcxproj( std::string const& srcPath,
                     std::string const& subFolder,
                     std::ofstream& vcxproj )
{
    if ( fs::exists( srcPath ) == false ) return 0;

    if ( fs::exists( srcPath + subFolder ) == false ) return 0;

    for ( auto const& entry : fs::directory_iterator( srcPath + subFolder ) )
    {
        if ( entry.is_directory() )
        {
            AddSrcToVcxproj( srcPath, subFolder + "\\" + entry.path().filename().string(), vcxproj );
            continue;
        }

        if ( std::string const& fileExtension = entry.path().extension().string();
             fileExtension == ".h" ||
             fileExtension == ".hpp" ||
             fileExtension == ".tpp" ||
             fileExtension == ".inl" )
            vcxproj << "        <ClInclude Include=\"$(SolutionDir)..\\src\\" + subFolder + "\\" + entry.path().filename().string() + "\" />"                                                                  "\n";

        else if ( fileExtension == ".c" ||
                  fileExtension == ".cpp" )
        {
            std::string const& fileName = entry.path().filename().string();

            if ( fileName == "pch.cpp" )
            {
                vcxproj << CLCOMPILE_PCH_CPP( subFolder, fileName );
                continue;
            }

            vcxproj << "        <ClCompile Include=\"$(SolutionDir)..\\src\\" + subFolder + "\\" + fileName + "\" />"                                                                                          "\n";
        }

        else vcxproj << "        <None Include=\"$(SolutionDir)..\\src\\" + subFolder + "\\" + entry.path().filename().string() + "\" />"                                                                      "\n";
    }

    return 0;
}



int AddResToVcxproj( std::string const& resPath,
                     std::string const& subFolder,
                     std::ofstream& vcxproj )
{
    if ( fs::exists( resPath ) == false ) return 0;

    if ( fs::exists( resPath + subFolder ) == false ) return 0;
    
    for ( auto const& entry : fs::directory_iterator( resPath + subFolder ) )
    {
        if ( entry.is_directory() )
        {
            AddSrcToVcxproj( resPath, subFolder + "\\" + entry.path().filename().string(), vcxproj );
            continue;
        }

        if ( std::string const& fileExtension = entry.path().extension().string();
             fileExtension == ".png" ||
             fileExtension == ".jpg" ||
             fileExtension == ".jpeg" ||
             fileExtension == ".dds" ||
             fileExtension == ".bmp" ||
             fileExtension == ".gif" ||
             fileExtension == ".ico" ||
             fileExtension == ".svg" )
            vcxproj << "        <Image Include=\"$(SolutionDir)..\\res\\" + subFolder + "\\" + entry.path().filename().string() + "\" />"                                                             "\n";

        else vcxproj << "        <None Include=\"$(SolutionDir)..\\res\\" + subFolder + "\\" + entry.path().filename().string() + "\" />"                                                             "\n";
    }

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
        std::string const& dependencyName = static_cast<std::string>( dependency );
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



}