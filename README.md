# Angel - Linux Shell in C

## Introduction

This is the implementation of a Linux shell written in C language.


## How to run the shell

1. Run the command `make` on your terminal.
2. Run `./angel` to get a prompt of the form `<username@system_name:path>`.
3. Run any command in the shell. It can entail as many number of tabs and spaces, the shell accounts for those.
4. In order to exit, run `exit`.

## Features

### Built-in commands

These commands have been defined by me and are contained within the shell itself.

1. `pwd`
    
    - Displays the name of the working directory.
    - Implemented in [pwd.c](pwd.c).
    - Function Declarations are in [pwd.h](pwd.h).

2. `ls [-l -a] [directory]`
    
    - Lists all the files and directories in the specified directory in alphabetical order.
    - Variations such as `ls, ls . , ls .., ls ~, ls -la / ls -al, ls -a -l` also work.
    - Also handles multiple directories as arguments. eg. `ls [-l -a] dir1 dir2 dir3`.
    - Throws error if you try to `ls` on anything except a directory or a file. 
    - Implemented in [ls.c](ls.c).
    - Function Declarations are in [ls.h](ls.h).

3. `cd [file]`
    
    - Changes directory to the directory specified, throws an error if the directory does not exist.
    - Variations such as `cd ., cd .. , cd - and cd ~`.
    - Implemented in [cd.c](cd.c).
    - Function Declarations are in [cd.h](cd.h).

4. `echo [arguments]`
    
    - Displays whatever is specified in [arguments]. 
    - Accounts for double quotes and handle tabs and spaces.
    - Implemented in [echo.c](echo.c)
    - Function Declarations are in [echo.h](echo.h).

5. `exit`
    - Exits the shell.

6. promtpinting
    - Contains the `<username@system_name:path>` in blue, green and white colors similiar to the Linux shell.
    - Implemented in [prompt.c](prompt.c)
    - Function Declarations are in [prompt.h](prompt.h).

7. `repeat`
    - Responsible for executing the given instruction multiple times. 
    - Implemented in [repeat.c](repeat.c)
    - Function Declarations are in [repeat.h](repeat.h).

8. `Command Handler` 
    - Has the functionality to execute various commands entered by the user.
    - Implemented in [run.c](run.c)
    - Function Declarations are in [run.h](run.h).

9. `headers.c`
    - Contains some common headers and libraries.
    - Implemented in [headers.h](headers.H)

10. `signalHandlers.c`
    - Contains signal checker for any suspeneded or exited background process.
    - Also contains the signal controllers for Ctrl+C & Ctrl+Z.
    - Implemented in [signalHandlers.h](signalHandlers.h).

11. `bg [JobIndex]`
    - Changes the state of a stopped background job to running (in the background) & handles error if no background Process is present.
    - Implemented in [bg.h](bg.h) and [bg.c](bg.c).

12. `fg [JobIndex]`
    - Brings the running or stopped background job corresponding to job number to the foreground, and changes its state to running.
    - Implemented in [fg.h](fg.h) and [fg.c](fg.c).

13. `sig [JobIndex] [SIGNAL]`
    - Takes the job number (assigned by your shell) of a running job and sends the signal corresponding to signal number to that process.
    - Implemented in [sig.h](sig.h) and [sig.c](sig.c).

14. `jobs [-r -s]`
    - Prints a list of all currently running background processes in alphabetical increasing order as Running or Stopped.
    - If the flag specified is -r, then only the running processes are displayed 
    - If the flag is -s then the stopped processes are printed.

15. pipe.c
    - This file is used to implement the pipe and I/O Redirection within Command Pipelines functionality in the commands. 
    - I basically parse the pipes by the `|` symbol and then execute each subsequent command. 
    - For example in `c1 | c2 | c3`, initially, I tokenize the commands by `|` symbol. Then each of the commands is run sequentially such that the output of one command becomes the input of the following command using `dup(), dup2() & fork()`.

16. redirection.c
    - This file contains code for the Input/Output redirecting functionality i.e, `<, >, >>`.
    - Both input and output redirection can be used simultaneously.
    - The created output file has permissions 0644 if it does not already exist.
    - In case the output file already exists, then it overwrites in case of `>` and appends to in case of `>>`.

17. `CTRL-Z, CTRL-C, CTRL-D`
    - `CTRL-Z` - Pushes any currently running foreground job into the background, and change its state from running to stopped. This has no effect on the shell if there is no foreground process running.
    - `CTRL-C` - Interrupts any currently running foreground job, by sending it the SIGINT signal. This has no effect on the shell if there is no foreground process running.
    - `CTRL-D` - Logs the user out of the pseudo shell, without having any effect on the actual terminal.
    - Implemented in [sig.h](sig.h), [sig.c](sig.c) & [main.c](main.c).

18. `replay -command <command> -interval <timeInterval> -period <timePeriod>`
    - Executes <command> after every <timeInterval> seconds until <timePeriod> seconds are elapsed.
    - Implemented in [replay.c](replay.c) & [replay.h](replay.h).

19. baywatch [-n] <timeInSeconds> dirty
    - Prints the size of the part of the memory which is dirty.
    - A line every <timeInSeconds> second until ‘q’ is pressed.
    - Implemented in [dirty.c](dirty.c) & [dirty.h](dirty.h).

20. `makefile`
    - This file contains the code to run the shell. To compile the shell, run: `make`
    - After compilation, to start the shell run: `./angel`

### Foreground and Background Processes

- Upon termination of a background process, the shell prints its PID and exit status.
- Handles foreground processes `&` when it is in the end and prints the `[PID]` of the process.
- Implemented in [foregroundProcess.c](foregroundProcess.c) and [backgroundProcess.c](backgroundProcess.c).
- Function Declarations are in [foregroundProcess.h](foregroundProcess.h) and [backgroundProcess.h](backgroundProcess.h).


### Additional Commands

1. `pinfo [PID]`

    - Prints numerous details about the process such as its status, memory, and executable path.
    - Just `pinfo` with no arguments gives details of the shell.
    - Implemented in [pinfo.c](pinfo.c)
    - Function Declarations are in [pinfo.h](pinfo.h). 


2. `history [num] or history`

    - Lists the last [num] commands. If no arguments are specified, it displays the last k commands where k <= 10.
    - `[num]` should be less than 20.
    - Retains the `history` even upon Shell exit - uses [angelHistory.txt](angelHistory.txt).
    - Implemented in [history.c](history.c) 
    - Function Declarations are in [history.h](history.h).


### Coding style

The code is completely modular with different `.c` files for each command, and a `main.c` binding them all together. The files ending with `.h` entails all the necessary header files, and global variables. 

