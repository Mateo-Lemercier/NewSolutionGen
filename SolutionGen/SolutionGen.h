#ifndef SOLUTIONGEN_H_INCLUDED
#define SOLUTIONGEN_H_INCLUDED
#include <string>
#include <vector>


class SolutionGen final
{
public:
    static int Run( int argc, char* argv[] );

    // int SetSolutionPath( std::string const& solutionPath );

    // int SetProjectName( std::string const& projectName );
    // int SetProjectGuid( std::string const& projectGuid );

private:
    SolutionGen();
    ~SolutionGen() = default;

    int InternalRun( int argc, char* argv[] );
    
    enum Keys : unsigned char {
        ESCAPE           = 27,
        TAB              = 9,
        SPACE            = 32,
        BACKSPACE        = 8,
        CTRL_BACKSPACE   = 127,
        ENTER            = 13,

        SPECIAL          = 224,

        UP_ARROW         = 72,
        LEFT_ARROW       = 75,
        CTRL_LEFT_ARROW  = 115,
        DOWN_ARROW       = 80,
        RIGHT_ARROW      = 77,
        CTRL_RIGHT_ARROW = 116,

        INSERT           = 82,
        DEL              = 83,
        CTRL_DEL         = 147,
        HOME             = 71,
        END              = 79,
    };

    int SelectBetweenOptions( std::vector<std::string> const& options );

    std::vector<std::string> m_validSolutions {};

    // // Exe Path (Absolute)
    // std::string m_exePath;
    //
    // // Main Paths (Relative)
    // std::string m_solutionPath {};
    // std::string m_binPath {};
    // std::string m_configPath {};
    // std::string m_idePath {};
    // std::string m_libPath {};
    // std::string m_resPath {};
    // std::string m_srcPath {};
    //
    // // Project Paths (Relative)
    // std::string m_projectIdePath {};
    // std::string m_projectSrcPath {};
    //
    // // Identification
    // std::string m_solutionName {};
    // std::string m_solutionGuid {};
    // std::string m_projectName {};
    // std::string m_projectGuid {};

    static SolutionGen s_instance;
};


#endif