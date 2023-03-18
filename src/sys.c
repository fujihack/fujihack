void exit(int status) {
	
}

void abort() {
	
}

long int sys_timestamp() {
	return ((long int)MEM_MS_TIMER)[0];
}

int _gettimeofday() {
	return 0;
}

int _getpid() {
	return -1;
}

int _kill(int pid, int sig) {
	return -1;
}

int _isatty(int fd) {
	return 1;
}

