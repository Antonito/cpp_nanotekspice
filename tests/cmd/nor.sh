A=0
B=0

function filename {
	echo "01_basics/nor.nts"
}

function startInput {
	echo "a=0 b=0"	
}

function changeInput {
	if [ $(($RANDOM % 2)) -eq 0 ]; then
		A=$(($RANDOM % 2))
		TMP="a=$A"
	else
		B=$(($RANDOM % 2))
		TMP="b=$B"
	fi
}

function currentOutput {
	if [[ $A -eq 1 || $B -eq 1 ]]; then
		TMP="s=0"
	else
		TMP="s=1"
	fi
}