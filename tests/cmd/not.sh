for (( i=0; i<6; i++)); do
	I[$i]=0
done

function filename {
	echo "01_basics/not.nts"
}

function startInput {
	echo "i0=0 i1=0 i2=0 i3=0 i4=0 i5=0"	
}

function changeInput {
	n=$((RAMDOM % 6))
	I[$n]=$(($RANDOM % 2))
	TMP="i$n=${I[$n]}"
}

A=0

function currentOutput {
	TMP=""
	for (( i=0; i<6; i++)); do
		if [ $i -gt 0 ]; then
			TMP="$TMP
"
		fi

 		TMP="${TMP}o$i="
		if [ ${I[$i]} -eq 1 ]; then
			TMP="${TMP}0"
		else
			TMP="${TMP}1"
		fi
	done
}