#include "generate/codegen.hpp"
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <string.h>
#include <stack>
using namespace std;

extern stack <int> label_stack;
extern int label_num;
extern char fdir[100];
FILE * fp;
int current_rg = 0;
int idx_for_a = 0;

void increase_rg(){
    current_rg++;
}


void reset_rg(){
    current_rg = 0;
}

void decrease_rg(){
    current_rg--;
}

void initilaize(string program_name){
	reset_rg();
    string dir = "";
    dir += string(fdir) + "/" + program_name + ".s";
    fp = fopen( dir.c_str(),"w" );
    fprintf(fp,"	.file \"%s.p\"\n",  program_name.c_str());
    fprintf(fp,"	.option nopic\n");
}

void global_dec(string var_name, int value){
    if(value == 0)
        fprintf(fp,".bss\n");
    else 
        fprintf(fp,".text\n");
    fprintf(fp,"%s:\n", var_name.c_str());
    fprintf(fp,"	.word %d\n", value);
}

void local_dec(int offset, int value){
    fprintf(fp,"	li t%d, %d\n", current_rg, value);
    fprintf(fp,"	sw t%d, %d(s0)\n",current_rg, offset);

}



void local_assign(int sp_offset, int value){
    fprintf(fp,"	sw t%d, %d(s0)\n",0, sp_offset);
    reset_rg();
}

void global_assign(string global_name, int value){
    // fprintf(fp,"    li t0, %d\n", value);
    fprintf(fp,"	la t%d, %s\n", current_rg, global_name.c_str());
    fprintf(fp,"	sw t%d, 0(t%d)\n", 0, current_rg);
    reset_rg();
}


void load_int_to_register(int value){
    fprintf(fp,"	li t%d, %d\n", current_rg, value);
    increase_rg();
}

void binary_op(enumOperator op){
    switch(op){
        case OP_MINUS:
            fprintf(fp,"    subw t%d, t%d, t%d\n", current_rg-2, current_rg-2, current_rg-1);
            decrease_rg();
            break;
        case OP_MULTIPLY:
            fprintf(fp,"    mulw t%d, t%d, t%d\n", current_rg-2, current_rg-2, current_rg-1);
            decrease_rg();
            break;
        case OP_DIVIDE:
            fprintf(fp,"    divw t%d, t%d, t%d\n", current_rg-2, current_rg-2, current_rg-1);
            decrease_rg();
            break;
        case OP_MOD:
            fprintf(fp,"    remw t%d, t%d, t%d\n", current_rg-2, current_rg-2, current_rg-1);
            decrease_rg();
            break;
        case OP_PLUS:
            fprintf(fp,"    addw t%d, t%d, t%d\n", current_rg-2, current_rg-2, current_rg-1);
            decrease_rg();
            break;

        case OP_LESS:
            fprintf(fp,"    bge t%d, t%d, L%d\n", current_rg-2, current_rg-1,label_num + 1);
            label_stack.push(label_num);
            current_rg -= 2;
            break;
        case OP_LESS_OR_EQUAL:
            fprintf(fp,"    bgt t%d, t%d, L%d\n", current_rg-2, current_rg-1,label_num+1);
            label_stack.push(label_num);
            current_rg -= 2;
            break;
        case OP_EQUAL:
            fprintf(fp,"    bne t%d, t%d, L%d\n", current_rg-2, current_rg-1,label_num+1);
            label_stack.push(label_num);
            current_rg -= 2;
            break;
        case OP_GREATER:
            fprintf(fp,"	ble t%d, t%d, L%d\n", current_rg-2, current_rg-1,label_num+1);
            label_stack.push(label_num);
            current_rg -= 2;
            break;
        case OP_GREATER_OR_EQUAL:
            fprintf(fp,"    blt t%d, t%d, L%d\n", current_rg-2, current_rg-1,label_num+1);
            label_stack.push(label_num);
            current_rg -= 2;
            break;
        case OP_NOT_EQUAL:
            fprintf(fp,"    beq t%d, t%d, t%d\n", current_rg-2, current_rg-1,label_num+1);
            label_stack.push(label_num);
            current_rg -= 2;
            break;
        default:
            break;
    }
}

void unary_op(enumOperator op){
    if(op == OP_MINUS ){
        load_int_to_register(-1);
        fprintf(fp,"    mulw t%d, t%d, t%d\n", current_rg-2, current_rg-2, current_rg-1);
        decrease_rg();
    }
}


void load_local_var(int offset){
    fprintf(fp,"    lw t%d, %d(s0)\n", current_rg, offset);
    increase_rg();
}

void load_global_var(string name){
    fprintf(fp,"    la t%d, %s\n", current_rg, name.c_str());
    fprintf(fp,"	lw t%d, 0(t%d)\n", current_rg,current_rg);
    increase_rg();
}


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
	reset_rg();

    fprintf(fp,"	ld ra, 56(sp)\n");
    fprintf(fp,"	ld s0, 48(sp)\n");
    fprintf(fp,"	addi sp, sp, 64\n");
    fprintf(fp,"	jr ra\n");
    fprintf(fp,"	.size %s, .-%s \n",name.c_str(),name.c_str());
    if(name == "main") fclose(fp);
}

void load_parameter(int offset){
    fprintf(fp,"    sw a%d, %d(s0)\n", idx_for_a++, offset);
    // fprintf(fp,"    lw t%d, %d(s0)\n", current_rg++, offset);
}

void return_fun(){
    fprintf(fp,"    mv a0, t0\n");
}

void load_arg(int offset){
    fprintf(fp,"    mv a%d, t0\n", offset);
    // reset_rg();
    decrease_rg();
}

void jump_and_load(string name){
    fprintf(fp,"    jal ra, %s\n", name.c_str());
    fprintf(fp,"    mv t%d, a0\n", current_rg);
    increase_rg();
}

void print(){
    fprintf(fp,"	mv a0, t0\n");
    fprintf(fp,"	jal ra, print\n");
    decrease_rg();
}


void read(string name){
    // decrease_rg();
    fprintf(fp,"    jal ra, read\n");
    fprintf(fp,"    la  t%d, %s\n", current_rg, name.c_str());
    fprintf(fp,"    sw a0, 0(t%d)\n", current_rg);
}

void jump_label(int value){
    fprintf(fp,"	j L%d\n", value);
}

void set_label(int value){
    fprintf(fp,"L%d:\n", value);
}


void load_idx(int for_idx){
    fprintf(fp,"	lw t%d, %d(s0)\n", current_rg,for_idx);
    increase_rg();
}

void add_idx(int for_idx){
    fprintf(fp,"	lw t%d, %d(s0)\n", current_rg,for_idx);
    increase_rg();
	load_int_to_register(1);
	binary_op(OP_PLUS);
	local_assign(for_idx,0);
    // fprintf(fp,"	lw t%d, %d(s0)\n", current_rg++,for_idx);
}
