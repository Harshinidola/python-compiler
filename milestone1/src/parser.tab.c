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
#line 1 "parser.y"

    #include <bits/stdc++.h>
    using namespace std;
    void yyerror1(const char *s,int line);
    void yyerror(const char *s);
    extern "C" int yylex();
    extern "C" int yylineno;
    extern stack <int> indent_stack;
    char* numtochar( int num){
        string s="0";
        while(num>0){
            s.push_back(num%10+'0');
            num/=10;
        }
        reverse(s.begin(),s.end());
        int n=s.size();
        char* c= (char*)malloc(sizeof(char)*(n+1));
        for( int i=0;i<n;i++){
            c[i]=s[i];
        }
        c[n]='\0';
        return c;
    }
    int chartonum(char * c){
        int i=0;
        int num=0;
        while(c[i]!='\0'){
            num*=10;
            num+=c[i]-'0';
            i++;
        }
        return num;
    }
    struct node{
        int num;
        string l;
    } ;
    struct edge{
        int a;
        int b;
        string l;
    };

    vector<node> nodes;
    vector<edge> edges;
    char* addnode(string c){
        int n=nodes.size()+1;
        node q;
        q.num=n*10;
        q.l=c;
        nodes.push_back(q);
        return numtochar(n);
    }
    void addedge(char* a, char* b, string l=""){
        edge q;
        q.a=chartonum(a);
        q.b=chartonum(b);
        q.l=l;
        edges.push_back(q);

    }

#line 134 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NEWLINE = 3,                    /* NEWLINE  */
  YYSYMBOL_INDENT = 4,                     /* INDENT  */
  YYSYMBOL_DEDENT = 5,                     /* DEDENT  */
  YYSYMBOL_ENDMARKER = 6,                  /* ENDMARKER  */
  YYSYMBOL_DUNDER = 7,                     /* DUNDER  */
  YYSYMBOL_DATATYPE = 8,                   /* DATATYPE  */
  YYSYMBOL_IS = 9,                         /* IS  */
  YYSYMBOL_IF = 10,                        /* IF  */
  YYSYMBOL_ELSE = 11,                      /* ELSE  */
  YYSYMBOL_ELIF = 12,                      /* ELIF  */
  YYSYMBOL_WHILE = 13,                     /* WHILE  */
  YYSYMBOL_FOR = 14,                       /* FOR  */
  YYSYMBOL_TRY = 15,                       /* TRY  */
  YYSYMBOL_RETURN = 16,                    /* RETURN  */
  YYSYMBOL_YIELD = 17,                     /* YIELD  */
  YYSYMBOL_IN = 18,                        /* IN  */
  YYSYMBOL_FINALLY = 19,                   /* FINALLY  */
  YYSYMBOL_GLOBAL = 20,                    /* GLOBAL  */
  YYSYMBOL_EXCEPT = 21,                    /* EXCEPT  */
  YYSYMBOL_AS = 22,                        /* AS  */
  YYSYMBOL_DEF = 23,                       /* DEF  */
  YYSYMBOL_CLASS = 24,                     /* CLASS  */
  YYSYMBOL_ASSERT = 25,                    /* ASSERT  */
  YYSYMBOL_FROM = 26,                      /* FROM  */
  YYSYMBOL_CONTINUE = 27,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 28,                     /* BREAK  */
  YYSYMBOL_RAISE = 29,                     /* RAISE  */
  YYSYMBOL_NONE = 30,                      /* NONE  */
  YYSYMBOL_TRUE = 31,                      /* TRUE  */
  YYSYMBOL_FALSE = 32,                     /* FALSE  */
  YYSYMBOL_AND = 33,                       /* AND  */
  YYSYMBOL_NOT = 34,                       /* NOT  */
  YYSYMBOL_OR = 35,                        /* OR  */
  YYSYMBOL_DEL = 36,                       /* DEL  */
  YYSYMBOL_INT = 37,                       /* INT  */
  YYSYMBOL_FLOAT = 38,                     /* FLOAT  */
  YYSYMBOL_STR = 39,                       /* STR  */
  YYSYMBOL_BOOL = 40,                      /* BOOL  */
  YYSYMBOL_IDENTIFIER = 41,                /* IDENTIFIER  */
  YYSYMBOL_EEQ = 42,                       /* EEQ  */
  YYSYMBOL_GEQ = 43,                       /* GEQ  */
  YYSYMBOL_LEQ = 44,                       /* LEQ  */
  YYSYMBOL_NEQ = 45,                       /* NEQ  */
  YYSYMBOL_LLT = 46,                       /* LLT  */
  YYSYMBOL_GGT = 47,                       /* GGT  */
  YYSYMBOL_PEQ = 48,                       /* PEQ  */
  YYSYMBOL_MIEQ = 49,                      /* MIEQ  */
  YYSYMBOL_MUEQ = 50,                      /* MUEQ  */
  YYSYMBOL_DEQ = 51,                       /* DEQ  */
  YYSYMBOL_DDEQ = 52,                      /* DDEQ  */
  YYSYMBOL_MOEQ = 53,                      /* MOEQ  */
  YYSYMBOL_MUMUEQ = 54,                    /* MUMUEQ  */
  YYSYMBOL_AEQ = 55,                       /* AEQ  */
  YYSYMBOL_ALEQ = 56,                      /* ALEQ  */
  YYSYMBOL_POEQ = 57,                      /* POEQ  */
  YYSYMBOL_LLEQ = 58,                      /* LLEQ  */
  YYSYMBOL_GGEQ = 59,                      /* GGEQ  */
  YYSYMBOL_STRING = 60,                    /* STRING  */
  YYSYMBOL_NUMBER = 61,                    /* NUMBER  */
  YYSYMBOL_SSTAR = 62,                     /* SSTAR  */
  YYSYMBOL_DDOT = 63,                      /* DDOT  */
  YYSYMBOL_DMOND = 64,                     /* DMOND  */
  YYSYMBOL_ARROW = 65,                     /* ARROW  */
  YYSYMBOL_SSLASH = 66,                    /* SSLASH  */
  YYSYMBOL_COLON = 67,                     /* COLON  */
  YYSYMBOL_SEMICOLON = 68,                 /* SEMICOLON  */
  YYSYMBOL_PLUS = 69,                      /* PLUS  */
  YYSYMBOL_MINUS = 70,                     /* MINUS  */
  YYSYMBOL_DIVI = 71,                      /* DIVI  */
  YYSYMBOL_EQUAL = 72,                     /* EQUAL  */
  YYSYMBOL_COMMA = 73,                     /* COMMA  */
  YYSYMBOL_ALTE = 74,                      /* ALTE  */
  YYSYMBOL_AAND = 75,                      /* AAND  */
  YYSYMBOL_POWER = 76,                     /* POWER  */
  YYSYMBOL_MULTI = 77,                     /* MULTI  */
  YYSYMBOL_MOD = 78,                       /* MOD  */
  YYSYMBOL_NOPE = 79,                      /* NOPE  */
  YYSYMBOL_CIROPEN = 80,                   /* CIROPEN  */
  YYSYMBOL_CIRCLOSE = 81,                  /* CIRCLOSE  */
  YYSYMBOL_SQOPEN = 82,                    /* SQOPEN  */
  YYSYMBOL_SQCLOSE = 83,                   /* SQCLOSE  */
  YYSYMBOL_CUOPEN = 84,                    /* CUOPEN  */
  YYSYMBOL_CUCLOSE = 85,                   /* CUCLOSE  */
  YYSYMBOL_DOT = 86,                       /* DOT  */
  YYSYMBOL_LT = 87,                        /* LT  */
  YYSYMBOL_GT = 88,                        /* GT  */
  YYSYMBOL_ADUNDER = 89,                   /* ADUNDER  */
  YYSYMBOL_YYACCEPT = 90,                  /* $accept  */
  YYSYMBOL_starting = 91,                  /* starting  */
  YYSYMBOL_file_input = 92,                /* file_input  */
  YYSYMBOL_ns_sure = 93,                   /* ns_sure  */
  YYSYMBOL_ns = 94,                        /* ns  */
  YYSYMBOL_n_sure = 95,                    /* n_sure  */
  YYSYMBOL_stmt = 96,                      /* stmt  */
  YYSYMBOL_simple_stmt = 97,               /* simple_stmt  */
  YYSYMBOL_smlst = 98,                     /* smlst  */
  YYSYMBOL_smlst_sure = 99,                /* smlst_sure  */
  YYSYMBOL_small_stmt = 100,               /* small_stmt  */
  YYSYMBOL_expr_stmt = 101,                /* expr_stmt  */
  YYSYMBOL_yetse = 102,                    /* yetse  */
  YYSYMBOL_yetse_sure = 103,               /* yetse_sure  */
  YYSYMBOL_testlist_star_expr = 104,       /* testlist_star_expr  */
  YYSYMBOL_tse = 105,                      /* tse  */
  YYSYMBOL_tse_sure = 106,                 /* tse_sure  */
  YYSYMBOL_test = 107,                     /* test  */
  YYSYMBOL_or_test = 108,                  /* or_test  */
  YYSYMBOL_oat = 109,                      /* oat  */
  YYSYMBOL_oat_sure = 110,                 /* oat_sure  */
  YYSYMBOL_and_test = 111,                 /* and_test  */
  YYSYMBOL_ant = 112,                      /* ant  */
  YYSYMBOL_ant_sure = 113,                 /* ant_sure  */
  YYSYMBOL_not_test = 114,                 /* not_test  */
  YYSYMBOL_comparison = 115,               /* comparison  */
  YYSYMBOL_coe = 116,                      /* coe  */
  YYSYMBOL_coe_sure = 117,                 /* coe_sure  */
  YYSYMBOL_expr = 118,                     /* expr  */
  YYSYMBOL_xe = 119,                       /* xe  */
  YYSYMBOL_xe_sure = 120,                  /* xe_sure  */
  YYSYMBOL_xor_expr = 121,                 /* xor_expr  */
  YYSYMBOL_ae = 122,                       /* ae  */
  YYSYMBOL_ae_sure = 123,                  /* ae_sure  */
  YYSYMBOL_and_expr = 124,                 /* and_expr  */
  YYSYMBOL_se = 125,                       /* se  */
  YYSYMBOL_se_sure = 126,                  /* se_sure  */
  YYSYMBOL_shift_expr = 127,               /* shift_expr  */
  YYSYMBOL_bae = 128,                      /* bae  */
  YYSYMBOL_bae_sure = 129,                 /* bae_sure  */
  YYSYMBOL_arith_expr = 130,               /* arith_expr  */
  YYSYMBOL_pmterm = 131,                   /* pmterm  */
  YYSYMBOL_pmterm_sure = 132,              /* pmterm_sure  */
  YYSYMBOL_term = 133,                     /* term  */
  YYSYMBOL_sfac = 134,                     /* sfac  */
  YYSYMBOL_sfac_sure = 135,                /* sfac_sure  */
  YYSYMBOL_factor = 136,                   /* factor  */
  YYSYMBOL_power = 137,                    /* power  */
  YYSYMBOL_atom_expr = 138,                /* atom_expr  */
  YYSYMBOL_trailer_sure = 139,             /* trailer_sure  */
  YYSYMBOL_atom = 140,                     /* atom  */
  YYSYMBOL_yield_expr = 141,               /* yield_expr  */
  YYSYMBOL_yield_arg = 142,                /* yield_arg  */
  YYSYMBOL_testlist = 143,                 /* testlist  */
  YYSYMBOL_ct = 144,                       /* ct  */
  YYSYMBOL_ct_sure = 145,                  /* ct_sure  */
  YYSYMBOL_testlist_comp = 146,            /* testlist_comp  */
  YYSYMBOL_comp_for = 147,                 /* comp_for  */
  YYSYMBOL_exprlist = 148,                 /* exprlist  */
  YYSYMBOL_cese = 149,                     /* cese  */
  YYSYMBOL_cese_sure = 150,                /* cese_sure  */
  YYSYMBOL_comp_iter = 151,                /* comp_iter  */
  YYSYMBOL_comp_if = 152,                  /* comp_if  */
  YYSYMBOL_test_nocond = 153,              /* test_nocond  */
  YYSYMBOL_string_sure = 154,              /* string_sure  */
  YYSYMBOL_trailer = 155,                  /* trailer  */
  YYSYMBOL_arglist = 156,                  /* arglist  */
  YYSYMBOL_ca = 157,                       /* ca  */
  YYSYMBOL_ca_sure = 158,                  /* ca_sure  */
  YYSYMBOL_argument = 159,                 /* argument  */
  YYSYMBOL_subscriptlist = 160,            /* subscriptlist  */
  YYSYMBOL_csubs = 161,                    /* csubs  */
  YYSYMBOL_csubs_sure = 162,               /* csubs_sure  */
  YYSYMBOL_subscript = 163,                /* subscript  */
  YYSYMBOL_comp_op = 164,                  /* comp_op  */
  YYSYMBOL_annassign = 165,                /* annassign  */
  YYSYMBOL_augassign = 166,                /* augassign  */
  YYSYMBOL_flow_stmt = 167,                /* flow_stmt  */
  YYSYMBOL_break_stmt = 168,               /* break_stmt  */
  YYSYMBOL_continue_stmt = 169,            /* continue_stmt  */
  YYSYMBOL_return_stmt = 170,              /* return_stmt  */
  YYSYMBOL_raise_stmt = 171,               /* raise_stmt  */
  YYSYMBOL_yield_stmt = 172,               /* yield_stmt  */
  YYSYMBOL_global_stmt = 173,              /* global_stmt  */
  YYSYMBOL_cn = 174,                       /* cn  */
  YYSYMBOL_cn_sure = 175,                  /* cn_sure  */
  YYSYMBOL_assert_stmt = 176,              /* assert_stmt  */
  YYSYMBOL_compound_stmt = 177,            /* compound_stmt  */
  YYSYMBOL_if_stmt = 178,                  /* if_stmt  */
  YYSYMBOL_ets = 179,                      /* ets  */
  YYSYMBOL_ets_sure = 180,                 /* ets_sure  */
  YYSYMBOL_suite = 181,                    /* suite  */
  YYSYMBOL_nns = 182,                      /* nns  */
  YYSYMBOL_nns_sure = 183,                 /* nns_sure  */
  YYSYMBOL_new_stmt = 184,                 /* new_stmt  */
  YYSYMBOL_while_stmt = 185,               /* while_stmt  */
  YYSYMBOL_for_stmt = 186,                 /* for_stmt  */
  YYSYMBOL_try_stmt = 187,                 /* try_stmt  */
  YYSYMBOL_ecs = 188,                      /* ecs  */
  YYSYMBOL_except_clause = 189,            /* except_clause  */
  YYSYMBOL_ecs_sure = 190,                 /* ecs_sure  */
  YYSYMBOL_funcdef = 191,                  /* funcdef  */
  YYSYMBOL_parameters = 192,               /* parameters  */
  YYSYMBOL_typedargslist = 193,            /* typedargslist  */
  YYSYMBOL_ctet = 194,                     /* ctet  */
  YYSYMBOL_ctet_sure = 195,                /* ctet_sure  */
  YYSYMBOL_tfpdef = 196,                   /* tfpdef  */
  YYSYMBOL_classdef = 197,                 /* classdef  */
  YYSYMBOL_dunder_block = 198              /* dunder_block  */
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
typedef yytype_int16 yy_state_t;

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
#define YYFINAL  105
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1051

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  90
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  109
/* YYNRULES -- Number of rules.  */
#define YYNRULES  290
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  416

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   344


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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    81,    81,    84,    85,    88,    89,    92,    93,    96,
      97,   101,   102,   105,   106,   107,   108,   111,   114,   115,
     118,   119,   120,   121,   124,   125,   126,   127,   128,   131,
     132,   135,   136,   139,   140,   141,   142,   145,   148,   149,
     153,   154,   157,   158,   161,   164,   165,   168,   169,   172,
     175,   176,   179,   180,   183,   184,   187,   190,   191,   194,
     195,   198,   201,   202,   205,   206,   209,   212,   213,   216,
     217,   220,   223,   224,   227,   228,   231,   232,   235,   236,
     239,   240,   243,   244,   247,   248,   251,   252,   255,   256,
     257,   258,   261,   262,   265,   266,   267,   268,   271,   272,
     275,   276,   279,   280,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   302,   303,   306,   307,   310,   311,   312,   313,   316,
     319,   320,   323,   324,   325,   326,   327,   330,   331,   334,
     335,   336,   337,   340,   343,   344,   347,   348,   351,   352,
     355,   358,   359,   362,   363,   364,   365,   366,   369,   370,
     371,   372,   375,   378,   379,   382,   383,   384,   387,   388,
     389,   390,   393,   396,   397,   400,   401,   402,   403,   404,
     408,   409,   410,   411,   412,   413,   414,   415,   416,   417,
     418,   421,   422,   425,   426,   427,   428,   429,   430,   431,
     432,   433,   434,   435,   436,   439,   440,   441,   442,   443,
     446,   449,   452,   453,   456,   457,   458,   461,   465,   466,
     469,   472,   473,   476,   477,   480,   481,   482,   483,   484,
     485,   486,   489,   490,   491,   492,   495,   498,   499,   502,
     503,   506,   507,   510,   511,   514,   515,   516,   517,   518,
     519,   520,   523,   524,   528,   529,   532,   533,   534,   535,
     536,   540,   543,   544,   545,   548,   549,   552,   553,   554,
     555,   558,   559,   562,   563,   564,   565,   566,   567,   568,
     569,   572,   573,   576,   577,   579,   580,   583,   584,   585,
     588
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
  "\"end of file\"", "error", "\"invalid token\"", "NEWLINE", "INDENT",
  "DEDENT", "ENDMARKER", "DUNDER", "DATATYPE", "IS", "IF", "ELSE", "ELIF",
  "WHILE", "FOR", "TRY", "RETURN", "YIELD", "IN", "FINALLY", "GLOBAL",
  "EXCEPT", "AS", "DEF", "CLASS", "ASSERT", "FROM", "CONTINUE", "BREAK",
  "RAISE", "NONE", "TRUE", "FALSE", "AND", "NOT", "OR", "DEL", "INT",
  "FLOAT", "STR", "BOOL", "IDENTIFIER", "EEQ", "GEQ", "LEQ", "NEQ", "LLT",
  "GGT", "PEQ", "MIEQ", "MUEQ", "DEQ", "DDEQ", "MOEQ", "MUMUEQ", "AEQ",
  "ALEQ", "POEQ", "LLEQ", "GGEQ", "STRING", "NUMBER", "SSTAR", "DDOT",
  "DMOND", "ARROW", "SSLASH", "COLON", "SEMICOLON", "PLUS", "MINUS",
  "DIVI", "EQUAL", "COMMA", "ALTE", "AAND", "POWER", "MULTI", "MOD",
  "NOPE", "CIROPEN", "CIRCLOSE", "SQOPEN", "SQCLOSE", "CUOPEN", "CUCLOSE",
  "DOT", "LT", "GT", "ADUNDER", "$accept", "starting", "file_input",
  "ns_sure", "ns", "n_sure", "stmt", "simple_stmt", "smlst", "smlst_sure",
  "small_stmt", "expr_stmt", "yetse", "yetse_sure", "testlist_star_expr",
  "tse", "tse_sure", "test", "or_test", "oat", "oat_sure", "and_test",
  "ant", "ant_sure", "not_test", "comparison", "coe", "coe_sure", "expr",
  "xe", "xe_sure", "xor_expr", "ae", "ae_sure", "and_expr", "se",
  "se_sure", "shift_expr", "bae", "bae_sure", "arith_expr", "pmterm",
  "pmterm_sure", "term", "sfac", "sfac_sure", "factor", "power",
  "atom_expr", "trailer_sure", "atom", "yield_expr", "yield_arg",
  "testlist", "ct", "ct_sure", "testlist_comp", "comp_for", "exprlist",
  "cese", "cese_sure", "comp_iter", "comp_if", "test_nocond",
  "string_sure", "trailer", "arglist", "ca", "ca_sure", "argument",
  "subscriptlist", "csubs", "csubs_sure", "subscript", "comp_op",
  "annassign", "augassign", "flow_stmt", "break_stmt", "continue_stmt",
  "return_stmt", "raise_stmt", "yield_stmt", "global_stmt", "cn",
  "cn_sure", "assert_stmt", "compound_stmt", "if_stmt", "ets", "ets_sure",
  "suite", "nns", "nns_sure", "new_stmt", "while_stmt", "for_stmt",
  "try_stmt", "ecs", "except_clause", "ecs_sure", "funcdef", "parameters",
  "typedargslist", "ctet", "ctet_sure", "tfpdef", "classdef",
  "dunder_block", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-318)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     331,  -318,  -318,   109,   967,   222,   -33,   967,   797,    -4,
      18,     6,   967,  -318,  -318,   967,  -318,  -318,  -318,   967,
    -318,  -318,  -318,  -318,  -318,   -18,  -318,  -318,   222,   222,
     222,   708,   831,   -16,    90,  -318,   406,  -318,  -318,  -318,
      17,  -318,   268,    31,    70,    74,    66,  -318,    80,    43,
      55,    60,    27,    64,    35,  -318,    83,    50,  -318,  -318,
    -318,  -318,  -318,  -318,  -318,  -318,  -318,  -318,  -318,  -318,
    -318,  -318,  -318,  -318,  -318,  -318,   100,    84,    97,    93,
     153,    23,   103,  -318,   967,  -318,  -318,   111,   102,   102,
     -36,   119,   147,  -318,  -318,  -318,  -318,  -318,  -318,     4,
     113,   115,  -318,   117,  -318,  -318,  -318,  -318,  -318,   613,
    -318,    19,  -318,  -318,  -318,  -318,  -318,  -318,  -318,  -318,
    -318,  -318,  -318,  -318,   967,   742,  -318,   132,  -318,   742,
     967,  -318,   133,   967,   967,  -318,    74,   967,  -318,    66,
     173,  -318,   191,  -318,  -318,  -318,  -318,  -318,  -318,  -318,
    -318,    80,   222,   222,  -318,    43,   222,  -318,    55,   222,
    -318,    60,   222,   222,  -318,    27,   222,   222,  -318,    64,
     222,   222,   222,   222,  -318,    35,   222,   865,   899,    26,
      50,  -318,   121,    23,    23,   222,  -318,   139,   967,  -318,
     116,  -318,    37,   967,  -318,   140,  -318,   174,  -318,   111,
      -9,    29,    30,    23,   933,   967,   967,   222,   967,   141,
    -318,  -318,  -318,  -318,  -318,  -318,  -318,   674,  -318,   144,
    -318,  -318,  -318,  -318,  -318,  -318,   967,  -318,   206,  -318,
    -318,  -318,  -318,  -318,  -318,  -318,  -318,  -318,  -318,  -318,
    -318,  -318,  -318,  -318,  -318,  -318,  -318,  -318,  -318,  -318,
    -318,  -318,  -318,  -318,  -318,  -318,     7,   137,   146,   967,
     155,   143,   154,  -318,  -318,  -318,   157,   126,   209,  -318,
     222,  -318,   161,  -318,   552,   163,   967,  -318,   164,    89,
    -318,   967,  -318,  -318,  -318,   165,  -318,   152,    87,   967,
      23,   967,    23,  -318,   167,   158,  -318,  -318,   217,   967,
    -318,   967,   967,   967,  -318,  -318,   967,  -318,   168,  -318,
     967,  -318,   899,  -318,   169,    23,   171,   967,  -318,   151,
     178,    23,  -318,  -318,  -318,  -318,   479,  -318,  -318,  -318,
    -318,  -318,  -318,    23,   218,    23,   180,   181,  -318,   967,
    -318,   967,   210,  -318,   182,   190,  -318,   197,  -318,    23,
     198,   967,  -318,  -318,  -318,  -318,   967,  -318,  -318,  -318,
     899,  -318,  -318,    23,   199,   200,  -318,    23,   247,  -318,
    -318,  -318,   228,  -318,    23,    23,  -318,   201,   205,   210,
    -318,    23,    23,  -318,    23,    56,  -318,    23,    23,  -318,
     212,  -318,   253,  -318,   210,   207,   967,  -318,  -318,  -318,
     967,  -318,  -318,  -318,  -318,  -318,    23,   214,   210,  -318,
    -318,    56,  -318,    23,  -318,  -318
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,     7,     4,     0,     0,     0,     0,   212,   122,     0,
       0,     0,     0,   211,   210,   216,   117,   118,   119,     0,
     110,   111,   112,   113,   120,   151,   114,   116,     0,     0,
       0,     0,     0,     0,     0,     2,     0,     5,     8,    11,
       0,    20,    28,    34,    41,    43,    48,    53,    55,    60,
      65,    70,    75,    81,    87,    97,    99,   101,   217,   115,
      21,   205,   206,   207,   208,   209,    22,    23,    12,   225,
     226,   227,   228,   229,   230,   231,     0,     0,     0,   142,
       0,     0,   128,   213,     0,   121,   124,   219,     0,     0,
       0,   223,   215,    52,   152,    94,    95,    96,   106,   136,
       0,     0,   108,     0,   109,     1,     3,     6,    15,     0,
      18,     0,   193,   194,   195,   196,   204,   197,   203,   198,
     199,   200,   201,   202,     0,     0,    31,    27,    24,     0,
      36,    38,    33,     0,     0,    45,    42,     0,    50,    47,
     189,   187,     0,   182,   183,   184,   186,   185,   180,   181,
      57,    54,     0,     0,    62,    59,     0,    67,    64,     0,
      72,    69,     0,     0,    78,    74,     0,     0,    84,    80,
       0,     0,     0,     0,    92,    86,     0,     0,     0,     0,
     100,   102,     0,     0,     0,   140,   144,   141,     0,     9,
       0,   239,     0,   127,   130,   126,   123,     0,   221,   218,
       0,     0,     0,     0,     0,     0,     0,     0,   134,   135,
     132,   104,   105,   107,    16,    17,    13,     0,    19,   191,
      30,    29,    32,    25,    26,    37,    35,    39,     0,    44,
      46,    49,    51,   190,   188,    58,    56,    61,    63,    66,
      68,    71,    73,    76,    77,    79,    82,    83,    85,    91,
      89,    88,    90,    93,    98,   154,   165,     0,   159,   179,
     175,     0,   169,   157,   156,   103,     0,   235,   252,   143,
     139,   145,     0,    10,     0,     0,   263,   266,     0,   260,
     129,   125,   131,   220,   222,   285,   272,     0,   280,     0,
       0,     0,     0,   288,     0,     0,   224,   214,     0,   133,
      14,     0,     0,     0,   166,   153,   161,   163,   158,   178,
     177,   155,   171,   173,   168,     0,     0,     0,   237,   234,
       0,     0,   241,   245,   246,   243,     0,   242,   247,   248,
     249,   250,   251,     0,   264,     0,     0,     0,   265,     0,
     271,     0,   276,   283,   279,     0,   270,     0,   268,     0,
       0,     0,   192,    40,   167,   162,   160,   164,   176,   172,
     170,   174,   290,     0,     0,     0,   238,     0,   254,   240,
     244,   257,     0,   261,     0,     0,   286,   278,   282,   275,
     284,     0,     0,   289,     0,   138,   233,     0,     0,   253,
       0,   262,   258,   259,   274,   277,     0,   269,   267,   287,
       0,   146,   137,   147,   236,   232,     0,     0,   273,   281,
     150,   149,   255,     0,   148,   256
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -318,  -318,  -318,  -318,   248,  -318,  -318,     2,   176,  -318,
     -99,  -318,   162,  -318,   170,   179,  -318,    -3,  -130,   172,
    -318,   156,   166,  -318,    -8,  -318,   142,  -318,     1,   160,
    -318,   159,   136,  -318,   175,   149,  -318,   138,   148,  -318,
      36,   183,  -318,    14,   189,  -318,   -15,  -318,  -318,  -318,
    -318,   -14,  -318,    -1,  -160,   230,   298,   -91,   125,   186,
    -318,   -78,  -318,  -318,   314,   187,   145,    34,  -318,  -265,
    -318,    52,  -318,   196,  -318,  -318,  -318,  -318,  -318,  -318,
    -318,  -318,  -318,  -318,   177,  -318,  -318,  -318,  -258,    24,
    -318,  -138,    49,  -318,  -318,  -255,  -251,  -250,    71,  -318,
    -318,  -244,   288,  -318,  -317,     3,   184,  -318,  -238
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    34,    35,    36,    37,   190,    38,   191,   110,   111,
      40,    41,   126,   127,    42,   131,   132,    43,    44,   135,
     136,    45,   138,   139,    46,    47,   150,   151,    48,   154,
     155,    49,   157,   158,    50,   160,   161,    51,   164,   165,
      52,   168,   169,    53,   174,   175,    54,    55,    56,   180,
      57,    58,    85,    83,   194,   195,   101,   401,    80,   186,
     187,   402,   403,   411,    59,   181,   257,   307,   308,   258,
     261,   313,   314,   359,   152,   128,   129,    60,    61,    62,
      63,    64,    65,    66,   198,   199,    67,    68,    69,   318,
     319,   192,   325,   326,   327,    70,    71,    72,   277,   278,
     279,    73,   201,   287,   343,   344,   378,    74,    75
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      77,    78,    39,   228,    82,    82,    79,    86,   210,    91,
     215,    93,    92,    95,    96,    97,   324,   100,   207,   328,
     108,   207,   216,   329,   330,    88,   189,   380,    99,    99,
     331,   203,   285,   263,    81,   282,   332,    87,    39,     7,
       8,   355,    25,     9,   204,   267,   268,    90,    12,   282,
      13,    14,    15,    16,    17,    18,   275,    19,   276,    89,
      20,    21,    22,    23,    24,   293,   400,   264,   324,   104,
     207,   328,   286,   162,   163,   329,   330,   208,   380,   303,
     133,   196,   331,    25,    26,   109,    27,   217,   332,   140,
     105,   355,    28,    29,   289,   291,   290,   292,   141,   137,
     336,   170,    30,    31,   130,    32,   171,    33,   337,   134,
     276,   221,   172,   173,   142,   223,    76,   153,   215,   273,
     274,   219,   143,   144,   145,   146,    82,   225,   224,   231,
     177,   156,   178,   166,   167,   159,   179,   316,   317,    16,
      17,    18,   182,    19,   147,   176,    20,    21,    22,    23,
      24,   183,   346,   236,   348,   249,   250,   251,   252,   341,
     342,   254,   365,   317,   184,   304,   185,   148,   149,    25,
      26,   188,    27,   206,   256,   260,   193,   362,    28,    29,
     246,   247,   200,   368,   197,    82,   269,   272,    30,    31,
     280,    32,   205,    33,   211,   371,   212,   373,   243,   244,
     213,   256,   296,   297,   125,   280,   226,   233,    79,   234,
     266,   383,   270,   281,   299,   283,   301,   302,   305,   306,
     320,   385,   310,   225,   315,   386,   311,   312,   321,   389,
     333,   335,   339,   340,   349,   351,   392,   393,   363,   350,
     372,   356,   360,   397,   398,   367,   399,   374,   375,   404,
     405,   285,    16,    17,    18,   379,   309,   381,   390,    20,
      21,    22,    23,    24,   382,   384,   387,   388,   412,   391,
     410,   269,   407,   334,   394,   415,   323,   396,   280,   406,
     408,   413,    25,    26,   107,    27,   345,   218,   347,   222,
     229,    28,    29,   235,   240,   220,   280,   241,   352,   353,
     354,    30,    31,   256,    32,   232,    33,   358,   230,   260,
     242,   227,   237,   245,   364,   238,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   323,   209,
     103,   239,   298,   414,     1,   124,   376,     2,   377,    94,
     125,     3,   357,   366,     4,     5,     6,     7,     8,   295,
     338,     9,   248,   256,    10,    11,    12,   260,    13,    14,
      15,    16,    17,    18,   253,    19,   361,   265,    20,    21,
      22,    23,    24,   271,   262,   370,   284,   202,     0,     0,
     395,     0,     0,     0,   288,     0,     0,     0,     0,     0,
       0,    25,    26,   409,    27,     0,     0,     0,     0,     0,
      28,    29,     0,     0,     0,     0,     0,     0,     0,     1,
      30,    31,   106,    32,     0,    33,     3,     0,     0,     4,
       5,     6,     7,     8,     0,     0,     9,     0,     0,    10,
      11,    12,     0,    13,    14,    15,    16,    17,    18,     0,
      19,     0,     0,    20,    21,    22,    23,    24,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    25,    26,     0,    27,
       0,     0,     0,     0,     0,    28,    29,     0,     0,     0,
       0,     0,   322,     0,   369,    30,    31,     0,    32,     3,
      33,     0,     4,     5,     6,     7,     8,     0,     0,     9,
       0,     0,    10,     0,    12,     0,    13,    14,    15,    16,
      17,    18,     0,    19,     0,     0,    20,    21,    22,    23,
      24,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    25,
      26,     0,    27,     0,     0,     0,     0,     0,    28,    29,
       0,     0,     0,     0,     0,   322,     0,     0,    30,    31,
       0,    32,     3,    33,     0,     4,     5,     6,     7,     8,
       0,     0,     9,     0,     0,    10,     0,    12,     0,    13,
      14,    15,    16,    17,    18,     0,    19,     0,     0,    20,
      21,    22,    23,    24,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    25,    26,     0,    27,   214,     0,     0,     0,
       0,    28,    29,     0,     0,     0,     0,     0,     0,     7,
       8,    30,    31,     9,    32,     0,    33,     0,    12,     0,
      13,    14,    15,    16,    17,    18,     0,    19,     0,     0,
      20,    21,    22,    23,    24,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    25,    26,     0,    27,   300,     0,     0,
       0,     0,    28,    29,     0,     0,     0,     0,     0,     0,
       7,     8,    30,    31,     9,    32,     0,    33,     0,    12,
       0,    13,    14,    15,    16,    17,    18,     0,    19,     0,
       0,    20,    21,    22,    23,    24,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     8,     0,     0,     0,     0,
       0,     0,     0,     0,    25,    26,     0,    27,    16,    17,
      18,     0,    19,    28,    29,    20,    21,    22,    23,    24,
       0,     0,     0,    30,    31,     0,    32,     0,    33,     8,
       0,     0,     0,     0,     0,     0,     0,     0,    25,    26,
       0,    27,    16,    17,    18,     0,    19,    28,    29,    20,
      21,    22,    23,    24,     0,     0,     0,    30,    31,    98,
      32,     0,    33,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    25,    26,     0,    27,     0,     0,     0,     0,
       0,    28,    29,     0,     0,     0,     0,     0,     0,     0,
       0,    30,    31,    84,    32,     0,    33,    16,    17,    18,
       0,    19,     0,     0,    20,    21,    22,    23,    24,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    25,    26,     0,
      27,    16,    17,    18,     0,    19,    28,    29,    20,    21,
      22,    23,    24,     0,     0,     0,    30,    31,     0,    32,
       0,    33,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    25,    26,     0,    27,    16,    17,    18,     0,    19,
      28,    29,    20,    21,    22,    23,    24,     0,     0,     0,
      30,    31,     0,    32,   102,    33,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    25,    26,     0,    27,    16,
      17,    18,     0,    19,    28,    29,    20,    21,    22,    23,
      24,     0,     0,     0,    30,    31,   255,    32,     0,    33,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    25,
      26,     0,    27,    16,    17,    18,   259,    19,    28,    29,
      20,    21,    22,    23,    24,     0,     0,     0,    30,    31,
       0,    32,     0,    33,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    25,    26,     0,    27,    16,    17,    18,
       0,    19,    28,    29,    20,    21,    22,    23,    24,     0,
       0,     0,    30,    31,   294,    32,     0,    33,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    25,    26,     0,
      27,     0,     0,     0,     0,     0,    28,    29,     0,     0,
       0,     0,     0,     0,     0,     0,    30,    31,     0,    32,
       0,    33
};

static const yytype_int16 yycheck[] =
{
       3,     4,     0,   133,     7,     8,     5,     8,    99,    12,
     109,    19,    15,    28,    29,    30,   274,    31,    14,   274,
       3,    14,     3,   274,   274,     7,     3,   344,    31,    32,
     274,    67,    41,     7,    67,   195,   274,    41,    36,    16,
      17,   306,    60,    20,    80,   183,   184,    41,    25,   209,
      27,    28,    29,    30,    31,    32,    19,    34,    21,    41,
      37,    38,    39,    40,    41,   203,    10,    41,   326,    85,
      14,   326,    81,    46,    47,   326,   326,    73,   395,    72,
      10,    84,   326,    60,    61,    68,    63,    68,   326,     9,
       0,   356,    69,    70,    65,    65,    67,    67,    18,    33,
      11,    66,    79,    80,    73,    82,    71,    84,    19,    35,
      21,   125,    77,    78,    34,   129,     7,    74,   217,     3,
       4,   124,    42,    43,    44,    45,   129,   130,   129,   137,
      80,    76,    82,    69,    70,    75,    86,    11,    12,    30,
      31,    32,    42,    34,    64,    62,    37,    38,    39,    40,
      41,    67,   290,   152,   292,   170,   171,   172,   173,    72,
      73,   176,    11,    12,    67,   256,    73,    87,    88,    60,
      61,    18,    63,    26,   177,   178,    73,   315,    69,    70,
     166,   167,    80,   321,    73,   188,   185,   188,    79,    80,
     193,    82,    73,    84,    81,   333,    81,   335,   162,   163,
      83,   204,   205,   206,    72,   208,    73,    34,   207,    18,
      89,   349,    73,    73,    73,    41,    72,    11,    81,    73,
      11,   351,    67,   226,    67,   363,    83,    73,    67,   367,
      67,    67,    67,    81,    67,    18,   374,   375,    67,    81,
      22,    73,    73,   381,   382,    67,   384,    67,    67,   387,
     388,    41,    30,    31,    32,    73,   259,    67,    11,    37,
      38,    39,    40,    41,    67,    67,    67,    67,   406,    41,
     400,   270,    19,   276,    73,   413,   274,    72,   281,    67,
      73,    67,    60,    61,    36,    63,   289,   111,   291,   127,
     134,    69,    70,   151,   158,   125,   299,   159,   301,   302,
     303,    79,    80,   306,    82,   139,    84,   310,   136,   312,
     161,   132,   153,   165,   317,   155,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,   326,    99,
      32,   156,   207,   411,     3,    67,   339,     6,   341,    25,
      72,    10,   308,   319,    13,    14,    15,    16,    17,   204,
     279,    20,   169,   356,    23,    24,    25,   360,    27,    28,
      29,    30,    31,    32,   175,    34,   314,   180,    37,    38,
      39,    40,    41,   187,   178,   326,   199,    89,    -1,    -1,
     377,    -1,    -1,    -1,   200,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    61,   396,    63,    -1,    -1,    -1,    -1,    -1,
      69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
      79,    80,     6,    82,    -1,    84,    10,    -1,    -1,    13,
      14,    15,    16,    17,    -1,    -1,    20,    -1,    -1,    23,
      24,    25,    -1,    27,    28,    29,    30,    31,    32,    -1,
      34,    -1,    -1,    37,    38,    39,    40,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    -1,    63,
      -1,    -1,    -1,    -1,    -1,    69,    70,    -1,    -1,    -1,
      -1,    -1,     3,    -1,     5,    79,    80,    -1,    82,    10,
      84,    -1,    13,    14,    15,    16,    17,    -1,    -1,    20,
      -1,    -1,    23,    -1,    25,    -1,    27,    28,    29,    30,
      31,    32,    -1,    34,    -1,    -1,    37,    38,    39,    40,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,
      61,    -1,    63,    -1,    -1,    -1,    -1,    -1,    69,    70,
      -1,    -1,    -1,    -1,    -1,     3,    -1,    -1,    79,    80,
      -1,    82,    10,    84,    -1,    13,    14,    15,    16,    17,
      -1,    -1,    20,    -1,    -1,    23,    -1,    25,    -1,    27,
      28,    29,    30,    31,    32,    -1,    34,    -1,    -1,    37,
      38,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    61,    -1,    63,     3,    -1,    -1,    -1,
      -1,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    16,
      17,    79,    80,    20,    82,    -1,    84,    -1,    25,    -1,
      27,    28,    29,    30,    31,    32,    -1,    34,    -1,    -1,
      37,    38,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    60,    61,    -1,    63,     3,    -1,    -1,
      -1,    -1,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      16,    17,    79,    80,    20,    82,    -1,    84,    -1,    25,
      -1,    27,    28,    29,    30,    31,    32,    -1,    34,    -1,
      -1,    37,    38,    39,    40,    41,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    17,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    60,    61,    -1,    63,    30,    31,
      32,    -1,    34,    69,    70,    37,    38,    39,    40,    41,
      -1,    -1,    -1,    79,    80,    -1,    82,    -1,    84,    17,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,
      -1,    63,    30,    31,    32,    -1,    34,    69,    70,    37,
      38,    39,    40,    41,    -1,    -1,    -1,    79,    80,    81,
      82,    -1,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    61,    -1,    63,    -1,    -1,    -1,    -1,
      -1,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    79,    80,    26,    82,    -1,    84,    30,    31,    32,
      -1,    34,    -1,    -1,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    -1,
      63,    30,    31,    32,    -1,    34,    69,    70,    37,    38,
      39,    40,    41,    -1,    -1,    -1,    79,    80,    -1,    82,
      -1,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    61,    -1,    63,    30,    31,    32,    -1,    34,
      69,    70,    37,    38,    39,    40,    41,    -1,    -1,    -1,
      79,    80,    -1,    82,    83,    84,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    61,    -1,    63,    30,
      31,    32,    -1,    34,    69,    70,    37,    38,    39,    40,
      41,    -1,    -1,    -1,    79,    80,    81,    82,    -1,    84,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,
      61,    -1,    63,    30,    31,    32,    67,    34,    69,    70,
      37,    38,    39,    40,    41,    -1,    -1,    -1,    79,    80,
      -1,    82,    -1,    84,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    60,    61,    -1,    63,    30,    31,    32,
      -1,    34,    69,    70,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    79,    80,    81,    82,    -1,    84,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    -1,
      63,    -1,    -1,    -1,    -1,    -1,    69,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    79,    80,    -1,    82,
      -1,    84
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     6,    10,    13,    14,    15,    16,    17,    20,
      23,    24,    25,    27,    28,    29,    30,    31,    32,    34,
      37,    38,    39,    40,    41,    60,    61,    63,    69,    70,
      79,    80,    82,    84,    91,    92,    93,    94,    96,    97,
     100,   101,   104,   107,   108,   111,   114,   115,   118,   121,
     124,   127,   130,   133,   136,   137,   138,   140,   141,   154,
     167,   168,   169,   170,   171,   172,   173,   176,   177,   178,
     185,   186,   187,   191,   197,   198,     7,   107,   107,   118,
     148,    67,   107,   143,    26,   142,   143,    41,     7,    41,
      41,   107,   107,   114,   154,   136,   136,   136,    81,   107,
     141,   146,    83,   146,    85,     0,     6,    94,     3,    68,
      98,    99,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    67,    72,   102,   103,   165,   166,
      73,   105,   106,    10,    35,   109,   110,    33,   112,   113,
       9,    18,    34,    42,    43,    44,    45,    64,    87,    88,
     116,   117,   164,    74,   119,   120,    76,   122,   123,    75,
     125,   126,    46,    47,   128,   129,    69,    70,   131,   132,
      66,    71,    77,    78,   134,   135,    62,    80,    82,    86,
     139,   155,    42,    67,    67,    73,   149,   150,    18,     3,
      95,    97,   181,    73,   144,   145,   107,    73,   174,   175,
      80,   192,   192,    67,    80,    73,    26,    14,    73,   145,
     147,    81,    81,    83,     3,   100,     3,    68,    98,   107,
     104,   141,   102,   141,   143,   107,    73,   105,   108,   111,
     109,   114,   112,    34,    18,   116,   118,   121,   119,   124,
     122,   127,   125,   130,   130,   128,   133,   133,   131,   136,
     136,   136,   136,   134,   136,    81,   107,   156,   159,    67,
     107,   160,   163,     7,    41,   155,    89,   181,   181,   118,
      73,   149,   143,     3,     4,    19,    21,   188,   189,   190,
     107,    73,   144,    41,   174,    41,    81,   193,   196,    65,
      67,    65,    67,   181,    81,   156,   107,   107,   148,    73,
       3,    72,    11,    72,   147,    81,    73,   157,   158,   107,
      67,    83,    73,   161,   162,    67,    11,    12,   179,   180,
      11,    67,     3,    97,   178,   182,   183,   184,   185,   186,
     187,   191,   198,    67,   107,    67,    11,    19,   188,    67,
      81,    72,    73,   194,   195,   107,   181,   107,   181,    67,
      81,    18,   107,   107,   107,   159,    73,   157,   107,   163,
      73,   161,   181,    67,   107,    11,   179,    67,   181,     5,
     182,   181,    22,   181,    67,    67,   107,   107,   196,    73,
     194,    67,    67,   181,    67,   108,   181,    67,    67,   181,
      11,    41,   181,   181,    73,   195,    72,   181,   181,   181,
      10,   147,   151,   152,   181,   181,    67,    19,    73,   107,
     108,   153,   181,    67,   151,   181
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    90,    91,    92,    92,    93,    93,    94,    94,    95,
      95,    96,    96,    97,    97,    97,    97,    98,    99,    99,
     100,   100,   100,   100,   101,   101,   101,   101,   101,   102,
     102,   103,   103,   104,   104,   104,   104,   105,   106,   106,
     107,   107,   108,   108,   109,   110,   110,   111,   111,   112,
     113,   113,   114,   114,   115,   115,   116,   117,   117,   118,
     118,   119,   120,   120,   121,   121,   122,   123,   123,   124,
     124,   125,   126,   126,   127,   127,   128,   128,   129,   129,
     130,   130,   131,   131,   132,   132,   133,   133,   134,   134,
     134,   134,   135,   135,   136,   136,   136,   136,   137,   137,
     138,   138,   139,   139,   140,   140,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   140,
     140,   141,   141,   142,   142,   143,   143,   143,   143,   144,
     145,   145,   146,   146,   146,   146,   146,   147,   147,   148,
     148,   148,   148,   149,   150,   150,   151,   151,   152,   152,
     153,   154,   154,   155,   155,   155,   155,   155,   156,   156,
     156,   156,   157,   158,   158,   159,   159,   159,   160,   160,
     160,   160,   161,   162,   162,   163,   163,   163,   163,   163,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   165,   165,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   167,   167,   167,   167,   167,
     168,   169,   170,   170,   171,   171,   171,   172,   173,   173,
     174,   175,   175,   176,   176,   177,   177,   177,   177,   177,
     177,   177,   178,   178,   178,   178,   179,   180,   180,   181,
     181,   182,   182,   183,   183,   184,   184,   184,   184,   184,
     184,   184,   185,   185,   186,   186,   187,   187,   187,   187,
     187,   188,   189,   189,   189,   190,   190,   191,   191,   191,
     191,   192,   192,   193,   193,   193,   193,   193,   193,   193,
     193,   194,   194,   195,   195,   196,   196,   197,   197,   197,
     198
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     2,     1,     1,     1,
       2,     1,     1,     3,     4,     2,     3,     2,     1,     2,
       1,     1,     1,     1,     2,     3,     3,     2,     1,     2,
       2,     1,     2,     2,     1,     3,     2,     2,     1,     2,
       5,     1,     2,     1,     2,     1,     2,     2,     1,     2,
       1,     2,     2,     1,     2,     1,     2,     1,     2,     2,
       1,     2,     1,     2,     2,     1,     2,     1,     2,     2,
       1,     2,     1,     2,     2,     1,     2,     2,     1,     2,
       2,     1,     2,     2,     1,     2,     2,     1,     2,     2,
       2,     2,     1,     2,     2,     2,     2,     1,     3,     1,
       2,     1,     1,     2,     3,     3,     2,     3,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     2,     1,     3,     2,     2,     1,     2,
       1,     2,     2,     3,     2,     2,     1,     5,     4,     3,
       2,     2,     1,     2,     1,     2,     1,     1,     3,     2,
       1,     1,     2,     3,     2,     3,     2,     2,     2,     1,
       3,     2,     2,     1,     2,     1,     2,     3,     2,     1,
       3,     2,     2,     1,     2,     1,     3,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       2,     2,     4,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     4,     2,     1,     1,     3,     2,
       2,     1,     2,     2,     4,     1,     1,     1,     1,     1,
       1,     1,     8,     7,     5,     4,     4,     1,     2,     1,
       4,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     4,     7,     6,     9,    10,     6,     7,     7,
       4,     3,     4,     1,     2,     2,     1,     7,     5,     7,
       5,     3,     2,     5,     4,     3,     2,     4,     3,     2,
       1,     4,     2,     1,     2,     1,     3,     7,     4,     6,
       6
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
  case 2: /* starting: file_input  */
#line 81 "parser.y"
                     {(yyval.val)=addnode("starting");addedge((yyval.val), (yyvsp[0].val));return 0;}
#line 1783 "parser.tab.c"
    break;

  case 3: /* file_input: ns_sure ENDMARKER  */
#line 84 "parser.y"
                              {(yyval.val)=addnode("file_input");addedge((yyval.val), (yyvsp[-1].val));}
#line 1789 "parser.tab.c"
    break;

  case 4: /* file_input: ENDMARKER  */
#line 85 "parser.y"
                      {(yyval.val)=addnode("file_input");(yyvsp[0].val)=addnode(string("ENDMARKER") );addedge((yyval.val), (yyvsp[0].val));}
#line 1795 "parser.tab.c"
    break;

  case 5: /* ns_sure: ns  */
#line 88 "parser.y"
           {(yyval.val)= (yyvsp[0].val);}
#line 1801 "parser.tab.c"
    break;

  case 6: /* ns_sure: ns_sure ns  */
#line 89 "parser.y"
                   {(yyval.val)=addnode("ns_sure");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 1807 "parser.tab.c"
    break;

  case 7: /* ns: NEWLINE  */
#line 92 "parser.y"
            {(yyval.val)=addnode("NEWLINE");(yyvsp[0].val)=addnode(string("newline") );addedge((yyval.val), (yyvsp[0].val));}
#line 1813 "parser.tab.c"
    break;

  case 8: /* ns: stmt  */
#line 93 "parser.y"
          {(yyval.val)= (yyvsp[0].val);}
#line 1819 "parser.tab.c"
    break;

  case 9: /* n_sure: NEWLINE  */
#line 96 "parser.y"
                {(yyval.val)=addnode("NEWLINE");(yyvsp[0].val)=addnode(string("newline") );addedge((yyval.val), (yyvsp[0].val));}
#line 1825 "parser.tab.c"
    break;

  case 10: /* n_sure: n_sure NEWLINE  */
#line 97 "parser.y"
                       {(yyval.val)=addnode("n_sure");addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("NEWLINE"));addedge((yyval.val), (yyvsp[0].val));}
#line 1831 "parser.tab.c"
    break;

  case 11: /* stmt: simple_stmt  */
#line 101 "parser.y"
                  {(yyval.val)= (yyvsp[0].val);}
#line 1837 "parser.tab.c"
    break;

  case 12: /* stmt: compound_stmt  */
#line 102 "parser.y"
                     {(yyval.val)= (yyvsp[0].val);}
#line 1843 "parser.tab.c"
    break;

  case 13: /* simple_stmt: small_stmt smlst_sure NEWLINE  */
#line 105 "parser.y"
                                           {(yyval.val)=addnode("simple_stmt");addedge((yyval.val), (yyvsp[-2].val));addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("NEWLINE") );addedge((yyval.val), (yyvsp[0].val));}
#line 1849 "parser.tab.c"
    break;

  case 14: /* simple_stmt: small_stmt smlst_sure SEMICOLON NEWLINE  */
#line 106 "parser.y"
                                                     {(yyval.val)=addnode("simple_stmt");addedge((yyval.val), (yyvsp[-3].val));addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("SEMICOLON") );addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("NEWLINE") );addedge((yyval.val), (yyvsp[0].val));}
#line 1855 "parser.tab.c"
    break;

  case 15: /* simple_stmt: small_stmt NEWLINE  */
#line 107 "parser.y"
                                {(yyval.val)=addnode("simple_stmt");addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("NEWLINE"));addedge((yyval.val), (yyvsp[0].val));}
#line 1861 "parser.tab.c"
    break;

  case 16: /* simple_stmt: small_stmt SEMICOLON NEWLINE  */
#line 108 "parser.y"
                                          {(yyval.val)=addnode("simple_stmt");addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("SEMICOLON"));addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("NEWLINE") );addedge((yyval.val), (yyvsp[0].val));}
#line 1867 "parser.tab.c"
    break;

  case 17: /* smlst: SEMICOLON small_stmt  */
#line 111 "parser.y"
                            {(yyval.val)=addnode("smlst");(yyvsp[-1].val)=addnode(string("SEMICOLON") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 1873 "parser.tab.c"
    break;

  case 18: /* smlst_sure: smlst  */
#line 114 "parser.y"
                  {(yyval.val)=(yyvsp[0].val);}
#line 1879 "parser.tab.c"
    break;

  case 19: /* smlst_sure: smlst_sure smlst  */
#line 115 "parser.y"
                             {(yyval.val)=addnode("smlst_sure");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 1885 "parser.tab.c"
    break;

  case 20: /* small_stmt: expr_stmt  */
#line 118 "parser.y"
                      {(yyval.val)=(yyvsp[0].val);}
#line 1891 "parser.tab.c"
    break;

  case 21: /* small_stmt: flow_stmt  */
#line 119 "parser.y"
                      {(yyval.val)=(yyvsp[0].val);}
#line 1897 "parser.tab.c"
    break;

  case 22: /* small_stmt: global_stmt  */
#line 120 "parser.y"
                        {(yyval.val)=(yyvsp[0].val);}
#line 1903 "parser.tab.c"
    break;

  case 23: /* small_stmt: assert_stmt  */
#line 121 "parser.y"
                        {(yyval.val)=(yyvsp[0].val);}
#line 1909 "parser.tab.c"
    break;

  case 24: /* expr_stmt: testlist_star_expr annassign  */
#line 124 "parser.y"
                                        {(yyval.val)=addnode("expr_stmt");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 1915 "parser.tab.c"
    break;

  case 25: /* expr_stmt: testlist_star_expr augassign yield_expr  */
#line 125 "parser.y"
                                                   {(yyval.val)=addnode("expr_stmt");addedge((yyval.val), (yyvsp[-2].val));addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 1921 "parser.tab.c"
    break;

  case 26: /* expr_stmt: testlist_star_expr augassign testlist  */
#line 126 "parser.y"
                                                 {(yyval.val)=addnode("expr_stmt");addedge((yyval.val), (yyvsp[-2].val));addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 1927 "parser.tab.c"
    break;

  case 27: /* expr_stmt: testlist_star_expr yetse_sure  */
#line 127 "parser.y"
                                         {(yyval.val)=addnode("expr_stmt");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 1933 "parser.tab.c"
    break;

  case 28: /* expr_stmt: testlist_star_expr  */
#line 128 "parser.y"
                              {(yyval.val)=(yyvsp[0].val);}
#line 1939 "parser.tab.c"
    break;

  case 29: /* yetse: EQUAL yield_expr  */
#line 131 "parser.y"
                         {(yyval.val)=addnode("yetse");(yyvsp[-1].val)=addnode(string("EQUAL") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 1945 "parser.tab.c"
    break;

  case 30: /* yetse: EQUAL testlist_star_expr  */
#line 132 "parser.y"
                                 {(yyval.val)=addnode("yetse");(yyvsp[-1].val)=addnode(string("EQUAL") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 1951 "parser.tab.c"
    break;

  case 31: /* yetse_sure: yetse  */
#line 135 "parser.y"
                   {(yyval.val)=(yyvsp[0].val);}
#line 1957 "parser.tab.c"
    break;

  case 32: /* yetse_sure: yetse_sure yetse  */
#line 136 "parser.y"
                              {(yyval.val)=addnode("yetse_sure");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 1963 "parser.tab.c"
    break;

  case 33: /* testlist_star_expr: test tse_sure  */
#line 139 "parser.y"
                                  {(yyval.val)=addnode("testlist_star_expr");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 1969 "parser.tab.c"
    break;

  case 34: /* testlist_star_expr: test  */
#line 140 "parser.y"
                         {(yyval.val)=(yyvsp[0].val);}
#line 1975 "parser.tab.c"
    break;

  case 35: /* testlist_star_expr: test tse_sure COMMA  */
#line 141 "parser.y"
                                        {(yyval.val)=addnode("testlist_star_expr");addedge((yyval.val), (yyvsp[-2].val));addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("COMMA") );addedge((yyval.val), (yyvsp[0].val));}
#line 1981 "parser.tab.c"
    break;

  case 36: /* testlist_star_expr: test COMMA  */
#line 142 "parser.y"
                               {(yyval.val)=addnode("testlist_star_expr");addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("COMMA"));addedge((yyval.val), (yyvsp[0].val));}
#line 1987 "parser.tab.c"
    break;

  case 37: /* tse: COMMA test  */
#line 145 "parser.y"
                {(yyval.val)=addnode("tse");(yyvsp[-1].val)=addnode(string("COMMA") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 1993 "parser.tab.c"
    break;

  case 38: /* tse_sure: tse  */
#line 148 "parser.y"
               {(yyval.val)=(yyvsp[0].val);}
#line 1999 "parser.tab.c"
    break;

  case 39: /* tse_sure: tse_sure tse  */
#line 149 "parser.y"
                        {(yyval.val)=addnode("tse_sure");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2005 "parser.tab.c"
    break;

  case 40: /* test: or_test IF or_test ELSE test  */
#line 153 "parser.y"
                                   {(yyval.val)=addnode("test");addedge((yyval.val), (yyvsp[-4].val));(yyvsp[-3].val)=addnode(string("IF"));addedge((yyval.val), (yyvsp[-3].val));addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("ELSE") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2011 "parser.tab.c"
    break;

  case 41: /* test: or_test  */
#line 154 "parser.y"
              {(yyval.val)=(yyvsp[0].val);}
#line 2017 "parser.tab.c"
    break;

  case 42: /* or_test: and_test oat_sure  */
#line 157 "parser.y"
                           {(yyval.val)=addnode("or_test");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2023 "parser.tab.c"
    break;

  case 43: /* or_test: and_test  */
#line 158 "parser.y"
                  {(yyval.val)=(yyvsp[0].val);}
#line 2029 "parser.tab.c"
    break;

  case 44: /* oat: OR and_test  */
#line 161 "parser.y"
                {(yyval.val)=addnode("oat");(yyvsp[-1].val)=addnode(string("OR") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2035 "parser.tab.c"
    break;

  case 45: /* oat_sure: oat  */
#line 164 "parser.y"
              {(yyval.val)=(yyvsp[0].val);}
#line 2041 "parser.tab.c"
    break;

  case 46: /* oat_sure: oat_sure oat  */
#line 165 "parser.y"
                       {(yyval.val)=addnode("oat_sure");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2047 "parser.tab.c"
    break;

  case 47: /* and_test: not_test ant_sure  */
#line 168 "parser.y"
                            {(yyval.val)=addnode("and_test");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2053 "parser.tab.c"
    break;

  case 48: /* and_test: not_test  */
#line 169 "parser.y"
                   {(yyval.val)=(yyvsp[0].val);}
#line 2059 "parser.tab.c"
    break;

  case 49: /* ant: AND not_test  */
#line 172 "parser.y"
                  {(yyval.val)=addnode("ant");(yyvsp[-1].val)=addnode(string("AND") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2065 "parser.tab.c"
    break;

  case 50: /* ant_sure: ant  */
#line 175 "parser.y"
              {(yyval.val)=(yyvsp[0].val);}
#line 2071 "parser.tab.c"
    break;

  case 51: /* ant_sure: ant_sure ant  */
#line 176 "parser.y"
                       {(yyval.val)=addnode("ant_sure");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2077 "parser.tab.c"
    break;

  case 52: /* not_test: NOT not_test  */
#line 179 "parser.y"
                       {(yyval.val)=addnode("not_test");(yyvsp[-1].val)=addnode(string("NOT") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2083 "parser.tab.c"
    break;

  case 53: /* not_test: comparison  */
#line 180 "parser.y"
                     {(yyval.val)=(yyvsp[0].val);}
#line 2089 "parser.tab.c"
    break;

  case 54: /* comparison: expr coe_sure  */
#line 183 "parser.y"
                          {(yyval.val)=addnode("comparison");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2095 "parser.tab.c"
    break;

  case 55: /* comparison: expr  */
#line 184 "parser.y"
                 {(yyval.val)=(yyvsp[0].val);}
#line 2101 "parser.tab.c"
    break;

  case 56: /* coe: comp_op expr  */
#line 187 "parser.y"
                  {(yyval.val)=addnode("coe");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2107 "parser.tab.c"
    break;

  case 57: /* coe_sure: coe  */
#line 190 "parser.y"
               {(yyval.val)=(yyvsp[0].val);}
#line 2113 "parser.tab.c"
    break;

  case 58: /* coe_sure: coe_sure coe  */
#line 191 "parser.y"
                        {(yyval.val)=addnode("coe_sure");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2119 "parser.tab.c"
    break;

  case 59: /* expr: xor_expr xe_sure  */
#line 194 "parser.y"
                       {(yyval.val)=addnode("expr");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2125 "parser.tab.c"
    break;

  case 60: /* expr: xor_expr  */
#line 195 "parser.y"
               {(yyval.val)=(yyvsp[0].val);}
#line 2131 "parser.tab.c"
    break;

  case 61: /* xe: ALTE xor_expr  */
#line 198 "parser.y"
                  {(yyval.val)=addnode("xe");(yyvsp[-1].val)=addnode(string("ALTE") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2137 "parser.tab.c"
    break;

  case 62: /* xe_sure: xe  */
#line 201 "parser.y"
            {(yyval.val)=(yyvsp[0].val);}
#line 2143 "parser.tab.c"
    break;

  case 63: /* xe_sure: xe_sure xe  */
#line 202 "parser.y"
                    {(yyval.val)=addnode("xe_sure");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2149 "parser.tab.c"
    break;

  case 64: /* xor_expr: and_expr ae_sure  */
#line 205 "parser.y"
                           {(yyval.val)=addnode("xor_expr");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2155 "parser.tab.c"
    break;

  case 65: /* xor_expr: and_expr  */
#line 206 "parser.y"
                   {(yyval.val)=(yyvsp[0].val);}
#line 2161 "parser.tab.c"
    break;

  case 66: /* ae: POWER and_expr  */
#line 209 "parser.y"
                   {(yyval.val)=addnode("ae");(yyvsp[-1].val)=addnode(string("POWER") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2167 "parser.tab.c"
    break;

  case 67: /* ae_sure: ae  */
#line 212 "parser.y"
            {(yyval.val)=(yyvsp[0].val);}
#line 2173 "parser.tab.c"
    break;

  case 68: /* ae_sure: ae_sure ae  */
#line 213 "parser.y"
                    {(yyval.val)=addnode("ae_sure");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2179 "parser.tab.c"
    break;

  case 69: /* and_expr: shift_expr se_sure  */
#line 216 "parser.y"
                             {(yyval.val)=addnode("and_expr");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2185 "parser.tab.c"
    break;

  case 70: /* and_expr: shift_expr  */
#line 217 "parser.y"
                     {(yyval.val)=(yyvsp[0].val);}
#line 2191 "parser.tab.c"
    break;

  case 71: /* se: AAND shift_expr  */
#line 220 "parser.y"
                    {(yyval.val)=addnode("se");(yyvsp[-1].val)=addnode(string("AAND") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2197 "parser.tab.c"
    break;

  case 72: /* se_sure: se  */
#line 223 "parser.y"
             {(yyval.val)=(yyvsp[0].val);}
#line 2203 "parser.tab.c"
    break;

  case 73: /* se_sure: se_sure se  */
#line 224 "parser.y"
                     {(yyval.val)=addnode("se_sure");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2209 "parser.tab.c"
    break;

  case 74: /* shift_expr: arith_expr bae_sure  */
#line 227 "parser.y"
                                {(yyval.val)=addnode("shift_expr");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2215 "parser.tab.c"
    break;

  case 75: /* shift_expr: arith_expr  */
#line 228 "parser.y"
                       {(yyval.val)=(yyvsp[0].val);}
#line 2221 "parser.tab.c"
    break;

  case 76: /* bae: LLT arith_expr  */
#line 231 "parser.y"
                    {(yyval.val)=addnode("bae");(yyvsp[-1].val)=addnode(string("LLT") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2227 "parser.tab.c"
    break;

  case 77: /* bae: GGT arith_expr  */
#line 232 "parser.y"
                    {(yyval.val)=addnode("bae");(yyvsp[-1].val)=addnode(string("GGT") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2233 "parser.tab.c"
    break;

  case 78: /* bae_sure: bae  */
#line 235 "parser.y"
              {(yyval.val)=(yyvsp[0].val);}
#line 2239 "parser.tab.c"
    break;

  case 79: /* bae_sure: bae_sure bae  */
#line 236 "parser.y"
                       {(yyval.val)=addnode("bae_sure");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2245 "parser.tab.c"
    break;

  case 80: /* arith_expr: term pmterm_sure  */
#line 239 "parser.y"
                             {(yyval.val)=addnode("arith_expr");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2251 "parser.tab.c"
    break;

  case 81: /* arith_expr: term  */
#line 240 "parser.y"
                 {(yyval.val)=(yyvsp[0].val);}
#line 2257 "parser.tab.c"
    break;

  case 82: /* pmterm: PLUS term  */
#line 243 "parser.y"
                  {(yyval.val)=addnode("pmterm");(yyvsp[-1].val)=addnode(string("PLUS") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2263 "parser.tab.c"
    break;

  case 83: /* pmterm: MINUS term  */
#line 244 "parser.y"
                   {(yyval.val)=addnode("pmterm");(yyvsp[-1].val)=addnode(string("MINUS") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2269 "parser.tab.c"
    break;

  case 84: /* pmterm_sure: pmterm  */
#line 247 "parser.y"
                   {(yyval.val)=(yyvsp[0].val);}
#line 2275 "parser.tab.c"
    break;

  case 85: /* pmterm_sure: pmterm_sure pmterm  */
#line 248 "parser.y"
                               {(yyval.val)=addnode("pmterm_sure");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2281 "parser.tab.c"
    break;

  case 86: /* term: factor sfac_sure  */
#line 251 "parser.y"
                       {(yyval.val)=addnode("term");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2287 "parser.tab.c"
    break;

  case 87: /* term: factor  */
#line 252 "parser.y"
             {(yyval.val)=(yyvsp[0].val);}
#line 2293 "parser.tab.c"
    break;

  case 88: /* sfac: MULTI factor  */
#line 255 "parser.y"
                  {(yyval.val)=addnode("sfac");(yyvsp[-1].val)=addnode(string("PLUS") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2299 "parser.tab.c"
    break;

  case 89: /* sfac: DIVI factor  */
#line 256 "parser.y"
                 {(yyval.val)=addnode("sfac");(yyvsp[-1].val)=addnode(string("DIVI") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2305 "parser.tab.c"
    break;

  case 90: /* sfac: MOD factor  */
#line 257 "parser.y"
                {(yyval.val)=addnode("sfac");(yyvsp[-1].val)=addnode(string("MOD") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2311 "parser.tab.c"
    break;

  case 91: /* sfac: SSLASH factor  */
#line 258 "parser.y"
                   {(yyval.val)=addnode("sfac");(yyvsp[-1].val)=addnode(string("SSLASH") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2317 "parser.tab.c"
    break;

  case 92: /* sfac_sure: sfac  */
#line 261 "parser.y"
                {(yyval.val)=(yyvsp[0].val);}
#line 2323 "parser.tab.c"
    break;

  case 93: /* sfac_sure: sfac_sure sfac  */
#line 262 "parser.y"
                          {(yyval.val)=addnode("sfac_sure");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2329 "parser.tab.c"
    break;

  case 94: /* factor: PLUS factor  */
#line 265 "parser.y"
                   {(yyval.val)=addnode("factor");(yyvsp[-1].val)=addnode(string("PLUS") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2335 "parser.tab.c"
    break;

  case 95: /* factor: MINUS factor  */
#line 266 "parser.y"
                    {(yyval.val)=addnode("factor");(yyvsp[-1].val)=addnode(string("MINUS") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2341 "parser.tab.c"
    break;

  case 96: /* factor: NOPE factor  */
#line 267 "parser.y"
                   {(yyval.val)=addnode("factor");(yyvsp[-1].val)=addnode(string("NOPE") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2347 "parser.tab.c"
    break;

  case 97: /* factor: power  */
#line 268 "parser.y"
             {(yyval.val)=(yyvsp[0].val);}
#line 2353 "parser.tab.c"
    break;

  case 98: /* power: atom_expr SSTAR factor  */
#line 271 "parser.y"
                              {(yyval.val)=addnode("power");addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("SSTAR"));addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2359 "parser.tab.c"
    break;

  case 99: /* power: atom_expr  */
#line 272 "parser.y"
                 {(yyval.val)=(yyvsp[0].val);}
#line 2365 "parser.tab.c"
    break;

  case 100: /* atom_expr: atom trailer_sure  */
#line 275 "parser.y"
                             {(yyval.val)=addnode("atom_expr");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2371 "parser.tab.c"
    break;

  case 101: /* atom_expr: atom  */
#line 276 "parser.y"
                {(yyval.val)=(yyvsp[0].val);}
#line 2377 "parser.tab.c"
    break;

  case 102: /* trailer_sure: trailer  */
#line 279 "parser.y"
                      {(yyval.val)=(yyvsp[0].val);}
#line 2383 "parser.tab.c"
    break;

  case 103: /* trailer_sure: trailer_sure trailer  */
#line 280 "parser.y"
                                   {(yyval.val)=addnode("trailer_sure");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2389 "parser.tab.c"
    break;

  case 104: /* atom: CIROPEN yield_expr CIRCLOSE  */
#line 283 "parser.y"
                                  {(yyval.val)=addnode("atom");(yyvsp[-2].val)=addnode(string("CIROPEN") );addedge((yyval.val), (yyvsp[-2].val));addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("CIRCLOSE") );addedge((yyval.val), (yyvsp[0].val));}
#line 2395 "parser.tab.c"
    break;

  case 105: /* atom: CIROPEN testlist_comp CIRCLOSE  */
#line 284 "parser.y"
                                     {(yyval.val)=addnode("atom");(yyvsp[-2].val)=addnode(string("CIROPEN") );addedge((yyval.val), (yyvsp[-2].val));addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("CIRCLOSE") );addedge((yyval.val), (yyvsp[0].val));}
#line 2401 "parser.tab.c"
    break;

  case 106: /* atom: CIROPEN CIRCLOSE  */
#line 285 "parser.y"
                       {(yyval.val)=addnode("atom");(yyvsp[-1].val)=addnode(string("CIROPEN") );addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("CIRCLOSE"));addedge((yyval.val), (yyvsp[0].val));}
#line 2407 "parser.tab.c"
    break;

  case 107: /* atom: SQOPEN testlist_comp SQCLOSE  */
#line 286 "parser.y"
                                   {(yyval.val)=addnode("atom");(yyvsp[-2].val)=addnode(string("SQOPEN") );addedge((yyval.val), (yyvsp[-2].val));addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("SQCLOSE") );addedge((yyval.val), (yyvsp[0].val));}
#line 2413 "parser.tab.c"
    break;

  case 108: /* atom: SQOPEN SQCLOSE  */
#line 287 "parser.y"
                     {(yyval.val)=addnode("atom");(yyvsp[-1].val)=addnode(string("SQOPEN") );addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("SQCLOSE"));addedge((yyval.val), (yyvsp[0].val));}
#line 2419 "parser.tab.c"
    break;

  case 109: /* atom: CUOPEN CUCLOSE  */
#line 288 "parser.y"
                     {(yyval.val)=addnode("atom");(yyvsp[-1].val)=addnode(string("CUOPEN") );addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("CUCLOSE"));addedge((yyval.val), (yyvsp[0].val));}
#line 2425 "parser.tab.c"
    break;

  case 110: /* atom: INT  */
#line 289 "parser.y"
          {(yyval.val)=addnode("atom");(yyvsp[0].val)=addnode(string("INT") );addedge((yyval.val), (yyvsp[0].val));}
#line 2431 "parser.tab.c"
    break;

  case 111: /* atom: FLOAT  */
#line 290 "parser.y"
            {(yyval.val)=addnode("atom");(yyvsp[0].val)=addnode(string("FLOAT") );addedge((yyval.val), (yyvsp[0].val));}
#line 2437 "parser.tab.c"
    break;

  case 112: /* atom: STR  */
#line 291 "parser.y"
          {(yyval.val)=addnode("atom");(yyvsp[0].val)=addnode(string("STR") );addedge((yyval.val), (yyvsp[0].val));}
#line 2443 "parser.tab.c"
    break;

  case 113: /* atom: BOOL  */
#line 292 "parser.y"
           {(yyval.val)=addnode("atom");(yyvsp[0].val)=addnode(string("BOOL") );addedge((yyval.val), (yyvsp[0].val));}
#line 2449 "parser.tab.c"
    break;

  case 114: /* atom: NUMBER  */
#line 293 "parser.y"
             {(yyval.val)=addnode("atom");(yyvsp[0].val)=addnode(string("NUMBER") );addedge((yyval.val), (yyvsp[0].val));}
#line 2455 "parser.tab.c"
    break;

  case 115: /* atom: string_sure  */
#line 294 "parser.y"
                  {(yyval.val)=(yyvsp[0].val);}
#line 2461 "parser.tab.c"
    break;

  case 116: /* atom: DDOT  */
#line 295 "parser.y"
           {(yyval.val)=addnode("atom");(yyvsp[0].val)=addnode(string("DDOT") );addedge((yyval.val), (yyvsp[0].val));}
#line 2467 "parser.tab.c"
    break;

  case 117: /* atom: NONE  */
#line 296 "parser.y"
           {(yyval.val)=addnode("atom");(yyvsp[0].val)=addnode(string("NONE") );addedge((yyval.val), (yyvsp[0].val));}
#line 2473 "parser.tab.c"
    break;

  case 118: /* atom: TRUE  */
#line 297 "parser.y"
           {(yyval.val)=addnode("atom");(yyvsp[0].val)=addnode(string("TRUE") );addedge((yyval.val), (yyvsp[0].val));}
#line 2479 "parser.tab.c"
    break;

  case 119: /* atom: FALSE  */
#line 298 "parser.y"
            {(yyval.val)=addnode("atom");(yyvsp[0].val)=addnode(string("FALSE") );addedge((yyval.val), (yyvsp[0].val));}
#line 2485 "parser.tab.c"
    break;

  case 120: /* atom: IDENTIFIER  */
#line 299 "parser.y"
                 {(yyval.val)=addnode("atom");(yyvsp[0].val)=addnode(string("IDENTIFIER") );addedge((yyval.val), (yyvsp[0].val));}
#line 2491 "parser.tab.c"
    break;

  case 121: /* yield_expr: YIELD yield_arg  */
#line 302 "parser.y"
                            {(yyval.val)=addnode("yield_expr");(yyvsp[-1].val)=addnode(string("YIELD") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2497 "parser.tab.c"
    break;

  case 122: /* yield_expr: YIELD  */
#line 303 "parser.y"
                  {(yyval.val)=addnode("yield_expr");(yyvsp[0].val)=addnode(string("YIELD") );addedge((yyval.val), (yyvsp[0].val));}
#line 2503 "parser.tab.c"
    break;

  case 123: /* yield_arg: FROM test  */
#line 306 "parser.y"
                     {(yyval.val)=addnode("yield_arg");(yyvsp[-1].val)=addnode(string("FROM") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2509 "parser.tab.c"
    break;

  case 124: /* yield_arg: testlist  */
#line 307 "parser.y"
                    {(yyval.val)=(yyvsp[0].val);}
#line 2515 "parser.tab.c"
    break;

  case 125: /* testlist: test ct_sure COMMA  */
#line 310 "parser.y"
                             {(yyval.val)=addnode("testlist");addedge((yyval.val), (yyvsp[-2].val));addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("COMMA") );addedge((yyval.val), (yyvsp[0].val));}
#line 2521 "parser.tab.c"
    break;

  case 126: /* testlist: test ct_sure  */
#line 311 "parser.y"
                       {(yyval.val)=addnode("testlist");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2527 "parser.tab.c"
    break;

  case 127: /* testlist: test COMMA  */
#line 312 "parser.y"
                     {(yyval.val)=addnode("testlist");addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("COMMA"));addedge((yyval.val), (yyvsp[0].val));}
#line 2533 "parser.tab.c"
    break;

  case 128: /* testlist: test  */
#line 313 "parser.y"
               {(yyval.val)=(yyvsp[0].val);}
#line 2539 "parser.tab.c"
    break;

  case 129: /* ct: COMMA test  */
#line 316 "parser.y"
               {(yyval.val)=addnode("ct");(yyvsp[-1].val)=addnode(string("COMMA") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2545 "parser.tab.c"
    break;

  case 130: /* ct_sure: ct  */
#line 319 "parser.y"
            {(yyval.val)=(yyvsp[0].val);}
#line 2551 "parser.tab.c"
    break;

  case 131: /* ct_sure: ct_sure ct  */
#line 320 "parser.y"
                    {(yyval.val)=addnode("ct_sure");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2557 "parser.tab.c"
    break;

  case 132: /* testlist_comp: test comp_for  */
#line 323 "parser.y"
                             {(yyval.val)=addnode("testlist_comp");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2563 "parser.tab.c"
    break;

  case 133: /* testlist_comp: test ct_sure COMMA  */
#line 324 "parser.y"
                                  {(yyval.val)=addnode("testlist_comp");addedge((yyval.val), (yyvsp[-2].val));addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("COMMA") );addedge((yyval.val), (yyvsp[0].val));}
#line 2569 "parser.tab.c"
    break;

  case 134: /* testlist_comp: test COMMA  */
#line 325 "parser.y"
                          {(yyval.val)=addnode("testlist_comp");addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("COMMA"));addedge((yyval.val), (yyvsp[0].val));}
#line 2575 "parser.tab.c"
    break;

  case 135: /* testlist_comp: test ct_sure  */
#line 326 "parser.y"
                            {(yyval.val)=addnode("testlist_comp");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2581 "parser.tab.c"
    break;

  case 136: /* testlist_comp: test  */
#line 327 "parser.y"
                    {(yyval.val)=(yyvsp[0].val);}
#line 2587 "parser.tab.c"
    break;

  case 137: /* comp_for: FOR exprlist IN or_test comp_iter  */
#line 330 "parser.y"
                                            {(yyval.val)=addnode("comp_for");(yyvsp[-4].val)=addnode(string("FOR") );addedge((yyval.val), (yyvsp[-4].val));addedge((yyval.val), (yyvsp[-3].val));(yyvsp[-2].val)=addnode(string("IN") );addedge((yyval.val), (yyvsp[-2].val));addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2593 "parser.tab.c"
    break;

  case 138: /* comp_for: FOR exprlist IN or_test  */
#line 331 "parser.y"
                                  {(yyval.val)=addnode("comp_for");(yyvsp[-3].val)=addnode(string("FOR") );addedge((yyval.val), (yyvsp[-3].val));addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("IN") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2599 "parser.tab.c"
    break;

  case 139: /* exprlist: expr cese_sure COMMA  */
#line 334 "parser.y"
                               {(yyval.val)=addnode("exprlist");addedge((yyval.val), (yyvsp[-2].val));addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("COMMA") );addedge((yyval.val), (yyvsp[0].val));}
#line 2605 "parser.tab.c"
    break;

  case 140: /* exprlist: expr COMMA  */
#line 335 "parser.y"
                     {(yyval.val)=addnode("exprlist");addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("COMMA"));addedge((yyval.val), (yyvsp[0].val));}
#line 2611 "parser.tab.c"
    break;

  case 141: /* exprlist: expr cese_sure  */
#line 336 "parser.y"
                         {(yyval.val)=addnode("exprlist");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2617 "parser.tab.c"
    break;

  case 142: /* exprlist: expr  */
#line 337 "parser.y"
               {(yyval.val)=(yyvsp[0].val);}
#line 2623 "parser.tab.c"
    break;

  case 143: /* cese: COMMA expr  */
#line 340 "parser.y"
                 {(yyval.val)=addnode("cese");(yyvsp[-1].val)=addnode(string("COMMA") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2629 "parser.tab.c"
    break;

  case 144: /* cese_sure: cese  */
#line 343 "parser.y"
                {(yyval.val)=(yyvsp[0].val);}
#line 2635 "parser.tab.c"
    break;

  case 145: /* cese_sure: cese_sure cese  */
#line 344 "parser.y"
                           {(yyval.val)=addnode("cese_sure");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2641 "parser.tab.c"
    break;

  case 146: /* comp_iter: comp_for  */
#line 347 "parser.y"
                    {(yyval.val)=(yyvsp[0].val);}
#line 2647 "parser.tab.c"
    break;

  case 147: /* comp_iter: comp_if  */
#line 348 "parser.y"
                   {(yyval.val)=(yyvsp[0].val);}
#line 2653 "parser.tab.c"
    break;

  case 148: /* comp_if: IF test_nocond comp_iter  */
#line 351 "parser.y"
                                  {(yyval.val)=addnode("comp_if");(yyvsp[-2].val)=addnode(string("IF") );addedge((yyval.val), (yyvsp[-2].val));addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2659 "parser.tab.c"
    break;

  case 149: /* comp_if: IF test_nocond  */
#line 352 "parser.y"
                        {(yyval.val)=addnode("comp_if");(yyvsp[-1].val)=addnode(string("IF") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2665 "parser.tab.c"
    break;

  case 150: /* test_nocond: or_test  */
#line 355 "parser.y"
                     {(yyval.val)=(yyvsp[0].val);}
#line 2671 "parser.tab.c"
    break;

  case 151: /* string_sure: STRING  */
#line 358 "parser.y"
                   {(yyval.val)=addnode("string_sure");(yyvsp[0].val)=addnode(string("STRING") );addedge((yyval.val), (yyvsp[0].val));}
#line 2677 "parser.tab.c"
    break;

  case 152: /* string_sure: STRING string_sure  */
#line 359 "parser.y"
                               {(yyval.val)=addnode("string_sure");(yyvsp[-1].val)=addnode(string("STRING") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2683 "parser.tab.c"
    break;

  case 153: /* trailer: CIROPEN arglist CIRCLOSE  */
#line 362 "parser.y"
                                    {(yyval.val)=addnode("trailer");(yyvsp[-2].val)=addnode(string("CIROPEN") );addedge((yyval.val), (yyvsp[-2].val));addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("CIRCLOSE") );addedge((yyval.val), (yyvsp[0].val));}
#line 2689 "parser.tab.c"
    break;

  case 154: /* trailer: CIROPEN CIRCLOSE  */
#line 363 "parser.y"
                             {(yyval.val)=addnode("trailer");(yyvsp[-1].val)=addnode(string("CIROPEN") );addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("CIRCLOSE"));addedge((yyval.val), (yyvsp[0].val));}
#line 2695 "parser.tab.c"
    break;

  case 155: /* trailer: SQOPEN subscriptlist SQCLOSE  */
#line 364 "parser.y"
                                        {(yyval.val)=addnode("trailer");(yyvsp[-2].val)=addnode(string("SQOPEN") );addedge((yyval.val), (yyvsp[-2].val));addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("SQCLOSE") );addedge((yyval.val), (yyvsp[0].val));}
#line 2701 "parser.tab.c"
    break;

  case 156: /* trailer: DOT IDENTIFIER  */
#line 365 "parser.y"
                         {(yyval.val)=addnode("trailer");(yyvsp[-1].val)=addnode(string("DOT") );addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("IDENTIFIER"));addedge((yyval.val), (yyvsp[0].val));}
#line 2707 "parser.tab.c"
    break;

  case 157: /* trailer: DOT DUNDER  */
#line 366 "parser.y"
                     {(yyval.val)=addnode("trailer");(yyvsp[-1].val)=addnode(string("DOT") );addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("DUNDER"));addedge((yyval.val), (yyvsp[0].val));}
#line 2713 "parser.tab.c"
    break;

  case 158: /* arglist: argument ca_sure  */
#line 369 "parser.y"
                          {(yyval.val)=addnode("arglist");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2719 "parser.tab.c"
    break;

  case 159: /* arglist: argument  */
#line 370 "parser.y"
                  {(yyval.val)=(yyvsp[0].val);}
#line 2725 "parser.tab.c"
    break;

  case 160: /* arglist: argument ca_sure COMMA  */
#line 371 "parser.y"
                                {(yyval.val)=addnode("arglist");addedge((yyval.val), (yyvsp[-2].val));addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("COMMA") );addedge((yyval.val), (yyvsp[0].val));}
#line 2731 "parser.tab.c"
    break;

  case 161: /* arglist: argument COMMA  */
#line 372 "parser.y"
                        {(yyval.val)=addnode("arglist");addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("COMMA"));addedge((yyval.val), (yyvsp[0].val));}
#line 2737 "parser.tab.c"
    break;

  case 162: /* ca: COMMA argument  */
#line 375 "parser.y"
                  {(yyval.val)=addnode("ca");(yyvsp[-1].val)=addnode(string("COMMA") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2743 "parser.tab.c"
    break;

  case 163: /* ca_sure: ca  */
#line 378 "parser.y"
            {(yyval.val)=(yyvsp[0].val);}
#line 2749 "parser.tab.c"
    break;

  case 164: /* ca_sure: ca_sure ca  */
#line 379 "parser.y"
                    {(yyval.val)=addnode("ca_sure");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2755 "parser.tab.c"
    break;

  case 165: /* argument: test  */
#line 382 "parser.y"
               {(yyval.val)=(yyvsp[0].val);}
#line 2761 "parser.tab.c"
    break;

  case 166: /* argument: test comp_for  */
#line 383 "parser.y"
                        {(yyval.val)=addnode("argument");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2767 "parser.tab.c"
    break;

  case 167: /* argument: test EQUAL test  */
#line 384 "parser.y"
                          {(yyval.val)=addnode("argument");addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("EQUAL"));addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2773 "parser.tab.c"
    break;

  case 168: /* subscriptlist: subscript csubs_sure  */
#line 387 "parser.y"
                                    {(yyval.val)=addnode("subscriptlist");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2779 "parser.tab.c"
    break;

  case 169: /* subscriptlist: subscript  */
#line 388 "parser.y"
                         {(yyval.val)=(yyvsp[0].val);}
#line 2785 "parser.tab.c"
    break;

  case 170: /* subscriptlist: subscript csubs_sure COMMA  */
#line 389 "parser.y"
                                          {(yyval.val)=addnode("subscriptlist");addedge((yyval.val), (yyvsp[-2].val));addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("COMMA") );addedge((yyval.val), (yyvsp[0].val));}
#line 2791 "parser.tab.c"
    break;

  case 171: /* subscriptlist: subscript COMMA  */
#line 390 "parser.y"
                               {(yyval.val)=addnode("subscriptlist");addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("COMMA"));addedge((yyval.val), (yyvsp[0].val));}
#line 2797 "parser.tab.c"
    break;

  case 172: /* csubs: COMMA subscript  */
#line 393 "parser.y"
                       {(yyval.val)=addnode("csubs");(yyvsp[-1].val)=addnode(string("COMMA") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2803 "parser.tab.c"
    break;

  case 173: /* csubs_sure: csubs  */
#line 396 "parser.y"
                  {(yyval.val)=(yyvsp[0].val);}
#line 2809 "parser.tab.c"
    break;

  case 174: /* csubs_sure: csubs_sure csubs  */
#line 397 "parser.y"
                             {(yyval.val)=addnode("csubs_sure");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2815 "parser.tab.c"
    break;

  case 175: /* subscript: test  */
#line 400 "parser.y"
                {(yyval.val)=(yyvsp[0].val);}
#line 2821 "parser.tab.c"
    break;

  case 176: /* subscript: test COLON test  */
#line 401 "parser.y"
                            {(yyval.val)=addnode("subscript");addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("COLON"));addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2827 "parser.tab.c"
    break;

  case 177: /* subscript: test COLON  */
#line 402 "parser.y"
                       {(yyval.val)=addnode("subscript");addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("COLON"));addedge((yyval.val), (yyvsp[0].val));}
#line 2833 "parser.tab.c"
    break;

  case 178: /* subscript: COLON test  */
#line 403 "parser.y"
                      {(yyval.val)=addnode("subscript");(yyvsp[-1].val)=addnode(string("COLON") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2839 "parser.tab.c"
    break;

  case 179: /* subscript: COLON  */
#line 404 "parser.y"
                 {(yyval.val)=addnode("subscript");(yyvsp[0].val)=addnode(string("COLON") );addedge((yyval.val), (yyvsp[0].val));}
#line 2845 "parser.tab.c"
    break;

  case 180: /* comp_op: LT  */
#line 408 "parser.y"
            {(yyval.val)=addnode("comp_op");(yyvsp[0].val)=addnode(string("LT") );addedge((yyval.val), (yyvsp[0].val));}
#line 2851 "parser.tab.c"
    break;

  case 181: /* comp_op: GT  */
#line 409 "parser.y"
           {(yyval.val)=addnode("comp_op");(yyvsp[0].val)=addnode(string("GT") );addedge((yyval.val), (yyvsp[0].val));}
#line 2857 "parser.tab.c"
    break;

  case 182: /* comp_op: EEQ  */
#line 410 "parser.y"
            {(yyval.val)=addnode("comp_op");(yyvsp[0].val)=addnode(string("EEQ") );addedge((yyval.val), (yyvsp[0].val));}
#line 2863 "parser.tab.c"
    break;

  case 183: /* comp_op: GEQ  */
#line 411 "parser.y"
            {(yyval.val)=addnode("comp_op");(yyvsp[0].val)=addnode(string("GEQ") );addedge((yyval.val), (yyvsp[0].val));}
#line 2869 "parser.tab.c"
    break;

  case 184: /* comp_op: LEQ  */
#line 412 "parser.y"
            {(yyval.val)=addnode("comp_op");(yyvsp[0].val)=addnode(string("LEQ") );addedge((yyval.val), (yyvsp[0].val));}
#line 2875 "parser.tab.c"
    break;

  case 185: /* comp_op: DMOND  */
#line 413 "parser.y"
              {(yyval.val)=addnode("comp_op");(yyvsp[0].val)=addnode(string("DMOND") );addedge((yyval.val), (yyvsp[0].val));}
#line 2881 "parser.tab.c"
    break;

  case 186: /* comp_op: NEQ  */
#line 414 "parser.y"
            {(yyval.val)=addnode("comp_op");(yyvsp[0].val)=addnode(string("NEQ") );addedge((yyval.val), (yyvsp[0].val));}
#line 2887 "parser.tab.c"
    break;

  case 187: /* comp_op: IN  */
#line 415 "parser.y"
           {(yyval.val)=addnode("comp_op");(yyvsp[0].val)=addnode(string("IN") );addedge((yyval.val), (yyvsp[0].val));}
#line 2893 "parser.tab.c"
    break;

  case 188: /* comp_op: NOT IN  */
#line 416 "parser.y"
               {(yyval.val)=addnode("comp_op");(yyvsp[-1].val)=addnode(string("NOT") );addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("IN"));addedge((yyval.val), (yyvsp[0].val));}
#line 2899 "parser.tab.c"
    break;

  case 189: /* comp_op: IS  */
#line 417 "parser.y"
           {(yyval.val)=addnode("comp_op");(yyvsp[0].val)=addnode(string("IS") );addedge((yyval.val), (yyvsp[0].val));}
#line 2905 "parser.tab.c"
    break;

  case 190: /* comp_op: IS NOT  */
#line 418 "parser.y"
               {(yyval.val)=addnode("comp_op");(yyvsp[-1].val)=addnode(string("IS") );addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("NOT"));addedge((yyval.val), (yyvsp[0].val));}
#line 2911 "parser.tab.c"
    break;

  case 191: /* annassign: COLON test  */
#line 421 "parser.y"
                       {(yyval.val)=addnode("annassign");(yyvsp[-1].val)=addnode(string("COLON") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2917 "parser.tab.c"
    break;

  case 192: /* annassign: COLON test EQUAL test  */
#line 422 "parser.y"
                                  {(yyval.val)=addnode("annassign");(yyvsp[-3].val)=addnode(string("COLON") );addedge((yyval.val), (yyvsp[-3].val));addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("EQUAL") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 2923 "parser.tab.c"
    break;

  case 193: /* augassign: PEQ  */
#line 425 "parser.y"
               {(yyval.val)=addnode("augassign");(yyvsp[0].val)=addnode(string("PEQ") );addedge((yyval.val), (yyvsp[0].val));}
#line 2929 "parser.tab.c"
    break;

  case 194: /* augassign: MIEQ  */
#line 426 "parser.y"
                {(yyval.val)=addnode("augassign");(yyvsp[0].val)=addnode(string("MIEQ") );addedge((yyval.val), (yyvsp[0].val));}
#line 2935 "parser.tab.c"
    break;

  case 195: /* augassign: MUEQ  */
#line 427 "parser.y"
                {(yyval.val)=addnode("augassign");(yyvsp[0].val)=addnode(string("MUEQ") );addedge((yyval.val), (yyvsp[0].val));}
#line 2941 "parser.tab.c"
    break;

  case 196: /* augassign: DEQ  */
#line 428 "parser.y"
               {(yyval.val)=addnode("augassign");(yyvsp[0].val)=addnode(string("DEQ") );addedge((yyval.val), (yyvsp[0].val));}
#line 2947 "parser.tab.c"
    break;

  case 197: /* augassign: MOEQ  */
#line 429 "parser.y"
                {(yyval.val)=addnode("augassign");(yyvsp[0].val)=addnode(string("MOEQ") );addedge((yyval.val), (yyvsp[0].val));}
#line 2953 "parser.tab.c"
    break;

  case 198: /* augassign: AEQ  */
#line 430 "parser.y"
               {(yyval.val)=addnode("augassign");(yyvsp[0].val)=addnode(string("AEQ") );addedge((yyval.val), (yyvsp[0].val));}
#line 2959 "parser.tab.c"
    break;

  case 199: /* augassign: ALEQ  */
#line 431 "parser.y"
                {(yyval.val)=addnode("augassign");(yyvsp[0].val)=addnode(string("ALEQ") );addedge((yyval.val), (yyvsp[0].val));}
#line 2965 "parser.tab.c"
    break;

  case 200: /* augassign: POEQ  */
#line 432 "parser.y"
                {(yyval.val)=addnode("augassign");(yyvsp[0].val)=addnode(string("POEQ") );addedge((yyval.val), (yyvsp[0].val));}
#line 2971 "parser.tab.c"
    break;

  case 201: /* augassign: LLEQ  */
#line 433 "parser.y"
                {(yyval.val)=addnode("augassign");(yyvsp[0].val)=addnode(string("LLEQ") );addedge((yyval.val), (yyvsp[0].val));}
#line 2977 "parser.tab.c"
    break;

  case 202: /* augassign: GGEQ  */
#line 434 "parser.y"
                {(yyval.val)=addnode("augassign");(yyvsp[0].val)=addnode(string("GGEQ") );addedge((yyval.val), (yyvsp[0].val));}
#line 2983 "parser.tab.c"
    break;

  case 203: /* augassign: MUMUEQ  */
#line 435 "parser.y"
                  {(yyval.val)=addnode("augassign");(yyvsp[0].val)=addnode(string("MUMUEQ") );addedge((yyval.val), (yyvsp[0].val));}
#line 2989 "parser.tab.c"
    break;

  case 204: /* augassign: DDEQ  */
#line 436 "parser.y"
                {(yyval.val)=addnode("augassign");(yyvsp[0].val)=addnode(string("DDEQ") );addedge((yyval.val), (yyvsp[0].val));}
#line 2995 "parser.tab.c"
    break;

  case 205: /* flow_stmt: break_stmt  */
#line 439 "parser.y"
                      {(yyval.val)=(yyvsp[0].val);}
#line 3001 "parser.tab.c"
    break;

  case 206: /* flow_stmt: continue_stmt  */
#line 440 "parser.y"
                          {(yyval.val)=(yyvsp[0].val);}
#line 3007 "parser.tab.c"
    break;

  case 207: /* flow_stmt: return_stmt  */
#line 441 "parser.y"
                        {(yyval.val)=(yyvsp[0].val);}
#line 3013 "parser.tab.c"
    break;

  case 208: /* flow_stmt: raise_stmt  */
#line 442 "parser.y"
                       {(yyval.val)=(yyvsp[0].val);}
#line 3019 "parser.tab.c"
    break;

  case 209: /* flow_stmt: yield_stmt  */
#line 443 "parser.y"
                       {(yyval.val)=(yyvsp[0].val);}
#line 3025 "parser.tab.c"
    break;

  case 210: /* break_stmt: BREAK  */
#line 446 "parser.y"
                  {(yyval.val)=addnode("break_stmt");(yyvsp[0].val)=addnode(string("BREAK") );addedge((yyval.val), (yyvsp[0].val));}
#line 3031 "parser.tab.c"
    break;

  case 211: /* continue_stmt: CONTINUE  */
#line 449 "parser.y"
                        {(yyval.val)=addnode("continue_stmt");(yyvsp[0].val)=addnode(string("CONTINUE") );addedge((yyval.val), (yyvsp[0].val));}
#line 3037 "parser.tab.c"
    break;

  case 212: /* return_stmt: RETURN  */
#line 452 "parser.y"
                    {(yyval.val)=addnode("return_stmt");(yyvsp[0].val)=addnode(string("RETURN") );addedge((yyval.val), (yyvsp[0].val));}
#line 3043 "parser.tab.c"
    break;

  case 213: /* return_stmt: RETURN testlist  */
#line 453 "parser.y"
                             {(yyval.val)=addnode("return_stmt");(yyvsp[-1].val)=addnode(string("RETURN") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3049 "parser.tab.c"
    break;

  case 214: /* raise_stmt: RAISE test FROM test  */
#line 456 "parser.y"
                                 {(yyval.val)=addnode("raise_stmt");(yyvsp[-3].val)=addnode(string("RAISE") );addedge((yyval.val), (yyvsp[-3].val));addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("FROM") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3055 "parser.tab.c"
    break;

  case 215: /* raise_stmt: RAISE test  */
#line 457 "parser.y"
                        {(yyval.val)=addnode("raise_stmt");(yyvsp[-1].val)=addnode(string("RAISE") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3061 "parser.tab.c"
    break;

  case 216: /* raise_stmt: RAISE  */
#line 458 "parser.y"
                    {(yyval.val)=addnode("raise_stmt");(yyvsp[0].val)=addnode(string("RAISE") );addedge((yyval.val), (yyvsp[0].val));}
#line 3067 "parser.tab.c"
    break;

  case 217: /* yield_stmt: yield_expr  */
#line 461 "parser.y"
                       {(yyval.val)=(yyvsp[0].val);}
#line 3073 "parser.tab.c"
    break;

  case 218: /* global_stmt: GLOBAL IDENTIFIER cn_sure  */
#line 465 "parser.y"
                                       {(yyval.val)=addnode("global_stmt");(yyvsp[-2].val)=addnode(string("GLOBAL") );addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("IDENTIFIER"));addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3079 "parser.tab.c"
    break;

  case 219: /* global_stmt: GLOBAL IDENTIFIER  */
#line 466 "parser.y"
                               {(yyval.val)=addnode("global_stmt");(yyvsp[-1].val)=addnode(string("GLOBAL") );addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("IDENTIFIER"));addedge((yyval.val), (yyvsp[0].val));}
#line 3085 "parser.tab.c"
    break;

  case 220: /* cn: COMMA IDENTIFIER  */
#line 469 "parser.y"
                     {(yyval.val)=addnode("cn");(yyvsp[-1].val)=addnode(string("COMMA") );addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("IDENTIFIER"));addedge((yyval.val), (yyvsp[0].val));}
#line 3091 "parser.tab.c"
    break;

  case 221: /* cn_sure: cn  */
#line 472 "parser.y"
            {(yyval.val)=(yyvsp[0].val);}
#line 3097 "parser.tab.c"
    break;

  case 222: /* cn_sure: cn_sure cn  */
#line 473 "parser.y"
                    {(yyval.val)=addnode("cn_sure");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3103 "parser.tab.c"
    break;

  case 223: /* assert_stmt: ASSERT test  */
#line 476 "parser.y"
                         {(yyval.val)=addnode("assert_stmt");(yyvsp[-1].val)=addnode(string("ASSERT") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3109 "parser.tab.c"
    break;

  case 224: /* assert_stmt: ASSERT test COMMA test  */
#line 477 "parser.y"
                                    {(yyval.val)=addnode("assert_stmt");(yyvsp[-3].val)=addnode(string("ASSERT") );addedge((yyval.val), (yyvsp[-3].val));addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("COMMA") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3115 "parser.tab.c"
    break;

  case 225: /* compound_stmt: if_stmt  */
#line 480 "parser.y"
                       {(yyval.val)=(yyvsp[0].val);}
#line 3121 "parser.tab.c"
    break;

  case 226: /* compound_stmt: while_stmt  */
#line 481 "parser.y"
                          {(yyval.val)=(yyvsp[0].val);}
#line 3127 "parser.tab.c"
    break;

  case 227: /* compound_stmt: for_stmt  */
#line 482 "parser.y"
                        {(yyval.val)=(yyvsp[0].val);}
#line 3133 "parser.tab.c"
    break;

  case 228: /* compound_stmt: try_stmt  */
#line 483 "parser.y"
                        {(yyval.val)=(yyvsp[0].val);}
#line 3139 "parser.tab.c"
    break;

  case 229: /* compound_stmt: funcdef  */
#line 484 "parser.y"
                       {(yyval.val)=(yyvsp[0].val);}
#line 3145 "parser.tab.c"
    break;

  case 230: /* compound_stmt: classdef  */
#line 485 "parser.y"
                        {(yyval.val)=(yyvsp[0].val);}
#line 3151 "parser.tab.c"
    break;

  case 231: /* compound_stmt: dunder_block  */
#line 486 "parser.y"
                            {(yyval.val)=(yyvsp[0].val);}
#line 3157 "parser.tab.c"
    break;

  case 232: /* if_stmt: IF test COLON suite ets_sure ELSE COLON suite  */
#line 489 "parser.y"
                                                        {(yyval.val)=addnode("if_stmt");(yyvsp[-7].val)=addnode(string("IF") );addedge((yyval.val), (yyvsp[-7].val));addedge((yyval.val), (yyvsp[-6].val));(yyvsp[-5].val)=addnode(string("COLON") );addedge((yyval.val), (yyvsp[-5].val));addedge((yyval.val), (yyvsp[-4].val));addedge((yyval.val), (yyvsp[-3].val));(yyvsp[-2].val)=addnode(string("ELSE") );addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("COLON") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3163 "parser.tab.c"
    break;

  case 233: /* if_stmt: IF test COLON suite ELSE COLON suite  */
#line 490 "parser.y"
                                               {(yyval.val)=addnode("if_stmt");(yyvsp[-6].val)=addnode(string("IF") );addedge((yyval.val), (yyvsp[-6].val));addedge((yyval.val), (yyvsp[-5].val));(yyvsp[-4].val)=addnode(string("COLON") );addedge((yyval.val), (yyvsp[-4].val));addedge((yyval.val), (yyvsp[-3].val));(yyvsp[-2].val)=addnode(string("ELSE") );addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("COLON") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3169 "parser.tab.c"
    break;

  case 234: /* if_stmt: IF test COLON suite ets_sure  */
#line 491 "parser.y"
                                       {(yyval.val)=addnode("if_stmt");(yyvsp[-4].val)=addnode(string("IF") );addedge((yyval.val), (yyvsp[-4].val));addedge((yyval.val), (yyvsp[-3].val));(yyvsp[-2].val)=addnode(string("COLON") );addedge((yyval.val), (yyvsp[-2].val));addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3175 "parser.tab.c"
    break;

  case 235: /* if_stmt: IF test COLON suite  */
#line 492 "parser.y"
                              {(yyval.val)=addnode("if_stmt");(yyvsp[-3].val)=addnode(string("IF") );addedge((yyval.val), (yyvsp[-3].val));addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("COLON") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3181 "parser.tab.c"
    break;

  case 236: /* ets: ELIF test COLON suite  */
#line 495 "parser.y"
                          {(yyval.val)=addnode("ets");(yyvsp[-3].val)=addnode(string("ELIF") );addedge((yyval.val), (yyvsp[-3].val));addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("COLON") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3187 "parser.tab.c"
    break;

  case 237: /* ets_sure: ets  */
#line 498 "parser.y"
              {(yyval.val)=(yyvsp[0].val);}
#line 3193 "parser.tab.c"
    break;

  case 238: /* ets_sure: ets_sure ets  */
#line 499 "parser.y"
                       {(yyval.val)=addnode("ets_sure");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3199 "parser.tab.c"
    break;

  case 239: /* suite: simple_stmt  */
#line 502 "parser.y"
                   {(yyval.val)=(yyvsp[0].val);}
#line 3205 "parser.tab.c"
    break;

  case 240: /* suite: n_sure INDENT nns_sure DEDENT  */
#line 503 "parser.y"
                                     {(yyval.val)=addnode("suite");addedge((yyval.val), (yyvsp[-3].val));(yyvsp[-2].val)=addnode(string("INDENT"));addedge((yyval.val), (yyvsp[-2].val));addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("DEDENT") );addedge((yyval.val), (yyvsp[0].val));}
#line 3211 "parser.tab.c"
    break;

  case 241: /* nns: NEWLINE  */
#line 506 "parser.y"
             {(yyval.val)=addnode("nns");(yyvsp[0].val)=addnode(string("NEWLINE") );addedge((yyval.val), (yyvsp[0].val));}
#line 3217 "parser.tab.c"
    break;

  case 242: /* nns: new_stmt  */
#line 507 "parser.y"
              {(yyval.val)=(yyvsp[0].val);}
#line 3223 "parser.tab.c"
    break;

  case 243: /* nns_sure: nns  */
#line 510 "parser.y"
              {(yyval.val)=(yyvsp[0].val);}
#line 3229 "parser.tab.c"
    break;

  case 244: /* nns_sure: nns_sure nns  */
#line 511 "parser.y"
                       {(yyval.val)=addnode("nns_sure");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3235 "parser.tab.c"
    break;

  case 245: /* new_stmt: simple_stmt  */
#line 514 "parser.y"
                       {(yyval.val)=(yyvsp[0].val);}
#line 3241 "parser.tab.c"
    break;

  case 246: /* new_stmt: if_stmt  */
#line 515 "parser.y"
                   {(yyval.val)=(yyvsp[0].val);}
#line 3247 "parser.tab.c"
    break;

  case 247: /* new_stmt: while_stmt  */
#line 516 "parser.y"
                      {(yyval.val)=(yyvsp[0].val);}
#line 3253 "parser.tab.c"
    break;

  case 248: /* new_stmt: for_stmt  */
#line 517 "parser.y"
                    {(yyval.val)=(yyvsp[0].val);}
#line 3259 "parser.tab.c"
    break;

  case 249: /* new_stmt: try_stmt  */
#line 518 "parser.y"
                    {(yyval.val)=(yyvsp[0].val);}
#line 3265 "parser.tab.c"
    break;

  case 250: /* new_stmt: funcdef  */
#line 519 "parser.y"
                   {(yyval.val)=(yyvsp[0].val);}
#line 3271 "parser.tab.c"
    break;

  case 251: /* new_stmt: dunder_block  */
#line 520 "parser.y"
                        {(yyval.val)=(yyvsp[0].val);}
#line 3277 "parser.tab.c"
    break;

  case 252: /* while_stmt: WHILE test COLON suite  */
#line 523 "parser.y"
                                     {(yyval.val)=addnode("while_stmt");(yyvsp[-3].val)=addnode(string("WHILE") );addedge((yyval.val), (yyvsp[-3].val));addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("COLON") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3283 "parser.tab.c"
    break;

  case 253: /* while_stmt: WHILE test COLON suite ELSE COLON suite  */
#line 524 "parser.y"
                                                      {(yyval.val)=addnode("while_stmt");(yyvsp[-6].val)=addnode(string("WHILE") );addedge((yyval.val), (yyvsp[-6].val));addedge((yyval.val), (yyvsp[-5].val));(yyvsp[-4].val)=addnode(string("COLON") );addedge((yyval.val), (yyvsp[-4].val));addedge((yyval.val), (yyvsp[-3].val));(yyvsp[-2].val)=addnode(string("ELSE") );addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("COLON") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3289 "parser.tab.c"
    break;

  case 254: /* for_stmt: FOR exprlist IN testlist COLON suite  */
#line 528 "parser.y"
                                                {(yyval.val)=addnode("for_stmt");(yyvsp[-5].val)=addnode(string("FOR") );addedge((yyval.val), (yyvsp[-5].val));addedge((yyval.val), (yyvsp[-4].val));(yyvsp[-3].val)=addnode(string("IN") );addedge((yyval.val), (yyvsp[-3].val));addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("COLON") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3295 "parser.tab.c"
    break;

  case 255: /* for_stmt: FOR exprlist IN testlist COLON suite ELSE COLON suite  */
#line 529 "parser.y"
                                                                  {(yyval.val)=addnode("for_stmt");(yyvsp[-8].val)=addnode(string("FOR") );addedge((yyval.val), (yyvsp[-8].val));addedge((yyval.val), (yyvsp[-7].val));(yyvsp[-6].val)=addnode(string("IN") );addedge((yyval.val), (yyvsp[-6].val));addedge((yyval.val), (yyvsp[-5].val));(yyvsp[-4].val)=addnode(string("COLON") );addedge((yyval.val), (yyvsp[-4].val));addedge((yyval.val), (yyvsp[-3].val));(yyvsp[-2].val)=addnode(string("ELSE") );addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("COLON") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3301 "parser.tab.c"
    break;

  case 256: /* try_stmt: TRY COLON suite ecs_sure ELSE COLON suite FINALLY COLON suite  */
#line 532 "parser.y"
                                                                           {(yyval.val)=addnode("try_stmt");(yyvsp[-9].val)=addnode(string("TRY") );addedge((yyval.val), (yyvsp[-9].val));(yyvsp[-8].val)=addnode(string("COLON"));addedge((yyval.val), (yyvsp[-8].val));addedge((yyval.val), (yyvsp[-7].val));addedge((yyval.val), (yyvsp[-6].val));(yyvsp[-5].val)=addnode(string("ELSE") );addedge((yyval.val), (yyvsp[-5].val));(yyvsp[-4].val)=addnode(string("COLON") );addedge((yyval.val), (yyvsp[-4].val));addedge((yyval.val), (yyvsp[-3].val));(yyvsp[-2].val)=addnode(string("FINALLY") );addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("COLON") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3307 "parser.tab.c"
    break;

  case 257: /* try_stmt: TRY COLON suite FINALLY COLON suite  */
#line 533 "parser.y"
                                                {(yyval.val)=addnode("try_stmt");(yyvsp[-5].val)=addnode(string("TRY") );addedge((yyval.val), (yyvsp[-5].val));(yyvsp[-4].val)=addnode(string("COLON"));addedge((yyval.val), (yyvsp[-4].val));addedge((yyval.val), (yyvsp[-3].val));(yyvsp[-2].val)=addnode(string("FINALLY") );addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("COLON") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3313 "parser.tab.c"
    break;

  case 258: /* try_stmt: TRY COLON suite ecs_sure ELSE COLON suite  */
#line 534 "parser.y"
                                                      {(yyval.val)=addnode("try_stmt");(yyvsp[-6].val)=addnode(string("TRY") );addedge((yyval.val), (yyvsp[-6].val));(yyvsp[-5].val)=addnode(string("COLON"));addedge((yyval.val), (yyvsp[-5].val));addedge((yyval.val), (yyvsp[-4].val));addedge((yyval.val), (yyvsp[-3].val));(yyvsp[-2].val)=addnode(string("ELSE") );addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("COLON") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3319 "parser.tab.c"
    break;

  case 259: /* try_stmt: TRY COLON suite ecs_sure FINALLY COLON suite  */
#line 535 "parser.y"
                                                         {(yyval.val)=addnode("try_stmt");(yyvsp[-6].val)=addnode(string("TRY") );addedge((yyval.val), (yyvsp[-6].val));(yyvsp[-5].val)=addnode(string("COLON"));addedge((yyval.val), (yyvsp[-5].val));addedge((yyval.val), (yyvsp[-4].val));addedge((yyval.val), (yyvsp[-3].val));(yyvsp[-2].val)=addnode(string("FINALLY") );addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("COLON") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3325 "parser.tab.c"
    break;

  case 260: /* try_stmt: TRY COLON suite ecs_sure  */
#line 536 "parser.y"
                                    {(yyval.val)=addnode("try_stmt");(yyvsp[-3].val)=addnode(string("TRY") );addedge((yyval.val), (yyvsp[-3].val));(yyvsp[-2].val)=addnode(string("COLON"));addedge((yyval.val), (yyvsp[-2].val));addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3331 "parser.tab.c"
    break;

  case 261: /* ecs: except_clause COLON suite  */
#line 540 "parser.y"
                                 {(yyval.val)=addnode("ecs");addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("COLON"));addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3337 "parser.tab.c"
    break;

  case 262: /* except_clause: EXCEPT test AS IDENTIFIER  */
#line 543 "parser.y"
                                         {(yyval.val)=addnode("except_clause");(yyvsp[-3].val)=addnode(string("EXCEPT") );addedge((yyval.val), (yyvsp[-3].val));addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("as") );addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("IDENTIFIER") );addedge((yyval.val), (yyvsp[0].val));}
#line 3343 "parser.tab.c"
    break;

  case 263: /* except_clause: EXCEPT  */
#line 544 "parser.y"
                      {(yyval.val)=addnode("except_clause");(yyvsp[0].val)=addnode(string("EXCEPT") );addedge((yyval.val), (yyvsp[0].val));}
#line 3349 "parser.tab.c"
    break;

  case 264: /* except_clause: EXCEPT test  */
#line 545 "parser.y"
                           {(yyval.val)=addnode("except_clause");(yyvsp[-1].val)=addnode(string("EXCEPT") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3355 "parser.tab.c"
    break;

  case 265: /* ecs_sure: ecs_sure ecs  */
#line 548 "parser.y"
                        {(yyval.val)=addnode("ecs_sure");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3361 "parser.tab.c"
    break;

  case 266: /* ecs_sure: ecs  */
#line 549 "parser.y"
               {(yyval.val)=(yyvsp[0].val);}
#line 3367 "parser.tab.c"
    break;

  case 267: /* funcdef: DEF IDENTIFIER parameters ARROW test COLON suite  */
#line 552 "parser.y"
                                                           {(yyval.val)=addnode("funcdef");(yyvsp[-6].val)=addnode(string("DEF") );addedge((yyval.val), (yyvsp[-6].val));(yyvsp[-5].val)=addnode(string("IDENTIFIER"));addedge((yyval.val), (yyvsp[-5].val));addedge((yyval.val), (yyvsp[-4].val));(yyvsp[-3].val)=addnode(string("ARROW") );addedge((yyval.val), (yyvsp[-3].val));addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("COLON") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3373 "parser.tab.c"
    break;

  case 268: /* funcdef: DEF IDENTIFIER parameters COLON suite  */
#line 553 "parser.y"
                                                {(yyval.val)=addnode("funcdef");(yyvsp[-4].val)=addnode(string("DEF") );addedge((yyval.val), (yyvsp[-4].val));(yyvsp[-3].val)=addnode(string("IDENTIFIER"));addedge((yyval.val), (yyvsp[-3].val));addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("COLON") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3379 "parser.tab.c"
    break;

  case 269: /* funcdef: DEF DUNDER parameters ARROW test COLON suite  */
#line 554 "parser.y"
                                                      {(yyval.val)=addnode("funcdef");(yyvsp[-6].val)=addnode(string("DEF") );addedge((yyval.val), (yyvsp[-6].val));(yyvsp[-5].val)=addnode(string("DUNDER"));addedge((yyval.val), (yyvsp[-5].val));addedge((yyval.val), (yyvsp[-4].val));(yyvsp[-3].val)=addnode(string("ARROW") );addedge((yyval.val), (yyvsp[-3].val));addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("COLON") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3385 "parser.tab.c"
    break;

  case 270: /* funcdef: DEF DUNDER parameters COLON suite  */
#line 555 "parser.y"
                                            {(yyval.val)=addnode("funcdef");(yyvsp[-4].val)=addnode(string("DEF") );addedge((yyval.val), (yyvsp[-4].val));(yyvsp[-3].val)=addnode(string("DUNDER"));addedge((yyval.val), (yyvsp[-3].val));addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("COLON") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3391 "parser.tab.c"
    break;

  case 271: /* parameters: CIROPEN typedargslist CIRCLOSE  */
#line 558 "parser.y"
                                             {(yyval.val)=addnode("parameters");(yyvsp[-2].val)=addnode(string("CIROPEN") );addedge((yyval.val), (yyvsp[-2].val));addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("CIRCLOSE"));addedge((yyval.val), (yyvsp[0].val));}
#line 3397 "parser.tab.c"
    break;

  case 272: /* parameters: CIROPEN CIRCLOSE  */
#line 559 "parser.y"
                               {(yyval.val)=addnode("parameters");(yyvsp[-1].val)=addnode(string("CIROPEN") );addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("CIRCLOSE"));addedge((yyval.val), (yyvsp[0].val));}
#line 3403 "parser.tab.c"
    break;

  case 273: /* typedargslist: tfpdef EQUAL test ctet_sure COMMA  */
#line 562 "parser.y"
                                                {(yyval.val)=addnode("typedargslist");addedge((yyval.val), (yyvsp[-4].val));(yyvsp[-3].val)=addnode(string("EQUAL"));addedge((yyval.val), (yyvsp[-3].val));addedge((yyval.val), (yyvsp[-2].val));addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("COMMA") );addedge((yyval.val), (yyvsp[0].val));}
#line 3409 "parser.tab.c"
    break;

  case 274: /* typedargslist: tfpdef EQUAL test COMMA  */
#line 563 "parser.y"
                                     {(yyval.val)=addnode("typedargslist");addedge((yyval.val), (yyvsp[-3].val));(yyvsp[-2].val)=addnode(string("EQUAL"));addedge((yyval.val), (yyvsp[-2].val));addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("COMMA") );addedge((yyval.val), (yyvsp[0].val));}
#line 3415 "parser.tab.c"
    break;

  case 275: /* typedargslist: tfpdef ctet_sure COMMA  */
#line 564 "parser.y"
                                    {(yyval.val)=addnode("typedargslist");addedge((yyval.val), (yyvsp[-2].val));addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("COMMA") );addedge((yyval.val), (yyvsp[0].val));}
#line 3421 "parser.tab.c"
    break;

  case 276: /* typedargslist: tfpdef COMMA  */
#line 565 "parser.y"
                          {(yyval.val)=addnode("typedargslist");addedge((yyval.val), (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("COMMA"));addedge((yyval.val), (yyvsp[0].val));}
#line 3427 "parser.tab.c"
    break;

  case 277: /* typedargslist: tfpdef EQUAL test ctet_sure  */
#line 566 "parser.y"
                                         {(yyval.val)=addnode("typedargslist");addedge((yyval.val), (yyvsp[-3].val));(yyvsp[-2].val)=addnode(string("EQUAL"));addedge((yyval.val), (yyvsp[-2].val));addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3433 "parser.tab.c"
    break;

  case 278: /* typedargslist: tfpdef EQUAL test  */
#line 567 "parser.y"
                               {(yyval.val)=addnode("typedargslist");addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("EQUAL"));addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3439 "parser.tab.c"
    break;

  case 279: /* typedargslist: tfpdef ctet_sure  */
#line 568 "parser.y"
                              {(yyval.val)=addnode("typedargslist");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3445 "parser.tab.c"
    break;

  case 280: /* typedargslist: tfpdef  */
#line 569 "parser.y"
                    {(yyval.val)=(yyvsp[0].val);}
#line 3451 "parser.tab.c"
    break;

  case 281: /* ctet: COMMA tfpdef EQUAL test  */
#line 572 "parser.y"
                             {(yyval.val)=addnode("ctet");(yyvsp[-3].val)=addnode(string("COMMA") );addedge((yyval.val), (yyvsp[-3].val));addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("EQUAL") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3457 "parser.tab.c"
    break;

  case 282: /* ctet: COMMA tfpdef  */
#line 573 "parser.y"
                   {(yyval.val)=addnode("ctet");(yyvsp[-1].val)=addnode(string("COMMA") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3463 "parser.tab.c"
    break;

  case 283: /* ctet_sure: ctet  */
#line 576 "parser.y"
                {(yyval.val)=(yyvsp[0].val);}
#line 3469 "parser.tab.c"
    break;

  case 284: /* ctet_sure: ctet_sure ctet  */
#line 577 "parser.y"
                          {(yyval.val)=addnode("ctet_sure");addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3475 "parser.tab.c"
    break;

  case 285: /* tfpdef: IDENTIFIER  */
#line 579 "parser.y"
                   {(yyval.val)=addnode("tfpdef");(yyvsp[0].val)=addnode(string("IDENTIFIER") );addedge((yyval.val), (yyvsp[0].val));}
#line 3481 "parser.tab.c"
    break;

  case 286: /* tfpdef: IDENTIFIER COLON test  */
#line 580 "parser.y"
                               {(yyval.val)=addnode("tfpdef");(yyvsp[-2].val)=addnode(string("IDENTIFIER") );addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("COLON"));addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3487 "parser.tab.c"
    break;

  case 287: /* classdef: CLASS IDENTIFIER CIROPEN arglist CIRCLOSE COLON suite  */
#line 583 "parser.y"
                                                                   {(yyval.val)=addnode("classdef");(yyvsp[-6].val)=addnode(string("CLASS") );addedge((yyval.val), (yyvsp[-6].val));(yyvsp[-5].val)=addnode(string("IDENTIFIER"));addedge((yyval.val), (yyvsp[-5].val));(yyvsp[-4].val)=addnode(string("CIROPEN") );addedge((yyval.val), (yyvsp[-4].val));addedge((yyval.val), (yyvsp[-3].val));(yyvsp[-2].val)=addnode(string("CIRCLOSE") );addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("COLON") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3493 "parser.tab.c"
    break;

  case 288: /* classdef: CLASS IDENTIFIER COLON suite  */
#line 584 "parser.y"
                                        {(yyval.val)=addnode("classdef");(yyvsp[-3].val)=addnode(string("CLASS") );addedge((yyval.val), (yyvsp[-3].val));(yyvsp[-2].val)=addnode(string("IDENTIFIER"));addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("COLON") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3499 "parser.tab.c"
    break;

  case 289: /* classdef: CLASS IDENTIFIER CIROPEN CIRCLOSE COLON suite  */
#line 585 "parser.y"
                                                           {(yyval.val)=addnode("classdef");(yyvsp[-5].val)=addnode(string("CLASS") );addedge((yyval.val), (yyvsp[-5].val));(yyvsp[-4].val)=addnode(string("IDENTIFIER"));addedge((yyval.val), (yyvsp[-4].val));(yyvsp[-3].val)=addnode(string("CIROPEN") );addedge((yyval.val), (yyvsp[-3].val));(yyvsp[-2].val)=addnode(string("CIRCLOSE") );addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("COLON") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3505 "parser.tab.c"
    break;

  case 290: /* dunder_block: IF DUNDER EEQ ADUNDER COLON suite  */
#line 588 "parser.y"
                                                 {(yyval.val)=addnode("dunder_block");(yyvsp[-5].val)=addnode(string("IF") );addedge((yyval.val), (yyvsp[-5].val));(yyvsp[-4].val)=addnode(string("DUNDER"));addedge((yyval.val), (yyvsp[-4].val));(yyvsp[-3].val)=addnode(string("EEQ") );addedge((yyval.val), (yyvsp[-3].val));(yyvsp[-2].val)=addnode(string("ADUNDER") );addedge((yyval.val), (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("COLON") );addedge((yyval.val), (yyvsp[-1].val));addedge((yyval.val), (yyvsp[0].val));}
#line 3511 "parser.tab.c"
    break;


#line 3515 "parser.tab.c"

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

#line 593 "parser.y"



void yyerror(const char *s){
    cerr<<"syntax error in line number "<<yylineno<<endl;
    exit(1);
}

int main() {
    indent_stack.push(0);
    yyparse();
    cout << "digraph ASTVisual {\n ordering = out ;\n";
    for(auto e: nodes){
        string s;

         for( auto e1: e.l){
            if(e1=='\"' || e1=='\\'  ){
                s.push_back('\\');
            }
            s.push_back(e1);
        }
        cout<<e.num<<" [ label=\""<<s<<"\"]\n";
    }
    for(auto e: edges){
        string s;

        for( auto e1: e.l){
            if(e1=='\"' || e1=='\\'){
                s.push_back('\\');
            }
            s.push_back(e1);
        }
        cout<<e.a<< " -> "<<e.b << "[ label=\""<<s<<"\"]\n";
    }
    cout << "  }\n";
    return 0;
}

