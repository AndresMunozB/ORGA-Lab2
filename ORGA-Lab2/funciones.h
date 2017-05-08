#include "estructuras.h"

#ifndef _FUNCIONES_H
#define _FUNCIONES_H
/*
 * Funcion existFile
 * Funcion que verifica si un archivo de texto plano existe
 * @param char* filename, nombre del archivo
 * @return entero 1 en caso de que si exista y 0 en caso contrario
*/
int existsFile(char* filename);
/*
 * Funcion showInstruction
 * Funcion que muestra en consola una instruccion
 * @param Instruction instruction, instruccion que se desea mostrar
*/
void showInstruction(Instruction instruction);
/*
 * Funcion showRegisters
 * Funcion que escribe muestra en pantalla los registros del programa
 * @param Program* program, programa del cual se obtendran los registros
*/
void showRegisters(Program* program);
/*
 * Funcion showLabels
 * Funcion que escribe muestra en pantalla las etiquetas contenidas en el programa
 * @param Program* program, programa del cual se obtendran las etiquetas
*/
void showLabels(Program* program);
/*
 * Funcion instructionInit
 * Funcion que inicializa una instruccion, esto quiere decir que elimina la basura contenida en ella
 * @param Instruction* ins, direccion de memoria de la instruccion que se desea inicializar
*/
void instructionInit(Instruction* ins);
/*
 * Funcion getIndexRegister
 * Funcion que busca el indice del registro entregado
 * @param char *strRegister,Program* program. strRegister refiere al registro del cual se obtendra el indice dentro de los registros del programa
 * @return entero, indice del registro en el arreglo de registros del programa
*/
int getIndexRegister(char *strRegister,Program* program );
/*
 * Funcion getPClabel
 * Funcion que entrega el program counter a la cual apunta una etiqueta
 * @param char* label,Program* program, label refiere a la etiqueta de la cual se obtendra el PC
 * @return entero, PC a la cual apunta la etiqueta entregada
*/
int getPClabel(char* label,Program* program);
/*
 * Funcion setLinesControl
 * Funcion que modifica el arreglo de las lineas de control del programa segun la instruccion entregada
 * @param Instruction in,Program* program, instruccion para cambiar las lineas de control del programa
*/
void setLinesControl(Instruction in,Program* program);

void nameRegistersInit(Program *program);

void registersInit(Program *program);

void upRegisters(Program *program);

void resetInstruction(Instruction *in);

void resetInstructionsProgram(Program *program);

void resetInstructionStepsProgram(Program *program);

void resetInstructionsBuffers(Program *program);

void resetAllInstructions(Program *program);

void loadInstructions(Program *program,char *filename);

void resetBuffer(Buffer *buffer);

void initBuffers(Program *program);
/*
 * Funcion existFile
 * Funcion que inicializa una estructura program y retorna la direccion de momoria
 * @param char* filename, nombre del archivo del cual se cargara el programa
 * @return direccion de memoria de una estructura Program inicializada
*/
Program* programInit(char *filename,char *fileName2);

void exInstruction(Instruction instruction,Program *program,int step);

int checkEmptysInstructionsBuffers(Program *program);

void updateBufferIF(Instruction in,Program *program);

void fordwarding(Program *program);

int is_nop(Program *program);

void loadInstructionsSteps(Instruction in, Program *program);

/*
 * Funcion exProgram
 * Funcion ejecuta un programa ya cargado
 * @param Program* program,char* nameFileR, char* nameFileB, program es el programa que se va a ejecutar
                            nameFileR es el nombre del archivo de salida para las lineas de control de cada instruccion
                            nameFileB es el nombre del archivo de salida para la traza de las instrucciones contenidas en el programa
*/
void exProgram(Program* program,char* nameFileR, char* nameFileB);




#endif
