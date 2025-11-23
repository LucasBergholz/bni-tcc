#include "repl.h"

int SIZENAMES = 30;
char **action_names = NULL;
int race = 0;
char player_name[21];

int main(void) {
	rl_attempted_completion_function = action_name_completion;
	replmenu();
	initialize();
	action_names = malloc(SIZENAMES * sizeof(char*));
	if (action_names == NULL) perror("Error allocating initial memory for action_names"), exit(1);
	char *input, sactions[] = "/tmp/actions.XXXXXX";
	int iactions = mkstemp(sactions);
	if (race == 1) init_human();
	else if (race == 2) init_elf();
	else if (race == 3) init_goblin();
	for ( ; ; ) {
		if (checktrue_goal())
			if(!ask_yes_no("Goal has been hit! Do u want to continue? (y/N)\n")) break;
		printf("\nPlease enter one of the currently available actions:\n");
		check_show_actions(sactions);
		show_actions(sactions);
		input = readline(">> ");
		if (!input || strcmp(input, "quit") == 0 || strcmp(input, "exit") == 0) break;
		if (*input) add_history(input);
		char ar = apply_actions(input);
		if (ar == 2) printf("\033[31;1mATTENTION: \033[90mUnrecognised command. Check spelling and try again.\033[0m\n");
		else if (ar == 1) printf("\033[31;1mATTENTION: \033[90mAction with invalid parameters.\033[0m\n");
		free_names(), free(input);
	}
	free_names(), free(action_names);
	// free(input), 
	remove(sactions);
	return 0;
}

char** action_name_completion(const char *text, int start, int end) {
	rl_attempted_completion_over = 1;
	return rl_completion_matches(text, action_name_generator);
}

char* action_name_generator(const char *text, int state) {
	static int list_index, len;
	char *name;
	if (!state) {
		list_index = 0;
		len = strlen(text);
	}
	while ((name = action_names[list_index++]))
		if (strncmp(name, text, len) == 0)
			return strdup(name);
	return NULL;
}

void show_actions(const char *filename) {
	FILE *f = fopen(filename, "r");
	if (f == NULL) perror("Error opening file for action_names"), exit(1);
	int i = 0;
	char str[500];
	while (fscanf(f, "%[^\n]s", str) != EOF) {
		fscanf(f, "\n");
		if (i == SIZENAMES-1) {
			SIZENAMES *= 2; 
			action_names = realloc(action_names, SIZENAMES * sizeof(char*)); 
			if (action_names == NULL) perror("Error reallocating memory for action_names"), exit(1);
		}
		printf("  - %s\n", str);
		action_names[i] = malloc(strlen(str) + 1);
		if (action_names[i] == NULL) perror("Error allocating memory for action names"), exit(1);
		strcpy(action_names[i++], str);
	}
	action_names[i] = NULL;
	fclose(f);
}

void free_names(void) {
	int i = 0;
	while (action_names[i] != NULL)
		free(action_names[i++]);
	action_names[0] = NULL;
}

int ask_yes_no(const char *question) {
	char *response;
	for ( ; ; ) {
		response = readline(question);
		if (!response) {
			printf("\nEnd of input detected.\n");
			return 0;
		}
		to_uppercase(response);
		if (strcmp(response, "Y") == 0 || strcmp(response, "YES") == 0) {
			free(response);
			return 1;
		} else if (strcmp(response, "N") == 0 || strcmp(response, "NO") == 0 || (response && response[0] == '\0')) {
			free(response);
			return 0;
		}
		free(response);
		printf("Please answer Y or N.\n");
	}
}

void to_uppercase(char *str) {
	for (int i = 0; str[i] != '\0'; i++)
		str[i] = toupper((unsigned char) str[i]);
}

void printheader(void) {
	const char *header =
		"\033[90m################################################################################################\n"
		"\033[90m# " "\033[31m _             _     \033[32m _____   \033[33m _____   \033[34m _____   \033[35m _          \033[36m _____  \033[37m ______ \033[91m _____   _"       "       \033[90m#\n" 
		"\033[90m# " "\033[31m| |           (_)   \033[32m |  __ \\ \033[33m |  __ \\ \033[34m |  __ \\ \033[35m | |        \033[36m |  __ \\ \033[37m|  ____|\033[91m|  __ \\ | |"   "      \033[90m#\n"
		"\033[90m# " "\033[31m| |__   _ __   _    \033[32m | |__) |\033[33m | |  | |\033[34m | |  | |\033[35m | |        \033[36m | |__) |\033[37m| |__   \033[91m| |__) || |"        "      \033[90m#\n"
		"\033[90m# " "\033[31m| '_ \\ | '_ \\ | |   \033[32m |  ___/  \033[33m| |  | |\033[34m | |  | |\033[35m | |        \033[36m |  _  / \033[37m|  __|  \033[91m|  ___/ | |"      "      \033[90m#\n"
		"\033[90m# " "\033[31m| |_) || | | || |   \033[32m | |      \033[33m| |__| | \033[34m| |__| |\033[35m | |____    \033[36m | | \\ \\ \033[37m| |____ \033[91m| |     | |____"  "  \033[90m#\n"
		"\033[90m# " "\033[31m|_.__/ |_| |_||_|   \033[32m |_|      \033[33m|_____/  \033[34m|_____/  \033[35m|______|   \033[36m |_|  \\_\\\033[37m|______|\033[91m|_|     |______|" " \033[90m#\n"
		"\033[90m################################################################################################\n"
		"\033[0m";
	printf("\e[1;1H\e[2J");
	printf("%s\n", header);
}

void printmenu(void) {
	printf("\e[1;1H\e[2J");
	    // Códigos ANSI para cores
    const char *RESET = "\033[0m";
    const char *YELLOW = "\033[1;33m";
    const char *GREEN = "\033[1;32m";
    const char *CYAN = "\033[1;36m";
    const char *MAGENTA = "\033[1;35m";

    printf(
"%s  ====================================================\n"
"  ||                                               ||\n"
"  ||          ***  GOBBI'S GOBLINS  ***            ||\n"
"  ||               A Medieval RPG                  ||\n"
"  ||                                               ||\n"
"  ====================================================\n"
"                 \\      ^__^\n"
"                  \\     (oo)\\_______\n"
"                        (__)\\       )\\/\\\n"
"                            ||----- |\n"
"                            ||     ||\n\n"
"%s                  =========================\n"
"                  ||  [1] Start Game     ||\n"
"                  ||  [2] Instructions   ||\n"
"                  ||  [3] About the Game ||\n"
"                  ||  [4] Exit Game      ||\n"
"                  =========================\n\n"
"  ----------------------------------------------------\n"
"   \"In the land of Ogama, goblins roam and chaos reigns.\n"
"    Dare you challenge the cunning Gobbi and his horde?\"\n"
"  ----------------------------------------------------%s\n"
"\n"
"                 \033[90mdeveloped by\033[0m \033[1;35mLucas Bergholz\033[0m \n",
        YELLOW,     // start title color
        CYAN, RESET   // Footer
    );
}

void replmenu(void) {
    int choice = 0;
    while (1) {
        system("clear");
        printmenu();
        printf("\nSelect an option: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }

        if (choice == 1) {
            printf("\nStarting the game...\n");
            break;
        } else if (choice == 2) {
            printf("\n--- Instructions ---\n");
            printf("This game was developed by Lucas Bergholz for his undergraduate thesis.\n\n");
			printf("Gobbi’s Goblins is entirely played through the terminal. Every turn, the system\n");
			printf("presents a set of available actions derived from the current game state.\n\n");

			printf("To interact, simply type the number corresponding to the action you wish to take.\n");
			printf("Actions may include talking to characters, exploring regions, or engaging in\n");
			printf("confrontations. Each choice dynamically changes the world state and influences\n");
			printf("the possible endings of the game.\n\n");

			printf("The quest system is central to progression. At any given time, only one quest\n");
			printf("can be active. You are free to attempt any number of quests throughout the\n");
			printf("gameplay. These quests enrich the narrative and reshape the conditions of the world\n");
			printf("corresponding to the actions you take. They are NOT mandatory to finish the game.\n\n");

			printf("Only two quests are truly essential: the confrontation with Gobbi, as this is the\n");
			printf("central point of the  narrative, and the final quest that determines the ending of\n");
			printf("the simulation. Every decision you make influences how these final states are\n");
			printf("reached, and which version of Ogama’s fate is going to happen.\n\n");

            printf("Type 'quit' or 'exit' to leave the game.\n");
            printf("Press ENTER to return to the menu.\n");
            getchar(); getchar();
        } else if (choice == 3) {
            printf("\n--- About the Game ---\n\n\n");
		    printf("Ogama, once a thriving kingdom, now suffers under the rule of King Jekyll Hyde.\n");
			printf("The city’s walls strain under overpopulation, food shortages, and rampant crime.\n");
		    printf("In the shadows of Goblin’s Den, a charismatic rebel named Gobbi rises, a cunning\n");
	        printf("leader who gathers the oppressed and builds a mafia that challenges the crown.\n\n");

			printf("Hyde, desperate to maintain order, secretly enlists the player: a neutral agent\n");
	        printf("tasked with dismantling Gobbi’s network. But as your mission unfolds, the moral\n");
		    printf("divides blur, Gobbi’s rebellion may not be pure chaos, and Hyde’s justice may\n");
			printf("hide something darker.\n\n");

			printf("In a story filled with nuances and different sides of the same coin, who will YOU\n");
			printf("choose to rule the chaotic kingdom of Ogama?");
			printf("Press ENTER to return to the main menu.\n");
			getchar(); getchar();
        } else if (choice == 4) {
            printf("\nGoodbye, adventurer!\n");
            exit(0);
        } else {
            printf("Invalid option. Try again.\n");
        }
    }

    printf("\n\nSelect a name for your character:\n");
	scanf("%20s", &player_name);
	choice = 0;
    while (1) {
        system("clear");
        printf("\n\nSelect a race for %s:\n", player_name);
		printf(
"                  =========================\n"
"                  ||  [1] Human          ||\n"
"                  ||  [2] Elf            ||\n"
"                  ||  [3] Goblin         ||\n"
"                  =========================\n\n");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }

        if (choice == 1) {
			race = 1;
			break;
        } else if (choice == 2) {
			race = 2;
			break;
        } else if (choice == 3) {
			race = 3;
			break;
		} else {
            printf("Invalid option. Try again.\n");
        }
    }

}
