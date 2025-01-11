#include <bits/stdc++.h>
#include "symtable.cpp"

using namespace std;
extern glo_sym_tbl* GlobalSymbolTable ;
extern x86variables* x86_out;
extern int getTemporarySize(string name);

extern ofstream filedebug;

class basic_instruction{
public:
    string net_threeac = "";
    int net_threeac_size = 0;
    bool is_block = false;
    bool incomplete = false;
    bool field_declation = false;
    string scope;

    vector<string> x86code;

    virtual string gen_threeac()
    {
        return "";
    }

    virtual string x86codegen_helper(){
        //filedebug<< 1<<endl;
        return "";
    }

};

class assignment : public basic_instruction
{
public:
    assignment(){
        scope = GlobalSymbolTable->curr_scope;
    }
    string argument1;
    string argument2 = "";
    string op = "";

    string gen_threeac()
    {
        if(argument1 == "popparam")net_threeac_size = 8;
        net_threeac_size = 4;
        string s = "\t";

        if (net_threeac != "")
            s += net_threeac + " := ";

        if (op != ""){
            if (argument2 != "")
                return (s + argument1 + " " + op + " " + argument2);
            else
                return (s + argument1 + op);
        }
        else
        {
            return s + argument1;
        }
    }

    string x86codegen_helper()
    {
        //filedebug<<2<<endl;
        string loc ="";

        if(field_declation==true){
            int off = x86_out->check_offset(net_threeac,scope,4,true);
            loc = to_string(off)+"(%rdi)";
        }
        if(net_threeac[0]=='*'){
            string a1 = "";
            string a2 = "";
            int ind = 2;
            while(net_threeac[ind]!='+')a1+=net_threeac[ind++];
            ind++;
            while (net_threeac[ind] != ')')a2+=net_threeac[ind++];

            int off1 = x86_out->check_offset(a1,scope);
            int off2 = x86_out->check_offset(a2,scope);

            string reg11 = x86_out->register_put();
            string reg12 = x86_out->register_put();

            x86code.push_back("movq\t-"+to_string(off1)+"(%rbp), %"+reg11);
            if(x86_out->net_offsetsize[off2]==4){
                x86code.push_back("movslq\t-" + to_string(off2) + "(%rbp), %" + reg12);
            }
            else {
                x86code.push_back("movq\t-" + to_string(off2) + "(%rbp), %" + reg12);
            }
            x86code.push_back("addq\t%" + reg11 + ", %" + reg12);
            loc = "(%"+reg12+")";
        }
        else if(x86_out->temps_to_globals.find(net_threeac)!=x86_out->temps_to_globals.end()){
            loc = x86_out->temps_to_globals[net_threeac]+"(%rip)";
        }

        if(net_threeac=="stackPointer" && op=="+int"){
            int t = stoi(argument2);
            if(t%16){
                t += 16 - (t%16);
            }
            x86code.insert(x86code.begin(),"subq\t$"+to_string(t)+", %rsp");
        }
        else if (argument2 != "")
        {

            string instr = "";
            string reg1,reg2,reg3;
            vector<string> code;

            if (op[0] == '+')
            {
                instr = "addl";

                code =  x86_out->register_put(argument1,scope);
                x86code.push_back(code[0]);
                reg2 = code[1];

                code = x86_out->register_put(argument2, scope);
                x86code.push_back(code[0]);
                reg3 = code[1];

                reg1 = instr + "\t%" +reg2 + ", %" + reg3;
                x86code.push_back(reg1);
                if(loc==""){
                    int x = x86_out->check_offset(net_threeac,scope);
                    if(x <0)
                    {
                        x *= -1;
                        reg1 = "movl\t%" + reg3 + ", " + to_string(x) + "(%rdi)";
                    }
                    else reg1 = "movl\t%"+reg3+", -" + to_string(x) + "(%rbp)";
                }
                else reg1 = "movl\t%"+reg3+", " + loc;
                x86code.push_back(reg1);

            }
            else if (op[0] == '-')
            {
                instr = "subl";

                code =  x86_out->register_put(argument1,scope);
                x86code.push_back(code[0]);
                reg2 = code[1];

                code = x86_out->register_put(argument2, scope);
                x86code.push_back(code[0]);
                reg3 = code[1];

                reg1 = instr + "\t%" +reg3 + ", %" + reg2;
                x86code.push_back(reg1);

                if(loc==""){
                    int x = x86_out->check_offset(net_threeac,scope);
                    if (x < 0)
                    {
                        x *= -1;
                        reg1 = "movl\t%" + reg2 + ", " + to_string(x) + "(%rdi)";
                    }
                    else reg1 = "movl\t%"+reg2+", -" + to_string(x) + "(%rbp)";
                }
                else reg1 = "movl\t%"+reg2+", " + loc;
                x86code.push_back(reg1);
            }
            else if (op[0] == '*')
            {
                instr = "imull";

                code =  x86_out->register_put(argument1,scope);
                x86code.push_back(code[0]);
                reg2 = code[1];

                code = x86_out->register_put(argument2, scope);
                x86code.push_back(code[0]);
                reg3 = code[1];

                reg1 = instr + "\t%" +reg3 + ", %" + reg2;
                x86code.push_back(reg1);

                if (loc == "")
                {
                    int x = x86_out->check_offset(net_threeac, scope);
                    if (x < 0)
                    {
                        x *= -1;
                        reg1 = "movl\t%" + reg2 + ", " + to_string(x) + "(%rdi)";
                    }
                    else reg1 = "movl\t%" + reg2 + ", -" + to_string(x) + "(%rbp)";
                }
                else
                    reg1 = "movl\t%" + reg2 + ", " + loc;

                x86code.push_back(reg1);
            }
            else if (op[0] == '/')
            {
                instr = "idivl";

                code =  x86_out->register_put(argument1,scope);
                x86code.push_back(code[0]);
                reg2 = code[1];
                x86code.push_back("movl\t%"+reg2+", %eax");

                code = x86_out->register_put(argument2, scope);
                x86code.push_back(code[0]);
                x86code.push_back("movl\t%"+code[1]+", %ecx");
                x86code.push_back("cltd");
                x86code.push_back(instr+"\t%ecx");

                reg1 = "movl\t%eax, ";

                if(loc=="") {
                    int x = x86_out->check_offset(net_threeac, scope);
                    if (x < 0)
                    {
                        x *= -1;
                        loc = to_string(x) + "(%rdi)";
                    }
                    else loc ="-"+ to_string(x) + "(%rbp)";
                }
                reg1 +=loc;
                x86code.push_back(reg1);
            }
            else if (op[0] == '%')
            {
                instr = "idivl";

                code =  x86_out->register_put(argument1,scope);
                x86code.push_back(code[0]);
                reg2 = code[1];
                x86code.push_back("movl\t%"+reg2+", %eax");

                code = x86_out->register_put(argument2, scope);
                x86code.push_back(code[0]);
                x86code.push_back("movl\t%"+code[1]+", %ecx");
                x86code.push_back("cltd");
                x86code.push_back(instr+"\t%ecx");
                reg1 = "movl\t%edx, ";

                if(loc=="") {
                    int x = x86_out->check_offset(net_threeac, scope);
                    if (x < 0)
                    {
                        x *= -1;
                        loc = to_string(x) + "(%rdi)";
                    }
                    else loc += "-"+to_string(x) + "(%rbp)";
                }
                reg1 +=loc;

                x86code.push_back(reg1);
            }
            else if (op[0] == '|')
            {
                instr = "orl";

                code =  x86_out->register_put(argument1,scope);
                x86code.push_back(code[0]);
                reg2 = code[1];

                code = x86_out->register_put(argument2, scope);
                x86code.push_back(code[0]);
                reg3 = code[1];

                reg1 = instr + "\t%" +reg3 + ", %" + reg2;
                x86code.push_back(reg1);
                if (loc == "")
                {
                    int x = x86_out->check_offset(net_threeac, scope);
                    if (x < 0)
                    {
                        x *= -1;
                        reg1 = "movl\t%" + reg2 + ", " + to_string(x) + "(%rdi)";
                    }
                    else reg1 = "movl\t%" + reg2 + ", -" + to_string(x) + "(%rbp)";
                }
                else
                    reg1 = "movl\t%" + reg2 + ", " + loc;
                x86code.push_back(reg1);
            }
            else if (op[0] == '^')
            {
                instr = "xorl";

                code =  x86_out->register_put(argument1,scope);
                x86code.push_back(code[0]);
                reg2 = code[1];

                code = x86_out->register_put(argument2, scope);
                x86code.push_back(code[0]);
                reg3 = code[1];

                reg1 = instr + "\t%" +reg3 + ", %" + reg2;
                x86code.push_back(reg1);
                if (loc == "")
                {
                    int x = x86_out->check_offset(net_threeac, scope);
                    if (x < 0)
                    {
                        x *= -1;
                        reg1 = "movl\t%" + reg2 + ", " + to_string(x) + "(%rdi)";
                    }
                    else reg1 = "movl\t%" + reg2 + ", -" + to_string(x) + "(%rbp)";
                }
                else
                    reg1 = "movl\t%" + reg2 + ", " + loc;
                x86code.push_back(reg1);
            }
            else if (op[0] == '&')
            {
                instr = "andl";

                code =  x86_out->register_put(argument1,scope);
                x86code.push_back(code[0]);
                reg2 = code[1];

                code = x86_out->register_put(argument2, scope);
                x86code.push_back(code[0]);
                reg3 = code[1];

                reg1 = instr + "\t%" +reg3 + ", %" + reg2;
                x86code.push_back(reg1);
                if (loc == "")
                {
                    int x = x86_out->check_offset(net_threeac, scope);
                    if (x < 0)
                    {
                        x *= -1;
                        reg1 = "movl\t%" + reg2 + ", " + to_string(x) + "(%rdi)";
                    }
                    else reg1 = "movl\t%" + reg2 + ", -" + to_string(x) + "(%rbp)";
                }
                else
                    reg1 = "movl\t%" + reg2 + ", " + loc;
                x86code.push_back(reg1);
            }
            else if (op ==">>")
            {
                instr = "sarl";

                string dummy_reg=x86_out->usedregisters.front();
                code = x86_out->register_put(argument2, scope);
                x86code.push_back(code[0]);
                reg3 = code[1];

                if(x86_out->usedregisters.front() == "ecx"){
                    string dummy = x86_out->usedregisters.front();
                    x86_out->usedregisters.pop();
                    x86_out->usedregisters.push(dummy);
                }
                code =  x86_out->register_put(argument1,scope);
                x86code.push_back(code[0]);
                reg2 = code[1];

                if(dummy_reg != "ecx"){
                    string reg4 = "movl\t%"+dummy_reg+", %ecx";
                    x86code.push_back(reg4);
                }

                reg1 = instr + "\t%cl" + ", %" + reg2;
                x86code.push_back(reg1);

                if(loc=="") {
                    int x = x86_out->check_offset(net_threeac, scope);
                    if (x < 0)
                    {
                        x *= -1;
                        reg1 = "movl\t%"+reg2+", " + to_string(x) + "(%rdi)";
                    }
                    else reg1 ="movl\t%"+reg2+", -" + to_string(x) + "(%rbp)";
                }
                else
                    reg1 = "movl\t%" + reg2 + ", " + loc;
                x86code.push_back(reg1);
            }
            else if (op =="<<")
            {
                instr = "sall";

                string dummy_reg=x86_out->usedregisters.front();
                code = x86_out->register_put(argument2, scope);
                x86code.push_back(code[0]);
                reg3 = code[1];

                if(x86_out->usedregisters.front() == "ecx"){
                    string dummy = x86_out->usedregisters.front();
                    x86_out->usedregisters.pop();
                    x86_out->usedregisters.push(dummy);
                }
                code =  x86_out->register_put(argument1,scope);
                x86code.push_back(code[0]);
                reg2 = code[1];

                if(dummy_reg != "ecx"){
                    string reg4 = "movl\t%"+dummy_reg+", %ecx";
                    x86code.push_back(reg4);
                }

                reg1 = instr + "\t%cl" + ", %" + reg2;
                x86code.push_back(reg1);

                if(loc=="") {
                    int x = x86_out->check_offset(net_threeac, scope);
                    if (x < 0)
                    {
                        x *= -1;
                        reg1 = "movl\t%"+reg2+", " + to_string(x) + "(%rdi)";
                    }
                    else reg1 ="movl\t%"+reg2+", -" + to_string(x) + "(%rbp)";
                }
                else
                    reg1 = "movl\t%" + reg2 + ", " + loc;
                x86code.push_back(reg1);
            }
            else if (op[0] =='~')
            {
                instr = "notl";

                code = x86_out->register_put(argument2, scope);
                x86code.push_back(code[0]);
                reg3 = code[1];


                reg1 = instr + "\t" + "%" + reg3;
                x86code.push_back(reg1);
                if(loc==""){
                    int x = x86_out->check_offset(net_threeac,scope,4);
                    if (x < 0)
                    {
                        x *= -1;
                        reg1 = "movl\t%"+reg3+", " + to_string(x) + "(%rdi)";
                    }
                    else reg1 = "movl\t%"+reg3+", -" + to_string(x) + "(%rbp)";
                }
                else
                    reg1 = "movl\t%" + reg3 + ", " + loc;
                x86code.push_back(reg1);
            }
            else if (op =="!")
            {
                instr = "xorb";

                code = x86_out->register_put(argument2, scope,1);
                x86code.push_back(code[0]);
                reg3 = code[1];


                reg1 = instr + "\t$1, %" + reg3;
                x86code.push_back(reg1);
                if(loc==""){
                    int x = x86_out->check_offset(net_threeac,scope,1);
                    if (x < 0)
                    {
                        x *= -1;
                        reg1 = "movb\t%" + reg3 +", " + to_string(x) + "(%rdi)";
                    }
                    else
                        reg1 = "movb\t%" + reg3 + ", -" + to_string(x) + "(%rbp)";
                }
                else
                    reg1 = "movb\t%" + reg3 + ", " + loc;

                x86code.push_back(reg1);
            }
            else if (op == ">="){
                instr = "cmpl";

                code =  x86_out->register_put(argument1,scope);
                x86code.push_back(code[0]);
                reg2 = code[1];

                code = x86_out->register_put(argument2, scope);
                x86code.push_back(code[0]);
                reg3 = code[1];

                reg1 = instr + "\t%" +reg3 + ", %" + reg2;
                x86code.push_back(reg1);

                reg1 = "setge\t%al";
                x86code.push_back(reg1);
                if(loc==""){
                    int x = x86_out->check_offset(net_threeac,scope,1);
                    if (x < 0)
                    {
                        x *= -1;
                        reg1 = "movb\t%al, "  + to_string(x) + "(%rdi)";
                    }
                    else reg1 = "movb\t%al, -" + to_string(x) + "(%rbp)";
                }
                else reg1 = "movb\t%al, " + loc;
                x86code.push_back(reg1);
            }
            else if (op == "<="){
                instr = "cmpl";

                code =  x86_out->register_put(argument1,scope);
                x86code.push_back(code[0]);
                reg2 = code[1];

                code = x86_out->register_put(argument2, scope);
                x86code.push_back(code[0]);
                reg3 = code[1];

                reg1 = instr + "\t%" +reg3 + ", %" + reg2;
                x86code.push_back(reg1);

                reg1 = "setle\t%al";
                x86code.push_back(reg1);
                if(loc==""){
                    int x = x86_out->check_offset(net_threeac,scope,1);
                    if (x < 0)
                    {
                        x *= -1;
                        reg1 = "movb\t%al, " + to_string(x) + "(%rdi)";
                    }
                    else reg1 = "movb\t%al, -" + to_string(x) + "(%rbp)";
                }
                else reg1 = "movb\t%al, " + loc;
                x86code.push_back(reg1);
            }
            else if(op=="=="){
                instr = "cmpl";

                code =  x86_out->register_put(argument1,scope);
                x86code.push_back(code[0]);
                reg2 = code[1];

                code = x86_out->register_put(argument2, scope);
                x86code.push_back(code[0]);
                reg3 = code[1];

                reg1 = instr + "\t%" +reg2 + ", %" + reg3;
                x86code.push_back(reg1);

                reg1 = "sete\t%al";
                x86code.push_back(reg1);
                if(loc==""){
                    int x = x86_out->check_offset(net_threeac, scope, 1);
                    if (x < 0)
                    {
                        x *= -1;
                        reg1 = "movb\t%al, " + to_string(x) + "(%rdi)";
                    }
                    else reg1 = "movb\t%al, -" + to_string(x) + "(%rbp)";
                }
                else reg1 = "movb\t%al, " + loc;
                x86code.push_back(reg1);
            }
            else if(op=="!="){
                instr = "cmpl";

                code =  x86_out->register_put(argument1,scope);
                x86code.push_back(code[0]);
                reg2 = code[1];

                code = x86_out->register_put(argument2, scope);
                x86code.push_back(code[0]);
                reg3 = code[1];

                reg1 = instr + "\t%" +reg2 + ", %" + reg3;
                x86code.push_back(reg1);

                reg1 = "setne\t%al";
                x86code.push_back(reg1);
                if(loc==""){
                    int x = x86_out->check_offset(net_threeac,scope,1);
                    if (x < 0)
                    {
                        x *= -1;
                        reg1 = "movb\t%al, " + to_string(x) + "(%rdi)";
                    }
                    else
                        reg1 = "movb\t%al, -" + to_string(x) + "(%rbp)";
                }
                else reg1 = "movb\t%al, " + loc;

                x86code.push_back(reg1);
            }
            else if(op=="<"){
                instr = "cmpl";

                code =  x86_out->register_put(argument1,scope);
                x86code.push_back(code[0]);
                reg2 = code[1];

                code = x86_out->register_put(argument2, scope);
                x86code.push_back(code[0]);
                reg3 = code[1];

                reg1 = instr + "\t%" +reg3 + ", %" + reg2;
                x86code.push_back(reg1);

                reg1 = "setl\t%al";
                x86code.push_back(reg1);
                if(loc==""){
                    int x = x86_out->check_offset(net_threeac,scope,1);
                    if (x < 0)
                    {
                        x *= -1;
                        reg1 = "movb\t%al, " + to_string(x) + "(%rdi)";
                    }
                    else
                        reg1 = "movb\t%al, -" + to_string(x) + "(%rbp)";
                }
                else reg1 = "movb\t%al, " + loc;
                x86code.push_back(reg1);
            }
            else if(op==">"){
                instr = "cmpl";

                code =  x86_out->register_put(argument1,scope);
                x86code.push_back(code[0]);
                reg2 = code[1];

                code = x86_out->register_put(argument2, scope);
                x86code.push_back(code[0]);
                reg3 = code[1];

                reg1 = instr + "\t%" +reg3 + ", %" + reg2;
                x86code.push_back(reg1);

                reg1 = "setg\t%al";
                x86code.push_back(reg1);
                if(loc==""){
                    int x = x86_out->check_offset(net_threeac,scope,1);
                    if (x < 0)
                    {
                        x *= -1;
                        reg1 = "movb\t%al, " + to_string(x) + "(%rdi)";
                    }
                    else
                        reg1 = "movb\t%al, -" + to_string(x) + "(%rbp)";
                }
                else reg1 = "movb\t%al, " + loc;
                x86code.push_back(reg1);
            }
            else if(op=="||"){
                string label1,label2,label3;
                label1 = x86_out->label_local();
                label2 = x86_out->label_local();
                label3 = x86_out->label_local();

                code =  x86_out->register_put(argument1,scope,1);
                x86code.push_back(code[0]);
                reg2 = code[1];

                x86code.push_back("cmpb\t$0, %"+ reg2);
                x86code.push_back("jne\t"+label1);

                code = x86_out->register_put(argument2, scope,1);
                x86code.push_back(code[0]);
                reg3 = code[1];

                x86code.push_back("cmpb\t$0, %"+ reg3);
                x86code.push_back("je\t" + label2);
                int x;
                if(loc==""){
                    x = x86_out->check_offset(net_threeac,scope,1);
                    if (x < 0)
                    {
                        x *= -1;
                        loc = to_string(x) + "(%rdi)";
                    }
                    else
                        loc = "-" + to_string(x) + "(%rbp)";
                }


                x86code.push_back(label1+":");
                x86code.push_back("movb\t$1, "+loc);
                x86code.push_back("jmp\t" + label3);

                x86code.push_back(label2+":");
                x86code.push_back("movb\t$0, "+loc);

                x86code.push_back(label3+":");

            }
            else if(op=="&&"){
                string label1,label2;
                label1 = x86_out->label_local();
                label2 = x86_out->label_local();

                code =  x86_out->register_put(argument1,scope,1);
                x86code.push_back(code[0]);
                reg2 = code[1];

                x86code.push_back("cmpb\t$0, %"+ reg2);
                x86code.push_back("je\t"+label1);

                code = x86_out->register_put(argument2, scope,1);
                x86code.push_back(code[0]);
                reg3 = code[1];

                x86code.push_back("cmpb\t$0, %"+ reg3);
                x86code.push_back("je\t" + label1);

                int x;
                if(loc==""){
                    x = x86_out->check_offset(net_threeac,scope,1);
                    if (x < 0)
                    {
                        x *= -1;
                        loc = to_string(x) + "(%rdi)";
                    }
                    else
                        loc = "-" + to_string(x) + "(%rbp)";
                }

                x86code.push_back("movb\t$1, "+loc);
                x86code.push_back("jmp\t" + label2);
                x86code.push_back(label1+":");
                x86code.push_back("movb\t$0, "+loc);
                x86code.push_back(label2+":");
            }
        }
        else {
            string reg1,reg2;
            vector<string> code;
            if (argument1 == "popparam")
            {
                net_threeac_size=8;
                x86code.push_back("movq\t%rdi, -8(%rbp)");
                x86_out->to_memory(net_threeac, 8);
            }
            else if(argument1 == "popObject"){
                net_threeac_size = 8;
                int off = x86_out->check_offset(net_threeac,scope,8);
                x86code.push_back("movq\t%rdi, -"+ to_string(off)+"(%rbp)");
            }
            else if (argument1 == "popReturnValue"){
                net_threeac_size = 4;
                int off = x86_out->check_offset(net_threeac,scope,4);
                x86code.push_back("movq\t%rax, -" + to_string(off) + "(%rbp)");
            }
            else if(argument1 == "allocmem"){
                int off = x86_out->check_offset(op,scope);
                x86code.push_back("movslq\t-" + to_string(off) + "(%rbp), %rdi");
                x86code.push_back("call\tmalloc");
                int x  = x86_out->check_offset(net_threeac,scope,8);
                x86code.push_back("movq\t%rax, -"+to_string(x)+"(%rbp)");
            }
            else if (argument1 == "getAddress"){
                vector<string>code;
                int x = x86_out->temps_val[op];
                string reg1 = x86_out->register_put();
                x86code.push_back("movq\t-"+to_string(x)+"(%rbp), %"+reg1);
                x = x86_out->check_offset(net_threeac,scope,8);
                x86code.push_back("movq\t%"+reg1+", -"+to_string(x)+"(%rbp)");
            }
            else{
                if(argument1=="true"){
                    net_threeac_size=1;
                    code = x86_out->register_put("1", scope,1);
                }
                else if(argument1=="false"){
                    net_threeac_size=1;
                    code = x86_out->register_put("0", scope,1);
                }
                else {
                    int c;
                    if((argument1[0]<='9' && argument1[0]>='0') || (argument1[0]=='-')) c=4;
                    else c = x86_out->net_offsetsize[x86_out->check_offset(argument1,scope)];
                    if(c==1){
                        net_threeac_size=1;
                        code = x86_out->register_put(argument1, scope,1);
                    }
                    else if (c== 8)
                    {
                        net_threeac_size = 8;
                        code = x86_out->register_put(argument1, scope, 8);
                    }
                    else {
                        net_threeac_size=4;
                        code = x86_out->register_put(argument1, scope);
                    }
                }

                x86code.push_back(code[0]);
                reg2 = code[1];

                if(loc!="")reg1 = "movl\t%"+reg2+", " + loc;
                else {
                    int x = x86_out->check_offset(net_threeac, scope,net_threeac_size);
                    string suff =  ", -" + to_string(x) + "(%rbp)";
                    if(x<0){
                        x*=-1;
                        suff = ", " + to_string(x) + "(%rdi)";
                    }
                    if(net_threeac_size==1) reg1 = "movb \t%"+reg2+ suff;
                    else if(net_threeac_size==4) reg1 = "movl\t%"+reg2 + suff;
                    else reg1 = "movq\t%"+reg2 + suff;
                }
                x86code.push_back(reg1);
            }

        }

        string s="";
        for (auto x : x86code){
            if(x[0]!='L') s+="\t" + x+"\n";
            else s+= x+"\n";
        }
        return s;
    }
};

class unconditional_jump : public basic_instruction{
public:
    unconditional_jump(){
        scope = GlobalSymbolTable->curr_scope;
    }
    string argument1 = "goto";
    string argument2 = "";
    int index;

    string gen_threeac()
    {
        if (argument2 == "")
            return ("\t" + argument1 + " " + to_string(index));
        else
            return ("\t" + argument1 + " " + argument2);
    }

    string x86codegen_helper(){
        //filedebug<<3<<endl;
        string s="";
        s="jmp ";
        if (argument2 == "")
            s+= to_string(index);
        else
            s+=argument2;

        x86code.push_back(s);

        s="";
        for (auto x : x86code){
            s+="\t" + x+"\n";
        }

        return s;
    }


};

class conditional_jump : public basic_instruction{
public:
    conditional_jump()
    {
        scope = GlobalSymbolTable->curr_scope;
    }
    string argument1 = "if";
    string argument2;
    string argument3 = "goto";
    string argument4 = "";
    int index;

    string gen_threeac()
    {
        if (argument4 == "")
            return ("\t" + argument1 + " " + argument2 + " " + argument3 + " " + to_string(index));
        else
            return ("\t" + argument1 + " " + argument2 + " " + argument3 + " " + argument4);
    }

    string x86codegen_helper(){
        //filedebug<<4<<endl;

        string s = "cmpb\t$1, %";

        vector<string> code;
        code = x86_out->register_put(argument2, scope,1);
        x86code.push_back(code[0]);
        s += code[1];
        x86code.push_back(s);

        x86code.push_back("je "+argument4);

        s="";
        for (auto x : x86code){
            s+="\t" + x+"\n";
        }
        return s;
    }
};

class block : public basic_instruction{
public:
    vector<basic_instruction *> codes;
    block(){
        scope = GlobalSymbolTable->curr_scope;
    }

    string gen_threeac(){
        string s = net_threeac + ":";
        for (auto x : codes){
            s += "\n" + x->gen_threeac();
        }
        return s;
    }

    string x86codegen_helper(){
        //filedebug<<5<<endl;
        string s = net_threeac + ":\n";
        for (auto x : codes)
        {
            s += x->x86codegen_helper();
        }
        //filedebug<<s<<endl;
        return s;
    }

};

class two_word_instr : public basic_instruction{
public:
    two_word_instr(){
        scope = GlobalSymbolTable->curr_scope;
    }
    string argument1;
    string argument2;
    string gen_threeac()
    {
        return argument1 + " " + argument2;
    }

    string x86codegen_helper(){
        //filedebug<<6<<endl;
        //filedebug<<argument1<<endl;
        if (argument1 == "function begin"){
            x86_out->local_function_add();
            string parentName = GlobalSymbolTable->scope_table_map[scope]->parent->scope;
            string methodName = scope.substr(parentName.length() + 2, scope.length() - (parentName.length()));
            int size = x86_out->net_size(scope) + getTemporarySize(methodName);
            int a=16;
            while(a<size) a+=16;
            size=a;
            x86code.push_back("\tpushq\t%rbp");
            x86code.push_back("\tmovq\t%rsp, %rbp");
            x86code.push_back("\tsubq	$" + to_string(size) + ", %rsp");
        }
        if(argument1=="\tend constructor"){
            x86code.push_back("\tmovq\t-8(%rbp), %rdi");
        }
        if (argument1 == "function end" || argument1 == "\tend constructor")
        {
            x86code.push_back("\tmovq\t%rbp, %rsp");
            x86code.push_back("\tpopq\t%rbp");
            x86code.push_back("\tret");
        }
        if(argument1.substr(0,5) == "\tcall"){
            x86code.push_back(argument1);

        }
        if(argument1=="\tpush"){
            vector<string> code;

            code = x86_out->register_put(argument2, scope);
            x86code.push_back("\t"+code[0]);
            string reg = code[1];

            x86code.push_back("\tmovslq\t%"+reg+", %rax");
        }

        else if(argument1=="\tbegin constructor"){
            x86_out->local_function_add();
            string parentName = GlobalSymbolTable->scope_table_map[scope]->parent->scope;
            int size = x86_out->net_size(scope)+getTemporarySize(parentName);
            int a=16;
            while(a<size) a+=16;
            size=a;
            x86code.push_back("\tpushq\t%rbp");
            x86code.push_back("\tmovq\t%rsp, %rbp");
            x86code.push_back("\tsubq	$"+to_string(size)+", %rsp");
        }
        else if(argument1 == "\tprint"){
            x86code.push_back("\tmov\t$printLabel, %rdi");
            int off = x86_out->check_offset(argument2,scope,4);
            string xx = "";
            if(off>0){
                if(x86_out->temps_to_globals.find(argument2)!=x86_out->temps_to_globals.end()){
                    xx = "\tmovslq\t" + x86_out->temps_to_globals[argument2] + "(%rip), %rsi";
                }
                else xx= "\tmovslq\t-"+to_string(off)+"(%rbp), %rsi";
            }
            if(off<0){
                off*=-1;
                xx = "\tmovslq\t" + to_string(off) + "%(%rdi), %rsi";
            }
            x86code.push_back(xx);
            x86code.push_back("\txor\t%rax, %rax");
            x86code.push_back("\tcall\tprintf");
        }
        string s = "";
        for (auto x : x86code)
        {
            s += x + "\n";
        }
        return s;
    }
};

class function_call : public basic_instruction{
public:
    function_call(){
        scope = GlobalSymbolTable->curr_scope;
    }
    string name;
    string object_name;
    vector<string> params;
    bool is_call = false;
    bool is_constructor = false;
    string constructor_name = "";

    string mysize = "";

    string gen_threeac()
    {
        string s = "";
        if (!is_call){
            return s;
        }
        for (auto x : params){
            s += "\tparam " + x ;
        }
        //s += "\tpush basePointer\n\tbasePointer := stackPointer\n";
        //s += "\tstackPointer := stackPointer -int " + mysize;

        return s;
    }

    string x86codegen_helper(){
        //filedebug<<7<<endl;
        if(is_call){
            int size=0;
            for (auto x : params)
            {
                int y;
                if((x[0]<='9' && x[0]>='0') || (x[0]=='-')) {
                    x86code.push_back("subq\t$4,%rsp");
                    x86code.push_back("movl\t$" + x + ", (%rsp)");
                    y=4;
                }
                else{
                    if(x[0]=='*'){

                    }
                    vector<string> code;
                    y = x86_out->check_offset(x, scope);
                    if(y<0){
                        y*=-1;
                        code.push_back("");
                        code.push_back(to_string(y)+"(%rdi)");
                        y=4;
                    }
                    else{
                        y = x86_out->net_offsetsize[y];
                        code = x86_out->register_put(x, scope, y);
                        x86code.push_back(code[0]);
                    }

                    if(y==1){
                        x86code.push_back("pushb\t%"+code[1]);
                    }
                    else if(y==4){
                        x86code.push_back("subq\t$4,%rsp");
                        x86code.push_back("movl\t%"+code[1]+", (%rsp)");
                    }
                    else {
                        x86code.push_back("pushq\t%"+code[1]);
                    }
                }
                size+=y;
            }

            if(size%16){
                size = 16 - (size%16);
                x86code.insert(x86code.begin(),"subq\t$"+to_string(size)+", %rsp");
            }
            if(is_constructor==false){
                if(object_name!="" && object_name!=name){
                    int off1 = x86_out->check_offset(object_name,scope,8);
                    x86code.push_back("movq\t-"+to_string(off1)+"(%rbp), %rdi");
                }
                else{
                    x86code.push_back("movq\t-8(%rbp), %rdi");
                }
            }
        }
        string s="";
        for (auto x : x86code){
            s+="\t" + x+"\n";
        }
        return s;
    }
};

class array_insert : public basic_instruction{
public:
    array_insert(){
        scope = GlobalSymbolTable->curr_scope;
    }
    vector<string> elements;
    string array;
    int typesize;

    string gen_threeac()
    {
        int off = 0;
        string s = "";
        for (auto elem : elements)
        {
            if (elem == "")
                continue;
            s += "\tpushArr " + array + " " + elem + " " + to_string(off) + "\n"; // elem = $3 offset
            off += typesize;
        }
        return s;
    }

    string x86codegen_helper(){
        //filedebug<<8<<endl;
        x86code.push_back("movq\t-"+to_string(x86_out->check_offset(array,scope,8))+"(%rbp), %rax");

        int off = 0;
        for (auto elem : elements)
        {
            if (elem == "")
                continue;
            else if (elem.length()>1 && (elem[0]=='t' && elem[1]=='_')){
                int t = x86_out->check_offset(elem,scope);
                x86code.push_back("movl\t-" + to_string(t) + "(%rbp), %ecx");
                x86code.push_back("movl\t%ecx, "+to_string(off)+"(%rax)");
                off += typesize;
                continue;
            }
            x86code.push_back("movl\t$" + elem + ", "+to_string(off)+"(%rax)");
            off += typesize;
        }

        string s="";
        for (auto x : x86code){
            s+="\t" + x+"\n";
        }
        return s;
    }
};

class symbol_table_offset : public basic_instruction{
public:
    symbol_table_offset(){
        scope = GlobalSymbolTable->curr_scope;
    }
    string classname;
    string offset;
    int offset_value;
    bool array = false;

    string gen_threeac()
    {
        net_threeac_size = 4;
        string s = "\t" + net_threeac + " := getFromSymTable( " + classname + " , " + offset + ")";
        return s;
    }

    string x86codegen_helper(){
        //filedebug<<9<<endl;
        string s = "";
        for (auto yy : x86code)
        {
            s += "\t" + yy + "\n";
        }
        return s;
    }
};


class THREEACX86{
public:
    vector<basic_instruction *> quadruple;
    map<string, block *> blocks;
    int local_var_count = 0;
    int local_label_count = 0;

    string get_var(int index){
        return quadruple[index]->net_threeac;
    }
    string get_local_var(){
        return "t_" + to_string(local_var_count++);
    }
    string get_local_label(){
        return "L" + to_string(local_label_count++);
    }
    string next_label(){
        return "L" + to_string(local_label_count + 1);
    }

    int insert(basic_instruction *instruction){
        quadruple.push_back(instruction);
        return quadruple.size() - 1;
    }
    int insert(string argument1, string res = ""){
        assignment *instruction = new assignment();
        instruction->argument1 = argument1;

        if (res == "")
            instruction->net_threeac = get_local_var();
        else
            instruction->net_threeac = res;
        quadruple.push_back(instruction);
        return quadruple.size() - 1;
    }
    basic_instruction *create(string myargument1, string myargument2, string op, string res = "")
    {
        assignment *instruction = new assignment();
        instruction->argument1 = myargument1;
        instruction->argument2 = myargument2;
        instruction->op = op;

        if (res == "")
            instruction->net_threeac = get_local_var();
        else
            instruction->net_threeac = res;

        return instruction;
    }
    int make_block(int index, string name = "", int endindex = -1){
        if(endindex==-1)endindex=quadruple.size();
        block* curr_instruction = new block();
        if(name=="") curr_instruction->net_threeac = get_local_label();
        else curr_instruction->net_threeac=name;
        for(int i=index;i<endindex;i++){
            curr_instruction->codes.push_back(quadruple[i]);
        }
        quadruple.erase(quadruple.begin()+index,quadruple.begin()+endindex);
        blocks.insert({curr_instruction->net_threeac,curr_instruction});
        basic_instruction* curr_instruction2 = curr_instruction;
        curr_instruction2->is_block=true;
        quadruple.push_back(curr_instruction2);
        return quadruple.size()-1;
    }
    int make_block()
    {
        block* curr_instruction = new block();
        curr_instruction->net_threeac = get_local_label();
        blocks.insert({curr_instruction->net_threeac,curr_instruction});
        basic_instruction* curr_instruction2 = curr_instruction;
        curr_instruction2->is_block=true;
        quadruple.push_back(curr_instruction2);
        return quadruple.size()-1;
    }

    int insert_assignment(string givearg1, string givearg2, string op,string var=""){
        return insert(create(givearg1,givearg2,op,var));
    }

    int insert_jump(string givearg2, int index=-1){
        unconditional_jump* curr_instruction = new unconditional_jump();
        curr_instruction->argument2=givearg2;
        if(index==-1) quadruple.push_back(curr_instruction);
        else{
            quadruple.insert(quadruple.begin()+index+1,curr_instruction);
        }
        if(blocks.find(givearg2)==blocks.end()){
            block* curr_block = new block();
            curr_block->net_threeac = givearg2;
            curr_block->is_block=true;
            blocks.insert({givearg2,curr_block});
            basic_instruction* block_label = curr_block;
            quadruple.push_back(block_label);
        }
        return quadruple.size()-1;
    }
    void insert_next_jump(string arg1, string jump_loaction_number){
        unconditional_jump* curr_instruction = new unconditional_jump();
        curr_instruction->argument2=jump_loaction_number;
        basic_instruction* given_jump= curr_instruction;
        blocks[arg1]->codes.push_back(given_jump);
        if(blocks.find(jump_loaction_number)==blocks.end()){
            block* curr_block = new block();
            curr_block->net_threeac = jump_loaction_number;
            curr_block->is_block=true;
            blocks.insert({jump_loaction_number,curr_block});
            basic_instruction* block_label = curr_block;
            quadruple.push_back(block_label);
        }
    }
    int insert_if(int index ,string arg1,string arg2, string arg3){
        conditional_jump* curr_instruction = new conditional_jump();
        string next = get_local_label();
        curr_instruction->argument2= arg1;
        curr_instruction->argument4= arg2;
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
        curr_instruction->argument2= condition;
        curr_instruction->argument4= arg2;

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
        if(startindex>=0) curr_instruction->argument2= quadruple[endindex]->net_threeac;
        else curr_instruction->argument2 = "true";
        curr_instruction->argument4= arg2;
        quadruple.insert(quadruple.begin()+endindex+1,curr_instruction);

        insert_jump(next, endindex+1);
        int x;
        if(startindex>=0) x = make_block(startindex);
        else x = make_block(endindex+1);
        insert_next_jump(arg2,get_var(x));
        if(mystart>=0) x = make_block(mystart);

        update_incomplete_jump(quadruple[x]->net_threeac,changeExp,next);
        return quadruple.size()-1;

    }

    int insert_two_word_instr(string s, string arg2){
        two_word_instr* curr_instruction = new two_word_instr();
        curr_instruction->argument1 = s;
        curr_instruction->argument2 = arg2;
        return insert(curr_instruction);
    }

    int insert_function_call(string funcName, vector<pair<string,int>> argList, bool is_constructor=false, string mysize="", bool isVoid=true){
        function_call* my_function_call = new function_call();
        my_function_call->name = funcName;
        for(auto x: argList){
            my_function_call->params.push_back(x.first);
        }
        my_function_call->is_constructor = is_constructor;
        my_function_call->mysize = mysize;
        my_function_call->is_call=true;
        basic_instruction* curr_instruction = my_function_call;
        quadruple.push_back(curr_instruction);
        if(argList.size()) insert_two_word_instr("\tcall "+funcName,to_string(argList.size()));
        else insert_two_word_instr("\tcall "+funcName,"");
        if(!isVoid) insert_assignment("popReturnValue","","");
        int t=0;
        for(auto x : argList){
            t+=x.second;
        }
        //insert_assignment("stackPointer",to_string(t),"+int","stackPointer");
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
        instr->offset_value = offset;
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
                given_jump->argument2=arg2;
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
        cerr << "Opening file: " << "outputs/threeac.txt"<< endl;
        ofstream filethreeac("outputs/threeac.txt");
        if (!filethreeac.is_open()) {
            cerr << "Failed to open the file." << endl;
            return;
        }
        for(int i=0;i<quadruple.size();i++){
            filethreeac<<quadruple[i]->gen_threeac();
            filethreeac<<endl;
        }
    }

    void x86gen_threeac(){
        cerr << "Opening file: " << "outputs/output.s"<< endl;
        ofstream filex86("outputs/output.s");
        if (!filex86.is_open()) {
            cerr << "Failed to open the file." << endl;
            return;
        }

        filex86<<"\t.text\n\t.globl\tmain\n\t.type\tmain, @function\n";

        for (int i = 0; i < quadruple.size(); i++)
        {
            filex86 <<quadruple[i]->x86codegen_helper();
        }
        filex86<<"printLabel:\n";
        filex86 << "\t.asciz\t\"%d\\n\" ";
        filex86<<"\n";
    }
};
