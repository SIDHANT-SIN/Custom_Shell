#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>
#define argsze 100

int main() {
    char *input = NULL;
    size_t sze = 0;    
    char *args[argsze];       

    while (1) {
        printf("custom_shell$ ");
        fflush(stdout);

        // reading input
        if (getline(&input, &sze, stdin) == -1) {
            printf("\n");
            break;
        }
        input[strcspn(input, "\n")] = '\0'; 

        // exit cmd
        if (strcmp(input, "exit") == 0) {
            break;
        }

        int i = 0;
        args[i] = strtok(input," ");
        while (args[i] != NULL && i< (argsze - 1)) {
            i++;
            args[i] = strtok(NULL, " ");
        }
        args[i] = NULL;
        if (args[0] == NULL) continue;

        // echo cmd
        if (strcmp(args[0], "echo") == 0) {
            for (int j = 1; args[j] != NULL; j++) {
                printf("%s ", args[j]);
            }
            printf("\n");
            continue;
        }

        // pwd cmd
        if (strcmp(args[0], "pwd") == 0) {
            char cwd[1024];
            if (getcwd(cwd, sizeof(cwd)) != NULL)
                printf("%s\n", cwd);
            else
                perror("pwd error");
            continue;
        }

        // cd cmd
        if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL) {
                fprintf(stderr, "cd: missing argument\n");
            } else {
                if (chdir(args[1]) != 0)
                    perror("cd error");
            }
            continue;
        }

        // ls cmd
        if (strcmp(args[0], "ls") == 0) {
            DIR *d = opendir(".");
            if (d == NULL) {
                perror("ls error");
                continue;
            }
            struct dirent *entry;
              entry = readdir(d);
              while (entry != NULL) {
                if (entry->d_name[0] != '.'){
                printf("%s\n", entry->d_name);}
             entry = readdir(d); 
            }

            printf("\n");
            closedir(d);
            continue;
        }

        // prebuild cmds 
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork failed");
        } else if (pid == 0) {
            execvp(args[0], args);
            perror("command not found");
            exit(EXIT_FAILURE);
        } else {
            wait(NULL);
        }
    }
    free(input);
    return 0;
}
