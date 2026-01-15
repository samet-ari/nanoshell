#ifndef NANOSHELL_H
#define NANOSHELL_H

// Fonctions de parser.c
char** parse_command(char* line);
void free_args(char** args);
void print_args(char** args);

#endif