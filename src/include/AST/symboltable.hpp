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
    
public:
    std::stack <SymbolTable> tables;
};

