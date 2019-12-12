enableInterrupts();

main(){

	char line[80];
        char command[80];
        char param[80];
        char buffer[13312];
        int sectorsRead;
        int i;
        int parameterIndex;
        char shell[7];

	shell[0] = 'S';
	shell[1] = 'H';
	shell[2] = 'E';
	shell[3] = 'L';
	shell[4] = 'L';
	shell[5] = '>';
	shell[6] = '\0';


	syscall(0, shell); //displays "SHELL>" to the user
	syscall(1, line); //takes input

	i = 0;
	while (line[i] != ' ') {
		command[i] = line[i];
		i++;
		parameterIndex = i+1;
	}

	i = 0;
	while (line[parameterIndex] != '\0'){
		param[i] = line[parameterIndex];
		i++;
		parameterIndex++;
	}

	if (command[0] == 't' && command[1] == 'y' && command[2] == 'p' && command[3] == 'e'){
		syscall(3, param, buffer, &sectorsRead);
		if (sectorsRead > 0){
			syscall(0, buffer);
		} else {
			syscall(0,"File not found\n\r");
		}
	} else if (command[0] == 'e' && command[1] == 'x' && command[2] == 'e' && command[3] == 'c'){
		syscall(4, param);
		syscall(0, "exe file not found\n\r");
	} else {
		syscall(0, "Bad Command\n\r");
	}
}


