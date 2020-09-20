# 作業 5 報告

> 學生：蔣傑名
>
> 學號：0516097


## Add codegen.hpp for generating code
```cpp=
#pragma once
#include <cstdio>
#include "AST/ast.hpp"
#include <iomanip>
#include <iostream>
#include <string.h>
using namespace std;
```

- For register control 
```cpp=
int get_rg(int offset);
void reset_rg();
void decrease_rg();
void increase_rg();
```
- For main program nodes
```cpp=
void initilaize(string program_name);
void global_dec(string var_name, int value);
void local_dec(int offset, int value);
void local_assign(int sp_offset, int value);
void global_assign(string global_name, int value);
void load_int_to_register(int value);
void load_local_var(int offset);
void load_global_var(string name);
void binary_op(enumOperator op);
void unary_op(enumOperator op);
void ptext(string name);
void pend(string name);
```

- For functions
```cpp=
void load_parameter(int offset);
void return_fun();
void load_arg(int offset);
void jump_and_load(string name);
void print();
void read(string name);
```

- For condition nodes
```cpp=
//if
void jump_label(int value);
void set_label(int value);


//for
void load_idx(int for_idx);
void add_idx(int for_idx);
```
## Implementation of codegen.cpp

- egister control

    - Return a usable register 
    ```cpp=
    int get_rg(int offset){
        return (current_rg + offset)%7;
    }
    ```
    - Increase the register and put the it to stack if too much
    ```cpp=
    void increase_rg(){
        current_rg++;
        if(current_rg >6){
            record_offset[current_stack_num].push_back("temprg" + to_string(current_rg));
            fprintf(fp,"    sw t%d, %d(s0)\n", current_rg %7, -4*(record_offset[current_stack_num].size()+4));

        }
    }
    ```
    - Decrease the register and put the saved register in stack back
    ```cpp=
    void decrease_rg(){
        if(current_rg >6){
            for(int i=record_offset[current_stack_num].size()-1; i>=0; i--){
                if(record_offset[current_stack_num][i].substr(0,6) == "temprg"){
                    fprintf(fp,"    lw t%d, %d(s0)\n", ( atoi(record_offset[current_stack_num][i].substr(6,8).c_str()))%7,  -4*(record_offset[current_stack_num].size()+4));
                    record_offset[current_stack_num].pop_back();
                    break;
                }
            }

        }
        current_rg--;
    }
    ```
    - Reset the register
    ```cpp=
    void reset_rg(){
        current_rg = 0;
    }
    ```
- Initialize the program 
```cpp=
void initilaize(string program_name){
	reset_rg();
    string dir = "";
    dir += string(fdir) + "/" + program_name + ".s";
    fp = fopen( dir.c_str(),"w" );
    fprintf(fp,"	.file \"%s.p\"\n",  program_name.c_str());
    fprintf(fp,"	.option nopic\n");
}
```

- Declaration of global and local variable
```cpp=
void global_dec(string var_name, int value){
    if(value == 0)
        fprintf(fp,".bss\n");
    else 
        fprintf(fp,".text\n");
    fprintf(fp,"%s:\n", var_name.c_str());
    fprintf(fp,"	.word %d\n", value);
}

void local_dec(int offset, int value){
    fprintf(fp,"	li t%d, %d\n",  get_rg(0), value);
    fprintf(fp,"	sw t%d, %d(s0)\n",get_rg(0), offset);
}


void local_assign(int sp_offset, int value){
    fprintf(fp,"	sw t%d, %d(s0)\n",0, sp_offset);
    reset_rg();
}

void global_assign(string global_name, int value){
    // fprintf(fp,"    li t0, %d\n", value);
    fprintf(fp,"	la t%d, %s\n", get_rg(0), global_name.c_str());
    fprintf(fp,"	sw t%d, 0(t%d)\n", 0, get_rg(0));
    reset_rg();
}
```

- Load constant to register
```cpp=
void load_int_to_register(int value){
    fprintf(fp,"	li t%d, %d\n", get_rg(0), value);
    increase_rg();
}
```

- Operators
```cpp=


void binary_op(enumOperator op){
    switch(op){
        case OP_MINUS:
            fprintf(fp,"    subw t%d, t%d, t%d\n", get_rg(-2), get_rg(-2), get_rg(-1));
            decrease_rg();
            break;
        case OP_MULTIPLY:
            fprintf(fp,"    mulw t%d, t%d, t%d\n", get_rg(-2), get_rg(-2), get_rg(-1));
            decrease_rg();
            break;
        case OP_DIVIDE:
            fprintf(fp,"    divw t%d, t%d, t%d\n", get_rg(-2), get_rg(-2), get_rg(-1));
            decrease_rg();
            break;
        case OP_MOD:
            fprintf(fp,"    remw t%d, t%d, t%d\n", get_rg(-2), get_rg(-2), get_rg(-1));
            decrease_rg();
            break;
        case OP_PLUS:
            fprintf(fp,"    addw t%d, t%d, t%d\n", get_rg(-2), get_rg(-2), get_rg(-1));
            decrease_rg();
            break;

        case OP_LESS:
            fprintf(fp,"    bge t%d, t%d, L%d\n", get_rg(-2), get_rg(-1),label_num + 1);
            label_stack.push(label_num);
            decrease_rg();
            decrease_rg();
            break;
        case OP_LESS_OR_EQUAL:
            fprintf(fp,"    bgt t%d, t%d, L%d\n", get_rg(-2), get_rg(-1),label_num+1);
            label_stack.push(label_num);
            decrease_rg();
            decrease_rg();
            break;
        case OP_EQUAL:
            fprintf(fp,"    bne t%d, t%d, L%d\n", get_rg(-2), get_rg(-1),label_num+1);
            label_stack.push(label_num);
            decrease_rg();
            decrease_rg();
            break;
        case OP_GREATER:
            fprintf(fp,"	ble t%d, t%d, L%d\n", get_rg(-2), get_rg(-1),label_num+1);
            label_stack.push(label_num);
            decrease_rg();
            decrease_rg();
            break;
        case OP_GREATER_OR_EQUAL:
            fprintf(fp,"    blt t%d, t%d, L%d\n", get_rg(-2), get_rg(-1),label_num+1);
            label_stack.push(label_num);
            decrease_rg();
            decrease_rg();
            break;
        case OP_NOT_EQUAL:
            fprintf(fp,"    beq t%d, t%d, t%d\n", get_rg(-2), get_rg(-1),label_num+1);
            label_stack.push(label_num);
            decrease_rg();
            decrease_rg();
            break;
        default:
            break;
    }
}

void unary_op(enumOperator op){
    if(op == OP_MINUS ){
        load_int_to_register(-1);
        fprintf(fp,"    mulw t%d, t%d, t%d\n", get_rg(-2), get_rg(-2), get_rg(-1));
        decrease_rg();
    }
}
```

- Load local and global variable
```cpp=


void load_local_var(int offset){
    fprintf(fp,"    lw t%d, %d(s0)\n", get_rg(0), offset);
    increase_rg();
}

void load_global_var(string name){
    fprintf(fp,"    la t%d, %s\n", get_rg(0), name.c_str());
    fprintf(fp,"	lw t%d, 0(t%d)\n", get_rg(0),get_rg(0));
    increase_rg();
}


```

- The fixed part of function
```cpp=

void ptext(string name){
    idx_for_a = 0;
	reset_rg();

    fprintf(fp,".text\n");
    fprintf(fp,"	.align 2\n");
    fprintf(fp,"	.global %s\n", name.c_str());
    fprintf(fp,"	.type %s, @function\n", name.c_str());
    fprintf(fp,"%s:\n", name.c_str());
    fprintf(fp,"	addi sp, sp, -64\n");
    fprintf(fp,"	sd ra, 56(sp)\n");
    fprintf(fp,"	sd s0, 48(sp)\n");
    fprintf(fp,"	addi s0, sp, 64\n");
}

void pend(string name){
    idx_for_a = 0;
	reset_rg();

    fprintf(fp,"	ld ra, 56(sp)\n");
    fprintf(fp,"	ld s0, 48(sp)\n");
    fprintf(fp,"	addi sp, sp, 64\n");
    fprintf(fp,"	jr ra\n");
    fprintf(fp,"	.size %s, .-%s \n",name.c_str(),name.c_str());
    if(name == "main") fclose(fp);
}
```

- Load parameters
```cpp=
void load_parameter(int offset){
    if(idx_for_a < 8)
        fprintf(fp,"    sw a%d, %d(s0)\n", idx_for_a++, offset);
    //////////////////////
}
```

- Return node
```cpp=

void return_fun(){
    fprintf(fp,"    mv a0, t0\n");
}
```

- Load arguments to registers or stack
```cpp=

void load_arg(int offset){
    if(offset < 8){
        fprintf(fp,"    mv a%d, t%d\n", offset, get_rg(-1));
    }
    else{
        fprintf(fp,"    sw t%d, %d(s0)\n", get_rg(-1), -64-20-offset*4);
    }
    
    ///////////
    // reset_rg();
    decrease_rg();
}
```

- Jump and load
```cpp=

void jump_and_load(string name){
    int temp_rg = get_rg(0);
    // int occupy = temp_rg-1;
    for(int i=0; i<temp_rg; i++){
        //push to stack
        record_offset[current_stack_num].push_back("temparg" + to_string(i));
        fprintf(fp,"    sw t%d, %d(s0)\n", i, -4*(record_offset[current_stack_num].size()+4));
        // fprintf(fp,"    lw t%d, %d(s0)\n", get_rg(0), offset);
    }
    fprintf(fp,"    jal ra, %s\n", name.c_str());
    for(int i=temp_rg-1; i>=0; i--){
        fprintf(fp,"    lw t%d, %d(s0)\n", i, -4*(record_offset[current_stack_num].size()+4));
        record_offset[current_stack_num].pop_back();
        //push to stack
    }
    fprintf(fp,"    mv t%d, a0\n", get_rg(0));
    increase_rg();
}
```

- Print and Read 
```cpp=

void print(){
    fprintf(fp,"	mv a0, t0\n");
    fprintf(fp,"	jal ra, print\n");
    decrease_rg();
}


void read(string name){
    // decrease_rg();
    fprintf(fp,"    jal ra, read\n");
    fprintf(fp,"    la  t%d, %s\n", get_rg(0), name.c_str());
    fprintf(fp,"    sw a0, 0(t%d)\n", get_rg(0));
}
```
- Set label and Jump to certain label
```cpp=

void jump_label(int value){
    fprintf(fp,"	j L%d\n", value);
}

void set_label(int value){
    fprintf(fp,"L%d:\n", value);
}
```

- For node
```cpp=
void load_idx(int for_idx){
    fprintf(fp,"	lw t%d, %d(s0)\n", get_rg(0),for_idx);
    increase_rg();
}

void add_idx(int for_idx){
    fprintf(fp,"	lw t%d, %d(s0)\n", get_rg(0),for_idx);
    increase_rg();
	load_int_to_register(1);
	binary_op(OP_PLUS);
	local_assign(for_idx,0);
    // fprintf(fp,"	lw t%d, %d(s0)\n", current_rg++,for_idx);
}
```


## Change in this homework
- When doing the semantic analyze, convert the code below into assembly code as well.
    - Global variable or local variable declaration.
    - Global constant or local constant declaration.
    - Function declaration.
    - Assign statement.
    - Simple statement.
    - Expressions with only + - (unary and binary) * / mod function invocation included.
    - Function invocation statement.
    - Conditional statement.
    - For statement and while statement.

## Some advice for TA:

- Make the spec more detailed.
    - The implementation of for node is not on spec, although we could finish it, I think if there is detailed information will be good.
    - It should be informed in spec that output directory should be created if not exist.

- For every test case, it will be better if the assembly code provided. There is only the sample output of the test case, it's hard to check the assembly code.

## 作業 5 心得

雖然助教說這次的作業比較簡單，但還是花了很多時間在上面，主要是產生出來的是組合語言，閱讀上極不易，光是要檢查一次組合就花上不少心力，而且剛好這學期上過微處理機，多少碰過組合語言，才不至於覺得很痛苦，但是對於第一次接觸組合語言的同學(可能不多)，應該會覺得這次的作業蠻有難度的。

## 整學期編譯器作業心得

雖然助教很努力地寫spec，但還是有些地方不太清楚，例如寫HW4的時候，有些情況模稜兩可，造成寫作業的時候有點困擾，不過整體上感覺還算清晰。

另外作業的難度也頗高，相對於其他課程花上了不少的時間在上面；有些作業的基本測資的分數也只有60分，但是提供的test case又很簡單，看到作業成績才發覺只比基本分多一點點(test case都有過)，希望助教能稍微提供一些比較難的測資。

最後很謝謝助教們這麼努力地撰寫spec以及設計作業，雖然做作業的過程充滿了曲折，但是一步一步地把簡易的compiler做出來也是很感動! 助教們也很認真回答同學的問題，甚至在很多人不知道如何做AST時，額外花時間教學，助教們真的很辛苦!