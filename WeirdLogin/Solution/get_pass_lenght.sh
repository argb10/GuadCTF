#!/bin/bash


for i in {1..512}; 
do
	jamon+='a'
	#echo $jamon
	echo $i
	curl 'https://ctf2.kolhos.chichasov.es/login' -d $jamon
done