TicTacNode-AI
=============

AI program for the TicTacNode project.

###Compiling Instructions:
This project requires libcurl, Boost::Thread, Boost::PropertyTree, and Boost::Foreach. On Mac OSX and 
Linux these can be installed from your package manager. If, on OSX, you do not have a package manager, we recommend 
installing Homebrew (http://brew.sh/), as it will make installing dependencies much easier.
 Support is not currently available for Windows.

### Compiling on Linux ###

In a POSIX shell, run the following command from the directory in which this README is located:
```bash
$ make
```
This will compile a binary called "tictacnode_ai".

### Compiling on OSX ###

In a POSIX shell, run the following command from the directory in which this README is located:
```bash
$ make osx
```
This will compile a binary called "tictacnode_ai".

### Compiling the Documentation ###

In a POSIX shell, run the following command from the directory in which this README is located:
```bash
$ make doc
```
This will create a folder called "doc", in which you will find documentation formatted in both HTML and LaTeX. 

###Usage:
The AI is run from the command line as follows:
```bash
$ tictacnode_ai [hostname] [ai_name] [num_of_games]
```

The hostname is an optional argument which takes a URL pointing to an instance of the TicTacNode 
server. If no port number is supplied, it will default to 80. If left blank, the host will default to 
"cpssd4-web.copmuting.dcu.ie:80".

The ai_name is another optional argument which takes a string saying the name you wish the AI to use 
when connecting to the server. If no name is supplied, it will default to "ColinAI".

The num_of_games is the final optional argument which takes an int with the number of concurrent games you wish to run, with
a maximum of 20. If no number is supplied, it will default to 1 game.
