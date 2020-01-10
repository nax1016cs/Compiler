#include "generate/codegen.hpp"
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <string.h>
using namespace std;

FILE * fp;
int current_rg = 0;

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
	// fprintf(fp, "	li t0, %d\n", value);
    current_rg = 0;
    fprintf(fp, "	sw t0, %d(s0)\n", sp_offset);
}

void global_assign(string global_name, int value){
	// fprintf(fp, "	li t0, %d\n", value);
    current_rg = 0;
    fprintf(fp, "	la t1, %s\n", global_name.c_str());
	fprintf(fp, "	sw t0, 0(t1)\n");
}


void load_int_to_register(int value){
	fprintf(fp, "	li t%d, %d\n", current_rg++, value);
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
    }
}

void unary_op(enumOperator op){
    if(op == OP_MINUS ){
        load_int_to_register(-1);
        fprintf(fp, "    mulw t%d, t%d, t%d\n", current_rg-2, current_rg-2, current_rg-1);
        current_rg--;
    }
}

















void main_text(){
	fprintf(fp, ".text\n");
    fprintf(fp, "	.align 2\n");
	fprintf(fp, "	.global main\n");
    fprintf(fp, "	.type main\n");
    fprintf(fp, "main:\n");
    fprintf(fp, "	addi sp, sp, -64\n");
	fprintf(fp, "	sd ra, 56(sp)\n");
    fprintf(fp, "	sd s0, 48(sp)\n");
    fprintf(fp, "	addi s0, sp, 64\n");
}

void main_end(){

	fprintf(fp, "	ld ra, 56(sp)\n");
    fprintf(fp, "	ld s0, 48(sp)\n");
    fprintf(fp, "	addi sp, sp, 64\n");
    fprintf(fp, "	jr ra\n");
    fprintf(fp, "	.size main, .-main \n");
    fclose(fp);
}


