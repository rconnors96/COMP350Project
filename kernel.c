	void printChar(char); 		//printChar function declaration
	void printString(char*); 	//printString function declaration
	void readString(char*); 	//readString function declaration
	void readSector(char); 		// read sector
	void handleInterrupt21(int, int, int, int); //handle's interrupt 21
	void readFile(char*,char*,int*);	// read file
	void executeProgram(char*);		// execute program
	void terminate();			//terminate
	void writeSector();			//write sector

void main() {//main

	makeInterrupt21();			//creates our interrupt handler
	interrupt(0x21, 4, "shell", 0, 0);	//uses the interrupt handler and runs shell
	while(1);				// fail safe
}//end of main

void writeSector(){//write sector

	//parameter set up
	int AH = 2;
	int AL = 1;
	int BX = buffer;
	int CH = 0;
	int CL = sector + 1;
	int DH = 0;
	int DL = 0x80;

	//more parameter set up
	int AX = 6;
	int CX = CH*256+CL;
	int DX = DH*256+DL;

	//interrupt
	interrupt(0x13, AX, BX, CX, DX);
}//end of write sector

void terminate(){//terminate

	char shellname[6];	// creates char array
	shellname[0]='s'; 	//loads shell into it
	shellname[1]='h';
	shellname[2]='e';
	shellname[3]='l';
	shellname[4]='l';
	shellname[5]='\0';

	executeProgram(shellname);	//executes shellname
}//end of terminate

void executeProgram(char* name) {//execute program

	int i;			// integer
	int sectorsRead;	// sector read
	char buffer[13312];	// buffer of 13312

	readFile(name, buffer, &sectorsRead);//read file

	if(sectorsRead == 0){return;}		//if sector is zero, leave
	for(i=0; i<13312; i++) {		//if not
		putInMemory(0x2000,i,buffer[i]);//put into memory untill i is 13311
	}//end of if not

	launchProgram(0x2000);//launch program in 0x2000
}//end of execute program

void readFile(char* name, char* buffer, int* sectorsRead){
	int i = 0;
	int j = 6;
	int *sectorRead;
	char dir[512];
	*sectorsRead = 0;
	interrupt(0x21,2,dir,2,0);
	for(i = 0; i <512; i=i+32){//start of for loop 1
	//printChar(dir[i]);
	//printChar(dir[i+1]);
	//printChar(dir[i+2]);
	//printChar(dir[i+3]);
	//printChar(dir[i+4]);
	//printChar(dir[i+5]);
	//printChar('h');
		if(name[0] == dir[i+0]&&
			name[1] == dir[i+1] &&
			name[2] == dir[i+2] &&
			name[3] == dir[i+3] &&
			name[4] == dir[i+4] &&
			name[5] == dir[i+5]){ //if
			*sectorsRead = 1;

			for(j =i+ 6; dir[j]!=0; j+=32){//for loop 2
				interrupt(0x21,2,buffer,dir[j],0);
 				buffer = buffer + 512;
			}//end of for loop 2
		}//end of if
	}//end of for loop 1
}//end of read file

void printChar(char c) {//print char
        char al = c;
        interrupt(0x10,0xe*256+al,0,0,0);
}//end of print char

void printString(char* chars) {//print string
	int i=0;
	while (chars[i] != 0x0) {//while
		printChar(chars[i]);
		i++;
	}//end of while
}//end of print string

void readString(char* chars) {
	int i = 0;
	int run = 1;
	while (run == 1) {
		char current = interrupt(0x16,0,0,0,0); //sets user-entered char to current
		if (current != 0xd) { //checks if char is "Enter"
			if (current == 0x8) { //checks if char is "Backspace"
				if (i > 0) { //decreases i index if it is greater than 0
					i--; //this ensures index doesnt go negative
				}
			printChar(current);
			printChar(' ');
			}
			chars[i] = current; //stores the char in an array
			printChar(current); //prints the typed character
			i++; //increases char array index
		}
		else {
			chars[i] = 0x0; //adds line feed char to array
			i=0;
			printChar(0x0); //prints line feed
			printChar(0xa); //prints end of string char
			printChar(0xd);
			run = 0; //turns off the while loop that checks for input
		}
	}
}



void handleInterrupt21(int ax, int bx, int cx, int dx) {//start of handle 21

	if(ax > 5){//error check
		interrupt(0x21,0,"Eror Interupt Nt Dfined",0,0);
	}//end of check

	if (ax == 0){// print String
		printString(bx);
	}// end of print string

	if (ax == 1){// read string
		readString(bx);
	}// end of read string

	if(ax == 2){// read sector
		readSector(bx, cx);
	}// end of sector
	if(ax == 3){
		readFile(bx,cx,dx);
	}

	if(ax == 4){
		executeProgram(bx);
	}
	if(ax==5){
		terminate();
	}
	if(ax==6){
		writeSector();
	}

}//end of handle 21

void readSector(char*buffer ,int sector){// start of readSector

	// parameter set up
	int AH = 2;
	int AL = 1;
	int BX = buffer;
	int CH = 0;
	int CL = sector+1;
	int DH = 0;
	int DL = 0x80;

	// more parameter set up (simple input)
	int AX = AH*256+AL;
	int CX = CH*256+CL;
	int DX = DH*256+DL;

	// actual interrupt taking in simple input
	interrupt(0x13, AX, BX, CX, DX);

} // end of readSector
