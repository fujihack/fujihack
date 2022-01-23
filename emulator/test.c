// Entry trampoline
void *start();
void *_start() {
	return start();
}

// Test a function in firmware
unsigned int _strcpy();

char buffer[10];

// Code booter
void *start() {
	_strcpy(buffer, "asd");
	return buffer;
}
