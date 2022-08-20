/* MARTA MENNA
   PROGRAMMAZIONE 1 B
   GESTIONE BIBLIOTECA */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SCELTE  5
#define MAX 100

typedef struct l{
        char* titolo;
        char* autore;
        int ISBN;
        int c_disponibili;
        int c_totali;
        int c_prestate;
        struct l *next;
}libro;
typedef libro* ptr_libro;

void inserimento_biblioteca(ptr_libro*,int,char*,char*);
//per il menu
void menu(int*);
void stampa(ptr_libro*);
void cerca(ptr_libro*);
void prestito(ptr_libro*);
void restituzione(ptr_libro*);
void esci(ptr_libro*);

void trova_libro(ptr_libro,char*,char*);
void operazione_prestito(ptr_libro*,int);
void operazione_restituzione(ptr_libro*,int);

int main(){
	int codice;
	char* titolo = malloc(sizeof(char)*MAX);
	char* autore = malloc(sizeof(char)*MAX);
	ptr_libro biblioteca = NULL;
	
	do{
		scanf("%d,%[^,],%[^\n]",&codice,titolo,autore);
		if(codice > 0)	
			inserimento_biblioteca(&biblioteca,codice,titolo,autore);
	}while(codice > 0);
	
	free(titolo);
	free(autore);
	int scelta;
	
	do{
		menu(&scelta);
/*dichiaro funzione che prende in input variabili di tipo intero (S)
in riferimento a ptr_libro(testa di struct libro)*/
			void(*operazioni[SCELTE])(ptr_libro*) = {stampa,cerca,prestito,restituzione,esci};
		(*operazioni[scelta-1])(&biblioteca);
	
	}while(scelta !=5);
        
	return 0;
}
//inserimento di un nuovo libero(ordinato)
void inserimento_biblioteca(ptr_libro* testa, int codice, char* titolo, char* autore){
	ptr_libro nuovo = malloc(sizeof(libro));
//creo una nuova struct di tipo libro
	if(nuovo != NULL){
		nuovo->titolo = malloc(sizeof(char)*MAX);
		nuovo->autore = malloc(sizeof(char)*MAX);
		strcpy(nuovo->titolo,titolo);
		strcpy(nuovo->autore,autore);
		nuovo->c_totali = 1;
		nuovo->c_disponibili = 1;
		nuovo->c_prestate = 0;
		nuovo->ISBN = codice;
	}
//inserisco la mia nuova struct nella lista

/*caso lista vuota oppure
caso fine della lista (devo inserire il libro)*/
	if(*testa == NULL){
		nuovo->next = NULL;
		*testa = nuovo;
		return;
	}
/*caso in cui il libro da inserire è gia presente nella biblioteca,
aggiorno le copie totali e le copie disponibili*/
	if(codice == (*testa)->ISBN){
		(*testa)->c_totali++;
		(*testa)->c_disponibili++;
		return;
	}
// ordinamento per autore

/* inserimento in testa, ex: autore di n=a e autore di testa=b
(devo mettere n davanti alla testa)*/
	if(strcmp((*testa)->autore,autore) > 0){
		nuovo->next = *testa;
		*testa = nuovo;
		return;
	}
	
	if(strcmp((*testa)->autore,autore) <0 ){
		return inserimento_biblioteca(&((*testa)->next),codice,titolo,autore);     
	}

	if(strcmp((*testa)->autore,autore)==0){
// caso stesso autore: confronto i titoli
		if(strcmp((*testa)->titolo,titolo) > 0){
//inserimento in testa
			nuovo->next = *testa;
			*testa = nuovo;
			return;
		}
		else
			return inserimento_biblioteca(&((*testa)->next),codice,titolo,autore);
	}
}

// menu di scelta
void menu(int* scelta){

	printf("Scegli un opzione:\n");
	printf("1) Stampa catalogo.\n");
	printf("2) Cerca.\n");
	printf("3) Prestito.\n");
	printf("4) Restituzione.\n");
	printf("5) Esci.\n");
	printf("Scelta:  ");
	
	while(scanf("%d",scelta) !=1 || *scelta <= 0 || *scelta >6){
		printf("Errore. Scelta non valida.\n");
		scanf("%*[^\n]%*c");
	}
//ritorna una scelta compresa fra 1 e 5
	return;
}
// stampa libri
void stampa(ptr_libro* testa){
	ptr_libro temp = *testa;
	
	if(*testa == NULL)
		return;
	printf("%d - %s - %s (%d/%d)\n",temp->ISBN,temp->autore,temp->titolo,temp->c_disponibili,temp->c_totali);
	
	return stampa(&((*testa)->next));	
}

// interfaccia cerca libro
void cerca(ptr_libro* testa){
	char* titolo = malloc(sizeof(char)*MAX);
	char* autore = malloc(sizeof(char)*MAX);
	printf("Inserire nome autore: ");
	scanf("%*c%[^\n]",autore);
	printf("Inserire titolo: ");
	scanf("%*c%[^\n]",titolo);
	
	trova_libro(*testa,titolo,autore);
}

// cerca e stampa libro
void trova_libro(ptr_libro testa, char* titolo,char* autore){
// caso libro non trovato o biblioteca vuota
	if(testa == NULL){
		printf("Libro non trovato.\n");
		return;
	}
	
// caso libro trovato: stampo il numero di copie disponibili 
	if(strcmp(testa->titolo,titolo) == 0 && strcmp(testa->autore,autore) == 0){
		if(testa->c_disponibili > 0){
			printf("%d copie disponibili.\n", testa->c_disponibili);
			return;
		}else{
			printf("Non ci sono copie disponibili del libro richiesto.\n");
			return;
		}	
	}
/*richiamo la funzione fino a quando non trovo il libro
oppure non raggiungo la fine della lista*/
	return trova_libro(testa->next,titolo,autore);

}

// interfaccia prestito
void prestito(ptr_libro *testa){
	int codice;
	printf("ISBN: ");
	scanf("%d",&codice);
	
	operazione_prestito(testa,codice);
}

void operazione_prestito(ptr_libro* testa, int codice){
	if(*testa == NULL){
		printf("Libro non trovato.\n");
		return;
	}
/* caso in cui il libro è presente nella biblioteca e ci sono copie disponibli:
aggiorno il numero di copie disponibili e prestate*/
	if((*testa)->ISBN == codice){
		if((*testa)->c_disponibili > 0){
			(*testa)->c_disponibili--;
			(*testa)->c_prestate++;
			printf("Operazione completata.\n");
			return;
		}else{
			printf("Non ci sono copie disponibili del libro richiesto.\n");
			return;
			
		}
	}
/*richiamo la funzione finchè non trovo il libro
o raggiungo la fine lista*/
	return operazione_prestito(&((*testa)->next),codice);
}

//interfaccia restituzione
void restituzione(ptr_libro* testa){
	int codice;
	printf("ISBN: ");
	scanf("%d",&codice);
	
	operazione_restituzione(testa,codice);
}

void operazione_restituzione(ptr_libro* testa, int codice){
	if(*testa == NULL){
		printf("Libro non trovato.\n");
		return;
	}
	
/* caso in cui il libro è presente nella biblioteca e ci sono copie disponibli:
aggiorno il numero di copie disponibili e prestate*/
	if((*testa)->ISBN == codice){
		if((*testa)->c_prestate > 0){
			(*testa)->c_disponibili++;
			(*testa)->c_prestate--;
			printf("Operazione completata.\n");
			return;
		}else{
			printf("Non risultano copie in prestito.\n");
			return;	
		}
	}
/*richiamo la funzione finchè non trovo il libro
o raggiungo la fine lista*/
	return operazione_restituzione(&((*testa)->next),codice);
}

// interfaccia uscita
void esci(ptr_libro* testa){
	printf("Bye\n");
	return;
}