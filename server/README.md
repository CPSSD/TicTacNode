# TicTacNode Server #
This is the server for the TicTacToe game, written in Node.js


## Installation ##

### Linux ###
Install Node Package Manager

**Debian:** `sudo apt-get install npm`

**OpenSUSE:** `sudo zypper in npm`

**Arch:** `sudo pacman -S npm`

Add the nodejs to the node path

>`sudo ln -s "$(which nodejs)" /usr/bin/node`

Install Forever

>`sudo npm install forever -g`


### Windows and OSX ###
Download and install Node.js
>http://nodejs.org/download/

Install forever

>`npm install forever -g`


## Running the server ##

Start the server using forever to daemonize the server

>`forever start --uid "TicTacNode" server.js`

**Note**: When running the server below port 1024 on Linux add `sudo` before `forever`

## Stopping the server

`forever stop TicTacNode`

## Unit Testing

Install unit.js using npm.

`npm install unit.js`

Install mocha.

`npm install -g mocha`

Install the request module.

`npm install request`

The unit tests can now be run using this command.
`mocha test.js`
