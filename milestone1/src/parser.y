%{
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
%}
%union{
    char* val;
}
%start starting

%type<val> starting file_input ns ns_sure stmt n_sure simple_stmt smlst smlst_sure small_stmt expr_stmt yetse yetse_sure testlist_star_expr tse tse_sure test or_test oat oat_sure and_test ant ant_sure not_test comparison coe coe_sure expr xe xe_sure xor_expr ae ae_sure and_expr se se_sure shift_expr bae bae_sure arith_expr pmterm pmterm_sure term sfac sfac_sure factor power atom_expr trailer_sure atom yield_expr yield_arg testlist ct ct_sure testlist_comp comp_for exprlist cese cese_sure comp_iter comp_if test_nocond string_sure trailer arglist ca ca_sure argument subscriptlist csubs csubs_sure subscript comp_op annassign augassign flow_stmt break_stmt continue_stmt return_stmt raise_stmt yield_stmt global_stmt cn cn_sure assert_stmt compound_stmt if_stmt ets ets_sure suite nns nns_sure new_stmt while_stmt for_stmt try_stmt ecs ecs_sure except_clause funcdef parameters typedargslist ctet ctet_sure tfpdef classdef dunder_block
%token<val> NEWLINE INDENT DEDENT ENDMARKER DUNDER DATATYPE IS IF ELSE ELIF WHILE FOR TRY RETURN YIELD IN FINALLY GLOBAL EXCEPT AS DEF CLASS ASSERT FROM CONTINUE BREAK RAISE NONE TRUE FALSE AND NOT OR DEL INT FLOAT STR BOOL IDENTIFIER EEQ GEQ LEQ NEQ LLT GGT PEQ MIEQ MUEQ DEQ DDEQ MOEQ MUMUEQ AEQ ALEQ POEQ LLEQ GGEQ  STRING NUMBER SSTAR DDOT DMOND ARROW SSLASH COLON SEMICOLON PLUS MINUS DIVI EQUAL COMMA ALTE AAND POWER MULTI MOD NOPE CIROPEN CIRCLOSE SQOPEN SQCLOSE CUOPEN CUCLOSE DOT LT GT ADUNDER
%right NEWLINE
%nonassoc EQUAL



%%




/*starting*/
starting: file_input {$$=addnode("starting");addedge($$, $1);return 0;}
        ;

file_input: ns_sure ENDMARKER {$$=addnode("file_input");addedge($$, $1);}
          | ENDMARKER {$$=addnode("file_input");$1=addnode(string("ENDMARKER") );addedge($$, $1);}
          ;

ns_sure:ns {$$= $1;}
       |ns_sure ns {$$=addnode("ns_sure");addedge($$, $1);addedge($$, $2);}
       ;

ns: NEWLINE {$$=addnode("NEWLINE");$1=addnode(string("newline") );addedge($$, $1);}
   | stmt {$$= $1;}
   ;

n_sure: NEWLINE {$$=addnode("NEWLINE");$1=addnode(string("newline") );addedge($$, $1);}
      | n_sure NEWLINE {$$=addnode("n_sure");addedge($$, $1);$2=addnode(string("NEWLINE"));addedge($$, $2);}
      ;


stmt: simple_stmt {$$= $1;}
     | compound_stmt {$$= $1;}
     ;

simple_stmt: small_stmt smlst_sure NEWLINE {$$=addnode("simple_stmt");addedge($$, $1);addedge($$, $2);$3=addnode(string("NEWLINE") );addedge($$, $3);}
           | small_stmt smlst_sure SEMICOLON NEWLINE {$$=addnode("simple_stmt");addedge($$, $1);addedge($$, $2);$3=addnode(string("SEMICOLON") );addedge($$, $3);$4=addnode(string("NEWLINE") );addedge($$, $4);}
           | small_stmt NEWLINE {$$=addnode("simple_stmt");addedge($$, $1);$2=addnode(string("NEWLINE"));addedge($$, $2);}
           | small_stmt SEMICOLON NEWLINE {$$=addnode("simple_stmt");addedge($$, $1);$2=addnode(string("SEMICOLON"));addedge($$, $2);$3=addnode(string("NEWLINE") );addedge($$, $3);}
           ;

smlst: SEMICOLON small_stmt {$$=addnode("smlst");$1=addnode(string("SEMICOLON") );addedge($$, $1);addedge($$, $2);}
     ;

smlst_sure: smlst {$$=$1;}
          | smlst_sure smlst {$$=addnode("smlst_sure");addedge($$, $1);addedge($$, $2);}
          ;

small_stmt: expr_stmt {$$=$1;}
          | flow_stmt {$$=$1;}
          | global_stmt {$$=$1;}
          | assert_stmt {$$=$1;}
          ;

expr_stmt: testlist_star_expr annassign {$$=addnode("expr_stmt");addedge($$, $1);addedge($$, $2);}
         | testlist_star_expr augassign yield_expr {$$=addnode("expr_stmt");addedge($$, $1);addedge($$, $2);addedge($$, $3);}
         | testlist_star_expr augassign testlist {$$=addnode("expr_stmt");addedge($$, $1);addedge($$, $2);addedge($$, $3);}
         | testlist_star_expr yetse_sure {$$=addnode("expr_stmt");addedge($$, $1);addedge($$, $2);}
         | testlist_star_expr {$$=$1;}
         ;

yetse : EQUAL yield_expr {$$=addnode("yetse");$1=addnode(string("EQUAL") );addedge($$, $1);addedge($$, $2);}
      | EQUAL testlist_star_expr {$$=addnode("yetse");$1=addnode(string("EQUAL") );addedge($$, $1);addedge($$, $2);}
      ;

yetse_sure : yetse {$$=$1;}
           | yetse_sure yetse {$$=addnode("yetse_sure");addedge($$, $1);addedge($$, $2);}
           ;

testlist_star_expr: test tse_sure {$$=addnode("testlist_star_expr");addedge($$, $1);addedge($$, $2);}
                  | test {$$=$1;}
                  | test tse_sure COMMA {$$=addnode("testlist_star_expr");addedge($$, $1);addedge($$, $2);$3=addnode(string("COMMA") );addedge($$, $3);}
                  | test COMMA {$$=addnode("testlist_star_expr");addedge($$, $1);$2=addnode(string("COMMA"));addedge($$, $2);}
                  ;

tse: COMMA test {$$=addnode("tse");$1=addnode(string("COMMA") );addedge($$, $1);addedge($$, $2);}
   ;

tse_sure : tse {$$=$1;}
         | tse_sure tse {$$=addnode("tse_sure");addedge($$, $1);addedge($$, $2);}
         ;

/*test*/
test: or_test IF or_test ELSE test {$$=addnode("test");addedge($$, $1);$2=addnode(string("IF"));addedge($$, $2);addedge($$, $3);$4=addnode(string("ELSE") );addedge($$, $4);addedge($$, $5);}
    | or_test {$$=$1;}
    ;

or_test: and_test oat_sure {$$=addnode("or_test");addedge($$, $1);addedge($$, $2);}
       | and_test {$$=$1;}
       ;

oat:OR and_test {$$=addnode("oat");$1=addnode(string("OR") );addedge($$, $1);addedge($$, $2);}
   ;

oat_sure: oat {$$=$1;}
        | oat_sure oat {$$=addnode("oat_sure");addedge($$, $1);addedge($$, $2);}
        ;

and_test: not_test ant_sure {$$=addnode("and_test");addedge($$, $1);addedge($$, $2);}
        | not_test {$$=$1;}
        ;

ant: AND not_test {$$=addnode("ant");$1=addnode(string("AND") );addedge($$, $1);addedge($$, $2);}
   ;

ant_sure: ant {$$=$1;}
        | ant_sure ant {$$=addnode("ant_sure");addedge($$, $1);addedge($$, $2);}
        ;

not_test: NOT not_test {$$=addnode("not_test");$1=addnode(string("NOT") );addedge($$, $1);addedge($$, $2);}
        | comparison {$$=$1;}
        ;

comparison: expr coe_sure {$$=addnode("comparison");addedge($$, $1);addedge($$, $2);}
          | expr {$$=$1;}
          ;

coe: comp_op expr {$$=addnode("coe");addedge($$, $1);addedge($$, $2);}
   ;

coe_sure : coe {$$=$1;}
         | coe_sure coe {$$=addnode("coe_sure");addedge($$, $1);addedge($$, $2);}
         ;

expr: xor_expr xe_sure {$$=addnode("expr");addedge($$, $1);addedge($$, $2);}
    | xor_expr {$$=$1;}
    ;

xe: ALTE xor_expr {$$=addnode("xe");$1=addnode(string("ALTE") );addedge($$, $1);addedge($$, $2);}
  ;

xe_sure: xe {$$=$1;}
       | xe_sure xe {$$=addnode("xe_sure");addedge($$, $1);addedge($$, $2);}
       ;

xor_expr: and_expr ae_sure {$$=addnode("xor_expr");addedge($$, $1);addedge($$, $2);}
        | and_expr {$$=$1;}
        ;

ae: POWER and_expr {$$=addnode("ae");$1=addnode(string("POWER") );addedge($$, $1);addedge($$, $2);}
  ;

ae_sure: ae {$$=$1;}
       | ae_sure ae {$$=addnode("ae_sure");addedge($$, $1);addedge($$, $2);}
       ;

and_expr: shift_expr se_sure {$$=addnode("and_expr");addedge($$, $1);addedge($$, $2);}
        | shift_expr {$$=$1;}
        ;

se: AAND shift_expr {$$=addnode("se");$1=addnode(string("AAND") );addedge($$, $1);addedge($$, $2);}
  ;

se_sure : se {$$=$1;}
        | se_sure se {$$=addnode("se_sure");addedge($$, $1);addedge($$, $2);}
        ;

shift_expr: arith_expr bae_sure {$$=addnode("shift_expr");addedge($$, $1);addedge($$, $2);}
          | arith_expr {$$=$1;}
          ;

bae: LLT arith_expr {$$=addnode("bae");$1=addnode(string("LLT") );addedge($$, $1);addedge($$, $2);}
   | GGT arith_expr {$$=addnode("bae");$1=addnode(string("GGT") );addedge($$, $1);addedge($$, $2);}
   ;

bae_sure: bae {$$=$1;}
        | bae_sure bae {$$=addnode("bae_sure");addedge($$, $1);addedge($$, $2);}
        ;

arith_expr: term pmterm_sure {$$=addnode("arith_expr");addedge($$, $1);addedge($$, $2);}
          | term {$$=$1;}
          ;

pmterm: PLUS term {$$=addnode("pmterm");$1=addnode(string("PLUS") );addedge($$, $1);addedge($$, $2);}
      | MINUS term {$$=addnode("pmterm");$1=addnode(string("MINUS") );addedge($$, $1);addedge($$, $2);}
      ;

pmterm_sure:pmterm {$$=$1;}
           |pmterm_sure pmterm {$$=addnode("pmterm_sure");addedge($$, $1);addedge($$, $2);}
           ;

term: factor sfac_sure {$$=addnode("term");addedge($$, $1);addedge($$, $2);}
    | factor {$$=$1;}
    ;

sfac:MULTI factor {$$=addnode("sfac");$1=addnode(string("PLUS") );addedge($$, $1);addedge($$, $2);}
    |DIVI factor {$$=addnode("sfac");$1=addnode(string("DIVI") );addedge($$, $1);addedge($$, $2);}
    |MOD factor {$$=addnode("sfac");$1=addnode(string("MOD") );addedge($$, $1);addedge($$, $2);}
    |SSLASH factor {$$=addnode("sfac");$1=addnode(string("SSLASH") );addedge($$, $1);addedge($$, $2);}
    ;

sfac_sure: sfac {$$=$1;}
         | sfac_sure sfac {$$=addnode("sfac_sure");addedge($$, $1);addedge($$, $2);}
         ;

factor:PLUS factor {$$=addnode("factor");$1=addnode(string("PLUS") );addedge($$, $1);addedge($$, $2);}
      |MINUS factor {$$=addnode("factor");$1=addnode(string("MINUS") );addedge($$, $1);addedge($$, $2);}
      |NOPE factor {$$=addnode("factor");$1=addnode(string("NOPE") );addedge($$, $1);addedge($$, $2);}
      |power {$$=$1;}
      ;

power: atom_expr SSTAR factor {$$=addnode("power");addedge($$, $1);$2=addnode(string("SSTAR"));addedge($$, $2);addedge($$, $3);}
     | atom_expr {$$=$1;}
     ;

atom_expr: atom trailer_sure {$$=addnode("atom_expr");addedge($$, $1);addedge($$, $2);}
         | atom {$$=$1;}
         ;

trailer_sure: trailer {$$=$1;}
            | trailer_sure trailer {$$=addnode("trailer_sure");addedge($$, $1);addedge($$, $2);}
            ;

atom: CIROPEN yield_expr CIRCLOSE {$$=addnode("atom");$1=addnode(string("CIROPEN") );addedge($$, $1);addedge($$, $2);$3=addnode(string("CIRCLOSE") );addedge($$, $3);}
    | CIROPEN testlist_comp CIRCLOSE {$$=addnode("atom");$1=addnode(string("CIROPEN") );addedge($$, $1);addedge($$, $2);$3=addnode(string("CIRCLOSE") );addedge($$, $3);}
    | CIROPEN CIRCLOSE {$$=addnode("atom");$1=addnode(string("CIROPEN") );addedge($$, $1);$2=addnode(string("CIRCLOSE"));addedge($$, $2);}
    | SQOPEN testlist_comp SQCLOSE {$$=addnode("atom");$1=addnode(string("SQOPEN") );addedge($$, $1);addedge($$, $2);$3=addnode(string("SQCLOSE") );addedge($$, $3);}
    | SQOPEN SQCLOSE {$$=addnode("atom");$1=addnode(string("SQOPEN") );addedge($$, $1);$2=addnode(string("SQCLOSE"));addedge($$, $2);}
    | CUOPEN CUCLOSE {$$=addnode("atom");$1=addnode(string("CUOPEN") );addedge($$, $1);$2=addnode(string("CUCLOSE"));addedge($$, $2);}
    | INT {$$=addnode("atom");$1=addnode(string("INT") );addedge($$, $1);}
    | FLOAT {$$=addnode("atom");$1=addnode(string("FLOAT") );addedge($$, $1);}
    | STR {$$=addnode("atom");$1=addnode(string("STR") );addedge($$, $1);}
    | BOOL {$$=addnode("atom");$1=addnode(string("BOOL") );addedge($$, $1);}
    | NUMBER {$$=addnode("atom");$1=addnode(string("NUMBER") );addedge($$, $1);}
    | string_sure {$$=$1;}
    | DDOT {$$=addnode("atom");$1=addnode(string("DDOT") );addedge($$, $1);}
    | NONE {$$=addnode("atom");$1=addnode(string("NONE") );addedge($$, $1);}
    | TRUE {$$=addnode("atom");$1=addnode(string("TRUE") );addedge($$, $1);}
    | FALSE {$$=addnode("atom");$1=addnode(string("FALSE") );addedge($$, $1);}
    | IDENTIFIER {$$=addnode("atom");$1=addnode(string("IDENTIFIER") );addedge($$, $1);}
    ;

yield_expr: YIELD yield_arg {$$=addnode("yield_expr");$1=addnode(string("YIELD") );addedge($$, $1);addedge($$, $2);}
          | YIELD {$$=addnode("yield_expr");$1=addnode(string("YIELD") );addedge($$, $1);}
          ;

yield_arg: FROM test {$$=addnode("yield_arg");$1=addnode(string("FROM") );addedge($$, $1);addedge($$, $2);}
         | testlist {$$=$1;}
         ;

testlist: test ct_sure COMMA {$$=addnode("testlist");addedge($$, $1);addedge($$, $2);$3=addnode(string("COMMA") );addedge($$, $3);}
        | test ct_sure {$$=addnode("testlist");addedge($$, $1);addedge($$, $2);}
        | test COMMA {$$=addnode("testlist");addedge($$, $1);$2=addnode(string("COMMA"));addedge($$, $2);}
        | test {$$=$1;}
        ;

ct: COMMA test {$$=addnode("ct");$1=addnode(string("COMMA") );addedge($$, $1);addedge($$, $2);}
  ;

ct_sure: ct {$$=$1;}
       | ct_sure ct {$$=addnode("ct_sure");addedge($$, $1);addedge($$, $2);}
       ;

testlist_comp: test comp_for {$$=addnode("testlist_comp");addedge($$, $1);addedge($$, $2);}
             | test ct_sure COMMA {$$=addnode("testlist_comp");addedge($$, $1);addedge($$, $2);$3=addnode(string("COMMA") );addedge($$, $3);}
             | test COMMA {$$=addnode("testlist_comp");addedge($$, $1);$2=addnode(string("COMMA"));addedge($$, $2);}
             | test ct_sure {$$=addnode("testlist_comp");addedge($$, $1);addedge($$, $2);}
             | test {$$=$1;}
             ;

comp_for: FOR exprlist IN or_test comp_iter {$$=addnode("comp_for");$1=addnode(string("FOR") );addedge($$, $1);addedge($$, $2);$3=addnode(string("IN") );addedge($$, $3);addedge($$, $4);addedge($$, $5);}
        | FOR exprlist IN or_test {$$=addnode("comp_for");$1=addnode(string("FOR") );addedge($$, $1);addedge($$, $2);$3=addnode(string("IN") );addedge($$, $3);addedge($$, $4);}
        ;

exprlist: expr cese_sure COMMA {$$=addnode("exprlist");addedge($$, $1);addedge($$, $2);$3=addnode(string("COMMA") );addedge($$, $3);}
        | expr COMMA {$$=addnode("exprlist");addedge($$, $1);$2=addnode(string("COMMA"));addedge($$, $2);}
        | expr cese_sure {$$=addnode("exprlist");addedge($$, $1);addedge($$, $2);}
        | expr {$$=$1;}
        ;

cese: COMMA expr {$$=addnode("cese");$1=addnode(string("COMMA") );addedge($$, $1);addedge($$, $2);}
    ;

cese_sure: cese {$$=$1;}
          | cese_sure cese {$$=addnode("cese_sure");addedge($$, $1);addedge($$, $2);}
          ;

comp_iter: comp_for {$$=$1;}
         | comp_if {$$=$1;}
         ;

comp_if: IF test_nocond comp_iter {$$=addnode("comp_if");$1=addnode(string("IF") );addedge($$, $1);addedge($$, $2);addedge($$, $3);}
       | IF test_nocond {$$=addnode("comp_if");$1=addnode(string("IF") );addedge($$, $1);addedge($$, $2);}
       ;

test_nocond: or_test {$$=$1;}
           ;

string_sure:STRING {$$=addnode("string_sure");$1=addnode(string("STRING") );addedge($$, $1);}
           |STRING string_sure {$$=addnode("string_sure");$1=addnode(string("STRING") );addedge($$, $1);addedge($$, $2);}
           ;

trailer:  CIROPEN arglist  CIRCLOSE {$$=addnode("trailer");$1=addnode(string("CIROPEN") );addedge($$, $1);addedge($$, $2);$3=addnode(string("CIRCLOSE") );addedge($$, $3);}
       |  CIROPEN   CIRCLOSE {$$=addnode("trailer");$1=addnode(string("CIROPEN") );addedge($$, $1);$2=addnode(string("CIRCLOSE"));addedge($$, $2);}
       |  SQOPEN subscriptlist  SQCLOSE {$$=addnode("trailer");$1=addnode(string("SQOPEN") );addedge($$, $1);addedge($$, $2);$3=addnode(string("SQCLOSE") );addedge($$, $3);}
       |  DOT IDENTIFIER {$$=addnode("trailer");$1=addnode(string("DOT") );addedge($$, $1);$2=addnode(string("IDENTIFIER"));addedge($$, $2);}
       |  DOT DUNDER {$$=addnode("trailer");$1=addnode(string("DOT") );addedge($$, $1);$2=addnode(string("DUNDER"));addedge($$, $2);}
       ;

arglist: argument ca_sure {$$=addnode("arglist");addedge($$, $1);addedge($$, $2);}
       | argument {$$=$1;}
       | argument ca_sure COMMA {$$=addnode("arglist");addedge($$, $1);addedge($$, $2);$3=addnode(string("COMMA") );addedge($$, $3);}
       | argument COMMA {$$=addnode("arglist");addedge($$, $1);$2=addnode(string("COMMA"));addedge($$, $2);}
       ;

ca:COMMA argument {$$=addnode("ca");$1=addnode(string("COMMA") );addedge($$, $1);addedge($$, $2);}
  ;

ca_sure: ca {$$=$1;}
       | ca_sure ca {$$=addnode("ca_sure");addedge($$, $1);addedge($$, $2);}
       ;

argument: test {$$=$1;}
        | test comp_for {$$=addnode("argument");addedge($$, $1);addedge($$, $2);}
        | test EQUAL test {$$=addnode("argument");addedge($$, $1);$2=addnode(string("EQUAL"));addedge($$, $2);addedge($$, $3);}
        ;

subscriptlist: subscript csubs_sure {$$=addnode("subscriptlist");addedge($$, $1);addedge($$, $2);}
             | subscript {$$=$1;}
             | subscript csubs_sure COMMA {$$=addnode("subscriptlist");addedge($$, $1);addedge($$, $2);$3=addnode(string("COMMA") );addedge($$, $3);}
             | subscript COMMA {$$=addnode("subscriptlist");addedge($$, $1);$2=addnode(string("COMMA"));addedge($$, $2);}
             ;

csubs: COMMA subscript {$$=addnode("csubs");$1=addnode(string("COMMA") );addedge($$, $1);addedge($$, $2);}
     ;

csubs_sure: csubs {$$=$1;}
          | csubs_sure csubs {$$=addnode("csubs_sure");addedge($$, $1);addedge($$, $2);}
          ;

subscript: test {$$=$1;}
         | test  COLON test {$$=addnode("subscript");addedge($$, $1);$2=addnode(string("COLON"));addedge($$, $2);addedge($$, $3);}
         | test  COLON {$$=addnode("subscript");addedge($$, $1);$2=addnode(string("COLON"));addedge($$, $2);}
         | COLON test {$$=addnode("subscript");$1=addnode(string("COLON") );addedge($$, $1);addedge($$, $2);}
         | COLON {$$=addnode("subscript");$1=addnode(string("COLON") );addedge($$, $1);}
         ;

/*comparision operator from not-test in test*/
comp_op: LT {$$=addnode("comp_op");$1=addnode(string("LT") );addedge($$, $1);}
       |GT {$$=addnode("comp_op");$1=addnode(string("GT") );addedge($$, $1);}
       |EEQ {$$=addnode("comp_op");$1=addnode(string("EEQ") );addedge($$, $1);}
       |GEQ {$$=addnode("comp_op");$1=addnode(string("GEQ") );addedge($$, $1);}
       |LEQ {$$=addnode("comp_op");$1=addnode(string("LEQ") );addedge($$, $1);}
       |DMOND {$$=addnode("comp_op");$1=addnode(string("DMOND") );addedge($$, $1);}
       |NEQ {$$=addnode("comp_op");$1=addnode(string("NEQ") );addedge($$, $1);}
       |IN {$$=addnode("comp_op");$1=addnode(string("IN") );addedge($$, $1);}
       |NOT IN {$$=addnode("comp_op");$1=addnode(string("NOT") );addedge($$, $1);$2=addnode(string("IN"));addedge($$, $2);}
       |IS {$$=addnode("comp_op");$1=addnode(string("IS") );addedge($$, $1);}
       |IS NOT {$$=addnode("comp_op");$1=addnode(string("IS") );addedge($$, $1);$2=addnode(string("NOT"));addedge($$, $2);}
       ;

annassign:  COLON test {$$=addnode("annassign");$1=addnode(string("COLON") );addedge($$, $1);addedge($$, $2);}
         |  COLON test EQUAL test {$$=addnode("annassign");$1=addnode(string("COLON") );addedge($$, $1);addedge($$, $2);$3=addnode(string("EQUAL") );addedge($$, $3);addedge($$, $4);}
         ;

augassign: PEQ {$$=addnode("augassign");$1=addnode(string("PEQ") );addedge($$, $1);}
         | MIEQ {$$=addnode("augassign");$1=addnode(string("MIEQ") );addedge($$, $1);}
         | MUEQ {$$=addnode("augassign");$1=addnode(string("MUEQ") );addedge($$, $1);}
         | DEQ {$$=addnode("augassign");$1=addnode(string("DEQ") );addedge($$, $1);}
         | MOEQ {$$=addnode("augassign");$1=addnode(string("MOEQ") );addedge($$, $1);}
         | AEQ {$$=addnode("augassign");$1=addnode(string("AEQ") );addedge($$, $1);}
         | ALEQ {$$=addnode("augassign");$1=addnode(string("ALEQ") );addedge($$, $1);}
         | POEQ {$$=addnode("augassign");$1=addnode(string("POEQ") );addedge($$, $1);}
         | LLEQ {$$=addnode("augassign");$1=addnode(string("LLEQ") );addedge($$, $1);}
         | GGEQ {$$=addnode("augassign");$1=addnode(string("GGEQ") );addedge($$, $1);}
         | MUMUEQ {$$=addnode("augassign");$1=addnode(string("MUMUEQ") );addedge($$, $1);}
         | DDEQ {$$=addnode("augassign");$1=addnode(string("DDEQ") );addedge($$, $1);}
         ;

flow_stmt: break_stmt {$$=$1;}
          | continue_stmt {$$=$1;}
          | return_stmt {$$=$1;}
          | raise_stmt {$$=$1;}
          | yield_stmt {$$=$1;}
          ;

break_stmt: BREAK {$$=addnode("break_stmt");$1=addnode(string("BREAK") );addedge($$, $1);}
          ;

continue_stmt: CONTINUE {$$=addnode("continue_stmt");$1=addnode(string("CONTINUE") );addedge($$, $1);}
             ;

return_stmt: RETURN {$$=addnode("return_stmt");$1=addnode(string("RETURN") );addedge($$, $1);}
           | RETURN testlist {$$=addnode("return_stmt");$1=addnode(string("RETURN") );addedge($$, $1);addedge($$, $2);}
           ;

raise_stmt: RAISE test FROM test {$$=addnode("raise_stmt");$1=addnode(string("RAISE") );addedge($$, $1);addedge($$, $2);$3=addnode(string("FROM") );addedge($$, $3);addedge($$, $4);}
           | RAISE test {$$=addnode("raise_stmt");$1=addnode(string("RAISE") );addedge($$, $1);addedge($$, $2);}
           | RAISE  {$$=addnode("raise_stmt");$1=addnode(string("RAISE") );addedge($$, $1);}
           ;

yield_stmt: yield_expr {$$=$1;}
          ;


global_stmt: GLOBAL IDENTIFIER cn_sure {$$=addnode("global_stmt");$1=addnode(string("GLOBAL") );addedge($$, $1);$2=addnode(string("IDENTIFIER"));addedge($$, $2);addedge($$, $3);}
           | GLOBAL IDENTIFIER {$$=addnode("global_stmt");$1=addnode(string("GLOBAL") );addedge($$, $1);$2=addnode(string("IDENTIFIER"));addedge($$, $2);}
           ;

cn: COMMA IDENTIFIER {$$=addnode("cn");$1=addnode(string("COMMA") );addedge($$, $1);$2=addnode(string("IDENTIFIER"));addedge($$, $2);}
  ;

cn_sure: cn {$$=$1;}
       | cn_sure cn {$$=addnode("cn_sure");addedge($$, $1);addedge($$, $2);}
       ;

assert_stmt: ASSERT test {$$=addnode("assert_stmt");$1=addnode(string("ASSERT") );addedge($$, $1);addedge($$, $2);}
           | ASSERT test COMMA test {$$=addnode("assert_stmt");$1=addnode(string("ASSERT") );addedge($$, $1);addedge($$, $2);$3=addnode(string("COMMA") );addedge($$, $3);addedge($$, $4);}
           ;

compound_stmt: if_stmt {$$=$1;}
             | while_stmt {$$=$1;}
             | for_stmt {$$=$1;}
             | try_stmt {$$=$1;}
             | funcdef {$$=$1;}
             | classdef {$$=$1;}
             | dunder_block {$$=$1;}
             ;

if_stmt: IF test  COLON suite ets_sure ELSE COLON suite {$$=addnode("if_stmt");$1=addnode(string("IF") );addedge($$, $1);addedge($$, $2);$3=addnode(string("COLON") );addedge($$, $3);addedge($$, $4);addedge($$, $5);$6=addnode(string("ELSE") );addedge($$, $6);$7=addnode(string("COLON") );addedge($$, $7);addedge($$, $8);}
       | IF test  COLON suite ELSE COLON suite {$$=addnode("if_stmt");$1=addnode(string("IF") );addedge($$, $1);addedge($$, $2);$3=addnode(string("COLON") );addedge($$, $3);addedge($$, $4);$5=addnode(string("ELSE") );addedge($$, $5);$6=addnode(string("COLON") );addedge($$, $6);addedge($$, $7);}
       | IF test  COLON suite ets_sure {$$=addnode("if_stmt");$1=addnode(string("IF") );addedge($$, $1);addedge($$, $2);$3=addnode(string("COLON") );addedge($$, $3);addedge($$, $4);addedge($$, $5);}
       | IF test  COLON suite {$$=addnode("if_stmt");$1=addnode(string("IF") );addedge($$, $1);addedge($$, $2);$3=addnode(string("COLON") );addedge($$, $3);addedge($$, $4);}
       ;

ets:ELIF test COLON suite {$$=addnode("ets");$1=addnode(string("ELIF") );addedge($$, $1);addedge($$, $2);$3=addnode(string("COLON") );addedge($$, $3);addedge($$, $4);}
   ;

ets_sure: ets {$$=$1;}
        | ets_sure ets {$$=addnode("ets_sure");addedge($$, $1);addedge($$, $2);}
        ;

suite: simple_stmt {$$=$1;}
     | n_sure INDENT nns_sure DEDENT {$$=addnode("suite");addedge($$, $1);$2=addnode(string("INDENT"));addedge($$, $2);addedge($$, $3);$4=addnode(string("DEDENT") );addedge($$, $4);}
     ;

nns: NEWLINE {$$=addnode("nns");$1=addnode(string("NEWLINE") );addedge($$, $1);}
   | new_stmt {$$=$1;}
   ;

nns_sure: nns {$$=$1;}
        | nns_sure nns {$$=addnode("nns_sure");addedge($$, $1);addedge($$, $2);}
        ;

new_stmt : simple_stmt {$$=$1;}
         | if_stmt {$$=$1;}
         | while_stmt {$$=$1;}
         | for_stmt {$$=$1;}
         | try_stmt {$$=$1;}
         | funcdef {$$=$1;}
         | dunder_block {$$=$1;}
         ;

while_stmt: WHILE test  COLON suite  {$$=addnode("while_stmt");$1=addnode(string("WHILE") );addedge($$, $1);addedge($$, $2);$3=addnode(string("COLON") );addedge($$, $3);addedge($$, $4);}
          | WHILE test  COLON suite ELSE  COLON suite {$$=addnode("while_stmt");$1=addnode(string("WHILE") );addedge($$, $1);addedge($$, $2);$3=addnode(string("COLON") );addedge($$, $3);addedge($$, $4);$5=addnode(string("ELSE") );addedge($$, $5);$6=addnode(string("COLON") );addedge($$, $6);addedge($$, $7);}
          ;


for_stmt: FOR exprlist IN testlist  COLON suite {$$=addnode("for_stmt");$1=addnode(string("FOR") );addedge($$, $1);addedge($$, $2);$3=addnode(string("IN") );addedge($$, $3);addedge($$, $4);$5=addnode(string("COLON") );addedge($$, $5);addedge($$, $6);}
        | FOR exprlist IN testlist  COLON suite ELSE  COLON suite {$$=addnode("for_stmt");$1=addnode(string("FOR") );addedge($$, $1);addedge($$, $2);$3=addnode(string("IN") );addedge($$, $3);addedge($$, $4);$5=addnode(string("COLON") );addedge($$, $5);addedge($$, $6);$7=addnode(string("ELSE") );addedge($$, $7);$8=addnode(string("COLON") );addedge($$, $8);addedge($$, $9);}
        ;

try_stmt: TRY  COLON suite ecs_sure ELSE  COLON suite FINALLY  COLON suite {$$=addnode("try_stmt");$1=addnode(string("TRY") );addedge($$, $1);$2=addnode(string("COLON"));addedge($$, $2);addedge($$, $3);addedge($$, $4);$5=addnode(string("ELSE") );addedge($$, $5);$6=addnode(string("COLON") );addedge($$, $6);addedge($$, $7);$8=addnode(string("FINALLY") );addedge($$, $8);$9=addnode(string("COLON") );addedge($$, $9);addedge($$, $10);}
        | TRY  COLON suite FINALLY  COLON suite {$$=addnode("try_stmt");$1=addnode(string("TRY") );addedge($$, $1);$2=addnode(string("COLON"));addedge($$, $2);addedge($$, $3);$4=addnode(string("FINALLY") );addedge($$, $4);$5=addnode(string("COLON") );addedge($$, $5);addedge($$, $6);}
        | TRY  COLON suite ecs_sure ELSE  COLON suite {$$=addnode("try_stmt");$1=addnode(string("TRY") );addedge($$, $1);$2=addnode(string("COLON"));addedge($$, $2);addedge($$, $3);addedge($$, $4);$5=addnode(string("ELSE") );addedge($$, $5);$6=addnode(string("COLON") );addedge($$, $6);addedge($$, $7);}
        | TRY  COLON suite ecs_sure FINALLY  COLON suite {$$=addnode("try_stmt");$1=addnode(string("TRY") );addedge($$, $1);$2=addnode(string("COLON"));addedge($$, $2);addedge($$, $3);addedge($$, $4);$5=addnode(string("FINALLY") );addedge($$, $5);$6=addnode(string("COLON") );addedge($$, $6);addedge($$, $7);}
        | TRY  COLON suite ecs_sure {$$=addnode("try_stmt");$1=addnode(string("TRY") );addedge($$, $1);$2=addnode(string("COLON"));addedge($$, $2);addedge($$, $3);addedge($$, $4);}
        ;


ecs : except_clause  COLON suite {$$=addnode("ecs");addedge($$, $1);$2=addnode(string("COLON"));addedge($$, $2);addedge($$, $3);}
    ;

except_clause: EXCEPT test AS IDENTIFIER {$$=addnode("except_clause");$1=addnode(string("EXCEPT") );addedge($$, $1);addedge($$, $2);$3=addnode(string("as") );addedge($$, $3);$4=addnode(string("IDENTIFIER") );addedge($$, $4);}
             | EXCEPT {$$=addnode("except_clause");$1=addnode(string("EXCEPT") );addedge($$, $1);}
             | EXCEPT test {$$=addnode("except_clause");$1=addnode(string("EXCEPT") );addedge($$, $1);addedge($$, $2);}
             ;

ecs_sure : ecs_sure ecs {$$=addnode("ecs_sure");addedge($$, $1);addedge($$, $2);}
         | ecs {$$=$1;}
         ;

funcdef: DEF IDENTIFIER parameters ARROW test  COLON suite {$$=addnode("funcdef");$1=addnode(string("DEF") );addedge($$, $1);$2=addnode(string("IDENTIFIER"));addedge($$, $2);addedge($$, $3);$4=addnode(string("ARROW") );addedge($$, $4);addedge($$, $5);$6=addnode(string("COLON") );addedge($$, $6);addedge($$, $7);}
       | DEF IDENTIFIER parameters  COLON suite {$$=addnode("funcdef");$1=addnode(string("DEF") );addedge($$, $1);$2=addnode(string("IDENTIFIER"));addedge($$, $2);addedge($$, $3);$4=addnode(string("COLON") );addedge($$, $4);addedge($$, $5);}
       | DEF DUNDER parameters ARROW test COLON suite {$$=addnode("funcdef");$1=addnode(string("DEF") );addedge($$, $1);$2=addnode(string("DUNDER"));addedge($$, $2);addedge($$, $3);$4=addnode(string("ARROW") );addedge($$, $4);addedge($$, $5);$6=addnode(string("COLON") );addedge($$, $6);addedge($$, $7);}
       | DEF DUNDER parameters  COLON suite {$$=addnode("funcdef");$1=addnode(string("DEF") );addedge($$, $1);$2=addnode(string("DUNDER"));addedge($$, $2);addedge($$, $3);$4=addnode(string("COLON") );addedge($$, $4);addedge($$, $5);}
       ;

parameters:  CIROPEN typedargslist  CIRCLOSE {$$=addnode("parameters");$1=addnode(string("CIROPEN") );addedge($$, $1);addedge($$, $2);$3=addnode(string("CIRCLOSE"));addedge($$, $3);}
          |  CIROPEN  CIRCLOSE {$$=addnode("parameters");$1=addnode(string("CIROPEN") );addedge($$, $1);$2=addnode(string("CIRCLOSE"));addedge($$, $2);}
          ;

typedargslist:tfpdef EQUAL test ctet_sure COMMA {$$=addnode("typedargslist");addedge($$, $1);$2=addnode(string("EQUAL"));addedge($$, $2);addedge($$, $3);addedge($$, $4);$5=addnode(string("COMMA") );addedge($$, $5);}
           | tfpdef EQUAL test COMMA {$$=addnode("typedargslist");addedge($$, $1);$2=addnode(string("EQUAL"));addedge($$, $2);addedge($$, $3);$4=addnode(string("COMMA") );addedge($$, $4);}
           | tfpdef ctet_sure COMMA {$$=addnode("typedargslist");addedge($$, $1);addedge($$, $2);$3=addnode(string("COMMA") );addedge($$, $3);}
           | tfpdef COMMA {$$=addnode("typedargslist");addedge($$, $1);$2=addnode(string("COMMA"));addedge($$, $2);}
           | tfpdef EQUAL test ctet_sure {$$=addnode("typedargslist");addedge($$, $1);$2=addnode(string("EQUAL"));addedge($$, $2);addedge($$, $3);addedge($$, $4);}
           | tfpdef EQUAL test {$$=addnode("typedargslist");addedge($$, $1);$2=addnode(string("EQUAL"));addedge($$, $2);addedge($$, $3);}
           | tfpdef ctet_sure {$$=addnode("typedargslist");addedge($$, $1);addedge($$, $2);}
           | tfpdef {$$=$1;}
           ;

ctet:COMMA tfpdef EQUAL test {$$=addnode("ctet");$1=addnode(string("COMMA") );addedge($$, $1);addedge($$, $2);$3=addnode(string("EQUAL") );addedge($$, $3);addedge($$, $4);}
    | COMMA tfpdef {$$=addnode("ctet");$1=addnode(string("COMMA") );addedge($$, $1);addedge($$, $2);}
    ;

ctet_sure: ctet {$$=$1;}
         | ctet_sure ctet {$$=addnode("ctet_sure");addedge($$, $1);addedge($$, $2);}
         ;
tfpdef: IDENTIFIER {$$=addnode("tfpdef");$1=addnode(string("IDENTIFIER") );addedge($$, $1);}
      | IDENTIFIER  COLON test {$$=addnode("tfpdef");$1=addnode(string("IDENTIFIER") );addedge($$, $1);$2=addnode(string("COLON"));addedge($$, $2);addedge($$, $3);}
      ;

classdef: CLASS IDENTIFIER  CIROPEN arglist  CIRCLOSE  COLON suite {$$=addnode("classdef");$1=addnode(string("CLASS") );addedge($$, $1);$2=addnode(string("IDENTIFIER"));addedge($$, $2);$3=addnode(string("CIROPEN") );addedge($$, $3);addedge($$, $4);$5=addnode(string("CIRCLOSE") );addedge($$, $5);$6=addnode(string("COLON") );addedge($$, $6);addedge($$, $7);}
        | CLASS IDENTIFIER  COLON suite {$$=addnode("classdef");$1=addnode(string("CLASS") );addedge($$, $1);$2=addnode(string("IDENTIFIER"));addedge($$, $2);$3=addnode(string("COLON") );addedge($$, $3);addedge($$, $4);}
        | CLASS IDENTIFIER  CIROPEN  CIRCLOSE  COLON suite {$$=addnode("classdef");$1=addnode(string("CLASS") );addedge($$, $1);$2=addnode(string("IDENTIFIER"));addedge($$, $2);$3=addnode(string("CIROPEN") );addedge($$, $3);$4=addnode(string("CIRCLOSE") );addedge($$, $4);$5=addnode(string("COLON") );addedge($$, $5);addedge($$, $6);}
        ;

dunder_block : IF DUNDER EEQ ADUNDER COLON suite {$$=addnode("dunder_block");$1=addnode(string("IF") );addedge($$, $1);$2=addnode(string("DUNDER"));addedge($$, $2);$3=addnode(string("EEQ") );addedge($$, $3);$4=addnode(string("ADUNDER") );addedge($$, $4);$5=addnode(string("COLON") );addedge($$, $5);addedge($$, $6);}
             ;



%%


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

