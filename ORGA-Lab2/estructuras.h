#ifndef _STRUCTS_H_
#define _STRUCTS_H_

typedef struct Instruction{
	int arguments;
	char function[30];
	char a1[30];
	char a2[30];
	char a3[30];

}Instruction;

typedef struct Label{
	char name[30];
	int PC;
}Label;
/*
typedef struct IFID{
    Instruction instruction;
    char add_pc[30];

}IFID;

typedef struct IDEX{
    Instruction instruction;
    char add_pc[30];
    long aluSrc;
    long aluOp;
    long regDst;
    long branch;
    long memWrite;
    long memRead;
    long regWrite;
    long memToReg;
    long readData1;
    long readData2;
    long signExtend;
    char rs[7];
    char rt[7];
    char rd[7];

}IDEX;

typedef struct EXMEM{
    Instruction instruction;
    long branch;
    long memWrite;
    long memRead;
    long regWrite;
    long memToReg;
    long zero;
    long aluResult;
    long readData2;
    long addResult;
    char muxRegDst[7];
}EXMEM;

typedef struct MEMWB{
    Instruction instruction;
    long regWrite;
    long memToReg;
    long readData;
    long aluResult;
    char muRegDst[7];

}MEMWB;
*/
typedef struct Buffer{
	Instruction instruction;
	char linesControl[10];
	long add_pc;

    long readData1;
    long readData2;
    long signExtend;
    char rs[7];
    char rt[7];
    char rd[7];
	long zero;
    long aluResult;
    long addResult;
    char muxRegDst[7];
	long readData;
}Buffer;

typedef struct Program{

	int PC;
	int counterInstruction;
	int counterLabel;
	long registers[32];
	long registersCpy[32];
	int heapMemory[100000];
	int stackMemory[100000];
	char linesControl[10];
	char nameRegisters[32][7];
	Instruction instructions[100000];
	Label labels[50000];
    /*IFID ifid;
    IDEX idex;
    EXMEM exmem;
    MEMWB memwb;*/
    Instruction instructionsSteps[5];
	Buffer buffers[4];
}Program;


#endif
