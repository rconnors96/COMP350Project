void main() {

	char line[80];
	char command[10];
	char parameter[70];
	int i;
	int paramStart;

        while(1){
		syscall(0,"SHELL>"); //displays "SHELL>" to the user
		syscall(1, line); //takes input
		i=0;
		while(line[i] != ' ') { //checks the first word in input (launch, open, print, etc)
			command[i] = line[i];
			i++;
			paramStart = i+1; //this shows where to start in line when checking what user wants to print/open
		}
		i=0;
		while(line[paramStart] != '\0') {
			parameter[i] = line[paramStart];
			i++;
			paramStart++;
		}
		syscall(0,"Bad Command");
	}
}
