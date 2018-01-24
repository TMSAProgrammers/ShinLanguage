#pragma once
#include <vector>
#include "SyntaxDef.h"

//Define a more readable name for string
using str = std::string;
using expression_list_ptr = std::vector<ShinCompiler::Expression*>;

class ShinCompiler {
public:
	// Structures
	struct AssemblyConstruction {
	public:
		str data;
		str bss;
		str text;
	
		void addConstruction(AssemblyConstruction * otherConstruction) {
			this->data += otherConstruction->data;
			this->bss += otherConstruction->bss;
			this->text += otherConstruction->text;
		}
	};

	struct Expression {
	public:
		std::vector<str> content;
		int subjPos;
		int verbPos;
		int objPos;
	};

	// Fields
private:
	std::vector<str> highlevel_sources;
	str compiled_machine_assembly;
	
	//Language Definition
	SyntaxDef * langDef = new SyntaxDef();

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
	//Lexer
	expression_list_ptr lexerSource(str&);

	//Lexer helpers
	Expression * lineVecToExpr(std::vector<str>&);

	//Assembly
	AssemblyConstruction * assembleByteCode(expression_list_ptr);

	 //Returns a pointer to an AssemblyConstruction with a compiled source
	AssemblyConstruction * getCompileSource(int);
};