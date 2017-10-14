/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

  #include "ASTDefinition.h"
  #include <stdio.h>
  #include <stdlib.h>
  
  #define YYDEBUG 1

  int yylex (void);
  void yyerror (char const *s);
  ASTProgram *start = nullptr;

#line 78 "parser.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.h".  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    DECLBLOCK = 258,
    CODEBLOCK = 259,
    NUMBER = 260,
    FORLOOP = 261,
    WHILELOOP = 262,
    IF = 263,
    ELSE = 264,
    PRINT = 265,
    PRINTLN = 266,
    READ = 267,
    GOTO = 268,
    TYPE = 269,
    IDENTIFIER = 270,
    STRINGID = 271,
    ETOK = 272,
    EQTO = 273,
    LEQ = 274,
    GEQ = 275,
    NEQ = 276
  };
#endif

/* Value type.  */


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 146 "parser.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   315

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  58
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  132

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   276

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    39,     2,     2,     2,     2,     2,     2,
      34,    35,    24,    22,    30,    23,     2,    25,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    31,    29,
      38,    36,    37,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    32,     2,    33,    26,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    27,     2,    28,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    56,    56,    61,    65,    69,    75,    80,    86,    90,
      96,   101,   107,   112,   118,   122,   129,   133,   139,   143,
     149,   153,   157,   161,   165,   169,   173,   177,   182,   188,
     192,   198,   202,   206,   210,   214,   218,   222,   229,   233,
     239,   243,   247,   251,   255,   259,   263,   269,   273,   279,
     284,   288,   294,   298,   302,   306,   310,   314,   318
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DECLBLOCK", "CODEBLOCK", "NUMBER",
  "FORLOOP", "WHILELOOP", "IF", "ELSE", "PRINT", "PRINTLN", "READ", "GOTO",
  "TYPE", "IDENTIFIER", "STRINGID", "ETOK", "EQTO", "LEQ", "GEQ", "NEQ",
  "'+'", "'-'", "'*'", "'/'", "'^'", "'{'", "'}'", "';'", "','", "':'",
  "'['", "']'", "'('", "')'", "'='", "'>'", "'<'", "'!'", "$accept",
  "program", "declaration", "decl_line", "midentifiers", "statements",
  "identifier", "identifierdecl", "mathexp", "assignment",
  "cond_statement", "gotoblock", "statement_line", "forloop", "whileloop",
  "ifelse", "iostatement", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,    43,    45,    42,    47,    94,   123,   125,    59,
      44,    58,    91,    93,    40,    41,    61,    62,    60,    33
};
# endif

#define YYPACT_NINF -41

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-41)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      14,    -7,    22,    41,   -41,    -2,    21,    61,    42,   -41,
     -41,     6,    46,   -41,    23,    67,   -41,    48,   -41,    21,
     118,    50,    40,   -41,    66,     1,     1,     3,    29,    66,
      85,    53,   -41,   -41,   128,    65,    74,    75,   -41,   -41,
     -41,   -41,    91,   152,   -41,    89,    97,   -41,     0,    49,
       1,   -41,   277,   105,   110,   112,     8,   114,     8,   -41,
     137,   264,    49,    57,   -41,   -41,    49,   -41,   -41,   -41,
     -41,   162,    49,   -41,   -41,   126,   -41,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,   279,   279,    49,
      49,     1,   -41,   -12,   264,    65,     8,   -41,   -41,   282,
     -41,     8,     8,     8,     8,    34,    69,   129,   -41,     8,
       8,   186,   196,     8,     8,   -41,   -41,   -41,   279,    49,
     -41,   144,   220,   160,   139,   -41,   279,   279,   230,   254,
     -41,   -41
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     0,     0,     0,     6,
       9,    19,     0,    10,     0,     0,     7,     0,     8,     0,
       0,     0,     0,    11,     0,     0,     0,     0,     0,     0,
       0,    17,     5,    46,     0,     0,     0,     0,    15,    41,
      42,    43,     0,     0,    18,    17,     0,    25,     0,     0,
       0,    28,     0,     0,     0,    54,    56,    55,    57,    58,
      39,     0,     0,    17,     3,    14,     0,    40,    45,    44,
       4,     0,     0,    26,    27,     0,    37,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    13,     0,     0,    28,    30,    29,     2,     0,
      24,    35,    32,    31,    36,    20,    21,    22,    23,    33,
      34,     0,     0,    52,    53,    38,    16,    12,     0,     0,
      49,    51,     0,     0,     0,    48,     0,     0,     0,     0,
      47,    50
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -41,   -41,   -41,   147,   -41,   -40,   -20,   157,    33,   -17,
     -25,   -41,   -32,   -41,   -41,   -41,   -41
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     8,     9,    12,    34,    51,    13,    52,    36,
      53,    37,    38,    39,    40,    41,    42
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      35,    54,    65,    71,    35,    73,    47,    46,    47,    59,
      81,    82,    83,    84,    35,    45,    45,     1,    45,    55,
       3,   116,     4,    35,    48,    76,    48,    10,    74,    92,
      81,    82,    83,    84,    47,    49,    11,    49,    17,    65,
      50,    35,     5,     5,    45,    57,    95,   111,   112,    97,
      20,    35,    48,    22,    47,     6,     6,    82,    83,    84,
      56,    58,   117,    49,    45,    14,   115,    35,    35,     7,
      15,    21,    48,    44,    35,    18,    19,    43,   122,    65,
      65,    45,    75,    49,    61,    62,   128,   129,    94,    62,
      65,    35,    35,    83,    84,    93,    65,    65,    35,    96,
      60,    66,    35,    67,    68,    99,    35,    35,    35,    35,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
      69,    62,   113,   114,    24,    25,    26,    72,    27,    28,
      29,    30,    87,    31,    24,    25,    26,    88,    27,    28,
      29,    30,    89,    63,    90,    91,    32,    33,    81,    82,
      83,    84,   123,   124,    84,    16,    64,    33,    24,    25,
      26,   100,    27,    28,    29,    30,   127,    31,    24,    25,
      26,     0,    27,    28,    29,    30,    23,    63,     0,     0,
      70,    33,    81,    82,    83,    84,     0,   126,     0,     0,
      98,    33,    24,    25,    26,     0,    27,    28,    29,    30,
       0,    63,    24,    25,    26,     0,    27,    28,    29,    30,
       0,    63,     0,     0,   120,    33,     0,     0,     0,     0,
       0,     0,     0,     0,   121,    33,    24,    25,    26,     0,
      27,    28,    29,    30,     0,    63,    24,    25,    26,     0,
      27,    28,    29,    30,     0,    63,     0,     0,   125,    33,
       0,     0,     0,     0,     0,     0,     0,     0,   130,    33,
      24,    25,    26,     0,    27,    28,    29,    30,     0,    63,
      24,    25,    26,     0,    27,    28,    29,    30,     0,    45,
       0,     0,   131,    33,     0,    24,    25,    26,     0,    27,
      28,    29,    30,    33,    31,    77,    78,    79,    80,    81,
      82,    83,    84,     0,    81,    82,    83,    84,    33,   118,
       0,     0,   119,     0,    85,    86
};

static const yytype_int16 yycheck[] =
{
      20,    26,    34,    43,    24,     5,     5,    24,     5,    29,
      22,    23,    24,    25,    34,    15,    15,     3,    15,    16,
      27,    33,     0,    43,    23,    50,    23,    29,    48,    61,
      22,    23,    24,    25,     5,    34,    15,    34,    32,    71,
      39,    61,     1,     1,    15,    16,    66,    87,    88,    66,
      27,    71,    23,     5,     5,    14,    14,    23,    24,    25,
      27,    28,    94,    34,    15,     4,    91,    87,    88,    28,
      28,     4,    23,    33,    94,    29,    30,    27,   118,   111,
     112,    15,    49,    34,    31,    32,   126,   127,    31,    32,
     122,   111,   112,    24,    25,    62,   128,   129,   118,    66,
      15,    36,   122,    29,    29,    72,   126,   127,   128,   129,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      29,    32,    89,    90,     6,     7,     8,    30,    10,    11,
      12,    13,    27,    15,     6,     7,     8,    27,    10,    11,
      12,    13,    30,    15,    30,     8,    28,    29,    22,    23,
      24,    25,   119,     9,    25,     8,    28,    29,     6,     7,
       8,    35,    10,    11,    12,    13,    27,    15,     6,     7,
       8,    -1,    10,    11,    12,    13,    19,    15,    -1,    -1,
      28,    29,    22,    23,    24,    25,    -1,    27,    -1,    -1,
      28,    29,     6,     7,     8,    -1,    10,    11,    12,    13,
      -1,    15,     6,     7,     8,    -1,    10,    11,    12,    13,
      -1,    15,    -1,    -1,    28,    29,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    29,     6,     7,     8,    -1,
      10,    11,    12,    13,    -1,    15,     6,     7,     8,    -1,
      10,    11,    12,    13,    -1,    15,    -1,    -1,    28,    29,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,
       6,     7,     8,    -1,    10,    11,    12,    13,    -1,    15,
       6,     7,     8,    -1,    10,    11,    12,    13,    -1,    15,
      -1,    -1,    28,    29,    -1,     6,     7,     8,    -1,    10,
      11,    12,    13,    29,    15,    18,    19,    20,    21,    22,
      23,    24,    25,    -1,    22,    23,    24,    25,    29,    27,
      -1,    -1,    30,    -1,    37,    38
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    41,    27,     0,     1,    14,    28,    42,    43,
      29,    15,    44,    47,     4,    28,    43,    32,    29,    30,
      27,     4,     5,    47,     6,     7,     8,    10,    11,    12,
      13,    15,    28,    29,    45,    46,    49,    51,    52,    53,
      54,    55,    56,    27,    33,    15,    49,     5,    23,    34,
      39,    46,    48,    50,    50,    16,    48,    16,    48,    46,
      15,    31,    32,    15,    28,    52,    36,    29,    29,    29,
      28,    45,    30,     5,    46,    48,    50,    18,    19,    20,
      21,    22,    23,    24,    25,    37,    38,    27,    27,    30,
      30,     8,    52,    48,    31,    46,    48,    49,    28,    48,
      35,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    45,    45,    48,    48,    50,    33,    52,    27,    30,
      28,    28,    45,    48,     9,    28,    27,    27,    45,    45,
      28,    28
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    40,    41,    41,    41,    41,    42,    42,    43,    43,
      44,    44,    45,    45,    45,    45,    46,    46,    47,    47,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    49,
      49,    50,    50,    50,    50,    50,    50,    50,    51,    51,
      52,    52,    52,    52,    52,    52,    52,    53,    53,    54,
      55,    55,    56,    56,    56,    56,    56,    56,    56
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     8,     7,     7,     6,     1,     2,     3,     2,
       1,     3,     4,     3,     2,     1,     4,     1,     4,     1,
       3,     3,     3,     3,     3,     1,     2,     2,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     4,     2,
       2,     1,     1,     1,     2,     2,     1,     9,     7,     5,
       9,     5,     4,     4,     2,     2,     2,     2,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 57 "parser.y" /* yacc.c:1646  */
    {
					(yyval.program) = new ASTProgram((yyvsp[-5].decl_block), (yyvsp[-1].code_block));
					start = (yyval.program);
				}
#line 1344 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 62 "parser.y" /* yacc.c:1646  */
    {
					(yyval.program) = new ASTProgram((yyvsp[-1].code_block));
				}
#line 1352 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 66 "parser.y" /* yacc.c:1646  */
    {
					(yyval.program) = new ASTProgram((yyvsp[-4].decl_block));
				}
#line 1360 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 70 "parser.y" /* yacc.c:1646  */
    {
					(yyval.program) = new ASTProgram();
				}
#line 1368 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 76 "parser.y" /* yacc.c:1646  */
    {
					(yyval.decl_block) = new ASTDeclBlock();
					(yyval.decl_block)->addStatement((yyvsp[0].decl_line));
				}
#line 1377 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 81 "parser.y" /* yacc.c:1646  */
    {
					(yyval.decl_block)->addStatement((yyvsp[0].decl_line));
				}
#line 1385 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 87 "parser.y" /* yacc.c:1646  */
    {
					(yyval.decl_line) = new ASTDeclStatement(string((yyvsp[-2].string)), (yyvsp[-1].variableSet));
				}
#line 1393 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 91 "parser.y" /* yacc.c:1646  */
    {
					yyerrok;
				}
#line 1401 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 97 "parser.y" /* yacc.c:1646  */
    {
					(yyval.variableSet) = new ASTVariableSet();
					(yyval.variableSet)->addVariable((yyvsp[0].variable));
				}
#line 1410 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 102 "parser.y" /* yacc.c:1646  */
    {
					(yyval.variableSet)->addVariable((yyvsp[0].variable));
				}
#line 1418 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 108 "parser.y" /* yacc.c:1646  */
    {
					(yyvsp[0].code_statement)->setLabel((yyvsp[-2].string));
					(yyval.code_block)->addStatement((yyvsp[0].code_statement));
				}
#line 1427 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 113 "parser.y" /* yacc.c:1646  */
    {
					(yyval.code_block) = new ASTCodeBlock();
					(yyvsp[0].code_statement)->setLabel((yyvsp[-2].string));
					(yyval.code_block)->addStatement((yyvsp[0].code_statement));
				}
#line 1437 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 119 "parser.y" /* yacc.c:1646  */
    {
					(yyval.code_block)->addStatement((yyvsp[0].code_statement));
				}
#line 1445 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 123 "parser.y" /* yacc.c:1646  */
    {
					(yyval.code_block) = new ASTCodeBlock();
					(yyval.code_block)->addStatement((yyvsp[0].code_statement));
				}
#line 1454 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 130 "parser.y" /* yacc.c:1646  */
    {
					(yyval.var_location) = new ASTTargetVar((yyvsp[-3].string), (yyvsp[-1].mathexpr));
				}
#line 1462 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 134 "parser.y" /* yacc.c:1646  */
    {
					(yyval.var_location) = new ASTTargetVar((yyvsp[0].string));
				}
#line 1470 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 140 "parser.y" /* yacc.c:1646  */
    {
					(yyval.variable) = new ASTVariable(string((yyvsp[-3].string)), true, (yyvsp[-1].number));
				}
#line 1478 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 144 "parser.y" /* yacc.c:1646  */
    {
					(yyval.variable) = new ASTVariable(string((yyvsp[0].string)), false);
				}
#line 1486 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 150 "parser.y" /* yacc.c:1646  */
    {
					(yyval.mathexpr) = new ASTMathExpr((yyvsp[-2].mathexpr), (yyvsp[0].mathexpr), add);
				}
#line 1494 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 154 "parser.y" /* yacc.c:1646  */
    {
					(yyval.mathexpr) = new ASTMathExpr((yyvsp[-2].mathexpr), (yyvsp[0].mathexpr), sub);
				}
#line 1502 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 158 "parser.y" /* yacc.c:1646  */
    {
					(yyval.mathexpr) = new ASTMathExpr((yyvsp[-2].mathexpr), (yyvsp[0].mathexpr), mult);
				}
#line 1510 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 162 "parser.y" /* yacc.c:1646  */
    {
					(yyval.mathexpr) = new ASTMathExpr((yyvsp[-2].mathexpr), (yyvsp[0].mathexpr), divd);
				}
#line 1518 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 166 "parser.y" /* yacc.c:1646  */
    {
					(yyval.mathexpr) = new ASTMathExpr((yyvsp[-1].mathexpr), noop);
				}
#line 1526 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 170 "parser.y" /* yacc.c:1646  */
    {
					(yyval.mathexpr) = new ASTInteger((yyvsp[0].number));
				}
#line 1534 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 174 "parser.y" /* yacc.c:1646  */
    {
					(yyval.mathexpr) = new ASTInteger(-(yyvsp[0].number));
				}
#line 1542 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 178 "parser.y" /* yacc.c:1646  */
    {
					(yyvsp[0].var_location)->setOp(usub);
					(yyval.mathexpr) = (yyvsp[0].var_location);
				}
#line 1551 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 183 "parser.y" /* yacc.c:1646  */
    {
					(yyval.mathexpr) = (yyvsp[0].var_location);
				}
#line 1559 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 189 "parser.y" /* yacc.c:1646  */
    {
					(yyval.assignment) = new ASTAssignment((yyvsp[-2].var_location), (yyvsp[0].assignment));
				}
#line 1567 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 193 "parser.y" /* yacc.c:1646  */
    {
					(yyval.assignment) = new ASTAssignment((yyvsp[-2].var_location), (yyvsp[0].mathexpr));
				}
#line 1575 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 199 "parser.y" /* yacc.c:1646  */
    {
					(yyval.condition) = new ASTCondExpr((yyvsp[-2].mathexpr), geq, (yyvsp[0].mathexpr));
				}
#line 1583 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 203 "parser.y" /* yacc.c:1646  */
    {
					(yyval.condition) = new ASTCondExpr((yyvsp[-2].mathexpr), leq, (yyvsp[0].mathexpr));
				}
#line 1591 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 207 "parser.y" /* yacc.c:1646  */
    {
					(yyval.condition) = new ASTCondExpr((yyvsp[-2].mathexpr), grt, (yyvsp[0].mathexpr));
				}
#line 1599 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 211 "parser.y" /* yacc.c:1646  */
    {
					(yyval.condition) = new ASTCondExpr((yyvsp[-2].mathexpr), les, (yyvsp[0].mathexpr));
				}
#line 1607 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 215 "parser.y" /* yacc.c:1646  */
    {
					(yyval.condition) = new ASTCondExpr((yyvsp[-2].mathexpr), eqto, (yyvsp[0].mathexpr));
				}
#line 1615 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 219 "parser.y" /* yacc.c:1646  */
    {
					(yyval.condition) = new ASTCondExpr((yyvsp[-2].mathexpr), neq, (yyvsp[0].mathexpr));
				}
#line 1623 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 223 "parser.y" /* yacc.c:1646  */
    {
					(yyval.condition) = (yyvsp[0].condition);
					(yyval.condition)->flipNot();
				}
#line 1632 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 230 "parser.y" /* yacc.c:1646  */
    {
					(yyval.gotoblock) = new ASTGotoBlock((yyvsp[-2].string), (yyvsp[0].condition));
				}
#line 1640 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 234 "parser.y" /* yacc.c:1646  */
    {
					(yyval.gotoblock) = new ASTGotoBlock((yyvsp[0].string));
				}
#line 1648 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 240 "parser.y" /* yacc.c:1646  */
    {
					(yyval.code_statement) = (yyvsp[-1].assignment);
				}
#line 1656 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 244 "parser.y" /* yacc.c:1646  */
    {
					(yyval.code_statement) = (yyvsp[0].forloop);
				}
#line 1664 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 248 "parser.y" /* yacc.c:1646  */
    {
					(yyval.code_statement) = (yyvsp[0].whileloop);
				}
#line 1672 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 252 "parser.y" /* yacc.c:1646  */
    {
					(yyval.code_statement) = (yyvsp[0].ifelse);
				}
#line 1680 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 256 "parser.y" /* yacc.c:1646  */
    {
					(yyval.code_statement) = (yyvsp[-1].ioblock);
				}
#line 1688 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 260 "parser.y" /* yacc.c:1646  */
    {
					(yyval.code_statement) = (yyvsp[-1].gotoblock);
				}
#line 1696 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 264 "parser.y" /* yacc.c:1646  */
    {
					(yyval.code_statement) = new ASTCodeStatement();
				}
#line 1704 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 270 "parser.y" /* yacc.c:1646  */
    {
					(yyval.forloop) = new ASTForLoop((yyvsp[-7].assignment), (yyvsp[-5].mathexpr), (yyvsp[-3].mathexpr), (yyvsp[-1].code_block));
				}
#line 1712 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 274 "parser.y" /* yacc.c:1646  */
    {
					(yyval.forloop) = new ASTForLoop((yyvsp[-5].assignment), (yyvsp[-3].mathexpr), (yyvsp[-1].code_block));
				}
#line 1720 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 280 "parser.y" /* yacc.c:1646  */
    {
					(yyval.whileloop) = new ASTWhileLoop((yyvsp[-3].condition), (yyvsp[-1].code_block));
				}
#line 1728 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 285 "parser.y" /* yacc.c:1646  */
    {
					(yyval.ifelse) = new ASTIfElse((yyvsp[-7].condition), (yyvsp[-5].code_block), (yyvsp[-1].code_block));
				}
#line 1736 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 289 "parser.y" /* yacc.c:1646  */
    {
					(yyval.ifelse) = new ASTIfElse((yyvsp[-3].condition), (yyvsp[-1].code_block));
				}
#line 1744 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 295 "parser.y" /* yacc.c:1646  */
    {
					(yyval.ioblock) = new ASTIOBlock(print, (yyvsp[-2].string), (yyvsp[0].mathexpr));
				}
#line 1752 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 299 "parser.y" /* yacc.c:1646  */
    {
					(yyval.ioblock) = new ASTIOBlock(println, (yyvsp[-2].string), (yyvsp[0].mathexpr));
				}
#line 1760 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 303 "parser.y" /* yacc.c:1646  */
    {
					(yyval.ioblock) = new ASTIOBlock(print, (yyvsp[0].string));
				}
#line 1768 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 307 "parser.y" /* yacc.c:1646  */
    {
					(yyval.ioblock) = new ASTIOBlock(println, (yyvsp[0].string));
				}
#line 1776 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 311 "parser.y" /* yacc.c:1646  */
    {
					(yyval.ioblock) = new ASTIOBlock(print, (yyvsp[0].mathexpr));
				}
#line 1784 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 315 "parser.y" /* yacc.c:1646  */
    {
					(yyval.ioblock) = new ASTIOBlock(println, (yyvsp[0].mathexpr));
				}
#line 1792 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 319 "parser.y" /* yacc.c:1646  */
    {
					(yyval.ioblock) = new ASTIOBlock(readvar, (yyvsp[0].var_location));
				}
#line 1800 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 1804 "parser.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 325 "parser.y" /* yacc.c:1906  */


void yyerror (char const *s)
{
	   fprintf (stderr, "%s\n", s);
}

int main(int argc, char *argv[])
{
	extern FILE *yyin;
	if (argc == 1 ) {
		fprintf(stderr, "Correct usage: bcc filename\n");
		exit(1);
	}

	if (argc > 2) {
		fprintf(stderr, "Passing more arguments than necessary.\n");
		fprintf(stderr, "Correct usage: bcc filename\n");
	}
	yyin = fopen(argv[1], "r");

	yyparse();

	if(start)
	{
		ASTVisitor v;
		v.visit(start);
	}
}
