#include "AST/variable.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>

VariableNode::VariableNode(
    int _line_number, 
    int _col_number, 
    string _variable_name, 
    VariableInfo* _type, 
    Node _constant_value_node
    ){
        this->line_number = _line_number;
        this->col_number = _col_number;
        this->variable_name = _variable_name;
        this->type = _type;
        this->constant_value_node = _constant_value_node;
    }

VariableNode::~VariableNode(){
    SAFE_DELETE(this->type)
    SAFE_DELETE(this->constant_value_node)
}

void VariableNode::print() {    
    std::cout << "variable <line: " << line_number
        << ", col: " << col_number
        << "> " << variable_name
        << " " << this->getType()
        << std::endl;
}

string VariableNode::getType() {
    int first_bracket = 1;
    string temp;
    switch(this->type->type_set){

        case SET_SCALAR:
        case SET_CONSTANT_LITERAL:
            switch(this->type->type){
                case TYPE_INTEGER: temp = "integer"; break;
                case TYPE_REAL:    temp = "real"; break;
                case TYPE_STRING:  temp = "string"; break;
                case TYPE_BOOLEAN: temp = "boolean"; break;
                default:           temp = "unknown"; break;
            }
            break;
        case SET_ACCUMLATED:
            switch(this->type->type){
                case TYPE_INTEGER: temp = "integer"; break;
                case TYPE_REAL:    temp = "real"; break;
                case TYPE_STRING:  temp = "string"; break;
                case TYPE_BOOLEAN: temp = "boolean"; break;
                default:           temp = "unknown"; break;
            }
            
            for(uint i=0; i<this->type->array_range.size(); i++){
                if(first_bracket){
                    temp += " [";
                    first_bracket = 0;
                }
                else
                    temp += "[";
                temp += to_string(this->type->array_range[i].end -this->type->array_range[i].start );
                temp += "]";
            }
            break;
        default:
            temp = "unknown";
            break;
    }
    return temp;
}