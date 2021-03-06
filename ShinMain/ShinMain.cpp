// ShinMain.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "ShinCompiler.h"
#include <iostream>
#include <string>

int main() {

	std::string sourceString1 = "";

	ShinCompiler * compiler = new ShinCompiler();
	//Add file to compiler
	compiler->addSourceFile(sourceString1);
	//Compile all sources
	compiler->compileAllSources();
	//Grab the assembled output of the compiler
	std::string assembly_compiled = compiler->getCompiledAssembly();
	delete compiler;

	//Output result
	std::cout << assembly_compiled << std::endl;

    return 0;
}

