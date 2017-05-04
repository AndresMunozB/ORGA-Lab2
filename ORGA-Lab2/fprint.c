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
            fprintf(archivo,"%s %s, %s, %s\n", in.function,in.a1,in.a2,in.a3);
    }
    else if (
		!strcmp(in.function,"lw") ||
		!strcmp(in.function,"sw")
		){
		    fprintf(archivo,"%s %s, %s(%s)\n", in.function,in.a1,in.a2,in.a3);
    }
    else if (
		!strcmp(in.function,"la")
		){
		    fprintf(archivo,"%s %s, (%s)\n", in.function,in.a1,in.a2);
    }
    else if (
		!strcmp(in.function,"j") ||
		!strcmp(in.function,"jal") ||
		!strcmp(in.function,"jr")
		){
		    fprintf(archivo,"%s %s\n", in.function,in.a1);
    }
    else if (!strcmp(in.function,"Empty")){
        fprintf(archivo,"%s\n", in.function);
    }
    else if(!strcmp(in.function,"NOP")) {
        fprintf(archivo, "%s\n", in.function );
    }

}

/*void fprintRegisters(FILE* archivo, Program* program){
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
}*/

FILE* openFileHtml(char* namefile){
    FILE *file = fopen(namefile,"w");
    //fprintf(file,"<!DOCTYPE html>\n<html>\n<head>\n<title>Titulo</title>\n</head>\n<body>\n");
    fprintf(file,"<!DOCTYPE html>\n<html>\n<head>\n<title>Titulo</title>\n<style type=\"text/css\">\n#contenedor { width: 90%%; margin: 0 auto; }\n</style> </head>\n<body>\n<div id=\"contenedor\">\n");

    return file;
}

void closeFileHtml(FILE* file){
    //fprintf(file, "</body>\n</html>\n" );
    fprintf(file, "</div>\n</body>\n</html>\n" );
    fclose(file);
}

void fprintNameRegistersHtml(FILE* file, Program* program){
    fprintf(file, "<h1>Registros:</h1>\n" );
    fprintf(file, "<table border=1 cellspacing=0 cellpadding=2 bordercolor=\"0\">\n" );
    fprintf(file, "<tr>\n" );
    fprintf(file, "<td>Ciclo</td>\n");
    int i;
    for (i=0;i<32;i++){
        fprintf(file,"<td>%s</td>\n",program->nameRegisters[i]);
    }
    fprintf(file, "</tr>\n");
}

void fprintRegistersHtml(FILE* file,Program* program, int cycle){
    fprintf(file, "<tr>\n" );
    fprintf(file,"<td>C%d</td>\n", cycle);
    int i;
    for (i=0;i<32;i++){
        if(program->registers[i] != program->registersCpy[i]){
            fprintf(file,"<td>%li/%li</td>\n",program->registersCpy[i], program->registers[i]);
        }
        else{
            fprintf(file,"<td>%li</td>\n", program->registers[i]);

        }
    }
    fprintf(file, "</tr>\n");

}

void fprintNameBuffersHtml(FILE* file){
    fprintf(file, "<h1>Buffers:</h1>\n" );
    fprintf(file, "<table border=1 cellspacing=0 bordercolor=\"0\">\n" );
    fprintf(file, "<tr>\n" );
    fprintf(file, "<td>Ciclo</td>\n");
    fprintf(file, "<td>IF/ID</td>\n");
    fprintf(file, "<td>ID/EX</td>\n");
    fprintf(file, "<td>EX/MEN</td>\n");
    fprintf(file, "<td>MEM/WB</td>\n");
    fprintf(file, "</tr>\n");
}

void fprintBuffersHtml(FILE* file, Program* program,int cycle){
    //INSTRUCCIONES DE LOS BUFFER
    fprintf(file, "<tr>\n" );
    fprintf(file,"<td rowspan=\"2\">C%d</td>\n", cycle);
    fprintf(file, "<td>\n" );
    fprintInstruction(file,program->buffers[0].instruction);
    fprintf(file, "</td>\n" );
    fprintf(file, "<td>\n" );
    fprintInstruction(file,program->buffers[1].instruction);
    fprintf(file, "</td>\n" );
    fprintf(file, "<td>\n" );
    fprintInstruction(file,program->buffers[2].instruction);
    fprintf(file, "</td>\n" );
    fprintf(file, "<td>\n" );
    fprintInstruction(file,program->buffers[3].instruction);
    fprintf(file, "</td>\n" );
    fprintf(file, "</tr>\n" );

    //INFORMACION  DE LOS BUFFER
    fprintf(file, "<tr>\n" );
    fprintIFIDHtml(file,program);
    fprintIDEXHtml(file,program);
    fprintEXMEMHtml(file,program);
    fprintMEMWBHtml(file,program);
    fprintf(file, "</tr>\n" );

}

void fprintIFIDHtml(FILE* file, Program* program){
    //Falta lo del add_pc que nose como sera..
    fprintf(file, "<td>\n" );
    fprintf(file, "Add_PC=0x%08x<br>\n",program->buffers[0].add_pc);
    fprintf(file, "</td>\n" );
}

void fprintIDEXHtml(FILE* file, Program* program){
    //Falta lo del add_pc que nose como sera..
    fprintf(file, "<td>\n" );
    fprintf(file, "Add_PC=0x%08x<br>\n",program->buffers[1].add_pc);
    fprintf(file, "ALUSrc=%c<br>\n",program->buffers[1].linesControl[8]);
    fprintf(file, "ALUOp1=%c<br>\n",program->buffers[1].linesControl[5]);
    fprintf(file, "ALUOp2=%c<br>\n",program->buffers[1].linesControl[6]);
    fprintf(file, "RegDst=%c<br>\n",program->buffers[1].linesControl[0]);
    fprintf(file, "Branch=%c<br>\n",program->buffers[1].linesControl[2]);
    fprintf(file, "MemWrite=%c<br>\n",program->buffers[1].linesControl[7]);
    fprintf(file, "MemRead=%c<br>\n",program->buffers[1].linesControl[3]);
    fprintf(file, "RegWrite=%c<br>\n",program->buffers[1].linesControl[9]);
    fprintf(file, "MemToReg=%c<br>\n",program->buffers[1].linesControl[4]);
    fprintf(file, "Jump=%c<br>\n",program->buffers[1].linesControl[1]);

    fprintf(file, "Read data 1=%li<br>\n",program->buffers[1].readData1);
    fprintf(file, "Read data 2=%li<br>\n",program->buffers[1].readData2);
    fprintf(file, "Sign-extend=%li<br>\n",program->buffers[1].signExtend);
    fprintf(file, "Rs=%s<br>\n",program->buffers[1].rs);
    fprintf(file, "Rt=%s<br>\n",program->buffers[1].rt);
    fprintf(file, "Rd=%s<br>\n",program->buffers[1].rd);
    fprintf(file, "</td>\n" );
}

void fprintEXMEMHtml(FILE* file, Program* program){
    //Listo
    fprintf(file, "<td>\n" );
    fprintf(file, "Branch=%c<br>\n",program->buffers[2].linesControl[2]);
    fprintf(file, "MemWrite=%c<br>\n",program->buffers[2].linesControl[7]);
    fprintf(file, "MemRead=%c<br>\n",program->buffers[2].linesControl[3]);
    fprintf(file, "RegWrite=%c<br>\n",program->buffers[2].linesControl[9]);
    fprintf(file, "MemToReg=%c<br>\n",program->buffers[2].linesControl[4]);
    fprintf(file, "Zero=%li<br>\n",program->buffers[2].zero);
    fprintf(file, "ALU Result=%li<br>\n",program->buffers[2].aluResult);
    fprintf(file, "Read data 2=%li<br>\n",program->buffers[2].readData2);
    fprintf(file, "Add result=%li<br>\n",program->buffers[2].addResult);
    fprintf(file, "Mux RegDst=%s<br>\n",program->buffers[2].muxRegDst);
    fprintf(file, "</td>\n" );
}

void fprintMEMWBHtml(FILE* file, Program* program){
    fprintf(file, "<td>\n" );
    fprintf(file, "RegWrite=%c<br>\n",program->buffers[3].linesControl[9]);
    fprintf(file, "MemToReg=%c<br>\n",program->buffers[3].linesControl[4]);
    fprintf(file, "Read data=%li<br>\n",program->buffers[3].readData);
    fprintf(file, "ALU Result=%li<br>\n",program->buffers[3].aluResult);
    fprintf(file, "Mux RegDst=%s<br>\n",program->buffers[3].muxRegDst);
    fprintf(file, "</td>\n" );
}



#endif
