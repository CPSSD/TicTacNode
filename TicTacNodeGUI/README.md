TicTacNode-GUI Client
=============

GUI client for the TicTacNode project.

###Compiling Instructions:
On linux and mac, mono is required to compile the GUI. It can be downloaded from http://www.mono-project.com/

On windows, the GUI requires the .NET Framework which can be downloaded from http://www.microsoft.com/net

###Compiling
The program is compiled using the makefile.
For linux and osx : 
```bash
$ make all
```

On windows, the program can be complied from command line using the following command. The path to the compiler depends on where .NET is installed. e.g C:\Windows\Microsoft.NET\Framework\v4.0.30319\csc.exe
```bash
$ (path to compiler) /out:guiclient.exe ./*.cs /reference:Newtonsoft.Json.dll
```


###Usage:
The GUI client is run from the command line as follows:
```bash
$ ./guiclient.exe
```
