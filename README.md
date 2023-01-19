# UNIMORE-.baLeOS

 UNIX COMMANDS
 
 ps........mostra i processi attivi legati al terminale in uso
           -e -ef -eF -ely -ax -axu bene o male si occupano tutti di mostrare la lista completa dei processi attivi
           (i primmi con la 'e' con sintassi standard, i secondi con 'a' con sintassi BSD)
 
 echo
 
 ls.......list
 	        -l oltre al nome tutte le informazioni associate al file
 	        -a lista anche i nomi dei file nascosi
 	       	-A uguale a -a, vengono però esclusi i collegamenti . e .. alla directory corrente e precedente
 	     	-F evidenzia i file eseguibili con suffisso * e le directory co /
 	     	-d list directories themselves, not their contents
 	     	-R lista ricorsivamente i file nella gerarchia
 	     	-i lista gli inumer dei file al loro nome
 	     	-r lista con ordine rovesciato (reverse)
 	     	-t lista i file in ordine di ultima modifica (time)

 pwd......printf della direcotry corrente (print su standard output)
 
 cp.......file copy (sorgente -> destinazione)

 tr.......translate: nel case specifico dell'esame in cui compare serve a trasformare i caratteri da maiuscoli a minuscoli e viceversa 
          var=`echo $2| tr [:upper:] [:lower:]`

 basename.utilizzato per ottenere in nome del direttorio senza la radice

 ln.......link hw (file1 file2)
          -s link software

 mv.......move

 rm.......remove
          -i chiede conferma del file da eliminare
          -d se si vuole eliminate la direcotry indicata

 cat

 more....se cat di molteplici file li concatena in modo molto ignorante, la concatenazione tramite more aggiunge 3 line per file concatenato.
         per ogni file concatenato stamperà il titolo con sopra e sotto una linea di due punti ("::::::::::").
	 
 sort......ordina le linee di standard output
           -f ignora il case (maiuscolo o minuscoilo)
           -r reverse
           -n ordina le linee del file in base alla somma dei caratteri delle singole linee
           -R random

 grep......cerca la stringa indicata nel file selezionato/standard input

 rev.......reverse dei caratterei per linea

 wc........word count conta:
	          -l le linee
           -w le parole
           -c i caratteri

 haed......seleziona il primo n numero di linee

 tail......selziona l'ultimo n numero di linee

 //wildcards
 ls [q-s]*	cereca solo i file che iniziano con i caratteri compresi tra q e s, il resto dei caratteri è valido qualsiasi ed è indicato da *
 ls *[!0-9]  cerca solo i file che NON finioscono con numero compresi tra 0 e 9
 ls [a-p,1-7]*[c,f,d]
 		cerca solo i file che iniziano con lettere comrprese tra a e p, numeri tra 1 e 7
 		e finiscono con le lettere c, f o d
 ls *[!\*\?]* lista tutti i file che NON contengono * o ?
