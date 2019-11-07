	void printChar(char); 		//printChar function declaration
	void printString(char*); 	//printString function declaration
	void readString(char*); 	//readString function declaration
	void readSector(char*); 		// read sector
	void handleInterrupt21(int, int, int, int); //handle's interrupt 21
	void readFile(char*,char*,int);

void main() {

	char buffer[13312];   /*this is the maximum size of a file*/
	int sectorsRead;
	makeInterrupt21(); 
	interrupt(0x21, 3, "messag", buffer, &sectorsRead);   /*read the file into buffer*/ 
	if (sectorsRead>0)
		interrupt(0x21, 0, buffer, 0, 0);   /*print out the file*/ 
	else
		interrupt(0x21, 0, "messag not found\r\n", 0, 0);  /*no sectors read? then print an error*/
	while(1);   /*hang up*/ 
}

void printChar(char c) {
        char al = c;
        interrupt(0x10,0xe*256+al,0,0,0);
}

void printString(char* chars) {
	int i=0;
	while (chars[i] != 0x0) {
		printChar(chars[i]);
		i++;
	}
}

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

	if(ax > 3){//error check
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
	}
	if(ax == 3){
		readFile(bx,cx,dx);
	}// end of sector


}//end of handle 21

void readSector(char* buffer ,int sector){// start of readSector

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

void readFile(char* fileName, char* buffer, int sectorsRead) {
	char dir[512];
	readSector(dir,512);

	int numberOfLoops = 1; //for testing the for loop

	for(int fileEntry; fileEntry < 512 ; fileEntry+=32) {
		sectorsRead++;
		if(fileName[0]==dir[fileEntry+0] && fileName[1]==dir[fileEntry+1] && fileName[2]==dir[fileEntry+2] && fileName[3]==dir[fileEntry+3] && fileName[4]==dir[fileEntry+4] && fileName[5]==dir[fileEntry+5]) {
			for(int i = 6; i < 32; i++) {
				readSector(buffer, dir[fileEntry+i]);
				buffer += 512;
			}
		}
		numberOfLoops++; //testing the for loop
		printChar(numberOfLoops); //testing the for loop
	}
}
