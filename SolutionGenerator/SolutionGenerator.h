#ifndef SOLUTION_GENERATOR_H_INCLUDED
#define SOLUTION_GENERATOR_H_INCLUDED

#include "Json.hpp"
#include <string>

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

int CreateProject( std::string const& repositoryName,
                   std::string const& projectName,
                   bool startup,
                   bool pch,
                   bool vcpkg,
                   bool lib,
                   bool window );

int RenameProject( std::string const& repositoryName,
                   std::string const& projectName,
                   std::string const& newName );

int RemoveProject( std::string const& repositoryName,
                   std::string const& projectName );

int CreateBats( std::string const& repositoryName,
                std::string const& projectName );

int DeleteBats( std::string const& repositoryName,
                std::string const& projectName );

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



int EditProperties( std::string const& repositoryName,
                    std::string const& projectName,
                    std::vector<std::string> const& dependencies,
                    bool startup,
                    bool changePch,
                    bool changeVcpkg,
                    bool changeLib,
                    bool changeWindow );

int EnablePchProperty( nlohmann::json& settingsJson,
                       std::string const& repositoryName,
                       std::string const& projectName,
                       bool window );

int DisablePchProperty( nlohmann::json& settingsJson,
                        std::string const& repositoryName,
                        std::string const& projectName );

int EnableVcpkgProperty( nlohmann::json& settingsJson,
                         std::string const& repositoryName,
                         std::string const& projectName );

int DisableVcpkgProperty( nlohmann::json& settingsJson,
                          std::string const& repositoryName,
                          std::string const& projectName );

int EnableLibProperty( nlohmann::json& settingsJson,
                       std::string const& repositoryName,
                       std::string const& projectName );

int DisableLibProperty( nlohmann::json& settingsJson,
                        std::string const& repositoryName,
                        std::string const& projectName );

int AddDependency( nlohmann::json& settingsJson,
                   std::string const& repositoryName,
                   std::string const& projectName,
                   std::string const& dependency );

int AddDependency( std::string const& repositoryName,
                   std::string const& projectName,
                   std::vector<std::string> const& dependencies );

int RemoveDependency( nlohmann::json& settingsJson,
                      std::string const& projectName,
                      std::string const& dependency );

int RemoveDependency( std::string const& repositoryName,
                      std::string const& projectName,
                      std::vector<std::string> const& dependencies );

int AddPortVcpkg( nlohmann::json& settingsJson,
                  nlohmann::json& vcpkgJson,
                  std::string const& repositoryName,
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
                  nlohmann::json const& settingsJson,
                  bool clear,
                  bool open );

int AddDependenciesToSln( nlohmann::json const& settingsJson,
                          std::string const& projectName,
                          std::string& projectsForSln,
                          std::vector<std::array<std::string, 2>>& projects );

int MakeProject( std::string const& repositoryName,
                 std::string const& projectName,
                 nlohmann::json const& settingsJson );

int AddSrcToVcxproj( std::string const& srcPath,
                     std::string const& subFolder,
                     std::string& clIncludes,
                     std::string& clCompiles,
                     std::string& clIncludesFilters,
                     std::string& clCompilesFilters );

int AddResToVcxproj( std::string const& resPath,
                     std::string const& subFolder,
                     std::string& images,
                     std::string& shaders,
                     std::string& nones,
                     std::string& imagesFilters,
                     std::string& nonesFilters );


}


#endif