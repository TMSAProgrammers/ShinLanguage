#pragma once
class SyntaxDef {
	//Fields
public:
	wchar_t lineEnd = ';';
	wchar_t delimiter = ' ';
	wchar_t setter = '=';
	wchar_t getter = '*';
	wchar_t beginFunc = '(';
	wchar_t endFunc = ')';
	wchar_t argLimiter = ',';


	// Methods
public:
	SyntaxDef();
	~SyntaxDef();
};

