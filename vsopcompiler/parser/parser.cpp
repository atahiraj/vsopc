/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 10 "vsopcompiler/parser/parser.y"

	#include <cstddef>
	#include <iostream>
	#include <parser/parser.hpp>
	#include <lexer/lexer.hpp>
	std::string file_name;

	void yyerror(const char *s);
	AstNode* root;

#line 82 "vsopcompiler/parser/parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ASSIGN = 3,                     /* ASSIGN  */
  YYSYMBOL_AND = 4,                        /* AND  */
  YYSYMBOL_NOT = 5,                        /* NOT  */
  YYSYMBOL_LOWER = 6,                      /* LOWER  */
  YYSYMBOL_LOWERQ = 7,                     /* LOWERQ  */
  YYSYMBOL_EQUAL = 8,                      /* EQUAL  */
  YYSYMBOL_PLUS = 9,                       /* PLUS  */
  YYSYMBOL_MINUS = 10,                     /* MINUS  */
  YYSYMBOL_TIMES = 11,                     /* TIMES  */
  YYSYMBOL_DIVIDE = 12,                    /* DIVIDE  */
  YYSYMBOL_ISNULL = 13,                    /* ISNULL  */
  YYSYMBOL_UNARY_MINUS = 14,               /* UNARY_MINUS  */
  YYSYMBOL_POW = 15,                       /* POW  */
  YYSYMBOL_DOT = 16,                       /* DOT  */
  YYSYMBOL_BOOL = 17,                      /* BOOL  */
  YYSYMBOL_CLASS = 18,                     /* CLASS  */
  YYSYMBOL_COLON = 19,                     /* COLON  */
  YYSYMBOL_COMMA = 20,                     /* COMMA  */
  YYSYMBOL_DO = 21,                        /* DO  */
  YYSYMBOL_ELSE = 22,                      /* ELSE  */
  YYSYMBOL_EXTENDS = 23,                   /* EXTENDS  */
  YYSYMBOL_FALSE_LIT = 24,                 /* FALSE_LIT  */
  YYSYMBOL_IF = 25,                        /* IF  */
  YYSYMBOL_IN_ = 26,                       /* IN_  */
  YYSYMBOL_INT32 = 27,                     /* INT32  */
  YYSYMBOL_INT_LIT = 28,                   /* INT_LIT  */
  YYSYMBOL_LET = 29,                       /* LET  */
  YYSYMBOL_LBRACE = 30,                    /* LBRACE  */
  YYSYMBOL_LPAREN = 31,                    /* LPAREN  */
  YYSYMBOL_NEW = 32,                       /* NEW  */
  YYSYMBOL_OBJECTID = 33,                  /* OBJECTID  */
  YYSYMBOL_RBRACE = 34,                    /* RBRACE  */
  YYSYMBOL_RPAREN = 35,                    /* RPAREN  */
  YYSYMBOL_SEMICOLON = 36,                 /* SEMICOLON  */
  YYSYMBOL_STRING_TYPE = 37,               /* STRING_TYPE  */
  YYSYMBOL_STRING_LIT = 38,                /* STRING_LIT  */
  YYSYMBOL_THEN = 39,                      /* THEN  */
  YYSYMBOL_TRUE_LIT = 40,                  /* TRUE_LIT  */
  YYSYMBOL_TYPEID = 41,                    /* TYPEID  */
  YYSYMBOL_UNIT = 42,                      /* UNIT  */
  YYSYMBOL_WHILE = 43,                     /* WHILE  */
  YYSYMBOL_YYACCEPT = 44,                  /* $accept  */
  YYSYMBOL_program = 45,                   /* program  */
  YYSYMBOL_classes = 46,                   /* classes  */
  YYSYMBOL_class = 47,                     /* class  */
  YYSYMBOL_class_body = 48,                /* class_body  */
  YYSYMBOL_class_content = 49,             /* class_content  */
  YYSYMBOL_field = 50,                     /* field  */
  YYSYMBOL_method = 51,                    /* method  */
  YYSYMBOL_type = 52,                      /* type  */
  YYSYMBOL_formals = 53,                   /* formals  */
  YYSYMBOL_formal_m = 54,                  /* formal_m  */
  YYSYMBOL_formal = 55,                    /* formal  */
  YYSYMBOL_block = 56,                     /* block  */
  YYSYMBOL_expr_m = 57,                    /* expr_m  */
  YYSYMBOL_expr = 58,                      /* expr  */
  YYSYMBOL_args = 59,                      /* args  */
  YYSYMBOL_args_m = 60                     /* args_m  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   265

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  59
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  114

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   298


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   134,   134,   142,   147,   151,   162,   174,   178,   183,
     188,   195,   200,   208,   216,   217,   218,   219,   220,   224,
     229,   233,   238,   245,   253,   261,   266,   270,   277,   285,
     289,   294,   299,   304,   305,   306,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   325,   331,   335,   339,
     343,   347,   352,   357,   361,   365,   369,   374,   378,   383
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ASSIGN", "AND", "NOT",
  "LOWER", "LOWERQ", "EQUAL", "PLUS", "MINUS", "TIMES", "DIVIDE", "ISNULL",
  "UNARY_MINUS", "POW", "DOT", "BOOL", "CLASS", "COLON", "COMMA", "DO",
  "ELSE", "EXTENDS", "FALSE_LIT", "IF", "IN_", "INT32", "INT_LIT", "LET",
  "LBRACE", "LPAREN", "NEW", "OBJECTID", "RBRACE", "RPAREN", "SEMICOLON",
  "STRING_TYPE", "STRING_LIT", "THEN", "TRUE_LIT", "TYPEID", "UNIT",
  "WHILE", "$accept", "program", "classes", "class", "class_body",
  "class_content", "field", "method", "type", "formals", "formal_m",
  "formal", "block", "expr_m", "expr", "args", "args_m", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-33)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-58)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -33,     5,    -9,   -33,   -29,     9,   -20,   -11,   -33,   -33,
      15,    13,   -33,    -8,   -33,   -33,   -33,   134,    26,   -33,
     -33,   -33,   -33,   -33,     4,    25,    28,    82,   -33,    29,
      43,    44,    82,    82,    82,   -33,    82,   -33,    32,   -33,
      53,    27,    12,   -33,   -33,    82,   -33,   124,   134,   134,
     -33,   238,    39,    39,    10,    48,    82,   -33,   137,   -33,
      82,    34,   196,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    42,   -33,    46,   -33,    82,   134,    93,   -33,
     227,    54,    82,    82,   238,   249,   249,   249,    41,    41,
      39,    39,    39,    59,   -33,   179,     3,   -33,   -33,   -33,
     212,   227,    34,    82,    82,    82,   -33,    63,   227,   158,
     227,   -33,    82,   227
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     1,     0,     2,     0,     0,    10,     5,
       0,     0,     6,     0,     7,     8,     9,     0,    20,    16,
      15,    17,    14,    18,     0,     0,     0,     0,    11,     0,
       0,    19,     0,     0,     0,    51,     0,    49,     0,    26,
       0,     0,    48,    50,    52,     0,    55,     0,     0,     0,
      21,    33,    34,    35,     0,     0,     0,    54,     0,    47,
       0,    59,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    12,     0,    23,     0,     0,     0,    53,
      32,     0,     0,     0,    36,    38,    39,    37,    40,    41,
      42,    43,    44,     0,    13,    27,     0,    24,    25,    45,
      56,    29,    59,     0,     0,     0,    58,     0,    28,     0,
      30,    46,     0,    31
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -33,   -33,   -33,   -33,    64,   -33,   -33,   -33,    -7,   -33,
     -33,   -33,    20,   -33,   -32,   -23,   -33
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,     5,     9,    11,    15,    16,    24,    25,
      26,    31,    46,    56,    47,    81,    82
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      51,    52,    53,     7,    54,     3,   104,    27,    58,     4,
       8,    17,     6,    62,    63,    60,    64,    65,    66,    67,
      68,    69,    70,    18,    78,    71,    72,    -3,    80,   105,
      10,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      28,    74,    75,    61,    95,     8,    13,    14,    48,    76,
     100,   101,    69,    70,    71,    72,    71,    72,    32,   -22,
      29,    30,    49,    33,    50,    55,    34,    77,    59,   -57,
      96,   108,   109,   110,    12,    93,    39,    35,    36,   107,
     113,    37,    38,    39,    40,    41,    42,    32,    57,    99,
     102,    43,    33,    44,    94,    34,    45,    63,   111,    64,
      65,    66,    67,    68,    69,    70,    35,    36,    71,    72,
      37,    38,    39,    40,    41,    42,     0,     0,     0,     0,
      43,     0,    44,     0,     0,    45,     0,    97,    63,    98,
      64,    65,    66,    67,    68,    69,    70,     0,     0,    71,
      72,    63,     0,    64,    65,    66,    67,    68,    69,    70,
       0,    19,    71,    72,     0,     0,     0,     0,     0,     0,
      73,    20,    63,     0,    64,    65,    66,    67,    68,    69,
      70,    21,    79,    71,    72,    22,    23,     0,     0,     0,
       0,     0,     0,    63,   112,    64,    65,    66,    67,    68,
      69,    70,     0,     0,    71,    72,     0,     0,     0,     0,
      63,   103,    64,    65,    66,    67,    68,    69,    70,     0,
       0,    71,    72,     0,     0,     0,    63,    83,    64,    65,
      66,    67,    68,    69,    70,     0,     0,    71,    72,     0,
       0,    63,   106,    64,    65,    66,    67,    68,    69,    70,
       0,     0,    71,    72,    64,    65,    66,    67,    68,    69,
      70,     0,     0,    71,    72,   -58,   -58,   -58,    67,    68,
      69,    70,     0,     0,    71,    72
};

static const yytype_int8 yycheck[] =
{
      32,    33,    34,    23,    36,     0,     3,     3,    40,    18,
      30,    19,    41,    45,     4,     3,     6,     7,     8,     9,
      10,    11,    12,    31,    56,    15,    16,    18,    60,    26,
      41,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      36,    48,    49,    31,    76,    30,    33,    34,    19,    39,
      82,    83,    11,    12,    15,    16,    15,    16,     5,    33,
      35,    33,    19,    10,    20,    33,    13,    19,    41,    35,
      77,   103,   104,   105,    10,    33,    30,    24,    25,   102,
     112,    28,    29,    30,    31,    32,    33,     5,    35,    35,
      31,    38,    10,    40,    74,    13,    43,     4,    35,     6,
       7,     8,     9,    10,    11,    12,    24,    25,    15,    16,
      28,    29,    30,    31,    32,    33,    -1,    -1,    -1,    -1,
      38,    -1,    40,    -1,    -1,    43,    -1,    34,     4,    36,
       6,     7,     8,     9,    10,    11,    12,    -1,    -1,    15,
      16,     4,    -1,     6,     7,     8,     9,    10,    11,    12,
      -1,    17,    15,    16,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    27,     4,    -1,     6,     7,     8,     9,    10,    11,
      12,    37,    35,    15,    16,    41,    42,    -1,    -1,    -1,
      -1,    -1,    -1,     4,    26,     6,     7,     8,     9,    10,
      11,    12,    -1,    -1,    15,    16,    -1,    -1,    -1,    -1,
       4,    22,     6,     7,     8,     9,    10,    11,    12,    -1,
      -1,    15,    16,    -1,    -1,    -1,     4,    21,     6,     7,
       8,     9,    10,    11,    12,    -1,    -1,    15,    16,    -1,
      -1,     4,    20,     6,     7,     8,     9,    10,    11,    12,
      -1,    -1,    15,    16,     6,     7,     8,     9,    10,    11,
      12,    -1,    -1,    15,    16,     6,     7,     8,     9,    10,
      11,    12,    -1,    -1,    15,    16
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    45,    46,     0,    18,    47,    41,    23,    30,    48,
      41,    49,    48,    33,    34,    50,    51,    19,    31,    17,
      27,    37,    41,    42,    52,    53,    54,     3,    36,    35,
      33,    55,     5,    10,    13,    24,    25,    28,    29,    30,
      31,    32,    33,    38,    40,    43,    56,    58,    19,    19,
      20,    58,    58,    58,    58,    33,    57,    35,    58,    41,
       3,    31,    58,     4,     6,     7,     8,     9,    10,    11,
      12,    15,    16,    36,    52,    52,    39,    19,    58,    35,
      58,    59,    60,    21,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    33,    56,    58,    52,    34,    36,    35,
      58,    58,    31,    22,     3,    26,    20,    59,    58,    58,
      58,    35,    26,    58
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    44,    45,    46,    46,    47,    47,    48,    49,    49,
      49,    50,    50,    51,    52,    52,    52,    52,    52,    53,
      53,    54,    54,    55,    56,    57,    57,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    59,    59,    60,    60
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     0,     3,     5,     3,     2,     2,
       0,     4,     6,     7,     1,     1,     1,     1,     1,     2,
       0,     3,     0,     3,     4,     3,     0,     4,     6,     4,
       6,     8,     3,     2,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     4,     6,     2,     1,     1,
       1,     1,     1,     3,     2,     1,     2,     0,     3,     0
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: classes class  */
#line 135 "vsopcompiler/parser/parser.y"
        {
		(yyvsp[-1].class_node_vect)->push_back((yyvsp[0].class_node));
		root = new AstNode(* new YYLTYPE((yyloc)), * (yyvsp[-1].class_node_vect));
	}
#line 1347 "vsopcompiler/parser/parser.cpp"
    break;

  case 3: /* classes: classes class  */
#line 143 "vsopcompiler/parser/parser.y"
        {
		(yyvsp[-1].class_node_vect)->push_back((yyvsp[0].class_node));
		(yyval.class_node_vect) = (yyvsp[-1].class_node_vect);
	}
#line 1356 "vsopcompiler/parser/parser.cpp"
    break;

  case 4: /* classes: %empty  */
#line 147 "vsopcompiler/parser/parser.y"
           {(yyval.class_node_vect) = new std::vector<ClassNode*>();}
#line 1362 "vsopcompiler/parser/parser.cpp"
    break;

  case 5: /* class: CLASS TYPEID class_body  */
#line 152 "vsopcompiler/parser/parser.y"
        {
		std::vector<FieldNode*>& field_nodes = * (yyvsp[0].field_method_pair)->first;
		std::vector<MethodNode*>& method_nodes = * (yyvsp[0].field_method_pair)->second;

		delete (yyvsp[0].field_method_pair);
		
		(yyval.class_node) = new ClassNode(* new YYLTYPE((yyloc)), * (yyvsp[-1].str), * new std::string("Object"), field_nodes, method_nodes);
	}
#line 1375 "vsopcompiler/parser/parser.cpp"
    break;

  case 6: /* class: CLASS TYPEID EXTENDS TYPEID class_body  */
#line 163 "vsopcompiler/parser/parser.y"
        {
		std::vector<FieldNode*>& field_nodes = * (yyvsp[0].field_method_pair)->first;
		std::vector<MethodNode*>& method_nodes = * (yyvsp[0].field_method_pair)->second;

		delete (yyvsp[0].field_method_pair);

		(yyval.class_node) = new ClassNode(* new YYLTYPE((yyloc)), * (yyvsp[-3].str), * (yyvsp[-1].str), field_nodes, method_nodes);
	}
#line 1388 "vsopcompiler/parser/parser.cpp"
    break;

  case 7: /* class_body: LBRACE class_content RBRACE  */
#line 174 "vsopcompiler/parser/parser.y"
                                    {(yyval.field_method_pair) = (yyvsp[-1].field_method_pair);}
#line 1394 "vsopcompiler/parser/parser.cpp"
    break;

  case 8: /* class_content: class_content field  */
#line 179 "vsopcompiler/parser/parser.y"
        {
		(yyvsp[-1].field_method_pair)->first->push_back((yyvsp[0].field_node));
		(yyval.field_method_pair) = (yyvsp[-1].field_method_pair);
	}
#line 1403 "vsopcompiler/parser/parser.cpp"
    break;

  case 9: /* class_content: class_content method  */
#line 184 "vsopcompiler/parser/parser.y"
        {
		(yyvsp[-1].field_method_pair)->second->push_back((yyvsp[0].method_node));
		(yyval.field_method_pair) = (yyvsp[-1].field_method_pair);
	}
#line 1412 "vsopcompiler/parser/parser.cpp"
    break;

  case 10: /* class_content: %empty  */
#line 189 "vsopcompiler/parser/parser.y"
        {
		(yyval.field_method_pair) = new std::pair<std::vector<FieldNode*>*, std::vector<MethodNode*>*> (new std::vector<FieldNode*>(), new std::vector<MethodNode*>());
	}
#line 1420 "vsopcompiler/parser/parser.cpp"
    break;

  case 11: /* field: OBJECTID COLON type SEMICOLON  */
#line 196 "vsopcompiler/parser/parser.y"
        {
		ObjectIDNode& objectID = * new ObjectIDNode(* new YYLTYPE((yylsp[-3])), * (yyvsp[-3].str));
		(yyval.field_node) = new FieldNode(* new YYLTYPE((yyloc)), objectID, * new DummyNode(), * (yyvsp[-1].str));
	}
#line 1429 "vsopcompiler/parser/parser.cpp"
    break;

  case 12: /* field: OBJECTID COLON type ASSIGN expr SEMICOLON  */
#line 201 "vsopcompiler/parser/parser.y"
        {
		ObjectIDNode& objectID = * new ObjectIDNode(* new YYLTYPE((yylsp[-5])), * (yyvsp[-5].str));
		(yyval.field_node) = new FieldNode(* new YYLTYPE((yyloc)), objectID, * (yyvsp[-1].node), * (yyvsp[-3].str));
	}
#line 1438 "vsopcompiler/parser/parser.cpp"
    break;

  case 13: /* method: OBJECTID LPAREN formals RPAREN COLON type block  */
#line 209 "vsopcompiler/parser/parser.y"
        {
		ObjectIDNode& objectID = * new ObjectIDNode(* new YYLTYPE((yylsp[-6])), * (yyvsp[-6].str));
		(yyval.method_node) = new MethodNode(* new YYLTYPE((yyloc)), * (yyvsp[0].block_node), objectID, * (yyvsp[-4].formals_node), * (yyvsp[-1].str));
	}
#line 1447 "vsopcompiler/parser/parser.cpp"
    break;

  case 14: /* type: TYPEID  */
#line 216 "vsopcompiler/parser/parser.y"
               {(yyval.str) = (yyvsp[0].str);}
#line 1453 "vsopcompiler/parser/parser.cpp"
    break;

  case 15: /* type: INT32  */
#line 217 "vsopcompiler/parser/parser.y"
          {(yyval.str) = new std::string("int32");}
#line 1459 "vsopcompiler/parser/parser.cpp"
    break;

  case 16: /* type: BOOL  */
#line 218 "vsopcompiler/parser/parser.y"
         {(yyval.str) = new std::string("bool");}
#line 1465 "vsopcompiler/parser/parser.cpp"
    break;

  case 17: /* type: STRING_TYPE  */
#line 219 "vsopcompiler/parser/parser.y"
                {(yyval.str) = new std::string("string");}
#line 1471 "vsopcompiler/parser/parser.cpp"
    break;

  case 18: /* type: UNIT  */
#line 220 "vsopcompiler/parser/parser.y"
         {(yyval.str) = new std::string("unit");}
#line 1477 "vsopcompiler/parser/parser.cpp"
    break;

  case 19: /* formals: formal_m formal  */
#line 225 "vsopcompiler/parser/parser.y"
        {
		(yyvsp[-1].formal_pair_vect)->push_back((yyvsp[0].formal_pair));
		(yyval.formals_node) = new FormalsNode(* new YYLTYPE((yyloc)), * (yyvsp[-1].formal_pair_vect));
	}
#line 1486 "vsopcompiler/parser/parser.cpp"
    break;

  case 20: /* formals: %empty  */
#line 229 "vsopcompiler/parser/parser.y"
           {(yyval.formals_node) = new DummyNode();}
#line 1492 "vsopcompiler/parser/parser.cpp"
    break;

  case 21: /* formal_m: formal_m formal COMMA  */
#line 234 "vsopcompiler/parser/parser.y"
        {
		(yyvsp[-2].formal_pair_vect)->push_back((yyvsp[-1].formal_pair));
		(yyval.formal_pair_vect) = (yyvsp[-2].formal_pair_vect);
	}
#line 1501 "vsopcompiler/parser/parser.cpp"
    break;

  case 22: /* formal_m: %empty  */
#line 239 "vsopcompiler/parser/parser.y"
        {
		(yyval.formal_pair_vect) = new std::vector<std::pair<ObjectIDNode*, std::string*>*>();
	}
#line 1509 "vsopcompiler/parser/parser.cpp"
    break;

  case 23: /* formal: OBJECTID COLON type  */
#line 246 "vsopcompiler/parser/parser.y"
        {
		ObjectIDNode& objectID = * new ObjectIDNode(* new YYLTYPE((yylsp[-2])), * (yyvsp[-2].str));
		(yyval.formal_pair) = new std::pair<ObjectIDNode*, std::string*>(&objectID, (yyvsp[0].str));
	}
#line 1518 "vsopcompiler/parser/parser.cpp"
    break;

  case 24: /* block: LBRACE expr_m expr RBRACE  */
#line 254 "vsopcompiler/parser/parser.y"
        {
		(yyvsp[-2].node_vect)->push_back((yyvsp[-1].node));
		(yyval.block_node) = new BlockNode(* new YYLTYPE((yyloc)), * (yyvsp[-2].node_vect));
	}
#line 1527 "vsopcompiler/parser/parser.cpp"
    break;

  case 25: /* expr_m: expr_m expr SEMICOLON  */
#line 262 "vsopcompiler/parser/parser.y"
        {
		(yyvsp[-2].node_vect)->push_back((yyvsp[-1].node));
		(yyval.node_vect) = (yyvsp[-2].node_vect);
	}
#line 1536 "vsopcompiler/parser/parser.cpp"
    break;

  case 26: /* expr_m: %empty  */
#line 266 "vsopcompiler/parser/parser.y"
           {(yyval.node_vect) = new std::vector<Node*>();}
#line 1542 "vsopcompiler/parser/parser.cpp"
    break;

  case 27: /* expr: IF expr THEN expr  */
#line 271 "vsopcompiler/parser/parser.y"
        {
		std::vector<Node*>& exprs = * new std::vector<Node*>();
		exprs.push_back((yyvsp[-2].node));
		exprs.push_back((yyvsp[0].node));
		(yyval.node) = new IfNode(* new YYLTYPE((yyloc)), exprs);
	}
#line 1553 "vsopcompiler/parser/parser.cpp"
    break;

  case 28: /* expr: IF expr THEN expr ELSE expr  */
#line 278 "vsopcompiler/parser/parser.y"
        {
		std::vector<Node*>& exprs = * new std::vector<Node*>();
		exprs.push_back((yyvsp[-4].node));
		exprs.push_back((yyvsp[-2].node));
		exprs.push_back((yyvsp[0].node));
		(yyval.node) = new IfNode(* new YYLTYPE((yyloc)), exprs);
	}
#line 1565 "vsopcompiler/parser/parser.cpp"
    break;

  case 29: /* expr: WHILE expr DO expr  */
#line 286 "vsopcompiler/parser/parser.y"
        {
		(yyval.node) = new WhileNode(* new YYLTYPE((yyloc)), * (yyvsp[-2].node), * (yyvsp[0].node));
	}
#line 1573 "vsopcompiler/parser/parser.cpp"
    break;

  case 30: /* expr: LET OBJECTID COLON type IN_ expr  */
#line 290 "vsopcompiler/parser/parser.y"
        {
		ObjectIDNode& objectID = * new ObjectIDNode(* new YYLTYPE((yylsp[-4])), * (yyvsp[-4].str));
		(yyval.node) = new LetNode(* new YYLTYPE((yyloc)), objectID, * new DummyNode(), * (yyvsp[0].node), * (yyvsp[-2].str));
	}
#line 1582 "vsopcompiler/parser/parser.cpp"
    break;

  case 31: /* expr: LET OBJECTID COLON type ASSIGN expr IN_ expr  */
#line 295 "vsopcompiler/parser/parser.y"
        {
		ObjectIDNode& objectID = * new ObjectIDNode(* new YYLTYPE((yylsp[-6])), * (yyvsp[-6].str));
		(yyval.node) = new LetNode(* new YYLTYPE((yyloc)), objectID, * (yyvsp[-2].node), * (yyvsp[0].node), * (yyvsp[-4].str));
	}
#line 1591 "vsopcompiler/parser/parser.cpp"
    break;

  case 32: /* expr: OBJECTID ASSIGN expr  */
#line 300 "vsopcompiler/parser/parser.y"
        {
		ObjectIDNode& objectID = * new ObjectIDNode(* new YYLTYPE((yylsp[-2])), * (yyvsp[-2].str));
		(yyval.node) = new AssignNode(* new YYLTYPE((yyloc)), objectID, * (yyvsp[0].node));
	}
#line 1600 "vsopcompiler/parser/parser.cpp"
    break;

  case 33: /* expr: NOT expr  */
#line 304 "vsopcompiler/parser/parser.y"
             {(yyval.node) = new UnaryOpNode(* new YYLTYPE((yyloc)), UnaryOpNode::unaryType::NOT, * (yyvsp[0].node));}
#line 1606 "vsopcompiler/parser/parser.cpp"
    break;

  case 34: /* expr: MINUS expr  */
#line 305 "vsopcompiler/parser/parser.y"
                                 {(yyval.node) = new UnaryOpNode(* new YYLTYPE((yyloc)), UnaryOpNode::unaryType::MINUS, * (yyvsp[0].node));}
#line 1612 "vsopcompiler/parser/parser.cpp"
    break;

  case 35: /* expr: ISNULL expr  */
#line 306 "vsopcompiler/parser/parser.y"
                {(yyval.node) = new UnaryOpNode(* new YYLTYPE((yyloc)), UnaryOpNode::unaryType::ISNULL, * (yyvsp[0].node));}
#line 1618 "vsopcompiler/parser/parser.cpp"
    break;

  case 36: /* expr: expr AND expr  */
#line 308 "vsopcompiler/parser/parser.y"
                  {(yyval.node) = new BinaryOpNode(* new YYLTYPE((yyloc)), BinaryOpNode::binaryType::AND, * (yyvsp[-2].node), * (yyvsp[0].node));}
#line 1624 "vsopcompiler/parser/parser.cpp"
    break;

  case 37: /* expr: expr EQUAL expr  */
#line 309 "vsopcompiler/parser/parser.y"
                    {(yyval.node) = new BinaryOpNode(* new YYLTYPE((yyloc)), BinaryOpNode::binaryType::EQUAL, * (yyvsp[-2].node), * (yyvsp[0].node));}
#line 1630 "vsopcompiler/parser/parser.cpp"
    break;

  case 38: /* expr: expr LOWER expr  */
#line 310 "vsopcompiler/parser/parser.y"
                    {(yyval.node) = new BinaryOpNode(* new YYLTYPE((yyloc)), BinaryOpNode::binaryType::LOWER, * (yyvsp[-2].node), * (yyvsp[0].node));}
#line 1636 "vsopcompiler/parser/parser.cpp"
    break;

  case 39: /* expr: expr LOWERQ expr  */
#line 311 "vsopcompiler/parser/parser.y"
                     {(yyval.node) = new BinaryOpNode(* new YYLTYPE((yyloc)), BinaryOpNode::binaryType::LOWERQ, * (yyvsp[-2].node), * (yyvsp[0].node));}
#line 1642 "vsopcompiler/parser/parser.cpp"
    break;

  case 40: /* expr: expr PLUS expr  */
#line 312 "vsopcompiler/parser/parser.y"
                   {(yyval.node) = new BinaryOpNode(* new YYLTYPE((yyloc)), BinaryOpNode::binaryType::PLUS, * (yyvsp[-2].node), * (yyvsp[0].node));}
#line 1648 "vsopcompiler/parser/parser.cpp"
    break;

  case 41: /* expr: expr MINUS expr  */
#line 313 "vsopcompiler/parser/parser.y"
                    {(yyval.node) = new BinaryOpNode(* new YYLTYPE((yyloc)), BinaryOpNode::binaryType::MINUS, * (yyvsp[-2].node), * (yyvsp[0].node));}
#line 1654 "vsopcompiler/parser/parser.cpp"
    break;

  case 42: /* expr: expr TIMES expr  */
#line 314 "vsopcompiler/parser/parser.y"
                    {(yyval.node) = new BinaryOpNode(* new YYLTYPE((yyloc)), BinaryOpNode::binaryType::TIMES, * (yyvsp[-2].node), * (yyvsp[0].node));}
#line 1660 "vsopcompiler/parser/parser.cpp"
    break;

  case 43: /* expr: expr DIVIDE expr  */
#line 315 "vsopcompiler/parser/parser.y"
                     {(yyval.node) = new BinaryOpNode(* new YYLTYPE((yyloc)), BinaryOpNode::binaryType::DIVIDE, * (yyvsp[-2].node), * (yyvsp[0].node));}
#line 1666 "vsopcompiler/parser/parser.cpp"
    break;

  case 44: /* expr: expr POW expr  */
#line 316 "vsopcompiler/parser/parser.y"
                  {(yyval.node) = new BinaryOpNode(* new YYLTYPE((yyloc)), BinaryOpNode::binaryType::POW, * (yyvsp[-2].node), * (yyvsp[0].node));}
#line 1672 "vsopcompiler/parser/parser.cpp"
    break;

  case 45: /* expr: OBJECTID LPAREN args RPAREN  */
#line 318 "vsopcompiler/parser/parser.y"
        {
		ObjectIDNode& objectID = * new ObjectIDNode(* new YYLTYPE((yylsp[-3])), * (yyvsp[-3].str));
		ObjectIDNode& selfObj = * new ObjectIDNode(* new YYLTYPE((yyloc)), * new std::string("self"));

		
		(yyval.node) = new CallNode(* new YYLTYPE((yyloc)), selfObj, objectID, * (yyvsp[-1].node_vect));
	}
#line 1684 "vsopcompiler/parser/parser.cpp"
    break;

  case 46: /* expr: expr DOT OBJECTID LPAREN args RPAREN  */
#line 326 "vsopcompiler/parser/parser.y"
        {
		ObjectIDNode& objectID = * new ObjectIDNode(* new YYLTYPE((yylsp[-3])), * (yyvsp[-3].str));

		(yyval.node) = new CallNode(* new YYLTYPE((yyloc)), * (yyvsp[-5].node), objectID, * (yyvsp[-1].node_vect));
	}
#line 1694 "vsopcompiler/parser/parser.cpp"
    break;

  case 47: /* expr: NEW TYPEID  */
#line 332 "vsopcompiler/parser/parser.y"
        {
		(yyval.node) = new NewNode(* new YYLTYPE((yyloc)), * (yyvsp[0].str));
	}
#line 1702 "vsopcompiler/parser/parser.cpp"
    break;

  case 48: /* expr: OBJECTID  */
#line 336 "vsopcompiler/parser/parser.y"
        {
		(yyval.node) = new ObjectIDNode(* new YYLTYPE((yyloc)), * (yyvsp[0].str));
	}
#line 1710 "vsopcompiler/parser/parser.cpp"
    break;

  case 49: /* expr: INT_LIT  */
#line 340 "vsopcompiler/parser/parser.y"
        {
		(yyval.node) = new LiteralNode(* new YYLTYPE((yyloc)), LiteralNode::literalType::INTEGER, * (yyvsp[0].str));
	}
#line 1718 "vsopcompiler/parser/parser.cpp"
    break;

  case 50: /* expr: STRING_LIT  */
#line 344 "vsopcompiler/parser/parser.y"
        {
		(yyval.node) = new LiteralNode(* new YYLTYPE((yyloc)), LiteralNode::literalType::STRING, * (yyvsp[0].str));
	}
#line 1726 "vsopcompiler/parser/parser.cpp"
    break;

  case 51: /* expr: FALSE_LIT  */
#line 348 "vsopcompiler/parser/parser.y"
        {;
		(yyval.node) = new LiteralNode(* new YYLTYPE((yyloc)), LiteralNode::literalType::BOOL,
								* new std::string("false"));
	}
#line 1735 "vsopcompiler/parser/parser.cpp"
    break;

  case 52: /* expr: TRUE_LIT  */
#line 353 "vsopcompiler/parser/parser.y"
        {
		(yyval.node) = new LiteralNode(* new YYLTYPE((yyloc)), LiteralNode::literalType::BOOL,
								* new std::string("true"));
	}
#line 1744 "vsopcompiler/parser/parser.cpp"
    break;

  case 53: /* expr: LPAREN expr RPAREN  */
#line 358 "vsopcompiler/parser/parser.y"
        {
		(yyval.node) = (yyvsp[-1].node);
	}
#line 1752 "vsopcompiler/parser/parser.cpp"
    break;

  case 54: /* expr: LPAREN RPAREN  */
#line 362 "vsopcompiler/parser/parser.y"
        {
		(yyval.node) = new UnitNode(* new YYLTYPE((yyloc)));
	}
#line 1760 "vsopcompiler/parser/parser.cpp"
    break;

  case 55: /* expr: block  */
#line 365 "vsopcompiler/parser/parser.y"
          {(yyval.node) = (yyvsp[0].block_node);}
#line 1766 "vsopcompiler/parser/parser.cpp"
    break;

  case 56: /* args: args_m expr  */
#line 370 "vsopcompiler/parser/parser.y"
        {
		(yyvsp[-1].node_vect)->push_back((yyvsp[0].node));
		(yyval.node_vect) = (yyvsp[-1].node_vect);
	}
#line 1775 "vsopcompiler/parser/parser.cpp"
    break;

  case 57: /* args: %empty  */
#line 374 "vsopcompiler/parser/parser.y"
           {(yyval.node_vect) = new std::vector<Node*>();}
#line 1781 "vsopcompiler/parser/parser.cpp"
    break;

  case 58: /* args_m: args_m expr COMMA  */
#line 379 "vsopcompiler/parser/parser.y"
        {
		(yyvsp[-2].node_vect)->push_back((yyvsp[-1].node));
		(yyval.node_vect) = (yyvsp[-2].node_vect);
	}
#line 1790 "vsopcompiler/parser/parser.cpp"
    break;

  case 59: /* args_m: %empty  */
#line 383 "vsopcompiler/parser/parser.y"
           {(yyval.node_vect) = new std::vector<Node*>();}
#line 1796 "vsopcompiler/parser/parser.cpp"
    break;


#line 1800 "vsopcompiler/parser/parser.cpp"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 386 "vsopcompiler/parser/parser.y"


/********************************* EPILOGUE ***********************************/

void yyerror(const char *s)
{
	std::cerr << file_name << ":" << yylloc.first_line << ":" << yylloc.first_column << ": " << s << std::endl;
}

AstNode * parse(char* filename)
{
	int ret = 0;
	file_name = std::string(filename);
	ret = yyparse();

	
	if(ret == 0)
		return root;
	else
		return nullptr;
}
