#include "gamelibrary.h"
#include "repl.h"

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
			printcharacter(3);
            printf("Invalid option. Try again.\n");
			sleep(5);
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

void printcharacter(int index) {
	if (index == 0) {
		fputs(
"\033[38;5;220m"
"                                        .                                       \n"
"                                    .  :-   .                                   \n"
"                                ::  -  -.- -:  -.                               \n"
"                                 :-=.:-...:.:=-:                                \n"
"                                 -.:---==--:-:.                                 \n"
"\033[0m"
"                                =***************                                \n"
"                               *+***+*+++**+****+-                              \n"
"                              #**#=+##*++*#%*=****=                             \n"
"                             .*##     .::.     *#*+                             \n"
"                              #*+ .:::-  ::::: =*#                              \n"
"                        .:.  ::*:.-=+=.  .++=-:.*::                             \n"
"                      . ..-: ..%- ..::..  :::  :#-.-                            \n"
"                       -+--- -.-:  .:...  .:.  .#.-                             \n"
"                        -=+   +#-      :.      :%%                              \n"
"                         ++   %%*     .==.     *#%=                             \n"
"                         :*    +# =          ::+%                               \n"
"                          +      -..-+#**#+-:::                                 \n"
"                          =:    ****#+*##*+*****                                \n"
"                          +-   =-:-.-*#*+#*-::--=                               \n"
"                         . .:+*###%#*+---+**#%#%*                               \n"
"                          . **#*#%#***=--=***#*#*                               \n"
"                           *:  *##%###*#*=###%*##                               \n"
"                           ++  *##%##*#**#**#%**#                               \n"
"                           =*  *###*#******#** .*:                              \n"
"                           := :*#%************%#*=                              \n"
"                            = +*###%%*++++*#@###*#                              \n"
"                            +.**###%*#%##%#*####*#                              \n"
"                            #= #=  +**#==***+  -#:                              \n"
"                            +*     ++*:  -+++                                   \n"
"                             :    ==-:   .--==                                  \n"
"\033[0m",
stdout);

} else if (index == 1) {
    fputs(
"\033[0;32m" // Verde
"        +                                                                       \n"
"       .. =                                                                     \n"
"       - .. =                                                                    \n"
"       :......-                                                                 \n"
"      * ...... +                                                                 \n"
"      -....:...:                                                                 \n"
"      -....=....:                         =*                                    \n"
"       -....-.. #                   *%+#=+++*---:         ++#--                 \n"
"       .....-.  ..              # *++++++++++++++*=       @%=#                  \n"
"        *...:= ..-             #+++++++++++++++++++**   :%##                    \n"
"         -...= ..=            #*+**+#%*+++*%##=*#++*:  ++#+                     \n"
"         =........*           #+*.....:*#+:......***- *##+                      \n"
"          *...-...=     =-===.-*+...........=:...*+#*%+=.+                      \n"
"           .. .=....      ==+--%-+=..:-...-::==+-***:+*:%                       \n"
"           *. .-:..+      ==--*%....@*=+=+=*@* =.+#=+--+=*                      \n"
"            = .:=..-.      +.-*%..-=-*--:.-*--*:..-:+:=%+**                     \n"
"            - ..+:..+        +:+*....-+::=+...=:.+-.-%#.                        \n"
"             %...=..-          ==......-=::*.=...-%+:.:-:*%-         -*.+       \n"
"              -..=..:=       %. *...:..........::#=......=*#+=-.  -#..:%*@#:    \n"
"              +...*..*     -....:*%=..........:#%+.....:#*#%*#++*::-.*=::+*     \n"
"               *.==+##+*=+ +#:..*#%++#+=-==#*+#*=*+:.-=*%*+#++++=:-*%=--+*.     \n"
"              -#++*===+#=  :%**+#%*::*+===*#+::-*%*++++%*++%+#++**=--*+:=+      \n"
"            ====+####-:+#+*+@#**=......=.........****#%%%%%%%#%#-               \n"
"             .  :=.-*.+-+++*+*+#-......-..........+*%+                          \n"
"                 +..-##-+++*+%***....-==-=-......-=**                           \n"
"                  %-.:#+%####*. -:-=:..-...:==---=+#                            \n"
"                   .**#+        +##+==*****=--+*###%                            \n"
"                     ##%.       *++++*#+**+#**+#+#*%                            \n"
"                     =+:+=     +..:*%#+###+%#%@#=:..=                           \n"
"                     -##+    -=...:*@++++++++#==.....:                          \n"
"                             +*+--*%++#@@@@@#+*#*.:=#+#                         \n"
"                              %*#%*++#+     =#++%%#**%                          \n"
"                             *#%@%%%%=        %###%%%%*                         \n"
"                             *+++++*#:        %*++++++*                         \n"
"                             #*++++*#          %*++++#*                         \n"
"                          -##*++++*#:          -#*+++**#*                       \n"
"                        =#+++++++**%.          -#**+++++++%                     \n"
"\033[0m", // reset cor
stdout);

} else if (index == 2) {
	//Printar chief elf

} else if (index == 3) {
	//Print mapa
	    fputs(
"\033[0m"
"                          +-----------------------+\n"
"                          |\033[38;5;46m     North Dungeon     \033[0m|\n"
"                          +-----------------------+\n"
"                                   |\n"
"                                   |\n"
"   +-------------------+   +-----------------------+   +-------------------+\n"
"   |\033[38;5;46m   Elf's Lair      \033[0m|---|\033[38;5;46m      City Hall        \033[0m|---|\033[38;5;46m   Goblin's Den    \033[0m|\n"
"   +-------------------+   +-----------------------+   +-------------------+\n"
"                                   |\n"
"                                   |\n"
"                          +-----------------------+\n"
"                          |\033[38;5;46m     South Dungeon     \033[0m|\n"
"                          +-----------------------+\n"
"\033[0m", stdout);


} else if (index == 4) {
    fputs(
    "\033[38;5;220m" // Dourado
"     ____________________________________________\n"
"    /                                            \\\n"
"   /                                              \\\n"
"  |   ~~~~~~~~~~~~~~~~~ QUEST SCROLL ~~~~~~~~~~~~  |\n"
"  |                                                |\n"
"  |   Quest: The Goblin King's Wrath               |\n"
"  |                                                |\n"
"  |   \"The goblin mafia tightens its grip on       |\n"
"  |   Ogama. The cunning Gobbi plots from the      |\n"
"  |   shadows. Uncover his lair, sabotage his      |\n"
"  |   network, and decide: will you dethrone       |\n"
"  |   the king... or join him?\"                    |\n"
"  |                                                |\n"
"  |   Objectives:                                  |\n"
"  |     - Investigate goblin smuggling routes      |\n"
"  |     - Locate Gobbi's hideout                   |\n"
"  |     - Choose your fate                         |\n"
"  |                                                |\n"
"  |   Reward: ???                                  |\n"
"  |                                                |\n"
"  |   ------------------------------------------   |\n"
"  |   Accept the quest? (yes/no)                   |\n"
"   \\                                              /\n"
"    \\____________________________________________/\n"
"\033[0m", stdout); // Reset cor
}

}

