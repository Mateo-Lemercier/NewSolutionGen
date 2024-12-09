#ifndef SOLUTION_GENERATOR_INL_INCLUDED
#define SOLUTION_GENERATOR_INL_INCLUDED

#include <array>

namespace SolutionGenerator {


template <unsigned int size>
std::string AddDependenciesToProjectConfig( std::string const& repositoryName,
                                            std::string const& projectName,
                                            std::array<std::string const&, size> const& dependencies )
{
    for ( std::string const& dependency : dependencies )
        if ( std::string errorMessage = AddDependencyToProjectConfig( repositoryName, projectName, dependency );
            errorMessage.empty() == false )
            return errorMessage;
    return "";
}


}
#endif