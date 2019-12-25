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
int is_array_var = 0;
int lack_attr = 0;
extern int error_found;
extern long long int count_line[1000] ;
extern char *file_name;;
SymbolManager manager;


SymbolTable* current_table;
SymbolEntry* current_entry;

bool check_declared_reference(string id){
    // SymbolManager temp;
    std::stack <SymbolTable> temp_manager_stack;
    bool find = false;
    while(manager.tables.size()!=0){
        SymbolTable temp = manager.tables.top();
        manager.tables.pop();
        for(int j=0; j<temp.entries.size(); j++){
            if(temp.entries[j].name==id){
                find = true;
            }
        // cout<<temp.entries[j].name<<"current "<<j<< " "<<temp.entries.size()<<endl;

        }
        // printf("1111");

        temp_manager_stack.push(temp);
    }

    while(!temp_manager_stack.empty()){
        SymbolTable temp = temp_manager_stack.top();
        temp_manager_stack.pop();
        manager.tables.push(temp);
    }

    return find;
}



void print_tab(int n){
    for(int i=0; i<n; i++){
         fprintf(stderr, " ");
    }
}

void print_error_code(int end_line_number, int end_col_number){
    FILE *fp = fopen(file_name, "r");  
    char code [1000];
    fseek ( fp , count_line[end_line_number-1] , SEEK_SET );
    fgets (code , 1000 , fp);
    print_tab(4); 
    fprintf(stderr, "%s",code);
    print_tab(4 + end_col_number-1); 
    fprintf(stderr, "%c\n",'^');
    fclose (fp);
    error_found = 1;

}


void SemanticAnalyzer::visit(ProgramNode *m) {
    // string temp = "./test-cases/"+m->program_name + ".p";
    // string temp = m->program_name + ".p";


    // Here need to restore!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    // if(strcmp(temp.c_str(), file_name)){
    //     fprintf(stderr, "<Error> Found in line %d, column %d: program name must be the same as filename\n", m->line_number, m->col_number);
    //     print_error_code(m->line_number, m->col_number);
    // }

    SymbolEntry* s = new SymbolEntry(m->program_name.substr(0,31), "program", level, "void", "");
    SymbolTable* first = new SymbolTable;
    first->addSymbol(*s);
    current_table = first;
    delete(s);
    if (m->declaration_node_list != nullptr){
        for(uint i=0; i< m->declaration_node_list->size(); i++){
            (*(m->declaration_node_list))[i]->accept(*this);
        }
    }
        

    if (m->function_node_list != nullptr){
        for(uint i=0; i< m->function_node_list->size(); i++){
            (*(m->function_node_list))[i]->accept(*this);
            if(i!=m->function_node_list->size()-1){
                manager.tables.pop();
                current_table = first;
            }
        }
    }
    // i forget why
    if (m->function_node_list == nullptr){
        manager.pushScope(*current_table);
    }

    if (m->compound_statement_node != nullptr){
        SymbolTable* temp_table = new SymbolTable;
        current_table = temp_table;
        m->compound_statement_node->accept(*this);
    }
    // std::cout<<check_declared_reference("fun");

    manager.popScope();

    // if(strcmp(m->program_name.c_str(), m->end_name.c_str())){
    //     fprintf(stderr, "<Error> Found in line %d, column %d: identifier at the end of program must be the same as identifier at the beginning of program\n", m->end_line_number, m->end_col_number);
    //     print_error_code(m->end_line_number, m->end_col_number);
    // }
}

void SemanticAnalyzer::visit(DeclarationNode *m) {
    if (m->variables_node_list != nullptr)
        for(uint i=0; i< m->variables_node_list->size(); i++){
            (*(m->variables_node_list))[i]->accept(*this);
        }
}

void SemanticAnalyzer::visit(VariableNode *m) {
    int declared = 0;
    for(int i=0; i<current_table->entries.size(); i++){
        declared = (m->variable_name.substr(0,31) ==current_table->entries[i].name) ? 1 :0;
        if(declared){
            fprintf(stderr, "<Error> Found in line %d, column %d: symbol %s is redeclared \n", m->line_number, m->col_number, m->variable_name.c_str());
            print_error_code(m->line_number, m->col_number);
            return;
        }
    }
    if(m->type->array_range.size()!=0){
        for(int i=0; i<m->type->array_range.size(); i++){
            if(m->type->array_range[i].start<0 || m->type->array_range[i].end<0 || m->type->array_range[i].start > m->type->array_range[i].end){
                fprintf(stderr, "<Error> Found in line %d, column %d: symbol %s declared as an array with a lower bound greater or equal to upper bound \n", m->line_number, m->col_number, m->variable_name.c_str());
                print_error_code(m->line_number, m->col_number);
                return;
            }
        }
    }
    // constant value
    if (m->constant_value_node != nullptr){
        SymbolEntry* s = new SymbolEntry(m->variable_name.substr(0,31), "constant", level, m->getType(), "");
        current_entry = s;
        // cout<<s->name<<" "<<s->kind<<s->level<<s->type<<s->attr<<endl;      
        lack_attr = 1;

        m->constant_value_node->accept(*this);

        lack_attr = 0;

        // cout<<s->name<<" "<<s->kind<<s->level<<s->type<<s->attr<<endl;
        current_table->addSymbol(*s);
        // cout<<current_table->entries[current_table->entries.size()-1].name<<current_table->entries[current_table->entries.size()-1].type<<endl;
        delete(s);
    }
    else{
        //function's parameter
        if(isparameter){
            SymbolEntry* s = new SymbolEntry(m->variable_name.substr(0,31), "parameter", level, m->getType(), "");
            current_table->addSymbol(*s);
        // cout<<s->name<<" "<<s->kind<<s->level<<s->type<<s->attr<<endl;           

            delete(s);

        }
        //normal variable
        else{
            SymbolEntry* s = new SymbolEntry(m->variable_name.substr(0,31), "variable", level, m->getType(), "");
            current_table->addSymbol(*s);
        // cout<<s->name<<" "<<s->kind<<s->level<<s->type<<s->attr<<endl;           

            delete(s);
        }
    }


}

void SemanticAnalyzer::visit(ConstantValueNode *m) {
    // cout<<"this constant is "<<m->getValue()<<endl;
    if(lack_attr)
	   current_entry->attr = m->getValue();
}

void SemanticAnalyzer::visit(FunctionNode *m) {
	// get the function return type
    if(strcmp(m->function_name.c_str(), m->end_name.c_str())){
        fprintf(stderr, "<Error> Found in line %d, column %d: identifier at the end of function must be the same as identifier at the beginning of function\n", m->end_line_number, m->end_col_number);
        print_error_code(m->end_line_number,m->end_col_number);
    }

    for(int i=0; i<current_table->entries.size(); i++){
        if(m->function_name.substr(0,31) ==current_table->entries[i].name){
            fprintf(stderr, "<Error> Found in line %d, column %d: symbol %s is redeclared \n", m->line_number, m->col_number, m->function_name.c_str());
            print_error_code(m->line_number, m->col_number);
            manager.pushScope(*current_table);
            break;
        }
    }

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

    SymbolEntry* s = new SymbolEntry(m->function_name.substr(0,31), "function", level, function_type,attr);
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
}

void SemanticAnalyzer::visit(CompoundStatementNode *m) {
    level++;

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

void SemanticAnalyzer::visit(AssignmentNode *m) {

    if (m->variable_reference_node != nullptr)
        m->variable_reference_node->accept(*this);

    if (m->expression_node != nullptr)
        m->expression_node->accept(*this);
}

void SemanticAnalyzer::visit(PrintNode *m) {
    if (m->expression_node != nullptr){
         m->expression_node->accept(*this);
    }
}

void SemanticAnalyzer::visit(ReadNode *m) {
    if (m->variable_reference_node != nullptr)
        m->variable_reference_node->accept(*this);    
}

void SemanticAnalyzer::visit(VariableReferenceNode *m) {
    // cout<<"this variable is " <<m->variable_name<<endl;

    if(!check_declared_reference(m->variable_name)){
        cout<<"this is variable reference: "<<m->variable_name<<endl;
        fprintf(stderr, "<Error> Found in line %d, column %d: use of undeclared identifier %s\n", m->line_number, m->col_number, m->variable_name.c_str());
        print_error_code(m->line_number, m->col_number);
        //fix
        return;
    }
    // if(is_array_var){
        // std::cout<<m->variable_name<<endl;

    // }
    if (m->expression_node_list != nullptr){
        for(uint i=0; i< m->expression_node_list->size(); i++){
            // is_array_var = 1;
            // std::cout<<"["<<std::endl;
            (*(m->expression_node_list))[i]->accept(*this);

            // std::cout<<"]"<<std::endl;
            // is_array_var = 0;
        }
     }
}

void SemanticAnalyzer::visit(BinaryOperatorNode *m) {
    if (m->left_operand != nullptr)
            m->left_operand->accept(*this);

    if (m->right_operand != nullptr)
        m->right_operand->accept(*this);
}

void SemanticAnalyzer::visit(UnaryOperatorNode *m) {
    if (m->operand != nullptr)
        m->operand->accept(*this);
}

void SemanticAnalyzer::visit(IfNode *m) {
    if (m->condition != nullptr)
            m->condition->accept(*this);

    if (m->body != nullptr)
        for(uint i=0; i< m->body->size(); i++)
            (*(m->body))[i]->accept(*this);

    if (m->body_of_else != nullptr){
        this->print_space();
        std::cout<<"else"<<std::endl;

        this->space_counter_increase();
            for(uint i=0; i< m->body_of_else->size(); i++)
                (*(m->body_of_else))[i]->accept(*this);
        this->space_counter_decrease();
    }
}

void SemanticAnalyzer::visit(WhileNode *m) {
     if (m->condition != nullptr)
            m->condition->accept(*this);

    if (m->body != nullptr)
        for(uint i=0; i< m->body->size(); i++)
            (*(m->body))[i]->accept(*this);
}

void SemanticAnalyzer::visit(ForNode *m) {
    if (m->loop_variable_declaration != nullptr)
            m->loop_variable_declaration->accept(*this);
        
    if (m->initial_statement != nullptr)
        m->initial_statement->accept(*this);

    if (m->condition != nullptr)
        m->condition->accept(*this);

    if (m->body != nullptr)
        for(uint i=0; i< m->body->size(); i++)
            (*(m->body))[i]->accept(*this);
}

void SemanticAnalyzer::visit(ReturnNode *m) {
    if (m->return_value != nullptr)
        m->return_value->accept(*this);
}

void SemanticAnalyzer::visit(FunctionCallNode *m) {
    if (m->arguments != nullptr)
        for(uint i=0; i< m->arguments->size(); i++)
            (*(m->arguments))[i]->accept(*this);
}
