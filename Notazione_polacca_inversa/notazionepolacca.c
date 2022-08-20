/* MARTA MENNA
   PROGRAMMAZIONE 1 B
   NOTAZIONE POLACCA INVERSA */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define MAX 32

typedef struct nodo{
   int val;
   struct nodo *next;
} nodo;

void push(nodo **lptr, int val);
int pop(nodo **lptr);

int numero(char *num);
int check(int a, int b, char c, int *ris);
int op(int a, int b, char c);
void stampaInC2(int risultato);

int main(){
   int cifra, *ris, checkoverflow = 0;
   char *espressione = malloc(sizeof(char)*MAX);
   nodo *lptr = NULL;
//prendo una stringa dal buffer e mi fermo alla new line
   scanf("%[^\n]%*c", espressione);

   while(strcmp(espressione, "fine") != 0){
//divido eq in sottostrighe separate da uno spazio
      char *token = strtok(espressione, " ");

      while(token != NULL && checkoverflow == 0){
//Se il token è un numero positivo o negativo
         if(numero(token)){
//chiamo la push con la parte intera di token
            int n = atoi(token);
            push(&lptr, n);
         }else{
//Se il token è un operatore
            int a = pop(&lptr);
            int b = pop(&lptr);
            char op = token[0];

            checkoverflow = check(a, b, op, &ris);

            if(checkoverflow)
               printf("Overflow!\n");
            else
               push(&lptr, ris);
         }
         token = strtok(NULL, " ");
      }
      if(!checkoverflow){
         int risultato = pop(&lptr);

         printf("%d in C2: ", risultato);
         stampaInC2(risultato);
      }
      scanf("%[^\n]%*c", espressione);
      checkoverflow = 0;
   }

   free(espressione);
   return 0;
}
// aggiungo nodo in testa
void push(nodo **head, int val){
   nodo *nuovo = malloc(sizeof(nodo));

   if(nuovo != NULL){
      nuovo->val = val;
      nuovo->next = *head;
      *head = nuovo;
   }
}
//rimuovo nodo in testa
int pop(nodo **head){
   nodo *temp = *head;
//salvo il num del nodo in un intero
   int a = (*head)->val;
//sposto lo start
   *head = (*head)->next;
   free(temp);

   return a;

}
//Controllo se è un numero
int numero(char *num){
   if ( isdigit(num[0])!=0 || isdigit(num[1])!=0 )
      return 1;
   return 0;
}
//Controllo Overflow e eseguo operazioni
int check(int a, int b, char c, int *ris){
   switch(c){
      case '+':
//OF se uno dei 2 operandi è maggiore del massimo rappresentabile
         if((b > 0 && a > INT_MAX - b) || (b < 0 && a < INT_MIN - b)){
            return 1;
         }
         else{
            *ris = a + b;
            return 0;
         }
      break;
      case '-':
         if((a > 0 && b < INT_MIN + a) || (a < 0 && b > INT_MAX + a)){
            return 1;
         }
         else{
            *ris = b - a;
            return 0;
         }
      break;
      case '*':
         if((b > 0 && a > INT_MAX / b) || (b < 0 && a < INT_MIN / b)){
            return 1;
         }
         else{
            *ris = a * b;
            return 0;
         }
      break;
      default:
      break;
   }
}
//Stampa in complemento a 2
void stampaInC2(int risultato){
   const int bit = sizeof(unsigned int) * CHAR_BIT; 
   unsigned int j = 1;

   for(int i = 0; i < bit; i++){
/* con << traslo verso sinistra i bit di 31-i di una posizione,
aggiungendo zeri nei bit meno significativi(a destra) */
      unsigned int shift = 1u << (bit - 1 - i);
      printf("%c", (risultato & shift) ? '1' : '0');
      if(j % 4 == 0)
         printf(" ");
         j++;
      }
   printf("\n");
}