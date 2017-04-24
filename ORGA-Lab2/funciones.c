#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "estructuras.h"
#include "mips.h"
#include "fprint.h"


int existsFile(char* filename) {
	FILE* f = NULL;
	f = fopen(filename,"r");
	if (f == NULL)
		return 0;
	else {
		fclose(f);
		return 1;
	}
	return 0;
}

void showInstruction(Instruction instruction){
    if (instruction.arguments == 3){
		printf("%s %s %s %s\n",instruction.function,instruction.a1,instruction.a2,instruction.a3 );
    }
    if (instruction.arguments == 2){
        printf("%s %s %s\n",instruction.function,instruction.a1,instruction.a2);
    }
    if (instruction.arguments == 1){
        printf("%s %s\n",instruction.function,instruction.a1);
    }
}

void showRegisters(Program* program){
    int i;
    for (i=0;i<32;i++){
        printf(" %3li ", program->registers[i]);
    }
}

void showLabels(Program* program){
    int i;
    for (i=0;i<program->counterLabel;i++){
        printf("%s %d\n",program->labels[i].name,program->labels[i].PC);

    }
}

void instructionInit(Instruction* ins){
	memset(ins->function,0,30);
	memset(ins->a1,0,30);
	memset(ins->a2,0,30);
	memset(ins->a3,0,30);
}

int getIndexRegister(char *strRegister,Program* program ){
    //printf("Entrada:%s:\n",strRegister);
    int i;
    for (i=0;i<32;i++){
        //printf("%s:\n",program->nameRegisters[i]);
        if (!strcmp(program->nameRegisters[i],strRegister)){
                //printf("ENTRE IF: %d\n",i);
            return i;
        }
    }
    return -1;
}int getPClabel(char* label,Program* program){
    int i;
    for (i=0;i<program->counterLabel;i++){
        //printf("%s-%s\n",program->labels[i].name,label);
        if (! strcmp(program->labels[i].name, label)){
        	return program->labels[i].PC;
        }
    }
    return -1;
}

void setLinesControl(Instruction in,Program* program){
     if (
		!strcmp(in.function,"add") ||
		!strcmp(in.function,"sub") ||
		!strcmp(in.function,"mul") ||
		!strcmp(in.function,"div")
		){
		    program->linesControl[0]='1';
		    program->linesControl[1]='0';
		    program->linesControl[2]='0';
		    program->linesControl[3]='0';
		    program->linesControl[4]='0';
		    program->linesControl[5]='1';
		    program->linesControl[6]='0';
		    program->linesControl[7]='0';
		    program->linesControl[8]='0';
		    program->linesControl[9]='1';
    }
    else if(
        !strcmp(in.function,"addi") ||
        !strcmp(in.function,"subi")){
            program->linesControl[0]='0';
		    program->linesControl[1]='0';
		    program->linesControl[2]='0';
		    program->linesControl[3]='0';
		    program->linesControl[4]='0';
		    program->linesControl[5]='0';
		    program->linesControl[6]='0';
		    program->linesControl[7]='0';
		    program->linesControl[8]='1';
		    program->linesControl[9]='1';

    }
    else if(
        !strcmp(in.function,"beq") ||
        !strcmp(in.function,"blt") ||
        !strcmp(in.function,"bgt")){
            program->linesControl[0]='x';
		    program->linesControl[1]='0';
		    program->linesControl[2]='1';
		    program->linesControl[3]='0';
		    program->linesControl[4]='x';
		    program->linesControl[5]='0';
		    program->linesControl[6]='1';
		    program->linesControl[7]='0';
		    program->linesControl[8]='0';
		    program->linesControl[9]='0';

    }
    else if (
		!strcmp(in.function,"j") ||
		!strcmp(in.function,"jal") ||
		!strcmp(in.function,"jr")
		){
		    program->linesControl[0]='x';
		    program->linesControl[1]='1';
		    program->linesControl[2]='x';
		    program->linesControl[3]='0';
		    program->linesControl[4]='x';
		    program->linesControl[5]='x';
		    program->linesControl[6]='x';
		    program->linesControl[7]='0';
		    program->linesControl[8]='x';
		    program->linesControl[9]='0';

    }
    else if (
		!strcmp(in.function,"lw") ||
		!strcmp(in.function,"la")
		){
		    program->linesControl[0]='0';
		    program->linesControl[1]='0';
		    program->linesControl[2]='0';
		    program->linesControl[3]='1';
		    program->linesControl[4]='1';
		    program->linesControl[5]='0';
		    program->linesControl[6]='0';
		    program->linesControl[7]='0';
		    program->linesControl[8]='1';
		    program->linesControl[9]='1';

    }
    else if (
		!strcmp(in.function,"sw")
		){
		    program->linesControl[0]='x';
		    program->linesControl[1]='0';
		    program->linesControl[2]='0';
		    program->linesControl[3]='0';
		    program->linesControl[4]='x';
		    program->linesControl[5]='0';
		    program->linesControl[6]='0';
		    program->linesControl[7]='1';
		    program->linesControl[8]='1';
		    program->linesControl[9]='0';

    }
}

void nameRegistersInit(Program *program){
    strcpy(program->nameRegisters[0],"$zero");
	strcpy(program->nameRegisters[1],"$at");
	strcpy(program->nameRegisters[2],"$v0");
	strcpy(program->nameRegisters[3],"$v1");
	strcpy(program->nameRegisters[4],"$a0");
	strcpy(program->nameRegisters[5],"$a1");
	strcpy(program->nameRegisters[6],"$a2");
	strcpy(program->nameRegisters[7],"$a3");
	strcpy(program->nameRegisters[8],"$t0");
	strcpy(program->nameRegisters[9],"$t1");
	strcpy(program->nameRegisters[10],"$t2");
	strcpy(program->nameRegisters[11],"$t3");
	strcpy(program->nameRegisters[12],"$t4");
	strcpy(program->nameRegisters[13],"$t5");
	strcpy(program->nameRegisters[14],"$t6");
	strcpy(program->nameRegisters[15],"$t7");
	strcpy(program->nameRegisters[16],"$s0");
	strcpy(program->nameRegisters[17],"$s1");
	strcpy(program->nameRegisters[18],"$s2");
	strcpy(program->nameRegisters[19],"$s3");
	strcpy(program->nameRegisters[20],"$s4");
	strcpy(program->nameRegisters[21],"$s5");
	strcpy(program->nameRegisters[22],"$s6");
	strcpy(program->nameRegisters[23],"$s7");
	strcpy(program->nameRegisters[24],"$t8");
	strcpy(program->nameRegisters[25],"$t9");
	strcpy(program->nameRegisters[26],"$k0");
	strcpy(program->nameRegisters[27],"$k1");
	strcpy(program->nameRegisters[28],"$gp");
	strcpy(program->nameRegisters[29],"$sp");
	strcpy(program->nameRegisters[30],"$fp");
	strcpy(program->nameRegisters[31],"$ra");
}

void registersInit(Program *program,char *namefile){
    int i;
    for (i=0;i<32;i++){
        program->registers[i]=0;
    }
    /*FILE *fileAux = fopen("fileAux.txt", "w");
    FILE *file = fopen(namefile,"r");
    char buffer[30];
    char valor[30];
    long numero;
    while (!feof(file)){

        fscanf(file,"%s %s\n",buffer,valor);
        //printf("%s:\n",buffer );
        if(valor[0]=='0' && valor[1]=='x'){
            fprintf(fileAux,"%s %s\n",buffer, valor);
        }


    }
    fclose(fileAux);
    fileAux = fopen("fileAux.txt", "r");
    while (!feof(fileAux)){
        fscanf(fileAux,"%s %lX",buffer,&numero);
        printf("%s %s\n",buffer,valor);
        printf("HOLA: %08x, %li\n",numero,numero );

    }
    fclose(fileAux);
    fclose(file);*/
}

void loadIntructions(Program *program,char *filename){
    FILE* file;
	file = fopen(filename,"r");
	char buffer[40];
    while (!feof(file)){

		memset(buffer,0,sizeof(buffer));

		fscanf(file,"%s",buffer);
		//printf("%s\n",buffer );
		if (
		!strcmp(buffer,"add") ||
		!strcmp(buffer,"addi") ||
		!strcmp(buffer,"sub") ||
		!strcmp(buffer,"subi") ||
		!strcmp(buffer,"mul") ||
		!strcmp(buffer,"div") ||
		!strcmp(buffer,"beq") ||
		!strcmp(buffer,"blt") ||
		!strcmp(buffer,"bgt")
		){
			instructionInit(&program->instructions[program->counterInstruction]);
			strcpy(program->instructions[program->counterInstruction].function , buffer);
			fscanf(file," %[^','], %[^','], %s\n",program->instructions[program->counterInstruction].a1,program->instructions[program->counterInstruction].a2,program->instructions[program->counterInstruction].a3);
			program->instructions[program->counterInstruction].arguments = 3;
			//showInstruction(program->instructions[program->counterInstruction]);

			program->counterInstruction++;
			//printf("%d\n",program->counterInstruction);

		}
		else if (
		!strcmp(buffer,"lw") ||
		!strcmp(buffer,"sw")
		){
			instructionInit(&program->instructions[program->counterInstruction]);
			strcpy(program->instructions[program->counterInstruction].function , buffer);
			fscanf(file," %[^','], %[^'('](%[^')']",program->instructions[program->counterInstruction].a1,program->instructions[program->counterInstruction].a2,program->instructions[program->counterInstruction].a3);
			program->instructions[program->counterInstruction].arguments = 3;
			//showInstruction(program->instructions[program->counterInstruction]);

			program->counterInstruction++;

		}
		else if (
		!strcmp(buffer,"la")
		){
			instructionInit(&program->instructions[program->counterInstruction]);
			strcpy(program->instructions[program->counterInstruction].function , buffer);
			fscanf(file," %[^','], (%[^')']",program->instructions[program->counterInstruction].a1,program->instructions[program->counterInstruction].a2);
			program->instructions[program->counterInstruction].arguments = 2;
			//showInstruction(program->instructions[program->counterInstruction]);

			program->counterInstruction++;

		}
		else if (
		!strcmp(buffer,"j") ||
		!strcmp(buffer,"jal") ||
		!strcmp(buffer,"jr")
		){
			instructionInit(&program->instructions[program->counterInstruction]);
			strcpy(program->instructions[program->counterInstruction].function , buffer);
			fscanf(file," %s\n",program->instructions[program->counterInstruction].a1);
			program->instructions[program->counterInstruction].arguments = 1;
			//showInstruction(program->instructions[program->counterInstruction]);

			program->counterInstruction++;

		}

		else if (buffer[strlen(buffer)-1] == ':'){
			//printf("%s largo:%d\n", buffer,program->counterInstruction);
			//printf("%s\n", buffer);
			buffer[strlen(buffer)-1] = '\0';
			strcpy(program->labels[program->counterLabel].name,buffer);
			program->labels[program->counterLabel].PC = program->counterInstruction;
			program->counterLabel++;
			//printf("%d\n",program->counterLabel);


		}
    }
}

Program* programInit(char *filename){

	Program *program=(Program*)malloc(sizeof(Program));
	program->PC=0;
	program->counterInstruction=0;
	program->counterLabel=0;
    nameRegistersInit(program);
    registersInit(program,"inputRegistros.txt");
    loadIntructions(program,filename);
	return program;
}


void exProgram(Program* program,char* nameFileLC, char* nameFileT){
    showInstruction(program->instructions[0]);
    program->instBuffers[0]=program->instructions[0];
    showInstruction(program->instBuffers[0]);

}
