#ifndef SOLUTION_GENERATOR_H_INCLUDED
#define SOLUTION_GENERATOR_H_INCLUDED

#include "Json.hpp"

namespace SolutionGenerator {


std::string GenerateGuid();



void CheckVersion( std::string const& repositoryName );



int CreateRepository( std::string const& repositoryName,
                      std::string const& solutionName,
                      std::string const& projectName,
                      bool pch,
                      bool vcpkg,
                      bool lib,
                      bool window );

int CreateBats( std::string const& repositoryName );

int CreateBats( std::string const& repositoryName,
                std::string const& projectName );

int CreateSolutionConfig( std::string const& repositoryName,
                          std::string const& solutionName );

int CreateProject( std::string const& repositoryName,
                   std::string const& projectName,
                   bool startup,
                   bool pch,
                   bool vcpkg,
                   bool lib,
                   bool window );

int CreateProjectConfig( std::string const& repositoryName,
                         std::string const& projectName,
                         bool startup,
                         bool pch,
                         bool vcpkg,
                         bool lib,
                         bool window );

int CreateVcpkgJson( std::string const& repositoryName,
                     std::string const& projectName );

int CreateProjectSrc( std::string const& repositoryName,
                      std::string const& projectName,
                      bool pch,
                      bool lib,
                      bool window );



int AddDependency( std::string const& repositoryName,
                   std::string const& projectName,
                   std::string const& dependency );

int AddDependency( std::string const& repositoryName,
                   std::string const& projectName,
                   std::vector<std::string> const& dependencies );

int AddPortVcpkg( std::string const& repositoryName,
                  std::string const& projectName,
                  std::string const& port );

int AddPortVcpkg( std::string const& repositoryName,
                  std::string const& projectName,
                  std::vector<std::string> const& ports );



int MakeSolution( std::string const& repositoryName,
                  bool clear,
                  bool open );

int MakeSolution( std::string const& repositoryName,
                  std::string const& projectName,
                  bool clear,
                  bool open );

int MakeSolution( std::string const& repositoryName,
                  std::vector<std::array<std::string, 2>>& projects,
                  nlohmann::json const& settingsJson );

int MakeProject( std::string const& repositoryName,
                 std::string const& projectName,
                 nlohmann::json const& settingsJson );

int AddSrcToVcxproj( std::string const& srcPath,
                     std::string const& subFolder,
                     std::ofstream& vcxproj );

int AddResToVcxproj( std::string const& resPath,
                     std::string const& subFolder,
                     std::ofstream& vcxproj );

int AddDependenciesToSln( nlohmann::json const& settingsJson,
                          std::string const& projectName,
                          std::string& projectsForSln,
                          std::vector<std::array<std::string, 2>>& projects );


}


#endif