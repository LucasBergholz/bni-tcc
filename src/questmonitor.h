#ifndef QUESTMONITOR_H
#define QUESTMONITOR_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void create_problem_file(const char* domain_name, const char* problem_name, const char* ending);
void check_endings();

#endif

