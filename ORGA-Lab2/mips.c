#include <stdio.h>
#include <stdlib.h> //para el atoi!
#include <string.h>
#include "estructuras.h"
#include "funciones.h"
#include "fprint.h"

#ifndef _FUNCIONES_MIPS
#define _FUNCIONES_MIPS
//Listo
void empty(Instruction in,Program *program,int step){
    if (step == 0){
        updateBufferIF(in,program);
    }
    //ID
    else if (step == 1){
        program->buffers[1] = program->buffers[0];
    }
    //EX
    else if (step == 2){
        program->buffers[2] = program->buffers[1];
    }
    //MEM
    else if (step == 3){
        program->buffers[3] = program->buffers[2];
    }
    //WB
    else if (step == 4){
    }
}
//Listo
void add(Instruction in,Program *program,int step){
    //IF
    if (step == 0){
        updateBufferIF(in,program);
        strcpy(program->buffers[0].rs,in.a2);
        strcpy(program->buffers[0].rt,in.a3);
        strcpy(program->buffers[0].rd,in.a1);
        strcpy(program->buffers[0].muxRegDst,in.a1);
    }
    //ID
    else if (step == 1){
        program->buffers[1] = program->buffers[0];
        program->buffers[1].readData1 = program->registers[getIndexRegister(program->buffers[1].rs,program)];
    	program->buffers[1].readData2 = program->registers[getIndexRegister(program->buffers[1].rt,program)];
    }
    //EX
    else if (step == 2){
        program->buffers[2] = program->buffers[1];
        program->buffers[2].aluResult = program->buffers[2].readData1 + program->buffers[2].readData2;
    }
    //MEM
    else if (step == 3){
        program->buffers[3] = program->buffers[2];
    }
    //WB
    else if (step == 4){
        int index;
        index = getIndexRegister(program->buffers[3].muxRegDst,program);
        program->registers[index] =  program->buffers[3].aluResult;
    }
}
//Listo
void addi(Instruction in,Program *program,int step){
    //IF
    if (step == 0){
        updateBufferIF(in,program);
        strcpy(program->buffers[0].rs,in.a2);
        strcpy(program->buffers[0].rt,in.a1);
        strcpy(program->buffers[0].rd,"");
        program->buffers[0].signExtend=atoi(in.a3);
        strcpy(program->buffers[0].muxRegDst,in.a1);
    }
    //ID
    else if (step == 1){
        program->buffers[1] = program->buffers[0];
        program->buffers[1].readData1 = program->registers[getIndexRegister(program->buffers[1].rs,program)];
    	program->buffers[1].readData2 = program->registers[getIndexRegister(program->buffers[1].rt,program)];
    }
    //EX
    else if (step == 2){
        program->buffers[2] = program->buffers[1];
        program->buffers[2].aluResult = program->buffers[2].readData1 + program->buffers[2].signExtend;
    }
    //MEM
    else if (step == 3){
        program->buffers[3] = program->buffers[2];
    }
    //WB
    else if (step == 4){
        int index;
        index = getIndexRegister(program->buffers[3].muxRegDst,program);
        program->registers[index] =  program->buffers[3].aluResult;
    }
}
//Listo
void mul(Instruction in,Program *program,int step){
    //IF
    if (step == 0){
        updateBufferIF(in,program);
        strcpy(program->buffers[0].rs,in.a2);
        strcpy(program->buffers[0].rt,in.a3);
        strcpy(program->buffers[0].rd,in.a1);
        strcpy(program->buffers[0].muxRegDst,in.a1);
    }
    //ID
    else if (step == 1){
        program->buffers[1] = program->buffers[0];
        program->buffers[1].readData1 = program->registers[getIndexRegister(program->buffers[1].rs,program)];
    	program->buffers[1].readData2 = program->registers[getIndexRegister(program->buffers[1].rt,program)];
    }
    //EX
    else if (step == 2){
        program->buffers[2] = program->buffers[1];
        program->buffers[2].aluResult = program->buffers[2].readData1 * program->buffers[2].readData2;
    }
    //MEM
    else if (step == 3){
        program->buffers[3] = program->buffers[2];
    }
    //WB
    else if (step == 4){
        int index;
        index = getIndexRegister(program->buffers[3].muxRegDst,program);
        program->registers[index] =  program->buffers[3].aluResult;
    }
}
//Listo
void beq(Instruction in,Program *program,int step){
    //IF
    if (step == 0){
        updateBufferIF(in,program);
        strcpy(program->buffers[0].rs,in.a1);
        strcpy(program->buffers[0].rt,in.a2);
        program->buffers[0].signExtend = getPClabel(in.a3,program);
    }
    //ID
    else if (step == 1){
        program->buffers[1] = program->buffers[0];
    }
    //EX
    else if (step == 2){
        program->buffers[2] = program->buffers[1];
    }
    //MEM
    else if (step == 3){
        program->buffers[3] = program->buffers[2];
        if(program->registers[getIndexRegister(program->buffers[3].instruction.a1,program)]== program->registers[getIndexRegister(program->buffers[3].instruction.a2,program)] ){
            program->PC=program->buffers[3].signExtend;
            program->instructionsSteps[0] = program->instructions[program->PC];
            resetInstruction(&program->instructionsSteps[1]);
            resetInstruction(&program->instructionsSteps[2]);
			int i;
			for (i=0;i<3;i++){
				resetBuffer(&program->buffers[i]);
			}
        }
    }
    //WB
    else if (step == 4){
    }
}
//Listo
void jump(Instruction in,Program *program,int step){
    //IF
    if (step == 0){
        updateBufferIF(in,program);
        program->buffers[0].signExtend = getPClabel(in.a1,program);
    }
    //ID
    else if (step == 1){
        program->buffers[1] = program->buffers[0];
        program->PC=program->buffers[1].signExtend;
        program->instructionsSteps[0] = program->instructions[program->PC];

    }
    //EX
    else if (step == 2){
        program->buffers[2] = program->buffers[1];
    }
    //MEM
    else if (step == 3){
        program->buffers[3] = program->buffers[2];
    }
    //WB
    else if (step == 4){
    }
}
//Listo
void jal(Instruction in,Program *program,int step){
    //IF
    if (step == 0){
        updateBufferIF(in,program);
        program->buffers[0].signExtend = getPClabel(in.a1,program);
        strcpy(program->buffers[0].rt,"$ra");
    }
    //ID
    else if (step == 1){
        program->buffers[1] = program->buffers[0];
        program->PC=program->buffers[1].signExtend;
        program->instructionsSteps[0] = program->instructions[program->PC];
    }
    //EX
    else if (step == 2){
        program->buffers[2] = program->buffers[1];
    }
    //MEM
    else if (step == 3){
        program->buffers[3] = program->buffers[2];
    }
    //WB
    else if (step == 4){
        int index;
        index = getIndexRegister("$ra",program);
        program->registers[index] = (program->buffers[3].add_pc/4);
    }
}
//Listo
void jr(Instruction in,Program *program,int step){
    //IF
    if (step == 0){
        updateBufferIF(in,program);
        strcpy(program->buffers[0].rt,in.a1);
        program->buffers[0].readData2 = program->registers[getIndexRegister(in.a1,program)];
        program->PC= program->buffers[0].readData2;
    }
    //ID
    else if (step == 1){
        program->buffers[1] = program->buffers[0];
    }
    //EX
    else if (step == 2){
        program->buffers[2] = program->buffers[1];
    }
    //MEM
    else if (step == 3){
        program->buffers[3] = program->buffers[2];
    }
    //WB
    else if (step == 4){
    }
}
//Listo
void lw(Instruction in,Program *program,int step){
    //IF
    if (step == 0){
        updateBufferIF(in,program);
        strcpy(program->buffers[0].rs,in.a3);
        strcpy(program->buffers[0].rt,in.a1);
        program->buffers[0].signExtend = atoi(in.a2);
        strcpy(program->buffers[0].muxRegDst,in.a1);
    }
    //ID
    else if (step == 1){
        program->buffers[1] = program->buffers[0];
        program->buffers[1].readData1 = program->registers[getIndexRegister(program->buffers[1].rs,program)];
    	program->buffers[1].readData2 = program->registers[getIndexRegister(program->buffers[1].rt,program)];
    }
    //EX
    else if (step == 2){
        program->buffers[2] = program->buffers[1];
        program->buffers[2].aluResult = program->buffers[2].readData1 + program->buffers[2].signExtend;
    }
    //MEM
    else if (step == 3){
        long dir,index;
        program->buffers[3] = program->buffers[2];
        if(!strcmp(program->buffers[3].rs,"$sp")){
			dir = program->buffers[3].aluResult/4;
			index = getIndexRegister(program->buffers[3].muxRegDst,program);
            program->buffers[3].readData = program->stackMemory[dir];
        }
        else{
			dir = program->buffers[3].aluResult/4;
			index = getIndexRegister(program->buffers[3].muxRegDst,program);
            program->buffers[3].readData = program->heapMemory[dir];
        }
    }
    //WB
    else if (step == 4){
        int index;
        index = getIndexRegister(program->buffers[3].muxRegDst,program);
        program->registers[index] = program->buffers[3].readData;
    }
}
//Listo
void sw(Instruction in,Program *program,int step){
    //IF
    if (step == 0){
        updateBufferIF(in,program);
        strcpy(program->buffers[0].rs,in.a3);
        strcpy(program->buffers[0].rt,in.a1);
        program->buffers[0].signExtend = atoi(in.a2);
    }
    //ID
    else if (step == 1){
        program->buffers[1] = program->buffers[0];
        program->buffers[1].readData1 = program->registers[getIndexRegister(program->buffers[1].rs,program)];
    	program->buffers[1].readData2 = program->registers[getIndexRegister(program->buffers[1].rt,program)];
    }
    //EX
    else if (step == 2){
        program->buffers[2] = program->buffers[1];
        program->buffers[2].aluResult = program->buffers[2].readData1 + program->buffers[2].signExtend;
    }
    //MEM
    else if (step == 3){
        long index,dir;
        program->buffers[3] = program->buffers[2];
        if(!strcmp(program->buffers[3].rs,"$sp")){
			dir = program->buffers[3].aluResult/4;
			index = getIndexRegister(program->buffers[3].rt,program);
            program->stackMemory[dir]= program->registers[index];
        }
        else{
			dir = program->buffers[3].aluResult/4;
			index = getIndexRegister(program->buffers[3].rt,program);
            program->heapMemory[dir]= program->registers[index];
		}
    }
    //WB
    else if (step == 4){

    }
}



#endif
