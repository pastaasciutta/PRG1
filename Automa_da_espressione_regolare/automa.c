/* MARTA MENNA
   PROGRAMMAZIONE 1 B
   AUTOMA DA ESPRESSIONE REGOLARE */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 2
#define LEN 32

typedef enum stato{lettr, numbr, fail}stato;
int ncount=0;

stato checklet(char);
stato checknum(char);

int main(){

// dichiaro l'array di puntatori alle funzioni
    /*che mi permette di avere un "array di funzioni" (a fpnt[0] corrisponde checklet)
    che matchato con lo stato(enum) mi permette di entratre nelle funzioni
    in base allo stato di una qualsiasi variabile di tipo stato
    (ex: dichiaro stato s; s = (*fpnt[s])(str[a]); mi permette di "aggiornare" s*/
    stato (*fpnt[N])(char) = {checklet, checknum};

//alloco spazio e prendo stringa in input
    char* str= malloc (sizeof(char)*LEN);
    scanf("%s", str);

// dichiaro e "inizializzo" s(stato corrente)
    stato s=(*fpnt[0])(str[0]);

    for(int i=0; s!=fail && i<strlen(str); i++){
        s=(*fpnt[s])(str[i]);
    }

    if (s!=fail && (ncount==0 || ncount>2)){
        printf("stringa appartenente al linguaggio\n");
    }
    else{
        printf("stringa non appartenente al linguaggio\n");
    }
    free(str);
    return 0;
}

stato checklet(char c){
/* inizialmente posso avere caps o 0:
non appena trovo lo 0 passo allo stato succesivo */
    if (c>64 && c<91)
        return lettr;
    if (c=='0')
        return numbr;
    return fail;
}

stato checknum(char c){
/* posso avere 3 o piu cifre o nessuna*/
    if(isdigit(c) > 0){
/* ncount conta quante volte entro nella funzione
(almeno tre affinche la stringa appartenga al linguaggio) */
        ncount++;
        return numbr;
    }
    return fail;
}