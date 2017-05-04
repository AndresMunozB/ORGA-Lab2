#include "estructuras.h"
#include <stdio.h>
#ifndef _FUNCIONES_MIPS
#define _FUNCIONES_MIPS
void empty(Instruction in,Program *program,int step);
void add(Instruction in,Program *program,int step);
void sub(Instruction in,Program *program,int step);
void addi(Instruction in,Program *program,int step);
void subi(Instruction in,Program *program,int step);
void mul(Instruction in,Program *program,int step);
void div_m(Instruction in,Program *program,int step);
void beq(Instruction in,Program *program,int step);
void blt(Instruction in,Program *program,int step);
void bgt(Instruction in,Program *program,int step);
void jump(Instruction in,Program *program,int step);
void jal(Instruction in,Program *program,int step);
void jr(Instruction in,Program *program,int step);
void la(Instruction in,Program *program,int step);
void lw(Instruction in,Program *program,int step);
void sw(Instruction in,Program *program,int step);


#endif
