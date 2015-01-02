/* Driver template for the LMNO parser generator.
 * The author disclaims copyright to this source code.
 */


#include <iostream>
 using std::ostream;
#include <string>
 using std::string;
#include <deque>
 using std::deque;

// user-included code
#line 12 "ColossusParser.lmn"


	#include <iostream>
		using std::cout;
		using std::cerr;
		using std::endl;

	#include "Token.h"
	void token_destructor(Token* t);


#line 27 "ColossusParser.cpp"


/* Next is all token values, in a form suitable for use by makeheaders.
 * This section will be null unless lmno is run with the -m switch.
 */
/* 
 * These constants (all generated automatically by the parser generator)
 * specify the various kinds of tokens (terminals) that the parser
 * understands. 
 *
 * Each symbol here is a terminal symbol in the grammar.
 */

// Make sure the INTERFACE macro is defined.
#ifndef INTERFACE
# define INTERFACE 1
#endif

/* The next thing included is series of defines which control
 * various aspects of the generated parser.
 *    YYCODETYPE         is the data type used for storing terminal
 *                       and nonterminal numbers.  "unsigned char" is
 *                       used if there are fewer than 250 terminals
 *                       and nonterminals.  "int" is used otherwise.
 *    YYNOCODE           is a number of type YYCODETYPE which corresponds
 *                       to no legal terminal or nonterminal number.  This
 *                       number is used to fill in empty slots of the hash 
 *                       table.
 *    YYFALLBACK         If defined, this indicates that one or more tokens
 *                       have fall-back values which should be used if the
 *                       original value of the token will not parse.
 *    YYACTIONTYPE       is the data type used for storing terminal
 *                       and nonterminal numbers.  "unsigned char" is
 *                       used if there are fewer than 250 rules and
 *                       states combined.  "int" is used otherwise.
 *    ColossusTOKENTYPE     is the data type used for minor tokens given 
 *                       directly to the parser from the tokenizer.
 *    YYMINORTYPE        is the data type used for all minor tokens.
 *                       This is typically a union of many types, one of
 *                       which is ColossusTOKENTYPE.  The entry in the union
 *                       for base tokens is called "yy0".
 *    YYSTACKDEPTH       is the maximum depth of the parser's stack.
 *    ColossusARG_SDECL     A static variable declaration for the %extra_argument
 *    ColossusARG_PDECL     A parameter declaration for the %extra_argument
 *    ColossusARG_STORE     Code to store %extra_argument into yypParser
 *    ColossusARG_FETCH     Code to extract %extra_argument from yypParser
 *    YYNSTATE           the combined number of states.
 *    YYNRULE            the number of rules in the grammar
 *    YYERRORSYMBOL      is the code number of the error symbol.  If not
 *                       defined, then do no error processing.
 */
#define YYCODETYPE unsigned char
#define YYNOCODE 84
#define YYACTIONTYPE unsigned short int
#define ColossusTOKENTYPE Token*
union YYMINORTYPE
{
	YYMINORTYPE() : __dummy(0) { }
	int __dummy;
	ColossusTOKENTYPE yy0;
	int yy167;
};
#define YYSTACKDEPTH 100
#define ColossusARG_SDECL
#define ColossusARG_PDECL
#define ColossusARG_FETCH
#define ColossusARG_STORE
#define YYNSTATE 205
#define YYNRULE 89
#define YYERRORSYMBOL 48
#define YYERRSYMDT yy167
#define YY_NO_ACTION      (YYNSTATE+YYNRULE+2)
#define YY_ACCEPT_ACTION  (YYNSTATE+YYNRULE+1)
#define YY_ERROR_ACTION   (YYNSTATE+YYNRULE)

/* Next are that tables used to determine what action to take based on the
 * current state and lookahead token.  These tables are used to implement
 * functions that take a state number and lookahead value and return an
 * action integer.  
 *
 * Suppose the action integer is N.  Then the action is determined as
 * follows
 *
 *   0 <= N < YYNSTATE                  Shift N.  That is, push the lookahead
 *                                      token onto the stack and goto state N.
 *
 *   YYNSTATE <= N < YYNSTATE+YYNRULE   Reduce by rule N-YYNSTATE.
 *
 *   N == YYNSTATE+YYNRULE              A syntax error has occurred.
 *
 *   N == YYNSTATE+YYNRULE+1            The parser accepts its input.
 *
 *   N == YYNSTATE+YYNRULE+2            No such action.  Denotes unused
 *                                      slots in the yy_action[] table.
 *
 * The action table is constructed as a single large table named yy_action[].
 * Given state S and lookahead X, the action is computed as
 *
 *      yy_action[ yy_shift_ofst[S] + X ]
 *
 * If the index value yy_shift_ofst[S]+X is out of range or if the value
 * yy_lookahead[yy_shift_ofst[S]+X] is not equal to X or if yy_shift_ofst[S]
 * is equal to YY_SHIFT_USE_DFLT, it means that the action is not in the table
 * and that yy_default[S] should be used instead.  
 *
 * The formula above is for computing the action when the lookahead is
 * a terminal symbol.  If the lookahead is a non-terminal (as occurs after
 * a reduce action) then the yy_reduce_ofst[] array is used in place of
 * the yy_shift_ofst[] array and YY_REDUCE_USE_DFLT is used in place of
 * YY_SHIFT_USE_DFLT.
 *
 * The following are the tables generated in this section:
 *
 *  yy_action[]        A single table containing all actions.
 *  yy_lookahead[]     A table containing the lookahead for each entry in
 *                     yy_action.  Used to detect hash collisions.
 *  yy_shift_ofst[]    For each state, the offset into yy_action for
 *                     shifting terminals.
 *  yy_reduce_ofst[]   For each state, the offset into yy_action for
 *                     shifting non-terminals after a reduce.
 *  yy_default[]       Default action for each state.
 */
static YYACTIONTYPE yy_action[] = {
 /*     0 */   205,  110,  118,  122,   31,   33,   52,   37,   49,   78,
 /*    10 */    43,   65,  249,   56,  139,   59,   47,  126,   68,   46,
 /*    20 */    74,   65,   77,  102,  140,  119,   90,   96,  108,   46,
 /*    30 */   133,  107,  144,  153,  160,  162,  167,  172,  182,  187,
 /*    40 */   197,  194,   54,   55,   61,   62,  105,  196,   65,  110,
 /*    50 */   118,  198,   40,    3,   52,   66,   46,  295,    1,    4,
 /*    60 */     5,   56,   70,   59,  174,  126,  178,  114,   74,   76,
 /*    70 */    77,  102,  232,   43,   90,   96,   83,   26,  133,   44,
 /*    80 */   144,  153,  160,  162,  167,  172,  182,  187,  111,  194,
 /*    90 */    54,   55,   61,   62,   40,  196,  233,  110,  118,   86,
 /*   100 */    64,  203,   52,   28,   72,   30,   32,   34,   36,   56,
 /*   110 */   103,   59,   45,  126,   38,   42,   74,   48,   77,  102,
 /*   120 */   141,   50,   90,   96,   53,   57,  133,   67,  144,  153,
 /*   130 */   160,  162,  167,  172,  182,  187,   64,  194,   54,   55,
 /*   140 */    61,   62,  186,  196,    6,    7,    8,    9,   10,   11,
 /*   150 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   160 */    22,   23,   24,   73,   60,  166,   69,    6,    7,    8,
 /*   170 */     9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
 /*   180 */    19,   20,   21,   22,   23,   24,   73,  161,   71,    6,
 /*   190 */     7,    8,    9,   10,   11,   12,   13,   14,   15,   16,
 /*   200 */    17,   18,   19,   20,   21,   22,   23,   24,   73,  159,
 /*   210 */    75,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*   220 */    15,   16,   17,   18,   19,   20,   21,   22,   23,   24,
 /*   230 */    73,  188,   79,    6,    7,    8,    9,   10,   11,   12,
 /*   240 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   250 */    23,   24,   73,  202,   80,    6,    7,    8,    9,   10,
 /*   260 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   270 */    21,   22,   23,   24,   73,  191,  238,    6,    7,    8,
 /*   280 */     9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
 /*   290 */    19,   20,   21,   22,   23,   24,   73,    2,   82,    6,
 /*   300 */     7,    8,    9,   10,   11,   12,   13,   14,   15,   16,
 /*   310 */    17,   18,   19,   20,   21,   22,   23,   24,   73,  193,
 /*   320 */    84,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*   330 */    15,   16,   17,   18,   19,   20,   21,   22,   23,   24,
 /*   340 */    73,  130,   85,    6,    7,    8,    9,   10,   11,   12,
 /*   350 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   360 */    23,   24,   73,  132,   87,    6,    7,    8,    9,   10,
 /*   370 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   380 */    21,   22,   23,   24,   73,  152,   88,    6,    7,    8,
 /*   390 */     9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
 /*   400 */    19,   20,   21,   22,   23,   24,   73,  173,   89,    6,
 /*   410 */     7,    8,    9,   10,   11,   12,   13,   14,   15,   16,
 /*   420 */    17,   18,   19,   20,   21,   22,   23,   24,   73,  171,
 /*   430 */    91,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*   440 */    15,   16,   17,   18,   19,   20,   21,   22,   23,   24,
 /*   450 */    73,   39,   92,   27,   29,   35,   31,   33,   81,   37,
 /*   460 */    49,   93,   43,   94,   95,   97,   98,  147,  100,   99,
 /*   470 */   106,   39,  199,   27,   29,   35,   31,   33,  101,   37,
 /*   480 */    49,  104,   43,  109,  112,  113,    4,    5,  115,  116,
 /*   490 */    39,  117,   27,   29,   35,   31,   33,  120,   37,   49,
 /*   500 */   121,   43,  123,  124,  125,   39,  149,   27,   29,   35,
 /*   510 */    31,   33,  127,   37,   49,   39,   43,   27,   29,   35,
 /*   520 */    31,   33,  128,   37,   49,   39,   43,   27,   29,   35,
 /*   530 */    31,   33,  134,   37,   49,  135,   43,  129,  137,  138,
 /*   540 */   142,  143,  145,  146,  148,  154,  150,   58,   51,  155,
 /*   550 */   163,   39,  157,   27,   29,   35,   31,   33,  168,   37,
 /*   560 */    49,   39,   43,   27,   29,   35,   31,   33,  164,   37,
 /*   570 */    49,  169,   43,  185,  175,  176,   39,  179,   27,   29,
 /*   580 */    35,   31,   33,  181,   37,   49,   39,   43,   27,   29,
 /*   590 */    35,   31,   33,  183,   37,   49,  180,   43,  177,  184,
 /*   600 */   189,   39,  190,   27,   29,   35,   31,   33,  170,   37,
 /*   610 */    49,   39,   43,   27,   29,   35,   31,   33,  192,   37,
 /*   620 */    49,  195,   43,  165,  200,  204,   39,  174,   27,   29,
 /*   630 */    35,   31,   33,  158,   37,   49,   39,   43,   27,   29,
 /*   640 */    35,   31,   33,  174,   37,   49,  174,   43,  174,  174,
 /*   650 */   174,   25,  174,  174,  174,  174,  174,  156,  174,  174,
 /*   660 */   174,   39,  174,   27,   29,   35,   31,   33,  174,   37,
 /*   670 */    49,   39,   43,   27,   29,   35,   31,   33,  174,   37,
 /*   680 */    49,  174,   43,  151,  174,  174,   39,   41,   27,   29,
 /*   690 */    35,   31,   33,  201,   37,   49,   39,   43,   27,   29,
 /*   700 */    35,   31,   33,   52,   37,   49,  174,   43,  174,  174,
 /*   710 */    56,  174,   59,  174,   52,    4,    5,  174,  136,  174,
 /*   720 */    63,   56,  174,   59,  174,  174,  174,  174,  174,  174,
 /*   730 */   174,   63,  174,  248,  174,  174,  174,  174,   52,   54,
 /*   740 */    55,   61,   62,  174,  174,   56,  174,   59,  174,  174,
 /*   750 */    54,   55,   61,   62,   39,   63,   27,   29,   35,   31,
 /*   760 */    33,  174,   37,   49,  174,   43,  174,  174,  174,  174,
 /*   770 */   174,  174,  174,  174,   54,   55,   61,   62,  174,  174,
 /*   780 */    27,   29,   35,   31,   33,  174,   37,   49,  174,   43,
};
static YYCODETYPE yy_lookahead[] = {
 /*     0 */     0,    1,    2,    1,    8,    9,    6,   11,   12,   23,
 /*    10 */    14,   71,   25,   13,   21,   15,   29,   17,   78,   79,
 /*    20 */    20,   71,   22,   23,   31,   23,   26,   27,   78,   79,
 /*    30 */    30,   13,   32,   33,   34,   35,   36,   37,   38,   39,
 /*    40 */    71,   41,   42,   43,   44,   45,   28,   47,   71,    1,
 /*    50 */     2,   82,   71,   52,    6,   78,   79,   49,   50,   18,
 /*    60 */    19,   13,   81,   15,   36,   17,   38,    2,   20,   21,
 /*    70 */    22,   23,   20,   14,   26,   27,   24,   71,   30,   23,
 /*    80 */    32,   33,   34,   35,   36,   37,   38,   39,   23,   41,
 /*    90 */    42,   43,   44,   45,   71,   47,   20,    1,    2,   23,
 /*   100 */    13,   52,    6,   71,   81,   71,   71,   71,   71,   13,
 /*   110 */    23,   15,   13,   17,   71,   71,   20,   71,   22,   23,
 /*   120 */    71,   71,   26,   27,   71,   71,   30,   25,   32,   33,
 /*   130 */    34,   35,   36,   37,   38,   39,   13,   41,   42,   43,
 /*   140 */    44,   45,   51,   47,   53,   54,   55,   56,   57,   58,
 /*   150 */    59,   60,   61,   62,   63,   64,   65,   66,   67,   68,
 /*   160 */    69,   70,   71,   72,   71,   51,   25,   53,   54,   55,
 /*   170 */    56,   57,   58,   59,   60,   61,   62,   63,   64,   65,
 /*   180 */    66,   67,   68,   69,   70,   71,   72,   51,    4,   53,
 /*   190 */    54,   55,   56,   57,   58,   59,   60,   61,   62,   63,
 /*   200 */    64,   65,   66,   67,   68,   69,   70,   71,   72,   51,
 /*   210 */    50,   53,   54,   55,   56,   57,   58,   59,   60,   61,
 /*   220 */    62,   63,   64,   65,   66,   67,   68,   69,   70,   71,
 /*   230 */    72,   51,   73,   53,   54,   55,   56,   57,   58,   59,
 /*   240 */    60,   61,   62,   63,   64,   65,   66,   67,   68,   69,
 /*   250 */    70,   71,   72,   51,   20,   53,   54,   55,   56,   57,
 /*   260 */    58,   59,   60,   61,   62,   63,   64,   65,   66,   67,
 /*   270 */    68,   69,   70,   71,   72,   51,   21,   53,   54,   55,
 /*   280 */    56,   57,   58,   59,   60,   61,   62,   63,   64,   65,
 /*   290 */    66,   67,   68,   69,   70,   71,   72,   51,   21,   53,
 /*   300 */    54,   55,   56,   57,   58,   59,   60,   61,   62,   63,
 /*   310 */    64,   65,   66,   67,   68,   69,   70,   71,   72,   51,
 /*   320 */    75,   53,   54,   55,   56,   57,   58,   59,   60,   61,
 /*   330 */    62,   63,   64,   65,   66,   67,   68,   69,   70,   71,
 /*   340 */    72,   51,   76,   53,   54,   55,   56,   57,   58,   59,
 /*   350 */    60,   61,   62,   63,   64,   65,   66,   67,   68,   69,
 /*   360 */    70,   71,   72,   51,   13,   53,   54,   55,   56,   57,
 /*   370 */    58,   59,   60,   61,   62,   63,   64,   65,   66,   67,
 /*   380 */    68,   69,   70,   71,   72,   51,   23,   53,   54,   55,
 /*   390 */    56,   57,   58,   59,   60,   61,   62,   63,   64,   65,
 /*   400 */    66,   67,   68,   69,   70,   71,   72,   51,   25,   53,
 /*   410 */    54,   55,   56,   57,   58,   59,   60,   61,   62,   63,
 /*   420 */    64,   65,   66,   67,   68,   69,   70,   71,   72,   51,
 /*   430 */    23,   53,   54,   55,   56,   57,   58,   59,   60,   61,
 /*   440 */    62,   63,   64,   65,   66,   67,   68,   69,   70,   71,
 /*   450 */    72,    3,   73,    5,    6,    7,    8,    9,   74,   11,
 /*   460 */    12,   20,   14,   74,   21,   23,   73,   19,   74,   20,
 /*   470 */    71,    3,   24,    5,    6,    7,    8,    9,   21,   11,
 /*   480 */    12,   77,   14,   25,   23,   77,   18,   19,   23,   23,
 /*   490 */     3,   77,    5,    6,    7,    8,    9,   23,   11,   12,
 /*   500 */    77,   14,   23,   23,   77,    3,   19,    5,    6,    7,
 /*   510 */     8,    9,   13,   11,   12,    3,   14,    5,    6,    7,
 /*   520 */     8,    9,   71,   11,   12,    3,   14,    5,    6,    7,
 /*   530 */     8,    9,   13,   11,   12,   71,   14,   25,   20,   80,
 /*   540 */    52,   50,   13,   71,   71,   13,   71,   25,   46,   71,
 /*   550 */    13,    3,   71,    5,    6,    7,    8,    9,   13,   11,
 /*   560 */    12,    3,   14,    5,    6,    7,    8,    9,   71,   11,
 /*   570 */    12,   71,   14,   25,   13,   71,    3,   13,    5,    6,
 /*   580 */     7,    8,    9,   25,   11,   12,    3,   14,    5,    6,
 /*   590 */     7,    8,    9,   13,   11,   12,   71,   14,   25,   71,
 /*   600 */    40,    3,   13,    5,    6,    7,    8,    9,   25,   11,
 /*   610 */    12,    3,   14,    5,    6,    7,    8,    9,   25,   11,
 /*   620 */    12,   71,   14,   25,   71,   50,    3,   83,    5,    6,
 /*   630 */     7,    8,    9,   25,   11,   12,    3,   14,    5,    6,
 /*   640 */     7,    8,    9,   83,   11,   12,   83,   14,   83,   83,
 /*   650 */    83,   28,   83,   83,   83,   83,   83,   24,   83,   83,
 /*   660 */    83,    3,   83,    5,    6,    7,    8,    9,   83,   11,
 /*   670 */    12,    3,   14,    5,    6,    7,    8,    9,   83,   11,
 /*   680 */    12,   83,   14,   25,   83,   83,    3,    4,    5,    6,
 /*   690 */     7,    8,    9,   25,   11,   12,    3,   14,    5,    6,
 /*   700 */     7,    8,    9,    6,   11,   12,   83,   14,   83,   83,
 /*   710 */    13,   83,   15,   83,    6,   18,   19,   83,   25,   83,
 /*   720 */    23,   13,   83,   15,   83,   83,   83,   83,   83,   83,
 /*   730 */    83,   23,   83,   25,   83,   83,   83,   83,    6,   42,
 /*   740 */    43,   44,   45,   83,   83,   13,   83,   15,   83,   83,
 /*   750 */    42,   43,   44,   45,    3,   23,    5,    6,    7,    8,
 /*   760 */     9,   83,   11,   12,   83,   14,   83,   83,   83,   83,
 /*   770 */    83,   83,   83,   83,   42,   43,   44,   45,   83,   83,
 /*   780 */     5,    6,    7,    8,    9,   83,   11,   12,   83,   14,
};
#define YY_SHIFT_USE_DFLT (-15)
static short yy_shift_ofst[] = {
 /*     0 */   -15,    0,   41,  -15,  -15,  -15,  -15,  -15,  -15,  -15,
 /*    10 */   -15,  -15,  -15,  -15,  -15,  -15,  -15,  -15,  -15,  -15,
 /*    20 */   -15,  -15,  -15,  -15,  623,  732,  751,  732,   -4,  732,
 /*    30 */    -4,  732,   59,  732,   59,  732,   -4,  732,   59,  732,
 /*    40 */   683,  732,  775,   56,   99,  708,  -13,  732,  751,  732,
 /*    50 */   502,  -15,  732,   -4,  -15,  -15,  732,  522,  -15,  732,
 /*    60 */   -15,  -15,  -15,  123,  708,  751,  102,  -15,  141,  -15,
 /*    70 */   184,  732,  -15,  -15,  -15,   48,  -15,  -14,   52,  234,
 /*    80 */   255,  277,  -15,  -15,   76,  -15,  351,  363,  383,  -15,
 /*    90 */   407,   52,  441,  255,  443,  -15,  442,   52,  449,  255,
 /*   100 */   457,  -15,   87,   18,  -15,  732,  751,  708,  458,  -15,
 /*   110 */    65,  461,   18,  -15,  465,  466,   18,  -15,    2,  474,
 /*   120 */    18,  -15,  479,  480,   18,  -15,  499,  732,  512,   96,
 /*   130 */   -15,   96,  -15,  519,  732,  693,  518,  -15,   -7,  -15,
 /*   140 */   697,  468,  -15,   96,  529,  732,  448,  732,  487,  732,
 /*   150 */   658,   96,  -15,  532,  732,  633,  732,  608,   96,  -15,
 /*   160 */    96,  -15,  537,  732,  598,   96,  -15,  545,  732,  583,
 /*   170 */    96,  -15,   96,   28,  561,  732,  573,  -15,  564,  732,
 /*   180 */   558,  -15,  580,  732,  548,   96,  -15,   96,  560,  589,
 /*   190 */    96,  593,   96,  -15,  732,  751,  732,  751,  -15,  732,
 /*   200 */   668,   96,  -15,  -15,   96,
};
#define YY_REDUCE_USE_DFLT (-61)
static short yy_reduce_ofst[] = {
 /*     0 */     8,  246,    1,  -61,  -61,  -61,  -61,  -61,  -61,  -61,
 /*    10 */   -61,  -61,  -61,  -61,  -61,  -61,  -61,  -61,  -61,  -61,
 /*    20 */   -61,  -61,  -61,  -61,  -61,    6,  -61,   32,  -61,   34,
 /*    30 */   -61,   35,  -61,   36,  -61,   37,  -61,   43,  -61,  -19,
 /*    40 */   -61,   44,  -61,  -61,  -61,  -60,  -61,   46,  -61,   50,
 /*    50 */   -61,  -61,   53,  -61,  -61,  -61,   54,  -61,  -61,   93,
 /*    60 */   -61,  -61,  -61,  -61,  -23,  -61,  -61,  -61,  -61,  -61,
 /*    70 */   -61,   23,  -61,  -61,  160,  246,  -61,  -61,  159,  -61,
 /*    80 */   384,  -61,  -61,  245,  266,  -61,  -61,  -61,  -61,  -61,
 /*    90 */   -61,  379,  -61,  389,  -61,  -61,  -61,  393,  -61,  394,
 /*   100 */   -61,  -61,  -61,  404,  -61,  399,  -61,  -50,  -61,  -61,
 /*   110 */   -61,  -61,  408,  -61,  -61,  -61,  414,  -61,  -61,  -61,
 /*   120 */   423,  -61,  -61,  -61,  427,  -61,  -61,  451,  -61,  290,
 /*   130 */   -61,  312,  -61,  -61,  464,  -61,  -61,  459,  -61,  -61,
 /*   140 */    49,  488,  491,  246,  -61,  472,  -61,  473,  -61,  475,
 /*   150 */   -61,  334,  -61,  -61,  478,  -61,  481,  -61,  158,  -61,
 /*   160 */   136,  -61,  -61,  497,  -61,  114,  -61,  -61,  500,  -61,
 /*   170 */   378,  -61,  356,  -61,  -61,  504,  -61,  -61,  -61,  525,
 /*   180 */   -61,  -61,  -61,  528,  -61,   91,  -61,  180,  -61,  -61,
 /*   190 */   224,  -61,  268,  -61,  550,  -61,  -31,  -61,  -61,  553,
 /*   200 */   -61,  202,  -61,  575,  246,
};
static YYACTIONTYPE yy_default[] = {
 /*     0 */   206,  294,  294,  207,  208,  209,  210,  211,  212,  213,
 /*    10 */   214,  215,  216,  217,  218,  219,  220,  221,  222,  223,
 /*    20 */   224,  225,  226,  227,  228,  294,  252,  294,  270,  294,
 /*    30 */   271,  294,  272,  294,  273,  294,  278,  294,  279,  294,
 /*    40 */   294,  294,  282,  294,  288,  294,  294,  294,  251,  294,
 /*    50 */   294,  290,  294,  274,  275,  276,  294,  294,  277,  294,
 /*    60 */   280,  284,  285,  287,  294,  250,  294,  286,  294,  289,
 /*    70 */   281,  294,  283,  229,  206,  294,  230,  294,  294,  294,
 /*    80 */   294,  294,  231,  234,  294,  235,  236,  294,  294,  237,
 /*    90 */   294,  294,  294,  294,  294,  239,  294,  294,  294,  294,
 /*   100 */   294,  240,  287,  294,  241,  294,  246,  294,  294,  247,
 /*   110 */   294,  294,  294,  242,  294,  294,  294,  245,  294,  294,
 /*   120 */   294,  243,  294,  294,  294,  244,  294,  294,  294,  294,
 /*   130 */   253,  294,  254,  294,  294,  294,  294,  256,  294,  255,
 /*   140 */   294,  294,  206,  257,  294,  294,  294,  294,  294,  294,
 /*   150 */   294,  294,  259,  294,  294,  294,  294,  294,  294,  261,
 /*   160 */   294,  262,  294,  294,  294,  294,  263,  294,  294,  294,
 /*   170 */   294,  264,  294,  294,  294,  294,  294,  265,  294,  294,
 /*   180 */   294,  267,  294,  294,  294,  294,  266,  294,  294,  294,
 /*   190 */   294,  294,  294,  268,  294,  269,  292,  293,  291,  294,
 /*   200 */   294,  294,  260,  206,  258,
};
#define YY_SZ_ACTTAB (sizeof(yy_action)/sizeof(yy_action[0]))

/* The next table maps tokens into fallback tokens.  If a construct
 * like the following:
 * 
 *      %fallback ID X Y Z.
 *
 * appears in the grammer, then ID becomes a fallback token for X, Y,
 * and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
 * but it does not parse, the type of the token is changed to ID and
 * the parse is retried before an error is thrown.
 */
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
};
#endif /* YYFALLBACK */

// Stack Entry /////////////////////////////////////////////////////////////////

/*
 * Information stored includes:
 *
 *  +  The state number for the parser at this level of the stack.
 *
 *   +  The value of the token stored at this level of the stack.
 *      (In other words, the "major" token.)
 *
 *   +  The semantic value stored at this level of the stack.  This is
 *      the information used by the action routines in the grammar.
 *      It is sometimes called the "minor" token.
 */
struct yyStackEntry
{
	yyStackEntry() : stateno(0), major(0) { }
	yyStackEntry(int state, int major, YYMINORTYPE minor)
	: stateno(state), major(major), minor(minor)
	{
	}

	int stateno;       /* The state-number */
	int major;         /* The major token value.  This is the code
						** number for the token at this stack level */
	YYMINORTYPE minor; /* The user-supplied minor token value.  This
						** is the value of the token  */
};

// Shift-Reduce Stack //////////////////////////////////////////////////////////

class yyStack
{
public:
	virtual void push(const yyStackEntry& item);
	virtual yyStackEntry pop();
	virtual void lop();
	virtual void lop(size_t count);
	virtual yyStackEntry& top();
	virtual void pick(size_t n);
	virtual yyStackEntry& peek(size_t n);
	virtual void dup();
	virtual void over();
	virtual void toss(size_t n);
	virtual const yyStackEntry& yank(size_t n);
	virtual void roll(size_t n);
	virtual void swap();
	virtual void rot();
	
	virtual void clear();
	virtual size_t size();
	virtual bool empty();
	
	virtual yyStackEntry& operator[](size_t);
private:
	yyStackEntry popped_val;
	deque<yyStackEntry> c;
};

void yyStack::push(const yyStackEntry& item)
{
	c.push_back(item);
}

// pop head off (and return)
yyStackEntry yyStack::pop()
{
	popped_val = c.back();
	c.pop_back();
	return popped_val;
}

// lop head off (and discard)
void yyStack::lop()
{
	c.pop_back();
}

// lop head off (and discard)
void yyStack::lop(size_t count)
{
	while (count--)
	{
		c.pop_back();
	}
}

// return a reference to TOS
yyStackEntry& yyStack::top()
{
	return c.back();
}

// push a copy of the nth item from the top
void yyStack::pick(size_t n)
{
	c.push_back(this->c[c.size() - 1 - n]);
}

// push a duplicate of TOS
void yyStack::dup()
{
	c.push_back(c.back());
}

// push a dup of item under TOS
void yyStack::over()
{
	pick(1);
}

// return a reference to the nth item from TOS
yyStackEntry& yyStack::peek(size_t n)
{
	return this->c[c.size() - 1 - n];
}

// grab (and discard) nth item from TOS
void yyStack::toss(size_t n)
{
	yank(n);
}

// grab (and return) nth item from TOS
const yyStackEntry& yyStack::yank(size_t n)
{
	int top = c.size() - 1;
	n = top - n;
	popped_val = this->c[n];
	c.erase(c.begin()+n);
	return popped_val;
}

// grab (and push) nth item form TOS
void yyStack::roll(size_t n)
{
	c.push_back(yank(n));
}

// swap top two items
void yyStack::swap()
{
	//equivalent to roll(1);
	int n = c.size() - 1, m = n-1;
	yyStackEntry tmp = this->c[n];
	this->c[n] = this->c[m];
	this->c[m] = tmp;
}

// grab (and push) 2nd item from TOS
void yyStack::rot()
{
	roll(2);
}

// access arbitrary item in stack
yyStackEntry& yyStack::operator[](size_t i)
{
	return this->c[i];
}

// empty the stack
void yyStack::clear()
{
	c.clear();
}

// return stack height
size_t yyStack::size()
{
	return c.size();
}

// is stack empty?
bool yyStack::empty()
{
	return c.empty();
}

// Main Colossusr Class ///////////////////////////////////////////////////////////

/* The state of the parser is completely contained in an instance of
 * the following structure */
class yyParser
{
public:
	yyParser() : errCount(0) { stack.push(yyStackEntry()); }
	
	void Colossus(int yymajor, ColossusTOKENTYPE yyminor ColossusARG_PDECL);
	
	void ColossusTrace(ostream *traceStream, const string& tracePrompt);
	void ColossusTrace();
	const string ColossusTokenName(int tokenType);
	
protected:
	void destructor(YYCODETYPE yymajor, YYMINORTYPE *yypminor);

	int find_shift_action(int iLookAhead);
	int find_reduce_action(int iLookAhead);
	void shift(int yyNewState, int yyMajor, YYMINORTYPE *yypMinor);
	void reduce(int yyruleno);
	void accept();
	
	void parse_failed();
	void syntax_error(int yymajor, YYMINORTYPE yyminor);

	int errCount;						// Shifts left before out of the error
	ColossusARG_SDECL						// A place to hold %extra_argument
	yyStack stack;		// The parser's shift/reduce stack
	
	#ifndef NDEBUG
	static std::ostream* yyTraceStream;
	static string yyTracePrompt;
	static const string yyTokenName[];
	static const string yyRuleName[];
	#endif // NDEBUG
};

// Debug Tracing Data //
#ifndef NDEBUG
std::ostream* yyParser::yyTraceStream = NULL;
string yyParser::yyTracePrompt = "";

// the names of all terminals and nonterminals, for tracing shifts
const string yyParser::yyTokenName[] = { 
  "$",             "STATIC",        "CONST",         "IS",          
  "KEYWORDOR",     "PLUS",          "MINUS",         "OR",          
  "STAR",          "SLASH",         "PERCENT",       "AND",         
  "LBRACKET",      "LPAREN",        "DOT",           "NOT",         
  "ELSE",          "IF",            "NEWLINE",       "SEMICOLON",   
  "LBRACE",        "RBRACE",        "CLASS",         "IDENT",       
  "COLON",         "RPAREN",        "INTERFACE",     "MIXIN",       
  "EQUALS",        "COMMA",         "SWITCH",        "CASE",        
  "FOR",           "FOREACH",       "FOREVER",       "LOOP",        
  "WHILE",         "DO",            "UNTIL",         "TRY",         
  "CATCH",         "THROW",         "INT",           "FLOAT",       
  "TRUE",          "FALSE",         "RBRACKET",      "RETURN",      
  "error",         "main",          "statements",    "stmnt",       
  "terminator",    "block",         "classdef",      "interfacedef",
  "mixindef",      "declaration",   "assignstmnt",   "ifstmnt",     
  "switchstmnt",   "forstmnt",      "foreachstmnt",  "foreverstmnt",
  "loopstmnt",     "whilestmnt",    "dowhilestmnt",  "untilstmnt",  
  "dountilstmnt",  "trycatch",      "throwstmnt",    "expr",        
  "return",        "inheritence",   "classbody",     "ancestry",    
  "ancestor",      "initializer",   "args",          "arglist",     
  "cases",         "alternatives",  "retval",      
};
// the names of all rules, for tracing reduce actions
const string yyParser::yyRuleName[] = {
 /*   0 */ "main -> statements",
 /*   1 */ "statements ->",
 /*   2 */ "statements -> statements stmnt terminator",
 /*   3 */ "terminator -> NEWLINE",
 /*   4 */ "terminator -> SEMICOLON",
 /*   5 */ "stmnt -> block",
 /*   6 */ "stmnt -> classdef",
 /*   7 */ "stmnt -> interfacedef",
 /*   8 */ "stmnt -> mixindef",
 /*   9 */ "stmnt -> declaration",
 /*  10 */ "stmnt -> assignstmnt",
 /*  11 */ "stmnt -> ifstmnt",
 /*  12 */ "stmnt -> switchstmnt",
 /*  13 */ "stmnt -> forstmnt",
 /*  14 */ "stmnt -> foreachstmnt",
 /*  15 */ "stmnt -> foreverstmnt",
 /*  16 */ "stmnt -> loopstmnt",
 /*  17 */ "stmnt -> whilestmnt",
 /*  18 */ "stmnt -> dowhilestmnt",
 /*  19 */ "stmnt -> untilstmnt",
 /*  20 */ "stmnt -> dountilstmnt",
 /*  21 */ "stmnt -> trycatch",
 /*  22 */ "stmnt -> throwstmnt",
 /*  23 */ "stmnt -> expr",
 /*  24 */ "stmnt -> return",
 /*  25 */ "block -> LBRACE statements RBRACE",
 /*  26 */ "classdef -> CLASS IDENT inheritence LBRACE classbody RBRACE",
 /*  27 */ "inheritence ->",
 /*  28 */ "inheritence -> COLON ancestry",
 /*  29 */ "ancestry ->",
 /*  30 */ "ancestry -> ancestry ancestor",
 /*  31 */ "ancestor -> IDENT",
 /*  32 */ "ancestor -> IDENT LPAREN IDENT RPAREN",
 /*  33 */ "classbody ->",
 /*  34 */ "interfacedef -> INTERFACE IDENT inheritence LBRACE classbody RBRACE",
 /*  35 */ "mixindef -> MIXIN IDENT inheritence LBRACE classbody RBRACE",
 /*  36 */ "declaration -> IDENT IDENT initializer",
 /*  37 */ "declaration -> STATIC IDENT IDENT initializer",
 /*  38 */ "declaration -> CONST IDENT IDENT initializer",
 /*  39 */ "declaration -> CONST STATIC IDENT IDENT initializer",
 /*  40 */ "declaration -> STATIC CONST IDENT IDENT initializer",
 /*  41 */ "initializer -> EQUALS expr",
 /*  42 */ "initializer -> LPAREN args RPAREN",
 /*  43 */ "args ->",
 /*  44 */ "args -> arglist",
 /*  45 */ "arglist -> expr",
 /*  46 */ "arglist -> arglist COMMA expr",
 /*  47 */ "assignstmnt -> expr EQUALS expr",
 /*  48 */ "ifstmnt -> IF LPAREN expr RPAREN stmnt",
 /*  49 */ "ifstmnt -> IF LPAREN expr RPAREN stmnt ELSE stmnt",
 /*  50 */ "switchstmnt -> SWITCH LPAREN expr RPAREN LBRACE cases RBRACE",
 /*  51 */ "cases ->",
 /*  52 */ "cases -> cases CASE expr terminator statements",
 /*  53 */ "cases -> cases CASE terminator statements",
 /*  54 */ "forstmnt -> FOR LPAREN expr SEMICOLON expr SEMICOLON expr RPAREN stmnt",
 /*  55 */ "forstmnt -> FOR LPAREN expr COLON expr RPAREN stmnt",
 /*  56 */ "foreachstmnt -> FOREACH LPAREN expr COLON expr RPAREN stmnt",
 /*  57 */ "foreverstmnt -> FOREVER stmnt",
 /*  58 */ "loopstmnt -> LOOP LPAREN expr RPAREN stmnt",
 /*  59 */ "whilestmnt -> WHILE LPAREN expr RPAREN stmnt",
 /*  60 */ "dowhilestmnt -> DO stmnt WHILE LPAREN expr RPAREN",
 /*  61 */ "untilstmnt -> UNTIL LPAREN expr RPAREN stmnt",
 /*  62 */ "dountilstmnt -> DO stmnt UNTIL LPAREN expr RPAREN",
 /*  63 */ "trycatch -> TRY stmnt CATCH LPAREN stmnt RPAREN stmnt",
 /*  64 */ "throwstmnt -> THROW expr",
 /*  65 */ "expr -> expr PLUS expr",
 /*  66 */ "expr -> expr MINUS expr",
 /*  67 */ "expr -> expr STAR expr",
 /*  68 */ "expr -> expr SLASH expr",
 /*  69 */ "expr -> MINUS expr",
 /*  70 */ "expr -> INT",
 /*  71 */ "expr -> FLOAT",
 /*  72 */ "expr -> LPAREN expr RPAREN",
 /*  73 */ "expr -> expr OR expr",
 /*  74 */ "expr -> expr AND expr",
 /*  75 */ "expr -> NOT expr",
 /*  76 */ "expr -> expr IS alternatives",
 /*  77 */ "alternatives -> expr KEYWORDOR expr",
 /*  78 */ "alternatives -> alternatives KEYWORDOR alternatives",
 /*  79 */ "expr -> TRUE",
 /*  80 */ "expr -> FALSE",
 /*  81 */ "expr -> IDENT LPAREN args RPAREN",
 /*  82 */ "expr -> IDENT",
 /*  83 */ "expr -> expr DOT IDENT",
 /*  84 */ "expr -> expr DOT IDENT LPAREN args RPAREN",
 /*  85 */ "expr -> expr LBRACKET expr RBRACKET",
 /*  86 */ "return -> RETURN retval",
 /*  87 */ "retval ->",
 /*  88 */ "retval -> expr",
};
#endif /* NDEBUG */

/* 
 * Turn parser tracing on by giving a stream to which to write the trace
 * and a prompt to preface each trace message.  Tracing is turned off
 * by making either argument NULL 
 *
 * Inputs:
 * <ul>
 * <li> A FILE* to which trace output should be written.
 *      If NULL, then tracing is turned off.
 * <li> A prefix string written at the beginning of every
 *      line of trace output.  If NULL, then tracing is
 *      turned off.
 * </ul>
 *
 * Outputs:
 * None.
 */
void yyParser::ColossusTrace(ostream *traceStream, const string& tracePrompt)
{
#ifndef NDEBUG
	yyTraceStream = traceStream;
	yyTracePrompt = tracePrompt;
	if(yyTraceStream == NULL)
		yyTracePrompt.clear();
	else if(yyTracePrompt == "")
		yyTraceStream = NULL;
#endif
}

// shortcut overload to disable tracing
void yyParser::ColossusTrace()
{
#ifndef NDEBUG
	yyTraceStream = NULL;
	yyTracePrompt = "";
#endif
}

// This function returns the symbolic name associated with a token value.
const string yyParser::ColossusTokenName(int tokenType)
{
#ifndef NDEBUG
	if(tokenType>0 && tokenType<(sizeof(yyTokenName)/sizeof(yyTokenName[0])))
	{
		return yyTokenName[tokenType];
	}
	else
	{
		return "Unknown";
	}
#else
	return "";
#endif
}

/*
 * The following function deletes the value associated with a
 * symbol.  The symbol can be either a terminal or nonterminal.
 * "yymajor" is the symbol code, and "yypminor" is a pointer to
 * the value.
 */
void yyParser::destructor(YYCODETYPE yymajor, YYMINORTYPE *yypminor)
{
	switch(yymajor)
	{
			/* Here is inserted the actions which take place when a
			 * terminal or non-terminal is destroyed.  This can happen
			 * when the symbol is popped from the stack during a
			 * reduce or during error processing or when a parser is 
			 * being destroyed before it is finished parsing.
			 *
			 * Note: during a reduce, the only symbols destroyed are those
			 * which appear on the RHS of the rule, but which are not used
			 * inside the C code.
			 */
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 21:
	case 22:
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
	case 28:
	case 29:
	case 30:
	case 31:
	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
	case 37:
	case 38:
	case 39:
	case 40:
	case 41:
	case 42:
	case 43:
	case 44:
	case 45:
	case 46:
	case 47:
#line 38 "ColossusParser.lmn"
{ token_destructor((yypminor->yy0)); }
#line 865 "ColossusParser.cpp"
	  break;
		default:
			break;   /* If no destructor action specified: do nothing */
	}
}

/*
 * Find the appropriate action for a parser given the terminal
 * look-ahead token iLookAhead.
 *
 * If the look-ahead token is YYNOCODE, then check to see if the action is
 * independent of the look-ahead.  If it is, return the action, otherwise
 * return YY_NO_ACTION.
 */
int yyParser::find_shift_action(int iLookAhead)
{
	int i;
	//int stateno = pParser->stack[pParser->index].stateno;
	int stateno = stack.top().stateno;

	i = yy_shift_ofst[stateno];
	if(i==YY_SHIFT_USE_DFLT)
	{
		return yy_default[stateno];
	}
	if(iLookAhead==YYNOCODE)
	{
		return YY_NO_ACTION;
	}
	i += iLookAhead;
	if(i<0 || i>=YY_SZ_ACTTAB || yy_lookahead[i]!=iLookAhead)
	{
#ifdef YYFALLBACK
		int iFallback;            /* Fallback token */
		if(iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
		   && (iFallback = yyFallback[iLookAhead])!=0)
		{
#ifndef NDEBUG
			if(yyTraceStream)
			{
				*yyTraceStream << yyTracePrompt << "FALLBACK "
				<< yyTokenName[iLookAhead] << "=> "
				<< yyTokenName[iFallback] << std::endl;
			}
#endif
			return find_shift_action(iFallback);
		}
#endif
		return yy_default[stateno];
	}
	else
	{
		return yy_action[i];
	}
}

/*
 * Find the appropriate action for a parser given the non-terminal
 * look-ahead token iLookAhead.
 *
 * If the look-ahead token is YYNOCODE, then check to see if the action is
 * independent of the look-ahead.  If it is, return the action, otherwise
 * return YY_NO_ACTION.
 */
int yyParser::find_reduce_action(int iLookAhead)
{
	int i;
	int stateno = stack.top().stateno;
	
	i = yy_reduce_ofst[stateno];
	if(i==YY_REDUCE_USE_DFLT)
	{
		return yy_default[stateno];
	}
	if(iLookAhead==YYNOCODE)
	{
		return YY_NO_ACTION;
	}
	i += iLookAhead;
	if(i<0 || i>=YY_SZ_ACTTAB || yy_lookahead[i]!=iLookAhead)
	{
		return yy_default[stateno];
	}
	else
	{
		return yy_action[i];
	}
}

/*
 * Perform a shift action.
 */
void yyParser::shift(int yyNewState, int yyMajor, YYMINORTYPE *yypMinor)
{	
// TODO: remove this insertion point from lmno.c
// stack will never overflow
#if 0
#endif
	stack.push(yyStackEntry(yyNewState, yyMajor, *yypMinor));
	/*yyStackEntry& yytos = stack.top();
	yytos->stateno = yyNewState;
	yytos->major = yyMajor;
	yytos->minor = *yypMinor;*/
#ifndef NDEBUG
	if(yyTraceStream && stack.size())
	{
		int i;
		*yyTraceStream << yyTracePrompt << "Shift " << yyNewState << '\n'
		<< yyTracePrompt << "Stack: ";
		for(i=0; i < stack.size(); i++)
			*yyTraceStream << yyTokenName[stack[i].major];
		*yyTraceStream << std::endl;
	}
#endif
}

/* The following table contains information about every rule that
 * is used during the reduce.
 */
static struct {
	YYCODETYPE lhs;         /* Symbol on the left-hand side of the rule */
	unsigned char nrhs;     /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
  { 49, 1 },
  { 50, 0 },
  { 50, 3 },
  { 52, 1 },
  { 52, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 1 },
  { 53, 3 },
  { 54, 6 },
  { 73, 0 },
  { 73, 2 },
  { 75, 0 },
  { 75, 2 },
  { 76, 1 },
  { 76, 4 },
  { 74, 0 },
  { 55, 6 },
  { 56, 6 },
  { 57, 3 },
  { 57, 4 },
  { 57, 4 },
  { 57, 5 },
  { 57, 5 },
  { 77, 2 },
  { 77, 3 },
  { 78, 0 },
  { 78, 1 },
  { 79, 1 },
  { 79, 3 },
  { 58, 3 },
  { 59, 5 },
  { 59, 7 },
  { 60, 7 },
  { 80, 0 },
  { 80, 5 },
  { 80, 4 },
  { 61, 9 },
  { 61, 7 },
  { 62, 7 },
  { 63, 2 },
  { 64, 5 },
  { 65, 5 },
  { 66, 6 },
  { 67, 5 },
  { 68, 6 },
  { 69, 7 },
  { 70, 2 },
  { 71, 3 },
  { 71, 3 },
  { 71, 3 },
  { 71, 3 },
  { 71, 2 },
  { 71, 1 },
  { 71, 1 },
  { 71, 3 },
  { 71, 3 },
  { 71, 3 },
  { 71, 2 },
  { 71, 3 },
  { 81, 3 },
  { 81, 3 },
  { 71, 1 },
  { 71, 1 },
  { 71, 4 },
  { 71, 1 },
  { 71, 3 },
  { 71, 6 },
  { 71, 4 },
  { 72, 2 },
  { 82, 0 },
  { 82, 1 },
};

/*
 * Perform a reduce action and the shift that must immediately
 * follow the reduce.
 */
void yyParser::reduce(int yyruleno)
{
	int yygoto;                     /* The next state */
	int yyact;                      /* The next action */
	YYMINORTYPE yygotominor;        /* The LHS of the rule reduced */
	yyStackEntry *yymsp;            /* The top of the parser's stack */
	int yysize;                     /* Amount to pop the stack */
	ColossusARG_FETCH;
	yymsp = &stack.top();
	
#ifndef NDEBUG
	if(yyTraceStream && yyruleno>=0 
	   && yyruleno<sizeof(yyRuleName)/sizeof(yyRuleName[0]))
	{
		*yyTraceStream << yyTracePrompt << "Reduce [" << yyRuleName[yyruleno]
		<< "]." << std::endl;
	}
#endif /* NDEBUG */
	
	switch( yyruleno)
	{
			/* Beginning here are the reduction cases.  A typical example
			 * follows:
			 *   case 0:
			 *  #line <lineno> <grammarfile>
			 *     { ... }           // User supplied code
			 *  #line <lineno> <thisfile>
			 *     break;
			 */
	}
	yygoto = yyRuleInfo[yyruleno].lhs;
	yysize = yyRuleInfo[yyruleno].nrhs;
	//index -= yysize;
	stack.lop(yysize);
	yyact = find_reduce_action(yygoto);
	if(yyact < YYNSTATE)
	{
		shift(yyact,yygoto,&yygotominor);
	}
	else if(yyact == YYNSTATE + YYNRULE + 1)
	{
		accept();
	}
}

/*
 * The following code executes when the parse fails
 */
void yyParser::parse_failed()
{
	ColossusARG_FETCH;
#ifndef NDEBUG
	if(yyTraceStream)
	{
		*yyTraceStream << yyTracePrompt << "Fail!" << std::endl;
	}
#endif
	//while(index >= 0)
	//yy_pop_parser_stack(yypParser);
	stack.clear();
	/* Here code is inserted which will be executed whenever the
	 * parser fails */
	ColossusARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
 * The following code executes when a syntax error first occurs.
 */
void yyParser::syntax_error(int yymajor, YYMINORTYPE yyminor)
{
	ColossusARG_FETCH;
#define TOKEN (yyminor.yy0)
#line 57 "ColossusParser.lmn"
cerr << "error: " << yyminor.yy0->line << ": bad syntax" <<endl;
#line 1158 "ColossusParser.cpp"
	ColossusARG_STORE; /* Suppress warning about unused %extra_argument variable */
#undef TOKEN
}

/*
 * The following is executed when the parser accepts
 */
void yyParser::accept()
{
	ColossusARG_FETCH;
#ifndef NDEBUG
	if(yyTraceStream)
	{
		*yyTraceStream << yyTracePrompt << "Accept!" << std::endl;
	}
#endif
	//while(yypParser->index>=0) yy_pop_parser_stack(yypParser);
	stack.clear();

	/* Here code is inserted which will be executed whenever the
	 * parser accepts */
#line 56 "ColossusParser.lmn"
 cout << "Compilation complete." << endl; 
#line 1182 "ColossusParser.cpp"
	ColossusARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
 * The first argument is a pointer to a structure obtained from
 * "ColossusAlloc" which describes the current state of the parser.
 * The second argument is the major token number.  The third is
 * the minor token.  The fourth optional argument is whatever the
 * user wants (and specified in the grammar) and is available for
 * use by the action routines.
 *
 * Inputs:
 * <ul>
 * <li> A pointer to the parser (an opaque structure.)
 * <li> The major token number.
 * <li> The minor token number.
 * <li> An option argument of a grammar-specified type.
 * </ul>
 *
 * Outputs:
 * None.
 */
void yyParser::Colossus(int yymajor, ColossusTOKENTYPE yyminor ColossusARG_PDECL)
{
	YYMINORTYPE yyminorunion;
	int yyact;            		/* The parser action. */
	bool yyendofinput;     		/* True if we are at the end of input */
	bool yyerrorhit = false;	/* True if yymajor has invoked an error */
	
	/* (re)initialize the parser, if necessary */
	if(stack.empty())
	{
		if(yymajor == 0)
			return;
		errCount = -1;
		stack.push(yyStackEntry());
	}
	yyminorunion.yy0 = yyminor;
	yyendofinput = (yymajor==0);
	ColossusARG_STORE;
	
#ifndef NDEBUG
	if(yyTraceStream)
	{
		*yyTraceStream << yyTracePrompt << "Input " << yyTokenName[yymajor]
		<< std::endl;
	}
#endif
	
	do
	{
		yyact = find_shift_action(yymajor);
		if(yyact<YYNSTATE)
		{
			shift(yyact,yymajor,&yyminorunion);
			errCount--;
			if(yyendofinput && stack.size())
			{
				yymajor = 0;
			}
			else
			{
				yymajor = YYNOCODE;
			}
		}
		else if(yyact < YYNSTATE + YYNRULE)
		{
			reduce(yyact-YYNSTATE);
		}
		else if(yyact == YY_ERROR_ACTION)
		{
			int yymx;
#ifndef NDEBUG
			if(yyTraceStream)
			{
				*yyTraceStream << yyTracePrompt << "Syntax Error!" << std::endl;
			}
#endif
#ifdef YYERRORSYMBOL
			/* A syntax error has occurred.
			 * The response to an error depends upon whether or not the
			 * grammar defines an error token "ERROR".  
			 *
			 * This is what we do if the grammar does define ERROR:
			 *
			 *  * Call the %syntax_error function.
			 *
			 *  * Begin popping the stack until we enter a state where
			 *    it is legal to shift the error symbol, then shift
			 *    the error symbol.
			 *
			 *  * Set the error count to three.
			 *
			 *  * Begin accepting and shifting new tokens.  No new error
			 *    processing will occur until three tokens have been
			 *    shifted successfully.
			 *
			 */
			if(errCount<0){
				syntax_error(yymajor,yyminorunion);
			}
			yymx = stack.top().major;
			if(yymx==YYERRORSYMBOL || yyerrorhit)
			{
#ifndef NDEBUG
				if(yyTraceStream)
				{
					*yyTraceStream << yyTracePrompt << "Discard input token "
						<< yyTokenName[yymajor] << std::endl;
				}
#endif
				destructor(yymajor,&yyminorunion);
				yymajor = YYNOCODE;
			}
			else
			{
				while(stack.size() >= 0 &&
					  yymx != YYERRORSYMBOL &&
					  (yyact = find_shift_action(YYERRORSYMBOL)) >= YYNSTATE)
				{
					stack.lop();
				}
				if(stack.empty() || yymajor==0)
				{
					destructor(yymajor,&yyminorunion);
					parse_failed();
					yymajor = YYNOCODE;
				}
				else if(yymx!=YYERRORSYMBOL)
				{
					YYMINORTYPE u2;
					u2.YYERRSYMDT = 0;
					shift(yyact,YYERRORSYMBOL,&u2);
				}
			}
			errCount = 3;
			yyerrorhit = true;
#else  /* YYERRORSYMBOL is not defined */
			/* This is what we do if the grammar does not define ERROR:
			 *
			 *  * Report an error message, and throw away the input token.
			 *
			 *  * If the input token is $, then fail the parse.
			 *
			 * As before, subsequent error messages are suppressed until
			 * three input tokens have been successfully shifted.
			 */
			if(errCount<=0)
			{
				syntax_error(yymajor,yyminorunion);
			}
			errCount = 3;
			destructor(yymajor,&yyminorunion);
			if(yyendofinput){
				parse_failed();
			}
			yymajor = YYNOCODE;
#endif
		}
		else
		{
			accept();
			yymajor = YYNOCODE;
		}
	}
	while(yymajor!=YYNOCODE && stack.size());
	return;
}
#line 25 "ColossusParser.lmn"


	void token_destructor(Token* t)
	{
		delete t;
	}


#line 1360 "ColossusParser.cpp"
