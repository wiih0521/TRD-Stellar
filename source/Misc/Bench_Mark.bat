@echo off
title Bench Marker 6000
echo Compiling files, please wait...
g++ -O2 -Wl,--stack=268435456 -std=c++11   -o test.exe test.cpp
echo Done compiling test generator!
g++ -O2 -Wl,--stack=268435456 -std=c++11   -o sol.exe sol.cpp
echo Done compiling (probably) faulty submission!

for /l %%x in (1, 1, 1000) do (
	echo Test case numero: %%x
	test > input.inp
	sol < input.inp > output.out
)

pause 
exit
