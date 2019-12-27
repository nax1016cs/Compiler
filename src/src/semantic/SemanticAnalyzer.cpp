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
#include <vector>
using namespace std;

std:: stack <string> current_type;
std:: stack <int > return_available;
string var_type;
string var_kind;

int state = 0;
int loop_error = 0;
int fun_redeclared = 0;
int find_next_col = 0;
int record_col = 0;
int first_int = -999999999;
int second_int = -999999999;
int isloop = 0;
int var_scalar = 1;
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
extern char *file_name;
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

// 0 for kind , 1 for type, 2 for attr
string find_type_or_kind(string id, int type_or_kind){
    // SymbolManager temp;
    std::stack <SymbolTable> temp_manager_stack;
    bool find = false;
    string ans_type;
    string ans_kind;
    string ans_attr;
    while(manager.tables.size()!=0){
        SymbolTable temp = manager.tables.top();
        manager.tables.pop();
        for(int j=0; j<temp.entries.size(); j++){
            if(temp.entries[j].name==id){
                ans_type = temp.entries[j].type;
                ans_kind = temp.entries[j].kind;
                ans_attr = temp.entries[j].attr;

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
    if(type_or_kind == 0) 
        return ans_kind ;
    else if(type_or_kind == 1) 
        return ans_type;
    return ans_attr;
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
            fprintf(stderr, "<Error> Found in line %d, column %d: symbol '%s' is redeclared \n", line_number, col_number, s1.substr(0,32).c_str());
            break;
        case 4:
            fprintf(stderr, "<Error> Found in line %d, column %d: '%s' declared as an array with a lower bound greater or equal to upper bound \n", line_number, col_number, s1.c_str());
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
            fprintf(stderr, "<Error> Found in line %d, column %d: program/procedure should not return a value\n", line_number, col_number);
            break;
        case 16:
            fprintf(stderr, "<Error> Found in line %d, column %d: return '%s' from a function with return type '%s'\n", line_number, col_number, s1.c_str(), s2.c_str());
            break;
        case 17:
            fprintf(stderr, "<Error> Found in line %d, column %d: assigning to '%s' from incompatible type '%s'\n", line_number, col_number, s1.c_str(), s2.c_str());
        	break;
        case 18:
            fprintf(stderr, "<Error> Found in line %d, column %d: the expression of condition must be boolean type\n", line_number, col_number);
            break;
        case 19:
            fprintf(stderr, "<Error> Found in line %d, column %d: variable reference of print statement must be scalar type\n", line_number, col_number);
            break;
        case 20:
            fprintf(stderr, "<Error> Found in line %d, column %d: variable reference of read statement cannot be a constant variable reference\n", line_number, col_number);
            break;
        case 21:
            fprintf(stderr, "<Error> Found in line %d, column %d: the value of loop variable cannot be modified inside the loop\n", line_number, col_number);
            break;
        case 22:
            fprintf(stderr, "<Error> Found in line %d, column %d: variable reference of read statement must be scalar type\n", line_number, col_number);
            break;    
        case 23:
            fprintf(stderr, "<Error> Found in line %d, column %d: variable reference of print statement must be scalar type\n", line_number, col_number);
            break;              
        case 24:
            fprintf(stderr, "<Error> Found in line %d, column %d: the lower bound of iteration count must be smaller than or equal to the upper bound\n", line_number, col_number);
            break;
        case 25:
            fprintf(stderr, "<Error> Found in line %d, column %d: used of undeclared function '%s'\n", line_number, col_number,s1.c_str());
            break;
        case 26:
            fprintf(stderr, "<Error> Found in line %d, column %d: too few/much arguments to function invocation\n", line_number, col_number);
            break;
        case 27:
            fprintf(stderr, "<Error> Found in line %d, column %d: incompatible types passing '%s' to parameter of type '%s'\n", line_number, col_number,s1.c_str(),s2.c_str());
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
    while(!return_available.empty()) return_available.pop();
    // string temp = "./test-cases/"+m->program_name + ".p";
    string temp = "";
    // string temp = m->program_name + ".p";
    for(int i=0; i<strlen(file_name); i++){
        temp += file_name[i];
        if(i>0 && file_name[i] == '/'){
            temp.clear();
        }
    }
    temp = temp.substr(0, temp.size()-2);
    // cout<<"ffffffffffff"<<temp;
    // Here need to restore!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    if(strcmp(temp.c_str(), m->program_name.c_str())){
        print_error_code(m->line_number, m->col_number, 1 , "", "", "");
    }

    SymbolEntry* s = new SymbolEntry(m->program_name.substr(0,32), "program", level, "void", "");
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
    // cout<<m->variable_name<<endl;

    if(fun_redeclared){
        fun_redeclared =0;
        return;
    }
    // redeclared
    string var_kind = find_type_or_kind(m->variable_name, 0);
    if(var_kind == "loop_var"){
        print_error_code(m->line_number, m->col_number, 3 , m->variable_name, "", "");
        loop_error = 1;
        // cout<<"loop redesdssssssssss";
        // current_type.push("error");
        return;
    }
    for(int i=0; i<current_table->entries.size(); i++){
        // cout<<"this is "<<m->variable_name<<endl;
        // cout<<"the check var is "<< current_table->entries[i].name<<endl;
        declared = (m->variable_name.substr(0,32) ==current_table->entries[i].name) ? 1 :0;
        if(declared){
            // cout<<"dddddddddddd"<<endl;
            print_error_code(m->line_number, m->col_number, 3 , m->variable_name, "", "");
            // current_type.push("error");
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
        SymbolEntry* s = new SymbolEntry(m->variable_name.substr(0,32), "constant", level, m->getType(), "");
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
            SymbolEntry* s = new SymbolEntry(m->variable_name.substr(0,32), "parameter", level, m->getType(), "");
            current_table->addSymbol(*s);           
            delete(s);
        }
        //normal variable
        else if(isloop){
            SymbolEntry* s = new SymbolEntry(m->variable_name.substr(0,32), "loop_var", level, m->getType(), "");
            current_table->addSymbol(*s);     
            delete(s);    

        }
        else{
            SymbolEntry* s = new SymbolEntry(m->variable_name.substr(0,32), "variable", level, m->getType(), "");
            current_table->addSymbol(*s);    
            delete(s);
        }
    }
    // clear_the_stack();

}

void SemanticAnalyzer::visit(ConstantValueNode *m) {
    record_col = m->col_number;

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
    if(isloop){
        if(first_int == -999999999){
            first_int = m->constant_value->int_literal;
        }
        else{
            second_int = m->constant_value->int_literal;
        }
    }
}

void SemanticAnalyzer::visit(FunctionNode *m) {
	// get the function return type
    // cout<<"the return type is "<<return_type<<endl;
    if(strcmp(m->function_name.c_str(), m->end_name.c_str())){
        print_error_code(m->end_line_number,m->end_col_number, 5 , "", "", "");
    }

    for(int i=0; i<current_table->entries.size(); i++){
        if(m->function_name.substr(0,32) ==current_table->entries[i].name){
            print_error_code(m->line_number, m->col_number, 6 , m->function_name, "", "");
            // manager.pushScope(*current_table);
            // return;
            fun_redeclared = 1;
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
    if((strcmp(function_type.c_str(), "void")) ){
        return_available.push(1);
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

    SymbolEntry* s = new SymbolEntry(m->function_name.substr(0,32), "function", level, function_type,attr);
    current_table->addSymbol(*s);
    delete(s);
    if(!fun_redeclared)
        manager.pushScope(*current_table);
    fun_redeclared = 0;
    
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
    // check_return = 1;
    
    return_type = find_type_or_kind(m->function_name, 1);
    if (m->body != nullptr){
        function_cmp = 1;
        m->body->accept(*this);
    }
    // cout<<"111111"<<endl;
    if((strcmp(function_type.c_str(), "void")) ){
        return_available.pop();
    }
    // cout<<"111111"<<endl;
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

    string first = current_type.top();//expr
    current_type.pop();

    if(first =="error") return;

    if (m->expression_node != nullptr){
        is_assignment = 1;
        m->expression_node->accept(*this);
    }
    // clear_the_stack();
    
    string second = current_type.top();
    current_type.pop();
    if( second == "error") return;
    if(first!=second) {
        print_error_code(m->line_number, m->col_number, 17 , second, first, "");
    }
    if(isloop){
        current_type.push(first);
    }
}

void SemanticAnalyzer::visit(PrintNode *m) {
    var_scalar = 1;
    if (m->expression_node != nullptr){
         m->expression_node->accept(*this);
    }
    string temp = current_type.top();
    if(temp=="error") return;

    if(!var_scalar || temp == "void"){
        find_next_col = 1;
        if (m->expression_node != nullptr){
             m->expression_node->accept(*this);
        }
        print_error_code(m->line_number, record_col, 23 , "", "", "");
        var_scalar = 1;
        return;  
    }
    // clear_the_stack();

}

void SemanticAnalyzer::visit(ReadNode *m) {
    var_scalar = 1;
    var_kind = "";
    if (m->variable_reference_node != nullptr)
        m->variable_reference_node->accept(*this);
    string temp = current_type.top();
    if(temp == "error") return;
    if(var_kind == "constant"){
        find_next_col = 1;
        if (m->variable_reference_node != nullptr)
            m->variable_reference_node->accept(*this);
        print_error_code(m->line_number, record_col, 20 , "", "", "");
        var_scalar = 1;
        return;
    }
    else if(var_kind == "loop_var"){
        find_next_col = 1;
        if (m->variable_reference_node != nullptr)
            m->variable_reference_node->accept(*this);
        print_error_code(m->line_number, record_col, 21 , "", "", "");
        var_scalar = 1;
        return;  
    }
    else if(!var_scalar || temp == "void"){
        find_next_col = 1;
        if (m->variable_reference_node != nullptr)
            m->variable_reference_node->accept(*this);
        print_error_code(m->line_number, record_col, 22 , "", "", "");
        var_scalar = 1;
        return;  
    }


    // clear_the_stack();
}

void SemanticAnalyzer::visit(VariableReferenceNode *m) {
    // cout<<"this variable is " <<m->variable_name<<" and its type is "<<m->getType()<<endl;
    if(find_next_col){
        record_col = m->col_number;
        find_next_col = 0;
        return;
    }
    if(is_assignment){
        string type_finding = find_type_or_kind(m->variable_name, 0);
        string kind_finding = find_type_or_kind(m->variable_name, 1);
        size_t found = kind_finding.find('[');
        if(found !=std::string::npos){
            string temp = "";
            int ct=0;
            int append = 1;
            if(m->expression_node_list != nullptr){
                string temp = "";
                int ct=0;
                int append = 1;
                for(int i=0; i<kind_finding.size(); i++){
                    if(kind_finding[i] == '['){
                        if(ct < m->expression_node_list->size()){
                            append = 0;
                        }
                        else{
                            append = 1;
                        }
                    }
                    if(kind_finding[i] == ']'){
                        ct++;
                    }
                    if(append){
                        temp += kind_finding[i];
                    }
                }
                // cout<<temp<<endl;
                if(temp.find('[') == std::string::npos){
                    if(temp[temp.size()-1] == ' ') temp = temp.substr(0, temp.size()-1);
                }
                // cout<<temp;
                kind_finding = temp;
            }
            size_t tt = kind_finding.find('[');
            if(tt!=std::string::npos){
                print_error_code(m->line_number, m->col_number, 7, "", "", "");
                is_assignment = 0;
                current_type.push("error");
                return;
            }
                       
        }
        else if( type_finding == "constant"){
            print_error_code(m->line_number, m->col_number, 8 , m->variable_name, "", "");
            current_type.push("error");
            is_assignment = 0;
            return;
        }
        else if(type_finding == "loop_var" && !isloop){
            print_error_code(m->line_number, m->col_number, 9 ,"", "", "");
            is_assignment = 0;
            current_type.push("error");
            return;            
        }
    }
    if(!check_declared_reference(m->variable_name) ){
        // cout<<"this is variable reference: "<<m->variable_name<<endl;
        print_error_code(m->line_number, m->col_number, 10 , m->variable_name, "", "");
        current_type.push("error");
        return;
    }
    int count_bracket = 0;
    string ans = find_type_or_kind(m->variable_name,1);
    for(int i=0; i<ans.size(); i++){
        if(ans[i]=='[') count_bracket++;
    }
    if (m->expression_node_list != nullptr){
        for(uint i=0; i< m->expression_node_list->size(); i++){
            (*(m->expression_node_list))[i]->accept(*this);
                string arr_type = current_type.top();
                if(arr_type != "integer"){
                    // set_error = 1;
                    print_error_code(m->line_number, record_col, 12 , "", "", "");
                    current_type.push("error");
                    return;
                } 
        }

        if(m->expression_node_list->size() > count_bracket ){
            print_error_code(m->line_number, m->col_number, 11, "", "", "");
            current_type.push("error");
            return;
        }
        if(m->expression_node_list->size() != count_bracket ) var_scalar = 0;
    }
    else if (count_bracket){
        var_scalar = 0;
    }

    string t = find_type_or_kind(m->variable_name, 1);
    if(m->expression_node_list != nullptr){
        string temp = "";
        int ct=0;
        int append = 1;
        for(int i=0; i<t.size(); i++){
            // if(t[i]=='[') ct++;
            // if(ct == count_bracket - m->expression_node_list->size() +1 ) break;
            // if(t[i] != ' ')temp+=t[i];
            if(t[i] == '['){
                if(ct < m->expression_node_list->size()){
                    append = 0;
                }
                else{
                    append = 1;
                }
            }
            if(t[i] == ']'){
                ct++;
            }
            if(append){
                temp += t[i];
            }
        }
        // cout<<temp<<endl;
        if(temp.find('[') == std::string::npos){
            if(temp[temp.size()-1] == ' ') temp = temp.substr(0, temp.size()-1);
        }
        // cout<<temp;
        t = temp;
    }
    // cout<<t<<endl;
    // cout<<m->variable_name<<"type: "<<t<<endl;
    current_type.push(t);
    var_kind = find_type_or_kind(m->variable_name, 0);
    // cout<<m->variable_name <<" "<<var_kind<<endl;


}

void SemanticAnalyzer::visit(BinaryOperatorNode *m) {

    if(find_next_col){
        record_col = m->col_number;
        find_next_col = 0;
        return;
    }
    if (m->left_operand != nullptr)
        m->left_operand->accept(*this);

    string second = current_type.top();
    current_type.pop();

    if (m->right_operand != nullptr)
        m->right_operand->accept(*this);

    
    string first = current_type.top();
    current_type.pop(); 
    // cout<<first<<" "<<second<<endl;
    if(first == "error" || second =="error"){
        current_type.push("error");
        return;
    }
    int error = 0;
    char operation[100];
    switch(m->op){
        case OP_OR:       
            strcpy(operation, "or");         
            if(first != "boolean" || second != "boolean"){
                error = 1;
                current_type.push("error");

            }
            else{
                current_type.push("boolean");
            }
            break;
        case OP_AND:              
            strcpy(operation, "and");  
            if(first != "boolean" || second != "boolean"){
                error = 1;
                current_type.push("error");
            }
            else{
                current_type.push("boolean");
            }
            break;
        case OP_LESS:             
            strcpy(operation, "<");  
            if( !((first == "integer" || first == "real") && (second == "integer" || second == "real")) ){
                error = 1;
                current_type.push("error");
            }
            else{
                current_type.push("boolean");
            }
            break;            
        case OP_LESS_OR_EQUAL:    
            strcpy(operation, "<=");  
            if( !((first == "integer" || first == "real") && (second == "integer" || second == "real")) ){
                error = 1;
                current_type.push("error");
            }
            else{
                current_type.push("boolean");
            }
            break; 
        case OP_EQUAL:            
            strcpy(operation, "=");  
            if( !((first == "integer" || first == "real") && (second == "integer" || second == "real")) ){
                error = 1;
                current_type.push("error");
            }
            else{
                current_type.push("boolean");
            }
            break; 
        case OP_GREATER:          
            strcpy(operation, ">");  
            if( !((first == "integer" || first == "real") && (second == "integer" || second == "real")) ){
                error = 1;
                current_type.push("error");
            }
            else{
                current_type.push("boolean");
            }
            break; 
        case OP_GREATER_OR_EQUAL: 
            strcpy(operation, ">=");  
            if( !((first == "integer" || first == "real") && (second == "integer" || second == "real")) ){
                error = 1;
                current_type.push("error");
            }
            else{
                current_type.push("boolean");
            }
            break; 
        case OP_NOT_EQUAL:        
            strcpy(operation, "<>");  
            if( !((first == "integer" || first == "real") && (second == "integer" || second == "real")) ){
                error = 1;
                current_type.push("error");
            }
            else{
                current_type.push("boolean");
            }
            break; 
        case OP_PLUS:             
            strcpy(operation, "+");  
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
            strcpy(operation, "-");  
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
            strcpy(operation, "*");  
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
            strcpy(operation, "/");  
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
            strcpy(operation, "mod");  
            if(first!= "integer" || second!= "integer"){
                error = 1;
                current_type.push("error");
            }
            else{
                current_type.push("integer");
            }
            break;
        default:                 
             break;
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
    if(find_next_col){
        record_col = m->col_number;
        find_next_col = 0;
        return;
    }
    if (m->operand != nullptr){
        m->operand->accept(*this);
    }
    string first = current_type.top();
    current_type.pop();
    char operation[100];
    int error = 0;
    switch(m->op){
        case OP_NOT:         
            strcpy(operation, "not");      
            if(first != "boolean"){
                error = 1;
                current_type.push("error");
            }
            else{
                current_type.push("boolean");
            }
            break;
        case OP_MINUS:              
            strcpy(operation, "neg"); 
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
             break;
    }
    if(error){
        print_error_code(m->line_number, m->col_number, 14, operation, first, "");
    }
}

void SemanticAnalyzer::visit(IfNode *m) {
    if (m->condition != nullptr)
        m->condition->accept(*this);

    if(current_type.top()!="boolean"){
        find_next_col = 1;
        if (m->condition != nullptr){
             m->condition->accept(*this);
        }
        print_error_code(m->line_number, record_col, 18, "", "", "");
        current_type.push("error");

    }

    if (m->body != nullptr)
        for(uint i=0; i< m->body->size(); i++)
            (*(m->body))[i]->accept(*this);

    if (m->body_of_else != nullptr){
        for(uint i=0; i< m->body_of_else->size(); i++)
            (*(m->body_of_else))[i]->accept(*this);
    }
}

void SemanticAnalyzer::visit(WhileNode *m) {
     if (m->condition != nullptr)
        m->condition->accept(*this);

    if(current_type.top()!="boolean"){
        find_next_col = 1;
        if (m->condition != nullptr){
             m->condition->accept(*this);
        }
        print_error_code(m->line_number, record_col, 18, "", "", "");
        current_type.push("error");

    }
    if (m->body != nullptr)
        for(uint i=0; i< m->body->size(); i++)
            (*(m->body))[i]->accept(*this);
}

void SemanticAnalyzer::visit(ForNode *m) {
    level++;
    first_int = -999999999;
    second_int = -999999999;
    isloop = 1;
    loop_error = 0;

    SymbolTable* temp_table = new SymbolTable;
    current_table = temp_table;
    if (m->loop_variable_declaration != nullptr){
        m->loop_variable_declaration->accept(*this);
    }
    if(loop_error){
        // cout<<"11111111";
        manager.pushScope(*current_table);
        manager.popScope();
        loop_error = 0;
        current_table = &manager.tables.top();
        return;
    }
    // if(current_type.top()=="error") return;
    level--;    
    manager.pushScope(*current_table);
    if (m->initial_statement != nullptr)
        m->initial_statement->accept(*this);

    // cout<<"first"<<" "<<current_type.top()<<endl;
    if (m->condition != nullptr)
        m->condition->accept(*this);
    if(first_int > second_int){
        print_error_code(m->line_number, m->col_number, 24, "", "", "");
        isloop = 0;
        // return;
    }
    isloop = 0;

    if (m->body != nullptr)
        for(uint i=0; i< m->body->size(); i++)
            (*(m->body))[i]->accept(*this);
    // cout<<"for pop"<<endl;
    manager.popScope();
}

void SemanticAnalyzer::visit(ReturnNode *m) {

    if(return_available.empty()){        
        print_error_code(m->line_number, m->col_number, 15, "", "", "");
        return;
    }
    // cout<<"size is "<< return_available.size()<<endl;    
    if (m->return_value != nullptr)
        m->return_value->accept(*this);
    if(current_type.top()=="error") return;
    // cout<<"return value:"<<return_type<<endl;
    if(!return_available.empty() && return_type !=  current_type.top() && current_type.top() != "error"){
        find_next_col = 1;
        if (m->return_value != nullptr)
            m->return_value->accept(*this);
        check_return = 0;
        // while(!return_available.empty()) return_available.pop();
        print_error_code(m->line_number, record_col, 16 , current_type.top(), return_type, "");
    } 
}

void SemanticAnalyzer::visit(FunctionCallNode *m) {
    if(!check_declared_reference(m->function_name) ){
        print_error_code(m->line_number, m->col_number, 25 , m->function_name, "", "");
        current_type.push("error");
        return;
    }
    // if(current_type.top()=="error") return;
    int num = 0;
    string attr = find_type_or_kind(m->function_name, 2);
    // cout<<attr<<endl;
    // cout<<"tttttttt"<<attr<<endl;
    vector<string> v;
    string temp = "";
    for(int i=0; i<attr.size(); i++){
        if(attr[i] == ',') num++;
        if(attr[i]!= ' ' || attr[i]!= ','){
            temp += attr[i];
        }
        if(attr[i] == ' ' && i< attr.size() && attr[i+1] != '['){
            // cout<<temp;
            v.push_back(temp);
            temp.clear();
        }
    }
    // cout<<"tttttttt"<<temp<<endl;
    v.push_back(temp);

    if(attr.size()!=0)num++;
    if(num > 0 && m->arguments == nullptr){
        print_error_code(m->line_number, m->col_number, 26 ,"", "", "");
        current_type.push("error");
        return;
    }
    if (m->arguments != nullptr){
        if(num != m->arguments->size()){
            print_error_code(m->line_number, m->col_number, 26 ,"", "", "");
            current_type.push("error");
            return;
        }

        for(uint i=0; i< m->arguments->size(); i++){
            (*(m->arguments))[i]->accept(*this);
            // cout<<current_type.top()<<endl;
            if(current_type.top()!= v[i]){
                print_error_code(m->line_number, m->col_number, 27 ,current_type.top(), v[i], "");
                current_type.push("error");
                return;
            }
            // current_type.pop();
        }
    }
    
    string fun_type = find_type_or_kind(m->function_name, 1);
    current_type.push(fun_type);      
}
