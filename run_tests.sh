#! /bin/bash

# use `valgrind` to detect memory leaks
use_valgrind=$(which valgrind)

for f in tests/*_tests.c;do

    tmp_f=${f%%.c}
    tmp_f=${tmp_f##tests/}

    assert_nb=$(grep -c "assert(" ${f})
    
    tmp_err=$(tempfile)
    rm -f $tmp_err

    # Compilation

    echo "Compiling ${tmp_f%%_tests} tests…"
    gcc $f -o /tmp/$tmp_f 2> $tmp_err

    if [ -s $tmp_err ]; then
        echo -n 'ERROR: '
        cat $tmp_err
        rm -f $tmp_err
        exit -1
    fi
    
    # Running

    echo "Running ${tmp_f%%_tests} tests…"
    /tmp/$tmp_f 2> $tmp_err
    
    if [ -s $tmp_err ]; then
        echo -n 'ERROR: '
        cat $tmp_err
        rm -f $tmp_err
        exit -1
    fi

    # Checking for memory leaks
    if [ $use_valgrind ]; then
        valgrind --tool=memcheck --leak-check=full -q /tmp/$tmp_f
    fi

    echo "${assert_nb} assertions successfully passed."

done # 2> /dev/null
