all: testa_conta_palavras.cpp   conta_palavras.cpp conta_palavras.hpp conta_palavras.o
	g++ -std=c++17 -Wall conta_palavras.o testa_conta_palavras.cpp -o testa_conta_palavras
	./testa_conta_palavras

compile: testa_conta_palavras.cpp   conta_palavras.cpp conta_palavras.hpp conta_palavras.o
	g++ -std=c++17 -Wall conta_palavras.o testa_conta_palavras.cpp -o testa_conta_palavras

conta_palavras.o : conta_palavras.cpp conta_palavras.hpp
	g++ -std=c++17 -Wall -c conta_palavras.cpp
	
testa_conta_palavras: 	testa_conta_palavras.cpp   conta_palavras.cpp conta_palavras.hpp conta_palavras.o
	g++ -std=c++17 -Wall conta_palavras.o testa_conta_palavras.cpp -o testa_conta_palavras
	
test: testa_conta_palavras	
	./testa_conta_palavras

setup: 
	sudo apt-get install g++
	sudo apt-get install make
	sudo apt-get install valgrind
	sudo apt-get install cppcheck
	sudo apt-get install clang-format-14
	sudo apt-get install doxygen

	sudo apt-get install python3-pip
	sudo pip install cpplint
	
cpplint: testa_conta_palavras.cpp   conta_palavras.cpp conta_palavras.hpp
	clang-format -i conta_palavras.cpp 
	clang-format -i conta_palavras.hpp
	clang-format -i testa_conta_palavras.cpp
	cpplint   --exclude=catch.hpp input.txt  *.*

gcov: testa_conta_palavras.cpp   conta_palavras.cpp conta_palavras.hpp 
	g++ -std=c++17 -Wall -fprofile-arcs -ftest-coverage -c conta_palavras.cpp
	g++ -std=c++17 -Wall -fprofile-arcs -ftest-coverage conta_palavras.o testa_conta_palavras.cpp -o testa_conta_palavras
	./testa_conta_palavras
	gcov -c conta_palavras.cpp
	find . -type f -name "*.gcov" ! -name "conta_palavras.cpp.gcov" -exec rm -f {} +
	 
debug: testa_conta_palavras.cpp   conta_palavras.cpp conta_palavras.hpp 
	g++ -std=c++17 -Wall -g -c conta_palavras.cpp
	g++ -std=c++17 -Wall  -g conta_palavras.o testa_conta_palavras.cpp -o testa_conta_palavras
	gdb testa_conta_palavras
	
docs: testa_conta_palavras.cpp conta_palavras.cpp conta_palavras.hpp
	doxygen
	
cppcheck: testa_conta_palavras.cpp   conta_palavras.cpp conta_palavras.hpp
	cppcheck  --enable=warning conta_palavras.cpp

valgrind: testa_conta_palavras
	valgrind --leak-check=yes --log-file=valgrind.rpt ./testa_conta_palavras

clean:
	rm -rf *.o *.exe *.gc* testa_conta_palavras 