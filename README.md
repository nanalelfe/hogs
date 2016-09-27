# Hogs
A program that inspects the output from the ps aux command and finds the process consuming the most resources (either cpu cycles or memory).
## Usage Instructions
From standard input, the program reads input in the same format as produced by the ps program with the aux argument when run on cdf.

The program takes a command-line argument specifying a username, and will print some information about one process owned by this user to standard output.

The program accepts an optional command-line argument of -m or -c, which must come before the username. Only one of these arguments may be provided. If -c is provided, the program reports the user's process that has the highest value for CPU usage. If -m is provided, the program reports the user's process that has the highest memory usage instead. If neither argument is provided, report the process with the highest CPU usage.

The output of the program is one line containing the PID, usage value (either memory or CPU - whichever is being compared) with exactly one digit after the decimal, and command, separated by tabs ('\t').

If the input does not contain any processes owned by the specified user, there is no output. This is not an error.

We are assuming that usernames and commands will be at most 127 characters.
