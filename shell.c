#include <stdio.h>

main(){

	char line[80];
	char command[10];
	char param[70];
	char buffer[13312];
	int sectorsRead;
	int i = 0;
	int j;
	int parameterIndex;

	for (j=0; j<80; j++) {
		line[j] = 0;
	}

	syscall(0,"SHELL>"); //displays "SHELL>" to the user
	syscall(1, line); //takes input

	while(line[i] != ' ') {
		command[i] = line[i];
		i++;
		parameterIndex = i+1;
	}
	i = 0;
	while(line[parameterIndex] != '\0'){
		param[i] = line[parameterIndex];
		i++;
		parameterIndex++;
	}

	i = 0;
	if((command[0] == 't' && command[1] == 'y' && command[2] == 'p' && command[3] == 'e') || (command[0] == 'e' && command[1] == 'x' && command[2] == 'e' && command[3] == 'c') || (command[0] == 'd' && command[1] == 'i' && command [2] == 'r')) {
		if(command[0] == 't' && command[1] == 'y' && command[2] == 'p' && command[3] == 'e'){
			syscall(3, param, buffer, &sectorsRead);
			if(sectorsRead > 0){
				syscall(0, buffer);
			}
			else{
				syscall(0,"File not found\n\r");
			}
		} else if(command[0] == 'e' && command[1] == 'x' && command[2] == 'e' && command[3] == 'c'){
			syscall(4, param);
			syscall(0, "exe file not found\n\r");
		} else if(command[0] == 'd' && command[1] == 'i' && command [2] == 'r') {
			syscall(2, buffer, 2); //reads sector 2 (the directory) into buffer
			for (i=0; i < 512; i = i+32) {
				if(buffer[i] != '\0') { //doesnt print deleted files
					for (j = i; j < (i+6); j++) {
						syscall(0, buffer[j]);
					}
				}
			}
		}
	}
	else{
		syscall(0, "Bad Command\n\r");
	}
}

