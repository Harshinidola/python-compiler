/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    NEWLINE = 258,                 /* NEWLINE  */
    INDENT = 259,                  /* INDENT  */
    DEDENT = 260,                  /* DEDENT  */
    ENDMARKER = 261,               /* ENDMARKER  */
    DUNDER = 262,                  /* DUNDER  */
    DATATYPE = 263,                /* DATATYPE  */
    IS = 264,                      /* IS  */
    IF = 265,                      /* IF  */
    ELSE = 266,                    /* ELSE  */
    ELIF = 267,                    /* ELIF  */
    WHILE = 268,                   /* WHILE  */
    FOR = 269,                     /* FOR  */
    TRY = 270,                     /* TRY  */
    RETURN = 271,                  /* RETURN  */
    YIELD = 272,                   /* YIELD  */
    IN = 273,                      /* IN  */
    FINALLY = 274,                 /* FINALLY  */
    GLOBAL = 275,                  /* GLOBAL  */
    EXCEPT = 276,                  /* EXCEPT  */
    AS = 277,                      /* AS  */
    DEF = 278,                     /* DEF  */
    CLASS = 279,                   /* CLASS  */
    ASSERT = 280,                  /* ASSERT  */
    FROM = 281,                    /* FROM  */
    CONTINUE = 282,                /* CONTINUE  */
    BREAK = 283,                   /* BREAK  */
    RAISE = 284,                   /* RAISE  */
    NONE = 285,                    /* NONE  */
    TRUE = 286,                    /* TRUE  */
    FALSE = 287,                   /* FALSE  */
    AND = 288,                     /* AND  */
    NOT = 289,                     /* NOT  */
    OR = 290,                      /* OR  */
    DEL = 291,                     /* DEL  */
    INT = 292,                     /* INT  */
    FLOAT = 293,                   /* FLOAT  */
    STR = 294,                     /* STR  */
    BOOL = 295,                    /* BOOL  */
    IDENTIFIER = 296,              /* IDENTIFIER  */
    EEQ = 297,                     /* EEQ  */
    GEQ = 298,                     /* GEQ  */
    LEQ = 299,                     /* LEQ  */
    NEQ = 300,                     /* NEQ  */
    LLT = 301,                     /* LLT  */
    GGT = 302,                     /* GGT  */
    PEQ = 303,                     /* PEQ  */
    MIEQ = 304,                    /* MIEQ  */
    MUEQ = 305,                    /* MUEQ  */
    DEQ = 306,                     /* DEQ  */
    DDEQ = 307,                    /* DDEQ  */
    MOEQ = 308,                    /* MOEQ  */
    MUMUEQ = 309,                  /* MUMUEQ  */
    AEQ = 310,                     /* AEQ  */
    ALEQ = 311,                    /* ALEQ  */
    POEQ = 312,                    /* POEQ  */
    LLEQ = 313,                    /* LLEQ  */
    GGEQ = 314,                    /* GGEQ  */
    STRING = 315,                  /* STRING  */
    NUMBER = 316,                  /* NUMBER  */
    SSTAR = 317,                   /* SSTAR  */
    DDOT = 318,                    /* DDOT  */
    DMOND = 319,                   /* DMOND  */
    ARROW = 320,                   /* ARROW  */
    SSLASH = 321,                  /* SSLASH  */
    COLON = 322,                   /* COLON  */
    SEMICOLON = 323,               /* SEMICOLON  */
    PLUS = 324,                    /* PLUS  */
    MINUS = 325,                   /* MINUS  */
    DIVI = 326,                    /* DIVI  */
    EQUAL = 327,                   /* EQUAL  */
    COMMA = 328,                   /* COMMA  */
    ALTE = 329,                    /* ALTE  */
    AAND = 330,                    /* AAND  */
    POWER = 331,                   /* POWER  */
    MULTI = 332,                   /* MULTI  */
    MOD = 333,                     /* MOD  */
    NOPE = 334,                    /* NOPE  */
    CIROPEN = 335,                 /* CIROPEN  */
    CIRCLOSE = 336,                /* CIRCLOSE  */
    SQOPEN = 337,                  /* SQOPEN  */
    SQCLOSE = 338,                 /* SQCLOSE  */
    CUOPEN = 339,                  /* CUOPEN  */
    CUCLOSE = 340,                 /* CUCLOSE  */
    DOT = 341,                     /* DOT  */
    LT = 342,                      /* LT  */
    GT = 343,                      /* GT  */
    ADUNDER = 344                  /* ADUNDER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 63 "parser.y"

    char* val;

#line 157 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
