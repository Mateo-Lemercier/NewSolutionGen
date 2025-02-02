#pragma once



#define VERSION "1.17.4"



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
#define FG_ERROR STYLE( "31" )
#define FG_SUCCESS STYLE( "32" )
#define FG_SUBSUCCESS STYLE( "2;32" ) "  "
#define FG_INPUT STYLE( "36" )



// #define ACT( action ) "-" action
// #define OBL( argument ) " [" argument "]"
// #define OPT( argument ) " <" argument ">"
// #define LAST "               "

#define HELP_START STYLE("1;2") "\n"\
    "Le Solution Generator est un outil permettant de generer des solutions Visual Studio."                        "\n"\
    "Utilisation : SolutionGen.exe -action [Required_Arguments] <optional_arguments>"                              "\n"\
    ""                                                                                                             "\n"\

#define HELP_MESSAGE HELP_START \
    "Available Actions :"                                                                                          "\n"\
    "+-------------------------------------------------------------------------------------------------------------+\n"\
    "|                                                                                                             |\n"\
    "|  -help <action>                                                                                             |\n"\
    "|                                                                                                             |\n"\
    "|  -create [Repository] [Solution] <project> <-pch|-vcpkg|-lib|-window>                                       |\n"\
    "|                                                                                                             |\n"\
    "|  -make [Repository] <project> <-open|-clear>                                                                |\n"\
    "|                                                                                                             |\n"\
    "|  -add [Repository] [Project] <dependency_projects...> <-startup|-pch|-vcpkg|-lib|-window>                   |\n"\
    "|                                                                                                             |\n"\
    "|  -edit [Repository] [Project] <dependency_projects...> <-startup|-pch|-vcpkg|-lib|-window>                  |\n"\
    "|                                                                                                             |\n"\
    "|  -rename [Repository] [Project] [Name]                                                                      |\n"\
    "|                                                                                                             |\n"\
    "|  -addPort [Repository] [Project] [Port] <other_ports...>                                                    |\n"\
    "|                                                                                                             |\n"\
    "|  -remove [Repository] [Project]                                                                             |\n"\
    "|                                                                                                             |\n"\
    "+-------------------------------------------------------------------------------------------------------------+\n" STYLE_RESET

#define HELP_HELP HELP_START \
    "Action Description (Help) :"                                                                                  "\n"\
    "+-------------------------------------------------------------------------------------------------------------+\n"\
    "|  -help <action>                                                                                             |\n"\
    "|                                                                                                             |\n"\
    "|    action - The name of the action from which you want further informations                                 |\n"\
    "|                                                                                                             |\n"\
    "+-------------------------------------------------------------------------------------------------------------+\n" STYLE_RESET

#define HELP_CREATE HELP_START \
    "Action Description (Create) :"                                                                                "\n"\
    "+-------------------------------------------------------------------------------------------------------------+\n"\
    "|  -create [Repository] [Solution] <project> <-pch|-vcpkg|-lib|-window>                                       |\n"\
    "|                                                                                                             |\n"\
    "|    Repository - The name of the repository where the solution is going to be created                        |\n"\
    "|    Solution - The name of the solution to be created                                                        |\n"\
    "|    project - The name of the first project of the solution (default is the same as Solution)                |\n"\
    "|    -pch - Whether or not to enable the precompiled header file                                              |\n"\
    "|    -vcpkg - Whether or not to enable vcpkg                                                                  |\n"\
    "|    -lib - Whether or not to make this project a static library                                              |\n"\
    "|    -window - Whether or to make this project a windows project                                              |\n"\
    "|                                                                                                             |\n"\
    "+-------------------------------------------------------------------------------------------------------------+\n" STYLE_RESET

#define HELP_MAKE HELP_START \
    "Action Description (Make) :"                                                                                  "\n"\
    "+-------------------------------------------------------------------------------------------------------------+\n"\
    "|  -make [Repository] <project> <-open|-clear>                                                                |\n"\
    "|                                                                                                             |\n"\
    "|    Repository - The name of the repository folder                                                           |\n"\
    "|    project - The name of the project to make (only this project and its dependencies will be generated)     |\n"\
    "|    -open - Whether or not the file explorer will open in the ide folder                                     |\n"\
    "|    -clear - Whether or not the ide folder will be deleted before generating the files                       |\n"\
    "|                                                                                                             |\n"\
    "+-------------------------------------------------------------------------------------------------------------+\n" STYLE_RESET

#define HELP_ADD HELP_START \
    "Action Description (Add) :"                                                                                   "\n"\
    "+-------------------------------------------------------------------------------------------------------------+\n"\
    "|  -add [Repository] [Project] <dependency_projects...> <-startup|-pch|-vcpkg|-lib|-window>                   |\n"\
    "|                                                                                                             |\n"\
    "|    Repository - The name of the repository folder                                                           |\n"\
    "|    Project - The name of the project to be added                                                            |\n"\
    "|    dependency_projects... - The names of the projects you want to set as dependencies                       |\n"\
    "|    -startup - Whether or not this project will be the default startup project                               |\n"\
    "|    -pch - Whether or not to enable the precompiled header file                                              |\n"\
    "|    -vcpkg - Whether or not to enable vcpkg                                                                  |\n"\
    "|    -lib - Whether or not to make this project a static library                                              |\n"\
    "|    -window - Whether or to make this project a windows project                                              |\n"\
    "|                                                                                                             |\n"\
    "+-------------------------------------------------------------------------------------------------------------+\n" STYLE_RESET

#define HELP_EDIT HELP_START \
    "Action Description (Edit) :"                                                                                  "\n"\
    "+-------------------------------------------------------------------------------------------------------------+\n"\
    "|  -edit [Repository] [Project] <dependency_projects...> <-startup|-pch|-vcpkg|-lib|-window>                  |\n"\
    "|                                                                                                             |\n"\
    "|    Repository - The name of the repository folder                                                           |\n"\
    "|    Project - The name of the project you want to edit                                                       |\n"\
    "|    dependency_projects... - The name of the projects to be added or removed as dependencies                 |\n"\
    "|    -startup - Sets this project as the startup project                                                      |\n"\
    "|    -pch - Enables or disables the precompiled header file                                                   |\n"\
    "|    -vcpkg - Enables or disables vcpkg                                                                       |\n"\
    "|    -lib - Turns this project into a static library or turns it back to a console project                    |\n"\
    "|    -window - Turns this project into a windows project or turns it back to a console project                |\n"\
    "|                                                                                                             |\n"\
    "+-------------------------------------------------------------------------------------------------------------+\n" STYLE_RESET

#define HELP_RENAME HELP_START \
    "Action Description (Rename) :"                                                                                "\n"\
    "+-------------------------------------------------------------------------------------------------------------+\n"\
    "|  -rename [Repository] [Project] [Name]                                                                      |\n"\
    "|                                                                                                             |\n"\
    "|    Repository - The name of the repository folder                                                           |\n"\
    "|    Project - The name of the project you want to rename                                                     |\n"\
    "|    Name - The new name that should be given to the project                                                  |\n"\
    "|                                                                                                             |\n"\
    "+-------------------------------------------------------------------------------------------------------------+\n" STYLE_RESET

#define HELP_ADD_PORT HELP_START \
    "Action Description (AddPort) :"                                                                               "\n"\
    "+-------------------------------------------------------------------------------------------------------------+\n"\
    "|  -addPort [Repository] [Project] [Port] <other_ports...>                                                    |\n"\
    "|                                                                                                             |\n"\
    "|    Repository - The name of the repository folder                                                           |\n"\
    "|    Project - The name of the project to which the port will be added                                        |\n"\
    "|    Port - The name of the vcpkg port to be added                                                            |\n"\
    "|    other_ports... - As many other ports as you want                                                         |\n"\
    "|                                                                                                             |\n"\
    "+-------------------------------------------------------------------------------------------------------------+\n" STYLE_RESET

#define HELP_REMOVE HELP_START \
    "Action Description (Remove) :"                                                                                "\n"\
    "+-------------------------------------------------------------------------------------------------------------+\n"\
    "|  -remove [Repository] [Project]                                                                             |\n"\
    "|                                                                                                             |\n"\
    "|    Repository - The name of the repository folder                                                           |\n"\
    "|    Project - The name of the project to remove                                                              |\n"\
    "|                                                                                                             |\n"\
    "+-------------------------------------------------------------------------------------------------------------+\n" STYLE_RESET



#define CONFIG_SETTINGS( solutionName, solutionGuid ) (\
    "{"                                                    "\n"\
    "    \"version\": \"" VERSION "\","                    "\n"\
    "    \"solution_name\": \"" + ( solutionName ) + "\"," "\n"\
    "    \"solution_guid\": \"" + ( solutionGuid ) + "\"," "\n"\
    "    \"projects\": {},"                                "\n"\
    "    \"startup_project\": \"\""                        "\n"\
    "}")

#define PROJECT_CONFIG \
    "{"                                                    "\n"\
    "    \"guid\": \"\","                                  "\n"\
    "    \"pch\": false,"                                  "\n"\
    "    \"vcpkg\": false,"                                "\n"\
    "    \"lib\": false,"                                  "\n"\
    "    \"window\": false,"                               "\n"\
    /*"    \"filters\": ["                                   "\n"*/\
    /*"        "                                             "\n"*/\
    /*"    ],"                                               "\n"*/\
    "    \"dependencies\": [],"                            "\n"\
    "    \"dependents\": [],"                              "\n"\
    "    \"preprocessorDefinitions\": [],"                 "\n"\
    "    \"additionalIncludeDirectories\": [],"            "\n"\
    "    \"additionalLibraryDirectories\": [],"            "\n"\
    "    \"additionalDependencies\": []"                   "\n"\
    "}"



#define PCH_H \
    "#ifndef PCH_H"                          "\n"\
    "#define PCH_H"                          "\n"\
    ""                                       "\n"\
    "#include <iostream>"                    "\n"\
    ""                                       "\n"\
    "#endif"

#define PCH_H_WINDOW \
    "#ifndef PCH_H"                          "\n"\
    "#define PCH_H"                          "\n"\
    ""                                       "\n"\
    "#include <windows.h>"                   "\n"\
    ""                                       "\n"\
    "#endif"

#define PCH_CPP \
    "#include \"pch.h\""                     "\n"\
    ""



#define MAIN_H \
    "#ifndef MAIN_H"                         "\n"\
    "#define MAIN_H"                         "\n"\
    ""                                       "\n"\
    ""                                       "\n"\
    ""                                       "\n"\
    "#endif"

#define MAIN_CPP \
    "#include <iostream>"                    "\n"\
    "#include \"main.h\""                    "\n"\
    ""                                       "\n"\
    "int main()"                             "\n"\
    "{"                                      "\n"\
    "    std::cout << \"Hello, World!\\n\";" "\n"\
    "    return 0;"                          "\n"\
    "}"

#define MAIN_CPP_PCH \
    "#include \"pch.h\""                     "\n"\
    "#include \"main.h\""                    "\n"\
    ""                                       "\n"\
    "int main()"                             "\n"\
    "{"                                      "\n"\
    "    std::cout << \"Hello, World!\\n\";" "\n"\
    "    return 0;"                          "\n"\
    "}"

#define MAIN_CPP_WINDOW \
    "#include <windows.h>"                                                                 "\n"\
    "#include \"main.h\""                                                                  "\n"\
    ""                                                                                     "\n"\
    "int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR cmdLine, int cmdShow)" "\n"\
    "{"                                                                                    "\n"\
    "    return 0;"                                                                        "\n"\
    "}"

#define MAIN_CPP_PCH_WINDOW \
    "#include \"pch.h\""                                                                   "\n"\
    "#include \"main.h\""                                                                  "\n"\
    ""                                                                                     "\n"\
    "int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR cmdLine, int cmdShow)" "\n"\
    "{"                                                                                    "\n"\
    "    return 0;"                                                                        "\n"\
    "}"



#define VCPKG_CONFIGURATION \
    "{"                                                                                                    "\n"\
    "    \"default-registry\": {"                                                                          "\n"\
    "        \"baseline\": \"5a3e638f449206ac10f82f2171a21333004d7306\","                                  "\n"\
    "        \"kind\": \"git\","                                                                           "\n"\
    "        \"repository\": \"https://github.com/microsoft/vcpkg\""                                       "\n"\
    "    },"                                                                                               "\n"\
    "    \"registries\": ["                                                                                "\n"\
    "        {"                                                                                            "\n"\
    "            \"kind\": \"artifact\","                                                                      "\n"\
    "            \"location\": \"https://github.com/microsoft/vcpkg-ce-catalog/archive/refs/heads/main.zip\"," "\n"\
    "            \"name\": \"microsoft\""                                                                      "\n"\
    "        }"                                                                                            "\n"\
    "    ]"                                                                                                "\n"\
    "}"

#define VCPKG_JSON \
    "{"                                      "\n"\
    "    \"dependencies\": []"               "\n"\
    "}"



#define PROJECT_GLOBAL_SECTION( projectGuid ) (\
    "\t""\t""{" + (projectGuid) + "}.Debug|x64.ActiveCfg = Debug|x64"                                                                                                                                 "\n"\
    "\t""\t""{" + (projectGuid) + "}.Debug|x64.Build.0 = Debug|x64"                                                                                                                                   "\n"\
    "\t""\t""{" + (projectGuid) + "}.Debug|x86.ActiveCfg = Debug|Win32"                                                                                                                               "\n"\
    "\t""\t""{" + (projectGuid) + "}.Debug|x86.Build.0 = Debug|Win32"                                                                                                                                 "\n"\
    "\t""\t""{" + (projectGuid) + "}.Release|x64.ActiveCfg = Release|x64"                                                                                                                             "\n"\
    "\t""\t""{" + (projectGuid) + "}.Release|x64.Build.0 = Release|x64"                                                                                                                               "\n"\
    "\t""\t""{" + (projectGuid) + "}.Release|x86.ActiveCfg = Release|Win32"                                                                                                                           "\n"\
    "\t""\t""{" + (projectGuid) + "}.Release|x86.Build.0 = Release|Win32"                                                                                                                             "\n")

#define SLN( projects, globalSection, solutionGuid ) (\
    "Microsoft Visual Studio Solution File, Format Version 12.00"                                                                                                                                     "\n"\
    "# Visual Studio Version 17"                                                                                                                                                                      "\n"\
    "VisualStudioVersion = 17.9.34622.214"                                                                                                                                                            "\n"\
    "MinimumVisualStudioVersion = 10.0.40219.1"                                                                                                                                                       "\n"\
    + (projects) +                                                                                                                                                                                        \
    "Global"                                                                                                                                                                                          "\n"\
    "\t""GlobalSection(SolutionConfigurationPlatforms) = preSolution"                                                                                                                                 "\n"\
    "\t""\t""Debug|x64 = Debug|x64"                                                                                                                                                                   "\n"\
    "\t""\t""Debug|x86 = Debug|x86"                                                                                                                                                                   "\n"\
    "\t""\t""Release|x64 = Release|x64"                                                                                                                                                               "\n"\
    "\t""\t""Release|x86 = Release|x86"                                                                                                                                                               "\n"\
    "\t""EndGlobalSection"                                                                                                                                                                            "\n"\
    "\t""GlobalSection(ProjectConfigurationPlatforms) = postSolution"                                                                                                                                 "\n"\
    + (globalSection) +                                                                                                                                                                                   \
    "\t""EndGlobalSection"                                                                                                                                                                            "\n"\
    "\t""GlobalSection(SolutionProperties) = preSolution"                                                                                                                                             "\n"\
    "\t""\t""HideSolutionNode = FALSE"                                                                                                                                                                "\n"\
    "\t""EndGlobalSection"                                                                                                                                                                            "\n"\
    "\t""GlobalSection(ExtensibilityGlobals) = postSolution"                                                                                                                                          "\n"\
    "\t""\t""SolutionGuid = {" + (solutionGuid) + "}"                                                                                                                                                 "\n"\
    "\t""EndGlobalSection"                                                                                                                                                                            "\n"\
    "EndGlobal"                                                                                                                                                                                       "\n")



#define VCXPROJ( guid, configurationType, vcpkgEnabled, projectName, preprocessorDefinitions, precompiledHeader, additionalIncludeDirectories, subSystem, additionalLibraryDirectories, additionalDependencies, clIncludes, clCompiles, images, nones, projectReferences ) (\
    "<?xml version=\"1.0\" encoding=\"utf-8\"?>"                                                                                                                                                                        "\n"\
    "<Project DefaultTargets=\"Build\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">"                                                                                                                  "\n"\
    "    <ItemGroup Label=\"ProjectConfigurations\">"                                                                                                                                                                   "\n"\
    "        <ProjectConfiguration Include=\"Debug|Win32\">"                                                                                                                                                            "\n"\
    "            <Configuration>Debug</Configuration>"                                                                                                                                                                  "\n"\
    "            <Platform>Win32</Platform>"                                                                                                                                                                            "\n"\
    "        </ProjectConfiguration>"                                                                                                                                                                                   "\n"\
    "        <ProjectConfiguration Include=\"Release|Win32\">"                                                                                                                                                          "\n"\
    "            <Configuration>Release</Configuration>"                                                                                                                                                                "\n"\
    "            <Platform>Win32</Platform>"                                                                                                                                                                            "\n"\
    "        </ProjectConfiguration>"                                                                                                                                                                                   "\n"\
    "        <ProjectConfiguration Include=\"Debug|x64\">"                                                                                                                                                              "\n"\
    "            <Configuration>Debug</Configuration>"                                                                                                                                                                  "\n"\
    "            <Platform>x64</Platform>"                                                                                                                                                                              "\n"\
    "        </ProjectConfiguration>"                                                                                                                                                                                   "\n"\
    "        <ProjectConfiguration Include=\"Release|x64\">"                                                                                                                                                            "\n"\
    "            <Configuration>Release</Configuration>"                                                                                                                                                                "\n"\
    "            <Platform>x64</Platform>"                                                                                                                                                                              "\n"\
    "        </ProjectConfiguration>"                                                                                                                                                                                   "\n"\
    "    </ItemGroup>"                                                                                                                                                                                                  "\n"\
    "    <PropertyGroup Label=\"Globals\">"                                                                                                                                                                             "\n"\
    /*"        <VCProjectVersion>17.0</VCProjectVersion>"                                                                                                                                                               "\n"*/\
    "        <Keyword>Win32Proj</Keyword>"                                                                                                                                                                              "\n"\
    "        <ProjectGuid>{" + (guid) + "}</ProjectGuid>"                                                                                                                                                               "\n"\
    "        <RootNamespace>MonProjet1</RootNamespace>"                                                                                                                                                                 "\n"\
    /*"        <WindowsTargetPlatformVersion>10.0</WindowsTargetPlatformVersion>"                                                                                                                                       "\n"*/\
    "    </PropertyGroup>"                                                                                                                                                                                              "\n"\
    "    <Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.Default.props\" />"                                                                                                                                          "\n"\
    "    <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|Win32'\" Label=\"Configuration\">"                                                                                                           "\n"\
    "        <ConfigurationType>" + (configurationType) + "</ConfigurationType>"                                                                                                                                        "\n"\
    "        <UseDebugLibraries>true</UseDebugLibraries>"                                                                                                                                                               "\n"\
    "        <PlatformToolset>v143</PlatformToolset>"                                                                                                                                                                   "\n"\
    "        <CharacterSet>Unicode</CharacterSet>"                                                                                                                                                                      "\n"\
    "    </PropertyGroup>"                                                                                                                                                                                              "\n"\
    "    <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|Win32'\" Label=\"Configuration\">"                                                                                                         "\n"\
    "        <ConfigurationType>" + (configurationType) + "</ConfigurationType>"                                                                                                                                        "\n"\
    "        <UseDebugLibraries>false</UseDebugLibraries>"                                                                                                                                                              "\n"\
    "        <PlatformToolset>v143</PlatformToolset>"                                                                                                                                                                   "\n"\
    "        <WholeProgramOptimization>true</WholeProgramOptimization>"                                                                                                                                                 "\n"\
    "        <CharacterSet>Unicode</CharacterSet>"                                                                                                                                                                      "\n"\
    "    </PropertyGroup>"                                                                                                                                                                                              "\n"\
    "    <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\" Label=\"Configuration\">"                                                                                                             "\n"\
    "        <ConfigurationType>" + (configurationType) + "</ConfigurationType>"                                                                                                                                        "\n"\
    "        <UseDebugLibraries>true</UseDebugLibraries>"                                                                                                                                                               "\n"\
    "        <PlatformToolset>v143</PlatformToolset>"                                                                                                                                                                   "\n"\
    "        <CharacterSet>Unicode</CharacterSet>"                                                                                                                                                                      "\n"\
    "    </PropertyGroup>"                                                                                                                                                                                              "\n"\
    "    <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\" Label=\"Configuration\">"                                                                                                           "\n"\
    "        <ConfigurationType>" + (configurationType) + "</ConfigurationType>"                                                                                                                                        "\n"\
    "        <UseDebugLibraries>false</UseDebugLibraries>"                                                                                                                                                              "\n"\
    "        <PlatformToolset>v143</PlatformToolset>"                                                                                                                                                                   "\n"\
    "        <WholeProgramOptimization>true</WholeProgramOptimization>"                                                                                                                                                 "\n"\
    "        <CharacterSet>Unicode</CharacterSet>"                                                                                                                                                                      "\n"\
    "    </PropertyGroup>"                                                                                                                                                                                              "\n"\
    "    <Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.props\" />"                                                                                                                                                  "\n"\
    "    <ImportGroup Label=\"ExtensionSettings\">"                                                                                                                                                                     "\n"\
    "    </ImportGroup>"                                                                                                                                                                                                "\n"\
    "    <ImportGroup Label=\"Shared\">"                                                                                                                                                                                "\n"\
    "    </ImportGroup>"                                                                                                                                                                                                "\n"\
    "    <ImportGroup Label=\"PropertySheets\" Condition=\"'$(Configuration)|$(Platform)'=='Debug|Win32'\">"                                                                                                            "\n"\
    "        <Import Project=\"$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props\" Condition=\"exists('$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props')\" Label=\"LocalAppDataPlatform\" />"                   "\n"\
    "    </ImportGroup>"                                                                                                                                                                                                "\n"\
    "    <ImportGroup Label=\"PropertySheets\" Condition=\"'$(Configuration)|$(Platform)'=='Release|Win32'\">"                                                                                                          "\n"\
    "        <Import Project=\"$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props\" Condition=\"exists('$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props')\" Label=\"LocalAppDataPlatform\" />"                   "\n"\
    "    </ImportGroup>"                                                                                                                                                                                                "\n"\
    "    <ImportGroup Label=\"PropertySheets\" Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\">"                                                                                                              "\n"\
    "        <Import Project=\"$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props\" Condition=\"exists('$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props')\" Label=\"LocalAppDataPlatform\" />"                   "\n"\
    "    </ImportGroup>"                                                                                                                                                                                                "\n"\
    "    <ImportGroup Label=\"PropertySheets\" Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\">"                                                                                                            "\n"\
    "        <Import Project=\"$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props\" Condition=\"exists('$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props')\" Label=\"LocalAppDataPlatform\" />"                   "\n"\
    "    </ImportGroup>"                                                                                                                                                                                                "\n"\
    "    <PropertyGroup Label=\"UserMacros\" />"                                                                                                                                                                        "\n"\
    "    <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|Win32'\">"                                                                                                                                   "\n"\
    "        <OutDir>$(ProjectDir)$(Platform)\\$(Configuration)\\</OutDir>"                                                                                                                                             "\n"\
    "        <IntDir>$(ProjectDir)$(Platform)\\$(Configuration)\\intermediate\\</IntDir>"                                                                                                                               "\n"\
    "    </PropertyGroup>"                                                                                                                                                                                              "\n"\
    "    <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|Win32'\">"                                                                                                                                 "\n"\
    "        <OutDir>$(ProjectDir)$(Platform)\\$(Configuration)\\</OutDir>"                                                                                                                                             "\n"\
    "        <IntDir>$(ProjectDir)$(Platform)\\$(Configuration)\\intermediate\\</IntDir>"                                                                                                                               "\n"\
    "    </PropertyGroup>"                                                                                                                                                                                              "\n"\
    "    <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\">"                                                                                                                                     "\n"\
    "        <OutDir>$(ProjectDir)$(Platform)\\$(Configuration)\\</OutDir>"                                                                                                                                             "\n"\
    "        <IntDir>$(ProjectDir)$(Platform)\\$(Configuration)\\intermediate\\</IntDir>"                                                                                                                               "\n"\
    "    </PropertyGroup>"                                                                                                                                                                                              "\n"\
    "    <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\">"                                                                                                                                   "\n"\
    "        <OutDir>$(ProjectDir)$(Platform)\\$(Configuration)\\</OutDir>"                                                                                                                                             "\n"\
    "        <IntDir>$(ProjectDir)$(Platform)\\$(Configuration)\\intermediate\\</IntDir>"                                                                                                                               "\n"\
    "    </PropertyGroup>"                                                                                                                                                                                              "\n"\
    "    <PropertyGroup Label=\"Vcpkg\">"                                                                                                                                                                               "\n"\
    "        <VcpkgEnabled>" + (vcpkgEnabled) + "</VcpkgEnabled>"                                                                                                                                                       "\n"\
    "        <VcpkgEnableManifest>" + (vcpkgEnabled) + "</VcpkgEnableManifest>"                                                                                                                                         "\n"\
    "        <VcpkgManifestRoot>$(SolutionDir)..\\config\\" + (projectName) + "</VcpkgManifestRoot>"                                                                                                                    "\n"\
    "        <VcpkgInstalledDir>$(SolutionDir)\\vcpkg_installed\\$(VcpkgTriplet)</VcpkgInstalledDir>"                                                                                                                   "\n"\
    "    </PropertyGroup>"                                                                                                                                                                                              "\n"\
    "    <ItemDefinitionGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|Win32'\">"                                                                                                                             "\n"\
    "        <ClCompile>"                                                                                                                                                                                               "\n"\
    "            <WarningLevel>Level3</WarningLevel>"                                                                                                                                                                   "\n"\
    "            <SDLCheck>true</SDLCheck>"                                                                                                                                                                             "\n"\
    "            <PreprocessorDefinitions>WIN32;_DEBUG;" + (preprocessorDefinitions) + "%(PreprocessorDefinitions)</PreprocessorDefinitions>"                                                                           "\n"\
    "            <ConformanceMode>true</ConformanceMode>"                                                                                                                                                               "\n"\
    "            <LanguageStandard>stdcpp20</LanguageStandard>"                                                                                                                                                         "\n"\
    "            <PrecompiledHeader>" + (precompiledHeader) + "</PrecompiledHeader>"                                                                                                                                    "\n"\
    "            <PrecompiledHeaderFile>pch.h</PrecompiledHeaderFile>"                                                                                                                                                  "\n"\
    "            <AdditionalIncludeDirectories>$(SolutionDir)..\\src;$(SolutionDir)..\\src\\" + (projectName) + ";" + (additionalIncludeDirectories) + "%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>" "\n"\
    "        </ClCompile>"                                                                                                                                                                                              "\n"\
    "        <Link>"                                                                                                                                                                                                    "\n"\
    "            <SubSystem>" + (subSystem) + "</SubSystem>"                                                                                                                                                            "\n"\
    "            <GenerateDebugInformation>true</GenerateDebugInformation>"                                                                                                                                             "\n"\
    "            <AdditionalLibraryDirectories>" + (additionalLibraryDirectories) + "%(AdditionalLibraryDirectories)</AdditionalLibraryDirectories>"                                                                    "\n"\
    "            <AdditionalDependencies>" + (additionalDependencies) + "%(AdditionalDependencies)</AdditionalDependencies>"                                                                                            "\n"\
    "        </Link>"                                                                                                                                                                                                   "\n"\
    "    </ItemDefinitionGroup>"                                                                                                                                                                                        "\n"\
    "    <ItemDefinitionGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|Win32'\">"                                                                                                                           "\n"\
    "        <ClCompile>"                                                                                                                                                                                               "\n"\
    "            <WarningLevel>Level3</WarningLevel>"                                                                                                                                                                   "\n"\
    "            <FunctionLevelLinking>true</FunctionLevelLinking>"                                                                                                                                                     "\n"\
    "            <IntrinsicFunctions>true</IntrinsicFunctions>"                                                                                                                                                         "\n"\
    "            <SDLCheck>true</SDLCheck>"                                                                                                                                                                             "\n"\
    "            <PreprocessorDefinitions>WIN32;NDEBUG;" + (preprocessorDefinitions) + "%(PreprocessorDefinitions)</PreprocessorDefinitions>"                                                                           "\n"\
    "            <ConformanceMode>true</ConformanceMode>"                                                                                                                                                               "\n"\
    "            <LanguageStandard>stdcpp20</LanguageStandard>"                                                                                                                                                         "\n"\
    "            <PrecompiledHeader>" + (precompiledHeader) + "</PrecompiledHeader>"                                                                                                                                    "\n"\
    "            <PrecompiledHeaderFile>pch.h</PrecompiledHeaderFile>"                                                                                                                                                  "\n"\
    "            <AdditionalIncludeDirectories>$(SolutionDir)..\\src;$(SolutionDir)..\\src\\" + (projectName) + ";" + (additionalIncludeDirectories) + "%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>" "\n"\
    "        </ClCompile>"                                                                                                                                                                                              "\n"\
    "        <Link>"                                                                                                                                                                                                    "\n"\
    "            <SubSystem>" + (subSystem) + "</SubSystem>"                                                                                                                                                            "\n"\
    "            <EnableCOMDATFolding>true</EnableCOMDATFolding>"                                                                                                                                                       "\n"\
    "            <OptimizeReferences>true</OptimizeReferences>"                                                                                                                                                         "\n"\
    "            <GenerateDebugInformation>true</GenerateDebugInformation>"                                                                                                                                             "\n"\
    "            <AdditionalLibraryDirectories>" + (additionalLibraryDirectories) + "%(AdditionalLibraryDirectories)</AdditionalLibraryDirectories>"                                                                    "\n"\
    "            <AdditionalDependencies>" + (additionalDependencies) + "%(AdditionalDependencies)</AdditionalDependencies>"                                                                                            "\n"\
    "        </Link>"                                                                                                                                                                                                   "\n"\
    "    </ItemDefinitionGroup>"                                                                                                                                                                                        "\n"\
    "    <ItemDefinitionGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\">"                                                                                                                               "\n"\
    "        <ClCompile>"                                                                                                                                                                                               "\n"\
    "            <WarningLevel>Level3</WarningLevel>"                                                                                                                                                                   "\n"\
    "            <SDLCheck>true</SDLCheck>"                                                                                                                                                                             "\n"\
    "            <PreprocessorDefinitions>_DEBUG;" + (preprocessorDefinitions) + "%(PreprocessorDefinitions)</PreprocessorDefinitions>"                                                                                 "\n"\
    "            <ConformanceMode>true</ConformanceMode>"                                                                                                                                                               "\n"\
    "            <LanguageStandard>stdcpp20</LanguageStandard>"                                                                                                                                                         "\n"\
    "            <PrecompiledHeader>" + (precompiledHeader) + "</PrecompiledHeader>"                                                                                                                                    "\n"\
    "            <PrecompiledHeaderFile>pch.h</PrecompiledHeaderFile>"                                                                                                                                                  "\n"\
    "            <AdditionalIncludeDirectories>$(SolutionDir)..\\src;$(SolutionDir)..\\src\\" + (projectName) + ";" + (additionalIncludeDirectories) + "%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>" "\n"\
    "        </ClCompile>"                                                                                                                                                                                              "\n"\
    "        <Link>"                                                                                                                                                                                                    "\n"\
    "            <SubSystem>" + (subSystem) + "</SubSystem>"                                                                                                                                                            "\n"\
    "            <GenerateDebugInformation>true</GenerateDebugInformation>"                                                                                                                                             "\n"\
    "            <AdditionalLibraryDirectories>" + (additionalLibraryDirectories) + "%(AdditionalLibraryDirectories)</AdditionalLibraryDirectories>"                                                                    "\n"\
    "            <AdditionalDependencies>" + (additionalDependencies) + "%(AdditionalDependencies)</AdditionalDependencies>"                                                                                            "\n"\
    "        </Link>"                                                                                                                                                                                                   "\n"\
    "    </ItemDefinitionGroup>"                                                                                                                                                                                        "\n"\
    "    <ItemDefinitionGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\">"                                                                                                                             "\n"\
    "        <ClCompile>"                                                                                                                                                                                               "\n"\
    "            <WarningLevel>Level3</WarningLevel>"                                                                                                                                                                   "\n"\
    "            <FunctionLevelLinking>true</FunctionLevelLinking>"                                                                                                                                                     "\n"\
    "            <IntrinsicFunctions>true</IntrinsicFunctions>"                                                                                                                                                         "\n"\
    "            <SDLCheck>true</SDLCheck>"                                                                                                                                                                             "\n"\
    "            <PreprocessorDefinitions>NDEBUG;" + (preprocessorDefinitions) + "%(PreprocessorDefinitions)</PreprocessorDefinitions>"                                                                                 "\n"\
    "            <ConformanceMode>true</ConformanceMode>"                                                                                                                                                               "\n"\
    "            <LanguageStandard>stdcpp20</LanguageStandard>"                                                                                                                                                         "\n"\
    "            <PrecompiledHeader>" + (precompiledHeader) + "</PrecompiledHeader>"                                                                                                                                    "\n"\
    "            <PrecompiledHeaderFile>pch.h</PrecompiledHeaderFile>"                                                                                                                                                  "\n"\
    "            <AdditionalIncludeDirectories>$(SolutionDir)..\\src;$(SolutionDir)..\\src\\" + (projectName) + ";" + (additionalIncludeDirectories) + "%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>" "\n"\
    "        </ClCompile>"                                                                                                                                                                                              "\n"\
    "        <Link>"                                                                                                                                                                                                    "\n"\
    "            <SubSystem>" + (subSystem) + "</SubSystem>"                                                                                                                                                            "\n"\
    "            <EnableCOMDATFolding>true</EnableCOMDATFolding>"                                                                                                                                                       "\n"\
    "            <OptimizeReferences>true</OptimizeReferences>"                                                                                                                                                         "\n"\
    "            <GenerateDebugInformation>true</GenerateDebugInformation>"                                                                                                                                             "\n"\
    "            <AdditionalLibraryDirectories>" + (additionalLibraryDirectories) + "%(AdditionalLibraryDirectories)</AdditionalLibraryDirectories>"                                                                    "\n"\
    "            <AdditionalDependencies>" + (additionalDependencies) + "%(AdditionalDependencies)</AdditionalDependencies>"                                                                                            "\n"\
    "        </Link>"                                                                                                                                                                                                   "\n"\
    "    </ItemDefinitionGroup>"                                                                                                                                                                                        "\n"\
    "    <ItemGroup>"                                                                                                                                                                                                   "\n"\
    + (clIncludes) +                                                                                                                                                                                                        \
    "    </ItemGroup>"                                                                                                                                                                                                  "\n"\
    "    <ItemGroup>"                                                                                                                                                                                                   "\n"\
    + (clCompiles) +                                                                                                                                                                                                        \
    "    </ItemGroup>"                                                                                                                                                                                                  "\n"\
    "    <ItemGroup>"                                                                                                                                                                                                   "\n"\
    + (images) +                                                                                                                                                                                                            \
    "    </ItemGroup>"                                                                                                                                                                                                  "\n"\
    "    <ItemGroup>"                                                                                                                                                                                                   "\n"\
    + (nones) +                                                                                                                                                                                                             \
    "    </ItemGroup>"                                                                                                                                                                                                  "\n"\
    "    <ItemGroup>"                                                                                                                                                                                                   "\n"\
    + (projectReferences) +                                                                                                                                                                                                 \
    "    </ItemGroup>"                                                                                                                                                                                                  "\n"\
    "    <Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.targets\" />"                                                                                                                                                "\n"\
    "    <ImportGroup Label=\"ExtensionTargets\">"                                                                                                                                                                      "\n"\
    "    </ImportGroup>"                                                                                                                                                                                                "\n"\
    "</Project>")

#define CLCOMPILE_PCH_CPP( subFolder, fileName ) (\
    "        <ClCompile Include=\"$(SolutionDir)..\\src\\" + (subFolder) + "\\" + (fileName) + "\">"                                                                                                                    "\n"\
    "            <PrecompiledHeader Condition=\"&apos;$(Configuration)|$(Platform)&apos;==&apos;Debug|Win32&apos;\">Create</PrecompiledHeader>"                                                                         "\n"\
    "            <PrecompiledHeader Condition=\"&apos;$(Configuration)|$(Platform)&apos;==&apos;Release|Win32&apos;\">Create</PrecompiledHeader>"                                                                       "\n"\
    "            <PrecompiledHeader Condition=\"&apos;$(Configuration)|$(Platform)&apos;==&apos;Debug|x64&apos;\">Create</PrecompiledHeader>"                                                                           "\n"\
    "            <PrecompiledHeader Condition=\"&apos;$(Configuration)|$(Platform)&apos;==&apos;Release|x64&apos;\">Create</PrecompiledHeader>"                                                                         "\n"\
    "        </ClCompile>"                                                                                                                                                                                              "\n")

#define VCXPROJ_FILTERS( clIncludes, clCompiles, images, nones ) (\
    "<?xml version=\"1.0\" encoding=\"utf-8\"?>"                                                                                                                                                                        "\n"\
    "<Project ToolsVersion=\"4.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">"                                                                                                                      "\n"\
    "    <ItemGroup>"                                                                                                                                                                                                   "\n"\
    "        <Filter Include=\"Source Files\">"                                                                                                                                                                         "\n"\
    "            <UniqueIdentifier>{4FC737F1-C7A5-4376-A066-2A32D752A2FF}</UniqueIdentifier>"                                                                                                                           "\n"\
    "            <Extensions>cpp;c;cc;cxx;c++;cppm;ixx;def;odl;idl;hpj;bat;asm;asmx</Extensions>"                                                                                                                       "\n"\
    "        </Filter>"                                                                                                                                                                                                 "\n"\
    "        <Filter Include=\"Header Files\">"                                                                                                                                                                         "\n"\
    "            <UniqueIdentifier>{93995380-89BD-4B04-88EB-625FBE52EBFB}</UniqueIdentifier>"                                                                                                                           "\n"\
    "            <Extensions>h;hh;hpp;hxx;h++;hm;inl;inc;ipp;xsd</Extensions>"                                                                                                                                          "\n"\
    "        </Filter>"                                                                                                                                                                                                 "\n"\
    "        <Filter Include=\"Images\">"                                                                                                                                                                               "\n"\
    "            <UniqueIdentifier>{6E901252-3135-5382-5769-143D295A57A6}</UniqueIdentifier>"                                                                                                                           "\n"\
    "            <Extensions>png;jpg;jpeg;dds;bmp;tif;tiff;gif;ico;svg</Extensions>"                                                                                                                                    "\n"\
    "        </Filter>"                                                                                                                                                                                                 "\n"\
    "        <Filter Include=\"Resource Files\">"                                                                                                                                                                       "\n"\
    "            <UniqueIdentifier>{67DA6AB6-F800-4C08-8B7A-83BB121AAD01}</UniqueIdentifier>"                                                                                                                           "\n"\
    "            <Extensions>rc;cur;dlg;rc2;rct;bin;rgs;resx;wav;mfcribbon-ms</Extensions>"                                                                                                                             "\n"\
    "        </Filter>"                                                                                                                                                                                                 "\n"\
    "    </ItemGroup>"                                                                                                                                                                                                  "\n"\
    "    <ItemGroup>"                                                                                                                                                                                                   "\n"\
    + (clIncludes) +                                                                                                                                                                                                        \
    "    </ItemGroup>"                                                                                                                                                                                                  "\n"\
    "    <ItemGroup>"                                                                                                                                                                                                   "\n"\
    + (clCompiles) +                                                                                                                                                                                                        \
    "    </ItemGroup>"                                                                                                                                                                                                  "\n"\
    "    <ItemGroup>"                                                                                                                                                                                                   "\n"\
    + (images) +                                                                                                                                                                                                            \
    "    </ItemGroup>"                                                                                                                                                                                                  "\n"\
    "    <ItemGroup>"                                                                                                                                                                                                   "\n"\
    + (nones) +                                                                                                                                                                                                             \
    "    </ItemGroup>"                                                                                                                                                                                                  "\n"\
    "</Project>")



#define ERROR_IF( function, message ) \
    if ( function )\
    {\
        std::cout << FG_ERROR message STYLE_RESET;\
        return 1;\
    }

#define CHECK_FOR_ERROR( function ) \
    if ( SolutionGenerator::function != 0 )\
        return 1;


