all: main.cpp
	g++ commandclient.cpp -std=c++11 -lboost_system -lboost_thread -lcurl -o ./commandclient

debug: main.cpp
	g++ commandclient.cpp -std=c++11 -lboost_system -lboost_thread -lcurl -g -o ./commandclient

doc: Doxyfile
	doxygen
