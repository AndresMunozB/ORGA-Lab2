#include "estructuras.h"
#include <stdio.h>
#ifndef _FUNCIONES_MIPS
#define _FUNCIONES_MIPS
void add(Instruction in ,Program* program,FILE* linesControl,FILE* traza);
void sub(Instruction in ,Program* program,FILE* linesControl,FILE* traza);
void addi(Instruction in ,Program* program,FILE* linesControl,FILE* traza);
void subi(Instruction in ,Program* program,FILE* linesControl,FILE* traza);
void mul(Instruction in ,Program* program,FILE* linesControl,FILE* traza);
void div_m(Instruction in ,Program* program,FILE* linesControl,FILE* traza);
void beq(Instruction in ,Program* program,FILE* linesControl,FILE* traza);
void blt(Instruction in ,Program* program,FILE* linesControl,FILE* traza);
void bgt(Instruction in ,Program* program,FILE* linesControl,FILE* traza);
void jump(Instruction in ,Program* program,FILE* linesControl,FILE* traza);
void jal(Instruction in ,Program* program,FILE* linesControl,FILE* traza);
void jr(Instruction in ,Program* program,FILE* linesControl,FILE* traza);
void la(Instruction in ,Program* program,FILE* linesControl,FILE* traza);
void lw(Instruction in ,Program* program,FILE* linesControl,FILE* traza);
void sw(Instruction in ,Program* program,FILE* linesControl,FILE* traza);


#endif
