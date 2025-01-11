%{
    #include <bits/stdc++.h>
    #include "tree.cpp"
    using namespace std;
    extern void yyerror1(string s,int line);
    extern void yyerror(const char *s);
    extern "C" int yylex();
    extern int yylineno;
    extern stack <int> indent_stack;
    extern map<string,int> typeToSize;
    map<string,int> typeToSize;

glo_sym_tbl* GlobalSymbolTable = new glo_sym_tbl();
THREEACX86* threeacir = new THREEACX86();
x86variables* x86_out=new x86variables();

ofstream filedebug("outputs/debug.txt");


int getTemporarySize(string name){
    int sizes = 0;
    for(auto t : threeacir->blocks[name]->codes){

        if(t->is_block) sizes+=getTemporarySize(t->net_threeac);
        else if(t->net_threeac[0]=='t'){
            sizes+=t->net_threeac_size;
        }
    }
    return sizes;
};

%}

%union{
  char* val;
  class Info* info;
}

%start starting

%type<info> starting file_input line_or_stmt line_or_stmt_sure stmt line_sure simple_stmt smlst smlst_sure small_stmt expr_stmt equal_testlist_star_expr equal_testlist_star_expr_sure testlist_star_expr comma_test2 comma_test2_sure test or_test or_and_test or_and_test_sure and_test and_not_test and_not_test_sure not_test comparison comp_op_expr comp_op_expr_sure expr alte_xorexpr alte_xorexpr_sure xor_expr power_andexpr power_andexpr_sure and_expr and_shiftexpr and_shiftexpr_sure shift_expr llt_ggt_arithexpr llt_ggt_arithexpr_sure arith_expr plus_minus_term plus_minus_term_sure term operation_factor operation_factor_sure factor power atom_expr trailer_sure atom testlist comma_test comma_test_sure testlist_comp exprlist comma_expr comma_expr_sure string_sure trailer arglist comma_argument comma_argument_sure argument subscriptlist comma_subscript comma_subscript_sure subscript comp_op annassign augassign flow_stmt break_stmt continue_stmt return_stmt raise_stmt global_stmt comma_identifier comma_identifier_sure assert_stmt compound_stmt if_stmt else_if else_if_sure suite line_or_newstmt
line_or_newstmt_sure new_stmt while_stmt for_stmt funcdef parameters typedargslist comma_tfpdef comma_tfpdef_sure tfpdef classdef dunder_block testlistreturn func_end function_para_sure function_para
%token<val> NEWLINE INDENT DEDENT ENDMARKER DUNDER DATATYPE IS IF ELSE ELIF WHILE FOR RETURN IN FINALLY GLOBAL EXCEPT AS DEF CLASS ASSERT FROM CONTINUE BREAK RAISE NONE TRUE FALSE AND NOT OR DEL INT LISTINT LISTFLOAT LISTSTRING LISTBOOL LIST FLOAT STR BOOL IDENTIFIER DOUBLE_EQUAL GREATER_EQUAL LESS_EQUAL NOT_EQUAL DOUBLE_LESS DOUBLE_GREATER PLUS_EQUAL MINUS_EQUAL MULTI_EQUAL DIVI_EQUAL DOUBLE_DIVI_EQUAL MODULO_EQUAL DOUBLE_MULTI_EQUAL AND_EQUAL PIPE_EQUAL POWER_EQUAL DOUBLE_LESS_EQUAL DOUBLE_GREATER_EQUAL  STRING NUMBER FLOAT_NUMBER IMAGINARY_NUMBER DOUBLE_STAR THREE_DOT GREATER_LESS ARROW DOUBLE_SLASH COLON SEMICOLON PLUS MINUS DIVI EQUAL COMMA PIPE ANDSYMBOL POWER MULTI MOD NOSYMBOL CIROPEN CIRCLOSE SQOPEN SQCLOSE CUOPEN CUCLOSE DOT LESS GREATER ADUNDER
%right NEWLINE
%nonassoc EQUAL



%%




/*starting*/
starting: file_input { //cout<<" total done"<<endl;
$$=new Info();$$->val=addnode("starting");addedge($$->val, $1->val);
                       GlobalSymbolTable->printAll(); threeacir->print();threeacir->x86gen_threeac();
                     return 0;}
        ;

file_input: line_or_stmt_sure ENDMARKER {$$=new Info();$$->val=addnode("file_input");addedge($$->val, $1->val);}
          | ENDMARKER {$$=new Info();$$->val=addnode("file_input");$1=addnode(string("ENDMARKER") );addedge($$->val, $1);}
          ;

line_or_stmt_sure:line_or_stmt {
      //cout<<" lineorstmtsure1 "<<endl;
      $$=new Info();$$->val= $1->val;}
       |line_or_stmt_sure line_or_stmt {
          //cout<<" lineorstmtsure2 "<<endl;
          $$=new Info();$$->val=addnode("line_or_stmt_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
       ;

line_or_stmt: NEWLINE {  //cout<<" lineorstmt1 "<<endl;
$$=new Info();$$->val=addnode("NEWLINE");$1=addnode(string("newline") );addedge($$->val, $1);}
   | stmt {  //cout<<" lineorstmt2 "<<endl;
   $$=new Info();$$->val= $1->val;}
   ;




stmt: simple_stmt {$$=new Info();$$->val= $1->val;}
     | compound_stmt {$$=new Info();$$->val= $1->val;}
     ;

simple_stmt: small_stmt smlst_sure NEWLINE {
    //cout<<"simple_stmt1"<<endl;
                $$=new Info();
                $$->start=$1->start;
                $$->index=$2->index;
                $$->name=$1->name;
                $$->val=addnode("simple_stmt");addedge($$->val, $1->val);addedge($$->val, $2->val);$3=addnode(string("NEWLINE") );addedge($$->val, $3);}
           | small_stmt smlst_sure SEMICOLON NEWLINE {//cout<<"simple_stmt2"<<endl;
                $$=new Info();
                $$->start=$1->start;
                $$->index=$2->index;
                $$->name=$1->name;
                $$->val=addnode("simple_stmt");addedge($$->val, $1->val);addedge($$->val, $2->val);$3=addnode(string("SEMICOLON") );addedge($$->val, $3);$4=addnode(string("NEWLINE") );addedge($$->val, $4);}
           | small_stmt NEWLINE {//cout<<"simple_stmt3"<<" "<<endl;
                $$=new Info();
                $$->start=$1->start;
                $$->index=$1->index;
                $$->name=$1->name;
                $$->val=addnode("simple_stmt");addedge($$->val, $1->val);$2=addnode(string("NEWLINE"));addedge($$->val, $2);}
           | small_stmt SEMICOLON NEWLINE {//cout<<"simple_stmt4"<<endl;
                $$=new Info();
                $$->start=$1->start;
                $$->index=$1->index;
                $$->name=$1->name;
                $$->val=addnode("simple_stmt");addedge($$->val, $1->val);$2=addnode(string("SEMICOLON"));addedge($$->val, $2);$3=addnode(string("NEWLINE") );addedge($$->val, $3);}
           ;

smlst: SEMICOLON small_stmt {//cout<<"smlst1"<<endl;
            $$=new Info();
            $$->start=$2->start;
            $$->index=$2->index;
            $$->val=addnode("smlst");$1=addnode(string("SEMICOLON") );addedge($$->val, $1);addedge($$->val, $2->val);}
     ;

smlst_sure: smlst {
            $$=new Info();
            $$->start=$1->start;
            $$->index=$1->index;$$->val=$1->val;}
          | smlst_sure smlst {
            $$=new Info();
            $$->start=$1->start;
            $$->index=$2->index;
            $$->val=addnode("smlst_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
          ;

small_stmt: expr_stmt {//cout<<" smallstmt1 entered "<<endl;
                $$=new Info();
                $$->start=$1->start;
                $$->index=$1->index;
                $$->name=$1->name;
                $$->val=$1->val;
                }
          | flow_stmt {
                $$=new Info();
                $$->start=$1->start;
                $$->index=$1->index;
                $$->name=$1->name;
                $$->val=$1->val;}
          | global_stmt {
                $$=new Info();
                $$->start=$1->start;
                $$->index=$1->index;
                $$->name=$1->name;
                $$->val=$1->val;}
          | assert_stmt {
                $$=new Info();
                $$->start=$1->start;
                $$->index=$1->index;
                $$->name=$1->name;
                $$->val=$1->val;}
          ;

expr_stmt: testlist_star_expr annassign { 
                nor_sym* temp=GlobalSymbolTable->search_nor_sym($1->name,GlobalSymbolTable->curr_scope);
                $$=new Info();
               if($2->c>0){ temp->type="list"+$2->type;}
                else { 
                temp->type=$2->type; 
                }
                if($2->type== "string") temp->size=12;
                if($2->c==0) temp->size= type_size_map[$2->type];
                else if($2->c>0) {temp->isarray=1; temp->size= $2->c*type_size_map[$2->type];}
                GlobalSymbolTable->curr_sym_tbl->offset+=temp->size;

                if($2->c==0){
                     $$->index=threeacir->insert_assignment($2->name,"","",$1->name);
                     $$->start=$$->index;
                     $$->name=threeacir->get_var($$->index);}
                else if($2->c>0){
                    ////cout<<"did we really come here "<<endl;
                    //cout<<"expr_stmt1 entered4"<<endl;
                    int allocmem =type_size_map[$2->type];
                    allocmem *=$2->vec.size();
                    int ind = threeacir->insert_assignment(to_string(allocmem),"","","");
                    string z = threeacir->get_var(ind); //will give us return quadruple[index]->result;
                    threeacir->insert_two_word_instr("\tparam",z);
                    threeacir->insert_two_word_instr("\tallocmem","1");
                    string zz = threeacir->get_var(threeacir->insert_assignment("popparam","","",""));
                    // need to see this part $4->result = zz;
                    threeacir->insert_array(zz, $2->vec, type_size_map[$2->type]);

                    $$->index=threeacir->insert_assignment(zz,"","",$1->name);
                    $$->name=threeacir->get_var($$->index);
                    $$->start=ind;
                    //cout<<"expr_stmt1 entered5"<<endl;
                }
                else{
                    //cout<<"expr_stmt1 entered6"<<endl;
                    $$->start=threeacir->quadruple.size();
                    $$->index=threeacir->quadruple.size();
                    $$->name="nothing";
                    temp->type="list"+$2->type;
                    temp->isarray=1;
                    //cout<<"expr_stmt1 entered7"<<endl;
                }


                 //cout<<"expr_stmt1 exited"<<endl;
                $$->val=addnode("expr_stmt");addedge($$->val, $1->val);addedge($$->val, $2->val);}
         | testlist_star_expr augassign testlist { ////cout<<"expr_stmt2"<<endl;
                if(GlobalSymbolTable->type_check($3->type,$1->type))yyerror1("100 There is type mismach",yylineno);
                $$=new Info();$$->type=$1->type;
                string s="";
                int i=0;
                while($2->name[i]!='=') {
                    s+=$2->name[i];
                    i++;
                }

                $$->index=threeacir->insert_assignment($3->name,$1->name,s+$1->type,$1->name);

                $$->start=$3->start;
                $$->name=threeacir->get_var($$->index);

                $$->val=addnode("expr_stmt");addedge($$->val, $1->val);addedge($$->val, $2->val);addedge($$->val, $3->val);}
         | testlist_star_expr equal_testlist_star_expr_sure { ////cout<<"expr_stmt3"<<endl;
         ////cout<<$1->type<<" h "<<$2->type<<endl;
              if(GlobalSymbolTable->type_check($2->type,$1->type)) yyerror1("1 There is type mismach",yylineno);
              $$=new Info();$1->type=$1->type; int k=GlobalSymbolTable->curr_sym_tbl->nor_sym_vec.size();GlobalSymbolTable->curr_sym_tbl->nor_sym_vec[k-1]->type=$2->type;
              GlobalSymbolTable->curr_sym_tbl->nor_sym_vec[k-1]->size= type_size_map[$2->type];

              $$->index=threeacir->insert_assignment($2->name,"","",$1->name);
              $$->start=$$->index;
              $$->name=threeacir->get_var($$->index);




              $$->val=addnode("expr_stmt");addedge($$->val, $1->val);addedge($$->val, $2->val);}
         | testlist_star_expr { ////cout<<"expr_stmt4"<<endl;////cout<<$1->start<<endl;
              $$=new Info();
              $$->type=$1->type;
              $$->val=$1->val;
              $$->index=$1->index;
              $$->start=$1->start;
              $$->name=$1->name;
              $$->name=threeacir->get_var($$->index);}
         ;

equal_testlist_star_expr : EQUAL testlist_star_expr { ////cout<<"equal_testlist_star_expr"<<endl;
            $$=new Info();$$->type=$2->type;$$->name=$2->name;
            $$->val=addnode("equal_testlist_star_expr");$1=addnode(string("EQUAL") );addedge($$->val, $1);addedge($$->val, $2->val);}
      ;

equal_testlist_star_expr_sure : equal_testlist_star_expr { ////cout<<"equal_testlist_star_expr_sure 1"<<endl;
                $$=new Info();$$->type=$1->type;$$->val=$1->val;$$->name=$1->name; }
           | equal_testlist_star_expr_sure equal_testlist_star_expr {////cout<<"equal_testlist_star_expr_sure 2"<<endl;
                $$=new Info();$$->type=$1->type;
                if(GlobalSymbolTable->type_check($2->type,$1->type)) yyerror1("36 there is a type mismatch",yylineno);
                $$->val=addnode("equal_testlist_star_expr_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
           ;

testlist_star_expr: test comma_test2_sure { ////cout<<"testlist_star_expr 1"<<endl;
                        $$=new Info();
                        if(GlobalSymbolTable->type_check($1->type,$2->type) && GlobalSymbolTable->type_check($2->type,$1->type))
                            yyerror1("35 there is a type mismatch",yylineno);
                        if(GlobalSymbolTable->type_check($1->type,$2->type)) $$->type=$1->type;
                        else $$->type=$2->type;
                        $$->val=addnode("testlist_star_expr");addedge($$->val, $1->val);addedge($$->val, $2->val);}
                  | test { ////cout<<"testlist_star_expr 2"<<endl;////cout<<$1->start<<endl;
                        $$=new Info();$$->name=$1->name;$$->type=$1->type;$$->start=$1->start;$$->vec=$1->vec;
                         $$->val=$1->val;$$->index=$1->index;}
                  | test comma_test2_sure COMMA { ////cout<<"testlist_star_expr 3"<<endl;
                        $$=new Info();
                        if(GlobalSymbolTable->type_check($1->type,$2->type) && GlobalSymbolTable->type_check($2->type,$1->type))
                            yyerror1("34 there is a type mismatch",yylineno);
                        if(GlobalSymbolTable->type_check($1->type,$2->type)) $$->type=$1->type;
                        else $$->type=$2->type;
                        $$->val=addnode("testlist_star_expr");addedge($$->val, $1->val);addedge($$->val, $2->val);$3=addnode(string("COMMA") );addedge($$->val, $3);}
                  | test COMMA { ////cout<<"testlist_star_expr 4"<<endl;////cout<<$1->start<<endl;
                        $$=new Info();$$->type=$1->type;$$->name=$1->name;$$->start=$1->start;
                        $$->val=addnode("testlist_star_expr");addedge($$->val, $1->val);$2=addnode(string("COMMA"));addedge($$->val, $2);}
                  ;

comma_test2: COMMA test { ////cout<<"comma_test2"<<endl;
        $$=new Info();$$->type=$2->type;$$->name=$2->name;
        $$->val=addnode("comma_test2");$1=addnode(string("COMMA") );addedge($$->val, $1);addedge($$->val, $2->val);}
   ;

comma_test2_sure : comma_test2 { ////cout<<"comma_test2_sure 1"<<endl;
            $$=new Info();$$->type=$1->type;$$->val=$1->val;$$->name=$1->name;}
         | comma_test2_sure comma_test2 { ////cout<<"comma_test2_sure 2"<<endl;
            $$=new Info();
            if(GlobalSymbolTable->type_check($1->type,$2->type) && GlobalSymbolTable->type_check($2->type,$1->type))
                            yyerror1("34 there is a type mismatch",yylineno);
            if(GlobalSymbolTable->type_check($1->type,$2->type)) $$->type=$1->type;
            else $$->type=$2->type;
            $$->val=addnode("comma_test2_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
         ;

/*test*/
test: or_test IF or_test ELSE test { ////cout<<"test 1"<<endl;
         $$->val=addnode("test");addedge($$->val, $1->val);$2=addnode(string("IF"));addedge($$->val, $2);addedge($$->val, $3->val);$4=addnode(string("ELSE") );addedge($$->val, $4);addedge($$->val, $5->val);}
    | or_test {  ////cout<<"test 2"<<endl; ////cout<<$1->start<<endl;
        $$=new Info(); $$->start=$1->start;$$->index=$1->index;$$->name=$1->name;$$->type=$1->type;$$->c=$1->c;$$->vec=$1->vec;
         $$->val=$1->val;}
    ;

or_test: and_test or_and_test_sure { ////cout<<"or_test 1"<<endl;
            $$=new Info();$$->type=$1->type;
            if(GlobalSymbolTable->type_check($1->type,$2->type) && GlobalSymbolTable->type_check($2->type,$1->type)) yyerror1("33 there is a type mismatch",yylineno);

            if($$->operation!="")$$->operation=$1->operation;
            $$->index = threeacir->insert_assignment($1->name,$2->name,$2->operation);
            $$->name = threeacir->get_var($$->index);
            $$->start=$1->start;

            $$->val=addnode("or_test");addedge($$->val, $1->val);addedge($$->val, $2->val);}
       | and_test { ////cout<<"or_test 2"<<endl;////cout<<$1->index<<endl;
            $$=new Info();$$->name=$1->name;$$->type=$1->type;$$->c=$1->c;$$->start=$1->start;
            $$->index=$1->index;$$->vec=$1->vec;
              $$->val=$1->val;}
       ;

or_and_test:OR and_test { ////cout<<"or_and_test"<<endl;
          $$=new Info();$$->type=$2->type;
          $$->name=$2->name;
          $$->operation=$1;
          $$->val=addnode("or_and_test");$1=addnode(string("OR") );addedge($$->val, $1);addedge($$->val, $2->val);}
   ;

or_and_test_sure: or_and_test { ////cout<<"or_and_test_sure 1"<<endl;
           $$=new Info();$$->type=$1->type;
           $$->name=$1->name;
           $$->operation=$1->operation;
           $$->val=$1->val;}
        | or_and_test_sure or_and_test { ////cout<<"or_and_test_sure 2"<<endl;
            $$=new Info();$$->type=$2->type;
            if(GlobalSymbolTable->type_check($1->type,$2->type) && GlobalSymbolTable->type_check($2->type,$1->type)) yyerror1("32 there is a type mismatch",yylineno);

            $$->operation=$1->operation;
            $$->index = threeacir->insert_assignment($1->name,$2->name,$2->operation);
            $$->name = threeacir->get_var($$->index);

            $$->val=addnode("or_and_test_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
        ;

and_test: not_test and_not_test_sure { ////cout<<"and_test 1"<<endl;
            $$=new Info();$$->type=$1->type;
            if(GlobalSymbolTable->type_check($1->type,$2->type) && GlobalSymbolTable->type_check($2->type,$1->type)) yyerror1("31 there is a type mismatch",yylineno);

            $$->index = threeacir->insert_assignment($1->name,$2->name,$2->operation);
            $$->name = threeacir->get_var($$->index);
            if($1->operation!="") $$->operation=$1->operation;
            $$->start=$1->start;

            $$->val=addnode("and_test");addedge($$->val, $1->val);addedge($$->val, $2->val);}
        | not_test { ////cout<<"and_test 2"<<endl;
            $$=new Info();$$->name=$1->name;$$->type=$1->type;$$->c=$1->c;$$->start=$1->start;
            $$->index=$1->index; $$->vec=$1->vec;
             $$->val=$1->val;}
        ;

and_not_test: AND not_test { ////cout<<"and_not_test"<<endl;
        $$=new Info();$$->type=$2->type;
        $$->operation=$1;
        $$->name=$2->name;
        $$->val=addnode("and_not_test");$1=addnode(string("AND") );addedge($$->val, $1);addedge($$->val, $2->val);}
   ;

and_not_test_sure: and_not_test { ////cout<<"and_not_test_sure 1"<<endl;
            $$=new Info();$$->type=$1->type;
            $$->operation=$1->operation;
            $$->name=$1->name;
            $$->val=$1->val;}
        | and_not_test_sure and_not_test { ////cout<<"and_not_test_sure 2"<<endl;
            $$=new Info();$$->type=$2->type;

            $$->operation=$1->operation;
            $$->index = threeacir->insert_assignment($1->name,$2->name,$2->operation);
            $$->name = threeacir->get_var($$->index);

            if(GlobalSymbolTable->type_check($1->type,$2->type) && GlobalSymbolTable->type_check($2->type,$1->type)) yyerror1("30 there is a type mismatch",yylineno);
            $$->val=addnode("and_not_test_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
        ;

not_test: NOT not_test { ////cout<<"not_test 1"<<endl;////cout<<$2->index<<endl;
              $$=new Info();$$->type=$2->type;
              $$->operation=$1;
              $$->name=$2->name;
              $$->start=$2->start;
              $$->index=$2->index;
              $$->val=addnode("not_test");$1=addnode(string("NOT") );addedge($$->val, $1);addedge($$->val, $2->val);}
        | comparison { ////cout<<"not_test 2"<<endl; ////cout<<$1->index<<endl;
              $$=new Info();$$->name=$1->name;$$->type=$1->type;$$->c=$1->c;$$->vec=$1->vec;$$->start=$1->start;
               $$->index=$1->index;
               $$->val=$1->val;}
        ;

comparison: expr comp_op_expr_sure { ////cout<<"comparison1"<<endl; ////cout<<$1->start<<endl;
                  $$=new Info();
                  int k= GlobalSymbolTable->curr_sym_tbl->nor_sym_vec.size();
                  GlobalSymbolTable->curr_sym_tbl->nor_sym_vec[k-1]->type=$2->type;
                  GlobalSymbolTable->curr_sym_tbl->nor_sym_vec[k-1]->size= type_size_map[$2->type];

                  if(GlobalSymbolTable->type_check($1->type,$2->type) && GlobalSymbolTable->type_check($2->type,$1->type))
                       yyerror1("2 there is a type mismatch",yylineno);
                  $$->index= threeacir->insert_assignment($1->name,$2->name,$2->operation);
                  $$->name = threeacir->get_var($$->index);
                  $$->index=$1->index;
                  $$->start=$1->start;
                  $$->type="bool";
                  $$->val=addnode("comparison");addedge($$->val, $1->val);addedge($$->val, $2->val);}
          | expr { ////cout<<"comparison2"<<endl;
                  $$=new Info();$$->name=$1->name;$$->type=$1->type;$$->c=$1->c;$$->vec=$1->vec;$$->start=$1->start;$$->index=$1->index;
                    $$->val=$1->val;}
          ;

comp_op_expr: comp_op expr { ////cout<<"comp_op_expr"<<endl;
        $$=new Info();
        $$->type=$2->type;
        $$->name=$2->name;
        $$->operation=$1->name;
        $$->val=addnode("comp_op_expr");addedge($$->val, $1->val);addedge($$->val, $2->val);}
   ;

comp_op_expr_sure : comp_op_expr { ////cout<<"comp_op_expr_sure 1"<<endl;
              $$ = new Info();
              $$->type=$1->type;
              $$->name=$1->name;
              $$->operation=$1->operation;
              $$->val=$1->val;}
         | comp_op_expr_sure comp_op_expr { ////cout<<"comp_op_expr_sure 2"<<endl;
              $$=new Info();
              $$->type=$1->type;

              $$->index = threeacir->insert_assignment($1->name,$2->name,$2->operation);
              $$->name = threeacir->get_var($$->index);
              $$->operation=$1->operation;

              if(GlobalSymbolTable->type_check($1->type,$2->type) && GlobalSymbolTable->type_check($2->type,$1->type))
                    yyerror1("3 there is a type mismatch",yylineno);
              $$->val=addnode("comp_op_expr_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
         ;

expr: xor_expr alte_xorexpr_sure { ////cout<<"expr 1"<<endl;
          $$=new Info();$$->type=$1->type;
          if(GlobalSymbolTable->type_check($1->type,$2->type) && GlobalSymbolTable->type_check($2->type,$1->type))
              yyerror1("26 there is a type mismatch",yylineno);

          $$->index = threeacir->insert_assignment($1->name,$2->name,$2->operation);
          $$->name = threeacir->get_var($$->index);
          $$->operation=$1->operation;
          $$->start=$1->start;

          $$->val=addnode("expr");addedge($$->val, $1->val);addedge($$->val, $2->val);}
    | xor_expr { ////cout<<"expr 2"<<endl; ////cout<<$1->start<<endl;
          $$=new Info();$$->name=$1->name;$$->type=$1->type;$$->c=$1->c;$$->vec=$1->vec;
          if($1->operation!="")$$->operation=$1->operation;
          $$->start=$1->start;
          $$->index=$1->index;

           $$->val=$1->val;}
    ;

alte_xorexpr: PIPE xor_expr { ////cout<<"alte_xorexpr"<<endl;
        $$=new Info();$$->type=$2->type;
        $$->operation=$1;
        $$->name=$2->name;
        $$->val=addnode("alte_xorexpr");$1=addnode(string("PIPE") );addedge($$->val, $1);addedge($$->val, $2->val);}
  ;

alte_xorexpr_sure: alte_xorexpr { ////cout<<"alte_xorexpr_sure 1"<<endl;
            $$=new Info();$$->type=$1->type;
            $$->operation=$1->operation;
            $$->name=$1->name;
            $$->val=$1->val;}
       | alte_xorexpr_sure alte_xorexpr { ////cout<<"alte_xorexpr_sure 2"<<endl;
            $$=new Info();$$->type=$1->type;
            if(GlobalSymbolTable->type_check($1->type,$2->type) && GlobalSymbolTable->type_check($2->type,$1->type))
                 yyerror1("25 there is a type mismatch",yylineno);

            $$->index = threeacir->insert_assignment($1->name,$2->name,$2->operation);
            $$->name = threeacir->get_var($$->index);
            if($1->operation!="")$$->operation=$1->operation;

            $$->val=addnode("alte_xorexpr_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
       ;

xor_expr: and_expr power_andexpr_sure { ////cout<<"xor_expr 1"<<endl;
            $$=new Info();$$->type=$1->type;
            if(GlobalSymbolTable->type_check($2->type,$1->type)) yyerror1("25 there is a type mismatch",yylineno);

            $$->index = threeacir->insert_assignment($1->name,$2->name,$2->operation);
            $$->name = threeacir->get_var($$->index);
            if($1->operation!="")$$->operation=$1->operation;
            $$->start=$1->start;

            $$->val=addnode("xor_expr");addedge($$->val, $1->val);addedge($$->val, $2->val);}
        | and_expr { ////cout<<"xor_expr 2"<<endl;
            $$=new Info();$$->name=$1->name;$$->type=$1->type;$$->c=$1->c;$$->vec=$1->vec;
            if($1->operation!="")$$->operation=$1->operation;
            $$->start=$1->start;
            $$->index=$1->index;

            $$->val=$1->val;}
        ;

power_andexpr: POWER and_expr { ////cout<<"power_andexpr"<<endl;
        $$=new Info();$$->type=$2->type;
        $$->operation=$1;
        $$->name=$2->name;
        $$->val=addnode("power_andexpr");$1=addnode(string("POWER") );addedge($$->val, $1);addedge($$->val, $2->val);}
  ;

power_andexpr_sure: power_andexpr { ////cout<<"power_andexpr_sure 1"<<endl;
            $$=new Info();$$->type=$1->type;
            $$->operation=$1->operation;
            $$->name=$1->name;
            $$->val=$1->val;}
       | power_andexpr_sure power_andexpr { ////cout<<"power_andexpr_sure 2"<<endl;
            $$=new Info();$$->type=$1->type;
            if(GlobalSymbolTable->type_check($2->type,$1->type)) yyerror1("24 there is a type mismatch",yylineno);
            $$->index = threeacir->insert_assignment($1->name,$2->name,$2->operation);
            $$->name = threeacir->get_var($$->index);
            $$->operation=$1->operation;
            $$->val=addnode("power_andexpr_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
       ;

and_expr: shift_expr and_shiftexpr_sure { ////cout<<"and_expr 1"<<endl;
              $$=new Info();$$->type=$1->type;
              if(GlobalSymbolTable->type_check($2->type,$1->type)) yyerror1("23 there is a type mismatch",yylineno);

              $$->index = threeacir->insert_assignment($1->name,$2->name,$2->operation);
              $$->name = threeacir->get_var($$->index);
              if($1->operation!="")$$->operation=$1->operation;
              $$->start=$1->start;

              $$->val=addnode("and_expr");addedge($$->val, $1->val);addedge($$->val, $2->val);}
        | shift_expr { ////cout<<"and_expr 2"<<endl;
              $$=new Info();$$->name=$1->name;$$->type=$1->type;$$->c=$1->c;$$->vec=$1->vec;
              if($1->operation!="")$$->operation=$1->operation;
              $$->start=$1->start;
              $$->index=$1->index;

               $$->val=$1->val;}
        ;

and_shiftexpr: ANDSYMBOL shift_expr { ////cout<<"and_shiftexpr"<<endl;
         $$=new Info();$$->type=$2->type;
         $$->operation=$1;
         $$->name=$2->name;
         $$->val=addnode("and_shiftexpr");$1=addnode(string("ANDSYMBOL") );addedge($$->val, $1);addedge($$->val, $2->val);}
  ;

and_shiftexpr_sure : and_shiftexpr { ////cout<<"and_shiftexpr_sure 1"<<endl;
            $$=new Info();$$->type=$1->type;
            $$->operation=$1->operation;
            $$->name=$1->name;
            $$->val=$1->val;}
        | and_shiftexpr_sure and_shiftexpr { ////cout<<"and_shiftexpr_sure 2"<<endl;
            $$=new Info();$$->type=$1->type;
            if(GlobalSymbolTable->type_check($2->type,$1->type) && GlobalSymbolTable->type_check($1->type,$2->type)) yyerror1("22 there is a type mismatch",yylineno);

            $$->index = threeacir->insert_assignment($1->name,$2->name,$2->operation);
            $$->name = threeacir->get_var($$->index);
            $$->operation=$1->operation;

            $$->val=addnode("and_shiftexpr_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
        ;

shift_expr: arith_expr llt_ggt_arithexpr_sure { ////cout<<"shift_expr 1"<<endl;
              $$=new Info();$$->type=$1->type;
              if(GlobalSymbolTable->type_check($2->type,$1->type) && GlobalSymbolTable->type_check($1->type,$2->type)) yyerror1("21 there is a type mismatch",yylineno);

              $$->index = threeacir->insert_assignment($1->name,$2->name,$2->operation);
              $$->name = threeacir->get_var($$->index);
              if($1->operation!="")$$->operation=$1->operation;
              $$->start=$1->start;

              $$->val=addnode("shift_expr");addedge($$->val, $1->val);addedge($$->val, $2->val);}
          | arith_expr { ////cout<<"shift_expr 2"<<endl;
              $$=new Info();$$->name=$1->name;$$->type=$1->type;$$->c=$1->c;$$->vec=$1->vec;
              if($1->operation!="")$$->operation=$1->operation;
              $$->start=$1->start;
              $$->index=$1->index;

              $$->val=$1->val;}
          ;

llt_ggt_arithexpr: DOUBLE_LESS arith_expr { ////cout<<"llt_ggt_arithexpr 1"<<endl;
        $$=new Info();$$->type=$2->type;
        $$->operation=$1;
        $$->name=$2->name;
        $$->val=addnode("llt_ggt_arithexpr");$1=addnode(string("DOUBLE_LESS") );addedge($$->val, $1);addedge($$->val, $2->val);}
   | DOUBLE_GREATER arith_expr { ////cout<<"llt_ggt_arithexpr 2"<<endl;
        $$=new Info();$$->type=$2->type;
        $$->operation=$1;
        $$->name=$2->name;
        $$->val=addnode("llt_ggt_arithexpr");$1=addnode(string("DOUBLE_GREATER") );addedge($$->val, $1);addedge($$->val, $2->val);}
   ;

llt_ggt_arithexpr_sure: llt_ggt_arithexpr { ////cout<<"llt_ggt_arithexpr_sure 1"<<endl;
            $$=new Info();$$->type=$1->type;
            $$->operation=$1->operation;
            $$->name=$1->name;
            $$->val=$1->val;}
        | llt_ggt_arithexpr_sure llt_ggt_arithexpr { ////cout<<"llt_ggt_arithexpr_sure 2"<<endl;
            $$=new Info();$$->type=$1->type;
            if(GlobalSymbolTable->type_check($2->type,$1->type) && GlobalSymbolTable->type_check($1->type,$2->type)) yyerror1("20 there is a type mismatch",yylineno);

            $$->index = threeacir->insert_assignment($1->name,$2->name,$2->operation);
            $$->name = threeacir->get_var($$->index);
            $$->operation=$1->operation;

            $$->val=addnode("llt_ggt_arithexpr_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
        ;

arith_expr: term plus_minus_term_sure {  ////cout<<"arith_expr 1"<<endl;
                if(GlobalSymbolTable->type_check($2->type,$1->type) && GlobalSymbolTable->type_check($1->type,$2->type)) yyerror1("4 there is type mismatch",yylineno);
                $$=new Info();
                if(GlobalSymbolTable->type_check($2->type,$1->type))$$->type=$2->type;
                else $$->type=$2->type;

                $$->index = threeacir->insert_assignment($1->name,$2->name,$2->operation);
                $$->name = threeacir->get_var($$->index);
                if($1->operation!="")$$->operation=$1->operation;
                $$->start=$1->start;

                $$->val=addnode("arith_expr");addedge($$->val, $1->val);addedge($$->val, $2->val);}
          | term { ////cout<<"arith_expr 2"<<endl;
                $$=new Info();$$->name=$1->name;$$->type=$1->type;$$->c=$1->c;$$->vec=$1->vec;
                if($1->operation!="")$$->operation=$1->operation;
                $$->start=$1->start;
                $$->index=$1->index;

                $$->val=$1->val;}
          ;

plus_minus_term: PLUS term {  ////cout<<"plus_minus_term 1"<<endl;
            $$= new Info();
            $$->type = $2->type;
            $$->operation=$1;
            $$->name=$2->name;
            $$->val=addnode("plus_minus_term");$1=addnode(string("PLUS") );addedge($$->val, $1);addedge($$->val, $2->val);}
      | MINUS term {////cout<<"plus_minus_term 2"<<endl;
            $$= new Info();
            $$->type = $2->type;
            $$->operation=$1;
            $$->name=$2->name;
            $$->val=addnode("plus_minus_term");$1=addnode(string("MINUS") );addedge($$->val, $1);addedge($$->val, $2->val);}
      ;

plus_minus_term_sure:plus_minus_term { ////cout<<"plus_minus_term_sure 1"<<endl;
               $$=new Info();$$->type=$1->type;
               $$->operation=$1->operation;
               $$->name=$1->name;
               $$->val=$1->val;}
           |plus_minus_term_sure plus_minus_term { ////cout<<"plus_minus_term_sure 2"<<endl;
              $$=new Info();$$->type=$1->type;

              $$->operation=$1->operation;
              $$->index = threeacir->insert_assignment($1->name,$2->name,$2->operation);
              $$->name = threeacir->get_var($$->index);

              $$->val=addnode("plus_minus_term_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
           ;

term: factor operation_factor_sure { ////cout<<"term 1"<<endl;
            ////cout<<$2->type << $1->type << endl;
            if(GlobalSymbolTable->type_check($2->type,$1->type) && GlobalSymbolTable->type_check($1->type,$2->type)) yyerror1("4 there is type mismatch",yylineno);
            $$=new Info();
            if(GlobalSymbolTable->type_check($2->type,$1->type))$$->type=$2->type;
            else $$->type=$2->type;

            $$->index = threeacir->insert_assignment($1->name,$2->name,$2->operation);
            $$->name = threeacir->get_var($$->index);
            if($1->operation!="")$$->operation=$1->operation;
            $$->start=$1->start;

          $$->type=$1->type;$$->val=addnode("term");addedge($$->val, $1->val);addedge($$->val, $2->val);}
    |factor { ////cout<<"term 2"<<endl;
            $$=new Info();$$->name=$1->name;$$->type=$1->type;$$->c=$1->c;$$->vec=$1->vec;
            if($1->operation!="")$$->operation=$1->operation;
            $$->start=$1->start;
            $$->index=$1->index;

            $$->val=$1->val;}
    ;

operation_factor:MULTI factor { ////cout<<"operation_factor 1"<<endl;
        $$= new Info();
        $$->type= $2->type;
        $$->operation=$1;
        $$->name=$2->name;
        $$->val=addnode("operation_factor");$1=addnode(string("PLUS") );addedge($$->val, $1);addedge($$->val, $2->val);}
    |DIVI factor { ////cout<<"operation_factor 2"<<endl;
        $$= new Info();
        $$->type= $2->type;
        $$->operation=$1;
        $$->name=$2->name;
        $$->val=addnode("operation_factor");$1=addnode(string("DIVI") );addedge($$->val, $1);addedge($$->val, $2->val);}
    |MOD factor {  ////cout<<"operation_factor 3"<<endl;
        $$= new Info();
        $$->type= $2->type;
        $$->operation=$1;
        $$->name=$2->name;
        $$->val=addnode("operation_factor");$1=addnode(string("MOD") );addedge($$->val, $1);addedge($$->val, $2->val);}
    |DOUBLE_SLASH factor { ////cout<<"operation_factor 4"<<endl;
        $$= new Info();
        $$->type= $2->type;
        $$->operation=$1;
        $$->name=$2->name;
        $$->val=addnode("operation_factor");$1=addnode(string("DOUBLE_SLASH") );addedge($$->val, $1);addedge($$->val, $2->val);}
    ;

operation_factor_sure: operation_factor { ////cout<<"operation_factor_sure 1 "<<endl;
            $$=new Info(); $$->type= $1->type;
            $$->operation=$1->operation;
            $$->name=$1->name;
            $$->val=$1->val;}
         | operation_factor_sure operation_factor { ////cout<<"operation_factor_sure 2"<<endl;
            if(GlobalSymbolTable->type_check($2->type,$1->type) && GlobalSymbolTable->type_check($1->type,$2->type)) yyerror1("4 there is type mismatch",yylineno);
            $$=new Info();
            if(GlobalSymbolTable->type_check($2->type,$1->type))$$->type=$2->type;
            else $$->type=$2->type;
            $$->operation=$1->operation;

            $$->index = threeacir->insert_assignment($1->name,$2->name,$2->operation);
            $$->name = threeacir->get_var($$->index);


            $$->val=addnode("operation_factor_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
         ;

factor:PLUS factor {////cout<<"factor 1"<<endl;
             $$=new Info();$$->type=$2->type;
             $$->name=$2->name;
             $$->operation=$1;
             $$->val=addnode("factor");$1=addnode(string("PLUS") );addedge($$->val, $1);addedge($$->val, $2->val);}
      |MINUS factor {////cout<<"factor 2"<<endl;
            $$=new Info();$$->type=$2->type;
            $$->name=$2->name;
            $$->operation=$1;
            $$->val=addnode("factor");$1=addnode(string("MINUS") );addedge($$->val, $1);addedge($$->val, $2->val);}
      |NOSYMBOL factor {////cout<<"factor 3"<<endl;
            $$=new Info();$$->type=$2->type;
            $$->name=$2->name;
            $$->operation=$1;
            $$->val=addnode("factor");$1=addnode(string("NOSYMBOL") );addedge($$->val, $1);addedge($$->val, $2->val);}
      |power { //cout<<"factor 4"<<endl;
            $$=new Info();$$->name=$1->name;$$->type=$1->type;$$->c=$1->c;$$->vec=$1->vec;$$->start=$1->start;
            $$->index=$1->index;
             $$->val=$1->val;}
      ;

power: atom_expr DOUBLE_STAR factor {//cout<<"power 1"<<endl;
            $$=new Info();$$->type=$1->type;
            $$->index = threeacir->insert_assignment($1->name,$3->name,$2);
            $$->name = threeacir->get_var($$->index);
            $$->start=$1->start;

            $$->val=addnode("power");addedge($$->val, $1->val);$2=addnode(string("DOUBLE_STAR"));addedge($$->val, $2);addedge($$->val, $3->val);}
     | atom_expr {//cout<<"power 2"<<endl;
            $$=new Info();$$->name=$1->name;$$->type=$1->type;$$->c=$1->c;$$->vec=$1->vec;$$->start=$1->start;
            $$->index=$1->index;
             $$->val=$1->val;}
     ;

atom_expr: atom trailer_sure {//cout<<"atom_expr 1 entered"<<endl;//cout<<$1->name<<endl; ////cout<<$2->type<<$2->c<<endl;

                $$=new Info();
                //if($2->c!=-1)$$->type=$1->type;
                //else $$->type=$2->type;


                if($2->c==4000){
                    //cout<<"atom_expr 1 entered657"<<endl;
                    $$->name=$2->name;
                    $$->index=$1->index;
                    $$->start=$1->start;
                    $$->type=$2->type;
        
                }

                else if($2->c==9999){
                    vector<pair<string,int>>vec;
                    func* temp = GlobalSymbolTable->search_func( $2->name, $1->name);
                    if(temp==NULL){
                        temp = GlobalSymbolTable->search_func( $2->name, $1->type);
                        if(temp==NULL) yyerror1("function is defined before use"+$1->name+"."+$2->name,yylineno);
                    }

                    //cout<<temp->parameters_vec.size() << " "<< $2->parameters_vec.size()<<endl;
                    if(temp->parameters_vec.size()!=$2->parameters_vec.size()){
                        if(temp->parameters_vec.size()!=$2->parameters_vec.size()+1) 
                            yyerror1("number of parameters in function does not match",yylineno);
                    }
                    int k=temp->parameters_vec.size();
                    int p=$2->parameters_vec.size();
                    //cout<<k<<" "<<p<<endl;
                    int i=0,j=0;
                    if(k==p+1) i=1;
                    for(i;i<k;i++){
                        //cout<<i <<" "<<j<<" "<<temp->parameters_vec[i]->type <<" "<<$2->parameters_vec[i]->type<<" "<<GlobalSymbolTable->type_check($2->parameters_vec[j]->type,temp->parameters_vec[i]->type)<<endl;
                        if(GlobalSymbolTable->type_check($2->parameters_vec[j]->type,temp->parameters_vec[i]->type)){

                            //cout<< temp->parameters_vec[i]->type <<" "<<$2->parameters_vec[i]->type<<endl;

                        yyerror1("6 there is type mismatch in parameters of function "+$1->name,yylineno);}
                        vec.push_back({$2->parameters_vec[j]->name,type_size_map[$2->parameters_vec[j]->type]});
                        j++;}


                        for(i=0;i<$2->parameters_vec.size();i++){
                        threeacir->insert_two_word_instr("\tparam ",$2->parameters_vec[i]->name);
                        }
                        $$->index=threeacir->insert_two_word_instr("\tcall "+$2->name,to_string($2->parameters_vec.size()));
                        $$->start=$2->start;
                        //cout<<"atom_expr 1 entered111"<<endl;

                }
                else if($2->c==4444){
                    //cout<<"atom_expr 1 entered6543"<<endl;
                    $$->index=threeacir->insert_two_word_instr("\tcall "+$2->name,"");
                    $$->start=$$->index;
                 //cout<<"atom_expr 1 entered8976"<<endl;
                }


                else{
                    int p=$1->type.size();
                    if(p>4&&($1->type.substr(0,4)=="list")){
                        string s = $1->type.substr(4,p-4);
                        
                        $$->type=s; }
            
                    $$->name=$2->name;
                    nor_sym*temp=GlobalSymbolTable->search_nor_sym($1->name,GlobalSymbolTable->curr_scope);
                    $$->index = threeacir->insert_assignment($2->name,"1","*int","");
                    string t1 = threeacir->get_var($$->index);
                    int t4 = threeacir->insert_assignment(t1,to_string(type_size_map[temp->type]),"*int",t1);
                    int t3 = threeacir->insert_get_from_symtable(GlobalSymbolTable->curr_scope,$1->name,"",temp->offset);


                    $$->name = "*( "+threeacir->get_var(t3)+" + "+threeacir->get_var(t4)+" )";
                }
               
                $$->start=$2->start;

                  //cout<<"atom_expr 1 exited"<<endl;
                $$->val=addnode("atom_expr");addedge($$->val, $1->val);addedge($$->val, $2->val);}
            | atom function_para_sure{ ////cout<<"atom_expr2"<<endl;
                $$=new Info();$$->type=$1->type;
                vector<pair<string,int>>vec;

                if($1->isfunc==true && $1->name!="print" && $1->name!="input" && $1->name!="len" && $1->name!="range"){
                    ////cout<<$1->parameters_vec.size()<<" "<<$2->parameters_vec.size()<<endl;
                  if($1->parameters_vec.size()!=$2->parameters_vec.size())
                      yyerror1("number of parameters in function does not match",yylineno);
                  int k=$1->parameters_vec.size();
                  for(int i=0;i<k;i++){
                    if(GlobalSymbolTable->type_check($2->parameters_vec[i]->type,$1->parameters_vec[i]->type)){

                       yyerror1("6 there is type mismatch in parameters of function "+$1->name,yylineno);}
                    vec.push_back({$2->parameters_vec[i]->name,type_size_map[$2->parameters_vec[i]->type]});
                  }
                }

                if($1->name=="print") {
                    $$->index = threeacir->insert_two_word_instr("\tprint",$2->name);
                    $$->name=threeacir->get_var($$->index);
                    $$->start = $$->index;
                }
                else if($1->name=="len"){
                    ////cout<<"ggtgtf hvgfgyh hggyfgt vgvgyfg "<<$2->name<<endl;
                    $$->index = threeacir->insert_assignment("\tlen",$2->name,"of","");
                    $$->name=threeacir->get_var($$->index);
                    $$->start = $$->index;
                }
                else if($1->name=="input"){
                    $$->index = threeacir->insert_assignment("\tinput",$2->name,"of","");
                    $$->name=threeacir->get_var($$->index);
                    $$->start = $$->index;
                }
                else if($1->name=="range"){
                    $$->index = threeacir->insert_assignment("\trange",$2->name,"of","");
                    $$->name=threeacir->get_var($$->index);
                    $$->start = $$->index;
                }


                else{
                    for(int i=0;i<$2->parameters_vec.size();i++){
                        threeacir->insert_two_word_instr("\tparam ",$2->parameters_vec[i]->name);
                    }
                    if($2->parameters_vec.size())
                         $$->index=threeacir->insert_two_word_instr("\tcall "+$1->name,to_string($2->parameters_vec.size()));
                    else $$->index=threeacir->insert_two_word_instr("\tcall "+$1->name,"");

                    if($2->c!=4444) $$->start=$2->start;
                    else $$->start=$$->index;

                }
                $$->c=0;
                $$->parameters_vec=$2->parameters_vec;


                $$->val=addnode("atom_expr");addedge($$->val, $1->val);addedge($$->val, $2->val);
            }
         | atom { ////cout<<"atom_expr 3"<<endl;
                 $$=new Info();$$->name=$1->name;$$->type=$1->type;$$->c=$1->c;$$->vec=$1->vec;$$->start=$1->start;
                 $$->index=$1->index;$$->val=$1->val;}
         ;

trailer_sure: trailer {////cout<<"trailer_sure 1"<<endl; ////cout<<$1->start<<endl; ////cout<<$1->type<<endl;
                $$=new Info();
                $$->c =$1->c;
                $$->type=$1->type;
                $$->name=$1->name;
                $$->start=$1->start;
                $$->index=$1->index;
                $$->val=$1->val;
                }
                | trailer function_para { //cout<<"what the hell wr lost the name "<<$1->name;

                    $$=new Info();
                    if($2->c==4444) $$->c=$2->c;
                    else $$->c =9999;
                    $$->type=$1->type;
                    $$->name=$1->name;
                    $$->start=$2->start;
                    $$->index=$1->index;
                    $$->parameters_vec=$2->parameters_vec;
                    $$->val=addnode("trailer_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);

                };
function_para_sure: function_para {////cout<<"function_para_sure1"<<endl;
                $$=new Info();
                $$->c =$1->c;
                $$->parameters_vec=$1->parameters_vec;
                $$->type=$1->type;
                $$->name=$1->name;
                $$->start=$1->start;
                $$->index=$1->index;
                $$->val=$1->val;
                }
            | function_para_sure function_para{////cout<<"function_para_sure 2"<<endl;
                $$=new Info();
                $$->c =$1->c;
                $$->parameters_vec=$1->parameters_vec;
                $$->type=$1->type;
                $$->name=$1->name;
                $$->start=$1->start;
                $$->index=$2->index;
                $$->val=addnode("function_para_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);
            }
            ;
atom: CIROPEN testlist_comp CIRCLOSE { ////cout<<"atom 1"<<endl;
         $$=new Info(); $$->type=$2->type;
         $$->val=addnode("atom");$1=addnode(string("CIROPEN") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("CIRCLOSE") );addedge($$->val, $3);}
    | CIROPEN CIRCLOSE { ////cout<<"atom 2"<<endl;
         $$=new Info(); $$->c=0;
         $$->val=addnode("atom");$1=addnode(string("CIROPEN") );addedge($$->val, $1);$2=addnode(string("CIRCLOSE"));addedge($$->val, $2);}
    | SQOPEN testlist_comp SQCLOSE { ////cout<<"atom 3"<<endl;
        int k=GlobalSymbolTable->curr_sym_tbl->nor_sym_vec.size();
        GlobalSymbolTable->curr_sym_tbl->nor_sym_vec[k-1]->isarray=true;
        $$ = new Info(); $$->type=$2->type;
        GlobalSymbolTable->curr_sym_tbl->nor_sym_vec[k-1]->size=type_size_map[$2->type]*($2->c);

        $$->c=$2->c;

        $$->vec=$2->vec;

        $$->val=addnode("atom");$1=addnode(string("SQOPEN") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("SQCLOSE") );addedge($$->val, $3);}
    | SQOPEN SQCLOSE { ////cout<<"atom 4"<<endl;
        $$=new Info();
        int k=GlobalSymbolTable->curr_sym_tbl->nor_sym_vec.size();
        GlobalSymbolTable->curr_sym_tbl->nor_sym_vec[k-1]->isarray=true;
        $$ = new Info();
        GlobalSymbolTable->curr_sym_tbl->nor_sym_vec[k-1]->size=0;
        $$->val=addnode("atom");$1=addnode(string("SQOPEN") );addedge($$->val, $1);$2=addnode(string("SQCLOSE"));addedge($$->val, $2);}
    | CUOPEN CUCLOSE {////cout<<"atom 5"<<endl;
         $$=new Info();$$->val=addnode("atom");$1=addnode(string("CUOPEN") );addedge($$->val, $1);$2=addnode(string("CUCLOSE"));addedge($$->val, $2);}
    | INT { ////cout<<"atom 6"<<endl;
           $$=new Info();
           $$->type="int";
           $$->name=$1;
           $$->val=addnode("atom");$1=addnode(string("INT") );addedge($$->val, $1);}
    | LISTINT { ////cout<<"atom 7"<<endl;
           $$=new Info();
           $$->type="int";
           $$->name=$1;
           $$->c=-100;
           $$->val=addnode("atom");$1=addnode(string("LISTINT") );addedge($$->val, $1);}
    | LISTFLOAT { ////cout<<"atom 8"<<endl;
           $$=new Info();
           $$->type="float";
           $$->name=$1;
           $$->val=addnode("atom");$1=addnode(string("LISTFLOAT") );addedge($$->val, $1);}
    | LISTSTRING { ////cout<<"atom 9"<<endl;
           $$=new Info();
           $$->type="string";
           $$->name=$1;
           $$->val=addnode("atom");$1=addnode(string("LISTSTRING") );addedge($$->val, $1);}
    | LISTBOOL {////cout<<"atom 10"<<endl;
           $$=new Info();
           $$->type="bool";
           $$->name=$1;
           $$->val=addnode("atom");$1=addnode(string("LISTBOOL") );addedge($$->val, $1);}
    | LIST {  ////cout<<"atom 11"<<endl;
           $$=new Info();
           $$->type="list";
           $$->name=$1;
           $$->val=addnode("atom");$1=addnode(string("LIST") );addedge($$->val, $1);}
    | FLOAT { ////cout<<"atom 12"<<endl;
            $$=new Info();
            $$->type="float";
            $$->name=$1;
            $$->val=addnode("atom");$1=addnode(string("FLOAT") );addedge($$->val, $1);}
    | STR { ////cout<<"atom 13"<<endl;
            $$=new Info();
            $$->type="string";
            $$->name=$1;
           $$->val=addnode("atom");$1=addnode(string("STR") );addedge($$->val, $1);}
    | BOOL { ////cout<<"atom 14"<<endl;
            $$=new Info();
             $$->type="bool";
             $$->name=$1;
            $$->val=addnode("atom");$1=addnode(string("BOOL") );addedge($$->val, $1);}
    | NUMBER { ////cout<<"atom 15"<<endl; ////cout<<"found the number "<<$1<<endl;
              $$=new Info();
              $$->type="int";
              $$->name=$1;
              $$->start=threeacir->quadruple.size();
              $$->index=$$->start;
              $$->val=addnode("atom");
              $1=addnode(string("NUMBER") );addedge($$->val, $1);}
    | FLOAT_NUMBER { ////cout<<"atom 16"<<endl;
               $$=new Info();
               $$->type="float";
               $$->name=$1;
               $$->start=threeacir->quadruple.size()-1;
               $$->index=$$->start;
               $$->val=addnode("atom");$1=addnode(string("FLOAT_NUMBER") );addedge($$->val, $1);}
    | IMAGINARY_NUMBER { ////cout<<"atom 17"<<endl;
              $$=new Info();
               $$->type="inumber";
               $$->name=$1;
               $$->start=threeacir->quadruple.size()-1;
               $$->index=$$->start;
               $$->val=addnode("atom");$1=addnode(string("IMAGINARY_NUMBER") );addedge($$->val, $1);}
    | string_sure { ////cout<<"atom 18"<<endl;
                   $$=new Info();
                   $$->type="string";
                   $$->start=threeacir->quadruple.size()-1;
                   $$->index=$$->start;
                   $$->name=$1->name;
                   $$->val=$1->val;}
    | THREE_DOT { ////cout<<"atom 19"<<endl;
          $$=new Info();$$->val=addnode("atom");$1=addnode(string("THREE_DOT") );addedge($$->val, $1);}
    | NONE { ////cout<<"atom 20"<<endl;
               $$=new Info();
               $$->type="none";
               $$->name=$1;
      $$->val=addnode("atom");$1=addnode(string("NONE") );addedge($$->val, $1);}
    | TRUE { ////cout<<"atom 21"<<endl;
            $$=new Info();
            $$->type="bool";
            $$->name=$1;
            $$->val=addnode("atom");$1=addnode(string("TRUE") );addedge($$->val, $1);}
    | FALSE { ////cout<<"atom 22"<<endl;
            $$=new Info();
            $$->type="bool";
            $$->name=$1;
            $$->val=addnode("atom");$1=addnode(string("FALSE") );addedge($$->val, $1);}
    | IDENTIFIER {////cout<<"atom 23"<<endl; ////cout<<"we have found an Identifier named : "<<$1<<endl;

        loc_sym_tbl*curr=GlobalSymbolTable->scope_table_map[GlobalSymbolTable->curr_sym_tbl->scope];
        $$ = new Info();
        $$->start=threeacir->quadruple.size();
        $$->index=$$->start;
        ////cout<<$$->index<<endl;
        nor_sym* temp1= GlobalSymbolTable->search_nor_sym( $1, GlobalSymbolTable->curr_scope);
        func* temp2 = GlobalSymbolTable->search_func( $1, GlobalSymbolTable->curr_scope);
        Class* temp3 = GlobalSymbolTable->search_class( $1, GlobalSymbolTable->curr_scope);
        func* temp4 = GlobalSymbolTable->search_pre_func( $1, GlobalSymbolTable->curr_scope);
        if(temp1!=NULL){
          $$->name=$1;
          $$->type=temp1->type;
        }
        else if(temp2!=NULL){
          if(temp2->ret_type.size()==0) $$->type="none";
          else $$->type=temp2->ret_type;
          $$->name=$1;
          $$->isfunc=true;
          $$->parameters_vec=temp2->parameters_vec;
        }
        else if(temp3!=NULL){
          $$->name=$1;
          $$->type=temp3->name;
        }
        else if(temp4!=NULL){
          $$->name=temp4->name;
          $$->isfunc=true;
          if(temp4->ret_type.size()==0) $$->type="none";
          else $$->type=temp4->ret_type;
        }
        else{
          nor_sym* newsym= new nor_sym($1,yylineno);
          $$->name=$1;
          newsym->name=$1;
          newsym->offset = GlobalSymbolTable->curr_sym_tbl->offset;
          GlobalSymbolTable->insert(newsym);
        }
        $$->val=addnode("atom");$1=addnode(string("IDENTIFIER") );addedge($$->val, $1);}
    ;



testlist: test comma_test_sure COMMA {
            $$ = new Info();
            $$->type=$1->type;
            $$->start=$1->start;
            $$->index=$2->index;
            $$->val=addnode("testlist");addedge($$->val, $1->val);addedge($$->val, $2->val);$3=addnode(string("COMMA") );addedge($$->val, $3);}
        | test comma_test_sure {
            $$ = new Info();
            $$->type=$1->type;
            $$->start=$1->start;
            $$->index=$2->index;
            $$->val=addnode("testlist");addedge($$->val, $1->val);addedge($$->val, $2->val);}
        | test COMMA {
            $$= new Info();
            $$->type=$1->type;
            $$->name=$1->name;
            $$->start=$1->start;
            $$->index=$1->index;
            $$->val=addnode("testlist");addedge($$->val, $1->val);$2=addnode(string("COMMA"));addedge($$->val, $2);}
        | test {
            $$= new Info();
            $$->type=$1->type;
            $$->name=$1->name;
            $$->val=$1->val;
            $$->start=$1->start;
            $$->index=$1->index;}
        ;

testlistreturn:test COMMA {
                  $$= new Info();
                  $$->type=$1->type;
                  $$->name=$1->name;
                  $$->start=$1->start;
                  $$->index=$1->index;
                  $$->val=addnode("testlistreturn");addedge($$->val, $1->val);$2=addnode(string("COMMA"));addedge($$->val, $2);}
              | test {
                  $$= new Info();
                  $$->type=$1->type;
                  $$->val=$1->val;
                  $$->name=$1->name;
                  $$->start=$1->start;
                  $$->index=$1->index;}
              ;

comma_test: COMMA test { ////cout<<"comma_test"<<endl;
        $$ = new Info();
        $$->c=1;
        $$->type=$2->type;
        $$->name=$2->name;
        $$->start=$2->start;
        $$->index=$2->index;
        $$->val=addnode("comma_test");$1=addnode(string("COMMA") );addedge($$->val, $1);addedge($$->val, $2->val);}
  ;

comma_test_sure: comma_test { ////cout<<"comma_test_sure1"<<endl;
            $$ = new Info();
            $$->c=1;
            $$->vec.push_back($1->name);
            $$->val=$1->val;
            $$->start=$1->start;
            $$->index=$1->index;}
       | comma_test_sure comma_test { ////cout<<"comma_test_sure2"<<endl;
            $$ = new Info();
            $$->c=$1->c+1;
            for(int i=0;i<$1->vec.size();i++) $$->vec.push_back($1->vec[i]);
            $$->vec.push_back($2->name);
            $$->start=$1->start;
            $$->index=$2->index;
            $$->val=addnode("comma_test_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
       ;

testlist_comp: test comma_test_sure COMMA { ////cout<<"testlist_comp1"<<endl;
                   $$=new Info(); $$->type=$1->type; $$->c=$2->c+1;
                   $$->vec.push_back($1->name);
                   for(int i=0;i<$2->vec.size();i++) $$->vec.push_back($2->vec[i]);
                   $$->start=$1->start;
                   $$->index=$2->index;
                   $$->val=addnode("testlist_comp");addedge($$->val, $1->val);addedge($$->val, $2->val);$3=addnode(string("COMMA") );addedge($$->val, $3);}
             | test COMMA { ////cout<<"testlist_comp2"<<endl;
                  $$=new Info(); $$->type=$1->type; $$->c=1;$$->vec.push_back($1->name);
                  $$->start=$1->start;
                  $$->index=$1->index;
                  $$->val=addnode("testlist_comp");addedge($$->val, $1->val);$2=addnode(string("COMMA"));addedge($$->val, $2);}
             | test comma_test_sure { ////cout<<"testlist_comp3"<<endl;
                  $$=new Info(); $$->type=$1->type; $$->c=$2->c+1;
                  $$->vec.push_back($1->name);
                  for(int i=0;i<$2->vec.size();i++) $$->vec.push_back($2->vec[i]);
                  $$->start=$1->start;
                  $$->index=$2->index;
                  $$->val=addnode("testlist_comp");addedge($$->val, $1->val);addedge($$->val, $2->val);}
             | test { ////cout<<"testlist_comp4"<<endl;
                  $$=new Info(); $$->type=$1->type; $$->c=1;
                  $$->start=$1->start;
                  $$->index=$1->index;
                  $$->val=$1->val;$$->vec.push_back($1->name);}
             ;

exprlist: expr comma_expr_sure COMMA { $$=new Info();$$->val=addnode("exprlist");addedge($$->val, $1->val);addedge($$->val, $2->val);$3=addnode(string("COMMA") );addedge($$->val, $3);}
        | expr COMMA { $$=new Info();$$->val=addnode("exprlist");addedge($$->val, $1->val);$2=addnode(string("COMMA"));addedge($$->val, $2);}
        | expr comma_expr_sure { $$=new Info();$$->val=addnode("exprlist");addedge($$->val, $1->val);addedge($$->val, $2->val);}
        | expr { $$=new Info();
            $$->val=$1->val;}
        ;

comma_expr: COMMA expr { $$=new Info();$$->val=addnode("comma_expr");$1=addnode(string("COMMA") );addedge($$->val, $1);addedge($$->val, $2->val);}
    ;

comma_expr_sure: comma_expr { $$=new Info();$$->val=$1->val;}
          | comma_expr_sure comma_expr { $$=new Info();$$->val=addnode("comma_expr_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
          ;


string_sure:STRING {
                $$=new Info();
                $$->name=$1;
                $$->val=addnode("string_sure");$1=addnode(string("STRING") );addedge($$->val, $1);}
           |STRING string_sure {
                $$=new Info();
                $$->name=$1;
                $$->val=addnode("string_sure");$1=addnode(string("STRING") );addedge($$->val, $1);addedge($$->val, $2->val);}
           ;

trailer: SQOPEN subscriptlist SQCLOSE { //cout<<"trailer 1"<<endl;
              //cout<<$2->type<<" "<<$2->name<<endl;
              $$=new Info();
              $$->type=$2->type;
              $$->name=$2->name;
              $$->start=$2->start;
              $$->val=addnode("trailer");$1=addnode(string("SQOPEN") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("SQCLOSE") );addedge($$->val, $3);}
       |  DOT IDENTIFIER { //cout<<"trailer2 entered"<<endl;
              loc_sym_tbl*curr=GlobalSymbolTable->scope_table_map[GlobalSymbolTable->curr_sym_tbl->scope];
                $$ = new Info();
                $$->c=4000;
                ////cout<<$$->index<<endl;
                nor_sym* temp1= GlobalSymbolTable->search_nor_sym( $2, GlobalSymbolTable->curr_scope);
                func* temp2 = GlobalSymbolTable->search_func( $2, GlobalSymbolTable->curr_scope);
                Class* temp3 = GlobalSymbolTable->search_class( $2, GlobalSymbolTable->curr_scope);
                func* temp4 = GlobalSymbolTable->search_pre_func( $2, GlobalSymbolTable->curr_scope);
                if(temp1!=NULL){
                $$->name=$2;
                $$->type=temp1->type;
                }
                else if(temp2!=NULL){
                if(temp2->ret_type.size()==0) $$->type="none";
                else $$->type=temp2->ret_type;
                $$->name=$2;
                $$->isfunc=true;
                $$->parameters_vec=temp2->parameters_vec;
                }
                else if(temp3!=NULL){
                $$->name=$2;
                $$->type=temp3->name;
                }
                else if(temp4!=NULL){
                $$->name=temp4->name;
                $$->isfunc=true;
                if(temp4->ret_type.size()==0) $$->type="none";
                else $$->type=temp4->ret_type;
                }
                else{
                nor_sym* newsym= new nor_sym($1,yylineno);
                $$->name=$2;
                newsym->name=$2;
                newsym->offset = GlobalSymbolTable->curr_sym_tbl->offset;
                GlobalSymbolTable->insert(newsym);
                }


               //cout<<"trailer2 exited"<<endl;
              $$->val=addnode("trailer");$1=addnode(string("DOT") );addedge($$->val, $1);$2=addnode(string("IDENTIFIER"));addedge($$->val, $2);}
       |  DOT DUNDER {
              $$=new Info();

                loc_sym_tbl*curr=GlobalSymbolTable->scope_table_map[GlobalSymbolTable->curr_sym_tbl->scope];
                $$ = new Info();
                $$->c=4000;
                ////cout<<$$->index<<endl;
                nor_sym* temp1= GlobalSymbolTable->search_nor_sym( $2, GlobalSymbolTable->curr_scope);
                func* temp2 = GlobalSymbolTable->search_func( $2, GlobalSymbolTable->curr_scope);
                Class* temp3 = GlobalSymbolTable->search_class( $2, GlobalSymbolTable->curr_scope);
                func* temp4 = GlobalSymbolTable->search_pre_func( $2, GlobalSymbolTable->curr_scope);
                if(temp1!=NULL){
                $$->name=$2;
                $$->type=temp1->type;
                }
                else if(temp2!=NULL){
                if(temp2->ret_type.size()==0) $$->type="none";
                else $$->type=temp2->ret_type;
                $$->name=$2;
                $$->isfunc=true;
                $$->parameters_vec=temp2->parameters_vec;
                }
                else if(temp3!=NULL){
                $$->name=$2;
                $$->type=temp3->name;
                }
                else if(temp4!=NULL){
                $$->name=temp4->name;
                $$->isfunc=true;
                if(temp4->ret_type.size()==0) $$->type="none";
                else $$->type=temp4->ret_type;
                }
                else{
                nor_sym* newsym= new nor_sym($1,yylineno);
                $$->name=$2;
                newsym->name=$2;
                newsym->offset = GlobalSymbolTable->curr_sym_tbl->offset;
                GlobalSymbolTable->insert(newsym);
                }


              $$->val=addnode("trailer");$1=addnode(string("DOT") );addedge($$->val, $1);$2=addnode(string("DUNDER"));addedge($$->val, $2);}
       ;

function_para: CIROPEN arglist CIRCLOSE {
                $$=new Info();
                $$->parameters_vec=$2->parameters_vec;
                $$->type=$2->type;
                $$->name=$2->name;
                $$->start=$2->start;
                $$->index=$2->index;
                $$->val=addnode("function_para");$1=addnode(string("CIROPEN") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("CIRCLOSE") );addedge($$->val, $3);}
            |  CIROPEN  CIRCLOSE {
                    $$=new Info();
                    $$->parameters_vec={};
                    $$->start=4444;
                    $$->val=addnode("function_para");$1=addnode(string("CIROPEN") );addedge($$->val, $1);$2=addnode(string("CIRCLOSE"));addedge($$->val, $2);}

arglist: argument comma_argument_sure {
            $$ = new Info();
            $$->parameters_vec.push_back($1->parameters_vec[0]);
            for(int i=0;i<$2->parameters_vec.size();i++) $$->parameters_vec.push_back($2->parameters_vec[i]);
            $$->type=$1->type;
            $$->name=$1->name;
            $$->index = $2->index; $$->start = $1->start;
            $$->val=addnode("arglist");addedge($$->val, $1->val);addedge($$->val, $2->val);}
       | argument {
            $$ = new Info();
            $$->parameters_vec=$1->parameters_vec;
            $$->type=$1->type;
            $$->val=$1->val;
            $$->name=$1->name;
            $$->index = $1->index; $$->start = $1->start;}
       | argument comma_argument_sure COMMA {
            $$ = new Info();
            $$->parameters_vec.push_back($1->parameters_vec[0]);
            for(int i=0;i<$2->parameters_vec.size();i++) $$->parameters_vec.push_back($2->parameters_vec[i]);
            $$->type=$1->type;
            $$->name=$1->name;
            $$->index = $2->index; $$->start = $1->start;
            $$->val=addnode("arglist");addedge($$->val, $1->val);addedge($$->val, $2->val);$3=addnode(string("COMMA") );addedge($$->val, $3);}
       | argument COMMA {
            $$ = new Info();
            $$->parameters_vec.push_back($1->parameters_vec[0]);
            $$->type=$1->type;
            $$->name=$1->name;
            $$->index = $1->index; $$->start = $1->start;
            $$->val=addnode("arglist");addedge($$->val, $1->val);$2=addnode(string("COMMA"));addedge($$->val, $2);}
       ;

comma_argument:COMMA argument {
        $$ = new Info();
        $$->parameters_vec.push_back($2->parameters_vec[0]);
        $$->type=$2->type;
        $$->index = $2->index; $$->start = $2->start;
        $$->val=addnode("comma_argument");$1=addnode(string("COMMA") );addedge($$->val, $1);addedge($$->val, $2->val);}
  ;

comma_argument_sure: comma_argument {
            $$ = new Info();
            $$->parameters_vec.push_back($1->parameters_vec[0]);
            $$->type=$1->type;
            $$->val=$1->val;
            $$->index = $1->index; $$->start = $1->start;}
       | comma_argument_sure comma_argument {
            $$ = new Info();
            for(int i=0;i<$1->parameters_vec.size();i++) $$->parameters_vec.push_back($1->parameters_vec[i]);
            $$->parameters_vec.push_back($2->parameters_vec[0]);
            $$->type=$1->type;
            $$->index = $2->index; $$->start = $1->start;
            $$->val=addnode("comma_argument_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
       ;

argument: test {
            $$ = new Info();
            nor_sym* temp= new nor_sym($1->name,yylineno);
            temp->type=$1->type;
            $$->parameters_vec.push_back(temp);
            $$->type=$1->type;
            $$->val=$1->val;
            $$->name=$1->name;
            $$->index = $1->index; $$->start = $1->start;}
        | test EQUAL test {
             if(GlobalSymbolTable->type_check($3->type,$1->type)) yyerror1("7 There is a type mismatch",yylineno);

            $$->index = threeacir->insert_assignment($3->name,"","",$1->name);

            $$ = new Info();
            $$->start = $1->start;
            nor_sym* temp= new nor_sym($1->name,yylineno);
            temp->type=$1->type;
            $$->parameters_vec.push_back(temp);
            $$->type=$1->type;
            $$->name=$1->name;
            $$->val=addnode("argument");addedge($$->val, $1->val);$2=addnode(string("EQUAL"));addedge($$->val, $2);addedge($$->val, $3->val);}
        ;

subscriptlist: subscript comma_subscript_sure { ////cout<<"subscriptlist1"<<endl;
                    $$=new Info();$$->type=$1->type;
                    $$->start=$1->start;
                    $$->index=$2->index;$$->val=addnode("subscriptlist");addedge($$->val, $1->val);addedge($$->val, $2->val);}
             | subscript { ////cout<<"subscriptlist2"<<endl;
                $$=new Info();$$->type=$1->type;
                    $$->val=$1->val;
                    $$->name=$1->name;
                    $$->start=$1->start;
                    $$->index=$1->index;
                }
             | subscript comma_subscript_sure COMMA { ////cout<<"subscriptlist3"<<endl;
                   $$=new Info();$$->type=$1->type;
                    $$->start=$1->start;
                    $$->index=$2->index;$$->val=addnode("subscriptlist");addedge($$->val, $1->val);addedge($$->val, $2->val);$3=addnode(string("COMMA") );addedge($$->val, $3);}
             | subscript COMMA { ////cout<<"subscriptlist4"<<endl;
                   $$=new Info();$$->type=$1->type;
                    $$->start=$1->start;
                    $$->index=$1->index;$$->val=addnode("subscriptlist");addedge($$->val, $1->val);$2=addnode(string("COMMA"));addedge($$->val, $2);}
             ;

comma_subscript: COMMA subscript {
                    $$=new Info();$$->type=$2->type;
                    $$->start=$2->start;
                    $$->index=$2->index;$$->val=addnode("comma_subscript");$1=addnode(string("COMMA") );addedge($$->val, $1);addedge($$->val, $2->val);}
     ;

comma_subscript_sure: comma_subscript {
                    $$=new Info();$$->type=$1->type;
                    $$->start=$1->start;
                    $$->index=$1->index;$$->val=$1->val;}
          | comma_subscript_sure comma_subscript {
            $$=new Info();$$->type=$1->type;
            $$->start=$1->start;
            $$->index=$2->index;
            $$->val=addnode("comma_subscript_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
          ;

subscript: test { //cout<<"subscript1"<<endl; 
              //cout<<$1->name<<endl;
              //cout<<$1->type<<endl;
              if($1->type!="int") yyerror1("array index is not an integer",yylineno);
              $$=new Info();$$->type=$1->type;
              $$->name=$1->name;
              $$->start=$1->start;
              $$->index=$1->index;
              $$->val=$1->val;}
         | test  COLON test { //cout<<"subscript2"<<endl;
               if(GlobalSymbolTable->type_check($3->type,$1->type)) yyerror1(" 45 type mismatch in line ",yylineno);
               $$=new Info();$$->type=$1->type;
               $$->name=$3->name;
               $$->start=$1->start;
              $$->index=$1->index;
              $$->val=addnode("subscript");addedge($$->val, $1->val);$2=addnode(string("COLON"));addedge($$->val, $2);addedge($$->val, $3->val);}
         | test  COLON { //cout<<"subscript3"<<endl;
            $$=new Info();$$->type=$1->type;
            $$->name=$1->name;
            $$->start=$1->start;
              $$->index=$1->index;
            $$->val=addnode("subscript");addedge($$->val, $1->val);$2=addnode(string("COLON"));addedge($$->val, $2);}
         | COLON test { //cout<<"subscript4"<<endl;
            $$=new Info();$$->type=$2->type;
            $$->start=$2->start;
              $$->index=$2->index;
            $$->val=addnode("subscript");$1=addnode(string("COLON") );addedge($$->val, $1);addedge($$->val, $2->val);}
         | COLON { //cout<<"subscript5"<<endl;
            $$=new Info(); $$->val=addnode("subscript");$1=addnode(string("COLON") );addedge($$->val, $1);}
         ;

/*comparision operation from not-test in test*/
comp_op: LESS {
            $$=new Info();$$->name=$1;
            $$->val=addnode("comp_op");$1=addnode(string("LESS") );addedge($$->val, $1);}
       |GREATER {
            $$=new Info();$$->name=$1;
            $$->val=addnode("comp_op");$1=addnode(string("GREATER") );addedge($$->val, $1);}
       |DOUBLE_EQUAL {
            $$=new Info();$$->name=$1;
            $$->val=addnode("comp_op");$1=addnode(string("DOUBLE_EQUAL") );addedge($$->val, $1);}
       |GREATER_EQUAL {
            $$=new Info();$$->name=$1;
            $$->val=addnode("comp_op");$1=addnode(string("GREATER_EQUAL") );addedge($$->val, $1);}
       |LESS_EQUAL {
            $$=new Info();$$->name=$1;
            $$->val=addnode("comp_op");$1=addnode(string("LESS_EQUAL") );addedge($$->val, $1);}
       |GREATER_LESS {
            $$=new Info();$$->name=$1;
            $$->val=addnode("comp_op");$1=addnode(string("GREATER_LESS") );addedge($$->val, $1);}
       |NOT_EQUAL {
            $$=new Info();$$->name=$1;
            $$->val=addnode("comp_op");$1=addnode(string("NOT_EQUAL") );addedge($$->val, $1);}
       |IN {
            $$=new Info();$$->name=$1;
            $$->val=addnode("comp_op");$1=addnode(string("IN") );addedge($$->val, $1);}
       |NOT IN {
            $$=new Info();string s=$1; string s1=$2;$$->name=s+s1;
            $$->val=addnode("comp_op");$1=addnode(string("NOT") );addedge($$->val, $1);$2=addnode(string("IN"));addedge($$->val, $2);}
       |IS {
            $$=new Info();$$->name=$1;
            $$->val=addnode("comp_op");$1=addnode(string("IS") );addedge($$->val, $1);}
       |IS NOT {
            $$=new Info();string s=$1; string s1=$2;$$->name=s+s1;
            $$->val=addnode("comp_op");$1=addnode(string("IS") );addedge($$->val, $1);$2=addnode(string("NOT"));addedge($$->val, $2);}
       ;

annassign:  COLON test {  //cout<<"annassign 1"<<endl;
                $$=new Info();$$->type=$2->type;
                $$->c=$2->c;
                $$->name=$2->name;
                $$->val=addnode("annassign");$1=addnode(string("COLON") );addedge($$->val, $1);addedge($$->val, $2->val);}
         |  COLON test EQUAL test {  //cout<<"annassign 2 enteered"<<endl;
                if($2->type=="none") yyerror1("variables are declared as void type",yylineno);
                //cout<<$4->type << $2->type<<endl;
                if(GlobalSymbolTable->type_check($4->type,$2->type)) yyerror1("type did not match",yylineno);
                $$=new Info();$$->c=$4->c;
                ////cout<<"is it really true "<<$4->c<<endl;
                $$->name=$4->name;
                $$->vec=$4->vec;
                $$->parameters_vec=$4->parameters_vec;
                $$->type=$2->type; $$->val=addnode("annassign");$1=addnode(string("COLON") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("EQUAL") );addedge($$->val, $3);addedge($$->val, $4->val);}
         ;

augassign: PLUS_EQUAL {
                $$=new Info();$$->name=$1;
                $$->val=addnode("augassign");$1=addnode(string("PLUS_EQUAL") );addedge($$->val, $1);}
         | MINUS_EQUAL {
            $$=new Info();$$->name=$1;
            $$->val=addnode("augassign");$1=addnode(string("MINUS_EQUAL") );addedge($$->val, $1);}
         | MULTI_EQUAL {
            $$=new Info();$$->name=$1;
            $$->val=addnode("augassign");$1=addnode(string("MULTI_EQUAL") );addedge($$->val, $1);}
         | DIVI_EQUAL {
            $$=new Info();$$->name=$1;
            $$->val=addnode("augassign");$1=addnode(string("DIVI_EQUAL") );addedge($$->val, $1);}
         | MODULO_EQUAL {
            $$=new Info();$$->name=$1;
            $$->val=addnode("augassign");$1=addnode(string("MODULO_EQUAL") );addedge($$->val, $1);}
         | AND_EQUAL {
            $$=new Info();$$->name=$1;
            $$->val=addnode("augassign");$1=addnode(string("AND_EQUAL") );addedge($$->val, $1);}
         | PIPE_EQUAL {
            $$=new Info();$$->name=$1;
            $$->val=addnode("augassign");$1=addnode(string("PIPE_EQUAL") );addedge($$->val, $1);}
         | POWER_EQUAL {
            $$=new Info();$$->name=$1;
            $$->val=addnode("augassign");$1=addnode(string("POWER_EQUAL") );addedge($$->val, $1);}
         | DOUBLE_LESS_EQUAL {
            $$=new Info();$$->name=$1;
            $$->val=addnode("augassign");$1=addnode(string("DOUBLE_LESS_EQUAL") );addedge($$->val, $1);}
         | DOUBLE_GREATER_EQUAL {
            $$=new Info();$$->name=$1;
            $$->val=addnode("augassign");$1=addnode(string("DOUBLE_GREATER_EQUAL") );addedge($$->val, $1);}
         | DOUBLE_MULTI_EQUAL {
            $$=new Info();$$->name=$1;
            $$->val=addnode("augassign");$1=addnode(string("DOUBLE_MULTI_EQUAL") );addedge($$->val, $1);}
         | DOUBLE_DIVI_EQUAL {
            $$=new Info();$$->name=$1;
            $$->val=addnode("augassign");$1=addnode(string("DOUBLE_DIVI_EQUAL") );addedge($$->val, $1);}
         ;

flow_stmt: break_stmt { $$=new Info();$$->val=$1->val;}
          | continue_stmt { $$=new Info();$$->val=$1->val;}
          | return_stmt { $$=new Info();$$->val=$1->val;}
          | raise_stmt { $$=new Info();$$->val=$1->val;}
          ;

break_stmt: BREAK {
                $$ = new Info();
                $$->index = threeacir->insert_incomplete_jump("break");
                $$->start = $$->index;
                ////cout<<" break "<<$$->index<<endl;
                $$->val=addnode("break_stmt");$1=addnode(string("BREAK") );addedge($$->val, $1);}
          ;

continue_stmt: CONTINUE {
                $$ = new Info();
                $$->index = threeacir->insert_incomplete_jump("continue");
                $$->start = $$->index;
                $$->val=addnode("continue_stmt");$1=addnode(string("CONTINUE") );addedge($$->val, $1);}
             ;

return_stmt: RETURN { $$=new Info();
                $$->val=addnode("return_stmt");$1=addnode(string("RETURN") );addedge($$->val, $1);}
           | RETURN testlistreturn {
                $$ = new Info();
                loc_sym_tbl*temp=GlobalSymbolTable->curr_sym_tbl->parent;
                int k=temp->func_vec.size();
                if($2->type=="") temp->func_vec[k-1]->ret_type="none";
                else temp->func_vec[k-1]->ret_type=$2->type;

                $$->start = $2->start;
                threeacir->insert_two_word_instr("\tpush",$2->name);
                //threeacir->insert_two_word_instr("\tpop","basePointer");
                $$->index = threeacir->insert_two_word_instr("\treturn","");

                $$->val=addnode("return_stmt");$1=addnode(string("RETURN") );addedge($$->val, $1);addedge($$->val, $2->val);}
           ;

raise_stmt: RAISE test FROM test { $$=new Info();$$->val=addnode("raise_stmt");$1=addnode(string("RAISE") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("FROM") );addedge($$->val, $3);addedge($$->val, $4->val);}
           | RAISE test { $$=new Info();$$->val=addnode("raise_stmt");$1=addnode(string("RAISE") );addedge($$->val, $1);addedge($$->val, $2->val);}
           | RAISE  { $$=new Info();$$->val=addnode("raise_stmt");$1=addnode(string("RAISE") );addedge($$->val, $1);}
           ;



global_stmt: GLOBAL IDENTIFIER comma_identifier_sure { $$=new Info();$$->val=addnode("global_stmt");$1=addnode(string("GLOBAL") );addedge($$->val, $1);$2=addnode(string("IDENTIFIER"));addedge($$->val, $2);addedge($$->val, $3->val);}
           | GLOBAL IDENTIFIER { $$=new Info();$$->val=addnode("global_stmt");$1=addnode(string("GLOBAL") );addedge($$->val, $1);$2=addnode(string("IDENTIFIER"));addedge($$->val, $2);}
           ;

comma_identifier: COMMA IDENTIFIER { $$=new Info();$$->val=addnode("comma_identifier");$1=addnode(string("COMMA") );addedge($$->val, $1);$2=addnode(string("IDENTIFIER"));addedge($$->val, $2);}
  ;

comma_identifier_sure: comma_identifier { $$=new Info();$$->val=$1->val;}
       | comma_identifier_sure comma_identifier { $$=new Info();$$->val=addnode("comma_identifier_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
       ;

assert_stmt: ASSERT test { $$=new Info();$$->val=addnode("assert_stmt");$1=addnode(string("ASSERT") );addedge($$->val, $1);addedge($$->val, $2->val);}
           | ASSERT test COMMA test { $$=new Info();$$->val=addnode("assert_stmt");$1=addnode(string("ASSERT") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("COMMA") );addedge($$->val, $3);addedge($$->val, $4->val);}
           ;

compound_stmt: if_stmt { $$=new Info();$$->val=$1->val;}
             | while_stmt { $$=new Info();$$->val=$1->val;}
             | for_stmt { $$=new Info();$$->val=$1->val;}
             | funcdef {  //cout<<" done harshhuuuu "<<endl;
                 $$=new Info(); $$->val=$1->val;}
             | classdef { $$=new Info();$$->val=$1->val;}
             | dunder_block {  //cout<<" done harshhuluuu "<<endl;
                $$=new Info(); $$->val=$1->val;}
             ;

if_stmt: IF test  COLON suite else_if_sure ELSE COLON suite { $$=new Info();
            $$->val=addnode("if_stmt");$1=addnode(string("IF") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("COLON") );addedge($$->val, $3);addedge($$->val, $4->val);addedge($$->val, $5->val);$6=addnode(string("ELSE") );addedge($$->val, $6);$7=addnode(string("COLON") );addedge($$->val, $7);addedge($$->val, $8->val);}
       | IF test  COLON suite ELSE COLON suite {////cout<<"if_stmt2"<<endl;
            $$=new Info();

            if($2->type!="bool") yyerror1($2->type+" cannot be converted to boolean type",yylineno);


            ////cout<<"$7->start "<<$7->start << "$7->index "<<$7->index<<endl;
            ////cout<<"$4->start "<<$4->start << "$4->index "<<$4->index<<endl;
            if(!threeacir->quadruple[$7->start]->is_block || $7->start!=$7->index)
                $7->name = threeacir->get_var(threeacir->make_block($7->start));
            if(!threeacir->quadruple[$4->start]->is_block || $4->start!=$4->index)
               $4->name = threeacir->get_var(threeacir->make_block($4->start,"",$7->start));

            $$->index = threeacir->insert_if($4->start-1,$2->name,$4->name,$7->name);
            $$->start = $2->start;
            $$->name=threeacir->get_var($$->index);
            ////cout<<" start "<<$$->start<<" index "<<$$->index<<endl;
            $$->val=addnode("if_stmt");$1=addnode(string("IF") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("COLON") );addedge($$->val, $3);addedge($$->val, $4->val);$5=addnode(string("ELSE") );addedge($$->val, $5);$6=addnode(string("COLON") );addedge($$->val, $6);addedge($$->val, $7->val);}
       | IF test  COLON suite else_if_sure {
             $$=new Info();
            $$->val=addnode("if_stmt");$1=addnode(string("IF") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("COLON") );addedge($$->val, $3);addedge($$->val, $4->val);addedge($$->val, $5->val);}
       | IF test  COLON suite {//cout<<"if_stmt1"<<endl; ////cout<<$2->start<<endl;
           $$=new Info();
           if($2->type!="bool") yyerror1($2->type+" cannot be converted to boolean type",yylineno);

            if(!threeacir->quadruple[$4->start]->is_block || $4->start!=$4->index)
               $4->name = threeacir->get_var(threeacir->make_block($4->start));
            $$->index = threeacir->insert_if($4->start-1,$2->name,$4->name,"");
            $$->start = $2->start;
            $$->name=threeacir->get_var($$->index);
            ////cout<<" start "<<$$->start<<" index "<<$$->index<<endl;
            $$->val=addnode("if_stmt");$1=addnode(string("IF") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("COLON") );addedge($$->val, $3);addedge($$->val, $4->val);}
       ;

else_if:ELIF test COLON suite { $$=new Info();$$->val=addnode("else_if");$1=addnode(string("ELIF") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("COLON") );addedge($$->val, $3);addedge($$->val, $4->val);}
   ;

else_if_sure: else_if { $$=new Info();$$->val=$1->val;}
        | else_if_sure else_if { $$=new Info();$$->val=addnode("else_if_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
        ;

line_sure: NEWLINE {//cout<<" linesure1 "<<endl;
$$=new Info();$$->val=addnode("NEWLINE");$1=addnode(string("newline") );addedge($$->val, $1);}
      | line_sure NEWLINE {//cout<<" linesure2 "<<endl;
      $$=new Info();$$->val=addnode("line_sure");addedge($$->val, $1->val);$2=addnode(string("NEWLINE"));addedge($$->val, $2);}
      ;

suite: simple_stmt {//cout<<"suite1"<<endl;
            $$=new Info();
            $$->name = $1->name;
            $$->start = $1->start;
            $$->index = $1->index;
            $$->val=$1->val; }
     | line_sure INDENT line_or_newstmt_sure DEDENT {//cout<<"suite2"<<endl;
            $$=new Info();
            //cout<<"suite2  789 "<<$3->index<<endl;
            //cout<<threeacir->quadruple.size()<<endl;
            $$->name = threeacir->get_var($3->index);
   //cout<<"suite2  764689"<<endl;

            $$->start = $3->start;
            //cout<<"suite2   542456"<<endl;
            ////cout<<" uujygj "<<$3->start<<endl;
            $$->index = $3->index;
            //cout<<"suite2 23567"<<endl;
            $$->val=addnode("suite");addedge($$->val, $1->val);$2=addnode(string("INDENT"));addedge($$->val, $2);addedge($$->val, $3->val);$4=addnode(string("DEDENT") );addedge($$->val, $4);
            //cout<<"suite2 ended"<<endl;
             }
     ;

line_or_newstmt: NEWLINE { //cout<<"line_or_newstmt1"<<endl;
    $$=new Info();$$->name="NEWLINE";$$->val=addnode("line_or_newstmt");$1=addnode(string("NEWLINE") );addedge($$->val, $1);}
   | new_stmt { ////cout<<"line_or_newstmt2"<<endl;
        ////cout<<$1->start<<endl;
        $$=new Info();
        $$->name = $1->name;
        $$->start = $1->start;
        $$->index = $1->index;
        $$->val=$1->val;}
   ;

line_or_newstmt_sure: line_or_newstmt {////cout<<"line_or_newstmt_sure1"<<endl;
           ////cout<<$1->start<<endl;
            $$=new Info();
            $$->start = $1->start;
            $$->name=$1->name;
            $$->index = $1->index;$$->val=$1->val;}
        | line_or_newstmt_sure line_or_newstmt { ////cout<<"line_or_newstmt_sure2"<<endl;
            ////cout<<"$1->start "<<$1->start << "$2->start "<<$2->start<<endl;
            $$=new Info();
            if($1->name!="NEWLINE")$$->start = $1->start;
            else $$->start = $2->start;
            if($2->name=="NEWLINE") $$->index=$1->index;
            else $$->index = $2->index;
            $$->val=addnode("line_or_newstmt_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
        ;

new_stmt: simple_stmt { ////cout<<"new_stmt1"<<endl;////cout<<$1->start<<endl;
               $$=new Info();$$->name = $1->name;$$->start = $1->start;$$->index = $1->index;$$->val=$1->val;}
         | if_stmt { ////cout<<"new_stmt2"<<endl;
               $$=new Info();$$->name = $1->name;$$->start = $1->start;$$->index = $1->index;$$->val=$1->val;}
         | while_stmt {////cout<<"new_stmt3"<<endl;
               $$=new Info();$$->name = $1->name;$$->start = $1->start;$$->index = $1->index;$$->val=$1->val;}
         | for_stmt { ////cout<<"new_stmt4"<<endl;
               $$=new Info();$$->name = $1->name;$$->start = $1->start;$$->index = $1->index;$$->val=$1->val;}
         | funcdef { //cout<<"new_stmt5"<<endl;
               $$=new Info();$$->name = $1->name;$$->start = $1->start;$$->index = $1->index;$$->val=$1->val;}
         | dunder_block { //cout<<"new_stmt6"<<endl;
                $$=new Info();$$->name = $1->name;$$->start = $1->start;$$->index = $1->index;$$->val=$1->val;}
         ;

while_stmt: WHILE test  COLON suite  {
                $$=new Info();
                if($2->type!="bool") yyerror1($2->type+" cannot be converted to boolean type",yylineno);
                $$->start = $2->start;
                ////cout<<"harshini is a pig svhdvhg zvhsdgvh szvhwgdvhg sdvsnhdvhd sdvhsgdv "<<$2->start<<endl;
                if(!threeacir->quadruple[$4->start]->is_block || $4->start!=$4->index)
                    $4->name = threeacir->get_var(threeacir->make_block($4->start));
                $$->index = threeacir->insert_while($2->start,$4->start-1,$2->name,$4->name);

                $$->name=threeacir->get_var($$->start);
                $$->val=addnode("while_stmt");$1=addnode(string("WHILE") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("COLON") );addedge($$->val, $3);addedge($$->val, $4->val);}
          | WHILE test  COLON suite ELSE  COLON suite { $$=new Info();$$->val=addnode("while_stmt");$1=addnode(string("WHILE") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("COLON") );addedge($$->val, $3);addedge($$->val, $4->val);$5=addnode(string("ELSE") );addedge($$->val, $5);$6=addnode(string("COLON") );addedge($$->val, $6);addedge($$->val, $7->val);}
          ;


for_stmt: FOR exprlist IN testlist  COLON {


            $2->index=threeacir->insert_assignment("0","","",$2->name);
            $2->start=$2->index;

            $4->index=threeacir->insert_assignment($2->name,$4->name,"in","");

        }
         suite {////cout<<"forstmt2"<<endl;
            $$ = new Info();
            ////cout<<" start "<<$7->start<<" index "<<$7->index<<endl;
            for(int i=0;i<threeacir->quadruple.size();i++){
                ////cout<<threeacir->quadruple[i]->gen_threeac();
                ////cout<<endl;
            }

            int k=threeacir->insert_assignment($2->name,$2->name,"+",$2->name);
            $4->name=threeacir->get_var(k);
             ////cout<<$7->start<<endl;
            if(!threeacir->quadruple[$7->start]->is_block || $7->start!=$7->index){
               $7->name = threeacir->get_var(threeacir->make_block($7->start));}

            $$->index = threeacir->insert_for($2->start, $4->index,$4->index,$4->name, $7->name);
            $$->start = $$->index;

            for(int i=0;i<threeacir->quadruple.size();i++){
                ////cout<<threeacir->quadruple[i]->gen_threeac();
                ////cout<<endl;
            }

            $$->val=addnode("for_stmt");$1=addnode(string("FOR") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("IN") );addedge($$->val, $3);addedge($$->val, $4->val);$5=addnode(string("COLON") );addedge($$->val, $5);addedge($$->val, $7->val);

        };


funcdef: DEF IDENTIFIER { ////cout<<"funcdef1 started"<<$2<<endl;
              func* newfunc = new func($2,yylineno);
              newfunc->offset = GlobalSymbolTable->curr_sym_tbl->offset;
              GlobalSymbolTable->curr_sym_tbl->offset+=4;
              GlobalSymbolTable->insert(newfunc);
              GlobalSymbolTable->make_table(GlobalSymbolTable->curr_scope +"T_"+ $2);
              GlobalSymbolTable->curr_sym_tbl->functbl=true;

              threeacir->make_block(threeacir->quadruple.size(),$2);
              sprintf($1,"%d",threeacir->insert_two_word_instr("function begin", $2));}
       parameters {
             int k= GlobalSymbolTable->curr_sym_tbl->parent->func_vec.size();
             GlobalSymbolTable->curr_sym_tbl->parent->func_vec[k-1]->parameters_vec=$4->parameters_vec;
             string funcname=GlobalSymbolTable->curr_sym_tbl->parent->func_vec[k-1]->name;
              vector<pair<string,int>>arglist;
              for(int i=0;i<$4->parameters_vec.size();i++){
                arglist.push_back({$4->parameters_vec[i]->name , $4->parameters_vec[i]->size});
              }
              reverse(arglist.begin(),arglist.end());
              threeacir->insert_function_call(funcname, arglist, false, "", true);
              }
        func_end{ ////cout<<"funcdef1 ended"<<endl;
            int k= GlobalSymbolTable->curr_sym_tbl->func_vec.size();
              $$=new Info();
             GlobalSymbolTable->curr_sym_tbl->func_vec[k-1]->parameters_vec=$4->parameters_vec;
             string funcname=GlobalSymbolTable->curr_sym_tbl->func_vec[k-1]->name;
              //threeacir->insert_two_word_instr("\tpop","basePointer");
              threeacir->insert_two_word_instr("\treturn","");
              $$->index=threeacir->insert_two_word_instr("function end", funcname);

              $$->start=stoi($1);
              //cout<<" done harshh "<<endl;
                 //cout<<$2<<endl;
              $$->val=addnode("funcdef");$1=addnode(string("DEF") );addedge($$->val, $1);$2=addnode(string("IDENTIFIER"));addedge($$->val, $2);addedge($$->val, $4->val);addedge($$->val, $6->val);
                  //cout<<" done harshhinii "<<endl;
        }

       | DEF DUNDER {
           //cout<<"funcdef2"<<endl;
              func* newfunc = new func($2,yylineno);
              newfunc->offset = GlobalSymbolTable->curr_sym_tbl->offset;
              GlobalSymbolTable->curr_sym_tbl->offset+=4;
              GlobalSymbolTable->insert(newfunc);


              int k= GlobalSymbolTable->curr_sym_tbl->parent->class_vec.size();
              string s=GlobalSymbolTable->curr_sym_tbl->parent->class_vec[k-1]->name;

              GlobalSymbolTable->make_table(GlobalSymbolTable->curr_scope +"T_"+ $2);
              GlobalSymbolTable->curr_sym_tbl->functbl=true;


              threeacir->make_block(threeacir->quadruple.size(),s+".constructor");
              sprintf($1,"%d",threeacir->insert_two_word_instr("function begin", $2));}
       parameters {
           //cout<<"funcdef2 parameters entered"<<endl;
            int k= GlobalSymbolTable->curr_sym_tbl->parent->func_vec.size();

            //cout<<GlobalSymbolTable->curr_sym_tbl->parent->func_vec[k-1]->name<<" "<<$4->parameters_vec.size()<<endl;

             GlobalSymbolTable->curr_sym_tbl->parent->func_vec[k-1]->parameters_vec=$4->parameters_vec;
             string funcname=GlobalSymbolTable->curr_sym_tbl->parent->func_vec[k-1]->name;
              vector<pair<string,int>>arglist;
              for(int i=0;i<$4->parameters_vec.size();i++){
                arglist.push_back({$4->parameters_vec[i]->name , $4->parameters_vec[i]->size});
              }
              reverse(arglist.begin(),arglist.end());
              threeacir->insert_function_call(funcname, arglist, false, "", true);}
        COLON suite {
          //cout<<"funcdef2 suite entered"<<endl;
            GlobalSymbolTable->outofcurrst();
               $$=new Info();
            int k= GlobalSymbolTable->curr_sym_tbl->func_vec.size();

             GlobalSymbolTable->curr_sym_tbl->func_vec[k-1]->parameters_vec=$4->parameters_vec;
            string funcname=GlobalSymbolTable->curr_sym_tbl->func_vec[k-1]->name;
            //threeacir->insert_two_word_instr("\tpop","basePointer");
            threeacir->insert_two_word_instr("\treturn","");
            $$->index=threeacir->insert_two_word_instr("function end", funcname);
            $$->start=stoi($1);


            $$->val=addnode("funcdef");$1=addnode(string("DEF") );addedge($$->val, $1);$2=addnode(string("IDENTIFIER"));addedge($$->val, $2);addedge($$->val, $4->val);$6=addnode(string("COLON") );addedge($$->val, $6);addedge($$->val, $7->val);}
       ;

func_end: ARROW test COLON { ////cout<<"func_end1 started"<<endl;
      
             int k= GlobalSymbolTable->curr_sym_tbl->parent->func_vec.size();
             GlobalSymbolTable->curr_sym_tbl->parent->func_vec[k-1]->ret_type=$2->type;
             }
        suite{ ////cout<<"func_end1 ended"<<endl;
             GlobalSymbolTable->outofcurrst();
              $$=new Info();
             int k= GlobalSymbolTable->curr_sym_tbl->func_vec.size();
             string funcname=GlobalSymbolTable->curr_sym_tbl->func_vec[k-1]->name;
             $$->val=addnode("func_end");$1=addnode(string("ARROW") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("COLON") );addedge($$->val, $3);addedge($$->val, $5->val);

        }
        | COLON{////cout<<"func_end1 started"<<endl;
           
             int k= GlobalSymbolTable->curr_sym_tbl->parent->func_vec.size();

             GlobalSymbolTable->curr_sym_tbl->parent->func_vec[k-1]->ret_type="none";
              }
        suite{
              ////cout<<" the game "<<endl;
             GlobalSymbolTable->outofcurrst();
              $$=new Info();
             int k= GlobalSymbolTable->curr_sym_tbl->func_vec.size();
             string funcname=GlobalSymbolTable->curr_sym_tbl->func_vec[k-1]->name;

             $$->val=addnode("func_end");$1=addnode(string("COLON") );addedge($$->val, $1);addedge($$->val, $3->val);}
        ;

parameters:  CIROPEN typedargslist  CIRCLOSE {
       ////cout<<" srhhhh1 "<<endl;
               $$ = new Info();
               for(int i=0;i<$2->parameters_vec.size();i++){
                   $$->parameters_vec.push_back($2->parameters_vec[i]);
               }
               $$->val=addnode("parameters");$1=addnode(string("CIROPEN") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("CIRCLOSE"));addedge($$->val, $3);}
          |  CIROPEN CIRCLOSE {
               $$ = new Info();
               $$->parameters_vec={};
               $$->val=addnode("parameters");$1=addnode(string("CIROPEN") );addedge($$->val, $1);$2=addnode(string("CIRCLOSE"));addedge($$->val, $2);}
          ;

typedargslist:tfpdef EQUAL test comma_tfpdef_sure COMMA {
                $$ = new Info();
                if(GlobalSymbolTable->type_check($3->type,$1->parameters_vec[0]->type)) yyerror1("9 there is a type mismatch",yylineno);
                if($1->parameters_vec.size()!=0) $$->parameters_vec.push_back($1->parameters_vec[0]) ;
                for(int i=0;i<$4->parameters_vec.size();i++) $$->parameters_vec.push_back($4->parameters_vec[i]);
                $$->val=addnode("typedargslist");addedge($$->val, $1->val);$2=addnode(string("EQUAL"));addedge($$->val, $2);addedge($$->val, $3->val);addedge($$->val, $4->val);$5=addnode(string("COMMA") );addedge($$->val, $5);}
           | tfpdef EQUAL test COMMA {
                $$ = new Info();
                if(GlobalSymbolTable->type_check($3->type,$1->parameters_vec[0]->type)) yyerror1("10 there is a type mismatch",yylineno);
                if($1->parameters_vec.size()!=0) $$->parameters_vec.push_back($1->parameters_vec[0]);
                $$->val=addnode("typedargslist");addedge($$->val, $1->val);$2=addnode(string("EQUAL"));addedge($$->val, $2);addedge($$->val, $3->val);$4=addnode(string("COMMA") );addedge($$->val, $4);}
           | tfpdef comma_tfpdef_sure COMMA {
                $$ = new Info();
                if($1->parameters_vec.size()!=0) $$->parameters_vec.push_back($1->parameters_vec[0]);
                for(int i=0;i<$2->parameters_vec.size();i++) $$->parameters_vec.push_back($2->parameters_vec[i]);
                $$->val=addnode("typedargslist");addedge($$->val, $1->val);addedge($$->val, $2->val);$3=addnode(string("COMMA") );addedge($$->val, $3);}
           | tfpdef COMMA {
                $$ = new Info();
                if($1->parameters_vec.size()!=0) $$->parameters_vec.push_back($1->parameters_vec[0]);
                $$->val=addnode("typedargslist");addedge($$->val, $1->val);$2=addnode(string("COMMA"));addedge($$->val, $2);}
           | tfpdef EQUAL test comma_tfpdef_sure {
                $$ = new Info();
                if(GlobalSymbolTable->type_check($3->type,$1->parameters_vec[0]->type)) yyerror1("11 there is a type mismatch",yylineno);
                if($1->parameters_vec.size()!=0) $$->parameters_vec.push_back($1->parameters_vec[0]);
                for(int i=0;i<$4->parameters_vec.size();i++) $$->parameters_vec.push_back($4->parameters_vec[i]);
                $$->val=addnode("typedargslist");addedge($$->val, $1->val);$2=addnode(string("EQUAL"));addedge($$->val, $2);addedge($$->val, $3->val);addedge($$->val, $4->val);}
           | tfpdef EQUAL test {
                $$ = new Info();
                if(GlobalSymbolTable->type_check($3->type,$1->parameters_vec[0]->type)) yyerror1("12 there is a type mismatch",yylineno);
                if($1->parameters_vec.size()!=0) $$->parameters_vec.push_back($1->parameters_vec[0]);
                $$->val=addnode("typedargslist");addedge($$->val, $1->val);$2=addnode(string("EQUAL"));addedge($$->val, $2);addedge($$->val, $3->val);}
           | tfpdef comma_tfpdef_sure {
            ////cout<<" thyyy "<<endl;
                $$ = new Info();
                if($1->parameters_vec.size()!=0) $$->parameters_vec.push_back($1->parameters_vec[0]);
                for(int i=0;i<$2->parameters_vec.size();i++) $$->parameters_vec.push_back($2->parameters_vec[i]);
                $$->val=addnode("typedargslist");addedge($$->val, $1->val);addedge($$->val, $2->val); }
           | tfpdef {
                $$ = new Info();
                if($1->parameters_vec.size()!=0) $$->parameters_vec.push_back($1->parameters_vec[0]) ;
                else $$->parameters_vec={};
                $$->val=$1->val;}
           ;

comma_tfpdef:COMMA tfpdef EQUAL test {
             $$= new Info();
             if(GlobalSymbolTable->type_check($4->type,$2->parameters_vec[0]->type)) yyerror1("13 There is a type mismatch",yylineno);
             if($2->parameters_vec.size()!=0) $$->parameters_vec.push_back($2->parameters_vec[0]);
             $$->val=addnode("comma_tfpdef");$1=addnode(string("COMMA") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("EQUAL") );addedge($$->val, $3);addedge($$->val, $4->val);}
    | COMMA tfpdef { ////cout<<" myyyyy "<<endl;
            $$ = new Info();
            ////cout<<$2->parameters_vec.size()<<endl;
            if($2->parameters_vec.size()!=0) $$->parameters_vec.push_back($2->parameters_vec[0]);
             ////cout<<" uuuuuu "<<endl;
            $$->val=addnode("comma_tfpdef");$1=addnode(string("COMMA") );addedge($$->val, $1);addedge($$->val, $2->val);}
    ;

comma_tfpdef_sure: comma_tfpdef {
     ////cout<<" lyyyyy "<<endl;
             $$ = new Info();
             if($1->parameters_vec.size()!=0) $$->parameters_vec.push_back($1->parameters_vec[0]);
             $$->val=$1->val;}
         | comma_tfpdef_sure comma_tfpdef {
             ////cout<<" byyyyy "<<endl;
             $$ = new Info();
             for(int i=0;i<$1->parameters_vec.size();i++) $$->parameters_vec.push_back($1->parameters_vec[i]);
             if($2->parameters_vec.size()!=0) $$->parameters_vec.push_back($2->parameters_vec[0]);
              ////cout<<" dyyyyyy "<<endl;
             $$->val=addnode("comma_tfpdef_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
         ;
tfpdef: IDENTIFIER {
     ////cout<<" flyyyy "<<endl;
            $$ = new Info();
            nor_sym* newsym= new nor_sym($1,yylineno);
            newsym->offset = GlobalSymbolTable->curr_sym_tbl->offset;
            GlobalSymbolTable->insert(newsym);
            GlobalSymbolTable->curr_sym_tbl->offset+=4;
            $$->parameters_vec.push_back(newsym);
             ////cout<<" fluuuu "<<endl;
            $$->val=addnode("tfpdef");$1=addnode(string("IDENTIFIER") );addedge($$->val, $1);}
      | IDENTIFIER  COLON test {

            nor_sym* newsym= new nor_sym($1,yylineno);
            newsym->offset = GlobalSymbolTable->curr_sym_tbl->offset;
            $$ = new Info();
            if($3->c==-100)
            $$->type="list"+$3->type;
            else $$->type=$3->type;
            newsym->type=$$->type;
            if($3->type == "string") newsym->size=$3->name.size();
            else newsym->size=type_size_map[$3->type];
            $$->parameters_vec.push_back(newsym);
            GlobalSymbolTable->insert(newsym);
            GlobalSymbolTable->curr_sym_tbl->offset+=newsym->size;


            nor_sym* g=GlobalSymbolTable->search_nor_sym( $1, GlobalSymbolTable->curr_scope);
            $$->val=addnode("tfpdef");$1=addnode(string("IDENTIFIER") );addedge($$->val, $1);$2=addnode(string("COLON"));addedge($$->val, $2);addedge($$->val, $3->val);}
      ;

classdef: CLASS IDENTIFIER  CIROPEN arglist  CIRCLOSE  COLON {
               //cout<<"classdef1 entered"<<endl;
               //cout<<$2<<endl;
              Class *newclass = new Class($2,yylineno);
              newclass->offset = GlobalSymbolTable->curr_sym_tbl->offset;
              GlobalSymbolTable->insert(newclass);
              GlobalSymbolTable->make_table($2);
              GlobalSymbolTable->curr_sym_tbl->classtbl=true;
              threeacir->make_block(threeacir->quadruple.size(),$2);}
          suite {
            //cout<<" yayyyyyy "<<endl;
              GlobalSymbolTable->outofcurrst();
               $$=new Info();
              $$->val=addnode("classdef");$1=addnode(string("CLASS") );addedge($$->val, $1);$2=addnode(string("IDENTIFIER"));addedge($$->val, $2);$3=addnode(string("CIROPEN") );addedge($$->val, $3);addedge($$->val, $4->val);$5=addnode(string("CIRCLOSE") );addedge($$->val, $5);$6=addnode(string("COLON") );addedge($$->val, $6);addedge($$->val, $8->val);}
          | CLASS IDENTIFIER  COLON {
            //cout<<" srhhhh "<<endl;
               //cout<<$2<<endl;
              Class *newclass = new Class($2,yylineno);

              newclass->offset = GlobalSymbolTable->curr_sym_tbl->offset;
              GlobalSymbolTable->insert(newclass);
              GlobalSymbolTable->make_table($2);
              GlobalSymbolTable->curr_sym_tbl->classtbl=true;
               threeacir->make_block(threeacir->quadruple.size(),$2);}
          suite {
               //cout<<" cskkkk "<<endl;
               //cout<<$2<<endl;
                $$=new Info();
              GlobalSymbolTable->outofcurrst();
              $$->val=addnode("classdef");$1=addnode(string("CLASS") );addedge($$->val, $1);$2=addnode(string("IDENTIFIER"));addedge($$->val, $2);$3=addnode(string("COLON") );addedge($$->val, $3);addedge($$->val, $5->val);}
          | CLASS IDENTIFIER  CIROPEN  CIRCLOSE  COLON {
              Class *newclass = new Class($2,yylineno);
              newclass->offset = GlobalSymbolTable->curr_sym_tbl->offset;
              GlobalSymbolTable->insert(newclass);
              GlobalSymbolTable->make_table($2);
              GlobalSymbolTable->curr_sym_tbl->classtbl=true;
              threeacir->make_block(threeacir->quadruple.size(),$2);}
          suite { $$=new Info();
              GlobalSymbolTable->outofcurrst();
              $$->val=addnode("classdef");$1=addnode(string("CLASS") );addedge($$->val, $1);$2=addnode(string("IDENTIFIER"));addedge($$->val, $2);$3=addnode(string("CIROPEN") );addedge($$->val, $3);$4=addnode(string("CIRCLOSE") );addedge($$->val, $4);$5=addnode(string("COLON") );addedge($$->val, $5);addedge($$->val, $7->val);}
          ;

dunder_block: IF DUNDER DOUBLE_EQUAL ADUNDER COLON{
                   threeacir->insert_two_word_instr("dunder block", $2);}
               suite { //cout<<"dunder over"<<endl;
                    $$=new Info();
                    $$->index=$7->index;
                    $$->val=addnode("dunder_block");$1=addnode(string("IF") );addedge($$->val, $1);$2=addnode(string("DUNDER"));addedge($$->val, $2);$3=addnode(string("DOUBLE_EQUAL") );addedge($$->val, $3);$4=addnode(string("ADUNDER") );addedge($$->val, $4);$5=addnode(string("COLON") );addedge($$->val, $5);addedge($$->val, $7->val);}
             ;




%%


void yyerror(const char *s){
    cerr<<"syntax error in line number "<<yylineno<<endl;
    exit(1);
}

void yyerror1(string s,int num){
    cerr<<s<<" error in line number "<<num<<endl;
    exit(1);
}

int main() {
    indent_stack.push(0);
    yyparse();
    cerr << "Opening file: " << "outputs/output.dot"<< endl;
    ofstream dotfile("outputs/output.dot");
    dotfile << "digraph ASTVisual {\n ordering = out ;\n";
    for(auto e: nodes){
        string s;

         for( auto e1: e.l){
            if(e1=='\"' || e1=='\\'  ){
                s.push_back('\\');
            }
            s.push_back(e1);
        }
        dotfile<<e.num<<" [ label=\""<<s<<"\"]\n";
    }
    for(auto e: edges){
        string s;

        for( auto e1: e.l){
            if(e1=='\"' || e1=='\\'){
                s.push_back('\\');
            }
            s.push_back(e1);
        }
        dotfile<<e.a<< " -> "<<e.b << "[ label=\""<<s<<"\"]\n";
    }
    dotfile << "  }\n";
    return 0;
}
