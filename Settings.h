#pragma once



#define VERSION "1.17"



#define STYLE( style ) "\033[" style "m"
#define STYLE_RESET STYLE( "0" )
#define FG_RED STYLE( "31" )
#define FG_GREEN STYLE( "32" )



#define ACT( action ) "-" action
#define OBL( argument ) " [" argument "]"
#define OPT( argument ) " <" argument ">"
#define LAST "               "

#define HELP_MESSAGE "\n"\
    "Le Solution Generator est un outil permettant de generer des solutions Visual Studio."                        "\n"\
    "Utilisation : SolutionGen.exe -action [arguments_obligatoires] <argument_optionnels>"                         "\n"\
    ""                                                                                                             "\n"\
    "Actions Disponibles :"                                                                                        "\n"\
    "+-------------------------------------------------------------------------------------------------------------+\n"\
    "|                                                                                                             |\n"\
    "|  " ACT("help") LAST "                                                                                       |\n"\
    "|                                                                                                             |\n"\
    "|  " ACT("create") OBL("Nom_du_repos") LAST "                                                                 |\n"\
    "|                                                                                                             |\n"\
    "+-------------------------------------------------------------------------------------------------------------+\n"\
    ""



#define CONFIG_SETTINGS( solutionName, solutionGuid ) (\
    "{"                                                    "\n"\
    "    \"version\": " VERSION ","                        "\n"\
    "    \"solution_name\": \"" + ( solutionName ) + "\"," "\n"\
    "    \"solution_guid\": \"" + ( solutionGuid ) + "\"," "\n"\
    "    \"projects\": {}"                                 "\n"\
    "}")

#define PROJECT_CONFIG \
    "{"                                                    "\n"\
    "    \"guid\": \"\","                                  "\n"\
    "    \"pch\": false,"                                  "\n"\
    "    \"vcpkg\": false,"                                "\n"\
    "    \"lib\": false,"                                  "\n"\
    "    \"window\": false,"                               "\n"\
    "    \"dependencies\": []"                             "\n"\
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
    ""                                       "\n"\
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
    "#include \"main.h\""                    "\n"\
    "#include <iostream>"                    "\n"\
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
    "#include \"main.h\""                    "\n"\
    ""                                       "\n"\
    "int WinMain()"                          "\n"\
    "{"                                      "\n"\
    "    return 0;"                          "\n"\
    "}"

#define MAIN_CPP_PCH_WINDOW \
    "#include \"pch.h\""                     "\n"\
    "#include \"main.h\""                    "\n"\
    ""                                       "\n"\
    "int WinMain()"                          "\n"\
    "{"                                      "\n"\
    "    return 0;"                          "\n"\
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
    "        \"kind\": \"artifact\","                                                                      "\n"\
    "        \"location\": \"https://github.com/microsoft/vcpkg-ce-catalog/archive/refs/heads/main.zip\"," "\n"\
    "        \"name\": \"microsoft\""                                                                      "\n"\
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



#define VCXPROJ_1( guid, configurationType, vcpkgEnabled, projectName, preprocessorDefinitions, precompiledHeader, additionalIncludeDirectories, subSystem, additionalLibraryDirectories, additionalDependencies ) (\
    "<?xml version=\"1.0\" encoding=\"utf-8\"?>"                                                                                                                                                      "\n"\
    "<Project DefaultTargets=\"Build\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">"                                                                                                "\n"\
    "    <ItemGroup Label=\"ProjectConfigurations\">"                                                                                                                                                 "\n"\
    "        <ProjectConfiguration Include=\"Debug|Win32\">"                                                                                                                                          "\n"\
    "            <Configuration>Debug</Configuration>"                                                                                                                                                "\n"\
    "            <Platform>Win32</Platform>"                                                                                                                                                          "\n"\
    "        </ProjectConfiguration>"                                                                                                                                                                 "\n"\
    "        <ProjectConfiguration Include=\"Release|Win32\">"                                                                                                                                        "\n"\
    "            <Configuration>Release</Configuration>"                                                                                                                                              "\n"\
    "            <Platform>Win32</Platform>"                                                                                                                                                          "\n"\
    "        </ProjectConfiguration>"                                                                                                                                                                 "\n"\
    "        <ProjectConfiguration Include=\"Debug|x64\">"                                                                                                                                            "\n"\
    "            <Configuration>Debug</Configuration>"                                                                                                                                                "\n"\
    "            <Platform>x64</Platform>"                                                                                                                                                            "\n"\
    "        </ProjectConfiguration>"                                                                                                                                                                 "\n"\
    "        <ProjectConfiguration Include=\"Release|x64\">"                                                                                                                                          "\n"\
    "            <Configuration>Release</Configuration>"                                                                                                                                              "\n"\
    "            <Platform>x64</Platform>"                                                                                                                                                            "\n"\
    "        </ProjectConfiguration>"                                                                                                                                                                 "\n"\
    "    </ItemGroup>"                                                                                                                                                                                "\n"\
    "    <PropertyGroup Label=\"Globals\">"                                                                                                                                                           "\n"\
    /*"        <VCProjectVersion>17.0</VCProjectVersion>"                                                                                                                                               "\n"*/\
    "        <Keyword>Win32Proj</Keyword>"                                                                                                                                                            "\n"\
    "        <ProjectGuid>{" + (guid) + "}</ProjectGuid>"                                                                                                                                               "\n"\
    "        <RootNamespace>MonProjet1</RootNamespace>"                                                                                                                                               "\n"\
    /*"        <WindowsTargetPlatformVersion>10.0</WindowsTargetPlatformVersion>"                                                                                                                       "\n"*/\
    "    </PropertyGroup>"                                                                                                                                                                            "\n"\
    "    <Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.Default.props\" />"                                                                                                                        "\n"\
    "    <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|Win32'\" Label=\"Configuration\">"                                                                                         "\n"\
    "        <ConfigurationType>" + (configurationType) + "</ConfigurationType>"                                                                                                                      "\n"\
    "        <UseDebugLibraries>true</UseDebugLibraries>"                                                                                                                                             "\n"\
    "        <PlatformToolset>v143</PlatformToolset>"                                                                                                                                                 "\n"\
    "        <CharacterSet>Unicode</CharacterSet>"                                                                                                                                                    "\n"\
    "    </PropertyGroup>"                                                                                                                                                                            "\n"\
    "    <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|Win32'\" Label=\"Configuration\">"                                                                                       "\n"\
    "        <ConfigurationType>" + (configurationType) + "</ConfigurationType>"                                                                                                                      "\n"\
    "        <UseDebugLibraries>false</UseDebugLibraries>"                                                                                                                                            "\n"\
    "        <PlatformToolset>v143</PlatformToolset>"                                                                                                                                                 "\n"\
    "        <WholeProgramOptimization>true</WholeProgramOptimization>"                                                                                                                               "\n"\
    "        <CharacterSet>Unicode</CharacterSet>"                                                                                                                                                    "\n"\
    "    </PropertyGroup>"                                                                                                                                                                            "\n"\
    "    <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\" Label=\"Configuration\">"                                                                                           "\n"\
    "        <ConfigurationType>" + (configurationType) + "</ConfigurationType>"                                                                                                                      "\n"\
    "        <UseDebugLibraries>true</UseDebugLibraries>"                                                                                                                                             "\n"\
    "        <PlatformToolset>v143</PlatformToolset>"                                                                                                                                                 "\n"\
    "        <CharacterSet>Unicode</CharacterSet>"                                                                                                                                                    "\n"\
    "    </PropertyGroup>"                                                                                                                                                                            "\n"\
    "    <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\" Label=\"Configuration\">"                                                                                         "\n"\
    "        <ConfigurationType>" + (configurationType) + "</ConfigurationType>"                                                                                                                      "\n"\
    "        <UseDebugLibraries>false</UseDebugLibraries>"                                                                                                                                            "\n"\
    "        <PlatformToolset>v143</PlatformToolset>"                                                                                                                                                 "\n"\
    "        <WholeProgramOptimization>true</WholeProgramOptimization>"                                                                                                                               "\n"\
    "        <CharacterSet>Unicode</CharacterSet>"                                                                                                                                                    "\n"\
    "    </PropertyGroup>"                                                                                                                                                                            "\n"\
    "    <Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.props\" />"                                                                                                                                "\n"\
    "    <ImportGroup Label=\"ExtensionSettings\">"                                                                                                                                                   "\n"\
    "    </ImportGroup>"                                                                                                                                                                              "\n"\
    "    <ImportGroup Label=\"Shared\">"                                                                                                                                                              "\n"\
    "    </ImportGroup>"                                                                                                                                                                              "\n"\
    "    <ImportGroup Label=\"PropertySheets\" Condition=\"'$(Configuration)|$(Platform)'=='Debug|Win32'\">"                                                                                          "\n"\
    "        <Import Project=\"$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props\" Condition=\"exists('$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props')\" Label=\"LocalAppDataPlatform\" />" "\n"\
    "    </ImportGroup>"                                                                                                                                                                              "\n"\
    "    <ImportGroup Label=\"PropertySheets\" Condition=\"'$(Configuration)|$(Platform)'=='Release|Win32'\">"                                                                                        "\n"\
    "        <Import Project=\"$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props\" Condition=\"exists('$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props')\" Label=\"LocalAppDataPlatform\" />" "\n"\
    "    </ImportGroup>"                                                                                                                                                                              "\n"\
    "    <ImportGroup Label=\"PropertySheets\" Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\">"                                                                                            "\n"\
    "        <Import Project=\"$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props\" Condition=\"exists('$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props')\" Label=\"LocalAppDataPlatform\" />" "\n"\
    "    </ImportGroup>"                                                                                                                                                                              "\n"\
    "    <ImportGroup Label=\"PropertySheets\" Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\">"                                                                                          "\n"\
    "        <Import Project=\"$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props\" Condition=\"exists('$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props')\" Label=\"LocalAppDataPlatform\" />" "\n"\
    "    </ImportGroup>"                                                                                                                                                                              "\n"\
    "    <PropertyGroup Label=\"UserMacros\" />"                                                                                                                                                      "\n"\
    "    <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|Win32'\">"                                                                                                                 "\n"\
    "        <OutDir>$(ProjectDir)$(Platform)\\$(Configuration)\\</OutDir>"                                                                                                                           "\n"\
    "        <IntDir>$(ProjectDir)$(Platform)\\$(Configuration)\\intermediate\\</IntDir>"                                                                                                             "\n"\
    "    </PropertyGroup>"                                                                                                                                                                            "\n"\
    "    <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|Win32'\">"                                                                                                               "\n"\
    "        <OutDir>$(ProjectDir)$(Platform)\\$(Configuration)\\</OutDir>"                                                                                                                           "\n"\
    "        <IntDir>$(ProjectDir)$(Platform)\\$(Configuration)\\intermediate\\</IntDir>"                                                                                                             "\n"\
    "    </PropertyGroup>"                                                                                                                                                                            "\n"\
    "    <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\">"                                                                                                                   "\n"\
    "        <OutDir>$(ProjectDir)$(Platform)\\$(Configuration)\\</OutDir>"                                                                                                                           "\n"\
    "        <IntDir>$(ProjectDir)$(Platform)\\$(Configuration)\\intermediate\\</IntDir>"                                                                                                             "\n"\
    "    </PropertyGroup>"                                                                                                                                                                            "\n"\
    "    <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\">"                                                                                                                 "\n"\
    "        <OutDir>$(ProjectDir)$(Platform)\\$(Configuration)\\</OutDir>"                                                                                                                           "\n"\
    "        <IntDir>$(ProjectDir)$(Platform)\\$(Configuration)\\intermediate\\</IntDir>"                                                                                                             "\n"\
    "    </PropertyGroup>"                                                                                                                                                                            "\n"\
    "    <PropertyGroup Label=\"Vcpkg\">"                                                                                                                                                             "\n"\
    "        <VcpkgEnabled>" + (vcpkgEnabled) + "</VcpkgEnabled>"                                                                                                                                     "\n"\
    "        <VcpkgEnableManifest>" + (vcpkgEnabled) + "</VcpkgEnableManifest>"                                                                                                                       "\n"\
    "        <VcpkgManifestRoot>$(SolutionDir)..\\config\\" + (projectName) + "</VcpkgManifestRoot>"                                                                                                  "\n"\
    "        <VcpkgInstalledDir>$(SolutionDir)\\vcpkg_installed\\$(VcpkgTriplet)</VcpkgInstalledDir>"                                                                                                "\n"\
    "    </PropertyGroup>"                                                                                                                                                                            "\n"\
    "    <ItemDefinitionGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|Win32'\">"                                                                                                           "\n"\
    "        <ClCompile>"                                                                                                                                                                             "\n"\
    "            <WarningLevel>Level3</WarningLevel>"                                                                                                                                                 "\n"\
    "            <SDLCheck>true</SDLCheck>"                                                                                                                                                           "\n"\
    "            <PreprocessorDefinitions>WIN32;_DEBUG;_" + (preprocessorDefinitions) + ";%(PreprocessorDefinitions)</PreprocessorDefinitions>"                                                       "\n"\
    "            <ConformanceMode>true</ConformanceMode>"                                                                                                                                             "\n"\
    "            <LanguageStandard>stdcpp20</LanguageStandard>"                                                                                                                                       "\n"\
    "            <PrecompiledHeader>" + (precompiledHeader) + "</PrecompiledHeader>"                                                                                                                  "\n"\
    "            <PrecompiledHeaderFile>pch.h</PrecompiledHeaderFile>"                                                                                                                                "\n"\
    "            <AdditionalIncludeDirectories>" + (additionalIncludeDirectories) + "%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>"                                                  "\n"\
    "        </ClCompile>"                                                                                                                                                                            "\n"\
    "        <Link>"                                                                                                                                                                                  "\n"\
    "            <SubSystem>" + (subSystem) + "</SubSystem>"                                                                                                                                          "\n"\
    "            <GenerateDebugInformation>true</GenerateDebugInformation>"                                                                                                                           "\n"\
    "            <AdditionalLibraryDirectories>" + (additionalLibraryDirectories) + "%(AdditionalLibraryDirectories)</AdditionalLibraryDirectories>"                                                  "\n"\
    "            <AdditionalDependencies>" + (additionalDependencies) + "%(AdditionalDependencies)</AdditionalDependencies>"                                                                          "\n"\
    "        </Link>"                                                                                                                                                                                 "\n"\
    "    </ItemDefinitionGroup>"                                                                                                                                                                      "\n"\
    "    <ItemDefinitionGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|Win32'\">"                                                                                                         "\n"\
    "        <ClCompile>"                                                                                                                                                                             "\n"\
    "            <WarningLevel>Level3</WarningLevel>"                                                                                                                                                 "\n"\
    "            <FunctionLevelLinking>true</FunctionLevelLinking>"                                                                                                                                   "\n"\
    "            <IntrinsicFunctions>true</IntrinsicFunctions>"                                                                                                                                       "\n"\
    "            <SDLCheck>true</SDLCheck>"                                                                                                                                                           "\n"\
    "            <PreprocessorDefinitions>WIN32;NDEBUG;_" + (preprocessorDefinitions) + ";%(PreprocessorDefinitions)</PreprocessorDefinitions>"                                                       "\n"\
    "            <ConformanceMode>true</ConformanceMode>"                                                                                                                                             "\n"\
    "            <LanguageStandard>stdcpp20</LanguageStandard>"                                                                                                                                       "\n"\
    "            <PrecompiledHeader>" + (precompiledHeader) + "</PrecompiledHeader>"                                                                                                                  "\n"\
    "            <PrecompiledHeaderFile>pch.h</PrecompiledHeaderFile>"                                                                                                                                "\n"\
    "            <AdditionalIncludeDirectories>" + (additionalIncludeDirectories) + "%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>"                                                  "\n"\
    "        </ClCompile>"                                                                                                                                                                            "\n"\
    "        <Link>"                                                                                                                                                                                  "\n"\
    "            <SubSystem>" + (subSystem) + "</SubSystem>"                                                                                                                                          "\n"\
    "            <EnableCOMDATFolding>true</EnableCOMDATFolding>"                                                                                                                                     "\n"\
    "            <OptimizeReferences>true</OptimizeReferences>"                                                                                                                                       "\n"\
    "            <GenerateDebugInformation>true</GenerateDebugInformation>"                                                                                                                           "\n"\
    "            <AdditionalLibraryDirectories>" + (additionalLibraryDirectories) + "%(AdditionalLibraryDirectories)</AdditionalLibraryDirectories>"                                                  "\n"\
    "            <AdditionalDependencies>" + (additionalDependencies) + "%(AdditionalDependencies)</AdditionalDependencies>"                                                                          "\n"\
    "        </Link>"                                                                                                                                                                                 "\n"\
    "    </ItemDefinitionGroup>"                                                                                                                                                                      "\n"\
    "    <ItemDefinitionGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\">"                                                                                                             "\n"\
    "        <ClCompile>"                                                                                                                                                                             "\n"\
    "            <WarningLevel>Level3</WarningLevel>"                                                                                                                                                 "\n"\
    "            <SDLCheck>true</SDLCheck>"                                                                                                                                                           "\n"\
    "            <PreprocessorDefinitions>_DEBUG;_" + (preprocessorDefinitions) + ";%(PreprocessorDefinitions)</PreprocessorDefinitions>"                                                             "\n"\
    "            <ConformanceMode>true</ConformanceMode>"                                                                                                                                             "\n"\
    "            <LanguageStandard>stdcpp20</LanguageStandard>"                                                                                                                                       "\n"\
    "            <PrecompiledHeader>" + (precompiledHeader) + "</PrecompiledHeader>"                                                                                                                  "\n"\
    "            <PrecompiledHeaderFile>pch.h</PrecompiledHeaderFile>"                                                                                                                                "\n"\
    "            <AdditionalIncludeDirectories>" + (additionalIncludeDirectories) + "%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>"                                                  "\n"\
    "        </ClCompile>"                                                                                                                                                                            "\n"\
    "        <Link>"                                                                                                                                                                                  "\n"\
    "            <SubSystem>" + (subSystem) + "</SubSystem>"                                                                                                                                          "\n"\
    "            <GenerateDebugInformation>true</GenerateDebugInformation>"                                                                                                                           "\n"\
    "            <AdditionalLibraryDirectories>" + (additionalLibraryDirectories) + "%(AdditionalLibraryDirectories)</AdditionalLibraryDirectories>"                                                  "\n"\
    "            <AdditionalDependencies>" + (additionalDependencies) + "%(AdditionalDependencies)</AdditionalDependencies>"                                                                          "\n"\
    "        </Link>"                                                                                                                                                                                 "\n"\
    "    </ItemDefinitionGroup>"                                                                                                                                                                      "\n"\
    "    <ItemDefinitionGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\">"                                                                                                           "\n"\
    "        <ClCompile>"                                                                                                                                                                             "\n"\
    "            <WarningLevel>Level3</WarningLevel>"                                                                                                                                                 "\n"\
    "            <FunctionLevelLinking>true</FunctionLevelLinking>"                                                                                                                                   "\n"\
    "            <IntrinsicFunctions>true</IntrinsicFunctions>"                                                                                                                                       "\n"\
    "            <SDLCheck>true</SDLCheck>"                                                                                                                                                           "\n"\
    "            <PreprocessorDefinitions>NDEBUG;_" + (preprocessorDefinitions) + ";%(PreprocessorDefinitions)</PreprocessorDefinitions>"                                                             "\n"\
    "            <ConformanceMode>true</ConformanceMode>"                                                                                                                                             "\n"\
    "            <LanguageStandard>stdcpp20</LanguageStandard>"                                                                                                                                       "\n"\
    "            <PrecompiledHeader>" + (precompiledHeader) + "</PrecompiledHeader>"                                                                                                                  "\n"\
    "            <PrecompiledHeaderFile>pch.h</PrecompiledHeaderFile>"                                                                                                                                "\n"\
    "            <AdditionalIncludeDirectories>" + (additionalIncludeDirectories) + "%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>"                                                  "\n"\
    "        </ClCompile>"                                                                                                                                                                            "\n"\
    "        <Link>"                                                                                                                                                                                  "\n"\
    "            <SubSystem>" + (subSystem) + "</SubSystem>"                                                                                                                                          "\n"\
    "            <EnableCOMDATFolding>true</EnableCOMDATFolding>"                                                                                                                                     "\n"\
    "            <OptimizeReferences>true</OptimizeReferences>"                                                                                                                                       "\n"\
    "            <GenerateDebugInformation>true</GenerateDebugInformation>"                                                                                                                           "\n"\
    "            <AdditionalLibraryDirectories>" + (additionalLibraryDirectories) + "%(AdditionalLibraryDirectories)</AdditionalLibraryDirectories>"                                                  "\n"\
    "            <AdditionalDependencies>" + (additionalDependencies) + "%(AdditionalDependencies)</AdditionalDependencies>"                                                                          "\n"\
    "        </Link>"                                                                                                                                                                                 "\n"\
    "    </ItemDefinitionGroup>"                                                                                                                                                                      "\n"\
    "    <ItemGroup>"                                                                                                                                                                                 "\n")

#define VCXPROJ_2( projectReferences ) (\
    "    </ItemGroup>"                                                                                                                                                                                "\n"\
    "    <ItemGroup>"                                                                                                                                                                                 "\n"\
    + (projectReferences) +                                                                                                                                                                                 \
    "    </ItemGroup>"                                                                                                                                                                                "\n"\
    "    <Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.targets\" />"                                                                                                                              "\n"\
    "    <ImportGroup Label=\"ExtensionTargets\">"                                                                                                                                                    "\n"\
    "    </ImportGroup>"                                                                                                                                                                              "\n"\
    "</Project>")

#define CLCOMPILE_PCH_CPP( subFolder, fileName ) (\
    "        <ClCompile Include=\"$(SolutionDir)..\\src\\" + (subFolder) + "\\" + (fileName) + "\">"                                                                                                  "\n"\
    "            <PrecompiledHeader Condition=\"&apos;$(Configuration)|$(Platform)&apos;==&apos;Debug|Win32&apos;\">Create</PrecompiledHeader>"                                                       "\n"\
    "            <PrecompiledHeader Condition=\"&apos;$(Configuration)|$(Platform)&apos;==&apos;Release|Win32&apos;\">Create</PrecompiledHeader>"                                                     "\n"\
    "            <PrecompiledHeader Condition=\"&apos;$(Configuration)|$(Platform)&apos;==&apos;Debug|x64&apos;\">Create</PrecompiledHeader>"                                                         "\n"\
    "            <PrecompiledHeader Condition=\"&apos;$(Configuration)|$(Platform)&apos;==&apos;Release|x64&apos;\">Create</PrecompiledHeader>"                                                       "\n"\
    "        </ClCompile>"                                                                                                                                                                            "\n")


