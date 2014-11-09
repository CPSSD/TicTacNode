TicTacNode-AI
=============

AI program for the TicTacNode project.

###Compiling Instructions:
This project requires libcurl, Boost::Thread, Boost::PropertyTree, and Boost::Foreach. On Mac OSX and 
Linux these can be installed from your package manager. On Windows, compilation requires MinGW. Please 
consult the MinGW documentation for information on how to install and register the required libraries.

In a POSIX shell, run the following commands from the directory in which this README is located:
```
./configure
make
```
This will compile a binary called "ai" in the src subdirectory. If you wish to be able to run this AI 
from anywhere in your shell, then run the command:
```
sudo make install
```
from the same directory after running the previous two commands.

###Usage:
The AI is run from the command line as follows:
```
ai [hostname] [ai_name]
```

The hostname is an optional argument which takes a URL pointing to an instance of the TicTacNode 
server. If no port number is supplied, it will default to 80. If left blank, the host will default to 
"vm1.razoft.net:1337".

The ai_name is another optional argument which takes a string saying the name you wish the AI to use 
when connecting to the server. If no name is supplied, it will default to "ColinAI".
