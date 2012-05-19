#! /bin/bash

# use `valgrind` to detect memory leaks
use_valgrind=0

# temporary file
TEMP=.tests.tmp

if [ $# -ge 1 ] && [ "$1" == "--leaks" ] && [ $(which valgrind) != "" ]; then
     use_valgrind=1
fi

echo -n "Compiling binary... "
make othello > /dev/null && echo "ok" || echo "fail! "

total_assert_nb=0

for f in tests/*_tests.c;do

    tmp_f=${f%%.c}
    tmp_f=${tmp_f##tests/}

    assert_nb=$(grep -c "assert(" ${f})
    tmp_nb=$(grep -c "T_PLAY(" ${f})
    assert_nb=$((assert_nb+(tmp_nb-2)*5))
    
    tmp_err=$(tempfile)
    rm -f $tmp_err

    # Compilation

    echo "Compiling ${tmp_f%%_tests} tests…"
    gcc -Wall $f -o /tmp/$tmp_f 2> $tmp_err

    if [ $? -ne 0 ] || [ -s $tmp_err ]; then
        echo 'ERROR'
        cat $tmp_err
        rm -f $tmp_err
        exit -1
    fi
    
    # Running

    echo "Running ${tmp_f%%_tests} tests…"
    /tmp/$tmp_f 2>&1 # $tmp_err
    
    #if [ $? -ne 0 ] || [ -s $tmp_err ]; then
    #    echo 'ERROR'
    #    cat $tmp_err
    #    rm -f $tmp_err
    #    exit -1
    #fi

    # Checking for memory leaks
    if [ $use_valgrind -eq 1 ]; then
        echo "Checking for memory leaks…"
        # Use the first line for quiet mode, and the second for verbose mode
        #valgrind --tool=memcheck --leak-check=full -q /tmp/$tmp_f 2>&1
        valgrind --tool=memcheck --leak-check=full --track-origins=yes -v /tmp/$tmp_f 2>&1
    fi

    echo "${assert_nb} assertions successfully passed."
    total_assert_nb=$((total_assert_nb+assert_nb))

done # 2> /dev/null

echo "TOTAL: ${total_assert_nb} assertions successfully passed."

echo "Running simulated games: "

for f in tests/game_test_*.txt; do

    echo -n "- "

    winner=${f%%Wins*}
    winner=${winner##*game_test_}
    winner_fr='BLANC'
    [ $winner == 'Black' ] && winner_fr='NOIR'
    
    ./othello --play < $f > $TEMP

    result=$(tail -1 ${TEMP}) 

    [ "$result" != "$winner_fr gagne." ] && echo "fail! Bad winner." || echo "ok"

    # TODO check if every other line is 'OK'
done
