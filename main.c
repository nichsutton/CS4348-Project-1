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
        char* token = strtok(line, " ");
        // Check if first token is "cd"
        if (!strcmp(token, "cd")) {
            // Get second token of command
            token = strtok(NULL, " ");
            // Remove \n from end of token
            token[strlen(token) - 1] = 0;

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
        int i = 0;
        token = strtok(line, " \n"); // get the initial token from the line
        while (token != NULL && i < MAX_TOKENS) {
            args[i] = token; i++;
            token = strtok(NULL, " \n"); // get all subsequent tokens
        }
        args[i] = NULL; // null noken should always be last in arguments for execv to function properly

        // creates a process for the command execution
        pid_t pid = fork(); 
        if (pid < 0) {printf("Error in forking.\n"); continue;}
        // if we are in the child process..
        else if (pid == 0) {
            execvp(args[0], args); // execute command if able 
            errno && printf("Error: Command could not be executed\n"); exit(errno); // return error if not able to execute
        }
        else {int status; waitpid(pid, &status, 0);} // parent waits for child process to finish
    }

    return 0;
}