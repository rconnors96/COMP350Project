void printChar(char); //printChar function declaration
void printString(char*); //printString function declaration

void main() {

	printChar('F');


	while(1);
}

void printChar(char c) {
        char al = c;
        interrupt(0x10,0xe*256+al,0,0,0);
}

void printString(char* chars) {
	int i=0;
}

