@echo off
title My futile attempt at writing a stress tester.

echo Compiling files, please wait...
g++ -std=c++14 -o test.exe test.cpp
echo Done compiling test generator!

g++ -std=c++14 -o brute.exe brute.cpp
echo Done compiling bruteforce submission!

g++ -std=c++14 -o sol.exe sol.cpp
echo Done compiling (possibly) faulty submission!

for /l %%x in (1, 1, 1000000) do (
	echo Testcase numero: %%x
	test > input.inp
	sol < input.inp > output.out
	brute < input.inp > output.ans
	fc output.out output.ans > log.txt || call :WA

)
echo Accepted!
pause
exit

:WA
echo Wrong Answer
echo Test case:
type input.inp
echo Participant answer:
type output.out
echo Jury answer:
type output.ans

pause
exit