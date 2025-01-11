%{
    #include <bits/stdc++.h>
    #include <stack>
    #include "parser.tab.h"
    extern "C" int yylex();
     using namespace std;
    stack<int> indent_stack;
    int dedent_level=0;
    int pig=0;
    char* copyyytext;
    bool in_parenthsis = 0;
    int parenthesis_count1 = 0;
    int parenthesis_count2 = 0;
    int parenthesis_count3 = 0;
    char firstChar;



%}

%option noyywrap yylineno
%x DEDENTATION

DUNDER "__name__"|"__main__"|"__init__"
ADUNDER ["]__main__["]
ADUNDER1 ["]__name__["]
ADUNDER2 ["]__init__["]



digit [0-9]
nonzerodigit [1-9]
bindigit [0-1]
octdigit [0-7]
hexdigit digit|[a-fA-F]
bininteger "0"("b"|"B")(["_"]|{bindigit})+
octinteger "0"("o"|"O")(["_"]|{octdigit})+
hexinteger "0"("x"|"X")(["_"]|{hexdigit})+
decinteger {nonzerodigit}(["_"]|{digit})*|("0"+)(["_"]|"0")*
integer {decinteger}|{bininteger}|{octinteger}|{hexinteger}

digitpart {digit}(["_"]|{digit})*
fraction  "."{digitpart}
exponent  [eE][+-]?{digitpart}
pointfloat ({digitpart})({fraction}|{digitpart}".")
exponentfloat ({digitpart}|{pointfloat}){exponent}
floatnumber  {pointfloat}|{exponentfloat}

imagnumber  ({floatnumber}|{digitpart})[jJ]


shortstringchar [^\\\n'\"]
longstringchar  [^\\]
stringescapeseq \\.
shortstringitem {shortstringchar}|{stringescapeseq}
longstringitem  {longstringchar}|{stringescapeseq}
shortstring     [']{shortstringitem}*[']|["]{shortstringitem}*["]
longstring      '''{longstringitem}*'''|\"\"\"{longstringitem}*\"\"\"
stringprefix    "r"|"u"|"R"|"U"
stringliteral   {stringprefix}?({shortstring}|{longstring})

shortbytechar [^\\\n'\"]
longbytechar  [^\\'\"]
byteescapeseq \\.
shortbyteitem {shortbytechar}|{byteescapeseq}
longbyteitem  {longbytechar}|{byteescapeseq}
shortbyte     '{shortbyteitem}*'|\"{shortbyteitem}*\"
longbyte      '''{longbyteitem}*'''|\"\"\"{longbyteitem}*\"\"\"
byteprefix    "b"|"B"|"br"|"Br"|"bR"|"BR"|"rb"|"rB"|"Rb"|"RB"
byteliteral   {byteprefix}({shortbyte}|{longbyte})
errorbyteorstring     ['\"]+({shortbyteitem}*|{longbyteitem}*)['\"]+



%%
\r?\n      {
 return NEWLINE;
}
^[ \t]*\r?\n  {/*skip blank lines*/}
^[ \t]*#.*\r?\n {/*skip whole line comments*/}
#.*\n
#.*$  { /* Skip comments on the same line as a statement. */ }


\\[ \t]*\n

\\[ \t]*#.*\n {cerr<<"Comment not allowed after explicit line joining, at line no: "<<yylineno<<"  at "<<yytext<<'\n';
            exit(1);
            }

"(" {parenthesis_count1++;in_parenthsis = 1;/*cout<<"CIROPEN"<<endl*/;yylval.val = strdup(yytext);return CIROPEN;}
")" {parenthesis_count1--;if(parenthesis_count1  == 0 && parenthesis_count2  == 0 && parenthesis_count3  == 0){in_parenthsis =0;};/*cout<<"CIRCLOSE"<<endl*/;yylval.val = strdup(yytext);return CIRCLOSE;}

"[" {parenthesis_count2++;in_parenthsis = 1;/*cout<<"SQOPEN"<<endl*/;yylval.val = strdup(yytext);return SQOPEN;}
"]" {parenthesis_count2--;if(parenthesis_count1  == 0 && parenthesis_count2  == 0 && parenthesis_count3  == 0){in_parenthsis =0;};/*cout<<"SQCLOSE"<<endl*/;yylval.val = strdup(yytext);return SQCLOSE;}

"{" {parenthesis_count3++;in_parenthsis = 1;/*cout<<"CUOPEN"<<endl*/;yylval.val = strdup(yytext);return CUOPEN;}
"}" {parenthesis_count3--;if(parenthesis_count1  == 0 && parenthesis_count2  == 0 && parenthesis_count3  == 0){in_parenthsis =0;};/*cout<<"CUCLOSE"<<endl*/;yylval.val = strdup(yytext);return CUCLOSE;}




^[^ \t\n]+ {
    //cout<<"first"<<indent_stack.top()<<yyleng<<endl;
    if (indent_stack.top()!= 0){
        //cout<<"first if"<<indent_stack.top()<<yyleng<<endl;
        copyyytext=strdup(yytext);
        firstChar = yytext[0];
        unput(yytext[0]);
        BEGIN(DEDENTATION);
    }
    else
    {   //cout<<"first else"<<indent_stack.top()<<yyleng<<endl;
        REJECT;
    }
}

^[ \t]+  {
    //cout<<"second"<<indent_stack.top()<<yyleng<<endl;
    if (indent_stack.top() < yyleng) {
        //cout<<"second if"<<indent_stack.top()<<yyleng<<endl;
        indent_stack.push(yyleng);
        //cout<<"INDENT"<<endl;
        yylval.val = strdup(yytext);
        return INDENT;
    } else if (indent_stack.top() > yyleng) {
        //cout<<"second else"<<indent_stack.top()<<yyleng<<endl;
        dedent_level=yyleng;
        unput(32);/*32 for space*/
        BEGIN(DEDENTATION);
    }
}


<DEDENTATION>[ ] {
        //cout<<"DE first"<<indent_stack.top()<<yyleng<<endl;
        if (!indent_stack.empty() && indent_stack.top() != dedent_level) {
            //cout<<"DE first if"<<indent_stack.top()<<yyleng<<endl;
            indent_stack.pop();
            //cout<<"DEDENT"<<endl;
            unput(32);
            yylval.val = strdup(yytext);
            return DEDENT;

        }
        else
        {   //cout<<"DE first else"<<indent_stack.top()<<yyleng<<endl;
            dedent_level=0;
            BEGIN(INITIAL);
        }

        if (indent_stack.empty()) {
            fprintf(stderr, "Error: Incorrect indentation on line %d\n", yylineno);
            exit(1);
        }
}

<DEDENTATION>[^ \t\n] {
    //cout<<"DE second"<<indent_stack.top()<<yyleng<<endl;
    if (indent_stack.top() != 0) {
        //cout<<"DE second if"<<indent_stack.top()<<yyleng<<endl;
        indent_stack.pop();
        unput(yytext[0]);
       //cout<<"DEDENT"<<endl;
       yylval.val = strdup(yytext);
        return DEDENT;
    }
    else
    {   //cout<<"De second else"<<indent_stack.top()<<yyleng<<endl;
        if(copyyytext!=NULL){
        for (int i = strlen(copyyytext) - 1; i >= 0; i--) {
            unput(copyyytext[i]);
        }
        }
    BEGIN(INITIAL);
    }

}


<<EOF>> {
            //cout<<"efirst"<<indent_stack.top()<<yyleng<<endl;
           if (indent_stack.top()!= 0){
               //cout<<"efirst if"<<indent_stack.top()<<yyleng<<endl;
               copyyytext=NULL;
               firstChar = yytext[0];
              unput(yytext[0]);
              BEGIN(DEDENTATION);
            }
            else{
                yylval.val = strdup(yytext);
                return ENDMARKER;
                }
        }

[ \t]

{DUNDER} {
yylval.val = strdup(yytext);
return DUNDER;
}
{ADUNDER}|{ADUNDER1}|{ADUNDER2} {
yylval.val = strdup(yytext);
return ADUNDER;
}

int {
    yylval.val = strdup(yytext);
    return INT;
    }
list"["int"]" {
    yylval.val = strdup(yytext);
    return LISTINT;
    }
list"["float"]" {
    yylval.val = strdup(yytext);
    return LISTFLOAT;
    }
list"["string"]" {
    yylval.val = strdup(yytext);
    return LISTSTRING;
    }
list"["bool"]" {
    yylval.val = strdup(yytext);
    return LISTBOOL;
    }
list {
    yylval.val = strdup(yytext);
    return LIST;
    }
float {
    yylval.val = strdup(yytext);
    return FLOAT;
    }
str {
    yylval.val = strdup(yytext);
    return STR;
    }
bool {
    yylval.val = strdup(yytext);
    return BOOL;
    }

is { yylval.val = strdup(yytext);
        return IS;
        }
if { yylval.val = strdup(yytext);
        return IF;
        }
elif { yylval.val = strdup(yytext);
        return ELIF;
        }
else { yylval.val = strdup(yytext);
       return ELSE;
       }
while { yylval.val = strdup(yytext);
        return WHILE;
        }
for { yylval.val = strdup(yytext);
        return FOR;
        }
return { yylval.val = strdup(yytext);
        return  RETURN;
        }
in  { yylval.val = strdup(yytext);
        return IN;
        }
finally { yylval.val = strdup(yytext);
        return FINALLY;
        }
global { yylval.val = strdup(yytext);
        return GLOBAL;
        }
as { yylval.val = strdup(yytext);
    return AS;
    }
def { yylval.val = strdup(yytext);
        return DEF;
        }
class { yylval.val = strdup(yytext);
        return CLASS;
        }
assert { yylval.val = strdup(yytext);
        return ASSERT;
        }
from { yylval.val = strdup(yytext);
        return FROM;
        }
continue { yylval.val = strdup(yytext);
        return CONTINUE;
        }
break { yylval.val = strdup(yytext);
        return BREAK;
        }
raise { yylval.val = strdup(yytext);
        return RAISE;
        }
None { yylval.val = strdup(yytext);
        return NONE;
        }
True { yylval.val = strdup(yytext);
        return TRUE;
        }
False { yylval.val = strdup(yytext);
        return FALSE;
        }
and  { yylval.val = strdup(yytext);
        return AND;
        }
not  { yylval.val = strdup(yytext);
        return NOT;
        }
or  { yylval.val = strdup(yytext);
        return OR;
        }
del  { yylval.val = strdup(yytext);
        return DEL;
        }

[a-zA-Z_][a-zA-Z0-9_]*  { yylval.val = strdup(yytext);
                return IDENTIFIER;
              }

":" { yylval.val = strdup(yytext);
    return COLON;
}
";" { yylval.val = strdup(yytext);
    return SEMICOLON;
}
"+" { yylval.val = strdup(yytext);
    return PLUS;
}
"-" { yylval.val = strdup(yytext);
    return MINUS;
}
"=" { yylval.val = strdup(yytext);
    return EQUAL;
}
"/" { yylval.val = strdup(yytext);
    return DIVI;
}
"," { yylval.val = strdup(yytext);
    return COMMA;
}
"|" { yylval.val = strdup(yytext);
    return PIPE;
}
"&" { yylval.val = strdup(yytext);
    return ANDSYMBOL;
}
"^" { yylval.val = strdup(yytext);
    return POWER;
}
"*" { yylval.val = strdup(yytext);
    return MULTI;
}
"%" { yylval.val = strdup(yytext);
    return MOD;
}
"~" {
    yylval.val = strdup(yytext); return NOSYMBOL;
}
"." {
    yylval.val = strdup(yytext); return DOT;
}
"==" {
    yylval.val = strdup(yytext); return DOUBLE_EQUAL;
}
">=" {
    yylval.val = strdup(yytext); return GREATER_EQUAL;
}
"<=" {
    yylval.val = strdup(yytext); return LESS_EQUAL;
}
"!=" {
    yylval.val = strdup(yytext); return NOT_EQUAL;
}

">" {
        yylval.val = strdup(yytext); return GREATER;
    }
"<" {
        yylval.val = strdup(yytext); return LESS;
    }

"<<" {
    yylval.val = strdup(yytext); return DOUBLE_LESS;
}
">>" {
    yylval.val = strdup(yytext); return DOUBLE_GREATER;
}
"//" {
    yylval.val = strdup(yytext); return DOUBLE_SLASH;
}
"**" {
    yylval.val = strdup(yytext); return DOUBLE_STAR;
}
"+=" {
    yylval.val = strdup(yytext); return PLUS_EQUAL;
}
"-=" {
    yylval.val = strdup(yytext); return MINUS_EQUAL;
}
"*=" {
    yylval.val = strdup(yytext); return MULTI_EQUAL;
}
"/=" {
    yylval.val = strdup(yytext); return DIVI_EQUAL;
}
"//=" {
    yylval.val = strdup(yytext); return DOUBLE_DIVI_EQUAL;
}
"%=" {
    yylval.val = strdup(yytext); return MODULO_EQUAL;
}
"**=" {
    yylval.val = strdup(yytext); return DOUBLE_MULTI_EQUAL;
}
"&=" {
    yylval.val = strdup(yytext); return AND_EQUAL;
}
"|=" {
    yylval.val = strdup(yytext); return PIPE_EQUAL;
}
"^=" {
    yylval.val = strdup(yytext); return POWER_EQUAL;
}
"<<=" {
    yylval.val = strdup(yytext); return DOUBLE_LESS_EQUAL;
}
">>=" {
    yylval.val = strdup(yytext); return DOUBLE_GREATER_EQUAL;
}
"..." {
    yylval.val = strdup(yytext); return THREE_DOT;
}
"<>" {
    yylval.val = strdup(yytext); return GREATER_LESS;
}
"->" {
    yylval.val = strdup(yytext); return ARROW;
}

{stringliteral} {
yylval.val = strdup(yytext); return STRING;
}

{byteliteral} {
yylval.val = strdup(yytext); return STRING;
}


{errorbyteorstring} {cerr<<"Invalid String at line no: "<<yylineno<<"  at "<<yytext<<'\n';
            exit(1);
            }

{integer} {
yylval.val = strdup(yytext); return NUMBER;
}

{floatnumber} {
yylval.val = strdup(yytext); return FLOAT_NUMBER;
}

{imagnumber} {
yylval.val = strdup(yytext); return IMAGINARY_NUMBER;
}

[0-9][a-zA-Z0-9_]*  {cerr<<"Invalid Literal at line no: "<<yylineno<<"  at "<<yytext<<'\n';
            exit(1);
            }

0+{integer} {cerr<<"Leading zeroes at line no: "<<yylineno<<"  at "<<yytext<<'\n';
            exit(1);
            }


"$"|"?"|"`" {cerr<<"UnconditionalError at line no: "<<yylineno<<"  at "<<yytext<<'\n';
            exit(1);}

.           {
              cerr << "Unrecognized token on line " << yylineno << ": "
                << yytext << '\n';
              exit(1);
            }
%%







