all: main.cpp
	g++ ./*.cpp -Wall -std=c++11 -lboost_system -lboost_thread -lcurl -o ./tictacnode_ai

debug: main.cpp
	g++ ./*.cpp -Wall -std=c++11 -lboost_system -lboost_thread -lcurl -g -o ./tictacnode_ai

doc: Doxyfile
	doxygen
