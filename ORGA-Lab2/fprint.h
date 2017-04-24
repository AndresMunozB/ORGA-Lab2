#ifndef FPRINT_H_INCLUDED
#define FPRINT_H_INCLUDED
/*
 * Funcion fprintInstruction
 * Funcion que escribe en un archivo la instruccion entregada
 * @param FILE* archivo,Instruction in, archivo en el cual se escribira, instruccion que se escribira
*/
void fprintInstruction(FILE* archivo,Instruction in);

/*
 * Funcion fprintRegisters
 * Funcion que escribe en un archivo los registros del programa
 * @param FILE* archivo, Program* program, archivo en el cual se escribira
*/
void fprintRegisters(FILE* archivo, Program* program);
/*
 * Funcion fprintLinesControl
 * Funcion que escribe en un archivo las lineas de control activadas del programa
 * @param FILE* archivo, Program* program, archivo en el cual se escribira
*/
void fprintLinesControl(FILE* archivo, Program* program);
/*
 * Funcion fprintTitle
 * Funcion que escribe en un archivo los nombres de los campos que se mostraran en una traza
 * @param FILE* archivo, Program* program, archivo en el cual se escribira
*/
void fprintTitle(FILE* archivo, Program* program);


void fprintRegistersHtml(Program* program);


#endif // FPRINT_H_INCLUDED
