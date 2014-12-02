all: main.cpp
	g++ commandclient.cpp -Wall -std=c++11 -lboost_system -lboost_thread -lcurl -o ./commandclient

debug: main.cpp
	g++ commandclient.cpp -Wall -std=c++11 -lboost_system -lboost_thread -lcurl -g -o ./commandclient

test: test.cpp
	g++ test.cpp -std=c++11 -lboost_system -lboost_thread -lcurl -o ./test

doc: Doxyfile
	doxygen
