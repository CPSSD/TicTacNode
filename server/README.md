# TicTacNode Server #
This is the server for the TicTacToe game, written in Node.js

## Installation ##

###Install Node Package Manager###

>**Debian:** `sudo apt-get install npm`

>**OpenSUSE:** `sudo zypper in npm`

>**Arch:** `sudo pacman -S npm`

### Add the nodejs to the node path ###

>`sudo ln -s "$(which nodejs)" /usr/bin/node`

### Install server dependencies ###
Navigate to the server directory and run

>`sudo npm install`

### Install MongoDB ###
For operating system specific instructions please consult
> http://docs.mongodb.org/manual/installation/  

Start the server with operating system specific command  
>**Debian:** `sudo service mongod start`

## Running the server ##

In order to start the server automatically, execute permission must be given to the *ttn* file
> `chmod +x ttn`

Start the server using
> `sudo ./ttn`

## Stopping the server ##
> `sudo forever stop TictacNode`


## Configuration ##
All configuration is included in *config.json*

Only configuration with number and arrows can be edited without causing errors to the server
```
    {
      "version": {
        "major":2,
        "minor":2
      },

      "db":{
1-->    "name":"tictacnode",
        "collections": [
          "games",
          "meta"
        ]
      },

      "authReq": [
        "version",
        "startGame",
        "listGames",
        "joinGame",
        "endGame",
        "next",
        "move",
        "serverAdmin"
      ],

      "server": {
2-->    "check_interval": 20000,
3-->    "timeout": 3,
4-->    "start_timeout": 6,
5-->    "port":80
      }
    }
```

#### 1) Database name ####
This contains the connection information for the database. This must be a valid MongoDB connection string. More information can be found on http://docs.mongodb.org/manual/reference/connection-string/.

#### 2) Check Interval ####
This is the interval at which the server checks for old games. Value is given in milliseconds.  
__Default:__ `20000` (20 seconds)

#### 3) Timeout ####
This value determines the maximum time between movements of players. To set the game timeout, multiply this value by _2) Check Interval_  
__Example__: 20000 * 3 = 60000ms = 60 seconds  
__Default__: `3` (60 seconds)

#### 4) Start Timeout ####
At the beginning of the game, an exception is made where the games are terminated after longer amount of time. This allows for more time for players to join games. The time is calculated the same as _3) Timeout_.  
__Example__: 20000 * 6 = 120000ms == 2 minutes  
__Default__: `6` (2 minutes)

#### 5) Port ####
The port at which the server starts  
__Default__: `80`

---

## Common Problems and Solutions ##
### Server Failed to Start, please consult the README ###
Run `sudo ./ttn` and make sure it has proper execution permissions, as stated in [Running the Server](#Running-the-Server)

### Server says it started but no content is displayed
Make sure the dependencies are installed, as described in [Installing server dependencies](#install-server-dependencies)

### error: Forever cannot find process with index: TicTacNode ###
Running with `sudo` should solve the problem (as the server is running as root and not current user)
