#include <bits/stdc++.h>
#include "tac_x86.cpp"

using namespace std;

extern int yylineno;

extern void yyerror1(string s,int line);
extern void yyerror(const char *s);

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

class Info {
public:
    char* val;
    string name;
    string operation;
    int c;
    vector<nor_sym*>parameters_vec;
    vector<string>vec;
    string type;
    bool isfunc;
    string arrtype;
    int index;
    int start;
    Info() {
        c=0;
        val=NULL;
        name="";
        type="";
        isfunc=false;
        operation="";
    }
};