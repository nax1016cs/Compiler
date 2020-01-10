#include "generate/codegen.hpp"
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <string.h>
using namespace std;

FILE * fp;
int current_rg = 0;
int idx_for_a = 0;

void initilaize(string program_name){
    string dir = "";
    dir += "output_riscv_code/" + program_name + ".s";
    fp = fopen( dir.c_str(),"w" );
    fprintf(fp, "    .file %s.p\n",  program_name.c_str());
    fprintf(fp, "    .option nopic\n");
}

void global_dec(string var_name, int value){
    if(value == 0)
        fprintf(fp, ".bss\n");
    else 
        fprintf(fp, ".text\n");
    fprintf(fp, "%s\n", var_name.c_str());
    fprintf(fp, "    .word %d\n", value);
}

void local_assign(int sp_offset, int value){
    fprintf(fp, "   sw t%d, %d(s0)\n",0, sp_offset);
    current_rg = 0;
}

void global_assign(string global_name, int value){
    // fprintf(fp, "    li t0, %d\n", value);
    fprintf(fp, "   la t%d, %s\n", current_rg, global_name.c_str());
    fprintf(fp, "   sw t%d, 0(t%d)\n", 0, current_rg);
    current_rg = 0;
}


void load_int_to_register(int value){
    fprintf(fp, "   li t%d, %d\n", current_rg++, value);
}

void binary_op(enumOperator op){
    switch(op){
        case OP_MINUS:
            fprintf(fp, "    subw t%d, t%d, t%d\n", current_rg-2, current_rg-2, current_rg-1);
            current_rg--;
            break;
        case OP_MULTIPLY:
            fprintf(fp, "    mulw t%d, t%d, t%d\n", current_rg-2, current_rg-2, current_rg-1);
            current_rg--;
            break;
        case OP_DIVIDE:
            fprintf(fp, "    divw t%d, t%d, t%d\n", current_rg-2, current_rg-2, current_rg-1);
            current_rg--;
            break;
        case OP_MOD:
            fprintf(fp, "    remw t%d, t%d, t%d\n", current_rg-2, current_rg-2, current_rg-1);
            current_rg--;
            break;
        case OP_PLUS:
            fprintf(fp, "    addw t%d, t%d, t%d\n", current_rg-2, current_rg-2, current_rg-1);
            current_rg--;
            break;
        default:
            break;
    }
}

void unary_op(enumOperator op){
    if(op == OP_MINUS ){
        load_int_to_register(-1);
        fprintf(fp, "    mulw t%d, t%d, t%d\n", current_rg-2, current_rg-2, current_rg-1);
        current_rg--;
    }
}


void load_local_var(int offset){
    fprintf(fp, "    lw t%d, %d(s0)\n", current_rg++, offset);
}

void load_global_var(string name){
    fprintf(fp, "    la t%d, %s\n", current_rg, name.c_str());
    fprintf(fp, "    lw t%d, 0(t%d)\n", current_rg,current_rg++);
}


void ptext(string name){
    idx_for_a = 0;
    fprintf(fp, ".text\n");
    fprintf(fp, "   .align 2\n");
    fprintf(fp, "   .global %s\n", name.c_str());
    fprintf(fp, "   .type %s, @function\n", name.c_str());
    fprintf(fp, "%s:\n", name.c_str());
    fprintf(fp, "   addi sp, sp, -64\n");
    fprintf(fp, "   sd ra, 56(sp)\n");
    fprintf(fp, "   sd s0, 48(sp)\n");
    fprintf(fp, "   addi s0, sp, 64\n");
}

void pend(string name){
    cout<<name<<endl;
    fprintf(fp, "   ld ra, 56(sp)\n");
    fprintf(fp, "   ld s0, 48(sp)\n");
    fprintf(fp, "   addi sp, sp, 64\n");
    fprintf(fp, "   jr ra\n");
    fprintf(fp, "   .size %s, .-%s \n",name.c_str(),name.c_str());
}

void load_parameter(int offset){
    fprintf(fp, "    sw a%d, %d(s0)\n", idx_for_a++, offset);
    // fprintf(fp, "    lw t%d, %d(s0)\n", current_rg++, offset);
}

void return_fun(){
    fprintf(fp, "    mv a0, t0\n");
}

void load_arg(int offset){
    fprintf(fp, "    mv a%d, t0\n", offset);
    current_rg--;
}

void jump_and_load(string name){
    fprintf(fp, "    jal ra, %s\n", name.c_str());
    fprintf(fp, "    mv t%d, a0\n", current_rg++);
}

void print(){
    fprintf(fp, "    mv a0, t0\n");
    fprintf(fp, "    jal ra, print\n");
    current_rg--;
}


void read(string name){
    current_rg--;
    fprintf(fp, "    jal ra, read\n");
    fprintf(fp, "    la  t%d, %s\n", current_rg, name.c_str());
    fprintf(fp, "    sw a0, 0(t%d)\n", current_rg);
}
