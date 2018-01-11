#pragma once
#include <vector>

//Define a more readable name for string
using str = std::string;

class ShinCompiler {
	// Structures
	struct AssemblyConstruction {
	public:
		str data;
		str bss;
		str text;
	};

	// Fields
private:
	std::vector<str> highlevel_sources;
	str compiled_machine_assembly;

	// Methods
public:
	ShinCompiler();

	virtual ~ShinCompiler();

	//Add a source string to the vector list
	void addSourceFile(str);

	//Remove all source files
	void removeAllSources();

	//Compile source code
	void compileAllSources();

	//Retrieve source once compiled
	str getCompiledAssembly();

	// Encapsulation or helper functions
private:
	 //Returns a pointer to an AssemblyConstruction with a compiled source
	 AssemblyConstruction* getCompileSource(int);	 
};