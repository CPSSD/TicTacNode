all: main.cpp
	g++ commandclient.cpp -Wall -std=c++11 -lboost_system -lboost_thread -lcurl -o ./commandclient

debug: main.cpp
	g++ commandclient.cpp -Wall -std=c++11 -lboost_system -lboost_thread -lcurl -g -o ./tictacnode_ai

doc: Doxyfile
	doxygen
