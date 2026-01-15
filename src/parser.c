#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARGS 64

/**
 * Découpe la commande en arguments selon les espaces
 * Exemple: "ls -la /home" -> ["ls", "-la", "/home", NULL]
 * 
 * Après utilisation, il faut libérer la mémoire avec free_args() !
 */
char** parse_command(char* line) {
    char** args = malloc(MAX_ARGS * sizeof(char*));
    if (args == NULL) {
        perror("malloc");
        return NULL;
    }
    
    int i = 0;
    char* token = strtok(line, " \t");  // Découpe selon espaces et tabs
    
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i] = strdup(token);  // Copie le token
        i++;
        token = strtok(NULL, " \t");
    }
    
    args[i] = NULL;  // Dernier élément NULL (requis pour execve)
    
    return args;
}

/**
 * Libère la mémoire du tableau créé par parse_command()
 */
void free_args(char** args) {
    if (args == NULL) return;
    
    for (int i = 0; args[i] != NULL; i++) {
        free(args[i]);
    }
    free(args);
}

/**
 * Affiche les arguments (pour les tests)
 */
void print_args(char** args) {
    printf("Arguments parsés:\n");
    for (int i = 0; args[i] != NULL; i++) {
        printf("  args[%d] = '%s'\n", i, args[i]);
    }
}