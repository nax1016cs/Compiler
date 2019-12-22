#include "semantic/SemanticAnalyzer.hpp"
#include "AST/program.hpp"
#include "AST/declaration.hpp"
#include "AST/variable.hpp"
#include "AST/constant_value.hpp"
#include "AST/function.hpp"
#include "AST/compound_statement.hpp"
#include "AST/assignment.hpp"
#include "AST/print.hpp"
#include "AST/read.hpp"
#include "AST/variable_reference.hpp"
#include "AST/binary_operator.hpp"
#include "AST/unary_operator.hpp"
#include "AST/if.hpp"
#include "AST/while.hpp"
#include "AST/for.hpp"
#include "AST/return.hpp"
#include "AST/function_call.hpp"
#include "AST/symboltable.hpp"

#include <iostream>
#include <string.h>
using namespace std;
int isparameter = 0;
int level = 0;
int function_cmp = 0;
SymbolManager manager;

SymbolTable* current_table;
SymbolEntry* current_entry;

void SemanticAnalyzer::visit(ProgramNode *m) {
    SymbolEntry* s = new SymbolEntry(m->program_name, "program", level, "void", "");
    SymbolTable* first = new SymbolTable;
    first->addSymbol(*s);
    current_table = first;
    delete(s);
    if (m->declaration_node_list != nullptr)
        for(uint i=0; i< m->declaration_node_list->size(); i++){
            (*(m->declaration_node_list))[i]->accept(*this);
        }

    if (m->function_node_list != nullptr)
        for(uint i=0; i< m->function_node_list->size(); i++){
            (*(m->function_node_list))[i]->accept(*this);
        }
    // level++;
    if (m->compound_statement_node != nullptr){
        m->compound_statement_node->accept(*this);
    }
 	// level--;
    manager.popScope();
}

void SemanticAnalyzer::visit(DeclarationNode *m) {
    if (m->variables_node_list != nullptr)
        for(uint i=0; i< m->variables_node_list->size(); i++){
            (*(m->variables_node_list))[i]->accept(*this);
        }
}

void SemanticAnalyzer::visit(VariableNode *m) {

    if (m->constant_value_node != nullptr){
       	SymbolEntry* s = new SymbolEntry(m->variable_name, "constant", level, m->getType(), "");
       	current_entry = s;
        // cout<<s->name<<" "<<s->kind<<s->level<<s->type<<s->attr<<endl;       	
        m->constant_value_node->accept(*this);
        // cout<<s->name<<" "<<s->kind<<s->level<<s->type<<s->attr<<endl;
        current_table->addSymbol(*s);
   		delete(s);
    }
    else{
    	if(isparameter){
        	SymbolEntry* s = new SymbolEntry(m->variable_name, "parameter", level, m->getType(), "");
        	current_table->addSymbol(*s);
        // cout<<s->name<<" "<<s->kind<<s->level<<s->type<<s->attr<<endl;       	

        	delete(s);

    	}
    	else{
			SymbolEntry* s = new SymbolEntry(m->variable_name, "variable", level, m->getType(), "");
        	current_table->addSymbol(*s);
        // cout<<s->name<<" "<<s->kind<<s->level<<s->type<<s->attr<<endl;       	

   			delete(s);

    	}
    }
}

void SemanticAnalyzer::visit(ConstantValueNode *m) {
	current_entry->attr = m->getValue();
	// cout<<current_entry->name<<" "<<current_entry->kind<<current_entry->level<<current_entry->type<<current_entry->attr<<endl;
}

void SemanticAnalyzer::visit(FunctionNode *m) {
	// get the function return type
    string function_type;
    switch(m->return_type->type_set){
        case SET_SCALAR:
            switch(m->return_type->type){
                case TYPE_INTEGER: function_type = "integer"; break;
                case TYPE_REAL:    function_type = "real"; break;
                case TYPE_STRING:  function_type = "string"; break;
                case TYPE_BOOLEAN: function_type = "boolean"; break;
                default:           function_type = "unknown"; break;
            }
            break;
        case UNKNOWN_SET:
            switch(m->return_type->type){
                case TYPE_VOID: function_type = "void"; break;
                default:        function_type = "unknown"; break;
            }
            break;
        default: function_type = "unknown"; break; break;
    }
    string attr;
 	for(uint i=0; i<m->prototype.size(); i++){
        int first_bracket = 1;
        if(i != 0) attr += ", ";
        switch(m->prototype[i]->type_set){
            case SET_SCALAR:
            case SET_CONSTANT_LITERAL:
                switch(m->prototype[i]->type){
                    case TYPE_INTEGER: attr += "integer"; break;
                    case TYPE_REAL:    attr += "real"; break;
                    case TYPE_STRING:  attr += "string"; break;
                    case TYPE_BOOLEAN: attr += "boolean"; break;
                    default:           std::cout<<"unknown"; break;
                }
                break;
            case SET_ACCUMLATED:
                switch(m->prototype[i]->type){
                    case TYPE_INTEGER: attr += "integer"; break;
                    case TYPE_REAL:    attr += "real"; break;
                    case TYPE_STRING:  attr += "string"; break;
                    case TYPE_BOOLEAN: attr += "boolean"; break;
                    default:           std::cout<<"unknown"; break;
                }

                for(uint j=0; j<m->prototype[i]->array_range.size(); j++){
                    if(first_bracket){
                        attr += " [";
                        first_bracket = 0;
                    }
                    else
                        attr += "[";
                    attr += to_string(m->prototype[i]->array_range[j].end-m->prototype[i]->array_range[j].start);
                    attr += "]";
                }
                break;
            default: std::cout<<"unknown"; break;
        }
    }
    // std::cout<<m->function_name<<" " <<attr;
    SymbolEntry* s = new SymbolEntry(m->function_name, "function", level, function_type,attr);
    current_table->addSymbol(*s);
    delete(s);
    manager.pushScope(*current_table);

    // create the next table
    // level++;
    SymbolTable* temp_table = new SymbolTable;
    current_table = temp_table;
    if (m->parameters != nullptr){
    	isparameter = 1;
        level++;
    	for(uint i=0; i< m->parameters->size(); i++){
            (*(m->parameters))[i]->node->accept(*this);
        }
        level--;
    }
    isparameter = 0;
    if (m->body != nullptr){
        function_cmp = 1;
        m->body->accept(*this);
    }
    

    // level--;
    // manager.pushScope(*current_table);
}

void SemanticAnalyzer::visit(CompoundStatementNode *m) {
    level++;
    // if(function_cmp){
    //     level--;
    // }
    if (m->declaration_node_list != nullptr){

        if(!function_cmp){
            SymbolTable* temp_table = new SymbolTable;
            current_table = temp_table;
        }
        
    	for(uint i=0; i< m->declaration_node_list->size(); i++){
            (*(m->declaration_node_list))[i]->accept(*this);
        }
        function_cmp = 0;

    }
    manager.pushScope(*current_table);
        
    if (m->statement_node_list != nullptr){
    	for(uint i=0; i< m->statement_node_list->size(); i++){
            (*(m->statement_node_list))[i]->accept(*this);
        }
    }
    level--;
    manager.popScope();


}

void SemanticAnalyzer::visit(AssignmentNode *m) {}

void SemanticAnalyzer::visit(PrintNode *m) {}

void SemanticAnalyzer::visit(ReadNode *m) {}

void SemanticAnalyzer::visit(VariableReferenceNode *m) {}

void SemanticAnalyzer::visit(BinaryOperatorNode *m) {}

void SemanticAnalyzer::visit(UnaryOperatorNode *m) {}

void SemanticAnalyzer::visit(IfNode *m) {}

void SemanticAnalyzer::visit(WhileNode *m) {}

void SemanticAnalyzer::visit(ForNode *m) {}

void SemanticAnalyzer::visit(ReturnNode *m) {}

void SemanticAnalyzer::visit(FunctionCallNode *m) {}
