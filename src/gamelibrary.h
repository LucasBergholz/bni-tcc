#ifndef GAMELIBRARY_H
#define GAMELIBRARY_H

#include <stdio.h>  // se usa printf
#include <stdlib.h> // se precisar de malloc/free
#include <unistd.h>
#include <string.h>

typedef struct {
    const char *action;
    const char *text;
} action_text;

void printheader(void);
void printmenu(void);
void printcharacter(int index);
void replmenu(void);
void print_action_text(const char *action);

#endif

