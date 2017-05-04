void functionIF(Instruction in,Program *program){
	resetBuffer(&program->buffers[0]);
	program->PC++;
	program->buffers[0].instruction = in;
	setLinesControl(in,program);
	int i;
	for (i=0;i<10;i++){
		program->buffers[0].linesControl[i] = program->linesControl[i];
	}
	program->buffers[0].add_pc = program->PC*4;


	//Listo
	if (
	   !strcmp(in.function,"add") ||
	   !strcmp(in.function,"sub") ||
	   !strcmp(in.function,"mul") ||
	   !strcmp(in.function,"div")
	   ){
			strcpy(program->buffers[0].rs,in.a2);
   			strcpy(program->buffers[0].rt,in.a3);
   			strcpy(program->buffers[0].rd,in.a1);
   			strcpy(program->buffers[0].muxRegDst,in.a1);
   }
   //Listo
   else if(
	   !strcmp(in.function,"addi") ||
		   !strcmp(in.function,"subi")){
			strcpy(program->buffers[0].rs,in.a2);
   			strcpy(program->buffers[0].rt,in.a1);
   			strcpy(program->buffers[0].rd,"");
   			program->buffers[0].signExtend=atoi(in.a3);
			strcpy(program->buffers[0].muxRegDst,in.a1);

   }
   //Nose si listo
   else if(
	   !strcmp(in.function,"beq") ||
	   !strcmp(in.function,"blt") ||
	   !strcmp(in.function,"bgt")){
			strcpy(program->buffers[0].rs,in.a1);
   			strcpy(program->buffers[0].rt,in.a2);
   			program->buffers[0].signExtend = getPClabel(in.a3,program);


   }
   //Nose si listo
   else if (
	   !strcmp(in.function,"j") ||
	   !strcmp(in.function,"jal")

	   ){
		   strcpy( program->buffers[0].rt, "$ra");
		   strcpy( program->buffers[0].muxRegDst, "$ra");
		   //program->buffers[0].muxRegDst = "$ra";
		   program->buffers[0].signExtend = getPClabel(in.a1,program);

		   //TRUCO
		   int aux = program->PC;
		   program->PC=getPClabel(in.a1,program);
		   if (!strcmp(in.function,"jal")){

			   program->registers[getIndexRegister("$ra",program)] = aux;
		   }
           //program->PC-=1;



   }
   else if (!strcmp(in.function,"jr")){
	   		strcpy(program->buffers[0].rt,in.a1);
			strcpy(program->buffers[0].muxRegDst,in.a1);
   }
   else if (
	   !strcmp(in.function,"lw") ||
	   !strcmp(in.function,"la")
	   ){

			strcpy(program->buffers[0].rs,in.a3);
   			strcpy(program->buffers[0].rt,in.a1);
   			program->buffers[0].signExtend = atoi(in.a2);
			strcpy(program->buffers[0].muxRegDst,in.a1);

   }
   else if (
	   !strcmp(in.function,"sw")
	   ){
			strcpy(program->buffers[0].rs,in.a3);
   			strcpy(program->buffers[0].rt,in.a1);
			program->buffers[0].signExtend = atoi(in.a2);
			strcpy(program->buffers[0].muxRegDst,in.a1);


   }
   else if((!strcmp(in.function,"Empty")) || (!strcmp(in.function,"NOP"))) {
	   	strcpy(program->buffers[0].rs,"");
		strcpy(program->buffers[0].rt,"");
		strcpy(program->buffers[0].rd,"");
		strcpy(program->buffers[0].muxRegDst,"");
   }


}
void functionID(Program *program){
	//printf("hola\n" );
	program->buffers[1] = program->buffers[0];
	if (!strcmp(program->buffers[1].instruction.function,"jr")){
		printf("hola\n" );
		int index;
		index = getIndexRegister(program->buffers[1].rt,program);
		program->PC=program->registers[index];
		printf("pc: %d\n",program->PC );
	}
	else if (program->buffers[1].linesControl[1] == '1'){
		program->PC=getPClabel(program->buffers[1].instruction.a1,program);
	}

	/*
	printf("%s\n", program->buffers[1].instruction.function);
	program->buffers[1].readData1 = program->registers[getIndexRegister(program->buffers[1].rs,program)];
	program->buffers[1].readData2 = program->registers[getIndexRegister(program->buffers[1].rt,program)];
	*/
	program->buffers[1].readData1 = program->registers[getIndexRegister(program->buffers[1].rs,program)];
	program->buffers[1].readData2 = program->registers[getIndexRegister(program->buffers[1].rt,program)];
}
void functionEX(Program *program){
	program->buffers[2] = program->buffers[1];

	if (!strcmp(program->buffers[2].instruction.function,"add") ){
		program->buffers[2].aluResult = program->buffers[2].readData1 + program->buffers[2].readData2;
	}
	else if (!strcmp(program->buffers[2].instruction.function,"sub") ){
		program->buffers[2].aluResult = program->buffers[2].readData1 - program->buffers[2].readData2;
	}
	else if (!strcmp(program->buffers[2].instruction.function,"mul") ){
		program->buffers[2].aluResult = program->buffers[2].readData1 * program->buffers[2].readData2;
	}
	else if (!strcmp(program->buffers[2].instruction.function,"div") ){
		program->buffers[2].aluResult = program->buffers[2].readData1 / program->buffers[2].readData2;
	}
	else if (!strcmp(program->buffers[2].instruction.function,"addi") ){
		printf("pc: %d\n",program->PC );
		showInstruction(program->buffers[2].instruction);
		printf("addi\n");
		program->buffers[2].aluResult = program->buffers[2].readData1 + program->buffers[2].signExtend;
	}

	else if (!strcmp(program->buffers[2].instruction.function,"subi") ){
		//printf("addii\n" );
		program->buffers[2].aluResult = program->buffers[2].readData1 - program->buffers[2].signExtend;
	}
	else if (!strcmp(program->buffers[2].instruction.function,"sw") ){
		program->buffers[2].aluResult = program->buffers[2].readData2 + program->buffers[2].signExtend;
	}
	else if (!strcmp(program->buffers[2].instruction.function,"lw") ){
		program->buffers[2].aluResult = program->buffers[2].readData2 + program->buffers[2].signExtend;
	}

}
void functionMEM(Program *program){
	program->buffers[3] = program->buffers[2];
	int dir, offset, index;
	if (program->buffers[3].linesControl[7] == '1'){
		if(!strcmp(program->buffers[3].rs,"$sp")){
			dir = program->buffers[3].aluResult/4;
			index = getIndexRegister(program->buffers[3].muxRegDst,program);
            program->stackMemory[dir]= program->registers[index];
			printf("Valor: %d\n", program->stackMemory[dir]);
			printf("dir: %d\n",dir );

        }
        else{
			dir = program->buffers[3].aluResult/4;
			index = getIndexRegister(program->buffers[3].muxRegDst,program);
            program->heapMemory[dir]= program->registers[index];
			printf("valor heap: %d\n", program->heapMemory[dir] );
			printf("dir: %d\n",dir );
		}
	}
	if (program->buffers[3].linesControl[3] == '1'){
		if(!strcmp(program->buffers[3].rs,"$sp")){
			dir = program->buffers[3].aluResult/4;
			index = getIndexRegister(program->buffers[3].muxRegDst,program);
            program->buffers[3].readData = program->stackMemory[dir];
			showInstruction(program->buffers[3].instruction);
			printf("lw valor read data sp: %d\n",program->buffers[3].readData  );
			printf("lw dir: %d\n",dir );
        }
        else{
			dir = program->buffers[3].aluResult/4;
			index = getIndexRegister(program->buffers[3].muxRegDst,program);
            program->buffers[3].readData = program->heapMemory[dir];
			printf("lw valor read data heap: %d\n",program->buffers[3].readData  );

			printf("lw dir: %d\n",dir );
        }
	}
	if (!strcmp(program->buffers[3].instruction.function,"beq")){
		if(program->registers[getIndexRegister(program->buffers[3].instruction.a1,program)]== program->registers[getIndexRegister(program->buffers[3].instruction.a2,program)] ){
            program->PC=getPClabel(program->buffers[3].instruction.a3,program);
			printf("necesita un flush %d\n",program->PC );
			int i;
			for (i=0;i<3;i++){
				resetBuffer(&program->buffers[i]);
				printf("holaa123\n" );
			}
        }
	}

}
void functionWB(Program *program){
	int index;
	if (program->buffers[3].linesControl[9] == '1'){
		if (program->buffers[3].linesControl[4] == '0'){
			index = getIndexRegister(program->buffers[3].muxRegDst,program);
			program->registers[index] =  program->buffers[3].aluResult;
		}
		else if (program->buffers[3].linesControl[4] == '1'){
			index = getIndexRegister(program->buffers[3].muxRegDst,program);
			program->registers[index] = program->buffers[3].readData;
		}
	}
}
