main(){//start of main

	char line[80];
	char command[10];
	char buffer[13312];
	int sectorsRead;
	int i = 5;
	int j = 0;

	syscall(0,"SHELL>"); //displays "SHELL>" to the user
	syscall(1, line); //takes input


	if((line[0] == 't' &&
		 line[1] == 'y' &&
		 line[2] == 'p' &&
		 line[3] == 'e') ||

		 (line[0] == 'e' &&
		 line[1] == 'x' &&
		 line[2] == 'e' &&
		 line[3] == 'c') ||

		(line[0] == 'd' &&
		line[1] == 'i' &&
		line[2] == 'r')){ //command if

		while(line[i] != '\0'){//while
			command[j] = line[i];
			i++;
			j++;
		}//end of while

		if(line[0] == 't' &&
		 line[1] == 'y' &&
		 line[2] == 'p' &&
		 line[3] == 'e'){//type if
			syscall(3, command, buffer, &sectorsRead);

		if(sectorsRead > 0){//read sector if
				syscall(0, buffer);
			}//end of read sector if
			else{//read sector else
				syscall(0,"File not found\n\r");
			}//end of read sector else
		}//end of type if

		if(line[0] == 'e' &&
		line[1] == 'x' &&
	 	line[2] == 'e' &&
	 	line[3] == 'c'){//execute command
			syscall(4, command);
			syscall(0, "exe file not found\n\r");
		}//end of execute command

		if(line[0] == 'd'&&
		line[1] == 'i'&&
		line[2] == 'r'){//dir command
			syscall(0, "dir is working\n\r");
		}
	}//end of command if

	else{//command else
		syscall(0, "Bad Command\n\r");
	}//end of command else

}//end of shell main

