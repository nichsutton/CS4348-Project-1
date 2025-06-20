# Team 2
## Members: Daniel Dimitrov, Nicholas Sutton

### File Listings:
* main.c - This is the main shell program file. It includes all code used to implement the shell - including command execution, process management, tokenization of inputs, and prompting.
* README.md - This file includes all information regarding the project - including key commands, compilation and running instructions, and any used sources.

### Compiling the program:
To compile this program make sure you are in the project directory. Then type the following command:
`gcc -o shell main.c`

### Running the program:
To run this program, simply type the following into the same directory as where you compiled the program. (this should be in the same directory as before)
`./shell`    

To exit the shell at anytime type the following into its command prompt:
`exit`
... or you can you can send an EOF using `Ctrl + D`.

### Sources:
* For using the execvp function: https://www.qnx.com/developers/docs/8.0/com.qnx.doc.neutrino.lib_ref/topic/e/execvp.html
* For using the strtok function: https://www.geeksforgeeks.org/cpp/strtok-strtok_r-functions-c-examples/