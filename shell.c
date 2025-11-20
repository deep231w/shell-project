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
        printf("\033[1;32mmyshell>\033[0m ");
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
            if(execvp(args[0], args)==-1){
                printf("\x1b[31mcommand doesnot exit: '%s'\x1b[0m\n",args[0]);

            }
            // perror("command not found '%s'\n",args[0]);
            exit(1);
        } else {
            // parent waits
            wait(NULL);
        }
    }

    return 0;
}
