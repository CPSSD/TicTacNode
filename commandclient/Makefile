all: commandclient.cpp
	g++ commandclient.cpp -std=c++11 -lboost_system -lboost_thread -lcurl -o ./cmdclient

debug: commandclient.cpp
	g++ commandclient.cpp -std=c++11 -lboost_system -lboost_thread -lcurl -g -o ./cmdclient

test: test.cpp
	g++ test.cpp -std=c++11 -lboost_system -lboost_threadst_unit_test_framework -lcurl -o ./test
	
osx: commandclient.cpp
	g++ commandclient.cpp -std=c++11  -L/opt/local/lib -lboost_system-mt -lboost_thread-mt -lcurl -o ./cmdclient

test_osx: test.cpp
	g++ test.cpp -std=c++11 -L/opt/local/lib -lboost_system-mt -lboost_thread-mt -lboost_unit_test_framework-mt -lcurl -o ./test

doc: Doxyfile
	doxygen
