void html(char *nameFile){
    FILE *file = fopen(nameFile,"w");
    fprintf("<!DOCTYPE html>\n
    <html>\n
    <head>\n
    <title>Titulo</title>\n
    </head>\n
    <body>\n
    <table>\n
	<tr>\n
			<td>Elemento #1</td>\n
			<td>Elemento #2</td>\n
			<td>Elemento #3</td>\n
    <tr>\n
    </body>\n
    </html>\n");
    fclose(file);

}
