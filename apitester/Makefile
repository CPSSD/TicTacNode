all: apitester.cpp
	g++ ./apitester.cpp -std=c++11 -lboost_thread -lboost_system -lboost_unit_test_framework -lcurl -o ./apitester

osx: apitester.cpp
	g++ ./apitester.cpp -std=c++11 -L/opt/local/lib -lboost_thread-mt -lboost_system-mt -lboost_unit_test_framework-mt -lcurl -o ./apitester
