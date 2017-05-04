#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "estructuras.h"
#include "mips.h"
#include "fprint.h"
/*
 * Funcion existsFile
*/
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

/*
 * Funcion showInstruction
*/
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
	if (instruction.arguments == 0){
		printf("%s\n",instruction.function );
	}
}

/*
 * Funcion showRegisters
*/
void showRegisters(Program* program){
    int i;
    for (i=0;i<32;i++){
        printf(" %3li ", program->registers[i]);
    }
}

/*
 * Funcion showLabels
*/
void showLabels(Program* program){
    int i;
    for (i=0;i<program->counterLabel;i++){
        printf("%s %d\n",program->labels[i].name,program->labels[i].PC);

    }
}

/*
 * Funcion instructionInit
*/
void instructionInit(Instruction* ins){
	memset(ins->function,0,30);
	memset(ins->a1,0,30);
	memset(ins->a2,0,30);
	memset(ins->a3,0,30);
}

/*
 * Funcion getIndexRegister
*/
int getIndexRegister(char *strRegister,Program* program ){
    int i;
    for (i=0;i<32;i++){
        if (!strcmp(program->nameRegisters[i],strRegister)){
            return i;
        }
    }
    return 0;
}

/*
 * Funcion getPClabel
*/
int getPClabel(char* label,Program* program){
    int i;
    for (i=0;i<program->counterLabel;i++){
        if (! strcmp(program->labels[i].name, label)){
        	return program->labels[i].PC;
        }
    }
    return -1;
}

/*
 * Funcion setLinesControl
*/
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
	else if((!strcmp(in.function,"Empty")) || (!strcmp(in.function,"NOP"))) {
		program->linesControl[0]='0';
		program->linesControl[1]='0';
		program->linesControl[2]='0';
		program->linesControl[3]='0';
		program->linesControl[4]='0';
		program->linesControl[5]='0';
		program->linesControl[6]='0';
		program->linesControl[7]='0';
		program->linesControl[8]='0';
		program->linesControl[9]='0';
	}
}

/*
 * Funcion nameRegistersInit
*/
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

/*
 * Funcion initRegisters
*/
void initRegisters(Program *program,char *namefile){
	//Pasar esto para que el usuario ingrese el nombre del archivo
	FILE *file = fopen(namefile,"r");
    char registerStr[30];
    char valor[30];
    int indice;
    while (!feof(file)){

        fscanf(file,"%s %s\n",registerStr,valor);
		indice = getIndexRegister(registerStr,program);
		program->registers[indice] = strtol(valor,NULL,0);
    }
    fclose(file);
}

/*
 * Funcion upRegisters
*/
void upRegisters(Program *program){
	int reg;
	for (reg=0;reg<32;reg++){
		program->registersCpy[reg] = program->registers[reg];
	}
}

/*
 * Funcion resetInstruction
*/
void resetInstruction(Instruction *in){
	in->arguments = 0;
	strcpy(in->function , "Empty");
	strcpy(in->a1 , "");
	strcpy(in->a2 , "");
	strcpy(in->a3 , "");
}

/*
 * Funcion resetInstructionsProgram
*/
void resetInstructionsProgram(Program *program){
	int i;
	for (i=0;i<100000;i++){
		resetInstruction(&program->instructions[i]);
	}
}

/*
 * Funcion resetInstructionStepsProgram
*/
void resetInstructionStepsProgram(Program *program){
	int i;
	for (i=0;i<5;i++){
		resetInstruction(&program->instructionsSteps[i]);
	}
}

/*
 * Funcion resetInstructionsBuffers
*/
void resetInstructionsBuffers(Program *program){
	resetInstruction(&program->buffers[0].instruction);
	resetInstruction(&program->buffers[1].instruction);
	resetInstruction(&program->buffers[2].instruction);
	resetInstruction(&program->buffers[3].instruction);

}

/*
 * Funcion resetAllInstructions
*/
void resetAllInstructions(Program *program){
	resetInstructionsProgram(program);
	resetInstructionStepsProgram(program);
	resetInstructionsBuffers(program);
}

/*
 * Funcion loadInstructions
*/
void loadInstructions(Program *program,char *filename){
    FILE* file;
	file = fopen(filename,"r");
	char buffer[40];
    while (!feof(file)){

		memset(buffer,0,sizeof(buffer));

		fscanf(file,"%s",buffer);
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
			program->counterInstruction++;
		}
		else if (
		!strcmp(buffer,"lw") ||
		!strcmp(buffer,"sw")
		){
			instructionInit(&program->instructions[program->counterInstruction]);
			strcpy(program->instructions[program->counterInstruction].function , buffer);
			fscanf(file," %[^','], %[^'('](%[^')']",program->instructions[program->counterInstruction].a1,program->instructions[program->counterInstruction].a2,program->instructions[program->counterInstruction].a3);
			program->instructions[program->counterInstruction].arguments = 3;
			program->counterInstruction++;

		}
		else if (
		!strcmp(buffer,"la")
		){
			instructionInit(&program->instructions[program->counterInstruction]);
			strcpy(program->instructions[program->counterInstruction].function , buffer);
			fscanf(file," %[^','], (%[^')']",program->instructions[program->counterInstruction].a1,program->instructions[program->counterInstruction].a2);
			program->instructions[program->counterInstruction].arguments = 2;
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
			program->counterInstruction++;
		}
		else if (buffer[strlen(buffer)-1] == ':'){
			buffer[strlen(buffer)-1] = '\0';
			strcpy(program->labels[program->counterLabel].name,buffer);
			program->labels[program->counterLabel].PC = program->counterInstruction;
			program->counterLabel++;
		}
    }
}

/*
 * Funcion resetBuffer
*/
void resetBuffer(Buffer *buffer){

	resetInstruction(&buffer->instruction);

	int j;
	for (j=0;j<10;j++){
		buffer->linesControl[j] = '0';
	}
	buffer->add_pc = 0;
	buffer->readData1 = 0;
	buffer->readData2 = 0;
	buffer->signExtend = 0;
	buffer->zero = 0;
	buffer->aluResult = 0;
	buffer->addResult = 0;
	buffer->readData = 0;
	strcpy(buffer->rs,"");
	strcpy(buffer->rt,"");
	strcpy(buffer->rd,"");
	strcpy(buffer->muxRegDst,"");

}

/*
 * Funcion initBuffers
*/
void initBuffers(Program *program){
	int i;
	for (i=0;i<4;i++){
		resetBuffer(&program->buffers[i]);
	}
}

/*
 * Funcion programInit
*/
Program* programInit(char *filename,char *fileName2){
	Program *program=(Program*)malloc(sizeof(Program));
	program->PC=0;
	program->counterInstruction=0;
	program->counterLabel=0;
	resetAllInstructions(program);
	nameRegistersInit(program);
    initRegisters(program,fileName2);
    loadInstructions(program,filename);
	initBuffers(program);
	upRegisters(program);


	return program;
}

/*
 * Funcion exInstruction
*/
void exInstruction(Instruction instruction,Program *program,int step){
		if(!strcmp(instruction.function,"add")){
            add(instruction,program,step);
        }
        else if(!strcmp(instruction.function,"sub")){
            //sub(instruction,program,step);
        }
        else if(!strcmp(instruction.function,"addi")){
            addi(instruction,program,step);
        }
        else if(!strcmp(instruction.function,"subi")){
            //subi(instruction,program,step);
        }
        else if(!strcmp(instruction.function,"mul")){
            mul(instruction,program,step);
        }
        else if(!strcmp(instruction.function,"div")){
            //div_m(instruction,program,step);
        }
        else if(!strcmp(instruction.function,"beq")){
       		beq(instruction,program,step);

        }
        else if(!strcmp(instruction.function,"blt")){
       		//blt(instruction,program,step);
        }
        else if(!strcmp(instruction.function,"bgt")){
       		//bgt(instruction,program,step);

        }
        else if(!strcmp(instruction.function,"lw")){
       		lw(instruction,program,step);
        }
        else if(!strcmp(instruction.function,"sw")){
       		sw(instruction,program,step);
        }
        else if(!strcmp(instruction.function,"la")){
       		//la(instruction,program,step);
        }
        else if(!strcmp(instruction.function,"j")){
       		jump(instruction,program,step);
        }
        else if(!strcmp(instruction.function,"jal")){
       		jal(instruction,program,step);
        }
        else if(!strcmp(instruction.function,"jr")){
       		jr(instruction,program,step);
        }
		else if(!strcmp(instruction.function,"Empty")){
			empty(instruction,program,step);
		}

}

/*
 * Funcion checkEmptysInstructionsBuffers
*/
int checkEmptysInstructionsBuffers(Program *program){
	int i;
	for (i=0;i<4;i++){

		if (strcmp(program->buffers[i].instruction.function,"Empty")){
			return 0;
		}
	}
	return 1;
}

/*
 * Funcion updateBufferIF
*/
void updateBufferIF(Instruction in,Program *program){
	resetBuffer(&program->buffers[0]);
	program->PC++;
	program->buffers[0].instruction = in;
	setLinesControl(in,program);
	int i;
	for (i=0;i<10;i++){
		program->buffers[0].linesControl[i] = program->linesControl[i];
	}
	program->buffers[0].add_pc = program->PC*4;
}

/*
 * Funcion fordwarding
*/
void fordwarding(Program *program){

	if ((program->buffers[2].linesControl[9] == '1')
		&& (strcmp(program->buffers[2].muxRegDst,"$zero"))
		&& (!strcmp(program->buffers[2].muxRegDst,program->buffers[1].rs))
		){
			program->buffers[1].readData1 = program->buffers[2].aluResult;

	}
	if ((program->buffers[2].linesControl[9] == '1')
		&& (strcmp(program->buffers[2].muxRegDst,"$zero"))
		&& (!strcmp(program->buffers[2].muxRegDst,program->buffers[1].rt))
		){
			program->buffers[1].readData2 = program->buffers[2].aluResult;
	}

	if (program->buffers[3].linesControl[9] == '1' //regWrite
		&& strcmp(program->buffers[3].muxRegDst,"$zero")
		&& !strcmp(program->buffers[3].muxRegDst,program->buffers[1].rs)
	){
		if(program->buffers[3].linesControl[3] == '1' ){
			program->buffers[1].readData1 = program->buffers[3].readData;
		}
		else{
			program->buffers[1].readData1 = program->buffers[3].aluResult;
		}
	}
	if (program->buffers[3].linesControl[9] == '1'//regWrite
		 //memRead
		&& strcmp(program->buffers[3].muxRegDst,"$zero")
		&& !strcmp(program->buffers[3].muxRegDst,program->buffers[1].rt)
	){
		if(program->buffers[3].linesControl[3] == '1'){
			program->buffers[1].readData2 = program->buffers[3].readData;
		}
		else{
			program->buffers[1].readData2 = program->buffers[3].aluResult;
		}
	}
}

/*
 * Funcion is_nop
*/
int is_nop(Program *program){

	if(program->buffers[1].linesControl[3] == '1' &&
	strcmp(program->buffers[1].instruction.function,"Empty") &&
	(!strcmp(program->buffers[1].rt,program->buffers[0].rs) ||
	(!strcmp(program->buffers[1].rt,program->buffers[0].rt)))
	){
		return 1;
	}
	else{
		return 0;
	}
}

/*
 * Funcion loadInstructionsSteps
*/
void loadInstructionsSteps(Instruction in, Program *program){
	program->instructionsSteps[4] = program->instructionsSteps[3];
	program->instructionsSteps[3] = program->instructionsSteps[2];
	program->instructionsSteps[2] = program->instructionsSteps[1];
	program->instructionsSteps[1] = program->instructionsSteps[0];
	program->instructionsSteps[0] = in;
}

/*
 * Funcion exProgram
*/
void exProgram(Program* program,char* nameFileR, char* nameFileB){
	//Abre los archivos y los rellena con el codigo base para html
	FILE* file_buffers = openFileHtml(nameFileB);
	FILE* file_registros = openFileHtml(nameFileR);
	fprintNameBuffersHtml(file_buffers);
	fprintNameRegistersHtml(file_registros,program);
	//fin de agregar el codigo base de html
	upRegisters(program);
	int  cycle = 1;
	do{
		//fprintBuffersHtml(file_buffers,program,cycle);
		fordwarding(program);
		loadInstructionsSteps(program->instructions[program->PC], program);
		exInstruction(program->instructionsSteps[4],program,4);
		exInstruction(program->instructionsSteps[3],program,3);
		exInstruction(program->instructionsSteps[2],program,2);
		exInstruction(program->instructionsSteps[1],program,1);
		if (is_nop(program)){
			resetBuffer(&program->buffers[0]);

		}
		else{
			exInstruction(program->instructionsSteps[0],program,0);
		}
		fprintBuffersHtml(file_buffers,program,cycle);
		fprintRegistersHtml(file_registros,program,cycle);
		upRegisters(program);
		cycle++;
	}while(!checkEmptysInstructionsBuffers(program));
	closeFileHtml(file_buffers);
	closeFileHtml(file_registros);
}
