void printChar(char); //printChar function declaration
void printString(char*); //printString function declaration
void readString(char*); //readString function declaration

void main() {

	char line[80];
	printString("Enter a line: ");
	readString(line);
	printString(line);


	while(1);
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
				printChar(' ');
				printChar(0x8);
				if (i > 0) { //decreases i index if it is greater than 0
					i--; //this ensures index doesnt go negative
				}
			}
			chars[i] = current; //stores the char in an array
			printChar(current); //prints the typed character
			i++; //increases char array index
		}
		else {
			chars[i] = 0xa; //adds line feed char to array
			printChar(0xa); //prints line feed
			i++;
			chars[i] = 0x0; //adds end of string char to array
			printChar(0x0); //prints end of string char
			run = 0; //turns off the while loop that checks for input
		}
	}
}
