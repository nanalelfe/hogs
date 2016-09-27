#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

	if (argc < 2){
		printf("Usage: %s [-m | -c] username", argv[0]);
		return 1;
	}

	if (argc > 3){
		printf("Usage: %s [-m | -c] username", argv[0]);
		return 1;
	}

	// ARGUMENT VARIABLES:

	char function;
	char *username;

	if (argc < 3){
		function = 'c';
		username = argv[1];
	}
	else{
		function  = argv[1][1];
		username = argv[2];
	}

	// TEMPORARY SCANNING VARIABLES:

	char first_line[73];
	char username_parsed[128];
	long pid;
	double cpu;
	double mem;
	char command[128]; 

	// STORING VARIABLES:

	long pid_stored = -1;
	double cpu_stored = -1;
	double mem_stored = -1; 
	char command_stored[128] = "";

	// Read first line to ignore it
	scanf("%72[^\n]", first_line);

	/* Reads the standard input until end of line. Ignores irrelevant
	 * information, such as VSZ and RSS. 
	 * Stores all the relevant information into the temporary variables. 
	 */
	while (scanf("%s %ld %lf %lf %*d %*d %*s %*s %*s %*s %127[^\n]",
	 username_parsed, &pid, &cpu, &mem, command) != EOF){

		// only executes if the username read from the input matches the 
		// username specified as an argument.
		if (strcmp(username, username_parsed) == 0){

			// check which function was demanded from the command-line,
			// and store the information in the storing variables depending 
			// on it.
			if (function == 'c'){
				if (cpu_stored < cpu){
					pid_stored = pid;
					cpu_stored = cpu;
					mem_stored = mem;
					strncpy(command_stored, command, sizeof(command_stored));
					command_stored[127] = '\0';
				}

				// in case of a tie, store the information depending on 
				// which processes command comes alphabetically first. 
				else if (cpu_stored == cpu){
					int comp = strcasecmp(command, command_stored);
					if (comp < 0){
						pid_stored = pid;
						cpu_stored = cpu;
						mem_stored = mem;
						strncpy(command_stored, command, sizeof(command_stored));
						command_stored[127] = '\0';
					}

				}
			}

			if (function == 'm'){
				if (mem_stored < mem){
					pid_stored = pid;
					cpu_stored = cpu;
					mem_stored = mem;
					strncpy(command_stored, command, sizeof(command_stored));
					command_stored[127] = '\0';
				}
				// in case of a tie, store the information depending on 
				// which processes command comes alphabetically first. 
				else if (mem_stored == mem){
					int comp = strcasecmp(command, command_stored);
					if (comp < 0){
						pid_stored = pid;
						cpu_stored = cpu;
						mem_stored = mem;
						strncpy(command_stored, command, sizeof(command_stored));
						command_stored[127] = '\0';
					}

				}

			}

		}

	}

	/* Checking if pid_stored is still at its initial value, since if that's
	 * that case, it means that there are no processes owned by the specified
	 * username, in which case don't do anything
	 */

	if (pid_stored != -1){
		switch(function){

			case 'c' : printf("%ld\t%.1f\t%s\n", pid_stored, cpu_stored, command_stored);
						break;
			case 'm' : printf("%ld\t%.1f\t%s\n", pid_stored, mem_stored, command_stored);
					        break;

		}

	}

	return 0;
}


