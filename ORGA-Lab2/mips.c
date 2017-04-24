#include <stdio.h>
#include <stdlib.h> //para el atoi!
#include <string.h>
#include "estructuras.h"
#include "funciones.h"
#include "fprint.h"

#ifndef _FUNCIONES_MIPS
#define _FUNCIONES_MIPS
void add(Instruction in ,Program* program,FILE* linesControl,FILE* traza,int etapa){
    //Traza
    fprintInstruction(traza,in);
    fprintTitle(traza,program);
    //IF
    if (etapa == 1){

        fprintf(traza,"%3d",program->PC*4);
        fprintf(traza," IF  ");
        fprintRegisters(traza,program);
        fprintf(traza,"\n");
    }
    //ID
    else if (etapa == 2){

        fprintf(traza,"%3d",program->PC*4);
        fprintf(traza," ID  ");
        fprintRegisters(traza,program);
        fprintf(traza,"\n");
    }
    //EX
    else if (etapa == 3){

        fprintf(traza,"%3d",program->PC*4);
        fprintf(traza," EX  ");
        fprintRegisters(traza,program);
        fprintf(traza,"\n");
    }
    //MEM
    else if (etapa == 4){

        fprintf(traza,"%3d",program->PC*4);
        fprintf(traza," MEM ");
        fprintRegisters(traza,program);
        fprintf(traza,"\n");
    }
    //WB
    else if (etapa == 5){

        program->registers[getIndexRegister(in.a1,program)] = program->registers[getIndexRegister(in.a2,program)] + program->registers[getIndexRegister(in.a3,program)];
        fprintf(traza,"%3d",program->PC*4   );
        fprintf(traza," WB  ");
        fprintRegisters(traza,program);
        fprintf(traza,"\n\n");
    }






}
void sub(Instruction in ,Program* program,FILE* linesControl,FILE* traza){
    fprintInstruction(traza,in);
    fprintTitle(traza,program);
    //IF
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," IF  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //ID
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," ID  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //EX
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," EX  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //MEM
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," MEM ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //WB
    program->registers[getIndexRegister(in.a1,program)] = program->registers[getIndexRegister(in.a2,program)] - program->registers[getIndexRegister(in.a3,program)];
    fprintf(traza,"%3d",program->PC*4   );
    fprintf(traza," WB  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n\n");
}
void addi(Instruction in ,Program* program,FILE* linesControl,FILE* traza){
    fprintInstruction(traza,in);
    fprintTitle(traza,program);
    //IF
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," IF  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //ID
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," ID  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //EX
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," EX  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //MEM
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," MEM ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //WB
    program->registers[getIndexRegister(in.a1,program)] = program->registers[getIndexRegister(in.a2,program)] + atoi(in.a3);
    fprintf(traza,"%3d",program->PC*4   );
    fprintf(traza," WB  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n\n");
}
void subi(Instruction in ,Program* program,FILE* linesControl,FILE* traza){
    fprintInstruction(traza,in);
    fprintTitle(traza,program);
    //IF
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," IF  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //ID
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," ID  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //EX
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," EX  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //MEM
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," MEM ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //WB
    program->registers[getIndexRegister(in.a1,program)] = program->registers[getIndexRegister(in.a2,program)] - atoi(in.a3);
    fprintf(traza,"%3d",program->PC*4   );
    fprintf(traza," WB  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n\n");
}
void mul(Instruction in ,Program* program,FILE* linesControl,FILE* traza){
    fprintInstruction(traza,in);
    fprintTitle(traza,program);
    //IF
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," IF  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //ID
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," ID  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //EX
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," EX  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //MEM
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," MEM ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //WB
    program->registers[getIndexRegister(in.a1,program)] = program->registers[getIndexRegister(in.a2,program)] * program->registers[getIndexRegister(in.a3,program)];
    fprintf(traza,"%3d",program->PC*4   );
    fprintf(traza," WB  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n\n");
}
void div_m(Instruction in ,Program* program,FILE* linesControl,FILE* traza){
    fprintInstruction(traza,in);
    fprintTitle(traza,program);
    //IF
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," IF  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //ID
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," ID  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //EX
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," EX  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //MEM
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," MEM ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //WB
    program->registers[getIndexRegister(in.a1,program)] = program->registers[getIndexRegister(in.a2,program)] / program->registers[getIndexRegister(in.a3,program)];
    fprintf(traza,"%3d",program->PC*4   );
    fprintf(traza," WB  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n\n");
}
void beq(Instruction in ,Program* program,FILE* linesControl,FILE* traza){
    fprintInstruction(traza,in);
    fprintTitle(traza,program);
    //IF
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," IF  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //ID
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," ID  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //EX
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," EX  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //MEM
    if(program->registers[getIndexRegister(in.a1,program)]== program->registers[getIndexRegister(in.a2,program)] ){
        program->PC=getPClabel(in.a3,program);
    }

    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," MEM ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //WB
    fprintf(traza,"%3d",program->PC*4   );
    fprintf(traza," WB  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n\n");
    if(program->registers[getIndexRegister(in.a1,program)] == program->registers[getIndexRegister(in.a2,program)] ){
        program->PC-=1; //eso es porque siempre aumenta en 1 al final de la instruccion con el -1 se equilibra asi salta a la instruccion correcta
    }
}
void blt(Instruction in ,Program* program,FILE* linesControl,FILE* traza){
    fprintInstruction(traza,in);
    fprintTitle(traza,program);
    //IF
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," IF  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //ID
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," ID  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //EX
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," EX  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //MEM
    if(program->registers[getIndexRegister(in.a1,program)] < program->registers[getIndexRegister(in.a2,program)] ){
        program->PC=getPClabel(in.a3,program);
    }

    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," MEM ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //WB
    fprintf(traza,"%3d",program->PC*4   );
    fprintf(traza," WB  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n\n");
    if(program->registers[getIndexRegister(in.a1,program)] < program->registers[getIndexRegister(in.a2,program)] ){
        program->PC-=1; //eso es porque siempre aumenta en 1 al final de la instruccion con el -1 se equilibra asi salta a la instruccion correcta
    }


}
void bgt(Instruction in ,Program* program,FILE* linesControl,FILE* traza){
    fprintInstruction(traza,in);
    fprintTitle(traza,program);
    //IF
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," IF  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //ID
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," ID  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //EX
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," EX  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //MEM
    if(program->registers[getIndexRegister(in.a1,program)] > program->registers[getIndexRegister(in.a2,program)] ){
        //printf("%s = %d\n",in.r3,getPClabel(in.r3,program));
        program->PC=getPClabel(in.a3,program);
    }

    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," MEM ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //WB
    fprintf(traza,"%3d",program->PC*4   );
    fprintf(traza," WB  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n\n");
    if(program->registers[getIndexRegister(in.a1,program)] > program->registers[getIndexRegister(in.a2,program)] ){
        // program->PC-=1; //eso es porque siempre aumenta en 1 al final de la instruccion con el -1 se equilibra asi salta a la instruccion correcta
    }
}
void jump(Instruction in ,Program* program,FILE* linesControl,FILE* traza){
    fprintInstruction(traza,in);
    fprintTitle(traza,program);
    //IF
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," IF  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //ID
    //printf("jump: %d\n",getPClabel(in.r1,program));
    program->PC=getPClabel(in.a1,program);
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," ID  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //EX
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," EX  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //MEM
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," MEM ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //WB
    fprintf(traza,"%3d",program->PC*4   );
    fprintf(traza," WB  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n\n");
    program->PC-=1; //eso es porque siempre aumenta en 1 al final de la instruccion con el -1 se equilibra asi salta a la instruccion correcta
}
void jal(Instruction in ,Program* program,FILE* linesControl,FILE* traza){
    fprintInstruction(traza,in);
    fprintTitle(traza,program);
    //IF
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," IF  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //ID
    //printf("jump: %d\n",getPClabel(in.r1,program));
    int aux = program->PC;
    program->PC=getPClabel(in.a1,program);
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," ID  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //EX
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," EX  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //MEM
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," MEM ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //WB
    //printf("JAL RA: %d\n",program->registers[getIndexRegister("$ra",program)]);
    program->registers[getIndexRegister("$ra",program)] = aux+1;
    //printf("JAL RA: %d\n",program->registers[getIndexRegister("$ra",program)]);
    fprintf(traza,"%3d",program->PC*4   );
    fprintf(traza," WB  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n\n");
    program->PC-=1; //eso es porque siempre aumenta en 1 al final de la instruccion con el -1 se equilibra asi salta a la instruccion correcta

}
void jr(Instruction in ,Program* program,FILE* linesControl,FILE* traza){
    fprintInstruction(traza,in);
    fprintTitle(traza,program);
    //IF
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," IF  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //ID
    //printf("jump: %d\n",getPClabel(in.r1,program));

    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," ID  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //EX
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," EX  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //MEM
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," MEM ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //WB
    //printf("JR PC: %d\n",program->PC);
    program->PC=program->registers[getIndexRegister(in.a1,program)];
    //printf("JR PC: %d\n",program->PC);
    fprintf(traza,"%3d",program->PC*4   );
    fprintf(traza," WB  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n\n");
    program->PC-=1; //eso es porque siempre aumenta en 1 al final de la instruccion con el -1 se equilibra asi salta a la instruccion correcta

}
void la(Instruction in ,Program* program,FILE* linesControl,FILE* traza){
    fprintInstruction(traza,in);
    fprintTitle(traza,program);
    //IF
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," IF  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //ID
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," ID  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //EX
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," EX  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //MEM
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," MEM ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //WB
    //int dir = program->registers[getIndexRegister(in.r2,program)]/4;
    //program->registers[getIndexRegister(in.r1,program)] = program->heapMemory[dir];
    program->registers[getIndexRegister(in.a1,program)] =program->registers[getIndexRegister(in.a2,program)];
    fprintf(traza,"%3d",program->PC*4   );
    fprintf(traza," WB  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n\n");

}
void lw(Instruction in ,Program* program,FILE* linesControl,FILE* traza){
    fprintInstruction(traza,in);
    fprintTitle(traza,program);
    //IF
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," IF  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //ID
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," ID  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //EX
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," EX  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //MEM
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," MEM ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //WB
    if(!strcmp(in.a3,"$sp")){
        int dir = -program->registers[getIndexRegister(in.a3,program)]/4;
        int offset = -atoi(in.a2)/4;
        dir+=offset;
        program->registers[getIndexRegister(in.a1,program)] = program->stackMemory[dir];

    }
    else{
        int dir = program->registers[getIndexRegister(in.a3,program)]/4;
        int offset = atoi(in.a2)/4;
        dir+=offset;
        program->registers[getIndexRegister(in.a1,program)] = program->heapMemory[dir];

    }

    fprintf(traza,"%3d",program->PC*4   );
    fprintf(traza," WB  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n\n");
}
void sw(Instruction in ,Program* program,FILE* linesControl,FILE* traza){
    fprintInstruction(traza,in);
    fprintTitle(traza,program);
    //IF
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," IF  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //ID
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," ID  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //EX
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," EX  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //MEM
    fprintf(traza,"%3d",program->PC*4);
    fprintf(traza," MEM ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n");
    //WB
    if(!strcmp(in.a3,"$sp")){
        int dir = -program->registers[getIndexRegister(in.a3,program)]/4;
        int offset = -atoi(in.a2)/4;
        dir+=offset;

        program->stackMemory[dir]= program->registers[getIndexRegister(in.a1,program)];

    }
    else{
        int dir = program->registers[getIndexRegister(in.a3,program)]/4;
        int offset = atoi(in.a2)/4;
        dir+=offset;
        program->heapMemory[dir]=program->registers[getIndexRegister(in.a1,program)];

    }
    //program->heapMemory[0];
    //program->heapMemory[1];
    //program->stackMemory[0];
    //program->stackMemory[6];
    fprintf(traza,"%3d",program->PC*4   );
    fprintf(traza," WB  ");
    fprintRegisters(traza,program);
    fprintf(traza,"\n\n");
}
#endif
