#! /bin/bash

for f in tests/*_tests.c;do

    tmp_f=${f%%.c}
    tmp_f=${tmp_f##tests/}
    
    gcc $f -o /tmp/$tmp_f
    
    echo "Running ${tmp_f%%_tests} tests…"
    /tmp/$tmp_f
done
