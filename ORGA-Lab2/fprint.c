#include <stdio.h>
#include <stdlib.h> //para el atoi!
#include <string.h>
#include "estructuras.h"
#include "funciones.h"
#include "fprint.h"

#ifndef _FUNCIONES_FPRINT
#define _FUNCIONES_FPRINT

void fprintInstruction(FILE* archivo,Instruction in){
    if (
		!strcmp(in.function,"add") ||
		!strcmp(in.function,"addi") ||
		!strcmp(in.function,"sub") ||
		!strcmp(in.function,"subi") ||
		!strcmp(in.function,"mul") ||
		!strcmp(in.function,"div") ||
		!strcmp(in.function,"beq") ||
		!strcmp(in.function,"blt") ||
		!strcmp(in.function,"bgt")
		){
            fprintf(archivo,"%s %s, %s, %s:\n", in.function,in.a1,in.a2,in.a3);
    }
    else if (
		!strcmp(in.function,"lw") ||
		!strcmp(in.function,"sw")
		){
		    fprintf(archivo,"%s %s, %s(%s):\n", in.function,in.a1,in.a2,in.a3);
    }
    else if (
		!strcmp(in.function,"la")
		){
		    fprintf(archivo,"%s %s, (%s):\n", in.function,in.a1,in.a2);
    }
    else if (
		!strcmp(in.function,"j") ||
		!strcmp(in.function,"jal") ||
		!strcmp(in.function,"jr")
		){
		    fprintf(archivo,"%s %s:\n", in.function,in.a1);
    }
}
void fprintRegisters(FILE* archivo, Program* program){
    int i;
    for (i=0;i<32;i++){
        fprintf(archivo," %3li ", program->registers[i]);
    }
}

void fprintLinesControl(FILE* archivo, Program* program){
	fprintf(archivo,"RegDst:  %c\n",program->linesControl[0]);
    fprintf(archivo,"Jump:    %c\n",program->linesControl[1]);
    fprintf(archivo,"Branch:  %c\n",program->linesControl[2]);
    fprintf(archivo,"MemRead: %c\n",program->linesControl[3]);
    fprintf(archivo,"MemToReg:%c\n",program->linesControl[4]);
    fprintf(archivo,"ALUOP1:  %c\n",program->linesControl[5]);
    fprintf(archivo,"ALUOP2:  %c\n",program->linesControl[6]);
    fprintf(archivo,"MemWrite:%c\n",program->linesControl[7]);
    fprintf(archivo,"ALUSrc:  %c\n",program->linesControl[8]);
    fprintf(archivo,"RegWrite:%c\n",program->linesControl[9]);
}
void fprintTitle(FILE* archivo, Program* program){
    fprintf(archivo," PC FASE");
    fprintf(archivo," %s",program->nameRegisters[0]);
    fprintf(archivo," %s",program->nameRegisters[1]);
    int i;
    for (i=2;i<32;i++){
        fprintf(archivo,"  %s",program->nameRegisters[i]);
    }
    fprintf(archivo,"\n");
}

void fprintRegistersHtml(Program* program){
    FILE *file = fopen("pagina.html","w");
    fprintf(file,"<!DOCTYPE html>\n<html>\n<head>\n<title>Titulo</title>\n</head>\n<body>\n<table>\n<tr>\n");

    int i;
    for (i=0;i<32;i++){
        fprintf(file,"<td>%3li</td>\n", program->registers[i]);
    }
    fprintf(file, "<tr>\n</body>\n</html>\n" );
    fclose(file);
}

#endif
