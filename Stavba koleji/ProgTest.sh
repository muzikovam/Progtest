#!/bin/bash

#use to test programs

if !(command -v diff > /dev/null); then
	echo "Can't use diff. Aborting."
	exit 5
fi

if [ "$#" -ne 2 ]; then
	echo "Usage: sh ProgTest.sh <path/to/source-file.c> <path/to/test/data/>"
	exit 1
fi

#source file
if [ "${1%%/*}" = "" ]; then
	SFILE=$1
else
	SFILE=$PWD"/"$1
fi

#compiled file
OFILE=${SFILE%/*}"/a.out"

#path to downloaded data without slash at the end
if [ "${2%%/*}" = "" ]; then
	DPATH=${2%/}
else
	DPATH=$PWD"/"${2%/}
fi

if [ ! -f $SFILE ]; then
	echo "[ERROR] Source file not found! Aborting. (Use TAB for auto-complete)"
	exit 2
fi

if [ ! -f $DPATH/0000_in.txt ] || [ ! -f $DPATH/0000_out.txt ]; then
	echo "[ERROR] Downloaded files not found! Aborting. (Use TAB for auto-complete)"
	echo "[INFO] Files should look like 0000_in.txt (_out.txt), else update this script :)"
	exit 2
fi

if [ -f $OFILE ] && (test $OFILE -nt $SFILE); then
	echo "[INFO] Compiled file is newer than source file, skipping compiling."
else	
	echo "Compiling code ..."

	if !(gcc -std=c99 -Wall -Werror -pedantic -o $OFILE $SFILE); then
		echo "[ERROR] Can't compile the source code. Aborting."
		exit 3
	else 
		echo "Success!"
	fi
fi

COUNTER=0
FAILED=0

for i in $DPATH/*_in.txt; do
	COUNTER=$((COUNTER+1))
	echo -n "Testing - ${i#$DPATH/} ... "
	if ($OFILE < $i | diff - ${i%in.txt}out.txt); then
		echo "OK"
	else
		FAILED=$((FAILED+1))
		echo ""
	fi
done

if [ "$FAILED" -gt 0 ]; then
	echo "[Warning] Failed $FAILED test(s) out of $COUNTER."
else
	echo "Congratulations! All $COUNTER tests have been successful."
fi
