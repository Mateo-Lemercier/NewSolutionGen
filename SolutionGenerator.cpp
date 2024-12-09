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



std::string CreateRepository( std::string const& repositoryName,
                              std::string const& solutionName,
                              std::string const& projectName,
                              bool const pch,
                              bool const vcpkg,
                              bool const lib,
                              bool const window )
{
    if ( fs::exists( repositoryName ) == false && fs::create_directory( repositoryName ) == false )
            return "Could not create repository folder\n";
    
    if ( fs::exists( repositoryName + "/src" ) ) return "There is already a Solution Generated repository named " + repositoryName + "\n";

    if ( fs::create_directory( repositoryName + "/bin" ) == false ) return "Could not create bin folder\n";
    if ( fs::create_directory( repositoryName + "/config" ) == false ) return "Could not create config folder\n";
    if ( fs::create_directory( repositoryName + "/res" ) == false ) return "Could not create res folder\n";
    if ( fs::create_directory( repositoryName + "/src" ) == false ) return "Could not create src folder\n";

    std::ofstream gitignore( repositoryName + "/.gitignore" );
    gitignore << "ide";
    gitignore.close();

    std::cout << FG_GREEN "Repository (" + repositoryName + ") created successfully !\n" STYLE_RESET;

    if ( std::string const solutionConfigError = CreateSolutionConfig( repositoryName, solutionName );
        solutionConfigError.empty() == false )
        return solutionConfigError;

    std::cout << FG_GREEN "Solution (" + solutionName + ") config created successfully !\n" STYLE_RESET;

    if ( std::string const projectError = CreateProject( repositoryName, projectName, pch, vcpkg, lib, window );
        projectError.empty() == false )
        return projectError;

    std::cout << FG_GREEN "Project (" + projectName + ") created successfully !\n" STYLE_RESET;

    return "";
}



std::string CreateSolutionConfig( std::string const& repositoryName,
                                  std::string const& solutionName )
{
    std::ofstream config( repositoryName + "/config/settings.json" );
    config << CONFIG_SETTINGS( solutionName, GenerateGuid() );
    config.close();
    
    return "";
}



std::string CreateProject( std::string const& repositoryName,
                           std::string const& projectName,
                           bool const pch,
                           bool const vcpkg,
                           bool const lib,
                           bool const window )
{
    if ( std::string const configError = CreateProjectConfig( repositoryName, projectName, pch, vcpkg, lib, window );
        configError.empty() == false )
        return configError;

    std::cout << FG_GREEN "  Project (" + projectName + ") config added successfully !\n" STYLE_RESET;

    if ( std::string const srcError = CreateProjectSrc( repositoryName, projectName, pch, lib, window );
        srcError.empty() == false )
        return srcError;

    std::cout << FG_GREEN "  Project (" + projectName + ") src files created successfully !\n" STYLE_RESET;

    return "";
}



std::string CreateProjectConfig( std::string const& repositoryName,
                              std::string const& projectName,
                              bool const pch,
                              bool const vcpkg,
                              bool const lib,
                              bool const window )
{
    std::string const configPath = repositoryName + "/config/";
    
    std::ifstream settingsFileRead( configPath + "settings.json" );
    nlohmann::json settingsJson = nlohmann::json::parse( settingsFileRead );
    settingsFileRead.close();

    std::string guid = GenerateGuid();

    settingsJson["projects"][projectName] = nlohmann::json::parse( PROJECT_CONFIG );
    settingsJson["projects"][projectName]["guid"] = guid;
    settingsJson["projects"][projectName]["pch"] = pch;
    settingsJson["projects"][projectName]["vcpkg"] = vcpkg;
    settingsJson["projects"][projectName]["lib"] = lib;
    settingsJson["projects"][projectName]["window"] = window;

    std::ofstream settingsFileWrite( configPath + "settings.json" );
    settingsFileWrite << std::setw(4) << settingsJson;
    settingsFileWrite.close();

    if ( vcpkg )
    {
        bool vcpkgConfigured = false;
        
        std::ifstream vcpkgConfigurationRead( configPath + "vcpkg-configuration.json" );
        vcpkgConfigured = vcpkgConfigurationRead.good();
        vcpkgConfigurationRead.close();

        if ( vcpkgConfigured == false )
        {
            std::ofstream vcpkgConfigurationWrite( configPath + "vcpkg-configuration.json" );
            vcpkgConfigurationWrite << VCPKG_CONFIGURATION;
            vcpkgConfigurationWrite.close();

            std::cout << FG_GREEN "  vcpkg-configuration.json created successfully !\n" STYLE_RESET;
        }

        if ( fs::create_directory( configPath + projectName ) == false ) return "Could not create project (" + projectName + ") config folder\n";

        std::ofstream vcpkgJson( configPath + projectName + "/vcpkg.json" );
        vcpkgJson << VCPKG_JSON;
        vcpkgJson.close();
    }

    return "";
}



std::string CreateProjectSrc( std::string const& repositoryName,
                              std::string const& projectName,
                              bool const pch,
                              bool const lib,
                              bool const window )
{
    std::string const srcPath = repositoryName + "/src/" + projectName;
    if ( fs::create_directory( srcPath ) == false ) return "Could not create project (" + projectName + ") src folder\n";

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
    
    return "";
}



std::string AddDependencyToProjectConfig( std::string const& repositoryName,
                                          std::string const& projectName,
                                          std::string const& dependency )
{
    std::ifstream settingsFileRead( repositoryName + "/config/settings.json" );
    nlohmann::json settingsJson = nlohmann::json::parse( settingsFileRead );
    settingsFileRead.close();

    if ( settingsJson["projects"][dependency]["lib"] == false ) return "You can't add a non-library project (" + dependency + ") as a dependency\n";

    if ( settingsJson["projects"][dependency]["vcpkg"] )
    {
        if ( settingsJson["projects"][projectName]["vcpkg"] == false )
        {
            settingsJson["projects"][projectName]["vcpkg"] = true;

            std::string const projectConfigPath = repositoryName + "/config/" + projectName ;

            if ( fs::create_directory( projectConfigPath ) == false ) return "Could not create project (" + projectName + ") config folder\n";

            std::ofstream vcpkgJson( projectConfigPath + "/vcpkg.json" );
            vcpkgJson << VCPKG_JSON;
            vcpkgJson.close();
        }
    }

    settingsJson["projects"][projectName]["dependencies"].push_back( dependency );

    std::ofstream settingsFileWrite( repositoryName + "/config/settings.json" );
    settingsFileWrite << std::setw(4) << settingsJson;
    settingsFileWrite.close();

    return "";
}



std::string AddDependenciesToProjectConfig( std::string const& repositoryName,
                                            std::string const& projectName,
                                            std::vector<std::string> const& dependencies )
{
    for ( std::string const& dependency : dependencies )
        if ( std::string const errorMessage = AddDependencyToProjectConfig( repositoryName, projectName, dependency );
            errorMessage.empty() == false )
            return errorMessage;
    return "";
}



std::string MakeSolution( std::string const& repositoryName,
                          bool const clear,
                          bool const open )
{
    if ( std::string const idePath = repositoryName + "/ide";
        fs::exists( idePath ) )
    {
        // if ( clear )
        {
            fs::remove_all( idePath );
            if ( fs::create_directory( idePath ) == false ) return "Could not create ide folder\n";
        }
    }
    else if ( fs::create_directory( idePath ) == false ) return "Could not create ide folder\n";

    std::ifstream settingsFile( repositoryName + "/config/settings.json" );
    nlohmann::json settingsJson = nlohmann::json::parse( settingsFile );
    settingsFile.close();

    std::vector<std::array<std::string, 2>> projects;
    for ( auto const& project : static_cast<std::map<std::string, nlohmann::json>>( settingsJson["projects"] ) )
        projects.push_back( std::array<std::string, 2>{ project.first, project.second["guid"] } );

    if ( std::string const errorMessage = MakeSolution( repositoryName, projects, settingsJson );
         errorMessage.empty() == false )
        return errorMessage;

    if ( open ) ShellExecuteA( nullptr, "open", fs::absolute( repositoryName + "/ide" ).string().c_str(), nullptr, nullptr, SW_SHOWNORMAL );

    return "";
}



std::string MakeSolution( std::string const& repositoryName,
                          std::string const& projectName,
                          bool const clear,
                          bool const open )
{
    if ( std::string const idePath = repositoryName + "/ide";
        fs::exists( idePath ) )
    {
        // if ( clear )
        {
            fs::remove_all( idePath );
            if ( fs::create_directory( idePath ) == false ) return "Could not create ide folder\n";
        }
    }
    else if ( fs::create_directory( idePath ) == false ) return "Could not create ide folder\n";

    std::ifstream settingsFile( repositoryName + "/config/settings.json" );
    nlohmann::json settingsJson = nlohmann::json::parse( settingsFile );
    settingsFile.close();

    std::vector projects { std::array<std::string, 2>{ projectName, settingsJson["projects"][projectName]["guid"] } };
    for ( nlohmann::basic_json<> const& dependency: settingsJson["projects"][projectName]["dependencies"] )
    {
        std::string const& dependencyName = static_cast<std::string>( dependency );
        projects.push_back( std::array<std::string, 2>{ dependencyName, settingsJson["projects"][dependencyName]["guid"] } );
    }

    if ( std::string const errorMessage = MakeSolution( repositoryName, projects, settingsJson );
         errorMessage.empty() == false )
        return errorMessage;

    if ( open ) ShellExecuteA( nullptr, "open", fs::absolute( repositoryName + "/ide" ).string().c_str(), nullptr, nullptr, SW_SHOWNORMAL );

    return "";
}



std::string MakeSolution( std::string const& repositoryName,
                          std::vector<std::array<std::string, 2>>& projects,
                          nlohmann::json const& settingsJson )
{
    std::string projectsForSln;
    std::string globalSection;

    for ( std::array<std::string, 2> const& project : projects )
    {
        std::string const& projectName = project[0];
        std::string const& projectGui = project[1];

        if ( std::string const errorMessage = MakeProject( repositoryName, projectName, settingsJson );
             errorMessage.empty() == false )
            return errorMessage;
    
        projectsForSln += "Project(\"{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}\") = \"" + projectName + "\", \"" + projectName + "\\" + projectName + ".vcxproj\", \"{" + projectGui + "}\""                "\n";
        AddDependenciesToSln( settingsJson, projectName, projectsForSln, projects );
        projectsForSln += "EndProject"                                                                                                                                                                    "\n";
    
        globalSection += PROJECT_GLOBAL_SECTION( projectGui );
    }

    std::string const& solutionName = settingsJson[ "solution_name" ];
    std::string const& solutionGuid = settingsJson[ "solution_guid" ];
    
    std::ofstream sln( repositoryName + "/ide/" + solutionName + ".sln" );
    sln << SLN( projectsForSln, globalSection, solutionGuid );
    sln.close();

    return "";
}



std::string MakeProject( std::string const& repositoryName,
                         std::string const& projectName,
                         nlohmann::json const& settingsJson )
{
    std::string const ideProjectPath = repositoryName + "/ide/" + projectName;

    if ( fs::create_directory( ideProjectPath ) == false ) return "Could not create ide project (" + projectName + ") folder\n";

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
    AddSrcToVcxproj( repositoryName + "/src/", projectName, vcxproj );
    vcxproj << VCXPROJ_2( projectReferences );
    vcxproj.close();

    return "";
}



void AddSrcToVcxproj( std::string const& srcPath,
                      std::string const& subFolder,
                      std::ofstream& vcxproj )
{
    for ( auto const& entry : fs::directory_iterator( srcPath + subFolder ) )
    {
        if ( entry.is_directory() )
        {
            AddSrcToVcxproj( entry.path().string(), subFolder + "\\" + entry.path().filename().string(), vcxproj );
            continue;
        }

        if ( std::string const fileExtension = entry.path().extension().string();
             fileExtension == ".h" ||
             fileExtension == ".hpp" ||
             fileExtension == ".tpp" ||
             fileExtension == ".inl" )
            vcxproj << "        <ClInclude Include=\"$(SolutionDir)..\\src\\" + subFolder + "\\" + entry.path().filename().string() + "\" />"                                                             "\n";

        else if ( fileExtension == ".c" ||
                  fileExtension == ".cpp" )
        {
            std::string const fileName = entry.path().filename().string();

            if ( fileName == "pch.cpp" )
            {
                vcxproj << CLCOMPILE_PCH_CPP( subFolder, fileName );
                continue;
            }

            vcxproj << "        <ClCompile Include=\"$(SolutionDir)..\\src\\" + subFolder + "\\" + fileName + "\" />"                                                                                     "\n";
        }
    }
}



void AddDependenciesToSln( nlohmann::json const& settingsJson,
                           std::string const& projectName,
                           std::string& projectsForSln,
                           std::vector<std::array<std::string, 2>>& projects )
{
    nlohmann::json const& dependencies = settingsJson["projects"][projectName]["dependencies"];

    if ( dependencies.empty() ) return;
    
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
}




}