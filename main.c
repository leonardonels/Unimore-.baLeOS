#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>					//for isalpha, isDigit
#include <sys/stat.h>

typedef int pipe_t[2];

/*typedef struct {
        int Fpid;						//pid figlio (campo c1 del testo) 
        long int occ;					//numero occorrenze (campo c2 del testo) 
                } s_occ;
*/

int main(int argc, char** argv) {

	/*-----------------------------------variabili locali----------------------------------------------*/
	int pid, pidfiglio, status, ritorno;
	int N;
	int fd;
	pipe_t* p;		
  char ch;
	//pipe_t piped;
	//pipe_t *pipe_pf;
	//pipe_t *pipe_fp;
	//int pidSpeciale;					//pid per il figlio speciale
	//int fcreato;

	/*-------------------------------------------------------------------------------------------------*/

	/*----------------------------controllo del numero dei parametri passati---------------------------*/
	if (argc < 4){
		printf("Errore numero di parametri: infatti argc e' %d\n", argc);
		exit(1);
	}
	N = argc - 1;

	/*----------------------------controllo aventuali altri parametri passati-------------------------*/

	/* allocazione pipe */
	if ((p = (pipe_t*)malloc(N * sizeof(pipe_t))) == NULL){
		printf("Errore allocazione pipe\n");
		exit(4);
	}

	/* creazione pipe */
	for (int i = 0; i < N; i++){
		if (pipe(p[i]) < 0){
			printf("Errore creazione pipe\n");
			exit(5);
		}
	}

	/* creazione figli */
	for (int i = 0; i < N; i++){
		if ((pid = fork()) < 0){
			printf("Errore creazione figli\n");
			exit(6);
		}
		if (pid == 0){
			/* codice figlio */
			printf("Sono il figlio di indice %d e pid %d\n", i, getpid());
			
			/* chiusura pipes inutilizzate */
			for (int j = 0; j < N; j++){
				
			}
			
			/* testo del figlio */
			
			exit(0);
		}
	} 
	/* fine for */

	/* codice del padre */
	/* chiusura pipe: tutte meno l'ultima in lettura */
	for (int i = 0; i < N; i++){
		
	}

	/* testo del padre */
	
	/* Il padre aspetta i figli */
	for (int i = 0; i < N; i++){
		pidfiglio = wait(&status);
		if (pidfiglio < 0){
			printf("Errore in wait\n");
			exit(9);
		}

		if ((status & 0xFF) != 0){ printf("Figlio con pid %d terminato in modo anomalo\n", pidfiglio); }
		else{
			ritorno = (int)((status >> 8) & 0xFF);
			printf("Il figlio con pid=%d ha ritornato %d\n", pidfiglio, ritorno);
		}
	}

	exit(0);
}







/*--------apertura di file, due figli per file (analisi pari e dispari)----------/
	//figlio 0 apre file 1 per lettura pari, figlio 1 apre file 1 per lettura dispari
	//figlio 2 apre file 2 per lettura pari, figlio 3 apre file 2 per lettura dispari
	//e cosi via...

	if ((fd = open(argv[(n / 2) + 1], O_RDONLY)) < 0) { printf("errore nella open del file in posizione %d\n", (n / 2) + 1); exit(-1); }

	//il padre svuota le pipe a due a due

	for (int n = 0; n < N; n++) {
		int nrl = 1; int nr1, nr2, L1, L2;
		printf("le lunghezze delle linee del file %s sono:\n", argv[n]);
		do {
			nr1 = read(p[n * 2][0], &L1, sizeof(L1));
			nr2 = read(p[n * 2 + 1][0], &L2, sizeof(L2));
			if (nr1 != 0) {
				printf("linea numero %d e' lunga %d\n", nrl, L1);
				nrl++;
			}
			if (nr2 != 0) {
				printf("linea numero %d e' lunga %d\n", nrl, L2);
				nrl++;
			}

		} while (nr1 || nr2);

	}
	/---------------------------------------------------------------------------*/
	
	/*---------------------------------------------------------------------------/
	nel caso in cui si vogliano usare i segnali tra padre e figlio
	
	//al di fuori del main
	//funzioni per trattare i segnali SIGUSR1 e SIUSR2: la prima fara' la scrittura su stdout, mentre la seconda non fara' nulla 
	void scrivi(int sig)
	{
		//se il padre ha detto che devo scrivere allora si scrive la linea su standard output usando le write su 1
		write(1, linea, cur.num);
		stampate++;
	}

	void salta(int sig)
	{
		// non si deve fare nulla
	}
	
	//prima dei eseguire la creazione dei figli tramite fork()
	//padre aggancia le due funzioni (scrivi e salta) che useranno i figli alla ricezione dei segnali inviati dal padre 
	signal(SIGUSR1, scrivi);
	signal(SIGUSR2, salta);
	
	//il figlio usa la funzione pause() per attendere il segnale del padre
	pause();
	
	//nel testo del padre dopo la chiusura delle pipe non necessarie, eseguiamo sleep(1) per sicurezza 
	//il padre deve mandare il segnale che corrisponde a scrivi solo al processo di cui gli e' arrivato l'indice, mentre agli altri deve mandare il segnale che corrisponde a salta
		for (i = 0; i < N; i++)
		{
			sleep(1);
			if (i == pip.id)
				kill(pid[i], SIGUSR1);
			else
				kill(pid[i], SIGUSR2);
		}
	/---------------------------------------------------------------------------*/

	/*---------------------------------creare un file in /tmp--------------------/
		// i figli secondi della coppia devono creare il file specificato
	FCreato=(char *)malloc(strlen(argv[i-N+1]) + 11);	// bisogna allocare una stringa lunga come il nome del file associato + il carattere '.' + i caratteri della parola mescolato (9) + il terminatore di stringa: ATTENZIONE ALL'INDICE PER INDIVIDUARE IL FILE
	if (FCreato == NULL)
	{
		printf("Errore nelle malloc\n");
		exit(0);
	}
		// copiamo il nome del file associato
	strcpy(FCreato, argv[i-N+1]);
		// concateniamo la stringa specificata dal testo
	strcat(FCreato,".mescolato");
	fcreato=creat(FCreato, 0644);
	if (fcreato < 0){
		printf("Impossibile creare il file %s\n", FCreato);
		exit(0);
	}
	---------------------------------------------------------------------------*/

	/*--------comando per resettare il file descriptor in cima al file----------/
	lseek(fd, 0L, 0); //per resettare il puntatore ad inizio file
	---------------------------------------------------------------------------*/

	/*-------- coppia di figli per file primo-ultimo, secondo-penultimo --------/
	* dati N file creare 2*N figli i quali sono divisi primo e ultimo figlio,
	* secondo e penultimo, terzo e terzultimo e cosi via.... 
	* i figli scrivono sulla pipe 2*N-1-i e leggeno sulla propria.
	* i file da aprire vengono segnati come argv[i+1] e argv[2*N-i].
	/--------------------------------------------------------------------------*/



	/*---sistema di comunicazione a RING comprendente il padre----/
	dati Q figli servono Q+1 pipes con con la pipe Q+1 dedicata al padre.
	ogni figlio Q deve scrivere sulla pipe di quello successivo fino a Q+1
	che essendo il padre scroverà sulla pipe del figlio con Q=0.
	ogni filgio Q e padre Q+1 deve leggere dalla proprio pipe, il padre alla
	fine di ogni round lavora con tutte le informazione raccolte dai Q figli
	e carica sulla pipe del figlio Q=0 la struttura di raccolta dati vuota
	azionando così un nuovo round.
	per la chiusura:

		for(int j=0; j<Q+1; j++){
			if(j!=q){
				close(pipes[j][0]);
			}
			if(j!=(q+1)){
				close(pipes[j][1]);
			}
		} 
	/-----------------------------------------------------------*/

	/*------sistema di comunicazione a RING senza il padre-------/
	dati Q figli ogni figlio leggerà dalla propria pipe attendendo
	che il figlio precedente carichi qualcosa da leggere sulla pipe
	(dal punto di vista del filgio che scrive, esso srive sulla pipe
	Q+1). ogni figlio dovrà poi scrivere sulla pipe del filgio Q+1
	successivo, l'ultimo filgio scrive sulla pipe del primo Q=0.
	consigliabile usare (n+1)%N per indirizzare al figlio 0. 
	a iniziare il giro di figlio è il padre che scrive sulla pipe
	del figlio n=0.
	in questo caso nessuno si occupa attivamente di regolare il numero
	di cicli, ma un while read sopra a tutto si occupa di prevenire un
	loop infinito.
	/-----------------------------------------------------------*/

	/*-----------sistema di comunicazione TOKEN RING-------------/
  token con Q=1 pipe.
	/-----------------------------------------------------------*/

	/*-------sistema di comunicazione lineare concorrente--------/
	dati Q figli ogni figlio scrive sulla propria pipe il messaggio
	da trasmettere, tutti i figli diversi dal primo Q=0 prima di
	cominciare leggono dalla pipe del figlio precedente. infie il
	padre legge dalla pipe dell'ultimo figlio. queste pipe sono
	concorrenti, continuano parallelamente, il primo figlio non deve
	attendere nessuno e dopo aver mandato avanti un messaggio
	inizia subito a preparare il successivo.	

	nel caso in cui serva mandare avanti un array di strutture
	è possibile per i figli allocare un array grande i+1 (malloc)
	scrivere all'indirizzo i e recuperare dal figlio precedente
	il resto dell' array.

	if ((curr = (s_occ*)malloc((i + 1) * sizeof(s_occ))) == NULL){
			printf("Errore allocazione curr\n");
			exit(-1);
		}

		curr[i].c1 = getpid();
		curr[i].c2 = 0;


		if (i != 0) {
						int nr = read(p[i - 1][0], curr, i * sizeof(s_occ));
						if (nr != i * sizeof(s_occ))
						{
							printf("Figlio %d ha letto un numero di strutture sbagliate %d\n", i, nr);
							exit(-1);
						}
					}
					write(p[i][1], curr, (i + 1) * sizeof(s_occ));
	/-----------------------------------------------------------*/

	/*--------sistema di sequanziale lineare con token---------/
	* dati Q figli, ognuno dei quali comunica col padre e attende
	* un suo messaggio prima di procedere. si creino due pipe, una
	* per i messaggi dal padre ai figli e una per i messaggi dai
	* figli al padre. se il padre deve assicurarsi che i figli non
	* siano gia terminati sarà necessario usare un array per controllare
	* lo stato dei figli. 
	/-----------------------------------------------------------*/
