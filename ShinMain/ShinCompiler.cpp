#include "stdafx.h"
#include "ShinCompiler.h"
#include <string>

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
		
		//Merge the compiled source and the solution 
		assembly_file->addConstruction(assembly_item);

		delete assembly_item;
	}

	//Turns assembly construction into a string
	compiled_machine_assembly =
		"section.data:\n" + assembly_file->data +
		"\nsection.bss:\n" + assembly_file->bss +
		"\nsection.text:\n" + assembly_file->text;
	delete assembly_file;
}

ShinCompiler::AssemblyConstruction*
ShinCompiler::getCompileSource(int index) {
	//Source file string
	str source_file_string = highlevel_sources.at(index);

	//Assembly construction for this source file
	AssemblyConstruction *file_construction;

	expression_list_ptr lex_vector = lexerSource(source_file_string);
	file_construction = assembleByteCode(lex_vector);

	//Free objects
	for (int i = 0; i < lex_vector.size(); i++) {
		delete lex_vector.at(i);
	}

	return file_construction;
}

//Lexer (source to vector of expressions)
const std::string lexerExprTrailException = "Lexer Exception: Expression Trailing, no Terminator";
expression_list_ptr ShinCompiler::lexerSource(str& source) {
	//Expressions are our main method of storing the lexerized code
	expression_list_ptr expressions;

	//These are temporary storages for a current word and expression
	str word = "";
	std::vector<str> wordExpr;

	//First pass of lexer
	for (int i = 0; i < source.length(); i++) {
		wchar_t c = source.at(i); //Allows for unicode chars

		//Automatic break and dump current word into the expression
		if (c == langDef->delimiter) {
			if (word != "") {
				wordExpr.push_back(word);
				word = "";
			}
		}
		//End the line, lexer the output 
		else if (c == langDef->lineEnd) {
			
			// TODO : Lexer line into an expression and shove into expressions here
			expressions.push_back(lineVecToExpr(wordExpr));

			wordExpr.clear();
		}
		//Dump value into word if it isn't a special character
		else {
			word += c;
		}
	}

	//End processes

	//Error checking for the current word expression
	if (wordExpr.empty()) {
		//Clean up
		freeVector(&wordExpr);
		//Throw unhandled excwprion
		throw lexerExprTrailException;
	}

	freeVector(&wordExpr);

	return expressions;
};

//Lexer helpers

//Convert a simple str vector to an Expression via identification of metadata
ShinCompiler::Expression *
ShinCompiler::lineVecToExpr(std::vector<str>& lineVec) {
	Expression * expr = new Expression();

	expr->content = lineVec;
	// TODO : Find line vector metadata (subj, verb, obj)

	return expr;
}

//Assembler
ShinCompiler::AssemblyConstruction *
ShinCompiler::assembleByteCode(expression_list_ptr) {
	AssemblyConstruction * assembled_code = new AssemblyConstruction();

	// TODO : Convert to assembly here

	return assembled_code;
}

str ShinCompiler::getCompiledAssembly() {
	return compiled_machine_assembly;
}

//Custom function to murderize vectors (and get rid of all of their mem alloc)
template <typename T> void freeVector(std::vector<T> * vec) {
	vec->clear();
	std::vector<T>().swap(vec);
}
