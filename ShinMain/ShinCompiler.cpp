#include "stdafx.h"
#include "ShinCompiler.h"
#include <string>
#include <vector>

//Initializes source_highlevel
ShinCompiler::ShinCompiler() {}

ShinCompiler::~ShinCompiler() {}

void ShinCompiler::addSourceFile(str sourceFile) {
	//Add string to source file and reallocate structure as necessary
	highlevel_sources.push_back(sourceFile);
}

void ShinCompiler::removeAllSources() {
	highlevel_sources.clear();
}

void ShinCompiler::compileAllSources() {

	//Create a new AssemblyConstruction for the solution
	AssemblyConstruction *assembly_file = new AssemblyConstruction();

	for (int i = 0; i < highlevel_sources.size(); i++) {
		//Compile the source file at highlevel_sources[i]
		AssemblyConstruction *assembly_item = 
			getCompileSource(i);
		
		//Merge the source file and the solution 
		assembly_file->data += assembly_item->data;
		assembly_file->bss += assembly_item->bss;
		assembly_file->text += assembly_item->text;

		delete assembly_item;
	}

	compiled_machine_assembly = "";
	delete assembly_file;
}

ShinCompiler::AssemblyConstruction*
ShinCompiler::getCompileSource(int index) {
	//Source file string
	str sourceFileString = highlevel_sources.at(index);

	//Assembly construction for this source file
	AssemblyConstruction *fileConstruction = new AssemblyConstruction();

	//Line terms are the terms for every line in each evaluation
	std::vector<str> lineTerms;
	lineTerms.push_back(""); //Fill first vector
	str currentWord = "";
	//Loop through every char in the file
	for (int i = 0; i < sourceFileString.length(); i++) {
		str c = str(1, sourceFileString.at(i));
		
		//Convert the line to assembly
		if (c == ";") {
			//Do conversion
			lineTerms.clear();
		} 
		//Add currentWord to a lineTerm if sep and the lineTerm has content
		else if (c == " " && 
					lineTerms.at(lineTerms.size()).length() > 0) {
			lineTerms.push_back(currentWord);
			lineTerms.push_back(""); //Create 
			currentWord = "";
		}
		//Add to the current word if not a special character
		else {
			currentWord += c;
		}
	}

	return fileConstruction;
}

str ShinCompiler::getCompiledAssembly() {
	return compiled_machine_assembly;
}