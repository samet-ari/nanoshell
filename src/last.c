#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> // exit function
#include <sys/wait.h>
#include "nanoshell.h"

int my_strlen(char *str) {
    int i = 0;
    for (i = 0; str[i]; i++)
    return i;
}


int main (void) {
    char line[BUFFFER_SIZE] = {0};
    char *av[] = {"ls", NULL};
    char *env[] = {NULL};
    int pid = 0;

    
    
    while (1){
    printf("?> ");

    fgets(line, BUFFFER_SIZE, stdin);
    line[my_strlen(line) - 1] = 0; // remove newline character
    pid = fork();
    if (pid == 0) {
        execve("/bin/ls", av, env);
        printf("Wut :/\n");
        exit(-1);
    }
    // Parent process
    waitpid(pid, NULL, 0);
}
    return 0;

}