#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    char line[1024];

    while(1) {
        // Prompt user
        printf("ProjSh$: ");

        // Read single line from input
        fgets(line, sizeof(line), stdin);

        // Check if EOF is reached (Ctrl-D) or command is exit
        if (feof(stdin) || !strcmp(line, "exit\n")) {
            // Terminate
            printf("Exiting...\n");
            exit(0);
        }

        // Check if command is "cd"
        if (!strcmp(line, "cd\n")) {
            // Get home directory
            char* homeDirectory = getenv("HOME");
            // Change current working directory to home directory
            chdir(homeDirectory);
            // Skip to new command
            continue;
        }

        // Get first token of command
        char* token = strtok(line, " \n");
        // Check if first token is "cd"
        if (!strcmp(token, "cd")) {
            // Get second token of command
            token = strtok(NULL, " \n");

            // Attempt changing directory to second token
            if (chdir(token) != 0) {
                // Print error if there is one
                printf("%s\n", strerror(errno));
            }

            // Skip to new command
            continue;
        }


        // parses through the arguments in the line
        const int MAX_TOKENS = 10; // max arg value specified in project instructions
        char *args[MAX_TOKENS + 1]; // allocates an array for the arguments with a max of 10 (11 including NULL arg)
        args[0] = token; // we already have the first token so we just put it in the array
        int i = 1; // Start from the second token
        // Go until end of tokens or too many tokens
        while (token != NULL && i < MAX_TOKENS) {
            token = strtok(NULL, " \n"); // get next token
            args[i++] = token;
        }
        args[i] = NULL; // null token should always be last in arguments for execvp to function properly

        // creates a process for the command execution
        pid_t pid = fork(); 
        if (pid < 0) {
            printf("Error in forking.\n");
            continue;
        }
        // if we are in the child process..
        else if (pid == 0) {
            execvp(args[0], args); // execute command if able 
            errno && printf("Error: Command could not be executed\n");
            exit(errno); // return error if not able to execute
        }
        else {
            // parent waits for child process to finish
            int status;
            waitpid(pid, &status, 0);
        } 
    }

    return 0;
}