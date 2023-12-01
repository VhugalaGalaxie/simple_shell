#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_CMD_LEN 256
#define MAX_NUM_CMDS 32

void read_command(char *cmd_lin, char *cmd_s[], int *numb_cmds);
void execute_command(char *cmd_lin, char *cmd_s[], int numb_cmds);

int main() {
    char cmd_lin[MAX_CMD_LEN];
    char *cmd_s[MAX_NUM_CMDS];
    int numb_cmds;

    while (1) {
        printf("simple_shell> ");
        fgets(cmd_lin, MAX_CMD_LEN, stdin);
        read_command(cmd_lin, cmd_s, &numb_cmds);
        execute_command(cmd_lin, cmd_s, numb_cmds);
    }

    return 0;
}

void read_command(char *cmd_lin, char *cmd_s[], int *numb_cmds) {
    char *token = strtok(cmd_lin, " \n");
    int ii = 0;

    while (token != NULL && ii < MAX_NUM_CMDS) {
        cmd_s[ii] = token;
        ii++;
        token = strtok(NULL, " \n");
    }

    *numb_cmds = ii;
}

void execute_command(char *cmd_lin, char *cmd_s[], int numb_cmds) {
    if (strcmp(cmd_s[0], "exit") == 0) {
        exit(0);
    } else if (strcmp(cmd_s[0], "cd") == 0) {
        if (numb_cmds == 2) {
            chdir(cmd_s[1]);
        } else {
            printf("cd command requires 1 argument.\n");
        }
    } else {
        pid_t pid = fork();

        if (pid == 0) {
            execvp(cmd_s[0], cmd_s);
            printf("Command not found.\n");
            exit(0);
        } else if (pid < 0) {
            printf("Error creating child process.\n");
        } else {
            wait(NULL);
        }
    }
}