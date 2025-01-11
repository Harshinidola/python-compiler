%{
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


%}

%union{
  char* val;
  class Info* info;
}

%start starting

%type<info> starting file_input line_or_stmt line_or_stmt_sure stmt line_sure simple_stmt smlst smlst_sure small_stmt expr_stmt equal_testlist_star_expr equal_testlist_star_expr_sure testlist_star_expr comma_test2 comma_test2_sure test or_test or_and_test or_and_test_sure and_test and_not_test and_not_test_sure not_test comparison comp_op_expr comp_op_expr_sure expr alte_xorexpr alte_xorexpr_sure xor_expr power_andexpr power_andexpr_sure and_expr aand_shiftexpr aand_shiftexpr_sure shift_expr llt_ggt_arithexpr llt_ggt_arithexpr_sure arith_expr plus_minus_term plus_minus_term_sure term operator_factor operator_factor_sure factor power atom_expr trailer_sure atom testlist comma_test comma_test_sure testlist_comp exprlist comma_expr comma_expr_sure string_sure trailer arglist comma_argument comma_argument_sure argument subscriptlist comma_subscript comma_subscript_sure subscript comp_op annassign augassign flow_stmt break_stmt continue_stmt return_stmt raise_stmt global_stmt comma_identifier comma_identifier_sure assert_stmt compound_stmt if_stmt else_if else_if_sure suite line_or_newstmt line_or_newstmt_sure new_stmt while_stmt for_stmt funcdef parameters typedargslist comma_tfpdef comma_tfpdef_sure tfpdef classdef dunder_block testlistreturn func_end
%token<val> NEWLINE INDENT DEDENT ENDMARKER DUNDER DATATYPE IS IF ELSE ELIF WHILE FOR RETURN IN FINALLY GLOBAL EXCEPT AS DEF CLASS ASSERT FROM CONTINUE BREAK RAISE NONE TRUE FALSE AND NOT OR DEL INT LISTINT LISTFLOAT LISTSTRING LISTBOOL LIST FLOAT STR BOOL IDENTIFIER DOUBLE_EQUAL GREATER_EQUAL LESS_EQUAL NOT_EQUAL DOUBLE_LESS DOUBLE_GREATER PLUS_EQUAL MINUS_EQUAL MULTI_EQUAL DIVI_EQUAL DOUBLE_DIVI_EQUAL MODULO_EQUAL DOUBLE_MULTI_EQUAL AND_EQUAL PIPE_EQUAL POWER_EQUAL DOUBLE_LESS_EQUAL DOUBLE_GREATER_EQUAL  STRING NUMBER FLOAT_NUMBER IMAGINARY_NUMBER DOUBLE_STAR THREE_DOT GREATER_LESS ARROW DOUBLE_SLASH COLON SEMICOLON PLUS MINUS DIVI EQUAL COMMA PIPE ANDSYMBOL POWER MULTI MOD NOSYMBOL CIROPEN CIRCLOSE SQOPEN SQCLOSE CUOPEN CUCLOSE DOT LESS GREATER ADUNDER
%right NEWLINE
%nonassoc EQUAL



%%




/*starting*/
starting: file_input {$$->val=addnode("starting");addedge($$->val, $1->val); GlobalSymbolTable->printAll(); threeacir->print();
                     return 0;}
        ;

file_input: line_or_stmt_sure ENDMARKER {$$->val=addnode("file_input");addedge($$->val, $1->val);}
          | ENDMARKER {$$->val=addnode("file_input");$1=addnode(string("ENDMARKER") );addedge($$->val, $1);}
          ;

line_or_stmt_sure:line_or_stmt {$$->val= $1->val;}
       |line_or_stmt_sure line_or_stmt {$$->val=addnode("line_or_stmt_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
       ;

line_or_stmt: NEWLINE {$$->val=addnode("NEWLINE");$1=addnode(string("newline") );addedge($$->val, $1);}
   | stmt {$$->val= $1->val;}
   ;

line_sure: NEWLINE {$$->val=addnode("NEWLINE");$1=addnode(string("newline") );addedge($$->val, $1);}
      | line_sure NEWLINE {$$->val=addnode("line_sure");addedge($$->val, $1->val);$2=addnode(string("NEWLINE"));addedge($$->val, $2);}
      ;


stmt: simple_stmt {$$->val= $1->val;}
     | compound_stmt {$$->val= $1->val;}
     ;

simple_stmt: small_stmt smlst_sure NEWLINE {$$->val=addnode("simple_stmt");addedge($$->val, $1->val);addedge($$->val, $2->val);$3=addnode(string("NEWLINE") );addedge($$->val, $3);}
           | small_stmt smlst_sure SEMICOLON NEWLINE {$$->val=addnode("simple_stmt");addedge($$->val, $1->val);addedge($$->val, $2->val);$3=addnode(string("SEMICOLON") );addedge($$->val, $3);$4=addnode(string("NEWLINE") );addedge($$->val, $4);}
           | small_stmt NEWLINE {$$->val=addnode("simple_stmt");addedge($$->val, $1->val);$2=addnode(string("NEWLINE"));addedge($$->val, $2);}
           | small_stmt SEMICOLON NEWLINE {$$->val=addnode("simple_stmt");addedge($$->val, $1->val);$2=addnode(string("SEMICOLON"));addedge($$->val, $2);$3=addnode(string("NEWLINE") );addedge($$->val, $3);}
           ;

smlst: SEMICOLON small_stmt {$$->val=addnode("smlst");$1=addnode(string("SEMICOLON") );addedge($$->val, $1);addedge($$->val, $2->val);}
     ;

smlst_sure: smlst {$$->val=$1->val;}
          | smlst_sure smlst {$$->val=addnode("smlst_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
          ;

small_stmt: expr_stmt {$$->val=$1->val;}
          | flow_stmt {$$->val=$1->val;}
          | global_stmt {$$->val=$1->val;}
          | assert_stmt {$$->val=$1->val;}
          ;

expr_stmt: testlist_star_expr annassign { 
              nor_sym*temp=GlobalSymbolTable->search_nor_sym($1->name,GlobalSymbolTable->curr_scope);
              temp->type=$2->type;
              if($2->type== "string") temp->size=12;
              else temp->size= $2->c*type_size_map[$2->type];
              GlobalSymbolTable->curr_sym_tbl->offset+=temp->size;

              $$->val=addnode("expr_stmt");addedge($$->val, $1->val);addedge($$->val, $2->val);}
         | testlist_star_expr augassign testlist {
            if($1->type!=$3->type)yyerror1("100 There is type mismach",yylineno);
            $$=new Info();$$->type=$1->type;
              $$->val=addnode("expr_stmt");addedge($$->val, $1->val);addedge($$->val, $2->val);addedge($$->val, $3->val);}
         | testlist_star_expr equal_testlist_star_expr_sure {
              if($1->type!=$2->type) yyerror1("1 There is type mismach",yylineno);
              $$=new Info();$1->type=$2->type;$$->val=addnode("expr_stmt");addedge($$->val, $1->val);addedge($$->val, $2->val); int k=GlobalSymbolTable->curr_sym_tbl->nor_sym_vec.size();GlobalSymbolTable->curr_sym_tbl->nor_sym_vec[k-1]->type=$2->type;
              GlobalSymbolTable->curr_sym_tbl->nor_sym_vec[k-1]->size= type_size_map[$2->type];}
         | testlist_star_expr {
          $$=new Info();$$->type=$1->type;
              $$->val=$1->val;}
         ;

equal_testlist_star_expr : EQUAL testlist_star_expr {
            $$=new Info();$$->type=$2->type;
            $$->val=addnode("equal_testlist_star_expr");$1=addnode(string("EQUAL") );addedge($$->val, $1);addedge($$->val, $2->val);}
      ;

equal_testlist_star_expr_sure : equal_testlist_star_expr {
                $$=new Info();$$->type=$1->type;$$->val=$1->val;}
           | equal_testlist_star_expr_sure equal_testlist_star_expr {
                $$=new Info();$$->type=$2->type;
                if($1->type!=$2->type) yyerror1("36 there is a type mismatch",yylineno);
                $$->val=addnode("equal_testlist_star_expr_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
           ;

testlist_star_expr: test comma_test2_sure {
                        $$=new Info();$$->type=$1->type;
                        if($1->type!=$2->type) yyerror1("35 there is a type mismatch",yylineno);
                        $$->val=addnode("testlist_star_expr");addedge($$->val, $1->val);addedge($$->val, $2->val);}
                  | test {
                        $$=new Info();$$->name=$1->name;$$->type=$1->type;$$->val=$1->val;}
                  | test comma_test2_sure COMMA {
                        $$=new Info();$$->type=$1->type;
                        if($1->type!=$2->type) yyerror1("34 there is a type mismatch",yylineno);
                        $$->val=addnode("testlist_star_expr");addedge($$->val, $1->val);addedge($$->val, $2->val);$3=addnode(string("COMMA") );addedge($$->val, $3);}
                  | test COMMA {
                        $$=new Info();$$->type=$1->type;
                        $$->val=addnode("testlist_star_expr");addedge($$->val, $1->val);$2=addnode(string("COMMA"));addedge($$->val, $2);}
                  ;

comma_test2: COMMA test {
        $$=new Info();$$->type=$2->type;
        $$->val=addnode("comma_test2");$1=addnode(string("COMMA") );addedge($$->val, $1);addedge($$->val, $2->val);}
   ;

comma_test2_sure : comma_test2 {$$=new Info();$$->type=$1->type;$$->val=$1->val;}
         | comma_test2_sure comma_test2 {
            $$=new Info();$$->type=$1->type;
            if($1->type!=$2->type) yyerror1("33 there is a type mismatch",yylineno);
            $$->val=addnode("comma_test2_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
         ;

/*test*/
test: or_test IF or_test ELSE test {
         $$->val=addnode("test");addedge($$->val, $1->val);$2=addnode(string("IF"));addedge($$->val, $2);addedge($$->val, $3->val);$4=addnode(string("ELSE") );addedge($$->val, $4);addedge($$->val, $5->val);}
    | or_test {
        $$=new Info(); $$->name=$1->name;$$->type=$1->type;$$->val=$1->val;}
    ;

or_test: and_test or_and_test_sure {
            $$=new Info();$$->type=$1->type;
            if($1->type!=$2->type) yyerror1("33 there is a type mismatch",yylineno);
            $$->val=addnode("or_test");addedge($$->val, $1->val);addedge($$->val, $2->val);}
       | and_test {
            $$=new Info();$$->name=$1->name;$$->type=$1->type; $$->val=$1->val;}
       ;

or_and_test:OR and_test {
          $$=new Info();$$->type=$2->type;
          $$->val=addnode("or_and_test");$1=addnode(string("OR") );addedge($$->val, $1);addedge($$->val, $2->val);}
   ;

or_and_test_sure: or_and_test {$$=new Info();$$->type=$1->type;$$->val=$1->val;}
        | or_and_test_sure or_and_test {
            $$=new Info();$$->type=$2->type;
            if($1->type!=$2->type) yyerror1("32 there is a type mismatch",yylineno);
            $$->val=addnode("or_and_test_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
        ;

and_test: not_test and_not_test_sure {
            $$=new Info();$$->type=$1->type;
            if($1->type!=$2->type) yyerror1("31 there is a type mismatch",yylineno);
            $$->val=addnode("and_test");addedge($$->val, $1->val);addedge($$->val, $2->val);}
        | not_test {
            $$=new Info();$$->name=$1->name;$$->type=$1->type; $$->val=$1->val;}
        ;

and_not_test: AND not_test {
        $$=new Info();$$->type=$2->type;
        $$->val=addnode("and_not_test");$1=addnode(string("AND") );addedge($$->val, $1);addedge($$->val, $2->val);}
   ;

and_not_test_sure: and_not_test {$$=new Info();$$->type=$1->type;$$->val=$1->val;}
        | and_not_test_sure and_not_test {
            $$=new Info();$$->type=$2->type;
            if($1->type!=$2->type) yyerror1("30 there is a type mismatch",yylineno);
            $$->val=addnode("and_not_test_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
        ;

not_test: NOT not_test {
              $$=new Info();$$->type=$2->type;$$->val=addnode("not_test");$1=addnode(string("NOT") );addedge($$->val, $1);addedge($$->val, $2->val);}
        | comparison {
              $$=new Info();$$->name=$1->name;$$->type=$1->type;$$->val=$1->val;}
        ;

comparison: expr comp_op_expr_sure {
                  int k= GlobalSymbolTable->curr_sym_tbl->nor_sym_vec.size();
                  GlobalSymbolTable->curr_sym_tbl->nor_sym_vec[k-1]->type=$2->type;
                  GlobalSymbolTable->curr_sym_tbl->nor_sym_vec[k-1]->size= type_size_map[$2->type];
                  if($1->type!=$2->type) yyerror1("2 there is a type mismatch",yylineno);
                  $$=new Info();$$->type=$1->type;$$->val=addnode("comparison");addedge($$->val, $1->val);addedge($$->val, $2->val);}
          | expr {
                  $$=new Info();$$->name=$1->name;$$->type=$1->type; $$->val=$1->val;}
          ;

comp_op_expr: comp_op expr {
        $$=new Info();
        $$->type=$2->type;
        $$->val=addnode("comp_op_expr");addedge($$->val, $1->val);addedge($$->val, $2->val);}
   ;

comp_op_expr_sure : comp_op_expr {
              $$ = new Info();
              $$->type=$1->type;
              $$->val=$1->val;}
         | comp_op_expr_sure comp_op_expr {
              $$=new Info();
              $$->type=$1->type;
              if($1->type != $2->type) yyerror1("3 there is a type mismatch",yylineno);
              $$->val=addnode("comp_op_expr_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
         ;

expr: xor_expr alte_xorexpr_sure {
          $$=new Info();$$->type=$1->type;
          if($1->type!=$2->type) yyerror1("26 there is a type mismatch",yylineno);
          $$->val=addnode("expr");addedge($$->val, $1->val);addedge($$->val, $2->val);}
    | xor_expr {
          $$=new Info();$$->name=$1->name;$$->type=$1->type; $$->val=$1->val;}
    ;

alte_xorexpr: PIPE xor_expr {
        $$=new Info();$$->type=$2->type;$$->val=addnode("alte_xorexpr");$1=addnode(string("PIPE") );addedge($$->val, $1);addedge($$->val, $2->val);}
  ;

alte_xorexpr_sure: alte_xorexpr {$$=new Info();$$->type=$1->type;$$->val=$1->val;}
       | alte_xorexpr_sure alte_xorexpr {
            $$=new Info();$$->type=$1->type;
            if($1->type!=$2->type) yyerror1("25 there is a type mismatch",yylineno);
            $$->val=addnode("alte_xorexpr_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
       ;

xor_expr: and_expr power_andexpr_sure {
            $$=new Info();$$->type=$1->type;
            if($1->type!=$2->type) yyerror1("25 there is a type mismatch",yylineno);
            $$->val=addnode("xor_expr");addedge($$->val, $1->val);addedge($$->val, $2->val);}
        | and_expr {
            $$=new Info();$$->name=$1->name;$$->type=$1->type;$$->val=$1->val;}
        ;

power_andexpr: POWER and_expr {
        $$=new Info();$$->type=$2->type;$$->val=addnode("power_andexpr");$1=addnode(string("POWER") );addedge($$->val, $1);addedge($$->val, $2->val);}
  ;

power_andexpr_sure: power_andexpr {$$=new Info();$$->type=$1->type;$$->val=$1->val;}
       | power_andexpr_sure power_andexpr {
            $$=new Info();$$->type=$1->type;
            if($1->type!=$2->type) yyerror1("24 there is a type mismatch",yylineno);
            $$->val=addnode("power_andexpr_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
       ;

and_expr: shift_expr aand_shiftexpr_sure {
              $$=new Info();$$->type=$1->type;
              if($1->type!=$2->type) yyerror1("23 there is a type mismatch",yylineno);
              $$->val=addnode("and_expr");addedge($$->val, $1->val);addedge($$->val, $2->val);}
        | shift_expr {
              $$=new Info();$$->name=$1->name;$$->type=$1->type; $$->val=$1->val;}
        ;

aand_shiftexpr: ANDSYMBOL shift_expr {
         $$=new Info();$$->type=$2->type;$$->val=addnode("aand_shiftexpr");$1=addnode(string("ANDSYMBOL") );addedge($$->val, $1);addedge($$->val, $2->val);}
  ;

aand_shiftexpr_sure : aand_shiftexpr {
            $$=new Info();$$->type=$1->type;
            $$->val=$1->val;}
        | aand_shiftexpr_sure aand_shiftexpr {
            $$=new Info();$$->type=$1->type;
            if($1->type!=$2->type) yyerror1("22 there is a type mismatch",yylineno);
            $$->val=addnode("aand_shiftexpr_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
        ;

shift_expr: arith_expr llt_ggt_arithexpr_sure {
              $$=new Info();$$->type=$1->type;
              if($1->type!=$2->type) yyerror1("21 there is a type mismatch",yylineno);
              $$->val=addnode("shift_expr");addedge($$->val, $1->val);addedge($$->val, $2->val);}
          | arith_expr {
              $$=new Info();$$->name=$1->name;$$->type=$1->type;$$->val=$1->val;}
          ;

llt_ggt_arithexpr: DOUBLE_LESS arith_expr {
        $$=new Info();$$->type=$2->type;
        $$->val=addnode("llt_ggt_arithexpr");$1=addnode(string("DOUBLE_LESS") );addedge($$->val, $1);addedge($$->val, $2->val);}
   | DOUBLE_GREATER arith_expr {
        $$=new Info();$$->type=$2->type;
        $$->val=addnode("llt_ggt_arithexpr");$1=addnode(string("DOUBLE_GREATER") );addedge($$->val, $1);addedge($$->val, $2->val);}
   ;

llt_ggt_arithexpr_sure: llt_ggt_arithexpr {
            $$=new Info();$$->type=$1->type;$$->val=$1->val;}
        | llt_ggt_arithexpr_sure llt_ggt_arithexpr {
            $$=new Info();$$->type=$1->type;
            if($1->type!=$2->type) yyerror1("20 there is a type mismatch",yylineno);
            $$->val=addnode("llt_ggt_arithexpr_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
        ;

arith_expr: term plus_minus_term_sure { 
                if($1->type !=$2->type) yyerror1("4 there is type mismatch",yylineno);
                $$=new Info();$$->type=$1->type;$$->val=addnode("arith_expr");addedge($$->val, $1->val);addedge($$->val, $2->val);}
          | term { 
                $$=new Info();$$->name=$1->name;$$->type=$1->type;$$->val=$1->val;}
          ;

plus_minus_term: PLUS term { 
            $$= new Info();
            $$->type = $2->type;
            $$->val=addnode("plus_minus_term");$1=addnode(string("PLUS") );addedge($$->val, $1);addedge($$->val, $2->val);}
      | MINUS term {
            $$= new Info();
            $$->type = $2->type;
            $$->val=addnode("plus_minus_term");$1=addnode(string("MINUS") );addedge($$->val, $1);addedge($$->val, $2->val);}
      ;

plus_minus_term_sure:plus_minus_term {$$=new Info();$$->type=$1->type;$$->val=$1->val;}
           |plus_minus_term_sure plus_minus_term {
              $$=new Info();$$->type=$1->type;$$->val=addnode("plus_minus_term_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
           ;

term: factor operator_factor_sure {
            if($1->type !=$2->type) yyerror1("5 there is type mismatch",yylineno);
            $$=new Info();$$->type=$1->type;$$->val=addnode("term");addedge($$->val, $1->val);addedge($$->val, $2->val);}
    |factor {
            $$=new Info();$$->name=$1->name;$$->type=$1->type;$$->val=$1->val;}
    ;

operator_factor:MULTI factor {
        $$= new Info();
        $$->type= $2->type;
        $$->val=addnode("operator_factor");$1=addnode(string("PLUS") );addedge($$->val, $1);addedge($$->val, $2->val);}
    |DIVI factor {
        $$= new Info();
        $$->type= $2->type;
        $$->val=addnode("operator_factor");$1=addnode(string("DIVI") );addedge($$->val, $1);addedge($$->val, $2->val);}
    |MOD factor { 
        $$= new Info();
        $$->type= $2->type;
        $$->val=addnode("operator_factor");$1=addnode(string("MOD") );addedge($$->val, $1);addedge($$->val, $2->val);}
    |DOUBLE_SLASH factor { 
        $$= new Info();
        $$->type= $2->type;
        $$->val=addnode("operator_factor");$1=addnode(string("DOUBLE_SLASH") );addedge($$->val, $1);addedge($$->val, $2->val);}
    ;

operator_factor_sure: operator_factor { 
            $$=new Info(); $$->type= $1->type;$$->val=$1->val;}
         | operator_factor_sure operator_factor { 
            $$=new Info(); $$->type= $1->type;
            if($1->type!=$2->type) yyerror1("19 there is type mismatch",yylineno);
            $$->val=addnode("operator_factor_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
         ;

factor:PLUS factor {
             $$=new Info();$$->type=$2->type;$$->val=addnode("factor");$1=addnode(string("PLUS") );addedge($$->val, $1);addedge($$->val, $2->val);}
      |MINUS factor {
            $$=new Info();$$->type=$2->type;$$->val=addnode("factor");$1=addnode(string("MINUS") );addedge($$->val, $1);addedge($$->val, $2->val);}
      |NOSYMBOL factor {
            $$=new Info();$$->type=$2->type;$$->val=addnode("factor");$1=addnode(string("NOSYMBOL") );addedge($$->val, $1);addedge($$->val, $2->val);}
      |power { 
            $$=new Info();$$->name=$1->name;$$->type=$1->type;$$->val=$1->val;}
      ;

power: atom_expr DOUBLE_STAR factor {
            $$=new Info();$$->type=$1->type;$$->val=addnode("power");addedge($$->val, $1->val);$2=addnode(string("DOUBLE_STAR"));addedge($$->val, $2);addedge($$->val, $3->val);}
     | atom_expr {
            $$=new Info();$$->name=$1->name;$$->type=$1->type;$$->val=$1->val;}
     ;

atom_expr: atom trailer_sure {
                $$=new Info();$$->type=$1->type;
                $$->name=$2->name;
                if($1->isfunc==true && $1->name!="print" && $1->name!="input" && $1->name!="len"){
                  if($1->parameters_vec.size()!=$2->parameters_vec.size())
                      yyerror1("number of parameters in function does not match",yylineno);
                  int k=$1->parameters_vec.size();
                  for(int i=0;i<k;i++){
                    if($1->parameters_vec[i]->type != $2->parameters_vec[i]->name)
                       yyerror1("6 there is type mismatch",yylineno);
                  }
                }

               
                $$->val=addnode("atom_expr");addedge($$->val, $1->val);addedge($$->val, $2->val);}
         | atom { 
                 $$=new Info();$$->name=$1->name;$$->type=$1->type;$$->val=$1->val;}
         ;

trailer_sure: trailer {
                $$=new Info();
                $$->c =$1->c;
                if($1->c!=5000)
                $$->parameters_vec=$1->parameters_vec;
                $$->type=$1->type;
                $$->name=$1->name;
                $$->val=$1->val;
                }
            | trailer_sure trailer{
                $$=new Info();
                $$->c =$1->c;
                if($1->c!=5000) $$->parameters_vec=$1->parameters_vec;
                $$->type=$1->type;
                $$->name=$1->name;
                $$->val=$1->val;


            }     
            ;
atom: CIROPEN testlist_comp CIRCLOSE { 
         $$=new Info(); $$->type=$2->type;
         $$->val=addnode("atom");$1=addnode(string("CIROPEN") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("CIRCLOSE") );addedge($$->val, $3);}
    | CIROPEN CIRCLOSE { 
         $$=new Info(); $$->c=0;
         $$->val=addnode("atom");$1=addnode(string("CIROPEN") );addedge($$->val, $1);$2=addnode(string("CIRCLOSE"));addedge($$->val, $2);}
    | SQOPEN testlist_comp SQCLOSE { 
        int k=GlobalSymbolTable->curr_sym_tbl->nor_sym_vec.size();
        GlobalSymbolTable->curr_sym_tbl->nor_sym_vec[k-1]->isarray=true;
        $$ = new Info(); $$->type= $2->type;
        GlobalSymbolTable->curr_sym_tbl->nor_sym_vec[k-1]->size=type_size_map[$2->type]*($2->c);
        $$->val=addnode("atom");$1=addnode(string("SQOPEN") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("SQCLOSE") );addedge($$->val, $3);}
    | SQOPEN SQCLOSE { 
        int k=GlobalSymbolTable->curr_sym_tbl->nor_sym_vec.size();
        GlobalSymbolTable->curr_sym_tbl->nor_sym_vec[k-1]->isarray=true;
        $$ = new Info();
        GlobalSymbolTable->curr_sym_tbl->nor_sym_vec[k-1]->size=0;
        $$->val=addnode("atom");$1=addnode(string("SQOPEN") );addedge($$->val, $1);$2=addnode(string("SQCLOSE"));addedge($$->val, $2);}
    | CUOPEN CUCLOSE { 
        $$->val=addnode("atom");$1=addnode(string("CUOPEN") );addedge($$->val, $1);$2=addnode(string("CUCLOSE"));addedge($$->val, $2);}
    | INT { 
           $$=new Info();
           $$->type="int";
           $$->name=$1;
           $$->val=addnode("atom");$1=addnode(string("INT") );addedge($$->val, $1);}
    | LISTINT { 
           $$=new Info();
           $$->type="int";
           $$->name=$1;
           $$->val=addnode("atom");$1=addnode(string("LISTINT") );addedge($$->val, $1);}
    | LISTFLOAT { 
           $$=new Info();
           $$->type="float";
           $$->name=$1;
           $$->val=addnode("atom");$1=addnode(string("LISTFLOAT") );addedge($$->val, $1);}
    | LISTSTRING { 
           $$=new Info();
           $$->type="string";
           $$->name=$1;
           $$->val=addnode("atom");$1=addnode(string("LISTSTRING") );addedge($$->val, $1);}
    | LISTBOOL {
           $$=new Info();
           $$->type="bool";
           $$->name=$1;
           $$->val=addnode("atom");$1=addnode(string("LISTBOOL") );addedge($$->val, $1);}
    | LIST { 
           $$=new Info();
           $$->type="list";
           $$->name=$1;
           $$->val=addnode("atom");$1=addnode(string("LIST") );addedge($$->val, $1);}
    | FLOAT {
            $$=new Info();
            $$->type="float";
            $$->name=$1;
            $$->val=addnode("atom");$1=addnode(string("FLOAT") );addedge($$->val, $1);}
    | STR {
            $$=new Info();
            $$->type="string";
            $$->name=$1;
           $$->val=addnode("atom");$1=addnode(string("STR") );addedge($$->val, $1);}
    | BOOL {
            $$=new Info();
             $$->type="bool";
             $$->name=$1;
            $$->val=addnode("atom");$1=addnode(string("BOOL") );addedge($$->val, $1);}
    | NUMBER { 
              $$=new Info();
              $$->type="int";
              $$->name=$1;
              $$->val=addnode("atom");
              $1=addnode(string("NUMBER") );addedge($$->val, $1);}
    | FLOAT_NUMBER {
               $$=new Info();
               $$->type="float";
               $$->name=$1;
               $$->val=addnode("atom");$1=addnode(string("FLOAT_NUMBER") );addedge($$->val, $1);}
    | IMAGINARY_NUMBER {
              $$=new Info();
               $$->type="inumber";
               $$->name=$1;
               $$->val=addnode("atom");$1=addnode(string("IMAGINARY_NUMBER") );addedge($$->val, $1);}
    | string_sure {
                   $$=new Info();
                   $$->type="string";
                   $$->val=$1->val;}
    | THREE_DOT {
         $$->val=addnode("atom");$1=addnode(string("THREE_DOT") );addedge($$->val, $1);}
    | NONE {$$=new Info();
               $$->type="none";
               $$->name=$1;
      $$->val=addnode("atom");$1=addnode(string("NONE") );addedge($$->val, $1);}
    | TRUE {
            $$=new Info();
            $$->type="bool";
            $$->name=$1;
            $$->val=addnode("atom");$1=addnode(string("TRUE") );addedge($$->val, $1);}
    | FALSE {
            $$=new Info();
            $$->type="bool";
            $$->name=$1;
            $$->val=addnode("atom");$1=addnode(string("FALSE") );addedge($$->val, $1);}
    | IDENTIFIER {
        loc_sym_tbl*curr=GlobalSymbolTable->scope_table_map[GlobalSymbolTable->curr_sym_tbl->scope];


        $$ = new Info();
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
            $$->val=addnode("testlist");addedge($$->val, $1->val);addedge($$->val, $2->val);$3=addnode(string("COMMA") );addedge($$->val, $3);}
        | test comma_test_sure {
            $$ = new Info();
            $$->type=$1->type;
            $$->val=addnode("testlist");addedge($$->val, $1->val);addedge($$->val, $2->val);}
        | test COMMA {
            $$= new Info();
            $$->type=$1->type;
            $$->val=addnode("testlist");addedge($$->val, $1->val);$2=addnode(string("COMMA"));addedge($$->val, $2);}
        | test {
            $$= new Info();
            $$->type=$1->type;
            $$->val=$1->val;}
        ;

testlistreturn:test COMMA {
                  $$= new Info();
                  $$->type=$1->type;
                  $$->val=addnode("testlistreturn");addedge($$->val, $1->val);$2=addnode(string("COMMA"));addedge($$->val, $2);}
              | test {
                  $$= new Info();
                  $$->type=$1->type;
                  $$->val=$1->val;}
              ;

comma_test: COMMA test {
        $$ = new Info();
        $$->c=1;
        $$->type=$2->type;
        $$->val=addnode("comma_test");$1=addnode(string("COMMA") );addedge($$->val, $1);addedge($$->val, $2->val);}
  ;

comma_test_sure: comma_test {
            $$ = new Info();
            $$->c=1;
            $$->val=$1->val;}
       | comma_test_sure comma_test {
            $$ = new Info();
            $$->c=$1->c+1;
            $$->val=addnode("comma_test_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
       ;

testlist_comp: test comma_test_sure COMMA {
                   $$=new Info(); $$->type=$1->type; $$->c=$2->c+1;$$->val=addnode("testlist_comp");addedge($$->val, $1->val);addedge($$->val, $2->val);$3=addnode(string("COMMA") );addedge($$->val, $3);}
             | test COMMA {
                  $$=new Info(); $$->type=$1->type; $$->c=1;$$->val=addnode("testlist_comp");addedge($$->val, $1->val);$2=addnode(string("COMMA"));addedge($$->val, $2);}
             | test comma_test_sure {
                  $$=new Info(); $$->type=$1->type; $$->c=$2->c+1;$$->val=addnode("testlist_comp");addedge($$->val, $1->val);addedge($$->val, $2->val);}
             | test {
                  $$=new Info(); $$->type=$1->type; $$->c=1;$$->val=$1->val;}
             ;

exprlist: expr comma_expr_sure COMMA {$$->val=addnode("exprlist");addedge($$->val, $1->val);addedge($$->val, $2->val);$3=addnode(string("COMMA") );addedge($$->val, $3);}
        | expr COMMA {$$->val=addnode("exprlist");addedge($$->val, $1->val);$2=addnode(string("COMMA"));addedge($$->val, $2);}
        | expr comma_expr_sure {$$->val=addnode("exprlist");addedge($$->val, $1->val);addedge($$->val, $2->val);}
        | expr {
            $$->val=$1->val;}
        ;

comma_expr: COMMA expr {$$->val=addnode("comma_expr");$1=addnode(string("COMMA") );addedge($$->val, $1);addedge($$->val, $2->val);}
    ;

comma_expr_sure: comma_expr {$$->val=$1->val;}
          | comma_expr_sure comma_expr {$$->val=addnode("comma_expr_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
          ;


string_sure:STRING {$$->val=addnode("string_sure");$1=addnode(string("STRING") );addedge($$->val, $1);}
           |STRING string_sure {$$->val=addnode("string_sure");$1=addnode(string("STRING") );addedge($$->val, $1);addedge($$->val, $2->val);}
           ;

trailer:  CIROPEN arglist CIRCLOSE {
            $$=new Info();
            $$->parameters_vec=$2->parameters_vec;
            $$->type=$2->type;
            $$->val=addnode("trailer");$1=addnode(string("CIROPEN") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("CIRCLOSE") );addedge($$->val, $3);}
       |  CIROPEN  CIRCLOSE {
            $$=new Info();
            $$->parameters_vec={};
            $$->val=addnode("trailer");$1=addnode(string("CIROPEN") );addedge($$->val, $1);$2=addnode(string("CIRCLOSE"));addedge($$->val, $2);}
       |  SQOPEN subscriptlist SQCLOSE {
              $$=new Info(); $$->c=5000;$$->type=$2->type;
              $$->val=addnode("trailer");$1=addnode(string("SQOPEN") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("SQCLOSE") );addedge($$->val, $3);}
       |  DOT IDENTIFIER { 
              $$=new Info();
                nor_sym* temp1= GlobalSymbolTable->search_nor_sym( $1, GlobalSymbolTable->curr_scope);
                func* temp2 = GlobalSymbolTable->search_func( $1, GlobalSymbolTable->curr_scope);
                Class* temp3 = GlobalSymbolTable->search_class( $1, GlobalSymbolTable->curr_scope);
                func* temp4 = GlobalSymbolTable->search_pre_func( $1, GlobalSymbolTable->curr_scope);
                if(temp1!=NULL){
                $$->name=$2;
                $$->type=temp1->type;  
                $$->parameters_vec.push_back(temp1);
  
                }
                else{
                nor_sym* newsym= new nor_sym($1,yylineno);
                $$->name=$2;
                newsym->name=$2;
                GlobalSymbolTable->insert(newsym);
                $$->parameters_vec.push_back(newsym);

                }


              $$->val=addnode("trailer");$1=addnode(string("DOT") );addedge($$->val, $1);$2=addnode(string("IDENTIFIER"));addedge($$->val, $2);}
       |  DOT DUNDER {
        $$=new Info();$$->name="dunder";
              $$->val=addnode("trailer");$1=addnode(string("DOT") );addedge($$->val, $1);$2=addnode(string("DUNDER"));addedge($$->val, $2);}
       ;

arglist: argument comma_argument_sure {
            $$ = new Info();
            $$->parameters_vec.push_back($1->parameters_vec[0]);
            for(int i=0;i<$2->parameters_vec.size();i++) $$->parameters_vec.push_back($2->parameters_vec[i]);
            $$->type=$1->type;
            $$->val=addnode("arglist");addedge($$->val, $1->val);addedge($$->val, $2->val);}
       | argument {
            $$ = new Info();
            $$->parameters_vec=$1->parameters_vec;
            $$->type=$1->type;
            $$->val=$1->val;}
       | argument comma_argument_sure COMMA {
            $$ = new Info();
            $$->parameters_vec.push_back($1->parameters_vec[0]);
            for(int i=0;i<$2->parameters_vec.size();i++) $$->parameters_vec.push_back($2->parameters_vec[i]);
            $$->type=$1->type;
            $$->val=addnode("arglist");addedge($$->val, $1->val);addedge($$->val, $2->val);$3=addnode(string("COMMA") );addedge($$->val, $3);}
       | argument COMMA {
            $$ = new Info();
            $$->parameters_vec.push_back($1->parameters_vec[0]);
            $$->type=$1->type;
            $$->val=addnode("arglist");addedge($$->val, $1->val);$2=addnode(string("COMMA"));addedge($$->val, $2);}
       ;

comma_argument:COMMA argument {
        $$ = new Info();
        $$->parameters_vec.push_back($2->parameters_vec[0]);
        $$->type=$2->type;
        $$->val=addnode("comma_argument");$1=addnode(string("COMMA") );addedge($$->val, $1);addedge($$->val, $2->val);}
  ;

comma_argument_sure: comma_argument {
            $$ = new Info();
            $$->parameters_vec.push_back($1->parameters_vec[0]);
            $$->type=$1->type;
            $$->val=$1->val;}
       | comma_argument_sure comma_argument {
            $$ = new Info();
            for(int i=0;i<$1->parameters_vec.size();i++) $$->parameters_vec.push_back($1->parameters_vec[i]);
            $$->parameters_vec.push_back($2->parameters_vec[0]);
            $$->type=$1->type;
            $$->val=addnode("comma_argument_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
       ;

argument: test {
            $$ = new Info();
            nor_sym* temp= new nor_sym($1->type,yylineno);
            $$->parameters_vec.push_back(temp);
            $$->type=$1->type;
            $$->val=$1->val;}
        | test EQUAL test {
            if($1->type!=$3->type) yyerror1("7 There is a type mismatch",yylineno);

            $$ = new Info();

            nor_sym* temp= new nor_sym($1->type,yylineno);
            $$->parameters_vec.push_back(temp);
            $$->type=$1->type;
            $$->val=addnode("argument");addedge($$->val, $1->val);$2=addnode(string("EQUAL"));addedge($$->val, $2);addedge($$->val, $3->val);}
        ;

subscriptlist: subscript comma_subscript_sure {
                    $$->val=addnode("subscriptlist");addedge($$->val, $1->val);addedge($$->val, $2->val);}
             | subscript {
                $$=new Info();$$->type=$1->type;
                    $$->val=$1->val;
                }
             | subscript comma_subscript_sure COMMA {
                   $$->val=addnode("subscriptlist");addedge($$->val, $1->val);addedge($$->val, $2->val);$3=addnode(string("COMMA") );addedge($$->val, $3);}
             | subscript COMMA {
                   $$->val=addnode("subscriptlist");addedge($$->val, $1->val);$2=addnode(string("COMMA"));addedge($$->val, $2);}
             ;

comma_subscript: COMMA subscript {$$->val=addnode("comma_subscript");$1=addnode(string("COMMA") );addedge($$->val, $1);addedge($$->val, $2->val);}
     ;

comma_subscript_sure: comma_subscript {$$->val=$1->val;}
          | comma_subscript_sure comma_subscript {$$->val=addnode("comma_subscript_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
          ;

subscript: test { 
              if($1->type!="int") yyerror1("array index is not an integer",yylineno);
              $$=new Info();$$->type=$1->type;
              $$->val=$1->val;}
         | test  COLON test {
            if($1->type!=$3->type) yyerror1(" 45 type mismatch in line ",yylineno);
            $$=new Info();$$->type=$1->type;
              $$->val=addnode("subscript");addedge($$->val, $1->val);$2=addnode(string("COLON"));addedge($$->val, $2);addedge($$->val, $3->val);}
         | test  COLON {
            $$=new Info();$$->type=$1->type;
              $$->val=addnode("subscript");addedge($$->val, $1->val);$2=addnode(string("COLON"));addedge($$->val, $2);}
         | COLON test {
            $$=new Info();$$->type=$2->type;
              $$->val=addnode("subscript");$1=addnode(string("COLON") );addedge($$->val, $1);addedge($$->val, $2->val);}
         | COLON {
              $$->val=addnode("subscript");$1=addnode(string("COLON") );addedge($$->val, $1);}
         ;

/*comparision operator from not-test in test*/
comp_op: LESS {$$->val=addnode("comp_op");$1=addnode(string("LESS") );addedge($$->val, $1);}
       |GREATER {$$->val=addnode("comp_op");$1=addnode(string("GREATER") );addedge($$->val, $1);}
       |DOUBLE_EQUAL {$$->val=addnode("comp_op");$1=addnode(string("DOUBLE_EQUAL") );addedge($$->val, $1);}
       |GREATER_EQUAL {$$->val=addnode("comp_op");$1=addnode(string("GREATER_EQUAL") );addedge($$->val, $1);}
       |LESS_EQUAL {$$->val=addnode("comp_op");$1=addnode(string("LESS_EQUAL") );addedge($$->val, $1);}
       |GREATER_LESS {$$->val=addnode("comp_op");$1=addnode(string("GREATER_LESS") );addedge($$->val, $1);}
       |NOT_EQUAL {$$->val=addnode("comp_op");$1=addnode(string("NOT_EQUAL") );addedge($$->val, $1);}
       |IN {$$->val=addnode("comp_op");$1=addnode(string("IN") );addedge($$->val, $1);}
       |NOT IN {$$->val=addnode("comp_op");$1=addnode(string("NOT") );addedge($$->val, $1);$2=addnode(string("IN"));addedge($$->val, $2);}
       |IS {$$->val=addnode("comp_op");$1=addnode(string("IS") );addedge($$->val, $1);}
       |IS NOT {$$->val=addnode("comp_op");$1=addnode(string("IS") );addedge($$->val, $1);$2=addnode(string("NOT"));addedge($$->val, $2);}
       ;

annassign:  COLON test { 
                $$=new Info();$$->type=$2->type;
                $$->c=1;
                $$->val=addnode("annassign");$1=addnode(string("COLON") );addedge($$->val, $1);addedge($$->val, $2->val);}
         |  COLON test EQUAL test { 
                if($2->type=="none") yyerror1("variables are declared as void type",yylineno);
                $$=new Info();$$->c=$4->c;
                if($2->type!=$4->type) yyerror1("8 there is type mismatch",yylineno);
                $$->type=$2->type; $$->val=addnode("annassign");$1=addnode(string("COLON") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("EQUAL") );addedge($$->val, $3);addedge($$->val, $4->val);}
         ;

augassign: PLUS_EQUAL {$$->val=addnode("augassign");$1=addnode(string("PLUS_EQUAL") );addedge($$->val, $1);}
         | MINUS_EQUAL {$$->val=addnode("augassign");$1=addnode(string("MINUS_EQUAL") );addedge($$->val, $1);}
         | MULTI_EQUAL {$$->val=addnode("augassign");$1=addnode(string("MULTI_EQUAL") );addedge($$->val, $1);}
         | DIVI_EQUAL {$$->val=addnode("augassign");$1=addnode(string("DIVI_EQUAL") );addedge($$->val, $1);}
         | MODULO_EQUAL {$$->val=addnode("augassign");$1=addnode(string("MODULO_EQUAL") );addedge($$->val, $1);}
         | AND_EQUAL {$$->val=addnode("augassign");$1=addnode(string("AND_EQUAL") );addedge($$->val, $1);}
         | PIPE_EQUAL {$$->val=addnode("augassign");$1=addnode(string("PIPE_EQUAL") );addedge($$->val, $1);}
         | POWER_EQUAL {$$->val=addnode("augassign");$1=addnode(string("POWER_EQUAL") );addedge($$->val, $1);}
         | DOUBLE_LESS_EQUAL {$$->val=addnode("augassign");$1=addnode(string("DOUBLE_LESS_EQUAL") );addedge($$->val, $1);}
         | DOUBLE_GREATER_EQUAL {$$->val=addnode("augassign");$1=addnode(string("DOUBLE_GREATER_EQUAL") );addedge($$->val, $1);}
         | DOUBLE_MULTI_EQUAL {$$->val=addnode("augassign");$1=addnode(string("DOUBLE_MULTI_EQUAL") );addedge($$->val, $1);}
         | DOUBLE_DIVI_EQUAL {$$->val=addnode("augassign");$1=addnode(string("DOUBLE_DIVI_EQUAL") );addedge($$->val, $1);}
         ;

flow_stmt: break_stmt {$$->val=$1->val;}
          | continue_stmt {$$->val=$1->val;}
          | return_stmt {$$->val=$1->val;}
          | raise_stmt {$$->val=$1->val;}
          ;

break_stmt: BREAK {$$->val=addnode("break_stmt");$1=addnode(string("BREAK") );addedge($$->val, $1);}
          ;

continue_stmt: CONTINUE {$$->val=addnode("continue_stmt");$1=addnode(string("CONTINUE") );addedge($$->val, $1);}
             ;

return_stmt: RETURN {
                $$->val=addnode("return_stmt");$1=addnode(string("RETURN") );addedge($$->val, $1);}
           | RETURN testlistreturn {
                $$ = new Info();
                loc_sym_tbl*temp=GlobalSymbolTable->curr_sym_tbl->parent;
                int k=temp->func_vec.size();
                if($2->type=="") temp->func_vec[k-1]->ret_type="none";
                else temp->func_vec[k-1]->ret_type=$2->type;
                $$->val=addnode("return_stmt");$1=addnode(string("RETURN") );addedge($$->val, $1);addedge($$->val, $2->val);}
           ;

raise_stmt: RAISE test FROM test {$$->val=addnode("raise_stmt");$1=addnode(string("RAISE") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("FROM") );addedge($$->val, $3);addedge($$->val, $4->val);}
           | RAISE test {$$->val=addnode("raise_stmt");$1=addnode(string("RAISE") );addedge($$->val, $1);addedge($$->val, $2->val);}
           | RAISE  {$$->val=addnode("raise_stmt");$1=addnode(string("RAISE") );addedge($$->val, $1);}
           ;



global_stmt: GLOBAL IDENTIFIER comma_identifier_sure {$$->val=addnode("global_stmt");$1=addnode(string("GLOBAL") );addedge($$->val, $1);$2=addnode(string("IDENTIFIER"));addedge($$->val, $2);addedge($$->val, $3->val);}
           | GLOBAL IDENTIFIER {$$->val=addnode("global_stmt");$1=addnode(string("GLOBAL") );addedge($$->val, $1);$2=addnode(string("IDENTIFIER"));addedge($$->val, $2);}
           ;

comma_identifier: COMMA IDENTIFIER {$$->val=addnode("comma_identifier");$1=addnode(string("COMMA") );addedge($$->val, $1);$2=addnode(string("IDENTIFIER"));addedge($$->val, $2);}
  ;

comma_identifier_sure: comma_identifier {$$->val=$1->val;}
       | comma_identifier_sure comma_identifier {$$->val=addnode("comma_identifier_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
       ;

assert_stmt: ASSERT test {$$->val=addnode("assert_stmt");$1=addnode(string("ASSERT") );addedge($$->val, $1);addedge($$->val, $2->val);}
           | ASSERT test COMMA test {$$->val=addnode("assert_stmt");$1=addnode(string("ASSERT") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("COMMA") );addedge($$->val, $3);addedge($$->val, $4->val);}
           ;

compound_stmt: if_stmt {$$->val=$1->val;}
             | while_stmt {$$->val=$1->val;}
             | for_stmt {$$->val=$1->val;}
             | funcdef {$$->val=$1->val;}
             | classdef {$$->val=$1->val;}
             | dunder_block {$$->val=$1->val;}
             ;

if_stmt: IF test  COLON suite else_if_sure ELSE COLON suite {
            $$->val=addnode("if_stmt");$1=addnode(string("IF") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("COLON") );addedge($$->val, $3);addedge($$->val, $4->val);addedge($$->val, $5->val);$6=addnode(string("ELSE") );addedge($$->val, $6);$7=addnode(string("COLON") );addedge($$->val, $7);addedge($$->val, $8->val);}
       | IF test  COLON suite ELSE COLON suite {
            $$->val=addnode("if_stmt");$1=addnode(string("IF") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("COLON") );addedge($$->val, $3);addedge($$->val, $4->val);$5=addnode(string("ELSE") );addedge($$->val, $5);$6=addnode(string("COLON") );addedge($$->val, $6);addedge($$->val, $7->val);}
       | IF test  COLON suite else_if_sure {
            $$->val=addnode("if_stmt");$1=addnode(string("IF") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("COLON") );addedge($$->val, $3);addedge($$->val, $4->val);addedge($$->val, $5->val);}
       | IF test  COLON suite {
            $$->val=addnode("if_stmt");$1=addnode(string("IF") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("COLON") );addedge($$->val, $3);addedge($$->val, $4->val);}
       ;

else_if:ELIF test COLON suite {$$->val=addnode("else_if");$1=addnode(string("ELIF") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("COLON") );addedge($$->val, $3);addedge($$->val, $4->val);}
   ;

else_if_sure: else_if {$$->val=$1->val;}
        | else_if_sure else_if {$$->val=addnode("else_if_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
        ;

suite: simple_stmt {$$->val=$1->val; }
     | line_sure INDENT line_or_newstmt_sure DEDENT {
          $$->val=addnode("suite");addedge($$->val, $1->val);$2=addnode(string("INDENT"));addedge($$->val, $2);addedge($$->val, $3->val);$4=addnode(string("DEDENT") );addedge($$->val, $4); }
     ;

line_or_newstmt: NEWLINE {$$->val=addnode("line_or_newstmt");$1=addnode(string("NEWLINE") );addedge($$->val, $1);}
   | new_stmt {$$->val=$1->val;}
   ;

line_or_newstmt_sure: line_or_newstmt {$$->val=$1->val;}
        | line_or_newstmt_sure line_or_newstmt {$$->val=addnode("line_or_newstmt_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
        ;

new_stmt : simple_stmt {$$->val=$1->val;}
         | if_stmt {$$->val=$1->val;}
         | while_stmt {$$->val=$1->val;}
         | for_stmt {$$->val=$1->val;}
         | funcdef {$$->val=$1->val;}
         | dunder_block {$$->val=$1->val;}
         ;

while_stmt: WHILE test  COLON suite  {$$->val=addnode("while_stmt");$1=addnode(string("WHILE") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("COLON") );addedge($$->val, $3);addedge($$->val, $4->val);}
          | WHILE test  COLON suite ELSE  COLON suite {$$->val=addnode("while_stmt");$1=addnode(string("WHILE") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("COLON") );addedge($$->val, $3);addedge($$->val, $4->val);$5=addnode(string("ELSE") );addedge($$->val, $5);$6=addnode(string("COLON") );addedge($$->val, $6);addedge($$->val, $7->val);}
          ;


for_stmt: FOR exprlist IN testlist  COLON suite { 
            $$->val=addnode("for_stmt");$1=addnode(string("FOR") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("IN") );addedge($$->val, $3);addedge($$->val, $4->val);$5=addnode(string("COLON") );addedge($$->val, $5);addedge($$->val, $6->val);}
        | FOR exprlist IN testlist  COLON suite ELSE  COLON suite {$$->val=addnode("for_stmt");$1=addnode(string("FOR") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("IN") );addedge($$->val, $3);addedge($$->val, $4->val);$5=addnode(string("COLON") );addedge($$->val, $5);addedge($$->val, $6->val);$7=addnode(string("ELSE") );addedge($$->val, $7);$8=addnode(string("COLON") );addedge($$->val, $8);addedge($$->val, $9->val);}
        ; 


funcdef: DEF IDENTIFIER {
              func* newfunc = new func($2,yylineno);
              newfunc->offset = GlobalSymbolTable->curr_sym_tbl->offset;
              GlobalSymbolTable->curr_sym_tbl->offset+=4;
              GlobalSymbolTable->insert(newfunc);
              GlobalSymbolTable->make_table(GlobalSymbolTable->curr_scope +"T_"+ $2);
              GlobalSymbolTable->curr_sym_tbl->functbl=true;
              threeacir->insert_two_word_instr("function begin", $2);}
       parameters func_end{
             int k= GlobalSymbolTable->curr_sym_tbl->func_vec.size();

             GlobalSymbolTable->curr_sym_tbl->func_vec[k-1]->parameters_vec=$4->parameters_vec;
             string funcname=GlobalSymbolTable->curr_sym_tbl->func_vec[k-1]->name;
              vector<pair<string,int>>arglist;
              for(int i=0;i<$4->parameters_vec.size();i++){
                arglist.push_back({$4->parameters_vec[i]->name , $4->parameters_vec[i]->size});
              }
              reverse(arglist.begin(),arglist.end());
              threeacir->insert_function_call(funcname, arglist, false, "", true);
              threeacir->insert_two_word_instr("function end", funcname);
              
              $$->val=addnode("funcdef");$1=addnode(string("DEF") );addedge($$->val, $1);$2=addnode(string("IDENTIFIER"));addedge($$->val, $2);addedge($$->val, $4->val);addedge($$->val, $5->val);}

       | DEF DUNDER {
              func* newfunc = new func($2,yylineno);
              newfunc->offset = GlobalSymbolTable->curr_sym_tbl->offset;
              GlobalSymbolTable->curr_sym_tbl->offset+=4;
              GlobalSymbolTable->insert(newfunc);
              GlobalSymbolTable->make_table(GlobalSymbolTable->curr_scope +"T_"+ $2);
              GlobalSymbolTable->curr_sym_tbl->functbl=true;}
       parameters COLON suite {
             GlobalSymbolTable->outofcurrst();
             int k= GlobalSymbolTable->curr_sym_tbl->func_vec.size();
             GlobalSymbolTable->curr_sym_tbl->func_vec[k-1]->ret_type="None";
             GlobalSymbolTable->curr_sym_tbl->func_vec[k-1]->parameters_vec=$4->parameters_vec;
            
             $$->val=addnode("funcdef");$1=addnode(string("DEF") );addedge($$->val, $1);$2=addnode(string("IDENTIFIER"));addedge($$->val, $2);addedge($$->val, $4->val);$5=addnode(string("COLON") );addedge($$->val, $5);addedge($$->val, $6->val);}      
       ;

func_end: ARROW test COLON {
       
             int k= GlobalSymbolTable->curr_sym_tbl->parent->func_vec.size();
             GlobalSymbolTable->curr_sym_tbl->parent->func_vec[k-1]->ret_type=$2->type;}
        suite{
             GlobalSymbolTable->outofcurrst();
             
             int k= GlobalSymbolTable->curr_sym_tbl->func_vec.size();
             string funcname=GlobalSymbolTable->curr_sym_tbl->func_vec[k-1]->name;

             $$->val=addnode("func_end");$1=addnode(string("ARROW") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("COLON") );addedge($$->val, $3);addedge($$->val, $5->val);

        }
        | COLON{
             int k= GlobalSymbolTable->curr_sym_tbl->parent->func_vec.size();
             GlobalSymbolTable->curr_sym_tbl->parent->func_vec[k-1]->ret_type="none";}
        suite{
             GlobalSymbolTable->outofcurrst();
             
             int k= GlobalSymbolTable->curr_sym_tbl->func_vec.size();
             string funcname=GlobalSymbolTable->curr_sym_tbl->func_vec[k-1]->name;

             $$->val=addnode("func_end");$1=addnode(string("COLON") );addedge($$->val, $1);addedge($$->val, $3->val);}
        ;           

parameters:  CIROPEN typedargslist  CIRCLOSE {
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
                if($1->parameters_vec[0]->type!=$3->type) yyerror1("9 there is a type mismatch",yylineno);
                if($1->parameters_vec.size()!=0) $$->parameters_vec.push_back($1->parameters_vec[0]) ;
                for(int i=0;i<$4->parameters_vec.size();i++) $$->parameters_vec.push_back($4->parameters_vec[i]);
                $$->val=addnode("typedargslist");addedge($$->val, $1->val);$2=addnode(string("EQUAL"));addedge($$->val, $2);addedge($$->val, $3->val);addedge($$->val, $4->val);$5=addnode(string("COMMA") );addedge($$->val, $5);}
           | tfpdef EQUAL test COMMA {
                $$ = new Info();
                if($1->parameters_vec[0]->type!=$3->type) yyerror1("10 there is a type mismatch",yylineno);
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
                if($1->parameters_vec[0]->type!=$3->type) yyerror1("11 there is a type mismatch",yylineno);
                if($1->parameters_vec.size()!=0) $$->parameters_vec.push_back($1->parameters_vec[0]);
                for(int i=0;i<$4->parameters_vec.size();i++) $$->parameters_vec.push_back($4->parameters_vec[i]);
                $$->val=addnode("typedargslist");addedge($$->val, $1->val);$2=addnode(string("EQUAL"));addedge($$->val, $2);addedge($$->val, $3->val);addedge($$->val, $4->val);}
           | tfpdef EQUAL test {
                $$ = new Info();
                if($1->parameters_vec[0]->type!=$3->type) yyerror1("12 there is a type mismatch",yylineno);
                if($1->parameters_vec.size()!=0) $$->parameters_vec.push_back($1->parameters_vec[0]);
                $$->val=addnode("typedargslist");addedge($$->val, $1->val);$2=addnode(string("EQUAL"));addedge($$->val, $2);addedge($$->val, $3->val);}
           | tfpdef comma_tfpdef_sure {
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
             if($2->parameters_vec[0]->type!=$4->type) yyerror1("13 There is a type mismatch",yylineno);
             if($2->parameters_vec[0]!=0) $$->parameters_vec.push_back($2->parameters_vec[0]);
             $$->val=addnode("comma_tfpdef");$1=addnode(string("COMMA") );addedge($$->val, $1);addedge($$->val, $2->val);$3=addnode(string("EQUAL") );addedge($$->val, $3);addedge($$->val, $4->val);}
    | COMMA tfpdef {
            $$ = new Info();
            if($2->parameters_vec[0]!=0) $$->parameters_vec.push_back($2->parameters_vec[0]);
            $$->val=addnode("comma_tfpdef");$1=addnode(string("COMMA") );addedge($$->val, $1);addedge($$->val, $2->val);}
    ;

comma_tfpdef_sure: comma_tfpdef {
             $$ = new Info();
             if($1->parameters_vec[0]!=0) $$->parameters_vec.push_back($1->parameters_vec[0]);
             $$->val=$1->val;}
         | comma_tfpdef_sure comma_tfpdef {
             $$ = new Info();
             for(int i=0;i<$1->parameters_vec.size();i++) $$->parameters_vec.push_back($1->parameters_vec[i]);
             if($2->parameters_vec[0]!=0) $$->parameters_vec.push_back($2->parameters_vec[0]);
             $$->val=addnode("comma_tfpdef_sure");addedge($$->val, $1->val);addedge($$->val, $2->val);}
         ;
tfpdef: IDENTIFIER {
            $$ = new Info();
            nor_sym* newsym= new nor_sym($1,yylineno);
            newsym->offset = GlobalSymbolTable->curr_sym_tbl->offset;
            GlobalSymbolTable->insert(newsym);
            GlobalSymbolTable->curr_sym_tbl->offset+=4;

            $$->val=addnode("tfpdef");$1=addnode(string("IDENTIFIER") );addedge($$->val, $1);}
      | IDENTIFIER  COLON test {
            nor_sym* newsym= new nor_sym($1,yylineno);
            newsym->offset = GlobalSymbolTable->curr_sym_tbl->offset;
            $$ = new Info();
            $$->type=$3->type;
            newsym->type=$3->type;
            if($3->type == "string") newsym->size=$3->name.size();
            else newsym->size=type_size_map[$3->type];
            $$->parameters_vec.push_back(newsym);
            GlobalSymbolTable->insert(newsym);
            GlobalSymbolTable->curr_sym_tbl->offset+=newsym->size;
            $$->val=addnode("tfpdef");$1=addnode(string("IDENTIFIER") );addedge($$->val, $1);$2=addnode(string("COLON"));addedge($$->val, $2);addedge($$->val, $3->val);}
      ;

classdef: CLASS IDENTIFIER  CIROPEN arglist  CIRCLOSE  COLON {
              Class *newclass = new Class($2,yylineno);
              newclass->offset = GlobalSymbolTable->curr_sym_tbl->offset;
              GlobalSymbolTable->insert(newclass);
              GlobalSymbolTable->make_table($2);
              GlobalSymbolTable->curr_sym_tbl->classtbl=true;
              threeacir->make_block(threeacir->quadruple.size(),$2);}
          suite {
              GlobalSymbolTable->outofcurrst();
              $$->val=addnode("classdef");$1=addnode(string("CLASS") );addedge($$->val, $1);$2=addnode(string("IDENTIFIER"));addedge($$->val, $2);$3=addnode(string("CIROPEN") );addedge($$->val, $3);addedge($$->val, $4->val);$5=addnode(string("CIRCLOSE") );addedge($$->val, $5);$6=addnode(string("COLON") );addedge($$->val, $6);addedge($$->val, $8->val);}
          | CLASS IDENTIFIER  COLON {
              Class *newclass = new Class($2,yylineno);

              newclass->offset = GlobalSymbolTable->curr_sym_tbl->offset;
              GlobalSymbolTable->insert(newclass);
              GlobalSymbolTable->make_table($2);
              GlobalSymbolTable->curr_sym_tbl->classtbl=true;
               threeacir->make_block(threeacir->quadruple.size(),$2);}
          suite {
              GlobalSymbolTable->outofcurrst();
              $$->val=addnode("classdef");$1=addnode(string("CLASS") );addedge($$->val, $1);$2=addnode(string("IDENTIFIER"));addedge($$->val, $2);$3=addnode(string("COLON") );addedge($$->val, $3);addedge($$->val, $5->val);}
          | CLASS IDENTIFIER  CIROPEN  CIRCLOSE  COLON {
              Class *newclass = new Class($2,yylineno);
              newclass->offset = GlobalSymbolTable->curr_sym_tbl->offset;
              GlobalSymbolTable->insert(newclass);
              GlobalSymbolTable->make_table($2);
              GlobalSymbolTable->curr_sym_tbl->classtbl=true;
              threeacir->make_block(threeacir->quadruple.size(),$2);}
          suite {
              GlobalSymbolTable->outofcurrst();
              $$->val=addnode("classdef");$1=addnode(string("CLASS") );addedge($$->val, $1);$2=addnode(string("IDENTIFIER"));addedge($$->val, $2);$3=addnode(string("CIROPEN") );addedge($$->val, $3);$4=addnode(string("CIRCLOSE") );addedge($$->val, $4);$5=addnode(string("COLON") );addedge($$->val, $5);addedge($$->val, $7->val);}
          ;

dunder_block : IF DUNDER DOUBLE_EQUAL ADUNDER COLON suite {
    $$->val=addnode("dunder_block");$1=addnode(string("IF") );addedge($$->val, $1);$2=addnode(string("DUNDER"));addedge($$->val, $2);$3=addnode(string("DOUBLE_EQUAL") );addedge($$->val, $3);$4=addnode(string("ADUNDER") );addedge($$->val, $4);$5=addnode(string("COLON") );addedge($$->val, $5);addedge($$->val, $6->val);}
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
