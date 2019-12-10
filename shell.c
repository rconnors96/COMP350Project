main(){
	char line[80];
	char command[10];
	char buffer[13312];
	char filename[80];
	char dir[512];
	int sectorsRead;
	int i = 5;
	int j = 0;

	 syscall(0, "shell>");//displays "SHELL>" to the user
	syscall(1, line); //takes input
	if(line[0] == 't' && line[1] == 'y' && line[2] == 'p' && line[3] == 'e'){
		while(line[i] != '\0'){
			command[j] = line[i];
			i++;
			j++;
		}
		syscall(3, command, buffer,&sectorsRead);
		if(sectorsRead > 0){
		syscall(0, buffer);
		}
		else{
			syscall(0,"File not found\n\r");
		}
	}


	if(line[0] == 'e' && line[1] == 'x' && line[2] == 'e' && line[3] == 'c'){
		while(line[i] != '\0'){
			command[j] = line[i];
			i++;
			j++;
		}
		syscall(4, command);
		syscall(0, "exe file not found\n\r");
	}

	if(line[0] == 'd' && line[1] == 'i' && line[2]== 'r'){
		syscall(2, dir, 2);
		for(i = 0; i < 512; i=i+32){
			if(dir[i]!= '\0'){
				for(j= 0; j < 6; ++j){
					filename[j] = dir[i+j];
				}
				syscall(0, filename);
				syscall(0, "\n\r");
			}
		}
	}
	
}

