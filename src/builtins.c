#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "nanoshell.h"

// Variable d'environnement externe
extern char **environ;

/**
 * Commande: pwd
 * Affiche le répertoire courant
 */
int builtin_pwd(char** args) {
    (void)args;  // Non utilisé
    
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
        return 0;
    } else {
        perror("pwd");
        return 1;
    }
}

/**
 * Commande: cd
 * Change le répertoire courant
 * Gère: cd, cd ~, cd .., cd somedir
 */
int builtin_cd(char** args) {
    char* path;
    
    // cd sans argument ou cd ~ -> aller au home
    if (args[1] == NULL || strcmp(args[1], "~") == 0) {
        path = getenv("HOME");
        if (path == NULL) {
            fprintf(stderr, "cd: HOME non défini\n");
            return 1;
        }
    } else {
        path = args[1];
    }
    
    if (chdir(path) != 0) {
        perror("cd");
        return 1;
    }
    
    return 0;
}

/**
 * Commande: env
 * Affiche toutes les variables d'environnement
 */
int builtin_env(char** args) {
    (void)args;  // Non utilisé
    
    for (int i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }
    
    return 0;
}

/**
 * Commande: exit
 * Quitte le shell
 */
int builtin_exit(char** args) {
    (void)args;  // Non utilisé
    return -1;  // Signal spécial pour quitter
}

/**
 * Vérifie si la commande est un builtin et l'exécute
 * Retourne:
 *   -1 si c'est exit (signal de sortie)
 *    0 si builtin exécuté avec succès
 *    1 si ce n'est pas un builtin
 */
int execute_builtin(char** args) {
    if (args[0] == NULL) {
        return 1;
    }
    
    if (strcmp(args[0], "pwd") == 0) {
        return builtin_pwd(args);
    }
    else if (strcmp(args[0], "cd") == 0) {
        return builtin_cd(args);
    }
    else if (strcmp(args[0], "env") == 0) {
        return builtin_env(args);
    }
    else if (strcmp(args[0], "exit") == 0) {
        return builtin_exit(args);
    }
    
    // Ce n'est pas un builtin
    return 1;
}