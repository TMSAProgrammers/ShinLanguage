#pragma once
class SyntaxDef {
	//Fields
public:
	//Identification characters
	wchar_t lineEnd = ';';
	wchar_t delimiter = ' ';
	wchar_t setter = '=';
	wchar_t getter = '&';
	wchar_t beginFunc = '(';
	wchar_t endFunc = ')';
	wchar_t argLimiter = ',';
	wchar_t singularOp = '$';
	wchar_t pluralOp = '#';

	//Declarators (_d)
	std::string variable_d = "var";
	std::string array_d = "array";
	//Data type modifiers (_t)
	std::string integer_t = "int";
	std::string float_t = "float";
	std::string dfloat_t = "double";
	std::string string_t = "string";
	std::string largeint_t = "long";

	// Methods
public:
	SyntaxDef();
	~SyntaxDef();
};

