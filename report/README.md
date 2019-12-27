# 作業 4 報告

> 學生：蔣傑名
>
> 學號：0516097


## Add symboltable.hpp as data structure
```cpp=
#pragma once
extern  int OptSymbol;
#include <vector>
#include <stack>
#include <string.h>
#include "AST/ast.hpp"




class SymbolEntry {
public:
	SymbolEntry(string name_t, string kind_t, int level_t, string type_t, string attr_t){
		name = name_t;
		kind = kind_t;
		level = level_t;
		type = type_t;
		attr = attr_t;
	}
	// void add_attr(vector<struct NodeWithTypeList*>* attr_t){
	// 	attr = attr_t;
	// }
public:
	// id
	string name;
	// program, function, parameter, variable, loop_var, and constant.
	string kind;
	// 0 for global 
	int level;
	// integer, real, boolean, string, or the signature of an array
	string type;	
	//constant or parameter
	string  attr;	
};

class SymbolTable {
public:
    void addSymbol(SymbolEntry s){
    	entries.emplace_back(s);
    };
    // other methods
public:
    std::vector<SymbolEntry> entries;
};



void dumpDemarcation(const char chr) {
  for (size_t i = 0; i < 110; ++i) {
    printf("%c", chr);
  }
  puts("");
}

void dumpSymbol(SymbolTable s) {
  dumpDemarcation('=');
  printf("%-33s%-11s%-11s%-17s%-11s\n", "Name", "Kind", "Level", "Type",
                                        "Attribute");
  dumpDemarcation('-');
  {
  	for(int i=0; i<s.entries.size(); i++){
	    printf("%-33s", s.entries[i].name.c_str());
	    printf("%-11s", s.entries[i].kind.c_str());
	    if(s.entries[i].level==0)
	    	printf("%d%-10s", 0, "(global)");
	    else
	    	printf("%d%-10s", s.entries[i].level, "(local)");
	    printf("%-17s", s.entries[i].type.c_str());
	    printf("%-11s", s.entries[i].attr.c_str());
	    puts("");  		
  	}

  }
  dumpDemarcation('-');
}


class SymbolManager {
public:
    void pushScope(SymbolTable new_scope){
    	tables.push(new_scope);
    };
    void popScope(){
    	if(OptSymbol)
    		dumpSymbol(tables.top());
    	tables.pop();
    };

    // Point(const Point &p2) {x = p2.x; y = p2.y; } 
    
public:
    std::stack <SymbolTable> tables;
};
```

## Change in scanner.l

- Add a variable `count` and `count_line[1000]` for getting source code by `fseek()` and `fgets` when doing semantic analysis

- For each token, count adds the lenth of yytext like the code below
```cpp=
count += strlen(yytext)
```
- When the end line is found, write the `count` to the array of `count_line[1000]`
```cpp=
<INITIAL,CCOMMENT>\n {
    count += 1;
    count_line[LineNum] = count;
    if (OptSrc)
        printf("%d: %s\n", LineNum, Buffer);
    ++LineNum;
    ColNum = 1;
    Buffer[0] = '\0';
    BufferPtr = Buffer;
}
```
- Add psuedo comment D
```cpp=
"//&"[STD][+-].* {
    count += strlen(yytext); 
    LIST;
    char option = yytext[3];
    switch (option) {
    case 'S':
        OptSrc = (yytext[4] == '+') ? 1 : 0;
        break;
    case 'T':
        OptTok = (yytext[4] == '+') ? 1 : 0;
        break;
    case 'D':
        OptSymbol = (yytext[4] == '+') ? 1 : 0;
        break;
    }
}
```

## Change in parser 

- Add function to visit nodes and check semantic error
```cpp=
void semanticAST(ASTNodeBase* node){
    SemanticAnalyzer visitor;
    node->accept(visitor);
}

semanticAST(AST);
```

- Add a variable `error_found` and `semantic analyzer` will check whether there is error and set it to 1 or 0. So the parser could know whether to print `There is no syntactic and semantic error!`

## Change in semantic analyzer

- Construct a symbolmanager to record symbol table in the following nodes

    - ProgramNode
    - FunctioNode
    - CompoundstatementNode
    - ForNode

- Construct symbol entry in the following nodes

    - FunctioNode
    - VariableNode

- Doing semantic analyzer in all the nodes

## Result
```cpp=
Running test case: basic  ==>  Pass!
Running test case: error  ==>  Pass!
Running test case: test  ==>  Pass!
Running test case: Assignment  ==>  Pass!
Running test case: BinaryOperator  ==>  Pass!
Running test case: condition  ==>  Pass!
Running test case: ForLoop  ==>  Pass!
Running test case: function  ==>  Pass!
Running test case: PrintStatement  ==>  Pass!
Running test case: program  ==>  Pass!
Running test case: ReadStatement  ==>  Pass!
Running test case: ret  ==>  Pass!
Running test case: UnaryOperator  ==>  Pass!
Running test case: variable  ==>  Pass!
Running test case: VariableReference  ==>  Pass!
```

## Some advice for TA:

- Make the spec more detailed :  There are still some trivial cases that spec does not specify. Although the classmates will ask the question in issues, it's still a little confusing.

