all: main.cpp
	g++ commandclient.cpp -std=c++11 -lboost_system -lboost_thread -lcurl -o ./commandclient

debug: main.cpp
	g++ commandclient.cpp -std=c++11 -lboost_system -lboost_thread -lcurl -g -o ./commandclient

test: test.cpp
	g++ test.cpp -std=c++11 -lboost_system -lboost_threadst_unit_test_framework -lcurl -o ./test

test_osx: test.cpp
	g++ test.cpp -std=c++11 -L/opt/local/lib -lboost_system-mt -lboost_thread-mt -lboost_unit_test_framework-mt -lcurl -o ./test

doc: Doxyfile
	doxygen
