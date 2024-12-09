#ifndef SOLUTION_GENERATOR_H_INCLUDED
#define SOLUTION_GENERATOR_H_INCLUDED

#include "Json.hpp"

namespace SolutionGenerator {


std::string GenerateGuid();



std::string CreateRepository( std::string const& repositoryName,
                              std::string const& solutionName,
                              std::string const& projectName,
                              bool pch,
                              bool vcpkg,
                              bool lib,
                              bool window );

std::string CreateSolutionConfig( std::string const& repositoryName,
                                  std::string const& solutionName );

std::string CreateProject( std::string const& repositoryName,
                           std::string const& projectName,
                           bool pch,
                           bool vcpkg,
                           bool lib,
                           bool window );

std::string CreateProjectConfig( std::string const& repositoryName,
                              std::string const& projectName,
                              bool pch,
                              bool vcpkg,
                              bool lib,
                              bool window );

std::string CreateProjectSrc( std::string const& repositoryName,
                              std::string const& projectName,
                              bool pch,
                              bool lib,
                              bool window );



std::string AddDependencyToProjectConfig( std::string const& repositoryName,
                                          std::string const& projectName,
                                          std::string const& dependency );

std::string AddDependenciesToProjectConfig( std::string const& repositoryName,
                                            std::string const& projectName,
                                            std::vector<std::string> const& dependencies );



std::string MakeSolution( std::string const& repositoryName,
                          bool clear,
                          bool open );

std::string MakeSolution( std::string const& repositoryName,
                          std::string const& projectName,
                          bool clear,
                          bool open );

std::string MakeSolution( std::string const& repositoryName,
                          std::vector<std::array<std::string, 2>>& projects,
                          nlohmann::json const& settingsJson );

std::string MakeProject( std::string const& repositoryName,
                         std::string const& projectName,
                         nlohmann::json const& settingsJson );

void AddSrcToVcxproj( std::string const& srcPath,
                      std::string const& subFolder,
                      std::ofstream& vcxproj );

void AddDependenciesToSln( nlohmann::json const& settingsJson,
                           std::string const& projectName,
                           std::string& projectsForSln,
                           std::vector<std::array<std::string, 2>>& projects );


}


#endif