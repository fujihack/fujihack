// Basic temporary libc

int gdivmod(int a, int b, int o) {
	int di = 0;
	int re = 0;
	while (a != 0) {
		re++;
		di = 0;
		while (di != b) {
			if (a == 0) {
				break;
			}
			
			di++;
			a--;
		}
	}

	if (di == b) {
		di = 0;
	} else {
		re--;
	}
	
	if (o) {
		return di;
	}

	return re;
}

int strlen(char *buffer) {
	int a = 0;
	while (*buffer != 0) {
		buffer++;
		a++;
	}

	return a;
}

int strcmp(char *s1, char *s2) {
	while(*s1 && (*s1 == *s2)) {
		s1++;
		s2++;
	}

	return *(unsigned char*)s1 - *(unsigned char*)s2;
}

void *memcpy(void* dest, const void* src, int count) {
	char* dst8 = (char*)dest;
	char* src8 = (char*)src;
	while (count--) {
		*dst8++ = *src8++;
	}
	
	return dest;
}

void *memset(void *dest, int val, int len) {
	unsigned char *ptr = dest;
	while (len-- > 0) {
		*ptr++ = val;
	}
	
	return dest;
}
