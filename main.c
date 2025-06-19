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

        // Code for external commands goes here
        //fork.....
    }

    return 0;
}