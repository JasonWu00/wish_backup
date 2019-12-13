# WIndows SHell (WinShell)

### Features implemented by WISH

* Running singular commands (including cd and exit)
* Running multiple commands separated by one or more semicolons
* Simple redirection using > and <

### Features unsuccessfully implemented

* (Expected as of 11:31pm December 11) Pipes

### Bugs present in the shell

* Putting a space in front of and behind semicolons may result in commands not executed properly
  * E.g. "echo 1 ; echo 2" might not work, but "echo 1;echo 2" will work.

### Function Headers
