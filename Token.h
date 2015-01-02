// Token.h
// Colossus compiler
// Token class for Colossus language


#pragma once

#include <string>
	using std::string;


enum TokenType
{
	END = 0, NEWLINE,
	IF, ELSE, SWITCH, CASE, DEFAULT,
	FOR, FOREACH, FOREVER, WHILE, DO, UNTIL, LOOP, BREAK,
	CLASS, INTERFACE, MIXIN,
	PUBLIC, PRIVATE, PROTECTED, VIRTUAL, SINGLETON, PROPERTY, PROXY, OPERATOR,
	CONST, STATIC, VOLATILE,
	TRY, CATCH, THROW,
	INLINE, ENCLAVE, GLOBAL, IMPORT,
	TRUEVAL, FALSEVAL, NULLVAL,
	IDENT, AUTOINIT,
	CHAR, STRING, INT, HEX, BIN, FLOAT,
	NONE
};

class Token
{
public:
	Token() : type(NONE), line(0), text("") {}
	Token(TokenType type, int line, const string& text = "")
	: type(type), line(line), text(text)
	{
	}

	TokenType type;
	int line;
	string text;
};
