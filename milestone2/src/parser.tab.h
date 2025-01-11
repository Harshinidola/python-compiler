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
    RETURN = 270,                  /* RETURN  */
    IN = 271,                      /* IN  */
    FINALLY = 272,                 /* FINALLY  */
    GLOBAL = 273,                  /* GLOBAL  */
    EXCEPT = 274,                  /* EXCEPT  */
    AS = 275,                      /* AS  */
    DEF = 276,                     /* DEF  */
    CLASS = 277,                   /* CLASS  */
    ASSERT = 278,                  /* ASSERT  */
    FROM = 279,                    /* FROM  */
    CONTINUE = 280,                /* CONTINUE  */
    BREAK = 281,                   /* BREAK  */
    RAISE = 282,                   /* RAISE  */
    NONE = 283,                    /* NONE  */
    TRUE = 284,                    /* TRUE  */
    FALSE = 285,                   /* FALSE  */
    AND = 286,                     /* AND  */
    NOT = 287,                     /* NOT  */
    OR = 288,                      /* OR  */
    DEL = 289,                     /* DEL  */
    INT = 290,                     /* INT  */
    LISTINT = 291,                 /* LISTINT  */
    LISTFLOAT = 292,               /* LISTFLOAT  */
    LISTSTRING = 293,              /* LISTSTRING  */
    LISTBOOL = 294,                /* LISTBOOL  */
    LIST = 295,                    /* LIST  */
    FLOAT = 296,                   /* FLOAT  */
    STR = 297,                     /* STR  */
    BOOL = 298,                    /* BOOL  */
    IDENTIFIER = 299,              /* IDENTIFIER  */
    DOUBLE_EQUAL = 300,            /* DOUBLE_EQUAL  */
    GREATER_EQUAL = 301,           /* GREATER_EQUAL  */
    LESS_EQUAL = 302,              /* LESS_EQUAL  */
    NOT_EQUAL = 303,               /* NOT_EQUAL  */
    DOUBLE_LESS = 304,             /* DOUBLE_LESS  */
    DOUBLE_GREATER = 305,          /* DOUBLE_GREATER  */
    PLUS_EQUAL = 306,              /* PLUS_EQUAL  */
    MINUS_EQUAL = 307,             /* MINUS_EQUAL  */
    MULTI_EQUAL = 308,             /* MULTI_EQUAL  */
    DIVI_EQUAL = 309,              /* DIVI_EQUAL  */
    DOUBLE_DIVI_EQUAL = 310,       /* DOUBLE_DIVI_EQUAL  */
    MODULO_EQUAL = 311,            /* MODULO_EQUAL  */
    DOUBLE_MULTI_EQUAL = 312,      /* DOUBLE_MULTI_EQUAL  */
    AND_EQUAL = 313,               /* AND_EQUAL  */
    PIPE_EQUAL = 314,              /* PIPE_EQUAL  */
    POWER_EQUAL = 315,             /* POWER_EQUAL  */
    DOUBLE_LESS_EQUAL = 316,       /* DOUBLE_LESS_EQUAL  */
    DOUBLE_GREATER_EQUAL = 317,    /* DOUBLE_GREATER_EQUAL  */
    STRING = 318,                  /* STRING  */
    NUMBER = 319,                  /* NUMBER  */
    FLOAT_NUMBER = 320,            /* FLOAT_NUMBER  */
    IMAGINARY_NUMBER = 321,        /* IMAGINARY_NUMBER  */
    DOUBLE_STAR = 322,             /* DOUBLE_STAR  */
    THREE_DOT = 323,               /* THREE_DOT  */
    GREATER_LESS = 324,            /* GREATER_LESS  */
    ARROW = 325,                   /* ARROW  */
    DOUBLE_SLASH = 326,            /* DOUBLE_SLASH  */
    COLON = 327,                   /* COLON  */
    SEMICOLON = 328,               /* SEMICOLON  */
    PLUS = 329,                    /* PLUS  */
    MINUS = 330,                   /* MINUS  */
    DIVI = 331,                    /* DIVI  */
    EQUAL = 332,                   /* EQUAL  */
    COMMA = 333,                   /* COMMA  */
    PIPE = 334,                    /* PIPE  */
    ANDSYMBOL = 335,               /* ANDSYMBOL  */
    POWER = 336,                   /* POWER  */
    MULTI = 337,                   /* MULTI  */
    MOD = 338,                     /* MOD  */
    NOSYMBOL = 339,                /* NOSYMBOL  */
    CIROPEN = 340,                 /* CIROPEN  */
    CIRCLOSE = 341,                /* CIRCLOSE  */
    SQOPEN = 342,                  /* SQOPEN  */
    SQCLOSE = 343,                 /* SQCLOSE  */
    CUOPEN = 344,                  /* CUOPEN  */
    CUCLOSE = 345,                 /* CUCLOSE  */
    DOT = 346,                     /* DOT  */
    LESS = 347,                    /* LESS  */
    GREATER = 348,                 /* GREATER  */
    ADUNDER = 349                  /* ADUNDER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 876 "parser.y"

  char* val;
  class Info* info;

#line 163 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
