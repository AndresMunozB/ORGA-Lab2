
#include <stdlib.h>
#include <stdio.h>

int main(){


    /*char szNumbers[] = "2001 60c0c0 1101110100110100100000 0xffffff";
    char * pEnd;
    long li1, li2, li3, li4;
    li1 = strtol (szNumbers,&pEnd,10);
    li2 = strtol (pEnd,&pEnd,16);
    li3 = strtol (pEnd,&pEnd,2);
    li4 = strtol (pEnd,NULL,0);
    printf ("The decimal equivalents are: %ld, %ld, %ld and %ld.\n", li1, li2, li3, li4);*/

    FILE *file = fopen("inputRegistros.txt","r");
    char buffer[30];
    char valor[30];
    long long numero;
    while (!feof(file)){

        fscanf(file,"%s %s\n",buffer,valor);
        printf("%s %ld\n",buffer, strtol(valor,NULL,0));

    }
    fclose(file);




    return 0;
}
