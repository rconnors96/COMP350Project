main(){

	

	char line[80];
	char command[10];
	char buffer[13312];
	int sectorsRead;
	int i = 5;
	int j = 0;

	syscall(0,"SHELL>"); //displays "SHELL>" to the user
	syscall(1, line); //takes input
	
	
		if((line[0] == 't' && line[1] == 'y' && line[2] == 'p' && line[3] == 'e') || (line[0] == 'e' && line[1] == 'x' && line[2] == 'e' && line[3] == 'c')){
			while(line[i] != '\0'){
				command[j] = line[i];
				i++;
				j++;
			}
			if(line[0] == 't' && line[1] == 'y' && line[2] == 'p' && line[3] == 'e'){
				syscall(3, command, buffer, &sectorsRead);
				
				if(sectorsRead > 0){
					syscall(0, buffer);
				}
				else{
					syscall(0,"File not found\n\r");
				}
			}
			if(line[0] == 'e' && line[1] == 'x' && line[2] == 'e' && line[3] == 'c'){
				syscall(4, command);
					syscall(0, "exe file not found\n\r");
			}
			
		}
		else{
			syscall(0, "Bad Command\n\r");
		}
	}

