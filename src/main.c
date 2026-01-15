#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nanoshell.h"
#include "builtins.h"


#define MAX_LINE 1024

int main() {
    char line[MAX_LINE];
    
    printf("Nanoshell démarré! (Tapez 'exit' pour quitter)\n");
    
    while (1) {
        // Affiche le prompt
        printf("?> ");
        fflush(stdout);
        
        // Lit l'entrée utilisateur
        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\nAu revoir!\n");
            break;
        }
        
        // Supprime le caractère de fin de ligne
        line[strcspn(line, "\n")] = 0;
        
        // Vérifie si la ligne est vide
        if (strlen(line) == 0) {
            continue;
        }
        
        // Parse la commande (découpe en mots)
        char** args = parse_command(line);
        if (args == NULL || args[0] == NULL) {
            continue;
        }
        
        // Essaie d'exécuter un builtin
        int builtin_result = execute_builtin(args);
        
        if (builtin_result == -1) {
            // C'est la commande exit
            printf("Au revoir!\n");
            free_args(args);
            break;
        }
        else if (builtin_result == 0) {
            // Builtin exécuté avec succès
            free_args(args);
            continue;
        }
        
        // Ce n'est pas un builtin, on verra plus tard pour les commandes externes
        printf("nanoshell: weird, %s is not here… :/\n", args[0]);
        
        // Libère la mémoire
        free_args(args);
    }
    
    return 0;
}