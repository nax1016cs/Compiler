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

std:: stack <string> current_type;
int set_error = 0;
int check_return = 0;
int set_error_num = 0;
int isparameter = 0;
int level = 0;
int function_cmp = 0;
int is_array_var = 0;
int lack_attr = 0;
int is_assignment = 0;
int array_int_error = 0;
string return_type ;
extern int error_found;
extern long long int count_line[1000] ;
extern char *file_name;;
SymbolManager manager;


SymbolTable* current_table;
SymbolEntry* current_entry;

void clear_the_stack(){
    while(!current_type.empty()){
        current_type.pop();
    }
}


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
        }
        temp_manager_stack.push(temp);
    }
    while(!temp_manager_stack.empty()){
        SymbolTable temp = temp_manager_stack.top();
        temp_manager_stack.pop();
        manager.tables.push(temp);
    }
    return find;
}

// 0 for kind , 1 for type
string find_type_or_kind(string id, int type_or_kind){
    // SymbolManager temp;
    std::stack <SymbolTable> temp_manager_stack;
    bool find = false;
    string ans_type;
    string ans_kind;
    while(manager.tables.size()!=0){
        SymbolTable temp = manager.tables.top();
        manager.tables.pop();
        for(int j=0; j<temp.entries.size(); j++){
            if(temp.entries[j].name==id){
                ans_type = temp.entries[j].type;
                ans_kind = temp.entries[j].kind;
                // cout<<"type: "<< ans_type<<" kind: "<<ans_kind<<endl;
            }
        }
        temp_manager_stack.push(temp);
    }

    while(!temp_manager_stack.empty()){
        SymbolTable temp = temp_manager_stack.top();
        temp_manager_stack.pop();
        manager.tables.push(temp);
    }
    if(type_or_kind) 
        return ans_type;
    return ans_kind;
}


void print_tab(int n){
    for(int i=0; i<n; i++){
         fprintf(stderr, " ");
    }
}

void print_error_code(int line_number, int col_number, int error_num, string s1, string s2, string s3){
    switch(error_num){
        case 1:
            fprintf(stderr, "<Error> Found in line %d, column %d: program name must be the same as filename\n", line_number, col_number);
            break;
        case 2:
            fprintf(stderr, "<Error> Found in line %d, column %d: identifier at the end of program must be the same as identifier at the beginning of program\n", line_number, col_number);
            break;
        case 3:
            fprintf(stderr, "<Error> Found in line %d, column %d: symbol '%s' is redeclared \n", line_number, col_number, s1.c_str());
            break;
        case 4:
            fprintf(stderr, "<Error> Found in line %d, column %d: symbol '%s' declared as an array with a lower bound greater or equal to upper bound \n", line_number, col_number, s1.c_str());
            break;
        case 5:
            fprintf(stderr, "<Error> Found in line %d, column %d: identifier at the end of function must be the same as identifier at the beginning of function\n", line_number,col_number);
            break;
        case 6:
            fprintf(stderr, "<Error> Found in line %d, column %d: symbol '%s' is redeclared \n", line_number, col_number, s1.c_str());
            break;
        case 7:
            fprintf(stderr, "<Error> Found in line %d, column %d: array assignment is not allowed\n", line_number, col_number);
            break;
        case 8:
            fprintf(stderr, "<Error> Found in line %d, column %d: cannot assign to variable '%s' which is a constant\n", line_number, col_number, s1.c_str());
            break;
        case 9:
            fprintf(stderr, "<Error> Found in line %d, column %d: the value of loop variable cannot be modified inside the loop\n", line_number, col_number);
            break;
        case 10:
            fprintf(stderr, "<Error> Found in line %d, column %d: use of undeclared identifier '%s'\n", line_number, col_number, s1.c_str());
            break;
        case 11:
            fprintf(stderr, "<Error> Found in line %d, column %d: there is an over array subscript\n", line_number, col_number);
            break;
        case 12:
            fprintf(stderr, "<Error> Found in line %d, column %d: index of array reference must be an integer \n", line_number,col_number);
            break;
        case 13:
            fprintf(stderr, "<Error> Found in line %d, column %d: invalid operands to binary operation '%s' ('%s' and '%s')\n", line_number, col_number,s1.c_str(), s2.c_str(), s3.c_str() );
            break;
        case 14:
            fprintf(stderr, "<Error> Found in line %d, column %d: invalid operand to unary operation '%s' ('%s')\n", line_number, col_number,s1.c_str(), s2.c_str() );
            break;
        case 15:
            fprintf(stderr, "<Error> Found in line %d, column %d:  program/procedure should not return a value\n", line_number, col_number);
            break;
        case 16:
            fprintf(stderr, "<Error> Found in line %d, column %d:  return '%s' from a function with return type '%s'\n", line_number, col_number, s1.c_str(), s2.c_str());
            break;
        case 17:
            fprintf(stderr, "<Error> Found in line %d, column %d:  assigning to '%s' from incompatible type '%s'\n", line_number, col_number, s1.c_str(), s2.c_str());
        	break;

    }
    FILE *fp = fopen(file_name, "r");  
    char code [1000];
    fseek ( fp , count_line[line_number-1] , SEEK_SET );
    fgets (code , 1000 , fp);
    print_tab(4); 
    fprintf(stderr, "%s",code);
    print_tab(4 + col_number-1); 
    fprintf(stderr, "%c\n",'^');
    fclose (fp);
    error_found = 1;

}


void SemanticAnalyzer::visit(ProgramNode *m) {
    string temp = "./test-cases/"+m->program_name + ".p";
    // string temp = m->program_name + ".p";


    // Here need to restore!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    if(strcmp(temp.c_str(), file_name)){
        print_error_code(m->line_number, m->col_number, 1 , "", "", "");
    }

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

    if(strcmp(m->program_name.c_str(), m->end_name.c_str())){
        print_error_code(m->end_line_number, m->end_col_number, 2 , "", "", "");
    }
}

void SemanticAnalyzer::visit(DeclarationNode *m) {
    if (m->variables_node_list != nullptr)
        for(uint i=0; i< m->variables_node_list->size(); i++){
            (*(m->variables_node_list))[i]->accept(*this);
        }
    // clear_the_stack();
}

void SemanticAnalyzer::visit(VariableNode *m) {
    int declared = 0;

    // redeclared
    for(int i=0; i<current_table->entries.size(); i++){
        declared = (m->variable_name.substr(0,31) ==current_table->entries[i].name) ? 1 :0;
        if(declared){
            print_error_code(m->line_number, m->col_number, 3 , m->variable_name, "", "");
            return;
        }
    }
    if(m->type->array_range.size()!=0){
        for(int i=0; i<m->type->array_range.size(); i++){
            if(m->type->array_range[i].start<0 || m->type->array_range[i].end<0 || m->type->array_range[i].start >= m->type->array_range[i].end){
                print_error_code(m->line_number, m->col_number, 4 , m->variable_name, "", "");
                return;
            }
        }
    }
    // constant value
    if (m->constant_value_node != nullptr){
        SymbolEntry* s = new SymbolEntry(m->variable_name.substr(0,31), "constant", level, m->getType(), "");
        current_entry = s;    
        lack_attr = 1;
        m->constant_value_node->accept(*this);
        lack_attr = 0;
        current_table->addSymbol(*s);
        delete(s);
    }
    else{
        //function's parameter
        if(isparameter){
            SymbolEntry* s = new SymbolEntry(m->variable_name.substr(0,31), "parameter", level, m->getType(), "");
            current_table->addSymbol(*s);           
            delete(s);
        }
        //normal variable
        else{
            SymbolEntry* s = new SymbolEntry(m->variable_name.substr(0,31), "variable", level, m->getType(), "");
            current_table->addSymbol(*s);         
            delete(s);
        }
    }
    // clear_the_stack();

}

void SemanticAnalyzer::visit(ConstantValueNode *m) {
    if(lack_attr)
	   current_entry->attr = m->getValue();
    string attr;
    switch(m->constant_value->type){
        case TYPE_INTEGER: attr = "integer" ; break;
        case TYPE_REAL:    attr = "real"; break;
        case TYPE_STRING:  attr = "string"; break;
        case TYPE_BOOLEAN: attr = "boolean"; break;
        default: std::cout << "unknown"; break;
    }
    current_type.push(attr);
}

void SemanticAnalyzer::visit(FunctionNode *m) {
	// get the function return type

    // cout<<"the return type is "<<return_type<<endl;
    if(strcmp(m->function_name.c_str(), m->end_name.c_str())){
        print_error_code(m->end_line_number,m->end_col_number, 5 , "", "", "");
    }

    for(int i=0; i<current_table->entries.size(); i++){
        if(m->function_name.substr(0,31) ==current_table->entries[i].name){
            print_error_code(m->line_number, m->col_number, 6 , m->function_name, "", "");
            manager.pushScope(*current_table);
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
    check_return = 1;
    return_type = find_type_or_kind(m->function_name, 1);
    if (m->body != nullptr){
        function_cmp = 1;
        m->body->accept(*this);
    }

    // clear_the_stack();
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
    // clear_the_stack();


}

void SemanticAnalyzer::visit(AssignmentNode *m) {

    if (m->variable_reference_node != nullptr){
        is_assignment = 1;
        m->variable_reference_node->accept(*this);
    }
    if(is_assignment!=1){
        return ;
    }
    is_assignment = 0;

    if (m->expression_node != nullptr){
        // is_assignment = 1;
        m->expression_node->accept(*this);
    }
    // clear_the_stack();
    string first = current_type.top();
    current_type.pop();
    string second = current_type.top();
    current_type.pop();
    if(first!=second) {
        print_error_code(m->line_number, m->col_number, 17 , second, first, "");
    }
}

void SemanticAnalyzer::visit(PrintNode *m) {
    if (m->expression_node != nullptr){
         m->expression_node->accept(*this);
    }
    // clear_the_stack();

}

void SemanticAnalyzer::visit(ReadNode *m) {
    if (m->variable_reference_node != nullptr)
        m->variable_reference_node->accept(*this);
    string type = current_type.top();

    // clear_the_stack();
}

void SemanticAnalyzer::visit(VariableReferenceNode *m) {
    // cout<<"this variable is " <<m->variable_name<<" and its type is "<<m->getType()<<endl;
    if(is_assignment){
        string type_finding = find_type_or_kind(m->variable_name, 0);
        string kind_finding = find_type_or_kind(m->variable_name, 1);
        size_t found = kind_finding.find('[');
        if(found !=std::string::npos){
            print_error_code(m->line_number, m->col_number, 7, "", "", "");
            is_assignment = 0;
            return;           
        }
        else if( type_finding == "constant"){
            print_error_code(m->line_number, m->col_number, 8 , m->variable_name, "", "");
            is_assignment = 0;
            return;
        }
        else if(type_finding == "loop_var"){
            print_error_code(m->line_number, m->col_number, 9 ,"", "", "");
            is_assignment = 0;
            return;            
        }

    }
    if(!check_declared_reference(m->variable_name)){
        // cout<<"this is variable reference: "<<m->variable_name<<endl;
        print_error_code(m->line_number, m->col_number, 10 , m->variable_name, "", "");
        return;
    }

    if (m->expression_node_list != nullptr){
        int count_bracket = 0;
        string ans = find_type_or_kind(m->variable_name,1);
        for(uint i=0; i< m->expression_node_list->size(); i++){
            (*(m->expression_node_list))[i]->accept(*this);
                string arr_type = current_type.top();
                if(arr_type != "integer"){
                    set_error = 1;
                    print_error_code(m->line_number, m->col_number, 12 , "", "", "");
                    current_type.push("error");
                    return;
                } 
        }
        for(int i=0; i<ans.size(); i++){
            if(ans[i]=='[') count_bracket++;
        }
        if(m->expression_node_list->size() > count_bracket ){
            print_error_code(m->line_number, m->col_number, 11, "", "", "");
            return;
        }
        
    }
    string t = find_type_or_kind(m->variable_name, 1);
    current_type.push(t);


}

void SemanticAnalyzer::visit(BinaryOperatorNode *m) {

    if (m->left_operand != nullptr)
        m->left_operand->accept(*this);

    if (m->right_operand != nullptr)
        m->right_operand->accept(*this);

    string first = current_type.top();
    current_type.pop();
    string second = current_type.top();
    current_type.pop(); 
    if(first == "error" || second =="error"){
        current_type.push("error");
        return;
    }
    int error = 0;
    string operation;
    switch(m->op){
        case OP_OR:               
            operation = "or"; 
            if(first != "boolean" || second != "boolean"){
                error = 1;
                current_type.push("error");

            }
            else{
                current_type.push("boolean");
            }
            break;
        case OP_AND:              
            operation = "and"; 
            if(first != "boolean" || second != "boolean"){
                error = 1;
                current_type.push("error");
            }
            else{
                current_type.push("boolean");
            }
            break;
        case OP_LESS:             
            operation = "<"; 
            if( !((first == "integer" || first == "real") && (second == "integer" || second == "real")) ){
                error = 1;
                current_type.push("error");
            }
            else{
                current_type.push("boolean");
            }
            break;            
        case OP_LESS_OR_EQUAL:    
            operation = "<="; 
            if( !((first == "integer" || first == "real") && (second == "integer" || second == "real")) ){
                error = 1;
                current_type.push("error");
            }
            else{
                current_type.push("boolean");
            }
            break; 
        case OP_EQUAL:            
            operation = "="; 
            if( !((first == "integer" || first == "real") && (second == "integer" || second == "real")) ){
                error = 1;
                current_type.push("error");
            }
            else{
                current_type.push("boolean");
            }
            break; 
        case OP_GREATER:          
            operation = ">"; 
            if( !((first == "integer" || first == "real") && (second == "integer" || second == "real")) ){
                error = 1;
                current_type.push("error");
            }
            else{
                current_type.push("boolean");
            }
            break; 
        case OP_GREATER_OR_EQUAL: 
            operation = ">="; 
            if( !((first == "integer" || first == "real") && (second == "integer" || second == "real")) ){
                error = 1;
                current_type.push("error");
            }
            else{
                current_type.push("boolean");
            }
            break; 
        case OP_NOT_EQUAL:        
            operation = "<>"; 
            if( !((first == "integer" || first == "real") && (second == "integer" || second == "real")) ){
                error = 1;
                current_type.push("error");
            }
            else{
                current_type.push("boolean");
            }
            break; 
        case OP_PLUS:             
            operation = "+"; 
            if( !((first == "integer" || first == "real") && (second == "integer" || second == "real")) ){
                if(first == "string" && second == "string"){
                    current_type.push("string");
                }
                else{
                    error = 1;
                    current_type.push("error");
                }
            }
            else{
                if(first == "real" || second == "real"){
                    current_type.push("real");
                }
                else{
                    current_type.push("integer");
                }
            }
            break; 
        case OP_MINUS:            
            operation = "-"; 
            if( !((first == "integer" || first == "real") && (second == "integer" || second == "real")) ){
                error = 1;
                current_type.push("error");
            }
            else{
                if(first == "real" || second == "real"){
                    current_type.push("real");
                }
                else{
                    current_type.push("integer");
                }
            }
            break;             
        case OP_MULTIPLY:         
            operation = "*"; 
            if( !((first == "integer" || first == "real") && (second == "integer" || second == "real")) ){
                error = 1;
                current_type.push("error");
            }
            else{
                if(first == "real" || second == "real"){
                    current_type.push("real");
                }
                else{
                    current_type.push("integer");
                }
            }
            break;             
        case OP_DIVIDE:           
            operation = "/"; 
            if( !((first == "integer" || first == "real") && (second == "integer" || second == "real")) ){
                error = 1;
                current_type.push("error");
            }
            else{
                if(first == "real" || second == "real"){
                    current_type.push("real");
                }
                else{
                    current_type.push("integer");
                }
            }
            break;             
        case OP_MOD:              
            operation = "mod"; 
            if(first!= "integer" || second!= "integer"){
                error = 1;
                current_type.push("error");
            }
            else{
                current_type.push("integer");
            }
            break;
        default:                 
            operation = "unknown"; break;
    }
    if(error){
        print_error_code(m->line_number, m->col_number, 13, operation, second, first);
    }
                // cout<<current_type.top();

    // a[ b + c]
    // (456 + 123) + "str"
}

void SemanticAnalyzer::visit(UnaryOperatorNode *m) {
    // not
    if (m->operand != nullptr){
        m->operand->accept(*this);
    }
    string first = current_type.top();
    current_type.pop();
    string operation;
    int error = 0;
    switch(m->op){
        case OP_NOT:               
            operation = "not"; 
            if(first != "boolean"){
                error = 1;
                current_type.push("error");
            }
            else{
                current_type.push("boolean");
            }
            break;
        case OP_MINUS:              
            operation = "neg"; 
            if( !(first == "integer" || first == "real")  ){
                error = 1;
                current_type.push("error");
            }
            else{
                if(first == "real"){
                    current_type.push("real");
                }
                else{
                    current_type.push("integer");
                }
            }
            break;         
        default:                 
            operation = "unknown"; break;
    }
    if(error){
        print_error_code(m->line_number, m->col_number, 14, operation, first, "");
    }
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
    if(!check_return){
        print_error_code(m->line_number, m->col_number, 15, "", "", "");
        return;
    }
    if (m->return_value != nullptr)
        m->return_value->accept(*this);
    // cout<<"return value:"<<return_type<<endl;
    if(check_return && return_type !=  current_type.top() && current_type.top() != "error"){
        check_return = 0;
        print_error_code(m->line_number, m->col_number, 16 , current_type.top(), return_type, "");
    } 
}

void SemanticAnalyzer::visit(FunctionCallNode *m) {
    if (m->arguments != nullptr)
        for(uint i=0; i< m->arguments->size(); i++)
            (*(m->arguments))[i]->accept(*this);
}
