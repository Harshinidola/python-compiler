#include <bits/stdc++.h>

using namespace std;

extern int yylineno;
extern void yyerror1(string s,int line);
extern void yyerror(const char *s);
extern map<string,int> type_size_map;


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
        newfunc2->ret_type="byte";
        pre_func.push_back(newfunc2);


        func* newfunc3= new func("len",-1);
        newfunc3->ret_type="int";
        pre_func.push_back(newfunc3);

        func* newfunc4= new func("range",-1);
        newfunc4->ret_type="list";
        pre_func.push_back(newfunc4);

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

        // Open the file2 in write mode
        cerr << "Opening file2: " << "outputs/Table of scope" << scope << ".csv" << endl;
        ofstream file2("outputs/Table of scope"+scope+".csv");

        // Check if the file2 is opened successfully
        if (!file2.is_open()) {
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
                    file2 << row[i];
                    if (i != row.size() - 1) {
                        file2 << ",";
                    }
                }
                file2 << endl;
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
                    file2 << row[i];
                    if (i != row.size() - 1) {
                        file2 << ",";
                    }
                }
                file2 << endl;
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
                    file2 << row[i];
                    if (i != row.size() - 1) {
                        file2 << ",";
                    }
                }
                file2 << endl;
            }

        }

        file2.close();
        //cout << "CSV file2 created successfully for scope "<<scope<< endl;

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
            //count_table_map[i]->printTable();
        }
    }
    bool type_check(string s1, string s2){
        if(s1==s2) return false;
        map<string, vector<string>> check_map;
        vector<string> byte_conversion{"short", "byte", "int", "long", "float", "double"};
        vector<string> bool_conversion{"bool"};
        vector<string> short_conversion{"int", "short", "long", "float", "double"};
        vector<string> int_conversion{"long", "int", "float", "double"};
        vector<string> long_conversion{"float", "long", "double"};
        vector<string> float_conversion{"float", "double"};
        vector<string> double_conversion{"double"};
        vector<string> char_conversion{"char", "int", "long", "float", "double", "short", "byte"};
        check_map["byte"] = byte_conversion;
        check_map["short"] = short_conversion;
        check_map["int"] = int_conversion;
        check_map["long"] = long_conversion;
        check_map["float"] = float_conversion;
        check_map["double"] = double_conversion;
        check_map["char"] = char_conversion;
        check_map["bool"]=bool_conversion;
        int flag = 0;
        for (auto x : check_map[s1])
        {
            if (x == s2)
                flag++;
        }
        if (flag == 0)
            return true;
        else
            return false;
    }


};
extern glo_sym_tbl* GlobalSymbolTable ;

class x86variables{
public:
    vector<string> registers{"ecx", "edx", "r14d", "r15d"};
    vector<string> registers8bit{"al","bl"};
    vector<string> registerstype2{"r8","r9","r10","r11","r12","r13"};
    queue<string>usedregisters;
    queue<string>usedregisters8bit;
    queue<string>usedtype2registers;
    map<string,string>register_to_variables;
    map<string,int>temps_to_memory;
    map<int,int> net_offsetsize;
    map<string,string>temps_to_globals;
    map<string,int>temps_val;

    int offset;
    int labelcnt=0;

    x86variables(){
        for (auto i:registers){
            usedregisters.push(i);
        }
        for (auto i:registers8bit){
            usedregisters8bit.push(i);
        }
        for (auto i:registerstype2){
            usedtype2registers.push(i);
        }
    }

    void local_function_add(){
        offset=0;
        register_to_variables.clear();
        temps_to_memory.clear();
        net_offsetsize.clear();
    }
    string label_local(){
        return "L_OP" + to_string(labelcnt++);
    }
    int add_to_memory(int mysize){
        int x = offset;
        offset+=mysize;
        return offset;
    }

    string register_put(){
        string t = usedtype2registers.front();
        usedtype2registers.pop();
        usedtype2registers.push(t);
        return t;
    }

    vector<string> register_put(string name, string scope,  int mysize=4, bool slq = false){
        vector<string> v;
        string u,t;
        int myoffset;


        if(temps_to_globals.find(name)!=temps_to_globals.end()){
            t = usedregisters.front();
            u = "movl\t" + temps_to_globals[name] + "(%rip), %"+t;
            usedregisters.pop(); usedregisters.push(t);
            v.push_back(u);
            v.push_back(t);

            return v;
        }

        if(mysize==4) t = usedregisters.front();
        else if(mysize==1) t=usedregisters8bit.front();
        else t = usedtype2registers.front();

        if((name[0]<='9' && name[0]>='0') || (name[0]=='-')){

            if(mysize==4) u = "movl\t$";
            else if(mysize==1) u = "movb\t$";
            else if(slq==false) u = "movq\t$";
            else u = "movslq\t$";

            u += name + ", %"+t;
        }
        else if(name.length()>1 && (name[0]=='t' && name[1]=='_')) {
            int x;
            if(temps_to_memory.find(name)==temps_to_memory.end()){
                x = add_to_memory(mysize);
                myoffset = net_size(scope);
                x+=myoffset;
                temps_to_memory.insert({name,x}); // allocated a temporary
                net_offsetsize.insert({x,mysize});
            }
            else {
                x=temps_to_memory[name];
            }

            if(mysize==4) u = "movl\t-" + to_string(x) + "(%rbp), %"+t;
            else if(mysize==1) u = "movb\t-" + to_string(x) + "(%rbp), %"+t;
            else if(slq==false) u = "movq\t-" + to_string(x) + "(%rbp), %"+t;
            else u = "movslq\t-" + to_string(x) + "(%rbp), %" + t;
        }
        else{
            myoffset = location_in_memory(name,scope);
            if(myoffset!=-1){
                net_offsetsize[myoffset] = mysize;

                if(mysize==4) u = "movl\t-";
                else if(mysize==1) u = "movb\t-";
                else if(slq==false) u = "movq\t-";
                else u = "movslq\t-";

                u += to_string(myoffset) + "(%rbp), %" + t;
            }
            else{
                myoffset = location_in_memory(name,scope,true);
                u = "movq\t"+ to_string(myoffset) + "(%rdi), "+t;
            }
        }

        register_to_variables[t] = name;
        if(mysize==4) {
            usedregisters.pop(); usedregisters.push(t);
        }
        else if(mysize==1){
            usedregisters8bit.pop(); usedregisters8bit.push(t);
        }
        else{
            usedtype2registers.pop(); usedtype2registers.push(t);
        }

        v.push_back(u);
        v.push_back(t);

        return v;

    }

    int location_in_memory(string var, string scope, bool is_class=false){
        loc_sym_tbl * curr = GlobalSymbolTable->scope_table_map[scope];
        if(is_class==false)while(curr->scope!="ST_0" && curr->functbl==false && curr->classtbl)curr=curr->parent;
        else while(curr->scope!="ST_0" && curr->classtbl==false)curr=curr->parent;
        for(auto v:curr->nor_sym_vec){
            if(v->name==var){
                if(!is_class){
                    net_offsetsize.insert({v->offset+8+v->size,v->size});
                    return v->offset+v->size+8;
                }
                else{
                    net_offsetsize.insert({v->offset,v->size});
                    return v->offset;
                }
            }
        }
        return -1;
    }

    int net_size(string scope){
        loc_sym_tbl * curr = GlobalSymbolTable->scope_table_map[scope];
        while(curr->scope!="ST_0" && (curr->functbl==false && curr->classtbl))curr=curr->parent;
        return (curr->offset + 8);
    }

    int check_offset(string name, string scope, int mysize = 4, bool is_class = false)
    {
        int x,myoffset;
        if(name.length()>1 && (name[0]=='t' && name[1]=='_')){
            if(temps_to_memory.find(name)==temps_to_memory.end()){
                // cout<<name<<"-"<<mysize<<endl;
                x = add_to_memory(mysize);
                myoffset = net_size(scope);
                x+=myoffset;
                temps_to_memory.insert({name,x}); // allocated a temporary
                net_offsetsize.insert({x,mysize});
            }
            else {
                x=temps_to_memory[name];
            }
        }
        else{
            x = location_in_memory(name,scope,is_class);
        }
        if(x==-1){
            x=location_in_memory(name,scope,true);
            if(x!=1) {
                return -x;
            }

        }
        return x;
    }

    void to_memory(string var, int offset){
        temps_to_memory.insert({var, offset});
    }

};