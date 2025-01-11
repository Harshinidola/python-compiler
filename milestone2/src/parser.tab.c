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
    void yyerror1(string s,int line);
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


    //all information regarding symbol table
    map<string,int> type_size_map = {
      {"byte",1},
      {"short",2},
      {"char",2},
      {"int",4},
      {"float",4},
      {"double",8},
      {"long",8}
    };


    class nor_sym{
      public:
      string name;
      string type;
      string value;
      bool isarray;
      int listsize;
      int lineno;
      string classs_name;
      int size;
      int offset;
      bool inherited;
      string objName;


      nor_sym(string Name, int Lineno){
        name = Name;
        isarray = false;
        lineno = Lineno;
        // if(type_size_map.find(Type)!=type_size_map.end()){
        //     size = type_size_map[Type];
        // }
      }


      nor_sym(string Name, string Type, int Size ,int Lineno, bool Isarray, string Value){
        name = Name;
        type = Type;
        isarray = true;
        listsize = Size;
        lineno = Lineno;
        value = Value;
        if(type_size_map.find(Type)!=type_size_map.end()){
            size = type_size_map[Type] * Size;
        }
      }
    };

    class func{
      public:
      string name;
      string ret_type;
      vector<nor_sym*> parameters_vec ;
      int lineno;
      int size;
      int offset;

      func(string myname, int mylineno){
          name = myname;
          lineno = mylineno;
          size = 4;
      }
    };

    class Class{
      public:
      string name;
      int lineno;
      bool inherited;
      int size;
      int offset;
      Class(string myname, int mylineno){
          name = myname;
          lineno = mylineno;
      }
    };


     class loc_sym_tbl{
      public:
      loc_sym_tbl* parent;
      string scope;
      vector<nor_sym*> nor_sym_vec;
      vector<Class*> class_vec;
      vector<func*> func_vec;
      vector<func*>pre_func;
      int lcount;
      int offset = 0;
      bool functbl=false, classtbl=false;

      loc_sym_tbl(loc_sym_tbl* par_ent, string sco_pe , int n){
        parent = par_ent;
        scope = sco_pe;
        lcount=n;
        nor_sym_vec = {};
        class_vec = {};
        func_vec = {};
        pre_func={};
        func* newfunc1= new func("print",-1);
        pre_func.push_back(newfunc1);

        func* newfunc2= new func("input",-1);
        newfunc2->ret_type="int";
        pre_func.push_back(newfunc2);


        func* newfunc3= new func("len",-1);
        newfunc3->ret_type="int";
        pre_func.push_back(newfunc3);

      }

      void insert_nor_sym(nor_sym* symbol){
        nor_sym_vec.push_back(symbol);
      }
      void insert_func(func* symbol){
        func_vec.push_back(symbol);
      }
      void insert_class(Class* symbol){
        class_vec.push_back(symbol);
      }

      void printTable(){
        cout<<"Scope: "<<scope<<endl;
        cout<<"Variables coming\n\n";
        for(auto i:nor_sym_vec){
            cout<<"Name: "<<i->name<<endl;
            cout<<"Array? "<<i->isarray<<endl;
            cout<<"type "<<i->type<<endl;
            cout<<"linenumber "<<i->lineno<<endl;
            cout<<"size "<<i->size<<endl;
        }
        cout<<"Methods coming\n\n";
        for(auto i:func_vec){
            cout<<"Name: "<<i->name<<endl;
            cout<<"Parameters:";
            for(auto j:i->parameters_vec){
                cout<<"Name: "<<j->name<<" Type: "<<j->type<<endl;
            }
            cout<<"line number"<<i->lineno<<endl;
             cout<<"return type"<<i->ret_type<<endl;
            cout<<"\n\n";
        }
        cout<<"Classes coming\n\n";
        for(auto i:class_vec){
            cout<<"Name: "<<i->name<<" Line: "<<i->lineno<<endl;
        }
        cout<<"\n\n---Table end---\n\n";
      }



      void print_csv(){

        // Open the file in write mode
        ofstream file("outputs/Table of scope"+scope+".csv");

        // Check if the file is opened successfully
        if (!file.is_open()) {
        cerr << "Failed to open the file." << endl;
        return;
        }



        if(nor_sym_vec.size()>0){
          vector<vector<string>> data = {{"Lexeme","Token", "Type", "Line number"}};

          for(auto i:nor_sym_vec){
              vector<string> s;
              s.push_back(i->name);
              s.push_back("Identifier");
              s.push_back(i->type);
              s.push_back(to_string(i->lineno));
              data.push_back(s);
          }

          for (const auto& row : data) {
            for (size_t i = 0; i < row.size(); ++i) {
              file << row[i];
              if (i != row.size() - 1) {
                file << ",";
              }
            }
          file << endl;
          }
        }

        if(func_vec.size()>0){
          vector<vector<string>> data1 = {{"Function Name","Parameters", "Return Type", "Line number"}};
          for(auto i:func_vec){
            vector<string> s;
            s.push_back(i->name);
            string k="";
            for(auto j:i->parameters_vec){
              k+="Name: "+j->name+" Type: "+j->type+" ";
            }
            s.push_back(k);
            s.push_back(i->ret_type);
            s.push_back(to_string(i->lineno));
            data1.push_back(s);
          }

          for (const auto& row : data1) {
            for (size_t i = 0; i < row.size(); ++i) {
              file << row[i];
              if (i != row.size() - 1) {
                file << ",";
              }
            }
          file << endl;
          }
        }


        if(class_vec.size()>0){
          vector<vector<string>>data2={{"Class Name","Line Number"}};
          for(auto i:class_vec){
            vector<string>s;
            s.push_back(i->name);
            s.push_back(to_string(i->lineno));
            data2.push_back(s);
          }

          
          for (const auto& row : data2) {
            for (size_t i = 0; i < row.size(); ++i) {
              file << row[i];
              if (i != row.size() - 1) {
                file << ",";
              }
            }
          file << endl;
          }

        }  

          file.close();
          //cout << "CSV file created successfully for scope "<<scope<< endl;

        }

    };



    class glo_sym_tbl{
      public:
      loc_sym_tbl* curr_sym_tbl;
      string curr_scope;
      int count=0;
      map<int,loc_sym_tbl*> count_table_map; // scope-number maped
      map<string,loc_sym_tbl*> scope_table_map; // scope


      glo_sym_tbl(){
        curr_scope="ST_";
        curr_scope+=to_string(count);
        loc_sym_tbl* initial = new loc_sym_tbl(NULL, curr_scope, count);
        count_table_map[count]=initial;
        scope_table_map[curr_scope]= initial;
        count++;
        curr_sym_tbl = initial;
      }

        // searching in symbol table
        nor_sym* search_nor_sym(string s, string scope){

          loc_sym_tbl* curr = scope_table_map[scope];

          while(curr!=NULL){
            for(int i=0; i<curr->nor_sym_vec.size();i++){
                if(curr->nor_sym_vec[i]->name==s)return curr->nor_sym_vec[i];
            }

            curr=curr->parent;
          }
          return NULL;
        }

        func* search_func(string s, string scope){

          loc_sym_tbl* curr = scope_table_map[scope];

          while(curr!=NULL){
            for(int i=0; i<curr->func_vec.size();i++){
                if(curr->func_vec[i]->name==s)return curr->func_vec[i];
            }
            curr=curr->parent;
          }
          return NULL;
        }

         func* search_pre_func(string s, string scope){

          loc_sym_tbl* curr = scope_table_map[scope];

            for(int i=0; i<curr->pre_func.size();i++){
                if(curr->pre_func[i]->name==s)return curr->pre_func[i];
            }
          return NULL;
        }

        Class* search_class(string s, string scope){

          loc_sym_tbl* curr = scope_table_map[scope];

          while(curr!=NULL){
            for(int i=0; i<curr->class_vec.size();i++){
                if(curr->class_vec[i]->name==s)return curr->class_vec[i];
            }
            curr=curr->parent;
          }
          return NULL;
        }


        //making new symbol table

        loc_sym_tbl* make_table(){
        string curr_scope="ST_";
        curr_scope+=to_string(count);
        loc_sym_tbl* new_table = new loc_sym_tbl(curr_sym_tbl, curr_scope, count);
        count_table_map[count]=new_table;
        scope_table_map[curr_scope]=new_table;
        curr_sym_tbl= new_table;
        count++;
        return new_table;

      }

      loc_sym_tbl* make_table(string s){
        curr_scope=s;
        loc_sym_tbl* new_table = new loc_sym_tbl(curr_sym_tbl, curr_scope, count);
        count_table_map[count]=new_table;
        scope_table_map[curr_scope]=new_table;
        curr_sym_tbl= new_table;
        count++;
        return new_table;

      }

      void outofcurrst(){
        curr_sym_tbl=curr_sym_tbl->parent;
        curr_scope= curr_sym_tbl->scope;
      }


      bool checking(string symbol){
        if(search_nor_sym(symbol,curr_scope)==NULL){
            if(search_func(symbol,curr_scope)==NULL){
                if(search_class(symbol,curr_scope)==NULL){
                   if(search_pre_func(symbol,curr_scope)==NULL)
                    return true;
                }
            }
        }
        //throwError("Error: Redeclaration of symbol :"+symbol,yylineno);
        return false;

      }

      void insert(nor_sym* symbol){
        if(checking(symbol->name)){
           curr_sym_tbl->insert_nor_sym(symbol);
        }
      }

      void insert(func* symbol){
        if(checking(symbol->name)){
           curr_sym_tbl->insert_func(symbol);
        }
      }

      void insert(Class* symbol){
        if(checking(symbol->name)){
            curr_sym_tbl->insert_class(symbol);
        }
      }

      void printAll(){
        for(int i=0;i<count;i++){
            count_table_map[i]->print_csv();
        }
      }

    };

    class Info {
      public:
      char* val;
      string name;
      int c;
      vector<nor_sym*>parameters_vec;
      string type;
      bool isfunc;
      string arrtype;

      Info() {
        c=0;
        val=NULL;
        name="";
        type="";
        isfunc=false;
      }
    };

class Instruction{
    public:
        string net_threeac="";
        bool is_block=false;
        bool incomplete = false;

        virtual string gen_threeac(){
            return "";
        }
};

class assignment: public Instruction{
    public:
        string arg1;
        string arg2="";
        string op="";

        string gen_threeac(){

            string s="\t";

            if(net_threeac!="") s += net_threeac + " := ";

            if(op!="") {
                if(arg2!="") return ( s + arg1 + " " + op + " " + arg2);
                else return (s + arg1 + op);
            }
            else{
                return s + arg1;
            }
        }
};

class unconditional_jump: public Instruction{
    public:
        string arg1="goto";
        string arg2="";
        int index;

        string gen_threeac(){
            if(arg2=="") return ("\t"+ arg1 + " " + to_string(index));
            else return ("\t"+ arg1 + " " +arg2);
        }

};

class conditional_jump: public Instruction{
    public:
        string arg1="if";
        string arg2;
        string arg3="goto";
        string arg4="";
        int index;

        string gen_threeac(){
            if(arg4=="") return ("\t"+ arg1 + " " + arg2 + " " + arg3 + " " +to_string(index));
            else return ("\t"+ arg1 + " " + arg2 + " " + arg3 + " " +arg4);
        }

};

class block: public Instruction{
    public:

    vector<Instruction*> codes;

    string gen_threeac(){
        string s =net_threeac + ":";
        for(auto curr_code : codes){
            s +="\n"+ curr_code->gen_threeac();
        }
        return s;
    }
};

class two_word_instr: public Instruction{
    public:
        string arg1;
        string arg2;
    string gen_threeac(){
        return arg1+" "+arg2;
    }
};

class function_call: public Instruction{
    public:
        string name;
        vector<string> params;
        bool is_call=false;
        bool is_constructor = false;
        string constructor_name = "";

        string mysize="";

        string gen_threeac(){

            string s="";

            if(!is_call) {
                return s;
            }

            for(auto x:params){
                s+= "\tparam "+x + "\n";
            }
            // s=s.substr(0,s.length()-1);
            s+= "\tpush basePointer\n\tbasePointer := stackPointer\n";
            s+= "\tstackPointer := stackPointer -int "+mysize;

            return s;
        }
};

class array_insert: public Instruction{
    public:
        vector<string> elements;
        string array;
        int typesize;

        string gen_threeac(){
            int off=0;
            string s = "";
            for(auto elem: elements){
                if(elem=="")continue;
                s+= "\tpushArr "+array+" "+elem+" "+ to_string(off)+"\n";
                off+=typesize;
            }
            return s;

        }
};

class symbol_table_offset : public Instruction
{
    public:
        string classname;
        string offset;
        int offValue;

        string gen_threeac()
        {
            string s = "\t" + net_threeac + " := getFromSymTable( " + classname + " , " + offset + ")" ;
            return s;
        }
};

class THREEACX86{
  public:
  vector<Instruction*> quadruple;
  map<string,block*> blocks;
  int local_var_count=0;
  int local_label_count=0;


  string get_var(int index){
      return quadruple[index]->net_threeac;
  }
  string get_local_var(){
      return "t"+to_string(local_var_count++);
  }
  string get_local_label(){
      return "L"+to_string(local_label_count++);
  }
  string next_label(){
      return "L"+to_string(local_label_count+1);
  }
  int insert(Instruction* curr_instruction){
      quadruple.push_back(curr_instruction);
      return quadruple.size()-1;
  }


  int insert(string arg1, string var=""){
      assignment* curr_instruction = new assignment();
      curr_instruction->arg1=arg1;
      if(var=="") curr_instruction->net_threeac=get_local_var();
      else curr_instruction->net_threeac=var;
      quadruple.push_back(curr_instruction);
      return quadruple.size()-1;
  }

  Instruction* create(string givearg1, string givearg2, string op,string var=""){
      assignment* curr_instruction = new assignment();
      curr_instruction->arg1=givearg1;
      curr_instruction->arg2=givearg2;
      curr_instruction->op=op;
      if(var=="") curr_instruction->net_threeac=get_local_var();
      else curr_instruction->net_threeac=var;
      return curr_instruction;
  }


  int make_block(int index, string name="", int endindex=-1){
      if(endindex==-1)endindex=quadruple.size();
      block* curr_instruction = new block();
      if(name=="") curr_instruction->net_threeac = get_local_label();
      else curr_instruction->net_threeac=name;
      for(int i=index;i<endindex;i++){
          curr_instruction->codes.push_back(quadruple[i]);
      }
      quadruple.erase(quadruple.begin()+index,quadruple.begin()+endindex);
      blocks.insert({curr_instruction->net_threeac,curr_instruction});
      Instruction* curr_instruction2 = curr_instruction;
      curr_instruction2->is_block=true;
      quadruple.push_back(curr_instruction2);
      return quadruple.size()-1;
  }

  int make_block(){
      block* curr_instruction = new block();
      curr_instruction->net_threeac = get_local_label();
      blocks.insert({curr_instruction->net_threeac,curr_instruction});
      Instruction* curr_instruction2 = curr_instruction;
      curr_instruction2->is_block=true;
      quadruple.push_back(curr_instruction2);
      return quadruple.size()-1;
  }

  int insert_assignment(string givearg1, string givearg2, string op,string var=""){
      return insert(create(givearg1,givearg2,op,var));
  }

  int insert_jump(string givearg2, int index=-1){
      unconditional_jump* curr_instruction = new unconditional_jump();
      curr_instruction->arg2=givearg2;
      if(index==-1) quadruple.push_back(curr_instruction);
      else{
          quadruple.insert(quadruple.begin()+index+1,curr_instruction);
      }
      if(blocks.find(givearg2)==blocks.end()){
          block* curr_block = new block();
          curr_block->net_threeac = givearg2;
          curr_block->is_block=true;
          blocks.insert({givearg2,curr_block});
          Instruction* block_label = curr_block;
          quadruple.push_back(block_label);
      }
      return quadruple.size()-1;
  }

  void insert_next_jump(string arg1, string jump_loaction_number){
      unconditional_jump* curr_instruction = new unconditional_jump();
      curr_instruction->arg2=jump_loaction_number;
      Instruction* given_jump= curr_instruction;
      blocks[arg1]->codes.push_back(given_jump);
      if(blocks.find(jump_loaction_number)==blocks.end()){
          block* curr_block = new block();
          curr_block->net_threeac = jump_loaction_number;
          curr_block->is_block=true;
          blocks.insert({jump_loaction_number,curr_block});
          Instruction* block_label = curr_block;
          quadruple.push_back(block_label);
      }
  }

        // if statement
  int insert_if(int index ,string arg1,string arg2, string arg3){
      conditional_jump* curr_instruction = new conditional_jump();
      string next = get_local_label();
      curr_instruction->arg2= arg1;
      curr_instruction->arg4= arg2;
      quadruple.insert(quadruple.begin()+index+1,curr_instruction);
      insert_next_jump(arg2, next);
      if(arg3!=""){
          insert_jump(arg3,index+1);
          insert_next_jump(arg3, next);
      }
      else insert_jump(next, index+1);
      return index;
  }

  int insert_while(int startindex, int endindex, string condition, string arg2){
      conditional_jump* curr_instruction = new conditional_jump();
      string next = get_local_label();
      curr_instruction->arg2= condition;
      curr_instruction->arg4= arg2;

      quadruple.insert(quadruple.begin()+endindex+1,curr_instruction);
      insert_jump(next, endindex+1);

      int x = make_block(startindex);
      insert_next_jump(arg2,quadruple[x]->net_threeac);
      update_incomplete_jump(quadruple[x]->net_threeac,quadruple[x]->net_threeac,next);
      return quadruple.size()-1;
  }

  int insert_for(int mystart, int startindex, int endindex, string changeExp, string arg2 ){
      conditional_jump* curr_instruction = new conditional_jump();
      string next = get_local_label();
      if(startindex>=0) curr_instruction->arg2= quadruple[endindex]->net_threeac;
      else curr_instruction->arg2 = "true";
      curr_instruction->arg4= arg2;
      quadruple.insert(quadruple.begin()+endindex+1,curr_instruction);
      insert_jump(next, endindex+1);
      int x;

      if(startindex>=0) x = make_block(startindex);
      else x = make_block(endindex+1);
      if(changeExp!=""){
          insert_next_jump(arg2,changeExp);
          insert_next_jump(changeExp,quadruple[x]->net_threeac);
      }
      else {
          insert_next_jump(arg2,quadruple[x]->net_threeac);
      }
      if(mystart>=0) x = make_block(mystart);

      update_incomplete_jump(quadruple[x]->net_threeac,changeExp,next);
      return quadruple.size()-1;
  }


  int insert_two_word_instr(string instr, string arg2){
      two_word_instr* curr_instruction = new two_word_instr();
      curr_instruction->arg1 = instr;
      curr_instruction->arg2 = arg2;
      return insert(curr_instruction);
  }


  int insert_function_call(string funcName, vector<pair<string,int>> argList, bool is_constructor=false, string mysize="", bool isVoid=true){
      function_call* myCall = new function_call();
      myCall->name = funcName;
      for(auto x: argList){
          myCall->params.push_back(x.first);
      }
      myCall->is_constructor = is_constructor;
      myCall->mysize = mysize;
      myCall->is_call=true;
      Instruction* curr_instruction = myCall;
      quadruple.push_back(curr_instruction);
      if(argList.size()) insert_two_word_instr("\tcall "+funcName,to_string(argList.size()));
      else insert_two_word_instr("\tcall "+funcName,"");
      if(!isVoid) insert_assignment("popReturnValue","","");
      int t=0;
      for(auto x : argList){
          t+=x.second;
      }
      insert_assignment("stackPointer",to_string(t),"+int","stackPointer");
      return quadruple.size()-1;
  }

  int insert_get_from_symtable(string classs, string name, string var, int offset)
  {
      symbol_table_offset *instr = new symbol_table_offset();
      if (var == "")
          instr->net_threeac = get_local_var();
      else
          instr->net_threeac = var;
      instr->classname = classs;
      instr->offset = name;
      instr->offValue = offset;
      return insert(instr);
  }

  int insert_incomplete_jump(string arg1){
      unconditional_jump* given_jump = new unconditional_jump();
      given_jump->net_threeac=arg1;
      given_jump->incomplete=true;
      quadruple.push_back(given_jump);
      return quadruple.size()-1;
  }

  void update_incomplete_jump(string currBlock,string beforeBlock,string afterBlock){
      int i=0;
      for(auto x : blocks[currBlock]->codes){
          if(x->is_block){
              update_incomplete_jump(x->net_threeac,beforeBlock,afterBlock);
          }
          else if(x->incomplete){
              unconditional_jump* given_jump = new unconditional_jump();
              string arg2;
              if(x->net_threeac=="continue") arg2=beforeBlock;
              else arg2=afterBlock;
              given_jump->arg2=arg2;
              blocks[currBlock]->codes[i]=given_jump;
          }
          i++;
      }
  }

  int insert_array(string arr, vector<string>elementss, int typeSize){
      array_insert *myins = new array_insert();
      myins->array = arr;
      myins->elements = elementss;
      myins->typesize = typeSize;
      return insert(myins);
  }
  void print(){
      for(int i=0;i<quadruple.size();i++){
          cout<<quadruple[i]->gen_threeac();
          cout<<endl;
      }
  }
};


glo_sym_tbl* GlobalSymbolTable = new glo_sym_tbl();
THREEACX86* threeacir = new THREEACX86();



#line 946 "parser.tab.c"

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
  YYSYMBOL_RETURN = 15,                    /* RETURN  */
  YYSYMBOL_IN = 16,                        /* IN  */
  YYSYMBOL_FINALLY = 17,                   /* FINALLY  */
  YYSYMBOL_GLOBAL = 18,                    /* GLOBAL  */
  YYSYMBOL_EXCEPT = 19,                    /* EXCEPT  */
  YYSYMBOL_AS = 20,                        /* AS  */
  YYSYMBOL_DEF = 21,                       /* DEF  */
  YYSYMBOL_CLASS = 22,                     /* CLASS  */
  YYSYMBOL_ASSERT = 23,                    /* ASSERT  */
  YYSYMBOL_FROM = 24,                      /* FROM  */
  YYSYMBOL_CONTINUE = 25,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 26,                     /* BREAK  */
  YYSYMBOL_RAISE = 27,                     /* RAISE  */
  YYSYMBOL_NONE = 28,                      /* NONE  */
  YYSYMBOL_TRUE = 29,                      /* TRUE  */
  YYSYMBOL_FALSE = 30,                     /* FALSE  */
  YYSYMBOL_AND = 31,                       /* AND  */
  YYSYMBOL_NOT = 32,                       /* NOT  */
  YYSYMBOL_OR = 33,                        /* OR  */
  YYSYMBOL_DEL = 34,                       /* DEL  */
  YYSYMBOL_INT = 35,                       /* INT  */
  YYSYMBOL_LISTINT = 36,                   /* LISTINT  */
  YYSYMBOL_LISTFLOAT = 37,                 /* LISTFLOAT  */
  YYSYMBOL_LISTSTRING = 38,                /* LISTSTRING  */
  YYSYMBOL_LISTBOOL = 39,                  /* LISTBOOL  */
  YYSYMBOL_LIST = 40,                      /* LIST  */
  YYSYMBOL_FLOAT = 41,                     /* FLOAT  */
  YYSYMBOL_STR = 42,                       /* STR  */
  YYSYMBOL_BOOL = 43,                      /* BOOL  */
  YYSYMBOL_IDENTIFIER = 44,                /* IDENTIFIER  */
  YYSYMBOL_DOUBLE_EQUAL = 45,              /* DOUBLE_EQUAL  */
  YYSYMBOL_GREATER_EQUAL = 46,             /* GREATER_EQUAL  */
  YYSYMBOL_LESS_EQUAL = 47,                /* LESS_EQUAL  */
  YYSYMBOL_NOT_EQUAL = 48,                 /* NOT_EQUAL  */
  YYSYMBOL_DOUBLE_LESS = 49,               /* DOUBLE_LESS  */
  YYSYMBOL_DOUBLE_GREATER = 50,            /* DOUBLE_GREATER  */
  YYSYMBOL_PLUS_EQUAL = 51,                /* PLUS_EQUAL  */
  YYSYMBOL_MINUS_EQUAL = 52,               /* MINUS_EQUAL  */
  YYSYMBOL_MULTI_EQUAL = 53,               /* MULTI_EQUAL  */
  YYSYMBOL_DIVI_EQUAL = 54,                /* DIVI_EQUAL  */
  YYSYMBOL_DOUBLE_DIVI_EQUAL = 55,         /* DOUBLE_DIVI_EQUAL  */
  YYSYMBOL_MODULO_EQUAL = 56,              /* MODULO_EQUAL  */
  YYSYMBOL_DOUBLE_MULTI_EQUAL = 57,        /* DOUBLE_MULTI_EQUAL  */
  YYSYMBOL_AND_EQUAL = 58,                 /* AND_EQUAL  */
  YYSYMBOL_PIPE_EQUAL = 59,                /* PIPE_EQUAL  */
  YYSYMBOL_POWER_EQUAL = 60,               /* POWER_EQUAL  */
  YYSYMBOL_DOUBLE_LESS_EQUAL = 61,         /* DOUBLE_LESS_EQUAL  */
  YYSYMBOL_DOUBLE_GREATER_EQUAL = 62,      /* DOUBLE_GREATER_EQUAL  */
  YYSYMBOL_STRING = 63,                    /* STRING  */
  YYSYMBOL_NUMBER = 64,                    /* NUMBER  */
  YYSYMBOL_FLOAT_NUMBER = 65,              /* FLOAT_NUMBER  */
  YYSYMBOL_IMAGINARY_NUMBER = 66,          /* IMAGINARY_NUMBER  */
  YYSYMBOL_DOUBLE_STAR = 67,               /* DOUBLE_STAR  */
  YYSYMBOL_THREE_DOT = 68,                 /* THREE_DOT  */
  YYSYMBOL_GREATER_LESS = 69,              /* GREATER_LESS  */
  YYSYMBOL_ARROW = 70,                     /* ARROW  */
  YYSYMBOL_DOUBLE_SLASH = 71,              /* DOUBLE_SLASH  */
  YYSYMBOL_COLON = 72,                     /* COLON  */
  YYSYMBOL_SEMICOLON = 73,                 /* SEMICOLON  */
  YYSYMBOL_PLUS = 74,                      /* PLUS  */
  YYSYMBOL_MINUS = 75,                     /* MINUS  */
  YYSYMBOL_DIVI = 76,                      /* DIVI  */
  YYSYMBOL_EQUAL = 77,                     /* EQUAL  */
  YYSYMBOL_COMMA = 78,                     /* COMMA  */
  YYSYMBOL_PIPE = 79,                      /* PIPE  */
  YYSYMBOL_ANDSYMBOL = 80,                 /* ANDSYMBOL  */
  YYSYMBOL_POWER = 81,                     /* POWER  */
  YYSYMBOL_MULTI = 82,                     /* MULTI  */
  YYSYMBOL_MOD = 83,                       /* MOD  */
  YYSYMBOL_NOSYMBOL = 84,                  /* NOSYMBOL  */
  YYSYMBOL_CIROPEN = 85,                   /* CIROPEN  */
  YYSYMBOL_CIRCLOSE = 86,                  /* CIRCLOSE  */
  YYSYMBOL_SQOPEN = 87,                    /* SQOPEN  */
  YYSYMBOL_SQCLOSE = 88,                   /* SQCLOSE  */
  YYSYMBOL_CUOPEN = 89,                    /* CUOPEN  */
  YYSYMBOL_CUCLOSE = 90,                   /* CUCLOSE  */
  YYSYMBOL_DOT = 91,                       /* DOT  */
  YYSYMBOL_LESS = 92,                      /* LESS  */
  YYSYMBOL_GREATER = 93,                   /* GREATER  */
  YYSYMBOL_ADUNDER = 94,                   /* ADUNDER  */
  YYSYMBOL_YYACCEPT = 95,                  /* $accept  */
  YYSYMBOL_starting = 96,                  /* starting  */
  YYSYMBOL_file_input = 97,                /* file_input  */
  YYSYMBOL_line_or_stmt_sure = 98,         /* line_or_stmt_sure  */
  YYSYMBOL_line_or_stmt = 99,              /* line_or_stmt  */
  YYSYMBOL_line_sure = 100,                /* line_sure  */
  YYSYMBOL_stmt = 101,                     /* stmt  */
  YYSYMBOL_simple_stmt = 102,              /* simple_stmt  */
  YYSYMBOL_smlst = 103,                    /* smlst  */
  YYSYMBOL_smlst_sure = 104,               /* smlst_sure  */
  YYSYMBOL_small_stmt = 105,               /* small_stmt  */
  YYSYMBOL_expr_stmt = 106,                /* expr_stmt  */
  YYSYMBOL_equal_testlist_star_expr = 107, /* equal_testlist_star_expr  */
  YYSYMBOL_equal_testlist_star_expr_sure = 108, /* equal_testlist_star_expr_sure  */
  YYSYMBOL_testlist_star_expr = 109,       /* testlist_star_expr  */
  YYSYMBOL_comma_test2 = 110,              /* comma_test2  */
  YYSYMBOL_comma_test2_sure = 111,         /* comma_test2_sure  */
  YYSYMBOL_test = 112,                     /* test  */
  YYSYMBOL_or_test = 113,                  /* or_test  */
  YYSYMBOL_or_and_test = 114,              /* or_and_test  */
  YYSYMBOL_or_and_test_sure = 115,         /* or_and_test_sure  */
  YYSYMBOL_and_test = 116,                 /* and_test  */
  YYSYMBOL_and_not_test = 117,             /* and_not_test  */
  YYSYMBOL_and_not_test_sure = 118,        /* and_not_test_sure  */
  YYSYMBOL_not_test = 119,                 /* not_test  */
  YYSYMBOL_comparison = 120,               /* comparison  */
  YYSYMBOL_comp_op_expr = 121,             /* comp_op_expr  */
  YYSYMBOL_comp_op_expr_sure = 122,        /* comp_op_expr_sure  */
  YYSYMBOL_expr = 123,                     /* expr  */
  YYSYMBOL_alte_xorexpr = 124,             /* alte_xorexpr  */
  YYSYMBOL_alte_xorexpr_sure = 125,        /* alte_xorexpr_sure  */
  YYSYMBOL_xor_expr = 126,                 /* xor_expr  */
  YYSYMBOL_power_andexpr = 127,            /* power_andexpr  */
  YYSYMBOL_power_andexpr_sure = 128,       /* power_andexpr_sure  */
  YYSYMBOL_and_expr = 129,                 /* and_expr  */
  YYSYMBOL_aand_shiftexpr = 130,           /* aand_shiftexpr  */
  YYSYMBOL_aand_shiftexpr_sure = 131,      /* aand_shiftexpr_sure  */
  YYSYMBOL_shift_expr = 132,               /* shift_expr  */
  YYSYMBOL_llt_ggt_arithexpr = 133,        /* llt_ggt_arithexpr  */
  YYSYMBOL_llt_ggt_arithexpr_sure = 134,   /* llt_ggt_arithexpr_sure  */
  YYSYMBOL_arith_expr = 135,               /* arith_expr  */
  YYSYMBOL_plus_minus_term = 136,          /* plus_minus_term  */
  YYSYMBOL_plus_minus_term_sure = 137,     /* plus_minus_term_sure  */
  YYSYMBOL_term = 138,                     /* term  */
  YYSYMBOL_operator_factor = 139,          /* operator_factor  */
  YYSYMBOL_operator_factor_sure = 140,     /* operator_factor_sure  */
  YYSYMBOL_factor = 141,                   /* factor  */
  YYSYMBOL_power = 142,                    /* power  */
  YYSYMBOL_atom_expr = 143,                /* atom_expr  */
  YYSYMBOL_trailer_sure = 144,             /* trailer_sure  */
  YYSYMBOL_atom = 145,                     /* atom  */
  YYSYMBOL_testlist = 146,                 /* testlist  */
  YYSYMBOL_testlistreturn = 147,           /* testlistreturn  */
  YYSYMBOL_comma_test = 148,               /* comma_test  */
  YYSYMBOL_comma_test_sure = 149,          /* comma_test_sure  */
  YYSYMBOL_testlist_comp = 150,            /* testlist_comp  */
  YYSYMBOL_exprlist = 151,                 /* exprlist  */
  YYSYMBOL_comma_expr = 152,               /* comma_expr  */
  YYSYMBOL_comma_expr_sure = 153,          /* comma_expr_sure  */
  YYSYMBOL_string_sure = 154,              /* string_sure  */
  YYSYMBOL_trailer = 155,                  /* trailer  */
  YYSYMBOL_arglist = 156,                  /* arglist  */
  YYSYMBOL_comma_argument = 157,           /* comma_argument  */
  YYSYMBOL_comma_argument_sure = 158,      /* comma_argument_sure  */
  YYSYMBOL_argument = 159,                 /* argument  */
  YYSYMBOL_subscriptlist = 160,            /* subscriptlist  */
  YYSYMBOL_comma_subscript = 161,          /* comma_subscript  */
  YYSYMBOL_comma_subscript_sure = 162,     /* comma_subscript_sure  */
  YYSYMBOL_subscript = 163,                /* subscript  */
  YYSYMBOL_comp_op = 164,                  /* comp_op  */
  YYSYMBOL_annassign = 165,                /* annassign  */
  YYSYMBOL_augassign = 166,                /* augassign  */
  YYSYMBOL_flow_stmt = 167,                /* flow_stmt  */
  YYSYMBOL_break_stmt = 168,               /* break_stmt  */
  YYSYMBOL_continue_stmt = 169,            /* continue_stmt  */
  YYSYMBOL_return_stmt = 170,              /* return_stmt  */
  YYSYMBOL_raise_stmt = 171,               /* raise_stmt  */
  YYSYMBOL_global_stmt = 172,              /* global_stmt  */
  YYSYMBOL_comma_identifier = 173,         /* comma_identifier  */
  YYSYMBOL_comma_identifier_sure = 174,    /* comma_identifier_sure  */
  YYSYMBOL_assert_stmt = 175,              /* assert_stmt  */
  YYSYMBOL_compound_stmt = 176,            /* compound_stmt  */
  YYSYMBOL_if_stmt = 177,                  /* if_stmt  */
  YYSYMBOL_else_if = 178,                  /* else_if  */
  YYSYMBOL_else_if_sure = 179,             /* else_if_sure  */
  YYSYMBOL_suite = 180,                    /* suite  */
  YYSYMBOL_line_or_newstmt = 181,          /* line_or_newstmt  */
  YYSYMBOL_line_or_newstmt_sure = 182,     /* line_or_newstmt_sure  */
  YYSYMBOL_new_stmt = 183,                 /* new_stmt  */
  YYSYMBOL_while_stmt = 184,               /* while_stmt  */
  YYSYMBOL_for_stmt = 185,                 /* for_stmt  */
  YYSYMBOL_funcdef = 186,                  /* funcdef  */
  YYSYMBOL_187_1 = 187,                    /* $@1  */
  YYSYMBOL_188_2 = 188,                    /* $@2  */
  YYSYMBOL_func_end = 189,                 /* func_end  */
  YYSYMBOL_190_3 = 190,                    /* $@3  */
  YYSYMBOL_191_4 = 191,                    /* $@4  */
  YYSYMBOL_parameters = 192,               /* parameters  */
  YYSYMBOL_typedargslist = 193,            /* typedargslist  */
  YYSYMBOL_comma_tfpdef = 194,             /* comma_tfpdef  */
  YYSYMBOL_comma_tfpdef_sure = 195,        /* comma_tfpdef_sure  */
  YYSYMBOL_tfpdef = 196,                   /* tfpdef  */
  YYSYMBOL_classdef = 197,                 /* classdef  */
  YYSYMBOL_198_5 = 198,                    /* $@5  */
  YYSYMBOL_199_6 = 199,                    /* $@6  */
  YYSYMBOL_200_7 = 200,                    /* $@7  */
  YYSYMBOL_dunder_block = 201              /* dunder_block  */
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
#define YYFINAL  102
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1201

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  95
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  107
/* YYNRULES -- Number of rules.  */
#define YYNRULES  275
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  378

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   349


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
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   896,   896,   900,   901,   904,   905,   908,   909,   912,
     913,   917,   918,   921,   922,   923,   924,   927,   930,   931,
     934,   935,   936,   937,   940,   948,   952,   956,   961,   966,
     968,   974,   978,   980,   984,   989,   994,   995,  1002,  1004,
    1008,  1012,  1016,  1021,  1022,  1028,  1032,  1036,  1041,  1042,
    1048,  1050,  1054,  1060,  1064,  1070,  1074,  1081,  1085,  1089,
    1093,  1094,  1100,  1104,  1108,  1112,  1113,  1119,  1123,  1127,
    1131,  1134,  1140,  1144,  1148,  1151,  1156,  1158,  1164,  1167,
    1171,  1175,  1181,  1182,  1186,  1189,  1193,  1197,  1201,  1205,
    1211,  1213,  1219,  1221,  1223,  1225,  1229,  1231,  1235,  1250,
    1254,  1263,  1274,  1277,  1280,  1286,  1292,  1294,  1299,  1304,
    1309,  1314,  1319,  1324,  1329,  1334,  1339,  1345,  1350,  1355,
    1359,  1361,  1365,  1370,  1375,  1417,  1421,  1425,  1429,  1435,
    1439,  1445,  1452,  1456,  1462,  1464,  1466,  1468,  1472,  1473,
    1474,  1475,  1479,  1482,  1483,  1487,  1488,  1491,  1496,  1500,
    1503,  1526,  1531,  1537,  1542,  1548,  1555,  1562,  1567,  1575,
    1581,  1592,  1594,  1598,  1600,  1604,  1607,  1608,  1611,  1615,
    1619,  1622,  1625,  1630,  1631,  1632,  1633,  1634,  1635,  1636,
    1637,  1638,  1639,  1640,  1643,  1647,  1654,  1655,  1656,  1657,
    1658,  1659,  1660,  1661,  1662,  1663,  1664,  1665,  1668,  1669,
    1670,  1671,  1674,  1677,  1680,  1682,  1691,  1692,  1693,  1698,
    1699,  1702,  1705,  1706,  1709,  1710,  1713,  1714,  1715,  1716,
    1717,  1718,  1721,  1723,  1725,  1727,  1731,  1734,  1735,  1738,
    1739,  1743,  1744,  1747,  1748,  1751,  1752,  1753,  1754,  1755,
    1756,  1759,  1760,  1764,  1766,  1770,  1770,  1793,  1793,  1809,
    1809,  1822,  1822,  1834,  1840,  1846,  1852,  1857,  1862,  1866,
    1872,  1877,  1882,  1889,  1894,  1900,  1904,  1910,  1918,  1932,
    1932,  1942,  1942,  1953,  1953,  1965
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
  "WHILE", "FOR", "RETURN", "IN", "FINALLY", "GLOBAL", "EXCEPT", "AS",
  "DEF", "CLASS", "ASSERT", "FROM", "CONTINUE", "BREAK", "RAISE", "NONE",
  "TRUE", "FALSE", "AND", "NOT", "OR", "DEL", "INT", "LISTINT",
  "LISTFLOAT", "LISTSTRING", "LISTBOOL", "LIST", "FLOAT", "STR", "BOOL",
  "IDENTIFIER", "DOUBLE_EQUAL", "GREATER_EQUAL", "LESS_EQUAL", "NOT_EQUAL",
  "DOUBLE_LESS", "DOUBLE_GREATER", "PLUS_EQUAL", "MINUS_EQUAL",
  "MULTI_EQUAL", "DIVI_EQUAL", "DOUBLE_DIVI_EQUAL", "MODULO_EQUAL",
  "DOUBLE_MULTI_EQUAL", "AND_EQUAL", "PIPE_EQUAL", "POWER_EQUAL",
  "DOUBLE_LESS_EQUAL", "DOUBLE_GREATER_EQUAL", "STRING", "NUMBER",
  "FLOAT_NUMBER", "IMAGINARY_NUMBER", "DOUBLE_STAR", "THREE_DOT",
  "GREATER_LESS", "ARROW", "DOUBLE_SLASH", "COLON", "SEMICOLON", "PLUS",
  "MINUS", "DIVI", "EQUAL", "COMMA", "PIPE", "ANDSYMBOL", "POWER", "MULTI",
  "MOD", "NOSYMBOL", "CIROPEN", "CIRCLOSE", "SQOPEN", "SQCLOSE", "CUOPEN",
  "CUCLOSE", "DOT", "LESS", "GREATER", "ADUNDER", "$accept", "starting",
  "file_input", "line_or_stmt_sure", "line_or_stmt", "line_sure", "stmt",
  "simple_stmt", "smlst", "smlst_sure", "small_stmt", "expr_stmt",
  "equal_testlist_star_expr", "equal_testlist_star_expr_sure",
  "testlist_star_expr", "comma_test2", "comma_test2_sure", "test",
  "or_test", "or_and_test", "or_and_test_sure", "and_test", "and_not_test",
  "and_not_test_sure", "not_test", "comparison", "comp_op_expr",
  "comp_op_expr_sure", "expr", "alte_xorexpr", "alte_xorexpr_sure",
  "xor_expr", "power_andexpr", "power_andexpr_sure", "and_expr",
  "aand_shiftexpr", "aand_shiftexpr_sure", "shift_expr",
  "llt_ggt_arithexpr", "llt_ggt_arithexpr_sure", "arith_expr",
  "plus_minus_term", "plus_minus_term_sure", "term", "operator_factor",
  "operator_factor_sure", "factor", "power", "atom_expr", "trailer_sure",
  "atom", "testlist", "testlistreturn", "comma_test", "comma_test_sure",
  "testlist_comp", "exprlist", "comma_expr", "comma_expr_sure",
  "string_sure", "trailer", "arglist", "comma_argument",
  "comma_argument_sure", "argument", "subscriptlist", "comma_subscript",
  "comma_subscript_sure", "subscript", "comp_op", "annassign", "augassign",
  "flow_stmt", "break_stmt", "continue_stmt", "return_stmt", "raise_stmt",
  "global_stmt", "comma_identifier", "comma_identifier_sure",
  "assert_stmt", "compound_stmt", "if_stmt", "else_if", "else_if_sure",
  "suite", "line_or_newstmt", "line_or_newstmt_sure", "new_stmt",
  "while_stmt", "for_stmt", "funcdef", "$@1", "$@2", "func_end", "$@3",
  "$@4", "parameters", "typedargslist", "comma_tfpdef",
  "comma_tfpdef_sure", "tfpdef", "classdef", "$@5", "$@6", "$@7",
  "dunder_block", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-326)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      26,  -326,  -326,   678,  1050,  1112,  1050,   -30,    13,   -13,
    1050,  -326,  -326,  1050,  -326,  -326,  -326,  1050,  -326,  -326,
    -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,   -28,  -326,
    -326,  -326,  -326,  1112,  1112,  1112,   740,   802,    -9,    83,
    -326,   197,  -326,  -326,  -326,     6,  -326,   192,     7,    98,
      70,    62,  -326,    93,    33,    38,    34,   -25,     0,    60,
    -326,    53,   -64,  -326,  -326,  -326,  -326,  -326,  -326,  -326,
    -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,    81,    55,
      56,    52,   116,    57,  -326,    59,  -326,  -326,   -59,    66,
     109,  -326,  -326,  -326,  -326,  -326,  -326,    67,    61,  -326,
      58,  -326,  -326,  -326,  -326,  -326,   480,  -326,     9,  -326,
    -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,
    -326,  1050,  1050,  -326,    76,  -326,  1050,  1050,  -326,    78,
    1050,  1050,  -326,    70,  1050,  -326,    62,   122,  -326,   141,
    -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,    93,  1112,
    1112,  -326,    33,  1112,  -326,    38,  1112,  -326,    34,  1112,
    1112,  -326,   -25,  1112,  1112,  -326,     0,  1112,  1112,  1112,
    1112,  -326,    60,  1112,   864,   926,    15,   -64,  -326,    64,
     548,   548,  1112,  -326,    82,  1050,  -326,   115,  -326,    59,
      79,    79,  -326,   988,  1050,  1050,  1050,  -326,    87,  -326,
    -326,  -326,  -326,  -326,   616,  -326,    89,  -326,  -326,    90,
    -326,  -326,  1050,  -326,   150,  -326,  -326,  -326,  -326,  -326,
    -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,
    -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,
    -326,  -326,    92,    88,    95,  1050,   103,    91,   102,  -326,
    -326,  -326,   104,  -326,    74,  -326,    75,   159,  -326,  1112,
    -326,   117,  -326,  -326,   -26,   124,   -42,   548,   125,   101,
    -326,  -326,  -326,  1050,  -326,  -326,  1050,  1050,   110,  1050,
    1050,  -326,  1050,  -326,   121,  -326,  1050,  -326,   926,  -326,
     123,   548,  -326,   412,   132,  1050,  -326,    84,   133,   548,
     134,  -326,   108,    21,   548,  1050,  -326,  -326,  -326,  -326,
     136,  -326,  1050,  -326,  -326,  -326,  1050,  -326,  -326,  -326,
     926,  -326,  -326,  -326,  -326,  -326,  -326,   334,  -326,  -326,
    -326,  -326,  -326,   548,   142,   144,  -326,   548,   202,  1050,
    -326,  1050,   173,  -326,   143,  -326,   156,   548,   548,  -326,
    -326,  -326,  -326,   548,   548,  -326,   158,  -326,   153,   178,
     173,  -326,  -326,  -326,  -326,   548,  -326,  -326,   548,   173,
     179,  1050,   548,  -326,  -326,   173,  -326,  -326
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,     7,     4,     0,     0,     0,   204,     0,     0,     0,
       0,   203,   202,   208,   121,   122,   123,     0,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   124,   145,   116,
     117,   118,   120,     0,     0,     0,     0,     0,     0,     0,
       2,     0,     5,     8,    11,     0,    20,    27,    32,    39,
      41,    46,    51,    53,    58,    63,    68,    73,    79,    85,
      95,    97,    99,   119,    21,   198,   199,   200,   201,    22,
      23,    12,   216,   217,   218,   219,   220,   221,     0,     0,
       0,   141,     0,   130,   205,   210,   247,   245,     0,   214,
     207,    50,   146,    92,    93,    94,   103,   137,     0,   105,
       0,   106,     1,     3,     6,    15,     0,    18,     0,   186,
     187,   188,   189,   197,   190,   196,   191,   192,   193,   194,
     195,     0,     0,    29,    26,    24,     0,    34,    36,    31,
       0,     0,    43,    40,     0,    48,    45,   182,   180,     0,
     175,   176,   177,   179,   178,   173,   174,    55,    52,     0,
       0,    60,    57,     0,    65,    62,     0,    70,    67,     0,
       0,    76,    72,     0,     0,    82,    78,     0,     0,     0,
       0,    90,    84,     0,     0,     0,     0,    98,   100,     0,
       0,     0,   139,   143,   140,     0,   129,     0,   212,   209,
       0,     0,   271,     0,     0,     0,   135,   132,   136,   102,
     104,    16,    17,    13,     0,    19,   184,    28,    30,   128,
      25,    35,    33,    37,     0,    42,    44,    47,    49,   183,
     181,    56,    54,    59,    61,    64,    66,    69,    71,    74,
      75,    77,    80,    81,    83,    89,    87,    86,    88,    91,
      96,   148,   159,     0,   153,   172,   168,     0,   162,   151,
     150,   101,     0,     9,     0,   229,   225,   241,   142,   138,
     144,     0,   211,   213,     0,     0,     0,     0,     0,     0,
     215,   206,   131,   134,   133,    14,     0,   127,   126,     0,
       0,   147,   155,   157,   152,   171,   170,   149,   164,   166,
     161,     0,    10,     0,     0,     0,   227,   224,     0,     0,
     267,   254,     0,   262,     0,     0,   251,   246,   272,   273,
       0,   185,   125,    38,   160,   156,   154,   158,   169,   165,
     163,   167,   275,   231,   235,   236,   233,     0,   232,   237,
     238,   239,   240,     0,     0,     0,   228,     0,   243,     0,
     253,     0,   258,   265,   261,   248,     0,     0,     0,   269,
     230,   234,   223,     0,     0,   242,     0,   268,   260,   264,
     257,   266,   249,   252,   274,     0,   226,   222,     0,   256,
     259,     0,     0,   270,   244,   255,   263,   250
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -326,  -326,  -326,  -326,   215,  -326,  -326,     2,   151,  -326,
    -100,  -326,   154,  -326,   145,   137,  -326,    -3,   138,   147,
    -326,   157,   139,  -326,   -12,  -326,   146,  -326,    -1,   135,
    -326,   140,   148,  -326,   152,   131,  -326,   155,   129,  -326,
     -54,   127,  -326,   -47,   126,  -326,   -18,  -326,  -326,  -326,
    -326,   111,  -326,  -190,    97,   260,  -326,   120,  -326,   271,
     130,   107,    17,  -326,  -245,  -326,    18,  -326,   149,  -326,
    -326,  -326,  -326,  -326,  -326,  -326,  -326,  -326,   161,  -326,
    -326,  -326,  -255,    19,  -326,  -170,   -17,  -326,  -326,  -251,
    -247,  -243,  -326,  -326,  -326,  -326,  -326,   128,  -326,  -325,
     -46,    50,  -326,  -326,  -326,  -326,  -220
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    39,    40,    41,    42,   254,    43,   255,   107,   108,
      45,    46,   123,   124,    47,   128,   129,    48,    49,   132,
     133,    50,   135,   136,    51,    52,   147,   148,    53,   151,
     152,    54,   154,   155,    55,   157,   158,    56,   161,   162,
      57,   165,   166,    58,   171,   172,    59,    60,    61,   177,
      62,   210,    84,   197,   198,    98,    82,   183,   184,    63,
     178,   243,   283,   284,   244,   247,   289,   290,   319,   149,
     125,   126,    64,    65,    66,    67,    68,    69,   188,   189,
      70,    71,    72,   296,   297,   256,   326,   327,   328,    73,
      74,    75,   191,   190,   307,   372,   347,   265,   302,   343,
     344,   359,    76,   365,   267,   348,    77
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      79,    80,    44,    83,    81,    91,   202,    89,   274,   105,
      90,   257,   203,   192,    85,    93,    94,    95,   300,   361,
      86,   174,   249,   175,   159,   160,   193,   176,   305,     1,
     306,    88,     2,    97,    97,    28,     3,   315,   325,     4,
       5,     6,   329,    44,     7,   361,   330,     8,     9,    10,
     331,    11,    12,    13,    14,    15,    16,    87,    17,   250,
     301,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,   315,   325,   332,   163,   164,   329,   292,   293,   106,
     330,   101,   204,   102,   331,   127,   294,   295,   274,    28,
      29,    30,    31,   134,    32,   335,   295,   308,   341,   342,
      33,    34,   137,   131,   202,   229,   230,   332,   130,   138,
      35,    36,   150,    37,   156,    38,   232,   233,   206,   153,
     173,   322,   217,   209,   211,   139,   179,   180,   181,   338,
     182,   167,   185,   195,   345,   186,   168,   187,   140,   141,
     142,   143,   169,   170,   194,   196,   200,   199,   222,   235,
     236,   237,   238,   122,   219,   240,   212,   220,   252,   262,
     259,   279,   144,   352,   264,   273,   276,   355,   277,   280,
     298,   242,   246,   282,   281,   286,   291,   363,   364,   287,
     288,   258,   209,   366,   367,   145,   146,   310,   312,   299,
     242,   270,   271,   272,   340,   373,   304,   309,   374,   316,
       1,   320,   377,   103,   333,   337,   339,     3,   349,   211,
       4,     5,     6,   356,   353,     7,   354,   300,     8,     9,
      10,   360,    11,    12,    13,    14,    15,    16,   362,    17,
     368,   369,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,   285,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   371,   104,   375,   258,   205,
      28,    29,    30,    31,   121,    32,   213,   207,   214,   122,
     272,    33,    34,   311,   272,   218,   313,   314,   208,   242,
     216,    35,    36,   318,    37,   246,    38,   224,   215,   228,
     223,   231,   334,   234,   221,   324,   261,   100,   239,    92,
     269,   317,   346,   226,   260,   225,   278,   251,   321,   272,
     351,   227,   370,   242,   303,     0,   336,   246,     0,   266,
       0,     0,     0,     0,   248,     0,     0,     0,     0,   324,
       0,     0,     0,     0,     0,     0,   357,   323,   358,   350,
       0,     0,     0,     0,     3,     0,     0,     4,     5,     6,
     263,     0,     7,     0,     0,     8,     0,    10,     0,    11,
      12,    13,    14,    15,    16,     0,    17,     0,   376,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    28,    29,    30,
      31,     0,    32,     0,     0,     0,     0,     0,    33,    34,
       0,     0,     0,     0,     0,   323,     0,     0,    35,    36,
       0,    37,     3,    38,     0,     4,     5,     6,     0,     0,
       7,     0,     0,     8,     0,    10,     0,    11,    12,    13,
      14,    15,    16,     0,    17,     0,     0,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    28,    29,    30,    31,     0,
      32,     0,     0,   201,     0,     0,    33,    34,     0,     0,
       0,     0,     0,     0,     0,     6,    35,    36,     7,    37,
       0,    38,     0,    10,     0,    11,    12,    13,    14,    15,
      16,     0,    17,     0,     0,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    28,    29,    30,    31,     0,    32,     0,
       0,   253,     0,     0,    33,    34,     0,     0,     0,     0,
       0,     0,     0,     6,    35,    36,     7,    37,     0,    38,
       0,    10,     0,    11,    12,    13,    14,    15,    16,     0,
      17,     0,     0,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    28,    29,    30,    31,     0,    32,     0,     0,   275,
       0,     0,    33,    34,     0,     0,     0,     0,     0,     0,
       0,     6,    35,    36,     7,    37,     0,    38,     0,    10,
       0,    11,    12,    13,    14,    15,    16,     0,    17,     0,
       0,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    28,
      29,    30,    31,     0,    32,    78,     0,     0,     0,     0,
      33,    34,     0,     0,     0,     0,     0,     0,     0,     0,
      35,    36,     0,    37,     0,    38,    14,    15,    16,     0,
      17,     0,     0,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    28,    29,    30,    31,     0,    32,     0,     0,     0,
       0,     0,    33,    34,     0,     0,     0,     0,     0,     0,
       0,     0,    35,    36,     0,    37,     0,    38,    14,    15,
      16,     0,    17,     0,     0,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    28,    29,    30,    31,     0,    32,     0,
       0,     0,     0,     0,    33,    34,     0,     0,     0,     0,
       0,     0,     0,     0,    35,    36,    96,    37,     0,    38,
      14,    15,    16,     0,    17,     0,     0,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    28,    29,    30,    31,     0,
      32,     0,     0,     0,     0,     0,    33,    34,     0,     0,
       0,     0,     0,     0,     0,     0,    35,    36,     0,    37,
      99,    38,    14,    15,    16,     0,    17,     0,     0,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    28,    29,    30,
      31,     0,    32,     0,     0,     0,     0,     0,    33,    34,
       0,     0,     0,     0,     0,     0,     0,     0,    35,    36,
     241,    37,     0,    38,    14,    15,    16,     0,    17,     0,
       0,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    28,
      29,    30,    31,     0,    32,     0,     0,     0,   245,     0,
      33,    34,     0,     0,     0,     0,     0,     0,     0,     0,
      35,    36,     0,    37,     0,    38,    14,    15,    16,     0,
      17,     0,     0,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    28,    29,    30,    31,     0,    32,     0,     0,     0,
       0,     0,    33,    34,     0,     0,     0,     0,     0,     0,
       0,     0,    35,    36,   268,    37,     0,    38,    14,    15,
      16,     0,    17,     0,     0,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    28,    29,    30,    31,     0,    32,     0,
       0,     0,     0,     0,    33,    34,     0,     0,     0,     0,
       0,     0,     0,     0,    35,    36,     0,    37,     0,    38,
      14,    15,    16,     0,     0,     0,     0,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    28,    29,    30,    31,     0,
      32,     0,     0,     0,     0,     0,    33,    34,     0,     0,
       0,     0,     0,     0,     0,     0,    35,    36,     0,    37,
       0,    38
};

static const yytype_int16 yycheck[] =
{
       3,     4,     0,     6,     5,    17,   106,    10,   198,     3,
      13,   181,     3,    72,    44,    33,    34,    35,    44,   344,
       7,    85,     7,    87,    49,    50,    85,    91,    70,     3,
      72,    44,     6,    36,    37,    63,    10,   282,   293,    13,
      14,    15,   293,    41,    18,   370,   293,    21,    22,    23,
     293,    25,    26,    27,    28,    29,    30,    44,    32,    44,
      86,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,   316,   327,   293,    74,    75,   327,     3,     4,    73,
     327,    90,    73,     0,   327,    78,    11,    12,   278,    63,
      64,    65,    66,    31,    68,    11,    12,   267,    77,    78,
      74,    75,     9,    33,   204,   159,   160,   327,    10,    16,
      84,    85,    79,    87,    80,    89,   163,   164,   121,    81,
      67,   291,   134,   126,   127,    32,    45,    72,    72,   299,
      78,    71,    16,    24,   304,    78,    76,    78,    45,    46,
      47,    48,    82,    83,    78,    78,    88,    86,   149,   167,
     168,   169,   170,    77,    32,   173,    78,    16,    94,    44,
      78,    11,    69,   333,    85,    78,    77,   337,    78,    77,
      11,   174,   175,    78,    86,    72,    72,   347,   348,    88,
      78,   182,   185,   353,   354,    92,    93,    86,    78,    72,
     193,   194,   195,   196,    86,   365,    72,    72,   368,    78,
       3,    78,   372,     6,    72,    72,    72,    10,    72,   212,
      13,    14,    15,    11,    72,    18,    72,    44,    21,    22,
      23,    78,    25,    26,    27,    28,    29,    30,    72,    32,
      72,    78,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,   245,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    77,    41,    78,   259,   108,
      63,    64,    65,    66,    72,    68,   129,   122,   130,    77,
     273,    74,    75,   276,   277,   136,   279,   280,   124,   282,
     133,    84,    85,   286,    87,   288,    89,   152,   131,   158,
     150,   162,   295,   166,   148,   293,   185,    37,   172,    28,
     193,   284,   305,   155,   184,   153,   209,   177,   290,   312,
     327,   156,   358,   316,   264,    -1,   297,   320,    -1,   191,
      -1,    -1,    -1,    -1,   175,    -1,    -1,    -1,    -1,   327,
      -1,    -1,    -1,    -1,    -1,    -1,   339,     3,   341,     5,
      -1,    -1,    -1,    -1,    10,    -1,    -1,    13,    14,    15,
     189,    -1,    18,    -1,    -1,    21,    -1,    23,    -1,    25,
      26,    27,    28,    29,    30,    -1,    32,    -1,   371,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,    65,
      66,    -1,    68,    -1,    -1,    -1,    -1,    -1,    74,    75,
      -1,    -1,    -1,    -1,    -1,     3,    -1,    -1,    84,    85,
      -1,    87,    10,    89,    -1,    13,    14,    15,    -1,    -1,
      18,    -1,    -1,    21,    -1,    23,    -1,    25,    26,    27,
      28,    29,    30,    -1,    32,    -1,    -1,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    64,    65,    66,    -1,
      68,    -1,    -1,     3,    -1,    -1,    74,    75,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    15,    84,    85,    18,    87,
      -1,    89,    -1,    23,    -1,    25,    26,    27,    28,    29,
      30,    -1,    32,    -1,    -1,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    63,    64,    65,    66,    -1,    68,    -1,
      -1,     3,    -1,    -1,    74,    75,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    15,    84,    85,    18,    87,    -1,    89,
      -1,    23,    -1,    25,    26,    27,    28,    29,    30,    -1,
      32,    -1,    -1,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    64,    65,    66,    -1,    68,    -1,    -1,     3,
      -1,    -1,    74,    75,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    15,    84,    85,    18,    87,    -1,    89,    -1,    23,
      -1,    25,    26,    27,    28,    29,    30,    -1,    32,    -1,
      -1,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      64,    65,    66,    -1,    68,     7,    -1,    -1,    -1,    -1,
      74,    75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    85,    -1,    87,    -1,    89,    28,    29,    30,    -1,
      32,    -1,    -1,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    64,    65,    66,    -1,    68,    -1,    -1,    -1,
      -1,    -1,    74,    75,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    -1,    87,    -1,    89,    28,    29,
      30,    -1,    32,    -1,    -1,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    63,    64,    65,    66,    -1,    68,    -1,
      -1,    -1,    -1,    -1,    74,    75,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    86,    87,    -1,    89,
      28,    29,    30,    -1,    32,    -1,    -1,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    64,    65,    66,    -1,
      68,    -1,    -1,    -1,    -1,    -1,    74,    75,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    -1,    87,
      88,    89,    28,    29,    30,    -1,    32,    -1,    -1,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,    65,
      66,    -1,    68,    -1,    -1,    -1,    -1,    -1,    74,    75,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,
      86,    87,    -1,    89,    28,    29,    30,    -1,    32,    -1,
      -1,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      64,    65,    66,    -1,    68,    -1,    -1,    -1,    72,    -1,
      74,    75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    85,    -1,    87,    -1,    89,    28,    29,    30,    -1,
      32,    -1,    -1,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    64,    65,    66,    -1,    68,    -1,    -1,    -1,
      -1,    -1,    74,    75,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    86,    87,    -1,    89,    28,    29,
      30,    -1,    32,    -1,    -1,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    63,    64,    65,    66,    -1,    68,    -1,
      -1,    -1,    -1,    -1,    74,    75,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    -1,    87,    -1,    89,
      28,    29,    30,    -1,    -1,    -1,    -1,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    64,    65,    66,    -1,
      68,    -1,    -1,    -1,    -1,    -1,    74,    75,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    -1,    87,
      -1,    89
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     6,    10,    13,    14,    15,    18,    21,    22,
      23,    25,    26,    27,    28,    29,    30,    32,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    63,    64,
      65,    66,    68,    74,    75,    84,    85,    87,    89,    96,
      97,    98,    99,   101,   102,   105,   106,   109,   112,   113,
     116,   119,   120,   123,   126,   129,   132,   135,   138,   141,
     142,   143,   145,   154,   167,   168,   169,   170,   171,   172,
     175,   176,   177,   184,   185,   186,   197,   201,     7,   112,
     112,   123,   151,   112,   147,    44,     7,    44,    44,   112,
     112,   119,   154,   141,   141,   141,    86,   112,   150,    88,
     150,    90,     0,     6,    99,     3,    73,   103,   104,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    72,    77,   107,   108,   165,   166,    78,   110,   111,
      10,    33,   114,   115,    31,   117,   118,     9,    16,    32,
      45,    46,    47,    48,    69,    92,    93,   121,   122,   164,
      79,   124,   125,    81,   127,   128,    80,   130,   131,    49,
      50,   133,   134,    74,    75,   136,   137,    71,    76,    82,
      83,   139,   140,    67,    85,    87,    91,   144,   155,    45,
      72,    72,    78,   152,   153,    16,    78,    78,   173,   174,
     188,   187,    72,    85,    78,    24,    78,   148,   149,    86,
      88,     3,   105,     3,    73,   103,   112,   109,   107,   112,
     146,   112,    78,   110,   113,   116,   114,   119,   117,    32,
      16,   121,   123,   126,   124,   129,   127,   132,   130,   135,
     135,   133,   138,   138,   136,   141,   141,   141,   141,   139,
     141,    86,   112,   156,   159,    72,   112,   160,   163,     7,
      44,   155,    94,     3,   100,   102,   180,   180,   123,    78,
     152,   146,    44,   173,    85,   192,   192,   199,    86,   156,
     112,   112,   112,    78,   148,     3,    77,    78,   149,    11,
      77,    86,    78,   157,   158,   112,    72,    88,    78,   161,
     162,    72,     3,     4,    11,    12,   178,   179,    11,    72,
      44,    86,   193,   196,    72,    70,    72,   189,   180,    72,
      86,   112,    78,   112,   112,   159,    78,   157,   112,   163,
      78,   161,   180,     3,   102,   177,   181,   182,   183,   184,
     185,   186,   201,    72,   112,    11,   178,    72,   180,    72,
      86,    77,    78,   194,   195,   180,   112,   191,   200,    72,
       5,   181,   180,    72,    72,   180,    11,   112,   112,   196,
      78,   194,    72,   180,   180,   198,   180,   180,    72,    78,
     195,    77,   190,   180,   180,    78,   112,   180
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    95,    96,    97,    97,    98,    98,    99,    99,   100,
     100,   101,   101,   102,   102,   102,   102,   103,   104,   104,
     105,   105,   105,   105,   106,   106,   106,   106,   107,   108,
     108,   109,   109,   109,   109,   110,   111,   111,   112,   112,
     113,   113,   114,   115,   115,   116,   116,   117,   118,   118,
     119,   119,   120,   120,   121,   122,   122,   123,   123,   124,
     125,   125,   126,   126,   127,   128,   128,   129,   129,   130,
     131,   131,   132,   132,   133,   133,   134,   134,   135,   135,
     136,   136,   137,   137,   138,   138,   139,   139,   139,   139,
     140,   140,   141,   141,   141,   141,   142,   142,   143,   143,
     144,   144,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   146,   146,   146,   146,   147,
     147,   148,   149,   149,   150,   150,   150,   150,   151,   151,
     151,   151,   152,   153,   153,   154,   154,   155,   155,   155,
     155,   155,   156,   156,   156,   156,   157,   158,   158,   159,
     159,   160,   160,   160,   160,   161,   162,   162,   163,   163,
     163,   163,   163,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   165,   165,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   167,   167,
     167,   167,   168,   169,   170,   170,   171,   171,   171,   172,
     172,   173,   174,   174,   175,   175,   176,   176,   176,   176,
     176,   176,   177,   177,   177,   177,   178,   179,   179,   180,
     180,   181,   181,   182,   182,   183,   183,   183,   183,   183,
     183,   184,   184,   185,   185,   187,   186,   188,   186,   190,
     189,   191,   189,   192,   192,   193,   193,   193,   193,   193,
     193,   193,   193,   194,   194,   195,   195,   196,   196,   198,
     197,   199,   197,   200,   197,   201
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     2,     1,     1,     1,
       2,     1,     1,     3,     4,     2,     3,     2,     1,     2,
       1,     1,     1,     1,     2,     3,     2,     1,     2,     1,
       2,     2,     1,     3,     2,     2,     1,     2,     5,     1,
       2,     1,     2,     1,     2,     2,     1,     2,     1,     2,
       2,     1,     2,     1,     2,     1,     2,     2,     1,     2,
       1,     2,     2,     1,     2,     1,     2,     2,     1,     2,
       1,     2,     2,     1,     2,     2,     1,     2,     2,     1,
       2,     2,     1,     2,     2,     1,     2,     2,     2,     2,
       1,     2,     2,     2,     2,     1,     3,     1,     2,     1,
       1,     2,     3,     2,     3,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     2,     2,     1,     2,
       1,     2,     1,     2,     3,     2,     2,     1,     3,     2,
       2,     1,     2,     1,     2,     1,     2,     3,     2,     3,
       2,     2,     2,     1,     3,     2,     2,     1,     2,     1,
       3,     2,     1,     3,     2,     2,     1,     2,     1,     3,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     2,     2,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     4,     2,     1,     3,
       2,     2,     1,     2,     2,     4,     1,     1,     1,     1,
       1,     1,     8,     7,     5,     4,     4,     1,     2,     1,
       4,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     4,     7,     6,     9,     0,     5,     0,     6,     0,
       5,     0,     3,     3,     2,     5,     4,     3,     2,     4,
       3,     2,     1,     4,     2,     1,     2,     1,     3,     0,
       8,     0,     5,     0,     7,     6
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
#line 896 "parser.y"
                     {(yyval.info)->val=addnode("starting");addedge((yyval.info)->val, (yyvsp[0].info)->val); GlobalSymbolTable->printAll(); threeacir->print();
                     return 0;}
#line 2621 "parser.tab.c"
    break;

  case 3: /* file_input: line_or_stmt_sure ENDMARKER  */
#line 900 "parser.y"
                                        {(yyval.info)->val=addnode("file_input");addedge((yyval.info)->val, (yyvsp[-1].info)->val);}
#line 2627 "parser.tab.c"
    break;

  case 4: /* file_input: ENDMARKER  */
#line 901 "parser.y"
                      {(yyval.info)->val=addnode("file_input");(yyvsp[0].val)=addnode(string("ENDMARKER") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 2633 "parser.tab.c"
    break;

  case 5: /* line_or_stmt_sure: line_or_stmt  */
#line 904 "parser.y"
                               {(yyval.info)->val= (yyvsp[0].info)->val;}
#line 2639 "parser.tab.c"
    break;

  case 6: /* line_or_stmt_sure: line_or_stmt_sure line_or_stmt  */
#line 905 "parser.y"
                                       {(yyval.info)->val=addnode("line_or_stmt_sure");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 2645 "parser.tab.c"
    break;

  case 7: /* line_or_stmt: NEWLINE  */
#line 908 "parser.y"
                      {(yyval.info)->val=addnode("NEWLINE");(yyvsp[0].val)=addnode(string("newline") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 2651 "parser.tab.c"
    break;

  case 8: /* line_or_stmt: stmt  */
#line 909 "parser.y"
          {(yyval.info)->val= (yyvsp[0].info)->val;}
#line 2657 "parser.tab.c"
    break;

  case 9: /* line_sure: NEWLINE  */
#line 912 "parser.y"
                   {(yyval.info)->val=addnode("NEWLINE");(yyvsp[0].val)=addnode(string("newline") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 2663 "parser.tab.c"
    break;

  case 10: /* line_sure: line_sure NEWLINE  */
#line 913 "parser.y"
                          {(yyval.info)->val=addnode("line_sure");addedge((yyval.info)->val, (yyvsp[-1].info)->val);(yyvsp[0].val)=addnode(string("NEWLINE"));addedge((yyval.info)->val, (yyvsp[0].val));}
#line 2669 "parser.tab.c"
    break;

  case 11: /* stmt: simple_stmt  */
#line 917 "parser.y"
                  {(yyval.info)->val= (yyvsp[0].info)->val;}
#line 2675 "parser.tab.c"
    break;

  case 12: /* stmt: compound_stmt  */
#line 918 "parser.y"
                     {(yyval.info)->val= (yyvsp[0].info)->val;}
#line 2681 "parser.tab.c"
    break;

  case 13: /* simple_stmt: small_stmt smlst_sure NEWLINE  */
#line 921 "parser.y"
                                           {(yyval.info)->val=addnode("simple_stmt");addedge((yyval.info)->val, (yyvsp[-2].info)->val);addedge((yyval.info)->val, (yyvsp[-1].info)->val);(yyvsp[0].val)=addnode(string("NEWLINE") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 2687 "parser.tab.c"
    break;

  case 14: /* simple_stmt: small_stmt smlst_sure SEMICOLON NEWLINE  */
#line 922 "parser.y"
                                                     {(yyval.info)->val=addnode("simple_stmt");addedge((yyval.info)->val, (yyvsp[-3].info)->val);addedge((yyval.info)->val, (yyvsp[-2].info)->val);(yyvsp[-1].val)=addnode(string("SEMICOLON") );addedge((yyval.info)->val, (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("NEWLINE") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 2693 "parser.tab.c"
    break;

  case 15: /* simple_stmt: small_stmt NEWLINE  */
#line 923 "parser.y"
                                {(yyval.info)->val=addnode("simple_stmt");addedge((yyval.info)->val, (yyvsp[-1].info)->val);(yyvsp[0].val)=addnode(string("NEWLINE"));addedge((yyval.info)->val, (yyvsp[0].val));}
#line 2699 "parser.tab.c"
    break;

  case 16: /* simple_stmt: small_stmt SEMICOLON NEWLINE  */
#line 924 "parser.y"
                                          {(yyval.info)->val=addnode("simple_stmt");addedge((yyval.info)->val, (yyvsp[-2].info)->val);(yyvsp[-1].val)=addnode(string("SEMICOLON"));addedge((yyval.info)->val, (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("NEWLINE") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 2705 "parser.tab.c"
    break;

  case 17: /* smlst: SEMICOLON small_stmt  */
#line 927 "parser.y"
                            {(yyval.info)->val=addnode("smlst");(yyvsp[-1].val)=addnode(string("SEMICOLON") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 2711 "parser.tab.c"
    break;

  case 18: /* smlst_sure: smlst  */
#line 930 "parser.y"
                  {(yyval.info)->val=(yyvsp[0].info)->val;}
#line 2717 "parser.tab.c"
    break;

  case 19: /* smlst_sure: smlst_sure smlst  */
#line 931 "parser.y"
                             {(yyval.info)->val=addnode("smlst_sure");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 2723 "parser.tab.c"
    break;

  case 20: /* small_stmt: expr_stmt  */
#line 934 "parser.y"
                      {(yyval.info)->val=(yyvsp[0].info)->val;}
#line 2729 "parser.tab.c"
    break;

  case 21: /* small_stmt: flow_stmt  */
#line 935 "parser.y"
                      {(yyval.info)->val=(yyvsp[0].info)->val;}
#line 2735 "parser.tab.c"
    break;

  case 22: /* small_stmt: global_stmt  */
#line 936 "parser.y"
                        {(yyval.info)->val=(yyvsp[0].info)->val;}
#line 2741 "parser.tab.c"
    break;

  case 23: /* small_stmt: assert_stmt  */
#line 937 "parser.y"
                        {(yyval.info)->val=(yyvsp[0].info)->val;}
#line 2747 "parser.tab.c"
    break;

  case 24: /* expr_stmt: testlist_star_expr annassign  */
#line 940 "parser.y"
                                        { 
              nor_sym*temp=GlobalSymbolTable->search_nor_sym((yyvsp[-1].info)->name,GlobalSymbolTable->curr_scope);
              temp->type=(yyvsp[0].info)->type;
              if((yyvsp[0].info)->type== "string") temp->size=12;
              else temp->size= (yyvsp[0].info)->c*type_size_map[(yyvsp[0].info)->type];
              GlobalSymbolTable->curr_sym_tbl->offset+=temp->size;

              (yyval.info)->val=addnode("expr_stmt");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 2760 "parser.tab.c"
    break;

  case 25: /* expr_stmt: testlist_star_expr augassign testlist  */
#line 948 "parser.y"
                                                 {
            if((yyvsp[-2].info)->type!=(yyvsp[0].info)->type)yyerror1("100 There is type mismach",yylineno);
            (yyval.info)=new Info();(yyval.info)->type=(yyvsp[-2].info)->type;
              (yyval.info)->val=addnode("expr_stmt");addedge((yyval.info)->val, (yyvsp[-2].info)->val);addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 2769 "parser.tab.c"
    break;

  case 26: /* expr_stmt: testlist_star_expr equal_testlist_star_expr_sure  */
#line 952 "parser.y"
                                                            {
              if((yyvsp[-1].info)->type!=(yyvsp[0].info)->type) yyerror1("1 There is type mismach",yylineno);
              (yyval.info)=new Info();(yyvsp[-1].info)->type=(yyvsp[0].info)->type;(yyval.info)->val=addnode("expr_stmt");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val); int k=GlobalSymbolTable->curr_sym_tbl->nor_sym_vec.size();GlobalSymbolTable->curr_sym_tbl->nor_sym_vec[k-1]->type=(yyvsp[0].info)->type;
              GlobalSymbolTable->curr_sym_tbl->nor_sym_vec[k-1]->size= type_size_map[(yyvsp[0].info)->type];}
#line 2778 "parser.tab.c"
    break;

  case 27: /* expr_stmt: testlist_star_expr  */
#line 956 "parser.y"
                              {
          (yyval.info)=new Info();(yyval.info)->type=(yyvsp[0].info)->type;
              (yyval.info)->val=(yyvsp[0].info)->val;}
#line 2786 "parser.tab.c"
    break;

  case 28: /* equal_testlist_star_expr: EQUAL testlist_star_expr  */
#line 961 "parser.y"
                                                    {
            (yyval.info)=new Info();(yyval.info)->type=(yyvsp[0].info)->type;
            (yyval.info)->val=addnode("equal_testlist_star_expr");(yyvsp[-1].val)=addnode(string("EQUAL") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 2794 "parser.tab.c"
    break;

  case 29: /* equal_testlist_star_expr_sure: equal_testlist_star_expr  */
#line 966 "parser.y"
                                                         {
                (yyval.info)=new Info();(yyval.info)->type=(yyvsp[0].info)->type;(yyval.info)->val=(yyvsp[0].info)->val;}
#line 2801 "parser.tab.c"
    break;

  case 30: /* equal_testlist_star_expr_sure: equal_testlist_star_expr_sure equal_testlist_star_expr  */
#line 968 "parser.y"
                                                                    {
                (yyval.info)=new Info();(yyval.info)->type=(yyvsp[0].info)->type;
                if((yyvsp[-1].info)->type!=(yyvsp[0].info)->type) yyerror1("36 there is a type mismatch",yylineno);
                (yyval.info)->val=addnode("equal_testlist_star_expr_sure");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 2810 "parser.tab.c"
    break;

  case 31: /* testlist_star_expr: test comma_test2_sure  */
#line 974 "parser.y"
                                          {
                        (yyval.info)=new Info();(yyval.info)->type=(yyvsp[-1].info)->type;
                        if((yyvsp[-1].info)->type!=(yyvsp[0].info)->type) yyerror1("35 there is a type mismatch",yylineno);
                        (yyval.info)->val=addnode("testlist_star_expr");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 2819 "parser.tab.c"
    break;

  case 32: /* testlist_star_expr: test  */
#line 978 "parser.y"
                         {
                        (yyval.info)=new Info();(yyval.info)->name=(yyvsp[0].info)->name;(yyval.info)->type=(yyvsp[0].info)->type;(yyval.info)->val=(yyvsp[0].info)->val;}
#line 2826 "parser.tab.c"
    break;

  case 33: /* testlist_star_expr: test comma_test2_sure COMMA  */
#line 980 "parser.y"
                                                {
                        (yyval.info)=new Info();(yyval.info)->type=(yyvsp[-2].info)->type;
                        if((yyvsp[-2].info)->type!=(yyvsp[-1].info)->type) yyerror1("34 there is a type mismatch",yylineno);
                        (yyval.info)->val=addnode("testlist_star_expr");addedge((yyval.info)->val, (yyvsp[-2].info)->val);addedge((yyval.info)->val, (yyvsp[-1].info)->val);(yyvsp[0].val)=addnode(string("COMMA") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 2835 "parser.tab.c"
    break;

  case 34: /* testlist_star_expr: test COMMA  */
#line 984 "parser.y"
                               {
                        (yyval.info)=new Info();(yyval.info)->type=(yyvsp[-1].info)->type;
                        (yyval.info)->val=addnode("testlist_star_expr");addedge((yyval.info)->val, (yyvsp[-1].info)->val);(yyvsp[0].val)=addnode(string("COMMA"));addedge((yyval.info)->val, (yyvsp[0].val));}
#line 2843 "parser.tab.c"
    break;

  case 35: /* comma_test2: COMMA test  */
#line 989 "parser.y"
                        {
        (yyval.info)=new Info();(yyval.info)->type=(yyvsp[0].info)->type;
        (yyval.info)->val=addnode("comma_test2");(yyvsp[-1].val)=addnode(string("COMMA") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 2851 "parser.tab.c"
    break;

  case 36: /* comma_test2_sure: comma_test2  */
#line 994 "parser.y"
                               {(yyval.info)=new Info();(yyval.info)->type=(yyvsp[0].info)->type;(yyval.info)->val=(yyvsp[0].info)->val;}
#line 2857 "parser.tab.c"
    break;

  case 37: /* comma_test2_sure: comma_test2_sure comma_test2  */
#line 995 "parser.y"
                                        {
            (yyval.info)=new Info();(yyval.info)->type=(yyvsp[-1].info)->type;
            if((yyvsp[-1].info)->type!=(yyvsp[0].info)->type) yyerror1("33 there is a type mismatch",yylineno);
            (yyval.info)->val=addnode("comma_test2_sure");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 2866 "parser.tab.c"
    break;

  case 38: /* test: or_test IF or_test ELSE test  */
#line 1002 "parser.y"
                                   {
         (yyval.info)->val=addnode("test");addedge((yyval.info)->val, (yyvsp[-4].info)->val);(yyvsp[-3].val)=addnode(string("IF"));addedge((yyval.info)->val, (yyvsp[-3].val));addedge((yyval.info)->val, (yyvsp[-2].info)->val);(yyvsp[-1].val)=addnode(string("ELSE") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 2873 "parser.tab.c"
    break;

  case 39: /* test: or_test  */
#line 1004 "parser.y"
              {
        (yyval.info)=new Info(); (yyval.info)->name=(yyvsp[0].info)->name;(yyval.info)->type=(yyvsp[0].info)->type;(yyval.info)->val=(yyvsp[0].info)->val;}
#line 2880 "parser.tab.c"
    break;

  case 40: /* or_test: and_test or_and_test_sure  */
#line 1008 "parser.y"
                                   {
            (yyval.info)=new Info();(yyval.info)->type=(yyvsp[-1].info)->type;
            if((yyvsp[-1].info)->type!=(yyvsp[0].info)->type) yyerror1("33 there is a type mismatch",yylineno);
            (yyval.info)->val=addnode("or_test");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 2889 "parser.tab.c"
    break;

  case 41: /* or_test: and_test  */
#line 1012 "parser.y"
                  {
            (yyval.info)=new Info();(yyval.info)->name=(yyvsp[0].info)->name;(yyval.info)->type=(yyvsp[0].info)->type; (yyval.info)->val=(yyvsp[0].info)->val;}
#line 2896 "parser.tab.c"
    break;

  case 42: /* or_and_test: OR and_test  */
#line 1016 "parser.y"
                        {
          (yyval.info)=new Info();(yyval.info)->type=(yyvsp[0].info)->type;
          (yyval.info)->val=addnode("or_and_test");(yyvsp[-1].val)=addnode(string("OR") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 2904 "parser.tab.c"
    break;

  case 43: /* or_and_test_sure: or_and_test  */
#line 1021 "parser.y"
                              {(yyval.info)=new Info();(yyval.info)->type=(yyvsp[0].info)->type;(yyval.info)->val=(yyvsp[0].info)->val;}
#line 2910 "parser.tab.c"
    break;

  case 44: /* or_and_test_sure: or_and_test_sure or_and_test  */
#line 1022 "parser.y"
                                       {
            (yyval.info)=new Info();(yyval.info)->type=(yyvsp[0].info)->type;
            if((yyvsp[-1].info)->type!=(yyvsp[0].info)->type) yyerror1("32 there is a type mismatch",yylineno);
            (yyval.info)->val=addnode("or_and_test_sure");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 2919 "parser.tab.c"
    break;

  case 45: /* and_test: not_test and_not_test_sure  */
#line 1028 "parser.y"
                                     {
            (yyval.info)=new Info();(yyval.info)->type=(yyvsp[-1].info)->type;
            if((yyvsp[-1].info)->type!=(yyvsp[0].info)->type) yyerror1("31 there is a type mismatch",yylineno);
            (yyval.info)->val=addnode("and_test");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 2928 "parser.tab.c"
    break;

  case 46: /* and_test: not_test  */
#line 1032 "parser.y"
                   {
            (yyval.info)=new Info();(yyval.info)->name=(yyvsp[0].info)->name;(yyval.info)->type=(yyvsp[0].info)->type; (yyval.info)->val=(yyvsp[0].info)->val;}
#line 2935 "parser.tab.c"
    break;

  case 47: /* and_not_test: AND not_test  */
#line 1036 "parser.y"
                           {
        (yyval.info)=new Info();(yyval.info)->type=(yyvsp[0].info)->type;
        (yyval.info)->val=addnode("and_not_test");(yyvsp[-1].val)=addnode(string("AND") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 2943 "parser.tab.c"
    break;

  case 48: /* and_not_test_sure: and_not_test  */
#line 1041 "parser.y"
                                {(yyval.info)=new Info();(yyval.info)->type=(yyvsp[0].info)->type;(yyval.info)->val=(yyvsp[0].info)->val;}
#line 2949 "parser.tab.c"
    break;

  case 49: /* and_not_test_sure: and_not_test_sure and_not_test  */
#line 1042 "parser.y"
                                         {
            (yyval.info)=new Info();(yyval.info)->type=(yyvsp[0].info)->type;
            if((yyvsp[-1].info)->type!=(yyvsp[0].info)->type) yyerror1("30 there is a type mismatch",yylineno);
            (yyval.info)->val=addnode("and_not_test_sure");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 2958 "parser.tab.c"
    break;

  case 50: /* not_test: NOT not_test  */
#line 1048 "parser.y"
                       {
              (yyval.info)=new Info();(yyval.info)->type=(yyvsp[0].info)->type;(yyval.info)->val=addnode("not_test");(yyvsp[-1].val)=addnode(string("NOT") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 2965 "parser.tab.c"
    break;

  case 51: /* not_test: comparison  */
#line 1050 "parser.y"
                     {
              (yyval.info)=new Info();(yyval.info)->name=(yyvsp[0].info)->name;(yyval.info)->type=(yyvsp[0].info)->type;(yyval.info)->val=(yyvsp[0].info)->val;}
#line 2972 "parser.tab.c"
    break;

  case 52: /* comparison: expr comp_op_expr_sure  */
#line 1054 "parser.y"
                                   {
                  int k= GlobalSymbolTable->curr_sym_tbl->nor_sym_vec.size();
                  GlobalSymbolTable->curr_sym_tbl->nor_sym_vec[k-1]->type=(yyvsp[0].info)->type;
                  GlobalSymbolTable->curr_sym_tbl->nor_sym_vec[k-1]->size= type_size_map[(yyvsp[0].info)->type];
                  if((yyvsp[-1].info)->type!=(yyvsp[0].info)->type) yyerror1("2 there is a type mismatch",yylineno);
                  (yyval.info)=new Info();(yyval.info)->type=(yyvsp[-1].info)->type;(yyval.info)->val=addnode("comparison");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 2983 "parser.tab.c"
    break;

  case 53: /* comparison: expr  */
#line 1060 "parser.y"
                 {
                  (yyval.info)=new Info();(yyval.info)->name=(yyvsp[0].info)->name;(yyval.info)->type=(yyvsp[0].info)->type; (yyval.info)->val=(yyvsp[0].info)->val;}
#line 2990 "parser.tab.c"
    break;

  case 54: /* comp_op_expr: comp_op expr  */
#line 1064 "parser.y"
                           {
        (yyval.info)=new Info();
        (yyval.info)->type=(yyvsp[0].info)->type;
        (yyval.info)->val=addnode("comp_op_expr");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 2999 "parser.tab.c"
    break;

  case 55: /* comp_op_expr_sure: comp_op_expr  */
#line 1070 "parser.y"
                                 {
              (yyval.info) = new Info();
              (yyval.info)->type=(yyvsp[0].info)->type;
              (yyval.info)->val=(yyvsp[0].info)->val;}
#line 3008 "parser.tab.c"
    break;

  case 56: /* comp_op_expr_sure: comp_op_expr_sure comp_op_expr  */
#line 1074 "parser.y"
                                          {
              (yyval.info)=new Info();
              (yyval.info)->type=(yyvsp[-1].info)->type;
              if((yyvsp[-1].info)->type != (yyvsp[0].info)->type) yyerror1("3 there is a type mismatch",yylineno);
              (yyval.info)->val=addnode("comp_op_expr_sure");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3018 "parser.tab.c"
    break;

  case 57: /* expr: xor_expr alte_xorexpr_sure  */
#line 1081 "parser.y"
                                 {
          (yyval.info)=new Info();(yyval.info)->type=(yyvsp[-1].info)->type;
          if((yyvsp[-1].info)->type!=(yyvsp[0].info)->type) yyerror1("26 there is a type mismatch",yylineno);
          (yyval.info)->val=addnode("expr");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3027 "parser.tab.c"
    break;

  case 58: /* expr: xor_expr  */
#line 1085 "parser.y"
               {
          (yyval.info)=new Info();(yyval.info)->name=(yyvsp[0].info)->name;(yyval.info)->type=(yyvsp[0].info)->type; (yyval.info)->val=(yyvsp[0].info)->val;}
#line 3034 "parser.tab.c"
    break;

  case 59: /* alte_xorexpr: PIPE xor_expr  */
#line 1089 "parser.y"
                            {
        (yyval.info)=new Info();(yyval.info)->type=(yyvsp[0].info)->type;(yyval.info)->val=addnode("alte_xorexpr");(yyvsp[-1].val)=addnode(string("PIPE") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3041 "parser.tab.c"
    break;

  case 60: /* alte_xorexpr_sure: alte_xorexpr  */
#line 1093 "parser.y"
                                {(yyval.info)=new Info();(yyval.info)->type=(yyvsp[0].info)->type;(yyval.info)->val=(yyvsp[0].info)->val;}
#line 3047 "parser.tab.c"
    break;

  case 61: /* alte_xorexpr_sure: alte_xorexpr_sure alte_xorexpr  */
#line 1094 "parser.y"
                                        {
            (yyval.info)=new Info();(yyval.info)->type=(yyvsp[-1].info)->type;
            if((yyvsp[-1].info)->type!=(yyvsp[0].info)->type) yyerror1("25 there is a type mismatch",yylineno);
            (yyval.info)->val=addnode("alte_xorexpr_sure");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3056 "parser.tab.c"
    break;

  case 62: /* xor_expr: and_expr power_andexpr_sure  */
#line 1100 "parser.y"
                                      {
            (yyval.info)=new Info();(yyval.info)->type=(yyvsp[-1].info)->type;
            if((yyvsp[-1].info)->type!=(yyvsp[0].info)->type) yyerror1("25 there is a type mismatch",yylineno);
            (yyval.info)->val=addnode("xor_expr");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3065 "parser.tab.c"
    break;

  case 63: /* xor_expr: and_expr  */
#line 1104 "parser.y"
                   {
            (yyval.info)=new Info();(yyval.info)->name=(yyvsp[0].info)->name;(yyval.info)->type=(yyvsp[0].info)->type;(yyval.info)->val=(yyvsp[0].info)->val;}
#line 3072 "parser.tab.c"
    break;

  case 64: /* power_andexpr: POWER and_expr  */
#line 1108 "parser.y"
                              {
        (yyval.info)=new Info();(yyval.info)->type=(yyvsp[0].info)->type;(yyval.info)->val=addnode("power_andexpr");(yyvsp[-1].val)=addnode(string("POWER") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3079 "parser.tab.c"
    break;

  case 65: /* power_andexpr_sure: power_andexpr  */
#line 1112 "parser.y"
                                  {(yyval.info)=new Info();(yyval.info)->type=(yyvsp[0].info)->type;(yyval.info)->val=(yyvsp[0].info)->val;}
#line 3085 "parser.tab.c"
    break;

  case 66: /* power_andexpr_sure: power_andexpr_sure power_andexpr  */
#line 1113 "parser.y"
                                          {
            (yyval.info)=new Info();(yyval.info)->type=(yyvsp[-1].info)->type;
            if((yyvsp[-1].info)->type!=(yyvsp[0].info)->type) yyerror1("24 there is a type mismatch",yylineno);
            (yyval.info)->val=addnode("power_andexpr_sure");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3094 "parser.tab.c"
    break;

  case 67: /* and_expr: shift_expr aand_shiftexpr_sure  */
#line 1119 "parser.y"
                                         {
              (yyval.info)=new Info();(yyval.info)->type=(yyvsp[-1].info)->type;
              if((yyvsp[-1].info)->type!=(yyvsp[0].info)->type) yyerror1("23 there is a type mismatch",yylineno);
              (yyval.info)->val=addnode("and_expr");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3103 "parser.tab.c"
    break;

  case 68: /* and_expr: shift_expr  */
#line 1123 "parser.y"
                     {
              (yyval.info)=new Info();(yyval.info)->name=(yyvsp[0].info)->name;(yyval.info)->type=(yyvsp[0].info)->type; (yyval.info)->val=(yyvsp[0].info)->val;}
#line 3110 "parser.tab.c"
    break;

  case 69: /* aand_shiftexpr: ANDSYMBOL shift_expr  */
#line 1127 "parser.y"
                                     {
         (yyval.info)=new Info();(yyval.info)->type=(yyvsp[0].info)->type;(yyval.info)->val=addnode("aand_shiftexpr");(yyvsp[-1].val)=addnode(string("ANDSYMBOL") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3117 "parser.tab.c"
    break;

  case 70: /* aand_shiftexpr_sure: aand_shiftexpr  */
#line 1131 "parser.y"
                                     {
            (yyval.info)=new Info();(yyval.info)->type=(yyvsp[0].info)->type;
            (yyval.info)->val=(yyvsp[0].info)->val;}
#line 3125 "parser.tab.c"
    break;

  case 71: /* aand_shiftexpr_sure: aand_shiftexpr_sure aand_shiftexpr  */
#line 1134 "parser.y"
                                             {
            (yyval.info)=new Info();(yyval.info)->type=(yyvsp[-1].info)->type;
            if((yyvsp[-1].info)->type!=(yyvsp[0].info)->type) yyerror1("22 there is a type mismatch",yylineno);
            (yyval.info)->val=addnode("aand_shiftexpr_sure");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3134 "parser.tab.c"
    break;

  case 72: /* shift_expr: arith_expr llt_ggt_arithexpr_sure  */
#line 1140 "parser.y"
                                              {
              (yyval.info)=new Info();(yyval.info)->type=(yyvsp[-1].info)->type;
              if((yyvsp[-1].info)->type!=(yyvsp[0].info)->type) yyerror1("21 there is a type mismatch",yylineno);
              (yyval.info)->val=addnode("shift_expr");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3143 "parser.tab.c"
    break;

  case 73: /* shift_expr: arith_expr  */
#line 1144 "parser.y"
                       {
              (yyval.info)=new Info();(yyval.info)->name=(yyvsp[0].info)->name;(yyval.info)->type=(yyvsp[0].info)->type;(yyval.info)->val=(yyvsp[0].info)->val;}
#line 3150 "parser.tab.c"
    break;

  case 74: /* llt_ggt_arithexpr: DOUBLE_LESS arith_expr  */
#line 1148 "parser.y"
                                          {
        (yyval.info)=new Info();(yyval.info)->type=(yyvsp[0].info)->type;
        (yyval.info)->val=addnode("llt_ggt_arithexpr");(yyvsp[-1].val)=addnode(string("DOUBLE_LESS") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3158 "parser.tab.c"
    break;

  case 75: /* llt_ggt_arithexpr: DOUBLE_GREATER arith_expr  */
#line 1151 "parser.y"
                               {
        (yyval.info)=new Info();(yyval.info)->type=(yyvsp[0].info)->type;
        (yyval.info)->val=addnode("llt_ggt_arithexpr");(yyvsp[-1].val)=addnode(string("DOUBLE_GREATER") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3166 "parser.tab.c"
    break;

  case 76: /* llt_ggt_arithexpr_sure: llt_ggt_arithexpr  */
#line 1156 "parser.y"
                                          {
            (yyval.info)=new Info();(yyval.info)->type=(yyvsp[0].info)->type;(yyval.info)->val=(yyvsp[0].info)->val;}
#line 3173 "parser.tab.c"
    break;

  case 77: /* llt_ggt_arithexpr_sure: llt_ggt_arithexpr_sure llt_ggt_arithexpr  */
#line 1158 "parser.y"
                                                   {
            (yyval.info)=new Info();(yyval.info)->type=(yyvsp[-1].info)->type;
            if((yyvsp[-1].info)->type!=(yyvsp[0].info)->type) yyerror1("20 there is a type mismatch",yylineno);
            (yyval.info)->val=addnode("llt_ggt_arithexpr_sure");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3182 "parser.tab.c"
    break;

  case 78: /* arith_expr: term plus_minus_term_sure  */
#line 1164 "parser.y"
                                      { 
                if((yyvsp[-1].info)->type !=(yyvsp[0].info)->type) yyerror1("4 there is type mismatch",yylineno);
                (yyval.info)=new Info();(yyval.info)->type=(yyvsp[-1].info)->type;(yyval.info)->val=addnode("arith_expr");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3190 "parser.tab.c"
    break;

  case 79: /* arith_expr: term  */
#line 1167 "parser.y"
                 { 
                (yyval.info)=new Info();(yyval.info)->name=(yyvsp[0].info)->name;(yyval.info)->type=(yyvsp[0].info)->type;(yyval.info)->val=(yyvsp[0].info)->val;}
#line 3197 "parser.tab.c"
    break;

  case 80: /* plus_minus_term: PLUS term  */
#line 1171 "parser.y"
                           { 
            (yyval.info)= new Info();
            (yyval.info)->type = (yyvsp[0].info)->type;
            (yyval.info)->val=addnode("plus_minus_term");(yyvsp[-1].val)=addnode(string("PLUS") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3206 "parser.tab.c"
    break;

  case 81: /* plus_minus_term: MINUS term  */
#line 1175 "parser.y"
                   {
            (yyval.info)= new Info();
            (yyval.info)->type = (yyvsp[0].info)->type;
            (yyval.info)->val=addnode("plus_minus_term");(yyvsp[-1].val)=addnode(string("MINUS") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3215 "parser.tab.c"
    break;

  case 82: /* plus_minus_term_sure: plus_minus_term  */
#line 1181 "parser.y"
                                     {(yyval.info)=new Info();(yyval.info)->type=(yyvsp[0].info)->type;(yyval.info)->val=(yyvsp[0].info)->val;}
#line 3221 "parser.tab.c"
    break;

  case 83: /* plus_minus_term_sure: plus_minus_term_sure plus_minus_term  */
#line 1182 "parser.y"
                                                 {
              (yyval.info)=new Info();(yyval.info)->type=(yyvsp[-1].info)->type;(yyval.info)->val=addnode("plus_minus_term_sure");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3228 "parser.tab.c"
    break;

  case 84: /* term: factor operator_factor_sure  */
#line 1186 "parser.y"
                                  {
            if((yyvsp[-1].info)->type !=(yyvsp[0].info)->type) yyerror1("5 there is type mismatch",yylineno);
            (yyval.info)=new Info();(yyval.info)->type=(yyvsp[-1].info)->type;(yyval.info)->val=addnode("term");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3236 "parser.tab.c"
    break;

  case 85: /* term: factor  */
#line 1189 "parser.y"
            {
            (yyval.info)=new Info();(yyval.info)->name=(yyvsp[0].info)->name;(yyval.info)->type=(yyvsp[0].info)->type;(yyval.info)->val=(yyvsp[0].info)->val;}
#line 3243 "parser.tab.c"
    break;

  case 86: /* operator_factor: MULTI factor  */
#line 1193 "parser.y"
                             {
        (yyval.info)= new Info();
        (yyval.info)->type= (yyvsp[0].info)->type;
        (yyval.info)->val=addnode("operator_factor");(yyvsp[-1].val)=addnode(string("PLUS") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3252 "parser.tab.c"
    break;

  case 87: /* operator_factor: DIVI factor  */
#line 1197 "parser.y"
                 {
        (yyval.info)= new Info();
        (yyval.info)->type= (yyvsp[0].info)->type;
        (yyval.info)->val=addnode("operator_factor");(yyvsp[-1].val)=addnode(string("DIVI") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3261 "parser.tab.c"
    break;

  case 88: /* operator_factor: MOD factor  */
#line 1201 "parser.y"
                { 
        (yyval.info)= new Info();
        (yyval.info)->type= (yyvsp[0].info)->type;
        (yyval.info)->val=addnode("operator_factor");(yyvsp[-1].val)=addnode(string("MOD") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3270 "parser.tab.c"
    break;

  case 89: /* operator_factor: DOUBLE_SLASH factor  */
#line 1205 "parser.y"
                         { 
        (yyval.info)= new Info();
        (yyval.info)->type= (yyvsp[0].info)->type;
        (yyval.info)->val=addnode("operator_factor");(yyvsp[-1].val)=addnode(string("DOUBLE_SLASH") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3279 "parser.tab.c"
    break;

  case 90: /* operator_factor_sure: operator_factor  */
#line 1211 "parser.y"
                                      { 
            (yyval.info)=new Info(); (yyval.info)->type= (yyvsp[0].info)->type;(yyval.info)->val=(yyvsp[0].info)->val;}
#line 3286 "parser.tab.c"
    break;

  case 91: /* operator_factor_sure: operator_factor_sure operator_factor  */
#line 1213 "parser.y"
                                                { 
            (yyval.info)=new Info(); (yyval.info)->type= (yyvsp[-1].info)->type;
            if((yyvsp[-1].info)->type!=(yyvsp[0].info)->type) yyerror1("19 there is type mismatch",yylineno);
            (yyval.info)->val=addnode("operator_factor_sure");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3295 "parser.tab.c"
    break;

  case 92: /* factor: PLUS factor  */
#line 1219 "parser.y"
                   {
             (yyval.info)=new Info();(yyval.info)->type=(yyvsp[0].info)->type;(yyval.info)->val=addnode("factor");(yyvsp[-1].val)=addnode(string("PLUS") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3302 "parser.tab.c"
    break;

  case 93: /* factor: MINUS factor  */
#line 1221 "parser.y"
                    {
            (yyval.info)=new Info();(yyval.info)->type=(yyvsp[0].info)->type;(yyval.info)->val=addnode("factor");(yyvsp[-1].val)=addnode(string("MINUS") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3309 "parser.tab.c"
    break;

  case 94: /* factor: NOSYMBOL factor  */
#line 1223 "parser.y"
                       {
            (yyval.info)=new Info();(yyval.info)->type=(yyvsp[0].info)->type;(yyval.info)->val=addnode("factor");(yyvsp[-1].val)=addnode(string("NOSYMBOL") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3316 "parser.tab.c"
    break;

  case 95: /* factor: power  */
#line 1225 "parser.y"
             { 
            (yyval.info)=new Info();(yyval.info)->name=(yyvsp[0].info)->name;(yyval.info)->type=(yyvsp[0].info)->type;(yyval.info)->val=(yyvsp[0].info)->val;}
#line 3323 "parser.tab.c"
    break;

  case 96: /* power: atom_expr DOUBLE_STAR factor  */
#line 1229 "parser.y"
                                    {
            (yyval.info)=new Info();(yyval.info)->type=(yyvsp[-2].info)->type;(yyval.info)->val=addnode("power");addedge((yyval.info)->val, (yyvsp[-2].info)->val);(yyvsp[-1].val)=addnode(string("DOUBLE_STAR"));addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3330 "parser.tab.c"
    break;

  case 97: /* power: atom_expr  */
#line 1231 "parser.y"
                 {
            (yyval.info)=new Info();(yyval.info)->name=(yyvsp[0].info)->name;(yyval.info)->type=(yyvsp[0].info)->type;(yyval.info)->val=(yyvsp[0].info)->val;}
#line 3337 "parser.tab.c"
    break;

  case 98: /* atom_expr: atom trailer_sure  */
#line 1235 "parser.y"
                             {
                (yyval.info)=new Info();(yyval.info)->type=(yyvsp[-1].info)->type;
                (yyval.info)->name=(yyvsp[0].info)->name;
                if((yyvsp[-1].info)->isfunc==true && (yyvsp[-1].info)->name!="print" && (yyvsp[-1].info)->name!="input" && (yyvsp[-1].info)->name!="len"){
                  if((yyvsp[-1].info)->parameters_vec.size()!=(yyvsp[0].info)->parameters_vec.size())
                      yyerror1("number of parameters in function does not match",yylineno);
                  int k=(yyvsp[-1].info)->parameters_vec.size();
                  for(int i=0;i<k;i++){
                    if((yyvsp[-1].info)->parameters_vec[i]->type != (yyvsp[0].info)->parameters_vec[i]->name)
                       yyerror1("6 there is type mismatch",yylineno);
                  }
                }

               
                (yyval.info)->val=addnode("atom_expr");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3357 "parser.tab.c"
    break;

  case 99: /* atom_expr: atom  */
#line 1250 "parser.y"
                { 
                 (yyval.info)=new Info();(yyval.info)->name=(yyvsp[0].info)->name;(yyval.info)->type=(yyvsp[0].info)->type;(yyval.info)->val=(yyvsp[0].info)->val;}
#line 3364 "parser.tab.c"
    break;

  case 100: /* trailer_sure: trailer  */
#line 1254 "parser.y"
                      {
                (yyval.info)=new Info();
                (yyval.info)->c =(yyvsp[0].info)->c;
                if((yyvsp[0].info)->c!=5000)
                (yyval.info)->parameters_vec=(yyvsp[0].info)->parameters_vec;
                (yyval.info)->type=(yyvsp[0].info)->type;
                (yyval.info)->name=(yyvsp[0].info)->name;
                (yyval.info)->val=(yyvsp[0].info)->val;
                }
#line 3378 "parser.tab.c"
    break;

  case 101: /* trailer_sure: trailer_sure trailer  */
#line 1263 "parser.y"
                                  {
                (yyval.info)=new Info();
                (yyval.info)->c =(yyvsp[-1].info)->c;
                if((yyvsp[-1].info)->c!=5000) (yyval.info)->parameters_vec=(yyvsp[-1].info)->parameters_vec;
                (yyval.info)->type=(yyvsp[-1].info)->type;
                (yyval.info)->name=(yyvsp[-1].info)->name;
                (yyval.info)->val=(yyvsp[-1].info)->val;


            }
#line 3393 "parser.tab.c"
    break;

  case 102: /* atom: CIROPEN testlist_comp CIRCLOSE  */
#line 1274 "parser.y"
                                     { 
         (yyval.info)=new Info(); (yyval.info)->type=(yyvsp[-1].info)->type;
         (yyval.info)->val=addnode("atom");(yyvsp[-2].val)=addnode(string("CIROPEN") );addedge((yyval.info)->val, (yyvsp[-2].val));addedge((yyval.info)->val, (yyvsp[-1].info)->val);(yyvsp[0].val)=addnode(string("CIRCLOSE") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3401 "parser.tab.c"
    break;

  case 103: /* atom: CIROPEN CIRCLOSE  */
#line 1277 "parser.y"
                       { 
         (yyval.info)=new Info(); (yyval.info)->c=0;
         (yyval.info)->val=addnode("atom");(yyvsp[-1].val)=addnode(string("CIROPEN") );addedge((yyval.info)->val, (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("CIRCLOSE"));addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3409 "parser.tab.c"
    break;

  case 104: /* atom: SQOPEN testlist_comp SQCLOSE  */
#line 1280 "parser.y"
                                   { 
        int k=GlobalSymbolTable->curr_sym_tbl->nor_sym_vec.size();
        GlobalSymbolTable->curr_sym_tbl->nor_sym_vec[k-1]->isarray=true;
        (yyval.info) = new Info(); (yyval.info)->type= (yyvsp[-1].info)->type;
        GlobalSymbolTable->curr_sym_tbl->nor_sym_vec[k-1]->size=type_size_map[(yyvsp[-1].info)->type]*((yyvsp[-1].info)->c);
        (yyval.info)->val=addnode("atom");(yyvsp[-2].val)=addnode(string("SQOPEN") );addedge((yyval.info)->val, (yyvsp[-2].val));addedge((yyval.info)->val, (yyvsp[-1].info)->val);(yyvsp[0].val)=addnode(string("SQCLOSE") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3420 "parser.tab.c"
    break;

  case 105: /* atom: SQOPEN SQCLOSE  */
#line 1286 "parser.y"
                     { 
        int k=GlobalSymbolTable->curr_sym_tbl->nor_sym_vec.size();
        GlobalSymbolTable->curr_sym_tbl->nor_sym_vec[k-1]->isarray=true;
        (yyval.info) = new Info();
        GlobalSymbolTable->curr_sym_tbl->nor_sym_vec[k-1]->size=0;
        (yyval.info)->val=addnode("atom");(yyvsp[-1].val)=addnode(string("SQOPEN") );addedge((yyval.info)->val, (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("SQCLOSE"));addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3431 "parser.tab.c"
    break;

  case 106: /* atom: CUOPEN CUCLOSE  */
#line 1292 "parser.y"
                     { 
        (yyval.info)->val=addnode("atom");(yyvsp[-1].val)=addnode(string("CUOPEN") );addedge((yyval.info)->val, (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("CUCLOSE"));addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3438 "parser.tab.c"
    break;

  case 107: /* atom: INT  */
#line 1294 "parser.y"
          { 
           (yyval.info)=new Info();
           (yyval.info)->type="int";
           (yyval.info)->name=(yyvsp[0].val);
           (yyval.info)->val=addnode("atom");(yyvsp[0].val)=addnode(string("INT") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3448 "parser.tab.c"
    break;

  case 108: /* atom: LISTINT  */
#line 1299 "parser.y"
              { 
           (yyval.info)=new Info();
           (yyval.info)->type="int";
           (yyval.info)->name=(yyvsp[0].val);
           (yyval.info)->val=addnode("atom");(yyvsp[0].val)=addnode(string("LISTINT") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3458 "parser.tab.c"
    break;

  case 109: /* atom: LISTFLOAT  */
#line 1304 "parser.y"
                { 
           (yyval.info)=new Info();
           (yyval.info)->type="float";
           (yyval.info)->name=(yyvsp[0].val);
           (yyval.info)->val=addnode("atom");(yyvsp[0].val)=addnode(string("LISTFLOAT") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3468 "parser.tab.c"
    break;

  case 110: /* atom: LISTSTRING  */
#line 1309 "parser.y"
                 { 
           (yyval.info)=new Info();
           (yyval.info)->type="string";
           (yyval.info)->name=(yyvsp[0].val);
           (yyval.info)->val=addnode("atom");(yyvsp[0].val)=addnode(string("LISTSTRING") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3478 "parser.tab.c"
    break;

  case 111: /* atom: LISTBOOL  */
#line 1314 "parser.y"
               {
           (yyval.info)=new Info();
           (yyval.info)->type="bool";
           (yyval.info)->name=(yyvsp[0].val);
           (yyval.info)->val=addnode("atom");(yyvsp[0].val)=addnode(string("LISTBOOL") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3488 "parser.tab.c"
    break;

  case 112: /* atom: LIST  */
#line 1319 "parser.y"
           { 
           (yyval.info)=new Info();
           (yyval.info)->type="list";
           (yyval.info)->name=(yyvsp[0].val);
           (yyval.info)->val=addnode("atom");(yyvsp[0].val)=addnode(string("LIST") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3498 "parser.tab.c"
    break;

  case 113: /* atom: FLOAT  */
#line 1324 "parser.y"
            {
            (yyval.info)=new Info();
            (yyval.info)->type="float";
            (yyval.info)->name=(yyvsp[0].val);
            (yyval.info)->val=addnode("atom");(yyvsp[0].val)=addnode(string("FLOAT") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3508 "parser.tab.c"
    break;

  case 114: /* atom: STR  */
#line 1329 "parser.y"
          {
            (yyval.info)=new Info();
            (yyval.info)->type="string";
            (yyval.info)->name=(yyvsp[0].val);
           (yyval.info)->val=addnode("atom");(yyvsp[0].val)=addnode(string("STR") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3518 "parser.tab.c"
    break;

  case 115: /* atom: BOOL  */
#line 1334 "parser.y"
           {
            (yyval.info)=new Info();
             (yyval.info)->type="bool";
             (yyval.info)->name=(yyvsp[0].val);
            (yyval.info)->val=addnode("atom");(yyvsp[0].val)=addnode(string("BOOL") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3528 "parser.tab.c"
    break;

  case 116: /* atom: NUMBER  */
#line 1339 "parser.y"
             { 
              (yyval.info)=new Info();
              (yyval.info)->type="int";
              (yyval.info)->name=(yyvsp[0].val);
              (yyval.info)->val=addnode("atom");
              (yyvsp[0].val)=addnode(string("NUMBER") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3539 "parser.tab.c"
    break;

  case 117: /* atom: FLOAT_NUMBER  */
#line 1345 "parser.y"
                   {
               (yyval.info)=new Info();
               (yyval.info)->type="float";
               (yyval.info)->name=(yyvsp[0].val);
               (yyval.info)->val=addnode("atom");(yyvsp[0].val)=addnode(string("FLOAT_NUMBER") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3549 "parser.tab.c"
    break;

  case 118: /* atom: IMAGINARY_NUMBER  */
#line 1350 "parser.y"
                       {
              (yyval.info)=new Info();
               (yyval.info)->type="inumber";
               (yyval.info)->name=(yyvsp[0].val);
               (yyval.info)->val=addnode("atom");(yyvsp[0].val)=addnode(string("IMAGINARY_NUMBER") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3559 "parser.tab.c"
    break;

  case 119: /* atom: string_sure  */
#line 1355 "parser.y"
                  {
                   (yyval.info)=new Info();
                   (yyval.info)->type="string";
                   (yyval.info)->val=(yyvsp[0].info)->val;}
#line 3568 "parser.tab.c"
    break;

  case 120: /* atom: THREE_DOT  */
#line 1359 "parser.y"
                {
         (yyval.info)->val=addnode("atom");(yyvsp[0].val)=addnode(string("THREE_DOT") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3575 "parser.tab.c"
    break;

  case 121: /* atom: NONE  */
#line 1361 "parser.y"
           {(yyval.info)=new Info();
               (yyval.info)->type="none";
               (yyval.info)->name=(yyvsp[0].val);
      (yyval.info)->val=addnode("atom");(yyvsp[0].val)=addnode(string("NONE") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3584 "parser.tab.c"
    break;

  case 122: /* atom: TRUE  */
#line 1365 "parser.y"
           {
            (yyval.info)=new Info();
            (yyval.info)->type="bool";
            (yyval.info)->name=(yyvsp[0].val);
            (yyval.info)->val=addnode("atom");(yyvsp[0].val)=addnode(string("TRUE") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3594 "parser.tab.c"
    break;

  case 123: /* atom: FALSE  */
#line 1370 "parser.y"
            {
            (yyval.info)=new Info();
            (yyval.info)->type="bool";
            (yyval.info)->name=(yyvsp[0].val);
            (yyval.info)->val=addnode("atom");(yyvsp[0].val)=addnode(string("FALSE") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3604 "parser.tab.c"
    break;

  case 124: /* atom: IDENTIFIER  */
#line 1375 "parser.y"
                 {
        loc_sym_tbl*curr=GlobalSymbolTable->scope_table_map[GlobalSymbolTable->curr_sym_tbl->scope];


        (yyval.info) = new Info();
        nor_sym* temp1= GlobalSymbolTable->search_nor_sym( (yyvsp[0].val), GlobalSymbolTable->curr_scope);
        func* temp2 = GlobalSymbolTable->search_func( (yyvsp[0].val), GlobalSymbolTable->curr_scope);
        Class* temp3 = GlobalSymbolTable->search_class( (yyvsp[0].val), GlobalSymbolTable->curr_scope);
        func* temp4 = GlobalSymbolTable->search_pre_func( (yyvsp[0].val), GlobalSymbolTable->curr_scope);
        if(temp1!=NULL){
          (yyval.info)->name=(yyvsp[0].val);
          (yyval.info)->type=temp1->type;
        }
        else if(temp2!=NULL){
          if(temp2->ret_type.size()==0) (yyval.info)->type="none";
          else (yyval.info)->type=temp2->ret_type;
          (yyval.info)->name=(yyvsp[0].val);
          (yyval.info)->isfunc=true;
          (yyval.info)->parameters_vec=temp2->parameters_vec;
        }
        else if(temp3!=NULL){
          (yyval.info)->name=(yyvsp[0].val);
          (yyval.info)->type=temp3->name;
        }
        else if(temp4!=NULL){
          (yyval.info)->name=temp4->name;
          (yyval.info)->isfunc=true;
          if(temp4->ret_type.size()==0) (yyval.info)->type="none";
          else (yyval.info)->type=temp4->ret_type;
        }
        else{
          nor_sym* newsym= new nor_sym((yyvsp[0].val),yylineno);
          (yyval.info)->name=(yyvsp[0].val);
          newsym->name=(yyvsp[0].val);
          newsym->offset = GlobalSymbolTable->curr_sym_tbl->offset;
          GlobalSymbolTable->insert(newsym);
        }
        (yyval.info)->val=addnode("atom");(yyvsp[0].val)=addnode(string("IDENTIFIER") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3647 "parser.tab.c"
    break;

  case 125: /* testlist: test comma_test_sure COMMA  */
#line 1417 "parser.y"
                                     {
            (yyval.info) = new Info();
            (yyval.info)->type=(yyvsp[-2].info)->type;
            (yyval.info)->val=addnode("testlist");addedge((yyval.info)->val, (yyvsp[-2].info)->val);addedge((yyval.info)->val, (yyvsp[-1].info)->val);(yyvsp[0].val)=addnode(string("COMMA") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3656 "parser.tab.c"
    break;

  case 126: /* testlist: test comma_test_sure  */
#line 1421 "parser.y"
                               {
            (yyval.info) = new Info();
            (yyval.info)->type=(yyvsp[-1].info)->type;
            (yyval.info)->val=addnode("testlist");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3665 "parser.tab.c"
    break;

  case 127: /* testlist: test COMMA  */
#line 1425 "parser.y"
                     {
            (yyval.info)= new Info();
            (yyval.info)->type=(yyvsp[-1].info)->type;
            (yyval.info)->val=addnode("testlist");addedge((yyval.info)->val, (yyvsp[-1].info)->val);(yyvsp[0].val)=addnode(string("COMMA"));addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3674 "parser.tab.c"
    break;

  case 128: /* testlist: test  */
#line 1429 "parser.y"
               {
            (yyval.info)= new Info();
            (yyval.info)->type=(yyvsp[0].info)->type;
            (yyval.info)->val=(yyvsp[0].info)->val;}
#line 3683 "parser.tab.c"
    break;

  case 129: /* testlistreturn: test COMMA  */
#line 1435 "parser.y"
                          {
                  (yyval.info)= new Info();
                  (yyval.info)->type=(yyvsp[-1].info)->type;
                  (yyval.info)->val=addnode("testlistreturn");addedge((yyval.info)->val, (yyvsp[-1].info)->val);(yyvsp[0].val)=addnode(string("COMMA"));addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3692 "parser.tab.c"
    break;

  case 130: /* testlistreturn: test  */
#line 1439 "parser.y"
                     {
                  (yyval.info)= new Info();
                  (yyval.info)->type=(yyvsp[0].info)->type;
                  (yyval.info)->val=(yyvsp[0].info)->val;}
#line 3701 "parser.tab.c"
    break;

  case 131: /* comma_test: COMMA test  */
#line 1445 "parser.y"
                       {
        (yyval.info) = new Info();
        (yyval.info)->c=1;
        (yyval.info)->type=(yyvsp[0].info)->type;
        (yyval.info)->val=addnode("comma_test");(yyvsp[-1].val)=addnode(string("COMMA") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3711 "parser.tab.c"
    break;

  case 132: /* comma_test_sure: comma_test  */
#line 1452 "parser.y"
                            {
            (yyval.info) = new Info();
            (yyval.info)->c=1;
            (yyval.info)->val=(yyvsp[0].info)->val;}
#line 3720 "parser.tab.c"
    break;

  case 133: /* comma_test_sure: comma_test_sure comma_test  */
#line 1456 "parser.y"
                                    {
            (yyval.info) = new Info();
            (yyval.info)->c=(yyvsp[-1].info)->c+1;
            (yyval.info)->val=addnode("comma_test_sure");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3729 "parser.tab.c"
    break;

  case 134: /* testlist_comp: test comma_test_sure COMMA  */
#line 1462 "parser.y"
                                          {
                   (yyval.info)=new Info(); (yyval.info)->type=(yyvsp[-2].info)->type; (yyval.info)->c=(yyvsp[-1].info)->c+1;(yyval.info)->val=addnode("testlist_comp");addedge((yyval.info)->val, (yyvsp[-2].info)->val);addedge((yyval.info)->val, (yyvsp[-1].info)->val);(yyvsp[0].val)=addnode(string("COMMA") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3736 "parser.tab.c"
    break;

  case 135: /* testlist_comp: test COMMA  */
#line 1464 "parser.y"
                          {
                  (yyval.info)=new Info(); (yyval.info)->type=(yyvsp[-1].info)->type; (yyval.info)->c=1;(yyval.info)->val=addnode("testlist_comp");addedge((yyval.info)->val, (yyvsp[-1].info)->val);(yyvsp[0].val)=addnode(string("COMMA"));addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3743 "parser.tab.c"
    break;

  case 136: /* testlist_comp: test comma_test_sure  */
#line 1466 "parser.y"
                                    {
                  (yyval.info)=new Info(); (yyval.info)->type=(yyvsp[-1].info)->type; (yyval.info)->c=(yyvsp[0].info)->c+1;(yyval.info)->val=addnode("testlist_comp");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3750 "parser.tab.c"
    break;

  case 137: /* testlist_comp: test  */
#line 1468 "parser.y"
                    {
                  (yyval.info)=new Info(); (yyval.info)->type=(yyvsp[0].info)->type; (yyval.info)->c=1;(yyval.info)->val=(yyvsp[0].info)->val;}
#line 3757 "parser.tab.c"
    break;

  case 138: /* exprlist: expr comma_expr_sure COMMA  */
#line 1472 "parser.y"
                                     {(yyval.info)->val=addnode("exprlist");addedge((yyval.info)->val, (yyvsp[-2].info)->val);addedge((yyval.info)->val, (yyvsp[-1].info)->val);(yyvsp[0].val)=addnode(string("COMMA") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3763 "parser.tab.c"
    break;

  case 139: /* exprlist: expr COMMA  */
#line 1473 "parser.y"
                     {(yyval.info)->val=addnode("exprlist");addedge((yyval.info)->val, (yyvsp[-1].info)->val);(yyvsp[0].val)=addnode(string("COMMA"));addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3769 "parser.tab.c"
    break;

  case 140: /* exprlist: expr comma_expr_sure  */
#line 1474 "parser.y"
                               {(yyval.info)->val=addnode("exprlist");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3775 "parser.tab.c"
    break;

  case 141: /* exprlist: expr  */
#line 1475 "parser.y"
               {
            (yyval.info)->val=(yyvsp[0].info)->val;}
#line 3782 "parser.tab.c"
    break;

  case 142: /* comma_expr: COMMA expr  */
#line 1479 "parser.y"
                       {(yyval.info)->val=addnode("comma_expr");(yyvsp[-1].val)=addnode(string("COMMA") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3788 "parser.tab.c"
    break;

  case 143: /* comma_expr_sure: comma_expr  */
#line 1482 "parser.y"
                            {(yyval.info)->val=(yyvsp[0].info)->val;}
#line 3794 "parser.tab.c"
    break;

  case 144: /* comma_expr_sure: comma_expr_sure comma_expr  */
#line 1483 "parser.y"
                                       {(yyval.info)->val=addnode("comma_expr_sure");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3800 "parser.tab.c"
    break;

  case 145: /* string_sure: STRING  */
#line 1487 "parser.y"
                   {(yyval.info)->val=addnode("string_sure");(yyvsp[0].val)=addnode(string("STRING") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3806 "parser.tab.c"
    break;

  case 146: /* string_sure: STRING string_sure  */
#line 1488 "parser.y"
                               {(yyval.info)->val=addnode("string_sure");(yyvsp[-1].val)=addnode(string("STRING") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3812 "parser.tab.c"
    break;

  case 147: /* trailer: CIROPEN arglist CIRCLOSE  */
#line 1491 "parser.y"
                                   {
            (yyval.info)=new Info();
            (yyval.info)->parameters_vec=(yyvsp[-1].info)->parameters_vec;
            (yyval.info)->type=(yyvsp[-1].info)->type;
            (yyval.info)->val=addnode("trailer");(yyvsp[-2].val)=addnode(string("CIROPEN") );addedge((yyval.info)->val, (yyvsp[-2].val));addedge((yyval.info)->val, (yyvsp[-1].info)->val);(yyvsp[0].val)=addnode(string("CIRCLOSE") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3822 "parser.tab.c"
    break;

  case 148: /* trailer: CIROPEN CIRCLOSE  */
#line 1496 "parser.y"
                            {
            (yyval.info)=new Info();
            (yyval.info)->parameters_vec={};
            (yyval.info)->val=addnode("trailer");(yyvsp[-1].val)=addnode(string("CIROPEN") );addedge((yyval.info)->val, (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("CIRCLOSE"));addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3831 "parser.tab.c"
    break;

  case 149: /* trailer: SQOPEN subscriptlist SQCLOSE  */
#line 1500 "parser.y"
                                       {
              (yyval.info)=new Info(); (yyval.info)->c=5000;(yyval.info)->type=(yyvsp[-1].info)->type;
              (yyval.info)->val=addnode("trailer");(yyvsp[-2].val)=addnode(string("SQOPEN") );addedge((yyval.info)->val, (yyvsp[-2].val));addedge((yyval.info)->val, (yyvsp[-1].info)->val);(yyvsp[0].val)=addnode(string("SQCLOSE") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3839 "parser.tab.c"
    break;

  case 150: /* trailer: DOT IDENTIFIER  */
#line 1503 "parser.y"
                         { 
              (yyval.info)=new Info();
                nor_sym* temp1= GlobalSymbolTable->search_nor_sym( (yyvsp[-1].val), GlobalSymbolTable->curr_scope);
                func* temp2 = GlobalSymbolTable->search_func( (yyvsp[-1].val), GlobalSymbolTable->curr_scope);
                Class* temp3 = GlobalSymbolTable->search_class( (yyvsp[-1].val), GlobalSymbolTable->curr_scope);
                func* temp4 = GlobalSymbolTable->search_pre_func( (yyvsp[-1].val), GlobalSymbolTable->curr_scope);
                if(temp1!=NULL){
                (yyval.info)->name=(yyvsp[0].val);
                (yyval.info)->type=temp1->type;  
                (yyval.info)->parameters_vec.push_back(temp1);
  
                }
                else{
                nor_sym* newsym= new nor_sym((yyvsp[-1].val),yylineno);
                (yyval.info)->name=(yyvsp[0].val);
                newsym->name=(yyvsp[0].val);
                GlobalSymbolTable->insert(newsym);
                (yyval.info)->parameters_vec.push_back(newsym);

                }


              (yyval.info)->val=addnode("trailer");(yyvsp[-1].val)=addnode(string("DOT") );addedge((yyval.info)->val, (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("IDENTIFIER"));addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3867 "parser.tab.c"
    break;

  case 151: /* trailer: DOT DUNDER  */
#line 1526 "parser.y"
                     {
        (yyval.info)=new Info();(yyval.info)->name="dunder";
              (yyval.info)->val=addnode("trailer");(yyvsp[-1].val)=addnode(string("DOT") );addedge((yyval.info)->val, (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("DUNDER"));addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3875 "parser.tab.c"
    break;

  case 152: /* arglist: argument comma_argument_sure  */
#line 1531 "parser.y"
                                      {
            (yyval.info) = new Info();
            (yyval.info)->parameters_vec.push_back((yyvsp[-1].info)->parameters_vec[0]);
            for(int i=0;i<(yyvsp[0].info)->parameters_vec.size();i++) (yyval.info)->parameters_vec.push_back((yyvsp[0].info)->parameters_vec[i]);
            (yyval.info)->type=(yyvsp[-1].info)->type;
            (yyval.info)->val=addnode("arglist");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3886 "parser.tab.c"
    break;

  case 153: /* arglist: argument  */
#line 1537 "parser.y"
                  {
            (yyval.info) = new Info();
            (yyval.info)->parameters_vec=(yyvsp[0].info)->parameters_vec;
            (yyval.info)->type=(yyvsp[0].info)->type;
            (yyval.info)->val=(yyvsp[0].info)->val;}
#line 3896 "parser.tab.c"
    break;

  case 154: /* arglist: argument comma_argument_sure COMMA  */
#line 1542 "parser.y"
                                            {
            (yyval.info) = new Info();
            (yyval.info)->parameters_vec.push_back((yyvsp[-2].info)->parameters_vec[0]);
            for(int i=0;i<(yyvsp[-1].info)->parameters_vec.size();i++) (yyval.info)->parameters_vec.push_back((yyvsp[-1].info)->parameters_vec[i]);
            (yyval.info)->type=(yyvsp[-2].info)->type;
            (yyval.info)->val=addnode("arglist");addedge((yyval.info)->val, (yyvsp[-2].info)->val);addedge((yyval.info)->val, (yyvsp[-1].info)->val);(yyvsp[0].val)=addnode(string("COMMA") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3907 "parser.tab.c"
    break;

  case 155: /* arglist: argument COMMA  */
#line 1548 "parser.y"
                        {
            (yyval.info) = new Info();
            (yyval.info)->parameters_vec.push_back((yyvsp[-1].info)->parameters_vec[0]);
            (yyval.info)->type=(yyvsp[-1].info)->type;
            (yyval.info)->val=addnode("arglist");addedge((yyval.info)->val, (yyvsp[-1].info)->val);(yyvsp[0].val)=addnode(string("COMMA"));addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3917 "parser.tab.c"
    break;

  case 156: /* comma_argument: COMMA argument  */
#line 1555 "parser.y"
                              {
        (yyval.info) = new Info();
        (yyval.info)->parameters_vec.push_back((yyvsp[0].info)->parameters_vec[0]);
        (yyval.info)->type=(yyvsp[0].info)->type;
        (yyval.info)->val=addnode("comma_argument");(yyvsp[-1].val)=addnode(string("COMMA") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3927 "parser.tab.c"
    break;

  case 157: /* comma_argument_sure: comma_argument  */
#line 1562 "parser.y"
                                    {
            (yyval.info) = new Info();
            (yyval.info)->parameters_vec.push_back((yyvsp[0].info)->parameters_vec[0]);
            (yyval.info)->type=(yyvsp[0].info)->type;
            (yyval.info)->val=(yyvsp[0].info)->val;}
#line 3937 "parser.tab.c"
    break;

  case 158: /* comma_argument_sure: comma_argument_sure comma_argument  */
#line 1567 "parser.y"
                                            {
            (yyval.info) = new Info();
            for(int i=0;i<(yyvsp[-1].info)->parameters_vec.size();i++) (yyval.info)->parameters_vec.push_back((yyvsp[-1].info)->parameters_vec[i]);
            (yyval.info)->parameters_vec.push_back((yyvsp[0].info)->parameters_vec[0]);
            (yyval.info)->type=(yyvsp[-1].info)->type;
            (yyval.info)->val=addnode("comma_argument_sure");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3948 "parser.tab.c"
    break;

  case 159: /* argument: test  */
#line 1575 "parser.y"
               {
            (yyval.info) = new Info();
            nor_sym* temp= new nor_sym((yyvsp[0].info)->type,yylineno);
            (yyval.info)->parameters_vec.push_back(temp);
            (yyval.info)->type=(yyvsp[0].info)->type;
            (yyval.info)->val=(yyvsp[0].info)->val;}
#line 3959 "parser.tab.c"
    break;

  case 160: /* argument: test EQUAL test  */
#line 1581 "parser.y"
                          {
            if((yyvsp[-2].info)->type!=(yyvsp[0].info)->type) yyerror1("7 There is a type mismatch",yylineno);

            (yyval.info) = new Info();

            nor_sym* temp= new nor_sym((yyvsp[-2].info)->type,yylineno);
            (yyval.info)->parameters_vec.push_back(temp);
            (yyval.info)->type=(yyvsp[-2].info)->type;
            (yyval.info)->val=addnode("argument");addedge((yyval.info)->val, (yyvsp[-2].info)->val);(yyvsp[-1].val)=addnode(string("EQUAL"));addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3973 "parser.tab.c"
    break;

  case 161: /* subscriptlist: subscript comma_subscript_sure  */
#line 1592 "parser.y"
                                              {
                    (yyval.info)->val=addnode("subscriptlist");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 3980 "parser.tab.c"
    break;

  case 162: /* subscriptlist: subscript  */
#line 1594 "parser.y"
                         {
                (yyval.info)=new Info();(yyval.info)->type=(yyvsp[0].info)->type;
                    (yyval.info)->val=(yyvsp[0].info)->val;
                }
#line 3989 "parser.tab.c"
    break;

  case 163: /* subscriptlist: subscript comma_subscript_sure COMMA  */
#line 1598 "parser.y"
                                                    {
                   (yyval.info)->val=addnode("subscriptlist");addedge((yyval.info)->val, (yyvsp[-2].info)->val);addedge((yyval.info)->val, (yyvsp[-1].info)->val);(yyvsp[0].val)=addnode(string("COMMA") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 3996 "parser.tab.c"
    break;

  case 164: /* subscriptlist: subscript COMMA  */
#line 1600 "parser.y"
                               {
                   (yyval.info)->val=addnode("subscriptlist");addedge((yyval.info)->val, (yyvsp[-1].info)->val);(yyvsp[0].val)=addnode(string("COMMA"));addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4003 "parser.tab.c"
    break;

  case 165: /* comma_subscript: COMMA subscript  */
#line 1604 "parser.y"
                                 {(yyval.info)->val=addnode("comma_subscript");(yyvsp[-1].val)=addnode(string("COMMA") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4009 "parser.tab.c"
    break;

  case 166: /* comma_subscript_sure: comma_subscript  */
#line 1607 "parser.y"
                                      {(yyval.info)->val=(yyvsp[0].info)->val;}
#line 4015 "parser.tab.c"
    break;

  case 167: /* comma_subscript_sure: comma_subscript_sure comma_subscript  */
#line 1608 "parser.y"
                                                 {(yyval.info)->val=addnode("comma_subscript_sure");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4021 "parser.tab.c"
    break;

  case 168: /* subscript: test  */
#line 1611 "parser.y"
                { 
              if((yyvsp[0].info)->type!="int") yyerror1("array index is not an integer",yylineno);
              (yyval.info)=new Info();(yyval.info)->type=(yyvsp[0].info)->type;
              (yyval.info)->val=(yyvsp[0].info)->val;}
#line 4030 "parser.tab.c"
    break;

  case 169: /* subscript: test COLON test  */
#line 1615 "parser.y"
                            {
            if((yyvsp[-2].info)->type!=(yyvsp[0].info)->type) yyerror1(" 45 type mismatch in line ",yylineno);
            (yyval.info)=new Info();(yyval.info)->type=(yyvsp[-2].info)->type;
              (yyval.info)->val=addnode("subscript");addedge((yyval.info)->val, (yyvsp[-2].info)->val);(yyvsp[-1].val)=addnode(string("COLON"));addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4039 "parser.tab.c"
    break;

  case 170: /* subscript: test COLON  */
#line 1619 "parser.y"
                       {
            (yyval.info)=new Info();(yyval.info)->type=(yyvsp[-1].info)->type;
              (yyval.info)->val=addnode("subscript");addedge((yyval.info)->val, (yyvsp[-1].info)->val);(yyvsp[0].val)=addnode(string("COLON"));addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4047 "parser.tab.c"
    break;

  case 171: /* subscript: COLON test  */
#line 1622 "parser.y"
                      {
            (yyval.info)=new Info();(yyval.info)->type=(yyvsp[0].info)->type;
              (yyval.info)->val=addnode("subscript");(yyvsp[-1].val)=addnode(string("COLON") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4055 "parser.tab.c"
    break;

  case 172: /* subscript: COLON  */
#line 1625 "parser.y"
                 {
              (yyval.info)->val=addnode("subscript");(yyvsp[0].val)=addnode(string("COLON") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4062 "parser.tab.c"
    break;

  case 173: /* comp_op: LESS  */
#line 1630 "parser.y"
              {(yyval.info)->val=addnode("comp_op");(yyvsp[0].val)=addnode(string("LESS") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4068 "parser.tab.c"
    break;

  case 174: /* comp_op: GREATER  */
#line 1631 "parser.y"
                {(yyval.info)->val=addnode("comp_op");(yyvsp[0].val)=addnode(string("GREATER") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4074 "parser.tab.c"
    break;

  case 175: /* comp_op: DOUBLE_EQUAL  */
#line 1632 "parser.y"
                     {(yyval.info)->val=addnode("comp_op");(yyvsp[0].val)=addnode(string("DOUBLE_EQUAL") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4080 "parser.tab.c"
    break;

  case 176: /* comp_op: GREATER_EQUAL  */
#line 1633 "parser.y"
                      {(yyval.info)->val=addnode("comp_op");(yyvsp[0].val)=addnode(string("GREATER_EQUAL") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4086 "parser.tab.c"
    break;

  case 177: /* comp_op: LESS_EQUAL  */
#line 1634 "parser.y"
                   {(yyval.info)->val=addnode("comp_op");(yyvsp[0].val)=addnode(string("LESS_EQUAL") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4092 "parser.tab.c"
    break;

  case 178: /* comp_op: GREATER_LESS  */
#line 1635 "parser.y"
                     {(yyval.info)->val=addnode("comp_op");(yyvsp[0].val)=addnode(string("GREATER_LESS") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4098 "parser.tab.c"
    break;

  case 179: /* comp_op: NOT_EQUAL  */
#line 1636 "parser.y"
                  {(yyval.info)->val=addnode("comp_op");(yyvsp[0].val)=addnode(string("NOT_EQUAL") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4104 "parser.tab.c"
    break;

  case 180: /* comp_op: IN  */
#line 1637 "parser.y"
           {(yyval.info)->val=addnode("comp_op");(yyvsp[0].val)=addnode(string("IN") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4110 "parser.tab.c"
    break;

  case 181: /* comp_op: NOT IN  */
#line 1638 "parser.y"
               {(yyval.info)->val=addnode("comp_op");(yyvsp[-1].val)=addnode(string("NOT") );addedge((yyval.info)->val, (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("IN"));addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4116 "parser.tab.c"
    break;

  case 182: /* comp_op: IS  */
#line 1639 "parser.y"
           {(yyval.info)->val=addnode("comp_op");(yyvsp[0].val)=addnode(string("IS") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4122 "parser.tab.c"
    break;

  case 183: /* comp_op: IS NOT  */
#line 1640 "parser.y"
               {(yyval.info)->val=addnode("comp_op");(yyvsp[-1].val)=addnode(string("IS") );addedge((yyval.info)->val, (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("NOT"));addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4128 "parser.tab.c"
    break;

  case 184: /* annassign: COLON test  */
#line 1643 "parser.y"
                       { 
                (yyval.info)=new Info();(yyval.info)->type=(yyvsp[0].info)->type;
                (yyval.info)->c=1;
                (yyval.info)->val=addnode("annassign");(yyvsp[-1].val)=addnode(string("COLON") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4137 "parser.tab.c"
    break;

  case 185: /* annassign: COLON test EQUAL test  */
#line 1647 "parser.y"
                                  { 
                if((yyvsp[-2].info)->type=="none") yyerror1("variables are declared as void type",yylineno);
                (yyval.info)=new Info();(yyval.info)->c=(yyvsp[0].info)->c;
                if((yyvsp[-2].info)->type!=(yyvsp[0].info)->type) yyerror1("8 there is type mismatch",yylineno);
                (yyval.info)->type=(yyvsp[-2].info)->type; (yyval.info)->val=addnode("annassign");(yyvsp[-3].val)=addnode(string("COLON") );addedge((yyval.info)->val, (yyvsp[-3].val));addedge((yyval.info)->val, (yyvsp[-2].info)->val);(yyvsp[-1].val)=addnode(string("EQUAL") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4147 "parser.tab.c"
    break;

  case 186: /* augassign: PLUS_EQUAL  */
#line 1654 "parser.y"
                      {(yyval.info)->val=addnode("augassign");(yyvsp[0].val)=addnode(string("PLUS_EQUAL") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4153 "parser.tab.c"
    break;

  case 187: /* augassign: MINUS_EQUAL  */
#line 1655 "parser.y"
                       {(yyval.info)->val=addnode("augassign");(yyvsp[0].val)=addnode(string("MINUS_EQUAL") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4159 "parser.tab.c"
    break;

  case 188: /* augassign: MULTI_EQUAL  */
#line 1656 "parser.y"
                       {(yyval.info)->val=addnode("augassign");(yyvsp[0].val)=addnode(string("MULTI_EQUAL") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4165 "parser.tab.c"
    break;

  case 189: /* augassign: DIVI_EQUAL  */
#line 1657 "parser.y"
                      {(yyval.info)->val=addnode("augassign");(yyvsp[0].val)=addnode(string("DIVI_EQUAL") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4171 "parser.tab.c"
    break;

  case 190: /* augassign: MODULO_EQUAL  */
#line 1658 "parser.y"
                        {(yyval.info)->val=addnode("augassign");(yyvsp[0].val)=addnode(string("MODULO_EQUAL") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4177 "parser.tab.c"
    break;

  case 191: /* augassign: AND_EQUAL  */
#line 1659 "parser.y"
                     {(yyval.info)->val=addnode("augassign");(yyvsp[0].val)=addnode(string("AND_EQUAL") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4183 "parser.tab.c"
    break;

  case 192: /* augassign: PIPE_EQUAL  */
#line 1660 "parser.y"
                      {(yyval.info)->val=addnode("augassign");(yyvsp[0].val)=addnode(string("PIPE_EQUAL") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4189 "parser.tab.c"
    break;

  case 193: /* augassign: POWER_EQUAL  */
#line 1661 "parser.y"
                       {(yyval.info)->val=addnode("augassign");(yyvsp[0].val)=addnode(string("POWER_EQUAL") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4195 "parser.tab.c"
    break;

  case 194: /* augassign: DOUBLE_LESS_EQUAL  */
#line 1662 "parser.y"
                             {(yyval.info)->val=addnode("augassign");(yyvsp[0].val)=addnode(string("DOUBLE_LESS_EQUAL") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4201 "parser.tab.c"
    break;

  case 195: /* augassign: DOUBLE_GREATER_EQUAL  */
#line 1663 "parser.y"
                                {(yyval.info)->val=addnode("augassign");(yyvsp[0].val)=addnode(string("DOUBLE_GREATER_EQUAL") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4207 "parser.tab.c"
    break;

  case 196: /* augassign: DOUBLE_MULTI_EQUAL  */
#line 1664 "parser.y"
                              {(yyval.info)->val=addnode("augassign");(yyvsp[0].val)=addnode(string("DOUBLE_MULTI_EQUAL") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4213 "parser.tab.c"
    break;

  case 197: /* augassign: DOUBLE_DIVI_EQUAL  */
#line 1665 "parser.y"
                             {(yyval.info)->val=addnode("augassign");(yyvsp[0].val)=addnode(string("DOUBLE_DIVI_EQUAL") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4219 "parser.tab.c"
    break;

  case 198: /* flow_stmt: break_stmt  */
#line 1668 "parser.y"
                      {(yyval.info)->val=(yyvsp[0].info)->val;}
#line 4225 "parser.tab.c"
    break;

  case 199: /* flow_stmt: continue_stmt  */
#line 1669 "parser.y"
                          {(yyval.info)->val=(yyvsp[0].info)->val;}
#line 4231 "parser.tab.c"
    break;

  case 200: /* flow_stmt: return_stmt  */
#line 1670 "parser.y"
                        {(yyval.info)->val=(yyvsp[0].info)->val;}
#line 4237 "parser.tab.c"
    break;

  case 201: /* flow_stmt: raise_stmt  */
#line 1671 "parser.y"
                       {(yyval.info)->val=(yyvsp[0].info)->val;}
#line 4243 "parser.tab.c"
    break;

  case 202: /* break_stmt: BREAK  */
#line 1674 "parser.y"
                  {(yyval.info)->val=addnode("break_stmt");(yyvsp[0].val)=addnode(string("BREAK") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4249 "parser.tab.c"
    break;

  case 203: /* continue_stmt: CONTINUE  */
#line 1677 "parser.y"
                        {(yyval.info)->val=addnode("continue_stmt");(yyvsp[0].val)=addnode(string("CONTINUE") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4255 "parser.tab.c"
    break;

  case 204: /* return_stmt: RETURN  */
#line 1680 "parser.y"
                    {
                (yyval.info)->val=addnode("return_stmt");(yyvsp[0].val)=addnode(string("RETURN") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4262 "parser.tab.c"
    break;

  case 205: /* return_stmt: RETURN testlistreturn  */
#line 1682 "parser.y"
                                   {
                (yyval.info) = new Info();
                loc_sym_tbl*temp=GlobalSymbolTable->curr_sym_tbl->parent;
                int k=temp->func_vec.size();
                if((yyvsp[0].info)->type=="") temp->func_vec[k-1]->ret_type="none";
                else temp->func_vec[k-1]->ret_type=(yyvsp[0].info)->type;
                (yyval.info)->val=addnode("return_stmt");(yyvsp[-1].val)=addnode(string("RETURN") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4274 "parser.tab.c"
    break;

  case 206: /* raise_stmt: RAISE test FROM test  */
#line 1691 "parser.y"
                                 {(yyval.info)->val=addnode("raise_stmt");(yyvsp[-3].val)=addnode(string("RAISE") );addedge((yyval.info)->val, (yyvsp[-3].val));addedge((yyval.info)->val, (yyvsp[-2].info)->val);(yyvsp[-1].val)=addnode(string("FROM") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4280 "parser.tab.c"
    break;

  case 207: /* raise_stmt: RAISE test  */
#line 1692 "parser.y"
                        {(yyval.info)->val=addnode("raise_stmt");(yyvsp[-1].val)=addnode(string("RAISE") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4286 "parser.tab.c"
    break;

  case 208: /* raise_stmt: RAISE  */
#line 1693 "parser.y"
                    {(yyval.info)->val=addnode("raise_stmt");(yyvsp[0].val)=addnode(string("RAISE") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4292 "parser.tab.c"
    break;

  case 209: /* global_stmt: GLOBAL IDENTIFIER comma_identifier_sure  */
#line 1698 "parser.y"
                                                     {(yyval.info)->val=addnode("global_stmt");(yyvsp[-2].val)=addnode(string("GLOBAL") );addedge((yyval.info)->val, (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("IDENTIFIER"));addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4298 "parser.tab.c"
    break;

  case 210: /* global_stmt: GLOBAL IDENTIFIER  */
#line 1699 "parser.y"
                               {(yyval.info)->val=addnode("global_stmt");(yyvsp[-1].val)=addnode(string("GLOBAL") );addedge((yyval.info)->val, (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("IDENTIFIER"));addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4304 "parser.tab.c"
    break;

  case 211: /* comma_identifier: COMMA IDENTIFIER  */
#line 1702 "parser.y"
                                   {(yyval.info)->val=addnode("comma_identifier");(yyvsp[-1].val)=addnode(string("COMMA") );addedge((yyval.info)->val, (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("IDENTIFIER"));addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4310 "parser.tab.c"
    break;

  case 212: /* comma_identifier_sure: comma_identifier  */
#line 1705 "parser.y"
                                        {(yyval.info)->val=(yyvsp[0].info)->val;}
#line 4316 "parser.tab.c"
    break;

  case 213: /* comma_identifier_sure: comma_identifier_sure comma_identifier  */
#line 1706 "parser.y"
                                                {(yyval.info)->val=addnode("comma_identifier_sure");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4322 "parser.tab.c"
    break;

  case 214: /* assert_stmt: ASSERT test  */
#line 1709 "parser.y"
                         {(yyval.info)->val=addnode("assert_stmt");(yyvsp[-1].val)=addnode(string("ASSERT") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4328 "parser.tab.c"
    break;

  case 215: /* assert_stmt: ASSERT test COMMA test  */
#line 1710 "parser.y"
                                    {(yyval.info)->val=addnode("assert_stmt");(yyvsp[-3].val)=addnode(string("ASSERT") );addedge((yyval.info)->val, (yyvsp[-3].val));addedge((yyval.info)->val, (yyvsp[-2].info)->val);(yyvsp[-1].val)=addnode(string("COMMA") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4334 "parser.tab.c"
    break;

  case 216: /* compound_stmt: if_stmt  */
#line 1713 "parser.y"
                       {(yyval.info)->val=(yyvsp[0].info)->val;}
#line 4340 "parser.tab.c"
    break;

  case 217: /* compound_stmt: while_stmt  */
#line 1714 "parser.y"
                          {(yyval.info)->val=(yyvsp[0].info)->val;}
#line 4346 "parser.tab.c"
    break;

  case 218: /* compound_stmt: for_stmt  */
#line 1715 "parser.y"
                        {(yyval.info)->val=(yyvsp[0].info)->val;}
#line 4352 "parser.tab.c"
    break;

  case 219: /* compound_stmt: funcdef  */
#line 1716 "parser.y"
                       {(yyval.info)->val=(yyvsp[0].info)->val;}
#line 4358 "parser.tab.c"
    break;

  case 220: /* compound_stmt: classdef  */
#line 1717 "parser.y"
                        {(yyval.info)->val=(yyvsp[0].info)->val;}
#line 4364 "parser.tab.c"
    break;

  case 221: /* compound_stmt: dunder_block  */
#line 1718 "parser.y"
                            {(yyval.info)->val=(yyvsp[0].info)->val;}
#line 4370 "parser.tab.c"
    break;

  case 222: /* if_stmt: IF test COLON suite else_if_sure ELSE COLON suite  */
#line 1721 "parser.y"
                                                            {
            (yyval.info)->val=addnode("if_stmt");(yyvsp[-7].val)=addnode(string("IF") );addedge((yyval.info)->val, (yyvsp[-7].val));addedge((yyval.info)->val, (yyvsp[-6].info)->val);(yyvsp[-5].val)=addnode(string("COLON") );addedge((yyval.info)->val, (yyvsp[-5].val));addedge((yyval.info)->val, (yyvsp[-4].info)->val);addedge((yyval.info)->val, (yyvsp[-3].info)->val);(yyvsp[-2].val)=addnode(string("ELSE") );addedge((yyval.info)->val, (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("COLON") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4377 "parser.tab.c"
    break;

  case 223: /* if_stmt: IF test COLON suite ELSE COLON suite  */
#line 1723 "parser.y"
                                               {
            (yyval.info)->val=addnode("if_stmt");(yyvsp[-6].val)=addnode(string("IF") );addedge((yyval.info)->val, (yyvsp[-6].val));addedge((yyval.info)->val, (yyvsp[-5].info)->val);(yyvsp[-4].val)=addnode(string("COLON") );addedge((yyval.info)->val, (yyvsp[-4].val));addedge((yyval.info)->val, (yyvsp[-3].info)->val);(yyvsp[-2].val)=addnode(string("ELSE") );addedge((yyval.info)->val, (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("COLON") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4384 "parser.tab.c"
    break;

  case 224: /* if_stmt: IF test COLON suite else_if_sure  */
#line 1725 "parser.y"
                                           {
            (yyval.info)->val=addnode("if_stmt");(yyvsp[-4].val)=addnode(string("IF") );addedge((yyval.info)->val, (yyvsp[-4].val));addedge((yyval.info)->val, (yyvsp[-3].info)->val);(yyvsp[-2].val)=addnode(string("COLON") );addedge((yyval.info)->val, (yyvsp[-2].val));addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4391 "parser.tab.c"
    break;

  case 225: /* if_stmt: IF test COLON suite  */
#line 1727 "parser.y"
                              {
            (yyval.info)->val=addnode("if_stmt");(yyvsp[-3].val)=addnode(string("IF") );addedge((yyval.info)->val, (yyvsp[-3].val));addedge((yyval.info)->val, (yyvsp[-2].info)->val);(yyvsp[-1].val)=addnode(string("COLON") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4398 "parser.tab.c"
    break;

  case 226: /* else_if: ELIF test COLON suite  */
#line 1731 "parser.y"
                              {(yyval.info)->val=addnode("else_if");(yyvsp[-3].val)=addnode(string("ELIF") );addedge((yyval.info)->val, (yyvsp[-3].val));addedge((yyval.info)->val, (yyvsp[-2].info)->val);(yyvsp[-1].val)=addnode(string("COLON") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4404 "parser.tab.c"
    break;

  case 227: /* else_if_sure: else_if  */
#line 1734 "parser.y"
                      {(yyval.info)->val=(yyvsp[0].info)->val;}
#line 4410 "parser.tab.c"
    break;

  case 228: /* else_if_sure: else_if_sure else_if  */
#line 1735 "parser.y"
                               {(yyval.info)->val=addnode("else_if_sure");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4416 "parser.tab.c"
    break;

  case 229: /* suite: simple_stmt  */
#line 1738 "parser.y"
                   {(yyval.info)->val=(yyvsp[0].info)->val; }
#line 4422 "parser.tab.c"
    break;

  case 230: /* suite: line_sure INDENT line_or_newstmt_sure DEDENT  */
#line 1739 "parser.y"
                                                    {
          (yyval.info)->val=addnode("suite");addedge((yyval.info)->val, (yyvsp[-3].info)->val);(yyvsp[-2].val)=addnode(string("INDENT"));addedge((yyval.info)->val, (yyvsp[-2].val));addedge((yyval.info)->val, (yyvsp[-1].info)->val);(yyvsp[0].val)=addnode(string("DEDENT") );addedge((yyval.info)->val, (yyvsp[0].val)); }
#line 4429 "parser.tab.c"
    break;

  case 231: /* line_or_newstmt: NEWLINE  */
#line 1743 "parser.y"
                         {(yyval.info)->val=addnode("line_or_newstmt");(yyvsp[0].val)=addnode(string("NEWLINE") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4435 "parser.tab.c"
    break;

  case 232: /* line_or_newstmt: new_stmt  */
#line 1744 "parser.y"
              {(yyval.info)->val=(yyvsp[0].info)->val;}
#line 4441 "parser.tab.c"
    break;

  case 233: /* line_or_newstmt_sure: line_or_newstmt  */
#line 1747 "parser.y"
                                      {(yyval.info)->val=(yyvsp[0].info)->val;}
#line 4447 "parser.tab.c"
    break;

  case 234: /* line_or_newstmt_sure: line_or_newstmt_sure line_or_newstmt  */
#line 1748 "parser.y"
                                               {(yyval.info)->val=addnode("line_or_newstmt_sure");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4453 "parser.tab.c"
    break;

  case 235: /* new_stmt: simple_stmt  */
#line 1751 "parser.y"
                       {(yyval.info)->val=(yyvsp[0].info)->val;}
#line 4459 "parser.tab.c"
    break;

  case 236: /* new_stmt: if_stmt  */
#line 1752 "parser.y"
                   {(yyval.info)->val=(yyvsp[0].info)->val;}
#line 4465 "parser.tab.c"
    break;

  case 237: /* new_stmt: while_stmt  */
#line 1753 "parser.y"
                      {(yyval.info)->val=(yyvsp[0].info)->val;}
#line 4471 "parser.tab.c"
    break;

  case 238: /* new_stmt: for_stmt  */
#line 1754 "parser.y"
                    {(yyval.info)->val=(yyvsp[0].info)->val;}
#line 4477 "parser.tab.c"
    break;

  case 239: /* new_stmt: funcdef  */
#line 1755 "parser.y"
                   {(yyval.info)->val=(yyvsp[0].info)->val;}
#line 4483 "parser.tab.c"
    break;

  case 240: /* new_stmt: dunder_block  */
#line 1756 "parser.y"
                        {(yyval.info)->val=(yyvsp[0].info)->val;}
#line 4489 "parser.tab.c"
    break;

  case 241: /* while_stmt: WHILE test COLON suite  */
#line 1759 "parser.y"
                                     {(yyval.info)->val=addnode("while_stmt");(yyvsp[-3].val)=addnode(string("WHILE") );addedge((yyval.info)->val, (yyvsp[-3].val));addedge((yyval.info)->val, (yyvsp[-2].info)->val);(yyvsp[-1].val)=addnode(string("COLON") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4495 "parser.tab.c"
    break;

  case 242: /* while_stmt: WHILE test COLON suite ELSE COLON suite  */
#line 1760 "parser.y"
                                                      {(yyval.info)->val=addnode("while_stmt");(yyvsp[-6].val)=addnode(string("WHILE") );addedge((yyval.info)->val, (yyvsp[-6].val));addedge((yyval.info)->val, (yyvsp[-5].info)->val);(yyvsp[-4].val)=addnode(string("COLON") );addedge((yyval.info)->val, (yyvsp[-4].val));addedge((yyval.info)->val, (yyvsp[-3].info)->val);(yyvsp[-2].val)=addnode(string("ELSE") );addedge((yyval.info)->val, (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("COLON") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4501 "parser.tab.c"
    break;

  case 243: /* for_stmt: FOR exprlist IN testlist COLON suite  */
#line 1764 "parser.y"
                                                { 
            (yyval.info)->val=addnode("for_stmt");(yyvsp[-5].val)=addnode(string("FOR") );addedge((yyval.info)->val, (yyvsp[-5].val));addedge((yyval.info)->val, (yyvsp[-4].info)->val);(yyvsp[-3].val)=addnode(string("IN") );addedge((yyval.info)->val, (yyvsp[-3].val));addedge((yyval.info)->val, (yyvsp[-2].info)->val);(yyvsp[-1].val)=addnode(string("COLON") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4508 "parser.tab.c"
    break;

  case 244: /* for_stmt: FOR exprlist IN testlist COLON suite ELSE COLON suite  */
#line 1766 "parser.y"
                                                                  {(yyval.info)->val=addnode("for_stmt");(yyvsp[-8].val)=addnode(string("FOR") );addedge((yyval.info)->val, (yyvsp[-8].val));addedge((yyval.info)->val, (yyvsp[-7].info)->val);(yyvsp[-6].val)=addnode(string("IN") );addedge((yyval.info)->val, (yyvsp[-6].val));addedge((yyval.info)->val, (yyvsp[-5].info)->val);(yyvsp[-4].val)=addnode(string("COLON") );addedge((yyval.info)->val, (yyvsp[-4].val));addedge((yyval.info)->val, (yyvsp[-3].info)->val);(yyvsp[-2].val)=addnode(string("ELSE") );addedge((yyval.info)->val, (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("COLON") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4514 "parser.tab.c"
    break;

  case 245: /* $@1: %empty  */
#line 1770 "parser.y"
                        {
              func* newfunc = new func((yyvsp[0].val),yylineno);
              newfunc->offset = GlobalSymbolTable->curr_sym_tbl->offset;
              GlobalSymbolTable->curr_sym_tbl->offset+=4;
              GlobalSymbolTable->insert(newfunc);
              GlobalSymbolTable->make_table(GlobalSymbolTable->curr_scope +"T_"+ (yyvsp[0].val));
              GlobalSymbolTable->curr_sym_tbl->functbl=true;
              threeacir->insert_two_word_instr("function begin", (yyvsp[0].val));}
#line 4527 "parser.tab.c"
    break;

  case 246: /* funcdef: DEF IDENTIFIER $@1 parameters func_end  */
#line 1778 "parser.y"
                          {
             int k= GlobalSymbolTable->curr_sym_tbl->func_vec.size();

             GlobalSymbolTable->curr_sym_tbl->func_vec[k-1]->parameters_vec=(yyvsp[-1].info)->parameters_vec;
             string funcname=GlobalSymbolTable->curr_sym_tbl->func_vec[k-1]->name;
              vector<pair<string,int>>arglist;
              for(int i=0;i<(yyvsp[-1].info)->parameters_vec.size();i++){
                arglist.push_back({(yyvsp[-1].info)->parameters_vec[i]->name , (yyvsp[-1].info)->parameters_vec[i]->size});
              }
              reverse(arglist.begin(),arglist.end());
              threeacir->insert_function_call(funcname, arglist, false, "", true);
              threeacir->insert_two_word_instr("function end", funcname);
              
              (yyval.info)->val=addnode("funcdef");(yyvsp[-4].val)=addnode(string("DEF") );addedge((yyval.info)->val, (yyvsp[-4].val));(yyvsp[-3].val)=addnode(string("IDENTIFIER"));addedge((yyval.info)->val, (yyvsp[-3].val));addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4546 "parser.tab.c"
    break;

  case 247: /* $@2: %empty  */
#line 1793 "parser.y"
                    {
              func* newfunc = new func((yyvsp[0].val),yylineno);
              newfunc->offset = GlobalSymbolTable->curr_sym_tbl->offset;
              GlobalSymbolTable->curr_sym_tbl->offset+=4;
              GlobalSymbolTable->insert(newfunc);
              GlobalSymbolTable->make_table(GlobalSymbolTable->curr_scope +"T_"+ (yyvsp[0].val));
              GlobalSymbolTable->curr_sym_tbl->functbl=true;}
#line 4558 "parser.tab.c"
    break;

  case 248: /* funcdef: DEF DUNDER $@2 parameters COLON suite  */
#line 1800 "parser.y"
                              {
             GlobalSymbolTable->outofcurrst();
             int k= GlobalSymbolTable->curr_sym_tbl->func_vec.size();
             GlobalSymbolTable->curr_sym_tbl->func_vec[k-1]->ret_type="None";
             GlobalSymbolTable->curr_sym_tbl->func_vec[k-1]->parameters_vec=(yyvsp[-2].info)->parameters_vec;
            
             (yyval.info)->val=addnode("funcdef");(yyvsp[-5].val)=addnode(string("DEF") );addedge((yyval.info)->val, (yyvsp[-5].val));(yyvsp[-4].val)=addnode(string("IDENTIFIER"));addedge((yyval.info)->val, (yyvsp[-4].val));addedge((yyval.info)->val, (yyvsp[-2].info)->val);(yyvsp[-1].val)=addnode(string("COLON") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4570 "parser.tab.c"
    break;

  case 249: /* $@3: %empty  */
#line 1809 "parser.y"
                           {
       
             int k= GlobalSymbolTable->curr_sym_tbl->parent->func_vec.size();
             GlobalSymbolTable->curr_sym_tbl->parent->func_vec[k-1]->ret_type=(yyvsp[-1].info)->type;}
#line 4579 "parser.tab.c"
    break;

  case 250: /* func_end: ARROW test COLON $@3 suite  */
#line 1813 "parser.y"
             {
             GlobalSymbolTable->outofcurrst();
             
             int k= GlobalSymbolTable->curr_sym_tbl->func_vec.size();
             string funcname=GlobalSymbolTable->curr_sym_tbl->func_vec[k-1]->name;

             (yyval.info)->val=addnode("func_end");(yyvsp[-4].val)=addnode(string("ARROW") );addedge((yyval.info)->val, (yyvsp[-4].val));addedge((yyval.info)->val, (yyvsp[-3].info)->val);(yyvsp[-2].val)=addnode(string("COLON") );addedge((yyval.info)->val, (yyvsp[-2].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);

        }
#line 4593 "parser.tab.c"
    break;

  case 251: /* $@4: %empty  */
#line 1822 "parser.y"
               {
             int k= GlobalSymbolTable->curr_sym_tbl->parent->func_vec.size();
             GlobalSymbolTable->curr_sym_tbl->parent->func_vec[k-1]->ret_type="none";}
#line 4601 "parser.tab.c"
    break;

  case 252: /* func_end: COLON $@4 suite  */
#line 1825 "parser.y"
             {
             GlobalSymbolTable->outofcurrst();
             
             int k= GlobalSymbolTable->curr_sym_tbl->func_vec.size();
             string funcname=GlobalSymbolTable->curr_sym_tbl->func_vec[k-1]->name;

             (yyval.info)->val=addnode("func_end");(yyvsp[-2].val)=addnode(string("COLON") );addedge((yyval.info)->val, (yyvsp[-2].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4613 "parser.tab.c"
    break;

  case 253: /* parameters: CIROPEN typedargslist CIRCLOSE  */
#line 1834 "parser.y"
                                             {
               (yyval.info) = new Info();
               for(int i=0;i<(yyvsp[-1].info)->parameters_vec.size();i++){
                   (yyval.info)->parameters_vec.push_back((yyvsp[-1].info)->parameters_vec[i]);
               } 
               (yyval.info)->val=addnode("parameters");(yyvsp[-2].val)=addnode(string("CIROPEN") );addedge((yyval.info)->val, (yyvsp[-2].val));addedge((yyval.info)->val, (yyvsp[-1].info)->val);(yyvsp[0].val)=addnode(string("CIRCLOSE"));addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4624 "parser.tab.c"
    break;

  case 254: /* parameters: CIROPEN CIRCLOSE  */
#line 1840 "parser.y"
                              {
               (yyval.info) = new Info();
               (yyval.info)->parameters_vec={};
               (yyval.info)->val=addnode("parameters");(yyvsp[-1].val)=addnode(string("CIROPEN") );addedge((yyval.info)->val, (yyvsp[-1].val));(yyvsp[0].val)=addnode(string("CIRCLOSE"));addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4633 "parser.tab.c"
    break;

  case 255: /* typedargslist: tfpdef EQUAL test comma_tfpdef_sure COMMA  */
#line 1846 "parser.y"
                                                        {
                (yyval.info) = new Info();
                if((yyvsp[-4].info)->parameters_vec[0]->type!=(yyvsp[-2].info)->type) yyerror1("9 there is a type mismatch",yylineno);
                if((yyvsp[-4].info)->parameters_vec.size()!=0) (yyval.info)->parameters_vec.push_back((yyvsp[-4].info)->parameters_vec[0]) ;
                for(int i=0;i<(yyvsp[-1].info)->parameters_vec.size();i++) (yyval.info)->parameters_vec.push_back((yyvsp[-1].info)->parameters_vec[i]);
                (yyval.info)->val=addnode("typedargslist");addedge((yyval.info)->val, (yyvsp[-4].info)->val);(yyvsp[-3].val)=addnode(string("EQUAL"));addedge((yyval.info)->val, (yyvsp[-3].val));addedge((yyval.info)->val, (yyvsp[-2].info)->val);addedge((yyval.info)->val, (yyvsp[-1].info)->val);(yyvsp[0].val)=addnode(string("COMMA") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4644 "parser.tab.c"
    break;

  case 256: /* typedargslist: tfpdef EQUAL test COMMA  */
#line 1852 "parser.y"
                                     {
                (yyval.info) = new Info();
                if((yyvsp[-3].info)->parameters_vec[0]->type!=(yyvsp[-1].info)->type) yyerror1("10 there is a type mismatch",yylineno);
                if((yyvsp[-3].info)->parameters_vec.size()!=0) (yyval.info)->parameters_vec.push_back((yyvsp[-3].info)->parameters_vec[0]);
                (yyval.info)->val=addnode("typedargslist");addedge((yyval.info)->val, (yyvsp[-3].info)->val);(yyvsp[-2].val)=addnode(string("EQUAL"));addedge((yyval.info)->val, (yyvsp[-2].val));addedge((yyval.info)->val, (yyvsp[-1].info)->val);(yyvsp[0].val)=addnode(string("COMMA") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4654 "parser.tab.c"
    break;

  case 257: /* typedargslist: tfpdef comma_tfpdef_sure COMMA  */
#line 1857 "parser.y"
                                            {
                (yyval.info) = new Info();
                if((yyvsp[-2].info)->parameters_vec.size()!=0) (yyval.info)->parameters_vec.push_back((yyvsp[-2].info)->parameters_vec[0]);
                for(int i=0;i<(yyvsp[-1].info)->parameters_vec.size();i++) (yyval.info)->parameters_vec.push_back((yyvsp[-1].info)->parameters_vec[i]);
                (yyval.info)->val=addnode("typedargslist");addedge((yyval.info)->val, (yyvsp[-2].info)->val);addedge((yyval.info)->val, (yyvsp[-1].info)->val);(yyvsp[0].val)=addnode(string("COMMA") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4664 "parser.tab.c"
    break;

  case 258: /* typedargslist: tfpdef COMMA  */
#line 1862 "parser.y"
                          {
                (yyval.info) = new Info();
                if((yyvsp[-1].info)->parameters_vec.size()!=0) (yyval.info)->parameters_vec.push_back((yyvsp[-1].info)->parameters_vec[0]);
                (yyval.info)->val=addnode("typedargslist");addedge((yyval.info)->val, (yyvsp[-1].info)->val);(yyvsp[0].val)=addnode(string("COMMA"));addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4673 "parser.tab.c"
    break;

  case 259: /* typedargslist: tfpdef EQUAL test comma_tfpdef_sure  */
#line 1866 "parser.y"
                                                 {
                (yyval.info) = new Info();
                if((yyvsp[-3].info)->parameters_vec[0]->type!=(yyvsp[-1].info)->type) yyerror1("11 there is a type mismatch",yylineno);
                if((yyvsp[-3].info)->parameters_vec.size()!=0) (yyval.info)->parameters_vec.push_back((yyvsp[-3].info)->parameters_vec[0]);
                for(int i=0;i<(yyvsp[0].info)->parameters_vec.size();i++) (yyval.info)->parameters_vec.push_back((yyvsp[0].info)->parameters_vec[i]);
                (yyval.info)->val=addnode("typedargslist");addedge((yyval.info)->val, (yyvsp[-3].info)->val);(yyvsp[-2].val)=addnode(string("EQUAL"));addedge((yyval.info)->val, (yyvsp[-2].val));addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4684 "parser.tab.c"
    break;

  case 260: /* typedargslist: tfpdef EQUAL test  */
#line 1872 "parser.y"
                               {
                (yyval.info) = new Info();
                if((yyvsp[-2].info)->parameters_vec[0]->type!=(yyvsp[0].info)->type) yyerror1("12 there is a type mismatch",yylineno);
                if((yyvsp[-2].info)->parameters_vec.size()!=0) (yyval.info)->parameters_vec.push_back((yyvsp[-2].info)->parameters_vec[0]);
                (yyval.info)->val=addnode("typedargslist");addedge((yyval.info)->val, (yyvsp[-2].info)->val);(yyvsp[-1].val)=addnode(string("EQUAL"));addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4694 "parser.tab.c"
    break;

  case 261: /* typedargslist: tfpdef comma_tfpdef_sure  */
#line 1877 "parser.y"
                                      {
                (yyval.info) = new Info();
                if((yyvsp[-1].info)->parameters_vec.size()!=0) (yyval.info)->parameters_vec.push_back((yyvsp[-1].info)->parameters_vec[0]);
                for(int i=0;i<(yyvsp[0].info)->parameters_vec.size();i++) (yyval.info)->parameters_vec.push_back((yyvsp[0].info)->parameters_vec[i]);
                (yyval.info)->val=addnode("typedargslist");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val); }
#line 4704 "parser.tab.c"
    break;

  case 262: /* typedargslist: tfpdef  */
#line 1882 "parser.y"
                    {
                (yyval.info) = new Info();
                if((yyvsp[0].info)->parameters_vec.size()!=0) (yyval.info)->parameters_vec.push_back((yyvsp[0].info)->parameters_vec[0]) ;
                else (yyval.info)->parameters_vec={};
                (yyval.info)->val=(yyvsp[0].info)->val;}
#line 4714 "parser.tab.c"
    break;

  case 263: /* comma_tfpdef: COMMA tfpdef EQUAL test  */
#line 1889 "parser.y"
                                     {
             (yyval.info)= new Info();
             if((yyvsp[-2].info)->parameters_vec[0]->type!=(yyvsp[0].info)->type) yyerror1("13 There is a type mismatch",yylineno);
             if((yyvsp[-2].info)->parameters_vec[0]!=0) (yyval.info)->parameters_vec.push_back((yyvsp[-2].info)->parameters_vec[0]);
             (yyval.info)->val=addnode("comma_tfpdef");(yyvsp[-3].val)=addnode(string("COMMA") );addedge((yyval.info)->val, (yyvsp[-3].val));addedge((yyval.info)->val, (yyvsp[-2].info)->val);(yyvsp[-1].val)=addnode(string("EQUAL") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4724 "parser.tab.c"
    break;

  case 264: /* comma_tfpdef: COMMA tfpdef  */
#line 1894 "parser.y"
                   {
            (yyval.info) = new Info();
            if((yyvsp[0].info)->parameters_vec[0]!=0) (yyval.info)->parameters_vec.push_back((yyvsp[0].info)->parameters_vec[0]);
            (yyval.info)->val=addnode("comma_tfpdef");(yyvsp[-1].val)=addnode(string("COMMA") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4733 "parser.tab.c"
    break;

  case 265: /* comma_tfpdef_sure: comma_tfpdef  */
#line 1900 "parser.y"
                                {
             (yyval.info) = new Info();
             if((yyvsp[0].info)->parameters_vec[0]!=0) (yyval.info)->parameters_vec.push_back((yyvsp[0].info)->parameters_vec[0]);
             (yyval.info)->val=(yyvsp[0].info)->val;}
#line 4742 "parser.tab.c"
    break;

  case 266: /* comma_tfpdef_sure: comma_tfpdef_sure comma_tfpdef  */
#line 1904 "parser.y"
                                          {
             (yyval.info) = new Info();
             for(int i=0;i<(yyvsp[-1].info)->parameters_vec.size();i++) (yyval.info)->parameters_vec.push_back((yyvsp[-1].info)->parameters_vec[i]);
             if((yyvsp[0].info)->parameters_vec[0]!=0) (yyval.info)->parameters_vec.push_back((yyvsp[0].info)->parameters_vec[0]);
             (yyval.info)->val=addnode("comma_tfpdef_sure");addedge((yyval.info)->val, (yyvsp[-1].info)->val);addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4752 "parser.tab.c"
    break;

  case 267: /* tfpdef: IDENTIFIER  */
#line 1910 "parser.y"
                   {
            (yyval.info) = new Info();
            nor_sym* newsym= new nor_sym((yyvsp[0].val),yylineno);
            newsym->offset = GlobalSymbolTable->curr_sym_tbl->offset;
            GlobalSymbolTable->insert(newsym);
            GlobalSymbolTable->curr_sym_tbl->offset+=4;

            (yyval.info)->val=addnode("tfpdef");(yyvsp[0].val)=addnode(string("IDENTIFIER") );addedge((yyval.info)->val, (yyvsp[0].val));}
#line 4765 "parser.tab.c"
    break;

  case 268: /* tfpdef: IDENTIFIER COLON test  */
#line 1918 "parser.y"
                               {
            nor_sym* newsym= new nor_sym((yyvsp[-2].val),yylineno);
            newsym->offset = GlobalSymbolTable->curr_sym_tbl->offset;
            (yyval.info) = new Info();
            (yyval.info)->type=(yyvsp[0].info)->type;
            newsym->type=(yyvsp[0].info)->type;
            if((yyvsp[0].info)->type == "string") newsym->size=(yyvsp[0].info)->name.size();
            else newsym->size=type_size_map[(yyvsp[0].info)->type];
            (yyval.info)->parameters_vec.push_back(newsym);
            GlobalSymbolTable->insert(newsym);
            GlobalSymbolTable->curr_sym_tbl->offset+=newsym->size;
            (yyval.info)->val=addnode("tfpdef");(yyvsp[-2].val)=addnode(string("IDENTIFIER") );addedge((yyval.info)->val, (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("COLON"));addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4782 "parser.tab.c"
    break;

  case 269: /* $@5: %empty  */
#line 1932 "parser.y"
                                                             {
              Class *newclass = new Class((yyvsp[-4].val),yylineno);
              newclass->offset = GlobalSymbolTable->curr_sym_tbl->offset;
              GlobalSymbolTable->insert(newclass);
              GlobalSymbolTable->make_table((yyvsp[-4].val));
              GlobalSymbolTable->curr_sym_tbl->classtbl=true;
              threeacir->make_block(threeacir->quadruple.size(),(yyvsp[-4].val));}
#line 4794 "parser.tab.c"
    break;

  case 270: /* classdef: CLASS IDENTIFIER CIROPEN arglist CIRCLOSE COLON $@5 suite  */
#line 1939 "parser.y"
                {
              GlobalSymbolTable->outofcurrst();
              (yyval.info)->val=addnode("classdef");(yyvsp[-7].val)=addnode(string("CLASS") );addedge((yyval.info)->val, (yyvsp[-7].val));(yyvsp[-6].val)=addnode(string("IDENTIFIER"));addedge((yyval.info)->val, (yyvsp[-6].val));(yyvsp[-5].val)=addnode(string("CIROPEN") );addedge((yyval.info)->val, (yyvsp[-5].val));addedge((yyval.info)->val, (yyvsp[-4].info)->val);(yyvsp[-3].val)=addnode(string("CIRCLOSE") );addedge((yyval.info)->val, (yyvsp[-3].val));(yyvsp[-2].val)=addnode(string("COLON") );addedge((yyval.info)->val, (yyvsp[-2].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4802 "parser.tab.c"
    break;

  case 271: /* $@6: %empty  */
#line 1942 "parser.y"
                                    {
              Class *newclass = new Class((yyvsp[-1].val),yylineno);

              newclass->offset = GlobalSymbolTable->curr_sym_tbl->offset;
              GlobalSymbolTable->insert(newclass);
              GlobalSymbolTable->make_table((yyvsp[-1].val));
              GlobalSymbolTable->curr_sym_tbl->classtbl=true;
               threeacir->make_block(threeacir->quadruple.size(),(yyvsp[-1].val));}
#line 4815 "parser.tab.c"
    break;

  case 272: /* classdef: CLASS IDENTIFIER COLON $@6 suite  */
#line 1950 "parser.y"
                {
              GlobalSymbolTable->outofcurrst();
              (yyval.info)->val=addnode("classdef");(yyvsp[-4].val)=addnode(string("CLASS") );addedge((yyval.info)->val, (yyvsp[-4].val));(yyvsp[-3].val)=addnode(string("IDENTIFIER"));addedge((yyval.info)->val, (yyvsp[-3].val));(yyvsp[-2].val)=addnode(string("COLON") );addedge((yyval.info)->val, (yyvsp[-2].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4823 "parser.tab.c"
    break;

  case 273: /* $@7: %empty  */
#line 1953 "parser.y"
                                                       {
              Class *newclass = new Class((yyvsp[-3].val),yylineno);
              newclass->offset = GlobalSymbolTable->curr_sym_tbl->offset;
              GlobalSymbolTable->insert(newclass);
              GlobalSymbolTable->make_table((yyvsp[-3].val));
              GlobalSymbolTable->curr_sym_tbl->classtbl=true;
              threeacir->make_block(threeacir->quadruple.size(),(yyvsp[-3].val));}
#line 4835 "parser.tab.c"
    break;

  case 274: /* classdef: CLASS IDENTIFIER CIROPEN CIRCLOSE COLON $@7 suite  */
#line 1960 "parser.y"
                {
              GlobalSymbolTable->outofcurrst();
              (yyval.info)->val=addnode("classdef");(yyvsp[-6].val)=addnode(string("CLASS") );addedge((yyval.info)->val, (yyvsp[-6].val));(yyvsp[-5].val)=addnode(string("IDENTIFIER"));addedge((yyval.info)->val, (yyvsp[-5].val));(yyvsp[-4].val)=addnode(string("CIROPEN") );addedge((yyval.info)->val, (yyvsp[-4].val));(yyvsp[-3].val)=addnode(string("CIRCLOSE") );addedge((yyval.info)->val, (yyvsp[-3].val));(yyvsp[-2].val)=addnode(string("COLON") );addedge((yyval.info)->val, (yyvsp[-2].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4843 "parser.tab.c"
    break;

  case 275: /* dunder_block: IF DUNDER DOUBLE_EQUAL ADUNDER COLON suite  */
#line 1965 "parser.y"
                                                          {
    (yyval.info)->val=addnode("dunder_block");(yyvsp[-5].val)=addnode(string("IF") );addedge((yyval.info)->val, (yyvsp[-5].val));(yyvsp[-4].val)=addnode(string("DUNDER"));addedge((yyval.info)->val, (yyvsp[-4].val));(yyvsp[-3].val)=addnode(string("DOUBLE_EQUAL") );addedge((yyval.info)->val, (yyvsp[-3].val));(yyvsp[-2].val)=addnode(string("ADUNDER") );addedge((yyval.info)->val, (yyvsp[-2].val));(yyvsp[-1].val)=addnode(string("COLON") );addedge((yyval.info)->val, (yyvsp[-1].val));addedge((yyval.info)->val, (yyvsp[0].info)->val);}
#line 4850 "parser.tab.c"
    break;


#line 4854 "parser.tab.c"

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

#line 1971 "parser.y"



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
    //cout << "digraph ASTVisual {\n ordering = out ;\n";
    for(auto e: nodes){
        string s;

         for( auto e1: e.l){
            if(e1=='\"' || e1=='\\'  ){
                s.push_back('\\');
            }
            s.push_back(e1);
        }
        //cout<<e.num<<" [ label=\""<<s<<"\"]\n";
    }
    for(auto e: edges){
        string s;

        for( auto e1: e.l){
            if(e1=='\"' || e1=='\\'){
                s.push_back('\\');
            }
            s.push_back(e1);
        }
        //cout<<e.a<< " -> "<<e.b << "[ label=\""<<s<<"\"]\n";
    }
    //cout << "  }\n";
    return 0;
}
