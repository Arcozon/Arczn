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
#line 1 "config_parser.y"

	#include <stdio.h>
	#include <stdlib.h>

	#include "parser_types.h"
	t_parsConfig	parsConfig;
	t_parsStart		parsStart;
	t_parsClr		parsClr;
	t_parsClrRules	parsClrRules;
	t_oneClrRule	parsOneClrRule;

	void	yyerror (const char []);
	void	yy_warning (const char []);
	int		yylex (void);

# define YY_THROW(str)	{yyerror(str);YYABORT;}

#line 89 "gen/config_parser.c"

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

#include "config_parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_UINT64 = 3,                     /* UINT64  */
  YYSYMBOL_UINT8 = 4,                      /* UINT8  */
  YYSYMBOL_STRING = 5,                     /* STRING  */
  YYSYMBOL_CLR_RGB = 6,                    /* CLR_RGB  */
  YYSYMBOL_SEPARATOR = 7,                  /* SEPARATOR  */
  YYSYMBOL_ASSIGN = 8,                     /* ASSIGN  */
  YYSYMBOL_WIDTH = 9,                      /* WIDTH  */
  YYSYMBOL_HEIGHT = 10,                    /* HEIGHT  */
  YYSYMBOL_FNAME = 11,                     /* FNAME  */
  YYSYMBOL_BACKGROUND = 12,                /* BACKGROUND  */
  YYSYMBOL_FILL = 13,                      /* FILL  */
  YYSYMBOL_START = 14,                     /* START  */
  YYSYMBOL_N_START = 15,                   /* N_START  */
  YYSYMBOL_COLOR = 16,                     /* COLOR  */
  YYSYMBOL_RULES = 17,                     /* RULES  */
  YYSYMBOL_X = 18,                         /* X  */
  YYSYMBOL_Y = 19,                         /* Y  */
  YYSYMBOL_TRED = 20,                      /* TRED  */
  YYSYMBOL_TGREEN = 21,                    /* TGREEN  */
  YYSYMBOL_TBLUE = 22,                     /* TBLUE  */
  YYSYMBOL_MIN = 23,                       /* MIN  */
  YYSYMBOL_MAX = 24,                       /* MAX  */
  YYSYMBOL_DELTA = 25,                     /* DELTA  */
  YYSYMBOL_26_ = 26,                       /* '{'  */
  YYSYMBOL_27_ = 27,                       /* '}'  */
  YYSYMBOL_28_ = 28,                       /* ','  */
  YYSYMBOL_29_ = 29,                       /* '-'  */
  YYSYMBOL_30_ = 30,                       /* '('  */
  YYSYMBOL_31_ = 31,                       /* ')'  */
  YYSYMBOL_32_ = 32,                       /* '['  */
  YYSYMBOL_33_ = 33,                       /* ']'  */
  YYSYMBOL_YYACCEPT = 34,                  /* $accept  */
  YYSYMBOL_config = 35,                    /* config  */
  YYSYMBOL_36_1 = 36,                      /* $@1  */
  YYSYMBOL_37_2 = 37,                      /* $@2  */
  YYSYMBOL_settings = 38,                  /* settings  */
  YYSYMBOL_settings_content = 39,          /* settings_content  */
  YYSYMBOL_backgroud = 40,                 /* backgroud  */
  YYSYMBOL_start = 41,                     /* start  */
  YYSYMBOL_42_3 = 42,                      /* $@3  */
  YYSYMBOL_start_body = 43,                /* start_body  */
  YYSYMBOL_start_body_content = 44,        /* start_body_content  */
  YYSYMBOL_color = 45,                     /* color  */
  YYSYMBOL_46_4 = 46,                      /* $@4  */
  YYSYMBOL_single_color = 47,              /* single_color  */
  YYSYMBOL_clr_rules = 48,                 /* clr_rules  */
  YYSYMBOL_49_5 = 49,                      /* $@5  */
  YYSYMBOL_one_rule = 50,                  /* one_rule  */
  YYSYMBOL_verbose_one_rule = 51,          /* verbose_one_rule  */
  YYSYMBOL_start_0_ = 52,                  /* start_0_  */
  YYSYMBOL_start_1_ = 53,                  /* start_1_  */
  YYSYMBOL_separator_0_ = 54,              /* separator_0_  */
  YYSYMBOL_separator_1_ = 55,              /* separator_1_  */
  YYSYMBOL_uint64 = 56,                    /* uint64  */
  YYSYMBOL_clr_rgb = 57                    /* clr_rgb  */
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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
#define YYLAST   116

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  46
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  127

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   280


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
      30,    31,     2,     2,    28,    29,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    32,     2,    33,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    26,     2,    27,     2,     2,     2,     2,
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
      25
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    56,    56,    59,    56,    68,    69,    73,    83,    93,
     103,   110,   113,   119,   128,   128,   135,   136,   140,   147,
     154,   161,   174,   176,   176,   178,   183,   187,   191,   198,
     198,   205,   217,   223,   229,   238,   246,   257,   258,   261,
     262,   265,   266,   268,   269,   272,   275
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
  "\"end of file\"", "error", "\"invalid token\"", "UINT64", "UINT8",
  "STRING", "CLR_RGB", "SEPARATOR", "ASSIGN", "WIDTH", "HEIGHT", "FNAME",
  "BACKGROUND", "FILL", "START", "N_START", "COLOR", "RULES", "X", "Y",
  "TRED", "TGREEN", "TBLUE", "MIN", "MAX", "DELTA", "'{'", "'}'", "','",
  "'-'", "'('", "')'", "'['", "']'", "$accept", "config", "$@1", "$@2",
  "settings", "settings_content", "backgroud", "start", "$@3",
  "start_body", "start_body_content", "color", "$@4", "single_color",
  "clr_rules", "$@5", "one_rule", "verbose_one_rule", "start_0_",
  "start_1_", "separator_0_", "separator_1_", "uint64", "clr_rgb", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-92)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-43)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -92,    10,     6,   -92,   -92,    45,   -92,    16,    30,    42,
      43,    50,    51,    33,     6,   -92,   -92,    58,    58,    57,
      -2,    58,   -92,    49,   -92,     6,   -92,    16,   -92,   -92,
     -92,   -92,   -92,   -92,    58,   -92,    38,   -92,    39,   -92,
      34,    40,    22,     6,   -92,    58,    59,    61,    62,    44,
      12,   -92,    46,    58,    58,    58,    22,    63,    68,    69,
      70,   -92,     6,    58,   -92,   -92,   -92,    52,    -1,    60,
      58,    58,    16,    56,    22,   -92,   -92,   -92,    64,    55,
     -92,   -92,   -92,    67,     6,    60,   -92,    26,    66,    77,
      78,    80,     6,    58,   -17,   -17,   -17,     0,    71,    58,
      58,   -92,   -92,   -92,     6,    58,    74,    75,     0,    79,
      58,    58,     6,    58,    81,    65,    76,    82,    58,    84,
     -92,   -92,    83,    58,   -92,    85,   -92
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,    41,     1,    43,     3,     5,    42,     0,     0,
       0,     0,     0,    14,     0,    11,    44,     0,     0,     0,
       0,     0,    39,     0,     4,    41,    37,     6,    45,     7,
       8,    10,    22,    13,     0,    12,     0,     9,     0,    38,
      14,     0,     0,    41,    40,     0,     0,     0,     0,     0,
       0,    16,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    15,     0,     0,    26,    27,    28,     0,     0,    29,
       0,     0,    17,     0,     0,    20,    46,    21,     0,     0,
      18,    19,    25,     0,    41,     0,    24,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    32,    33,    34,     0,     0,     0,     0,     0,     0,
       0,     0,    41,     0,     0,     0,     0,     0,     0,     0,
      30,    31,     0,     0,    35,     0,    36
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -92,   -92,   -92,   -92,   -92,   -92,   -92,    72,   -92,   -92,
     -92,    21,   -92,   -48,   -92,   -92,   -91,   -77,   -92,   -92,
     -11,   -13,   -18,    23
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,    13,     5,    14,    15,    22,    23,    50,
      62,    35,    36,    49,    77,    78,    92,   101,    24,    25,
       6,     7,    29,    79
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      30,    27,    26,    37,    32,    32,   104,    16,    67,    99,
       3,    33,    40,     4,    39,   100,    41,   112,   102,   103,
      89,    90,    91,    16,    34,    34,    83,    52,    57,    58,
      59,    60,    51,   -41,   -42,    64,    65,    66,    17,    61,
       4,    16,    46,    47,    48,    73,    89,    90,    91,    72,
      18,    19,    80,    81,     8,     9,    10,    11,    20,    21,
      12,    28,    31,    38,    42,    43,    76,    53,    45,    54,
      55,    68,    56,    87,    63,    98,    69,    70,    71,    97,
      74,   106,   107,    82,    85,    94,    95,   109,    96,    75,
      84,   108,   114,   115,    86,   117,    93,     0,   119,   105,
     122,   116,   110,   120,   111,   125,     0,   113,    88,   118,
     124,     0,    44,   121,   123,     0,   126
};

static const yytype_int8 yycheck[] =
{
      18,    14,    13,    21,     6,     6,    97,     7,    56,    26,
       0,    13,    25,     7,    25,    32,    34,   108,    95,    96,
      20,    21,    22,     7,    26,    26,    74,    45,    16,    17,
      18,    19,    43,     0,     0,    53,    54,    55,     8,    27,
       7,     7,    20,    21,    22,    63,    20,    21,    22,    62,
       8,     8,    70,    71,     9,    10,    11,    12,     8,     8,
      15,     3,     5,    14,    26,    26,     6,     8,    28,     8,
       8,     8,    28,    84,    28,    93,     8,     8,     8,    92,
      28,    99,   100,    27,    29,     8,     8,   105,     8,    68,
      26,   104,   110,   111,    27,   113,    30,    -1,    33,    28,
     118,   112,    28,    27,    29,   123,    -1,    28,    85,    28,
      27,    -1,    40,    31,    30,    -1,    31
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    35,    36,     0,     7,    38,    54,    55,     9,    10,
      11,    12,    15,    37,    39,    40,     7,     8,     8,     8,
       8,     8,    41,    42,    52,    53,    54,    55,     3,    56,
      56,     5,     6,    13,    26,    45,    46,    56,    14,    54,
      55,    56,    26,    26,    41,    28,    20,    21,    22,    47,
      43,    54,    56,     8,     8,     8,    28,    16,    17,    18,
      19,    27,    44,    28,    56,    56,    56,    47,     8,     8,
       8,     8,    55,    56,    28,    45,     6,    48,    49,    57,
      56,    56,    27,    47,    26,    29,    27,    54,    57,    20,
      21,    22,    50,    30,     8,     8,     8,    55,    56,    26,
      32,    51,    51,    51,    50,    28,    56,    56,    55,    56,
      28,    29,    50,    28,    56,    56,    54,    56,    28,    33,
      27,    31,    56,    30,    27,    56,    31
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    34,    36,    37,    35,    38,    38,    39,    39,    39,
      39,    39,    40,    40,    42,    41,    43,    43,    44,    44,
      44,    44,    45,    46,    45,    45,    47,    47,    47,    49,
      48,    48,    50,    50,    50,    51,    51,    52,    52,    53,
      53,    54,    54,    55,    55,    56,    57
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     0,     4,     1,     3,     3,     3,     3,
       3,     1,     3,     3,     0,     5,     1,     3,     3,     3,
       3,     3,     1,     0,     8,     7,     3,     3,     3,     0,
      10,    10,     3,     3,     3,     7,     8,     1,     2,     1,
       3,     0,     1,     1,     2,     1,     1
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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* $@1: %empty  */
#line 56 "config_parser.y"
        {
		parsConfig = (t_parsConfig){.nStart = 1};
	}
#line 1205 "gen/config_parser.c"
    break;

  case 3: /* $@2: %empty  */
#line 59 "config_parser.y"
                 {
		if (!parsConfig.width_Defined)	YY_THROW("Width not defined");
		if (!parsConfig.height_Defined)	YY_THROW("Height not defined");
		if (!parsConfig.width_Defined)	YY_THROW("Width not defined");
	}
#line 1215 "gen/config_parser.c"
    break;

  case 7: /* settings_content: WIDTH ASSIGN uint64  */
#line 74 "config_parser.y"
                {
		if (parsConfig.width_Defined)	YY_THROW("Width redefined");
		if ((yyvsp[0].uint64) == 0)	{
			yy_warning("Width was 0, set to 1 instead");
			(yyvsp[0].uint64) = 1;
		}
		parsConfig.width_Defined = 1;
		parsConfig.width = (yyvsp[0].uint64);
	}
#line 1229 "gen/config_parser.c"
    break;

  case 8: /* settings_content: HEIGHT ASSIGN uint64  */
#line 84 "config_parser.y"
        {
		if (parsConfig.height_Defined)	YY_THROW("Height redefined");
		if ((yyvsp[0].uint64) == 0)	{
			yy_warning("Height was 0, set to 1 instead");
			(yyvsp[0].uint64) = 1;
		}
		parsConfig.height_Defined = 1;
		parsConfig.height = (yyvsp[0].uint64);
	}
#line 1243 "gen/config_parser.c"
    break;

  case 9: /* settings_content: N_START ASSIGN uint64  */
#line 94 "config_parser.y"
        {
		if (parsConfig.nStart_Defined)	YY_THROW("nStart redefined");
		if ((yyvsp[0].uint64) == 0)	{
			yy_warning("nStart was 0, set to 1 instead");
			(yyvsp[0].uint64) = 1;
		}
		parsConfig.nStart_Defined = 1;
		parsConfig.nStart = (yyvsp[0].uint64);
	}
#line 1257 "gen/config_parser.c"
    break;

  case 10: /* settings_content: FNAME ASSIGN STRING  */
#line 104 "config_parser.y"
        {
		if (parsConfig.fName_Defined)	YY_THROW("Fname redefined");
		if (yylval.str == NULL)			YY_THROW("Fname malloc fail");
		parsConfig.fName_Defined = 1;
		parsConfig.fName = yylval.str;
	}
#line 1268 "gen/config_parser.c"
    break;

  case 12: /* backgroud: BACKGROUND ASSIGN color  */
#line 114 "config_parser.y"
        {
		if (parsConfig.bg_Defined)	YY_THROW("BackGround redefined");
		parsConfig.bg_Defined = 1;
		parsConfig.bg = (yyvsp[0].clr);
	}
#line 1278 "gen/config_parser.c"
    break;

  case 13: /* backgroud: BACKGROUND ASSIGN FILL  */
#line 120 "config_parser.y"
        {
		if (parsConfig.bg_Defined)	YY_THROW("BackGround redefined");
		parsConfig.bg_Defined = 1;
		parsConfig.bgFill = 1;
	}
#line 1288 "gen/config_parser.c"
    break;

  case 14: /* $@3: %empty  */
#line 128 "config_parser.y"
        {parsStart = (t_parsStart){};}
#line 1294 "gen/config_parser.c"
    break;

  case 15: /* start: $@3 START '{' start_body '}'  */
#line 130 "config_parser.y"
        {
		//Dup start
	}
#line 1302 "gen/config_parser.c"
    break;

  case 18: /* start_body_content: X ASSIGN uint64  */
#line 141 "config_parser.y"
                {
			if (parsStart.x_Defined) YY_THROW("X redefined")
			parsStart.x_Defined = 1;
			parsStart.start.x = (yyvsp[0].uint64);
			printf("X = %lu\n ", (yyvsp[0].uint64));
		}
#line 1313 "gen/config_parser.c"
    break;

  case 19: /* start_body_content: Y ASSIGN uint64  */
#line 148 "config_parser.y"
                {
			if (parsStart.y_Defined) YY_THROW("Y redefined")
			parsStart.y_Defined = 1;
			parsStart.start.y = (yyvsp[0].uint64);
			printf("Y = %lu\n ", (yyvsp[0].uint64));
		}
#line 1324 "gen/config_parser.c"
    break;

  case 20: /* start_body_content: COLOR ASSIGN color  */
#line 155 "config_parser.y"
                {
			if (parsStart.clr_Defined) YY_THROW("Color redefined")
			parsStart.clr_Defined = 1;
			parsStart.start.baseClr = (yyvsp[0].clr);
			printf("Clr = #%02X%02X%02X\n", (yyvsp[0].clr).r, (yyvsp[0].clr).g, (yyvsp[0].clr).b);
		}
#line 1335 "gen/config_parser.c"
    break;

  case 21: /* start_body_content: RULES ASSIGN clr_rules  */
#line 162 "config_parser.y"
                {
			if (parsStart.rules_Defined) YY_THROW("Color rule redefined")
			parsStart.rules_Defined = 1;
			parsStart.start.rules = (yyvsp[0].clrRules);
			printf("Color rule\n");
			printf("\t r: %u-%u (%u)\n", (yyvsp[0].clrRules).r.min, (yyvsp[0].clrRules).r.max, (yyvsp[0].clrRules).r.delta);
			printf("\t g: %u-%u (%u)\n", (yyvsp[0].clrRules).g.min, (yyvsp[0].clrRules).g.max, (yyvsp[0].clrRules).g.delta);
			printf("\t b: %u-%u (%u)\n", (yyvsp[0].clrRules).b.min, (yyvsp[0].clrRules).b.max, (yyvsp[0].clrRules).b.delta);
		}
#line 1349 "gen/config_parser.c"
    break;

  case 22: /* color: CLR_RGB  */
#line 175 "config_parser.y"
                {	(yyval.clr) = yylval.clr; }
#line 1355 "gen/config_parser.c"
    break;

  case 23: /* $@4: %empty  */
#line 176 "config_parser.y"
                {parsClr = (t_parsClr){};}
#line 1361 "gen/config_parser.c"
    break;

  case 24: /* color: $@4 '{' single_color ',' single_color ',' single_color '}'  */
#line 177 "config_parser.y"
                {	(yyval.clr) = parsClr.clr;	}
#line 1367 "gen/config_parser.c"
    break;

  case 25: /* color: '{' uint64 ',' uint64 ',' uint64 '}'  */
#line 179 "config_parser.y"
                {	(yyval.clr) = (t_clr){.r = (yyvsp[-5].uint64), .g = (yyvsp[-3].uint64), .b = (yyvsp[-1].uint64)}; }
#line 1373 "gen/config_parser.c"
    break;

  case 26: /* single_color: TRED ASSIGN uint64  */
#line 184 "config_parser.y"
                {	if (parsClr.r_Defined) YY_THROW("Red redefined")
			parsClr.clr.r = (yyvsp[0].uint64); parsClr.r_Defined = 1;
		}
#line 1381 "gen/config_parser.c"
    break;

  case 27: /* single_color: TGREEN ASSIGN uint64  */
#line 188 "config_parser.y"
                {	if (parsClr.g_Defined) YY_THROW("Green redefined")
			parsClr.clr.g = (yyvsp[0].uint64); parsClr.g_Defined = 1;
		}
#line 1389 "gen/config_parser.c"
    break;

  case 28: /* single_color: TBLUE ASSIGN uint64  */
#line 192 "config_parser.y"
                {	if (parsClr.b_Defined)  YY_THROW("Blue redefined")
			parsClr.clr.b = (yyvsp[0].uint64); parsClr.b_Defined = 1;
		}
#line 1397 "gen/config_parser.c"
    break;

  case 29: /* $@5: %empty  */
#line 198 "config_parser.y"
                { parsClrRules = (t_parsClrRules){};}
#line 1403 "gen/config_parser.c"
    break;

  case 30: /* clr_rules: $@5 '{' separator_0_ one_rule separator_1_ one_rule separator_1_ one_rule separator_0_ '}'  */
#line 204 "config_parser.y"
                { (yyval.clrRules) = parsClrRules.rules; }
#line 1409 "gen/config_parser.c"
    break;

  case 31: /* clr_rules: clr_rgb '-' clr_rgb '(' uint64 ',' uint64 ',' uint64 ')'  */
#line 206 "config_parser.y"
        {
		t_clrRules	res = {};
		res.r = (t_oneClrRules){.min = (yyvsp[-9].clr).r, .max = (yyvsp[-7].clr).r, .delta = (yyvsp[-5].uint64)};
		res.g = (t_oneClrRules){.min = (yyvsp[-9].clr).g, .max = (yyvsp[-7].clr).g, .delta = (yyvsp[-3].uint64)};
		res.b = (t_oneClrRules){.min = (yyvsp[-9].clr).b, .max = (yyvsp[-7].clr).b, .delta = (yyvsp[-1].uint64)};
		(yyval.clrRules) = res;
	}
#line 1421 "gen/config_parser.c"
    break;

  case 32: /* one_rule: TRED ASSIGN verbose_one_rule  */
#line 218 "config_parser.y"
                {
			if (parsClrRules.r_Defined)	YY_THROW("Color rule for red redefined");
			parsClrRules.r_Defined = 1;
			parsClrRules.rules.r = (yyvsp[0].oneClrRule);
		}
#line 1431 "gen/config_parser.c"
    break;

  case 33: /* one_rule: TGREEN ASSIGN verbose_one_rule  */
#line 224 "config_parser.y"
                {
			if (parsClrRules.g_Defined)	YY_THROW("Color rule for green redefined");
			parsClrRules.g_Defined = 1;
			parsClrRules.rules.g = (yyvsp[0].oneClrRule);
		}
#line 1441 "gen/config_parser.c"
    break;

  case 34: /* one_rule: TBLUE ASSIGN verbose_one_rule  */
#line 230 "config_parser.y"
                {
			if (parsClrRules.b_Defined)	YY_THROW("Color rule for blue redefined");
			parsClrRules.b_Defined = 1;
			parsClrRules.rules.b = (yyvsp[0].oneClrRule);
		}
#line 1451 "gen/config_parser.c"
    break;

  case 35: /* verbose_one_rule: '{' uint64 ',' uint64 ',' uint64 '}'  */
#line 239 "config_parser.y"
                {
			t_oneClrRules	res = {};
			res.min = (yyvsp[-5].uint64);
			res.max = (yyvsp[-3].uint64);
			res.delta = (yyvsp[-1].uint64);
			(yyval.oneClrRule) = res;
		}
#line 1463 "gen/config_parser.c"
    break;

  case 36: /* verbose_one_rule: '[' uint64 '-' uint64 ']' '(' uint64 ')'  */
#line 247 "config_parser.y"
                {
			t_oneClrRules	res = {};
			res.min = (yyvsp[-6].uint64);
			res.max = (yyvsp[-4].uint64);
			res.delta = (yyvsp[-1].uint64);
			(yyval.oneClrRule) = res;
		}
#line 1475 "gen/config_parser.c"
    break;

  case 45: /* uint64: UINT64  */
#line 273 "config_parser.y"
        { (yyval.uint64) = yylval.uint64; }
#line 1481 "gen/config_parser.c"
    break;

  case 46: /* clr_rgb: CLR_RGB  */
#line 276 "config_parser.y"
        { (yyval.clr) = yylval.clr; }
#line 1487 "gen/config_parser.c"
    break;


#line 1491 "gen/config_parser.c"

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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 279 "config_parser.y"


t_parsStart	pStart = {};

void	yyerror (const char s[]) {
	fprintf (stderr, "\033[1;31mError: \033[0;31m%s\033[0m\n", s);
}

void	yy_warning (const char s[]) {
	fprintf (stderr, "\033[1;35mWarning: \033[0;35m%s\033[0m\n", s);
}

int main(void) {
	yyparse();
}
