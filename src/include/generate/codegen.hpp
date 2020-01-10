#pragma once
#include <cstdio>
#include "AST/ast.hpp"
#include <iomanip>
#include <iostream>
#include <string.h>
using namespace std;

// main 
void initilaize(string program_name);
void global_dec(string var_name, int value);
void local_assign(int sp_offset, int value);
void global_assign(string global_name, int value);
void load_int_to_register(int value);
void load_local_var(int offset);
void load_global_var(string name);
void binary_op(enumOperator op);
void unary_op(enumOperator op);
void ptext(string name);
void pend(string name);

//function
void load_parameter(int offset);
void return_fun();


