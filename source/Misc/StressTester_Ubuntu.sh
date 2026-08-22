/*
    chmod +x run.sh
    ./run.sh
*/

#!/bin/bash
g++ -O3 -std=c++17 gen.cpp -o gen || exit 1
g++ -O3 -std=c++17 brute.cpp -o brute || exit 1
g++ -O3 -std=c++17 sol.cpp -o sol || exit 1

for ((i = 1; ; ++i)); do
    ./gen > input.txt
    ./brute < input.txt > brute_out.txt
    ./sol < input.txt > sol_out.txt

    if ! diff -w brute_out.txt sol_out.txt > /dev/null; then
        echo "=============================="
        echo "--> WA o test $i!"
        echo "Input:"
        cat input.txt
        echo "Expected Output (Brute):"
        cat brute_out.txt
        echo "Your Output (Sol):"
        cat sol_out.txt
        echo "=============================="
        break
    fi
    echo "Passed test $i"
done