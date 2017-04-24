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


typedef struct IFID{
    Instruction in;
    char add_pc[30];

}IFID;


typedef struct IDEX{
    Instruction in;
    char add_pc[30];
    int aluSrc;
    int aluOp;
    int regDst;
    int branch;
    int memWrite;
    int memRead;
    int regWrite;
    int memToReg;
    int readData1;
    int readData2;
    int signExtend;
    char Rs[7];
    char Rt[7];
    char Rd[7];

}IDEX;
typedef struct EXMEM{
    Instruction in;
    int branch;
    int memWrite;
    int memRead;
    int regWrite;
    int memToReg;
    int zero;
    int aluResult;
    int readData2;
    int addResult;
    char muxRegDst[7];
}EXMEM;
typedef struct MEMWB{
    Instruction in;
    int regWrite;
    int memToReg;
    int readData;
    int aluResult;
    char muRegDst[7];

}MEMWB;
typedef struct Program{

	int PC;
	int counterInstruction;
	int counterLabel;
	long registers[32];
	int heapMemory[100000];
	int stackMemory[100000];
	char linesControl[10];
	char nameRegisters[32][7];
	Instruction instructions[100000];
	Label labels[50000];
    IFID ifid;
    IDEX idex;
    EXMEM exmem;
    MEMWB memwb;
    Instruction instBuffers[5];
}Program;




#endif
