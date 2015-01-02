// ColossusScanner.cpp.rl
// Colossus compiler
// Ragel input for lexical scanner for Colossus language


#include <iostream>
	using std::cout;
	using std::cerr;
	using std::endl;
#include <algorithm>
#include <queue>
	using std::queue;

#include "ColossusParser.h"
#include "Token.h"


// return this when 
static Token nullTok;


%%{
	machine Colossus;

	# blocks delineated by { ... } define a C++ handler for this match
	# expr >{action}
	# 	Embeds {action} into starting transitions.
	# expr @{action}
	# 	Embeds {action} into transitions that go into a final state.
	# expr ${action}
	# 	Embeds {action} into all transitions. Does not include pending out
	# 	transitions.
	# expr %{action}
	# 	Embeds {action} into pending out transitions from final states.
	
	## definitions #############################################################

	# whitespace
	newline = ('\r\n' | '\r' | '\n') # DOS/Win | Old Mac | UNIX
	@{
		processTok(NEWLINE, "\\n");
		lineNum++;
	};
	anything = any | newline;
	whitespace = anything - graph;	# Treat all non-graphical chars as space.
									# Is this really what we want to do?

	# identifiers
	idHead = alpha | '_';
	idBody = idHead | digit;
	identifier = idHead idBody*;
	autoInitializer = '@' identifier;
	
	
	# text
	literalChar = [^\\] | newline | ( '\\' anything );
	charLiteral = '\'' . (literalChar - '\'')* . '\'';
	stringLiteral = '"' . (literalChar - '"')* . '"';
	
	# numbers
	intLiteral = '-'? digit+;
	hexLiteral = '0x' xdigit+;
	bit = [01];
	binLiteral = '0b' bit+;
	floatLiteral = '-'? digit+ '.' digit+ ([eE] '-'? digit+)?;

	## machinery ##############################################################
	
	# block comment mode
	blockCmnt := |*

		'/*' => { cmntDepth++; };
		'*/' => { if(!cmntDepth--) fgoto main; };
		'/';
		'*';
		(anything - [/*])*;

	*|;

	# scanner body
	main := |*

		# Whitespace
		whitespace; # do nothing

		# operators and other puctuation
		# TODO: explicit detect the ones we care about
		( punct - [_'"`@$] ) =>
		{
			printf( "symbol: %i: (%c)\n", lineNum, ts[0]);
		};

		# comments
		'//' [^\n]* newline;	# skip to end of line
		'/*' =>					# drop into "in-a-comment" mode
		{
			cmntDepth++;
			fgoto blockCmnt;
		};
		
		# reserved words - flow control
		'if' => { processTok(IF, "if"); };
		'else' => { processTok(ELSE, "else"); };
		'switch' => { processTok(SWITCH, "switch"); };
		'case' => { processTok(CASE, "case"); };
		'default' => { processTok(DEFAULT, "default"); };
		'for' => { processTok(FOR, "for"); };
		'foreach' => { processTok(FOREACH, "foreach"); };
		'forever' => { processTok(FOREVER, "forever"); };
		'while' => { processTok(WHILE, "while"); };
		'do' => { processTok(DO, "do"); };
		'until' => { processTok(UNTIL, "until"); };
		'loop' => { processTok(LOOP, "loop"); };
		'break' => { processTok(BREAK, "break"); };
		
		# reserved words - OO
		'class' => { processTok(CLASS, "class"); };
		'interface' => { processTok(INTERFACE, "interface"); };
		'mixin' => { processTok(MIXIN, "mixin"); };
		'public' => { processTok(PUBLIC, "public"); };
		'private' => { processTok(PRIVATE, "private"); };
		'protected' => { processTok(PROTECTED, "protected"); };
		'virtual' => { processTok(VIRTUAL, "virtual"); };
		'singleton' => { processTok(SINGLETON, "singleton"); };
		'property' => { processTok(PROPERTY, "property"); };
		'proxy' => { processTok(PROXY, "proxy"); };
		'operator' => { processTok(OPERATOR, "operator"); };
		
		# reserved words - spec modifiers
		'const' => { processTok(CONST, "const"); };
		'static' => { processTok(STATIC,  "static"); };
		'volatile' => { processTok(VOLATILE,  "volatile"); };
		
		# reserved words - exceptions
		'try' => { processTok(TRY,  "try"); };
		'catch' => { processTok(CATCH,  "catch"); };
		'throw' => { processTok(THROW,  "throw"); };
		
		# reserved words - coross-platform and modue features
		'inline' => { processTok(INLINE,  "inline"); };
		'enclave' => { processTok(ENCLAVE,  "enclave"); };
		'global' => { processTok(GLOBAL,  "global"); };
		'import' => { processTok(IMPORT,  "import"); };
		
		# reserved words - literal values
		'true' => { processTok(TRUEVAL,  "true"); };
		'false' => { processTok(FALSEVAL,  "false"); };
		'null' => { processTok(NULLVAL,  "null"); };

		# identifiers
		identifier => { processTok(IDENT); };
		autoInitializer => { processTok(AUTOINIT); };

		# inline text data
		charLiteral => { processTok(CHAR); };
		stringLiteral => { processTok(STRING); };

		# numeric literals
		intLiteral => { processTok(INT); };
		hexLiteral => { processTok(HEX); };
		binLiteral => { processTok(BIN); };
		floatLiteral => { processTok(FLOAT); };

	*|;
}%%


%% write data nofinal;

class Scanner
{
public:
	Scanner() : have(0), lineNum(1), ts(0), te(0), BUFSIZE(128), cmntDepth(-1)
	{
		%% write init;
		buf = new char[BUFSIZE];
	}
	virtual ~Scanner()
	{
		delete [] buf;
	}

	int scan()
	{
		bool done = false;
		while(!done)
		{
			char *p = buf + have, *pe, *eof = 0;
			int len, space = BUFSIZE - have;
			
			if(space == 0)
			{
				// We've used up the entire buffer storing an already-parsed
				// token prefix that must be preserved.
				fprintf(stderr, "OUT OF BUFFER SPACE\n" );
				return 1;
			}

			len = fread(p, 1, space, stdin);
			pe = p + len;

			/* Check if this is the end of file. */
			if(len < space)
			{
				eof = pe;
				done = true;
			}
				
			%% write exec;

			if(cs == Colossus_error)
			{
				printErr();
				return 1;
			}

			if(ts == 0)
				have = 0;
			else
			{
				/* There is a prefix to preserve, shift it over. */
				have = pe - ts;
				memmove( buf, ts, have );
				te = buf + (te-ts);
				ts = buf;
			}
		}
		return 0;
	}
	
	queue<Token*>& GetStream()
	{
		return tokStream;
	}
	
private:
	void processTok(TokenType type, string text = "")
	{
		if(text.length() == 0)
			text = currTok();
		Token* tok = new Token(type, lineNum, text);
		printTok(*tok);
		tokStream.push(tok);
	}
	inline string currTok()
	{
		string buf;
		buf.resize(te-ts);
		copy(ts, te, buf.begin());
		buf.push_back('\0');
		return buf;
	}
	void printTok(Token& t)
	{
		cout << t.line << ": (" << t.text << ")" << endl;
	}
	void printErr()
	{
		cerr << "error: " << lineNum << ": unknown symbol" << endl;
	}

	const int BUFSIZE;

	char* buf;
	int cs, act, have, lineNum;
	char *ts, *te;
	int cmntDepth;
	
	queue<Token*> tokStream;
};

/*
int main()
{
	Scanner s;
	int ret = s.scan();
	if(ret)
		return ret;
	queue<Token*>& tokStream = s.GetStream();
	Token* t;
	//Parser p;
	while(tokStream.size())
	{
		t = tokStream.front();
		tokStream.pop();
		// p.Parse(t);
	}
}*/
