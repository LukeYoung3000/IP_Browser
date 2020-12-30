# IP Browser #

Small/Simple GUI program to help keep track of IPv4 addresses allocated to network devices.
IPs can be filtered via assosiated sub network or physical device.

### Implementation Overview ###
This project was a little weekender to help me learn the basics of WXWidgets and SQL in C++ for work.
The program dosen't do very much error checking. Just dose the basics for everything to work.

* GUI: WXWidgets 3.1.4 (Not Included)
* Storage: SQLite 3.24.0 (Included)
* Compiler/IDE: Visual Studio 2017 Community

### How To Use ###
1. Run "App\IP_Browser.exe" to start the application or compile from source.
2. Open "App\ip.db" in a SQLite editor (sqlitebrowser.org) to update your IP database.
Currently there is random test data in the db. I will add a db editor feature to the GUI at some point.

### Features To Add ###
* Select/load any database from the file system.
* Database editor (Add Network, Add Device, ect).
* Display "Notes" feild of the database.
* Copy IP addresse(s) to clip board.
