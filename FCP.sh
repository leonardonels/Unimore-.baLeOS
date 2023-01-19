#!/bin/sh

#controllo in numero di parametri
case $# in
0|1) echo non abbastanza parametri; exit 1;;
2);;
*) echo troppi parametri; exit 2;;
esac

#controllo che il parametro sia una directory passata tramite nome assoluto
case $1 in
/*) if test ! -d $1 -a ! -x $1; then echo errore non direttorio o non leggibile; exit 3; fi;;
*) echo non nome assoluto; exit 4;;
esac

#controllo che il parametro passato sia un numero STRETTAMENTE maggiore di zero
case $2 in
*[!0-9]*) echo non numerico; exit 5;;
0) echo non strettamente maggiore di 0; exit 6;;
*);;
esac

#creo un file temporaneo
>/tmp/tmp$$

#PATH
PATH=`pwd`:$PATH
export PATH

#invoco il file ricorsivo per le diverse fasi
#for i
#do
#	./FCR.sh $i $X /tmp/tmp$$
#done

#invoco una sola fase per il file ricorsivo
./FCR.sh $1 $2 /tmp/tmp$$

#invoco la parte C per gli N elemente dentro al file temporaneo
for i in `cat /tmp/tmp$$`
do
	echo invoco la parte C per $i
done

#rimuovo il file temporaneo
rm /tmp/tmp$$
