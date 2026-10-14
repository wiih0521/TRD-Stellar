#!/bin/bash
# chmod +x run.sh && ./run.sh
g++ -O3 -std=c++17 gen.cpp -o gen || exit 1
g++ -O3 -std=c++17 brute.cpp -o brute || exit 1
g++ -O3 -std=c++17 sol.cpp -o sol || exit 1

for ((i = 1; ; ++i)); do
    ./gen > in.txt
    ./brute < in.txt > ans.txt
    ./sol < in.txt > out.txt

    if ! diff -w ans.txt out.txt > /dev/null; then
        echo "=============================="
        echo "--> WA at test $i!"
        echo "Input:"
        cat in.txt
        echo "Expected Output (Brute):"
        cat ans.txt
        echo "Your Output (Sol):"
        cat out.txt
        echo "=============================="
        break
    fi
    echo "Passed test $i"
done