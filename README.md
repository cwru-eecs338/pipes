Pipes
=====

Getting the files:
------------------
If git is installed, you can just use:

    git clone git://github.com/cwru-eecs338/pipes.git

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

Named Pipes:
------------
The pipes used above are called "unnamed pipes," since they only live for the
duration of the program in which they are used. Another type of pipe is the
"named pipe," which is given a name in the file system and can serve as a
rendezvous point for two processes.

For example, you can created a named pipe via the command `mkfifo` as in:

    mkfifo my_named_pipe

This makes a pipe with the given name in the current directory. If you use `ls`,
you will be able to see the pipe in the file system.

Now, to use the pipe, you need one process to write to it and another process to
read from it. To do this at once, I recommend using a tool like `screen` or
`byobu`. After you've started `byobu`, use `ctrl+a` followed by `c` to create a
new screen. Then, use `ctrl+a` followed by `S` (i.e. `shift+s`) to split the
screen. Use `ctrl+a` followed by `Tab` to navigate between the split screens,
and `ctrl+a` followed by either `0` or `1` (the appropriate window number) to
load a window into each half of the split.

Now that your screen session is set up, in the top window, run the command:

    echo "Hello Pipes" > my_named_pipe

which will write the string `"Hello Pipes"` into the file `my_named_pipe`.
However, because this is actually a pipe instead of a file, note how this
command freezes until the other end of the pipe has been opened.

Now, use `ctrl+a` followed by `Tab` to switch to the other window, and run the
command:

    cat my_named_pipe

which will read the contents of `my_named_pipe` and print it to standard out.
Note that at this point, both commands execute and the string is transfered
between the two processes.

After you've done this, you can use `ls` to see that the named pipe is still
there. To get rid of it, just use `rm my_named_pipe` as you would for a normal
file.
