#!/bin/sh
# The previous line is called a "shebang," and is used by the program loader to
# determine what program should be used to interpret this script. This file is
# given to the specified program as an argument. Therefore, executing this file
# is equivalent to running the command `sh secret.sh`

# A shell script is just a list of shell commands in a file.  In this case,
# we're piping the output of one command ("echo") into another ("rev")
echo ".egassem terces eht derevocsid tsuj ev'uoY .snoitalutargnoC" | rev
