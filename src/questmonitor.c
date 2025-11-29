#include "questmonitor.h"

void create_problem_file(const char* domain_name, const char* problem_name, const char* ending) {
	FILE* f = fopen(problem_name, "w");
	if (!f) {
		printf("Erro ao criar arquivo problema: %s\n", problem_name);
		return;
	}

	// Pega world state
	char vetorFuncs[10][100];
	memset(vetorFuncs, 0, sizeof(vetorFuncs));
	check_show_functions(1, vetorFuncs);

    char vetorPreds[100][100];
    memset(vetorPreds, 0, sizeof(vetorPreds));
    check_shows(1, vetorPreds);

	fprintf(f,
	    "(define (problem %s)\n"
	    "\t(:domain %s)\n"
		"\t(:objects )\n"
	    "\t(:init\n",
	    problem_name,
	    domain_name
	);

    // imprime predicados
	for(int i = 0; i < 100; i++){
	    if (vetorPreds && vetorPreds[i][0] != '\0') {
			fprintf(f, "\t\t%s", vetorPreds[i]);
		}
	}

    // imprime funcoes
	for(int i = 0; i < 10; i++){
		if (vetorFuncs && vetorFuncs[i][0] != '\0') {
			fprintf(f, "\t\t%s", vetorFuncs[i]);
		}
	}

    fprintf(f,
        "\n\t)\n"
        "(:goal (and (%s) (gameover)))\n"
        ")\n", ending);

    fclose(f);
}

void check_endings() {
	create_problem_file("gamedomain", "problem.pddl", "gobbiking");
    system("cd team-1 && ./run-opt-lnp-1 ../game/gamedomain.pddl ../problem.pddl plan > /dev/null 2>&1 && cat plan && rm plan"); //> /dev/null 2>&1");
	system("rm problem.pddl");
}
