ARG_EXPECTED=$1
ARG_SOURCE=$2
TMP=""

source $ARG_SOURCE

COMMAND=""
currentOutput
EXPECTED=$TMP

N=$(($RANDOM % 10 + 10))

for (( i_=0; i_<N; i_++)); do
	EXPECTED="$EXPECTED
"
	changeInput
	COMMAND="${COMMAND}${TMP}
"
	EXPECTED="$EXPECTED> > > "
	COMMAND="${COMMAND}simulate
display
"

	currentOutput
	EXPECTED="${EXPECTED}${TMP}"
done

COMMAND="${COMMAND}exit"
EXPECTED="$EXPECTED
> "

#echo "$COMMAND"

echo -n "$EXPECTED" > $ARG_EXPECTED

echo "$COMMAND" | ./nts $(filename) $(startInput)