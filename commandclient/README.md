TicTacNode-CommandLineClient
=============

Command Line Client for the TicTacNode project.

###Compiling Instructions:
This project requires libcurl, Boost::Thread, Boost::PropertyTree, and Boost::Foreach. On Mac OSX and 
Linux these can be installed from your package manager. If, on OSX, you do not have a package manager, we recommend 
installing Homebrew (http://brew.sh/), as it will make installing dependencies much easier.
Support is not currently available for Windows.

###Compiling
The program is compiled using the makefile.
```bash
$ make all
```

###Usage:
The command line client is run from the command line as follows:
```bash
$ ./cmdclient
```

The program will ask you if you want to use the default host or change to a different host. Press y to use the default host cpssd4-web.computing.dcu.ie:80/ and n to use an alternitive host.
