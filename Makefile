out: clean compile execute

compile: main.cpp
	g++ -g -Wall -std=c++11 *.cpp -o mainexe

execute: mainexe
	./mainexe

clean:
	rm -f mainexe