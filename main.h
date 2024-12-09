#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED


int Help();

int Create( int argc, char* argv[] );

int Make( int argc, char* argv[] );

int AddProject( int argc, char* argv[] );

int AddDependency( int argc, char* argv[] );

int AddPort( int argc, char* argv[] );

int main( int argc, char* argv[] );


#endif