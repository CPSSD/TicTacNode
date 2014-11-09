AM_CXXFLAGS = -Wall -std=c++11

bin_PROGRAMS = tictacnode_ai
tictacnode_ai_SOURCES = main.cpp Connector.hpp Connector.cpp AI.hpp AI.cpp Response.hpp Response.cpp
tictacnode_ai_CPPFLAGS = $(BOOST_CPPFLAGS)
tictacnode_ai_LDFLAGS = $(BOOST_THREAD_LDFLAGS) $(BOOST_SYSTEM_LDFLAGS)
tictacnode_ai_LDADD = $(BOOST_THREAD_LIBS) $(BOOST_SYSTEM_LIBS) -lcurl
