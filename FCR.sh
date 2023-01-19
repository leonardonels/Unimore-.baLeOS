#!/bin/sh

#entro nella direcory
#echo entro in $1
cd $1

for F in *
do
	if test -f $F -a -r $F
	then
		#analisi dei file
	fi
done

#cerco la prossima cartella in cui proseguire con FCR.sh
for i in *
do
	if test -d $i -a -x $i
	then
		#$0 `pwd`/$i $2 $3
	fi
done
