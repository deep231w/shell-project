#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT 1024

int main() {
    char input[MAX_INPUT];

    while (1) {
        // 1. Print prompt
        printf("myshell> ");
        fflush(stdout);

        // 2. Read input
        if (!fgets(input, MAX_INPUT, stdin)) {
            break;
        }

        // Remove newline
        input[strcspn(input, "\n")] = 0;

        // 3. Exit command
        if (strcmp(input, "exit") == 0) {
            printf("Goodbye!\n");
            break;
        }

        // 4. Parse into args
        char *args[64];
        int i = 0;
        args[i] = strtok(input, " ");

        while (args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " ");
        }

        // 5. Fork child
        pid_t pid = fork();
        if (pid == 0) {
            // child runs command
            execvp(args[0], args);
            perror("Command failed");
            exit(1);
        } else {
            // parent waits
            wait(NULL);
        }
    }

    return 0;
}
