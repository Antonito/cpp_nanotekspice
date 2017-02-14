#!/bin/sh

RED='\033[1;31m'
GREEN='\033[1;32m'
CYAN='\033[1;36m'
NC='\033[0m' # No Color

TEST_LIST=(and or nand nor not xor)
OPT_DIFF=0

for param in $*; do
	case $param in
		"--diff")
			OPT_DIFF=1;;
		*)
			echo "Unknown option or parameter '$param'"
			exit 1;;
	esac
done

for TEST in ${TEST_LIST[@]}; do
	echo -ne "Test ${CYAN}$TEST${NC}: "

	CMD_FILE="tests/cmd/$TEST.sh"
	EXPECTED="tests/expected/$TEST.txt"
	OUTPUT="tests/output_tmp/$TEST.txt"

#	./$CMD_FILE > $OUTPUT || { echo -e "${RED}KO (execution failed)${NC}"; rm $OUTPUT; continue; }
	./tests/routine.sh $EXPECTED $CMD_FILE > $OUTPUT || { echo -e "${RED}KO (execution failed)${NC}"; rm $OUTPUT; continue; }
	DIFF=$(diff $EXPECTED $OUTPUT)
	if [ -z "$DIFF" ]
	then
		echo -e "${GREEN}OK${NC}"
	else
		echo -e "${RED}KO${NC}"
		if [ $OPT_DIFF = 1 ]
		then
			echo -e "\n===== Your  output ====="
			cat $OUTPUT
			echo -e "\n=====   Expected   ====="
			cat $EXPECTED
			echo -e "\n=====     Diff     ====="
			echo "$DIFF"
		fi
	fi
	rm $OUTPUT
done