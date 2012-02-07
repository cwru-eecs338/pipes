Pipes
=====

Getting the files:
------------------
If git is installed, you can just use:

    git clone git@github.com:cwru-eecs338/pipes.git

Otherwise, you can download and extract the tarball using:

    wget --no-check-certificate -q -O - https://github.com/cwru-eecs338/pipes/tarball/master | tar -xzvf -

Lessons:
--------
 - How to write a basic shell script
 - How to pipe the output (stdout) of one command into the input (stdin) of another
 - Using the `pipe` and `dup` system calls to implement pipes between commands in C

Instructions:
-------------
1. Open `secret.sh` and read the comments
2. Execute the script using `./secret.sh` on the command line
3. Now, open `c_cret.c` and read the comments (this program essentially does the
   same thing as `secret.sh`, but it explicitly implements the pipe between the
   commands using `pipe` and `dup`)
4. Compile `c_cret.c` using `make`, and run it using `./c_cret`
