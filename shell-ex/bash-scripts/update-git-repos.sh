#!/bin/bash

REPOS=/home/gitoff
SLEEP=10

function refreshgitrepo() {
	a=(*);

	for ((i=${#a[*]}; i>1; i--));
		do j=$[RANDOM%i];
		b=${a[$j]};
		a[$j]=${a[$[i-1]]};
		a[$[i-1]]=$b;
	done;

	for i in "${a[@]}";
		do cd $i;
		echo -e "\n\nREPOSITORY: $i\n";
		git stash;
		git fetch;
		git pull;
		sleep $SLEEP;
		cd ..;
	done;
}

cd $REPOS/

for i in *;
	do cd $REPOS/$i;
	echo -e "\n\nUpdating repositories in: $i \n=========================\n";
	refreshgitrepo;
done
