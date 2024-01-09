#!/bin/bash

RED='\033[0;31m'
ORANGE='\033[0;33m'
GREEN='\033[0;32m'
WHITE='\033[0m'

tests_count=0
passed_tests=0

bash_compare()
{
	echo "$1" > cmd
	if [[ $2 == "1" ]]; then
		minishell_output=$(env -i ../minishell < ./cmd 2>&1 | head -n -1 |  tail -n +2)
		bash_output=$(env -i /bin/bash < ./cmd 2>&1)
	else
		minishell_output=$(../minishell < ./cmd 2>&1 | head -n -1 |  tail -n +2)
		rm -rf ./ftest*
		bash_output=$(/bin/bash < ./cmd 2>&1)
	fi

	if [[ "$minishell_output" == "$bash_output" ]]; then
		echo -e "TEST $tests_count : ${GREEN}OK${WHITE}"
		return 1
	else
		echo -e "TEST $tests_count : ${RED}FAIL${WHITE}"
		(printf "========= TEST $tests_count =========\n$1\nminishell_output: $minishell_output\n\nbash_output: $bash_output \n=======================\n\n") >> errors
		return 0
	fi
}

str_compare()
{
	echo "$1" > cmd
	minishell_output=$(../minishell < ./cmd 2>&1 | head -n -1 |  tail -n +2)
	if [[ "$minishell_output" == "$2" ]]; then
		echo -e "TEST $tests_count : ${GREEN}OK${WHITE}"
		return 1
	else
		echo -e "TEST $tests_count : ${RED}FAIL${WHITE}"
		(printf "========= TEST $tests_count =========\n$1\nminishell_output: $minishell_output\n\nexpected_output: $2 \n=======================\n\n") >> errors
		return 0
	fi
}

str_contains()
{
	echo "$1" > cmd
	minishell_output=$(../minishell < ./cmd 2>&1 | head -n -1 |  tail -n +2)
	if [[ "$minishell_output" == "$2"* ]]; then
		echo -e "TEST $tests_count : ${GREEN}OK${WHITE}"
		return 1
	else
		echo -e "TEST $tests_count : ${RED}FAIL${WHITE}"
		(printf "========= TEST $tests_count =========\n$1\nminishell_output: $minishell_output\n\nexpected_output: $2 \n=======================\n\n") >> errors
		return 0
	fi
}

exit_test()
{
	echo "$1" > cmd
	minishell_output=$(../minishell < ./cmd 2>&1)
	minishell_exit_code=$?
	bash_output=$(/bin/bash < ./cmd 2>&1)
	bash_exit_code=$?
	if [[ "$minishell_exit_code" == "$bash_exit_code" ]]; then
		echo -e "TEST $tests_count : ${GREEN}OK${WHITE}"
		return 1
	else
		echo -e "TEST $tests_count : ${RED}FAIL${WHITE}"
		(printf "========= TEST $tests_count =========\n$1\nminishell_exit: $minishell_exit_code\n\nexpected_output: $bash_exit_code \n=======================\n\n") >> errors
		return 0
	fi
}

run_cmd()
{
	((tests_count++))
	if [[ $1 == "PARSING" || $1 == "PIPES + REDIRECTIONS" || $1 == "EXECUTION" ]]; then
		bash_compare "$2"
	elif [[ $1 == "SYNTAX ERRORS" ]]; then
		str_compare "$2" "-minishell: syntax error"
	elif [[ $1 == "INVALID QUOTES" ]]; then
		str_compare "$2" "invalid quotes"
	elif [[ $1 == "AMBIGUOUS REDIRECT" ]]; then
		str_contains "$2" "-minishell: ambiguous redirect"
	elif [[ $1 == "env -i + BUILTINS" ]]; then
		bash_compare "$2" "1"
	elif [[ $1 == "EXIT" ]]; then
		exit_test "$2"
	fi
}

type=""
tests_file="./all_tests"

rm -rf ./errors
while read -r line
do
	if [[ $line == "#"* ]]; then
		printf "\n"
		line=$(echo "$line" | cut -d "#" -f 2)
		echo -e "${ORANGE}$line${WHITE}"
		type="$line"
	elif [[ $line != "" ]]; then
		run_cmd "$type" "$line"
		if [[ $? == "1" ]]; then
			((passed_tests++))
		fi
	fi
done < "$tests_file"
rm -rf ./ftest*
rm -rf ./cmd

echo ""
echo -e "${ORANGE}PASSED TESTS:${WHITE} $passed_tests/$tests_count"

printf "\nmanual tests to do:
cat | cat | ls (2x enter + unblocked = ok otherwise fail)
export (+= too)
unset
cat /dev/random | head -c 100 | wc -c
ls | \$test | cat
< \$tt | echo lol
\n"
