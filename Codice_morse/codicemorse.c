/* MARTA MENNA
   PROGRAMMAZIONE 1 B
   CODICE MORSE */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEP "****\n"
#define SEP_WORD "    " // 4 spazi
#define SEP_LET "   " // 3 spazi
#define A_a_DIST 32 // distanza fra A e a in ASCII
#define ASCIILEN 256 // dimesinone tab ascii
#define MAX_LET_LEN 16 // massima dimensione di una lettera codificata
#define FILENAME "input.txt"

// trasformo tutte le maiuscole in minuscole
char lowcase(char);
// traduco il testo preso dal file
void traduci(char*, char*[]);

int main() {
// dichiaro il dizionario codice morse, array di stringhe
    char* coded[ASCIILEN];

// alloco e inizializzo il dizionario
    for (int i = 0; i < ASCIILEN; i++) {
// alloco stringa di dimensione 16
        coded[i] = (char*) calloc(MAX_LET_LEN, sizeof(char));
        strcpy(coded[i], "");
    }
    
// stringa da leggere da terminale
    size_t len = 256;
    char *line = malloc (sizeof(char)*len);
    char letter;
    FILE *fp = fopen(FILENAME, "r");

// scivo il dizionario
    while (fgets(line, len, fp)!= NULL && strcmp(line, SEP)!=0 ) {
// leggo max 100 caratteri e mi fermo alla new line
        letter = lowcase(line[0]);
/* copio da line la codifica in morse di letter nel dizionario,
(la codifica inizia alla terza posizione di line)(uso aritmetica dei puntatori)
((NON VA BENE coded[letter] = line + 2, uso strcopy)) */
        strcpy(coded[letter],line+2);
/* sostituisco l'ultimo carattere della codifica (il newline)
nel dizionario con un fine stringa */
        coded[letter][strlen(coded[letter])-1] = '\0';
    }

    //char *risultato = (char*) calloc(MAX_LET_LEN * len, sizeof(char));

//&line perche cosi puo modificare quell'indirizzo di memoria
    while(fgets(line, len, fp)!= NULL) {
// sostituisco l'ultimo carattere della linea (il newline) con un fine stringa
        line[strlen(line) - 1] = '\0';
/* traduci non deve ricevere o restituire stringhe contenenti newline
perche newline è un carattere speciale e darrebbe errore */
        traduci(line, coded);
    }

//faccio le mie belle free
    for (int i = 0; i < ASCIILEN; i++)
    {
        free(coded[i]);
    }
    //free(risultato);
    free(line);
    fclose(fp);
    return 0;
}

char lowcase(char c) {
    if (65 <= c && c <= 90)
        c = c+A_a_DIST;
    return c;
}

void traduci(char *ln, char* cod[]) {
    char curr;
    size_t l = strlen(ln);    
// alloco una stringa per il risultato
    char* ris = (char*) calloc(MAX_LET_LEN * l, sizeof(char*));
    
    for (int i = 0; i < l; i++) {
        curr = lowcase(ln[i]);
// se il carattere è uno spazio, concateno 4 spazi
        if(curr == ' ') {
            strcat(ris, SEP_WORD);
        }
/* altrimenti se trovo un simbolo di cui non ho
la codifica restituisco la str vuota*/
        else if(strcmp(cod[curr], "") == 0) {
                /*strcpy(ris, "Errore nell'input\n");
                return ris;*/
                printf("Errore nell'input\n");
                return;
            } 
// se sono sulla prima lettera non metto lo spazio davanti
            else if (i == 0) {
                    strcat(ris, cod[curr]);
/* altrimenti concateno: il vecchio risultato,
il separatore di lettera e la nuova codif*/
                } else {
                    strcat(ris, SEP_LET);
                    strcat(ris, cod[curr]);
                }
    }
    printf("%s\n",ris);
    free(ris);
    return;
}