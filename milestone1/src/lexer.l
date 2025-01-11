%{
    #include <bits/stdc++.h>
    #include <stack>
    #include "parser.tab.h"
    extern "C" int yylex();
     using namespace std;
    //vector<pair<string,string>> token_lexemes;
    stack<int> indent_stack;
    int dedent_level=0;
    int pig=0;
    char* copyyytext;
    bool in_parenthsis = 0;
    int parenthesis_count1 = 0;
    int parenthesis_count2 = 0;
    int parenthesis_count3 = 0;
    char firstChar;


    //    void print_output(){
    //            //cout<<"TOKEN"<<'\n';
    //            for(auto token_lexeme : token_lexemes){
    //                //cout<<token_lexeme.first<<"     "<<token_lexeme.second<<'\n';
    //            }
    //      }
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
\r?\n      { //token_lexemes.push_back(make_pair("NEWLINE","\n"));
 //cout<<"NEWLINE"<<endl;
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

"(" {parenthesis_count1++;in_parenthsis = 1;/*cout<<"CIROPEN"<<endl*/;return CIROPEN;}
")" {parenthesis_count1--;if(parenthesis_count1  == 0 && parenthesis_count2  == 0 && parenthesis_count3  == 0){in_parenthsis =0;};/*cout<<"CIRCLOSE"<<endl*/;return CIRCLOSE;}

"[" {parenthesis_count2++;in_parenthsis = 1;/*cout<<"SQOPEN"<<endl*/;return SQOPEN;}
"]" {parenthesis_count2--;if(parenthesis_count1  == 0 && parenthesis_count2  == 0 && parenthesis_count3  == 0){in_parenthsis =0;};/*cout<<"SQCLOSE"<<endl*/;return SQCLOSE;}

"{" {parenthesis_count3++;in_parenthsis = 1;/*cout<<"CUOPEN"<<endl*/;return CUOPEN;}
"}" {parenthesis_count3--;if(parenthesis_count1  == 0 && parenthesis_count2  == 0 && parenthesis_count3  == 0){in_parenthsis =0;};/*cout<<"CUCLOSE"<<endl*/;return CUCLOSE;}




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
                 //cout<<"ENDMARKER"<<endl;
                 return ENDMARKER;
                }
        }

[ \t]

{DUNDER} { //token_lexemes.push_back(make_pair("DUNDER",yytext));
//cout<<"DUNDER"<<endl;
return DUNDER;
}
{ADUNDER}|{ADUNDER1}|{ADUNDER2} { //token_lexemes.push_back(make_pair("DUNDER",yytext));
//cout<<"ADUNDER"<<endl;
return ADUNDER;
}

int|float|str|bool {
         //token_lexemes.push_back(make_pair("DATATYPE",yytext));
         //cout<<"DATATYpe"<<endl;
        return IDENTIFIER;
        }

is {
         //token_lexemes.push_back(make_pair("IS",yytext));
         //cout<<"IS"<<endl;
        return IS;
        }
if {
         //token_lexemes.push_back(make_pair("IF",yytext));
         //cout<<"IF"<<endl;
        return IF;
        }
elif {
         //token_lexemes.push_back(make_pair("ELIF",yytext));
          //cout<<"ELIF"<<endl;
        return ELIF;
        }
else {
        //token_lexemes.push_back(make_pair("ELSE",yytext));
        //cout<<"ELSE"<<endl;
       return ELSE;
       }
while {
         //token_lexemes.push_back(make_pair("WHILE",yytext));
         //cout<<"WHILe"<<endl;
        return WHILE;
        }
for {
         //token_lexemes.push_back(make_pair("FOR",yytext));
         //cout<<"FOR"<<endl;
        return FOR;
        }
try {
         //token_lexemes.push_back(make_pair("TRY",yytext));
         //cout<<"TRY"<<endl;
        return TRY;
        }
return {
         //token_lexemes.push_back(make_pair(" return",yytext));
         //cout<<"RETURN"<<endl;
        return  RETURN;
        }
yield {
         //token_lexemes.push_back(make_pair("YIELD",yytext));
         //cout<<"YIELD"<<endl;
        return YIELD;
        }
in  {
         //token_lexemes.push_back(make_pair("IN",yytext));
         //cout<<"IN"<<endl;
        return IN;
        }
finally {
         //token_lexemes.push_back(make_pair("FINALLY",yytext));
         //cout<<"FINALLY"<<endl;
        return FINALLY;
        }
global {
         //token_lexemes.push_back(make_pair("GLOBAL",yytext));
         //cout<<"GLOBAL"<<endl;
        return GLOBAL;
        }
except {
         //token_lexemes.push_back(make_pair("EXCEPT",yytext));
         //cout<<"EXCEPT"<<endl;
        return EXCEPT;
        }
as {
         //token_lexemes.push_back(make_pair("AS",yytext));
         //cout<<"AS"<<endl;
        return AS;
        }
def {
         //token_lexemes.push_back(make_pair("DEF",yytext));
         //cout<<"DEF"<<endl;
        return DEF;
        }
class {
         //token_lexemes.push_back(make_pair("CLASS",yytext));
         //cout<<"CLASS"<<endl;
        return CLASS;
        }
assert {
         //token_lexemes.push_back(make_pair("ASSERT",yytext));
         //cout<<"ASSERT"<<endl;
        return ASSERT;
        }
from {
         //token_lexemes.push_back(make_pair("FROM",yytext));
         //cout<<"FROM"<<endl;
        return FROM;
        }
continue {
         //token_lexemes.push_back(make_pair("CONTINUE",yytext));
         //cout<<"CONTINUE"<<endl;
        return CONTINUE;
        }
break {
         //token_lexemes.push_back(make_pair("BREAK",yytext));
         //cout<<"BREAK"<<endl;
        return BREAK;
        }
raise {
         //token_lexemes.push_back(make_pair("RAISE",yytext));
         //cout<<"RAISE"<<endl;
        return RAISE;
        }
None {
         //token_lexemes.push_back(make_pair("NONE",yytext));
         //cout<<"NONE"<<endl;
        return NONE;
        }
True {
         //token_lexemes.push_back(make_pair("TRUE",yytext));
         //cout<<"TRUE"<<endl;
        return TRUE;
        }
False {
         //token_lexemes.push_back(make_pair("FALSE",yytext));
         //cout<<"FALSE"<<endl;
        return FALSE;
        }
and  {
         //token_lexemes.push_back(make_pair("AND",yytext));
         //cout<<"AND"<<endl;
        return AND;
        }
not  {
         //token_lexemes.push_back(make_pair("NOT",yytext));
         //cout<<"NOT"<<endl;
        return NOT;
        }
or  {
         //token_lexemes.push_back(make_pair("OR",yytext));
         //cout<<"OR"<<endl;
        return OR;
        }
del  {
         //token_lexemes.push_back(make_pair("DEL",yytext));
         //cout<<"DEL"<<endl;
        return DEL;
        }

[a-zA-Z_][a-zA-Z0-9_]*  {
                 //token_lexemes.push_back(make_pair("IDENTIFIER",yytext));
                 //cout<<"IDENTIFIER"<<endl;
                return IDENTIFIER;
              }

":" {
    //token_lexemes.push_back(make_pair("COLON",yytext));
    //cout<<"COLON"<<endl;
    return COLON;
}
";" {
    //token_lexemes.push_back(make_pair("SEMICOLON",yytext));
    //cout<<"SEMICOLON"<<endl;
    return SEMICOLON;
}
"+" {
    //token_lexemes.push_back(make_pair("PLUS",yytext));
    //cout<<" PLUS"<<endl;
    return PLUS;
}
"-" {
    //token_lexemes.push_back(make_pair("MINUS",yytext));
    //cout<<" MINUS"<<endl;
    return MINUS;
}
"=" {
    //token_lexemes.push_back(make_pair("EQUAL",yytext));
    //cout<<"EQUAL"<<endl;
    return EQUAL;
}
"/" {
    //token_lexemes.push_back(make_pair("DIVI",yytext));
    //cout<<"DIVI"<<endl;
    return DIVI;
}
"," {
    //token_lexemes.push_back(make_pair("COMMA",yytext));
    //cout<<"COMMA"<<endl;
    return COMMA;
}
"|" {
    //token_lexemes.push_back(make_pair("ALTE",yytext));
    //cout<<"ALTE"<<endl;
    return ALTE;
}
"&" {
    //token_lexemes.push_back(make_pair("AAND",yytext));
    //cout<<"AAND"<<endl;
    return AAND;
}
"^" {
    //token_lexemes.push_back(make_pair("POWER",yytext));
    //cout<<"POWER"<<endl;
    return POWER;
}
"*" {
    //token_lexemes.push_back(make_pair("MULTI",yytext));
    //cout<<"MULTI"<<endl;
    return MULTI;
}
"%" {
    //token_lexemes.push_back(make_pair("MOD",yytext));
    //cout<<"MOD"<<endl;
    return MOD;
}
"~" {
    //token_lexemes.push_back(make_pair("NOPE",yytext));
    //cout<<"NOPE"<<endl;
    return NOPE;
}
"." {
    //token_lexemes.push_back(make_pair("DOT",yytext));
    //cout<<"DOT"<<endl;
    return DOT;
}
"==" {
     //token_lexemes.push_back(make_pair("EEQ",yytext));
     //cout<<"EEQ"<<endl;
    return EEQ;
}
">=" {
     //token_lexemes.push_back(make_pair("GEQ",yytext));
     //cout<<"LEQ"<<endl;
    return GEQ;
}
"<=" {
     //token_lexemes.push_back(make_pair("LEQ",yytext));
     //cout<<"GEQ"<<endl;
    return LEQ;
}
"!=" {
     //token_lexemes.push_back(make_pair("NEQ",yytext));
     //cout<<"NEQ"<<endl;
    return NEQ;
}

">" {
         //token_lexemes.push_back(make_pair("GT",yytext));
         //cout<<"GT"<<endl;
        return GT;
    }
"<" {
         //token_lexemes.push_back(make_pair("LT",yytext));
         //cout<<"LT"<<endl;
        return LT;
    }

"<<" {
     //token_lexemes.push_back(make_pair("LLT",yytext));
     //cout<<"LLT"<<endl;
    return LLT;
}
">>" {
     //token_lexemes.push_back(make_pair("GGT",yytext));
     //cout<<"GGT"<<endl;
    return GGT;
}
"//" {
     //token_lexemes.push_back(make_pair("SSLASH",yytext));
     //cout<<"SSLASH"<<endl;
    return SSLASH;
}
"**" {
     //token_lexemes.push_back(make_pair("SSTAR",yytext));
     //cout<<"SSTAR"<<endl;
    return SSTAR;
}
"+=" {
     //token_lexemes.push_back(make_pair("PEQ",yytext));
     //cout<<"PEQ"<<endl;
    return PEQ;
}
"-=" {
     //token_lexemes.push_back(make_pair("MIEQ",yytext));
     //cout<<"MIEQ"<<endl;
    return MIEQ;
}
"*=" {
     //token_lexemes.push_back(make_pair("MUEQ",yytext));
     //cout<<"MUEQ"<<endl;
    return MUEQ;
}
"/=" {
     //token_lexemes.push_back(make_pair("DEQ",yytext));
     //cout<<"DEQ"<<endl;
    return DEQ;
}
"//=" {
     //token_lexemes.push_back(make_pair("DDEQ",yytext));
     //cout<<"DDEQ"<<endl;
    return DDEQ;
}
"%=" {
     //token_lexemes.push_back(make_pair("MOEQ",yytext));
     //cout<<"MOEQ"<<endl;
    return MOEQ;
}
"**=" {
     //token_lexemes.push_back(make_pair("MUMUEQ",yytext));
     //cout<<"MUMUEQ"<<endl;
    return MUMUEQ;
}
"&=" {
     //token_lexemes.push_back(make_pair("AEQ",yytext));
     //cout<<"AEQ"<<endl;
    return AEQ;
}
"|=" {
     //token_lexemes.push_back(make_pair("ALEQ",yytext));
     //cout<<"ALEQ"<<endl;
    return ALEQ;
}
"^=" {
     //token_lexemes.push_back(make_pair("POEQ",yytext));
     //cout<<"POEQ"<<endl;
    return POEQ;
}
"<<=" {
     //token_lexemes.push_back(make_pair("LLEQ",yytext));
     //cout<<"LLEQ"<<endl;
    return LLEQ;
}
">>=" {
     //token_lexemes.push_back(make_pair("GGEQ",yytext));
     //cout<<"GGEQ"<<endl;
    return GGEQ;
}
"..." {
     //token_lexemes.push_back(make_pair("DDOT",yytext));
     //cout<<"DDOT"<<endl;
    return DDOT;
}
"<>" {
     //token_lexemes.push_back(make_pair("DMOND",yytext));
     //cout<<"DMOND"<<endl;
    return DMOND;
}
"->" {
     //token_lexemes.push_back(make_pair("ARROW",yytext));
     //cout<<"ARROW"<<endl;
    return ARROW;
}

{stringliteral} { //token_lexemes.push_back(make_pair("STRING",yytext));
//cout<<"STRING"<<endl;
return STRING;
}

{byteliteral} { //token_lexemes.push_back(make_pair("BYTESTRING",yytext));
//cout<<"STRING"<<endl;
return STRING;
}


{errorbyteorstring} {cerr<<"Invalid String at line no: "<<yylineno<<"  at "<<yytext<<'\n';
            //print_output();
            exit(1);
            }

{integer} { //token_lexemes.push_back(make_pair("INTEGER",yytext));
//cout<<"INTEGER"<<endl;
return NUMBER;
}

{floatnumber} { //token_lexemes.push_back(make_pair("FLOATING",yytext));
//cout<<"FLOAT"<<endl;
return NUMBER;
}

{imagnumber} { //token_lexemes.push_back(make_pair("IMAGINARY",yytext));
//cout<<"INUMBER"<<endl;
return NUMBER;
}

[0-9][a-zA-Z0-9_]*  {cerr<<"Invalid Literal at line no: "<<yylineno<<"  at "<<yytext<<'\n';
            //print_output();
            exit(1);
            }

0+{integer} {cerr<<"Leading zeroes at line no: "<<yylineno<<"  at "<<yytext<<'\n';
            //print_output();
            exit(1);
            }


"$"|"?"|"`" {cerr<<"UnconditionalError at line no: "<<yylineno<<"  at "<<yytext<<'\n';
            //print_output();
            exit(1);}

.           {
              cerr << "Unrecognized token on line " << yylineno << ": "
                << yytext << '\n';
              //print_output();
              exit(1);
            }
%%






